// SPDX-License-Identifier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Shared descriptors for CAAM black key
 * and blob encapsulation/decapsulation
 *
 * Copyright 2018-2020 NXP
 */
#include "caamkeyblob_desc.h"

/* Size of tmp buffer for descriptor const. */
#define INITIAL_DESCSZ 64

/*
 * Construct a black key conversion job descriptor
 *
 * This function constructs a job descriptor capable of performing
 * a key blackening operation on a plaintext secure memory resident object.
 *
 * @desc          : Pointer to a pointer to the descriptor generated by this
 *                  function. Caller will be responsible to kfree() this
 *                  descriptor after execution.
 * @key           : Pointer to the plaintext, which will also hold
 *                  the result. Since encryption occurs in place, caller must
 *                  ensure that the space is large enough to accommodate the
 *                  blackened key
 * @key_len       : Size of the plaintext
 * @black_key     : DMA address of the black key obtained from hardware
 * @black_key_len : Size of the black key
 * @key_enc       : Encrypted Key Type (AES-ECB or AES-CCM)
 * @trusted_key   : Trusted Key (use Job Descriptor Key Encryption Key (JDKEK)
 *                  or Trusted Descriptor Key Encryption Key (TDKEK) to
 *                  decrypt the key to be loaded into a Key Register).
 *
 * Return         : '0' on success, error code otherwise
 */
int cnstr_desc_black_key(u32 **desc, char *key, size_t key_len,
			 dma_addr_t black_key, size_t black_key_len,
			 u8 key_enc, u8 trusted_key)
{
	u32 *tdesc, tmpdesc[INITIAL_DESCSZ];
	u16 dsize;
	u32 bk_store;
	u32 key_length_for_desc = key_len;

	/* Trusted key not supported */
	if (trusted_key != UNTRUSTED_KEY)
		return -EOPNOTSUPP;

	memset(tmpdesc, 0, sizeof(tmpdesc));

	init_job_desc(tmpdesc, 0);

	/*
	 * KEY commands seems limited to 32 bytes, so we should use the load
	 * command instead which can load up to 64 bytes.
	 * The size must also be loaded.
	 *
	 * TODO: The KEY command indicate it should be able to load key bigger
	 * than 32bytes but it doesn't work in practice
	 *
	 * TODO: The LOAD command indicate it should be able to load up to 96
	 * byte keys it doesn't work in practice and is limited to 64 bytes
	 */

	/* Load key to class 1 key register */
	append_load_as_imm(tmpdesc, (void *)key, key_length_for_desc,
			   LDST_CLASS_1_CCB | LDST_SRCDST_BYTE_KEY);

	/* Load the size of the key */
	append_load_imm_u32(tmpdesc, key_length_for_desc, LDST_CLASS_1_CCB |
			    LDST_IMM | LDST_SRCDST_WORD_KEYSZ_REG);

	/* ...and write back out via FIFO store*/
	bk_store = CLASS_1;
	if (key_enc == KEY_COVER_ECB)
		bk_store |= FIFOST_TYPE_KEY_KEK;
	else
		bk_store |= FIFOST_TYPE_KEY_CCM_JKEK;

	/* Save the key as black key in memory */
	append_fifo_store(tmpdesc, black_key, black_key_len, bk_store);

	dsize = desc_bytes(&tmpdesc);

	/* Now allocate execution buffer and coat it with executable */
	tdesc = kmemdup(tmpdesc, dsize, GFP_KERNEL | GFP_DMA);
	if (!tdesc)
		return -ENOMEM;

	*desc = tdesc;

	print_hex_dump_debug("black key desc@" __stringify(__LINE__) ":",
			     DUMP_PREFIX_ADDRESS, 16, 4, *desc,
			     desc_bytes(*desc), 1);

	return 0;
}
EXPORT_SYMBOL(cnstr_desc_black_key);

/*
 * Construct a black key using RNG job descriptor
 *
 * This function constructs a job descriptor capable of performing
 * a key blackening operation on RNG generated.
 *
 * @desc          : Pointer to a pointer to the descriptor generated by this
 *                  function. Caller will be responsible to kfree() this
 *                  descriptor after execution.
 * @key_len       : Size of the random plaintext
 * @black_key     : DMA address of the black key obtained from hardware
 * @black_key_len : Size of the black key
 * @key_enc       : Encrypted Key Type (AES-ECB or AES-CCM)
 * @trusted_key   : Trusted Key (use Job Descriptor Key Encryption Key (JDKEK)
 *                  or Trusted Descriptor Key Encryption Key (TDKEK) to
 *                  decrypt the key to be loaded into a Key Register).
 *
 * Return         : '0' on success, error code otherwise
 */
int cnstr_desc_random_black_key(u32 **desc, size_t key_len,
				dma_addr_t black_key, size_t black_key_len,
				u8 key_enc, u8 trusted_key)
{
	u32 *tdesc, tmpdesc[INITIAL_DESCSZ];
	u16 dsize;
	u32 bk_store;

	memset(tmpdesc, 0, sizeof(tmpdesc));

	init_job_desc(tmpdesc, 0);

	/* Prepare RNG */
	append_operation(tmpdesc, OP_ALG_ALGSEL_RNG | OP_TYPE_CLASS1_ALG);

	/* Generate RNG and left it in output data fifo */
	append_cmd(tmpdesc, CMD_FIFO_STORE | FIFOST_TYPE_RNGFIFO | key_len);

	/* Copy RNG from outfifo to class 1 Key register */
	append_move(tmpdesc, MOVE_SRC_OUTFIFO | MOVE_DEST_CLASS1KEY |
			MOVE_WAITCOMP | (key_len & MOVE_LEN_MASK));

	/* Write the size of the key moved */
	append_load_imm_u32(tmpdesc, key_len, LDST_CLASS_1_CCB |
			    LDST_SRCDST_WORD_KEYSZ_REG | LDST_IMM);

	bk_store = CLASS_1;
	if (key_enc == KEY_COVER_ECB)
		bk_store |= FIFOST_TYPE_KEY_KEK;
	else
		bk_store |= FIFOST_TYPE_KEY_CCM_JKEK;

	/* Fifo store to save the key as black key in memory */
	append_fifo_store(tmpdesc, black_key, black_key_len, bk_store);

	dsize = desc_bytes(&tmpdesc);

	/* Now allocate execution buffer and coat it with executable */
	tdesc = kmemdup(tmpdesc, dsize, GFP_KERNEL | GFP_DMA);
	if (!tdesc)
		return -ENOMEM;

	*desc = tdesc;

	print_hex_dump_debug("black key random desc@" __stringify(__LINE__) ":",
			     DUMP_PREFIX_ADDRESS, 16, 4, *desc,
			     desc_bytes(*desc), 1);

	return 0;
}
EXPORT_SYMBOL(cnstr_desc_random_black_key);

/*
 * Construct a blob encapsulation job descriptor
 *
 * This function dynamically constructs a blob encapsulation job descriptor
 * from the following arguments:
 *
 * @desc          : Pointer to a pointer to the descriptor generated by this
 *                  function. Caller will be responsible to kfree() this
 *                  descriptor after execution.
 * @black_key     : Physical pointer to a secret, normally a black or red key,
 *                  possibly residing within an accessible secure memory page,
 *                  of the secret to be encapsulated to an output blob.
 * @black_key_len : Size of input secret, in bytes. This is limited to 65536
 *                  less the size of blob overhead, since the length embeds
 *                  into DECO pointer in/out instructions.
 * @keycolor      : Determines if the source data is covered (black key) or
 *                  plaintext (red key). RED_KEY or BLACK_KEY are defined in
 *                  for this purpose.
 * @key_enc       : If BLACK_KEY source is covered via AES-CCM, specify
 *                  KEY_COVER_CCM, else uses AES-ECB (KEY_COVER_ECB).
 * @trusted_key   : Trusted Key (use Job Descriptor Key Encryption Key (JDKEK)
 *                  or Trusted Descriptor Key Encryption Key (TDKEK) to
 *                  decrypt the key to be loaded into a Key Register).
 * @mem_type      : Determine if encapsulated blob should be a secure memory
 *                  blob (DATA_SECMEM), with partition data embedded with key
 *                  material, or a general memory blob (DATA_GENMEM).
 * @key_mod       : Pointer to a key modifier, which must reside in a
 *                  contiguous piece of memory. Modifier will be assumed to be
 *                  8 bytes long for a blob of type DATA_SECMEM, or 16 bytes
 *                  long for a blob of type DATA_GENMEM
 * @key_mod_len   : Modifier length is 8 bytes long for a blob of type
 *                  DATA_SECMEM, or 16 bytes long for a blob of type DATA_GENMEM
 * @blob          : Physical pointer to the destination buffer to receive the
 *                  encapsulated output. This buffer will need to be 48 bytes
 *                  larger than the input because of the added encapsulation
 *                  data. The generated descriptor will account for the
 *                  increase in size, but the caller must also account for
 *                  this increase in the buffer allocator.
 * @blob_len      : Size of the destination buffer to receive the
 *                  encapsulated output.
 * Return         : '0' on success, error code otherwise
 *
 * Upon completion, desc points to a buffer containing a CAAM job
 * descriptor which encapsulates data into an externally-storable blob
 * suitable for use across power cycles.
 *
 * This is an example of a black key encapsulation job into a general memory
 * blob. Notice the 16-byte key modifier in the LOAD instruction. Also note
 * the output 48 bytes longer than the input:
 *
 * [00] B0800008       jobhdr: stidx=0 len=8
 * [01] 14400010           ld: ccb2-key len=16 offs=0
 * [02] 08144891               ptr->@0x08144891
 * [03] F800003A    seqoutptr: len=58
 * [04] 01000000               out_ptr->@0x01000000
 * [05] F000000A     seqinptr: len=10
 * [06] 09745090               in_ptr->@0x09745090
 * [07] 870D0004    operation: encap blob  reg=memory, black, format=normal
 *
 * This is an example of a red key encapsulation job for storing a red key
 * into a secure memory blob. Note the 8 byte modifier on the 12 byte offset
 * in the LOAD instruction; this accounts for blob permission storage:
 *
 * [00] B0800008       jobhdr: stidx=0 len=8
 * [01] 14400C08           ld: ccb2-key len=8 offs=12
 * [02] 087D0784               ptr->@0x087d0784
 * [03] F8000050    seqoutptr: len=80
 * [04] 09251BB2               out_ptr->@0x09251bb2
 * [05] F0000020     seqinptr: len=32
 * [06] 40000F31               in_ptr->@0x40000f31
 * [07] 870D0008    operation: encap blob  reg=memory, red, sec_mem,
 *                             format=normal
 */
int cnstr_desc_blob_encap(u32 **desc, dma_addr_t black_key,
			  size_t key_len, u8 keycolor, u8 key_enc,
			  u8 trusted_key, u8 mem_type, const void *key_mod,
			  size_t key_mod_len, dma_addr_t blob, size_t blob_len)
{
	u32 *tdesc, tmpdesc[INITIAL_DESCSZ];
	u16 dsize;
	u32 bk_store;

	/* Trusted key not supported */
	if (trusted_key != UNTRUSTED_KEY)
		return -EOPNOTSUPP;

	memset(tmpdesc, 0, sizeof(tmpdesc));

	init_job_desc(tmpdesc, 0);

	/*
	 * Key modifier works differently for secure/general memory blobs
	 * This accounts for the permission/protection data encapsulated
	 * within the blob if a secure memory blob is requested
	 */
	if (mem_type == DATA_SECMEM)
		append_load_as_imm(tmpdesc, key_mod, key_mod_len,
				   LDST_CLASS_2_CCB | LDST_SRCDST_BYTE_KEY |
				   ((12 << LDST_OFFSET_SHIFT) &
				    LDST_OFFSET_MASK));
	else /* is general memory blob */
		append_load_as_imm(tmpdesc, key_mod, key_mod_len,
				   LDST_CLASS_2_CCB | LDST_SRCDST_BYTE_KEY);

	/* Input data, should be somewhere in secure memory */
	append_seq_in_ptr_intlen(tmpdesc, black_key, key_len, 0);

	/*
	 * Encapsulation output must include space for blob key encryption
	 * key and MAC tag
	 */
	append_seq_out_ptr_intlen(tmpdesc, blob, CCM_BLACK_KEY_SIZE(key_len) +
				  BLOB_OVERHEAD, 0);

	bk_store = OP_PCLID_BLOB;
	if (mem_type == DATA_SECMEM)
		bk_store |= OP_PCL_BLOB_PTXT_SECMEM;

	if (key_enc == KEY_COVER_CCM)
		bk_store |= OP_PCL_BLOB_EKT;

	/* An input black key cannot be stored in a red blob */
	if (keycolor == BLACK_KEY)
		bk_store |= OP_PCL_BLOB_BLACK;

	/* Set blob encap, then color */
	append_operation(tmpdesc, OP_TYPE_ENCAP_PROTOCOL | bk_store);

	dsize = desc_bytes(&tmpdesc);

	tdesc = kmemdup(tmpdesc, dsize, GFP_KERNEL | GFP_DMA);
	if (!tdesc)
		return -ENOMEM;

	*desc = tdesc;

	print_hex_dump_debug("blob encap desc@" __stringify(__LINE__) ":",
			     DUMP_PREFIX_ADDRESS, 16, 4, *desc,
			     desc_bytes(*desc), 1);
	return 0;
}
EXPORT_SYMBOL(cnstr_desc_blob_encap);

/*
 * Construct a blob decapsulation job descriptor
 *
 * This function dynamically constructs a blob decapsulation job descriptor
 * from the following arguments:
 *
 * @desc          : Pointer to a pointer to the descriptor generated by this
 *                  function. Caller will be responsible to kfree() this
 *                  descriptor after execution.
 * @blob          : Physical pointer (into external memory) of the blob to
 *                  be decapsulated. Blob must reside in a contiguous memory
 *                  segment.
 * @blob_len      : Size of the blob buffer to be decapsulated.
 * @key_mod       : Pointer to a key modifier, which must reside in a
 *                  contiguous piece of memory. Modifier will be assumed to be
 *                  8 bytes long for a blob of type DATA_SECMEM, or 16 bytes
 *                  long for a blob of type DATA_GENMEM
 * @key_mod_len   : Modifier length is 8 bytes long for a blob of type
 *                  DATA_SECMEM, or 16 bytes long for a blob of type DATA_GENMEM
 * @black_key     : Physical pointer of the decapsulated output, possibly into
 *                  a location within a secure memory page. Must be contiguous.
 * @black_key_len : Size of encapsulated secret in bytes (not the size of the
 *                  input blob).
 * @keycolor      : Determines if the source data is covered (black key) or
 *                  plaintext (red key). RED_KEY or BLACK_KEY are defined in
 *                  for this purpose.
 * @key_enc       : If BLACK_KEY source is covered via AES-CCM, specify
 *                  KEY_COVER_CCM, else uses AES-ECB (KEY_COVER_ECB).
 * @trusted_key   : Trusted Key (use Job Descriptor Key Encryption Key (JDKEK)
 *                  or Trusted Descriptor Key Encryption Key (TDKEK) to
 *                  decrypt the key to be loaded into a Key Register).
 * @mem_type      : Determine if encapsulated blob should be a secure memory
 *                  blob (DATA_SECMEM), with partition data embedded with key
 *                  material, or a general memory blob (DATA_GENMEM).
 * Return         : '0' on success, error code otherwise
 *
 * Upon completion, desc points to a buffer containing a CAAM job descriptor
 * that decapsulates a key blob from external memory into a black (encrypted)
 * key or red (plaintext) content.
 *
 * This is an example of a black key decapsulation job from a general memory
 * blob. Notice the 16-byte key modifier in the LOAD instruction.
 *
 * [00] B0800008       jobhdr: stidx=0 len=8
 * [01] 14400010           ld: ccb2-key len=16 offs=0
 * [02] 08A63B7F               ptr->@0x08a63b7f
 * [03] F8000010    seqoutptr: len=16
 * [04] 01000000               out_ptr->@0x01000000
 * [05] F000003A     seqinptr: len=58
 * [06] 01000010               in_ptr->@0x01000010
 * [07] 860D0004    operation: decap blob  reg=memory, black, format=normal
 *
 * This is an example of a red key decapsulation job for restoring a red key
 * from a secure memory blob. Note the 8 byte modifier on the 12 byte offset
 * in the LOAD instruction:
 *
 * [00] B0800008       jobhdr: stidx=0 len=8
 * [01] 14400C08           ld: ccb2-key len=8 offs=12
 * [02] 01000000               ptr->@0x01000000
 * [03] F8000020    seqoutptr: len=32
 * [04] 400000E6               out_ptr->@0x400000e6
 * [05] F0000050     seqinptr: len=80
 * [06] 08F0C0EA               in_ptr->@0x08f0c0ea
 * [07] 860D0008    operation: decap blob  reg=memory, red, sec_mem,
 *			       format=normal
 */
int cnstr_desc_blob_decap(u32 **desc, dma_addr_t blob, size_t blob_len,
			  const void *key_mod, size_t key_mod_len,
			  dma_addr_t black_key, size_t plaintext_len,
			  u8 keycolor, u8 key_enc, u8 trusted_key, u8 mem_type)
{
	u32 *tdesc, tmpdesc[INITIAL_DESCSZ];
	u16 dsize;
	u32 bk_store;

	/* Trusted key not supported */
	if (trusted_key != UNTRUSTED_KEY)
		return -EOPNOTSUPP;

	memset(tmpdesc, 0, sizeof(tmpdesc));

	init_job_desc(tmpdesc, 0);

	/* Load key modifier */
	if (mem_type == DATA_SECMEM)
		append_load_as_imm(tmpdesc, key_mod, key_mod_len,
				   LDST_CLASS_2_CCB | LDST_SRCDST_BYTE_KEY |
				   ((12 << LDST_OFFSET_SHIFT) &
				    LDST_OFFSET_MASK));
	else /* is general memory blob */
		append_load_as_imm(tmpdesc, key_mod, key_mod_len,
				   LDST_CLASS_2_CCB | LDST_SRCDST_BYTE_KEY);

	/* Compensate blob header + MAC tag over size of encapsulated secret */
	append_seq_in_ptr_intlen(tmpdesc, blob, plaintext_len + BLOB_OVERHEAD,
				 0);

	append_seq_out_ptr_intlen(tmpdesc, black_key, plaintext_len, 0);

	/* Decapsulate from secure memory partition to black blob */
	bk_store = OP_PCLID_BLOB;
	if (mem_type == DATA_SECMEM)
		bk_store |= OP_PCL_BLOB_PTXT_SECMEM;

	if (key_enc == KEY_COVER_CCM)
		bk_store |= OP_PCL_BLOB_EKT;

	/* An input black key cannot be stored in a red blob */
	if (keycolor == BLACK_KEY)
		bk_store |= OP_PCL_BLOB_BLACK;

	/* Set blob encap, then color */
	append_operation(tmpdesc, OP_TYPE_DECAP_PROTOCOL | bk_store);

	dsize = desc_bytes(&tmpdesc);

	tdesc = kmemdup(tmpdesc, dsize, GFP_KERNEL | GFP_DMA);
	if (!tdesc)
		return -ENOMEM;

	*desc = tdesc;

	print_hex_dump_debug("blob decap desc@" __stringify(__LINE__) ":",
			     DUMP_PREFIX_ADDRESS, 16, 4, *desc,
			     desc_bytes(*desc), 1);

	return 0;
}
EXPORT_SYMBOL(cnstr_desc_blob_decap);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("NXP CAAM Black Key and Blob descriptors");
MODULE_AUTHOR("NXP Semiconductors");