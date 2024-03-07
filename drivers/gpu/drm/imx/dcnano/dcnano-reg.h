/* SPDX-License-Identifier: GPL-2.0+ */

/*
 * Copyright 2020,2021 NXP
 */

#ifndef _DCNANO_REG_H_
#define _DCNANO_REG_H_

#include <linux/bitfield.h>
#include <linux/io.h>
#include <linux/sizes.h>

#define DCNANO_FRAMEBUFFERCONFIG	0x1240
/* double buffered */
#define  FBCFG_FORMAT_MASK		GENMASK(2, 0)
#define  FBCFG_FORMAT_NONE		FIELD_PREP(FBCFG_FORMAT_MASK, 0)
#define  FBCFG_FORMAT_R4G4B4		FIELD_PREP(FBCFG_FORMAT_MASK, 1)
#define  FBCFG_FORMAT_R5G5B5		FIELD_PREP(FBCFG_FORMAT_MASK, 2)
#define  FBCFG_FORMAT_R5G6B5		FIELD_PREP(FBCFG_FORMAT_MASK, 3)
#define  FBCFG_FORMAT_R8G8B8		FIELD_PREP(FBCFG_FORMAT_MASK, 4)
/* double buffered */
#define  FBCFG_MODE_LINEAR		0
#define  FBCFG_MODE_TILE4X4		BIT(4)
/* double buffered */
#define  FBCFG_OUTPUT_MASK		BIT(8)
#define  FBCFG_OUTPUT_DISABLE		0
#define  FBCFG_OUTPUT_ENABLE		BIT(8)
/* double buffered */
#define  FBCFG_SWITCHPANEL_DISABLE	0
#define  FBCFG_SWITCHPANEL_ENABLE	BIT(9)
/* double buffered */
#define  FBCFG_GAMMA_DISABLE		0
#define  FBCFG_GAMMA_ENABLE		BIT(12)
#define  FBCFG_VALID_WORKING		0
#define  FBCFG_VALID_PENDING		BIT(16)
#define  FBCFG_RESET_MASK		BIT(20)
#define  FBCFG_RESET_DISABLE		0
#define  FBCFG_RESET_ENABLE		BIT(20)
#define  FBCFG_UNDERFLOW_NO		0
#define  FBCFG_UNDERFLOW_YES		BIT(24)
#define  FBCFG_FLIP_INPROGRSS_NO	0
#define  FBCFG_FLIP_INPROGRSS_YES	BIT(28)
#define  FBCFG_BACK_PRES_DISABLE_NO	0
#define  FBCFG_BACK_PRES_DISABLE_YES	BIT(29)

/* double buffered */
#define DCNANO_FRAMEBUFFERADDRESS	0x1260
#define  FBADDRESS_MASK			GENMASK(31, 0)
#define  FBADDRESS(x)			FIELD_PREP(FBADDRESS_MASK, (x))
#define  FBADDRESS_TYPE_SYSTEM		0
#define  FBADDRESS_TYPE_VIRTUAL		BIT(31)

/* double buffered */
#define DCNANO_FRAMEBUFFERSTRIDE	0x1280
#define  FBSTRIDE_MASK			GENMASK(16, 0)
#define  FBSTRIDE(x)			FIELD_PREP(FBSTRIDE_MASK, (x))
#define  FBSTRIDE_MAX			FIELD_MAX(FBSTRIDE_MASK)

#define DCNANO_DISPLAYDITHERCONFIG	0x1360
#define  DITHERCFG_BLUESIZE_MASK	GENMASK(3, 0)
#define  DITHERCFG_BLUESIZE(x)		FIELD_PREP(DITHERCFG_BLUESIZE_MASK, (x))
#define  DITHERCFG_GREENSIZE_MASK	GENMASK(11, 8)
#define  DITHERCFG_GREENSIZE(x)		FIELD_PREP(DITHERCFG_GREENSIZE_MASK, (x))
#define  DITHERCFG_REDSIZE_MASK		GENMASK(19, 16)
#define  DITHERCFG_REDSIZE(x)		FIELD_PREP(DITHERCFG_REDSIZE_MASK, (x))
#define  DITHERCFG_DISABLE		0
/* double buffered */
#define  DITHERCFG_ENABLE		BIT(31)

#define DCNANO_DISPLAYDITHERTABLELOW	0x1380
#define  DITHERTLB_LOW_Y0X0_MASK	GENMASK(3, 0)
#define  DITHERTLB_LOW_Y0X0(x)		FIELD_PREP(DITHERTLB_LOW_Y0X0_MASK, (x))
#define  DITHERTLB_LOW_Y0X1_MASK	GENMASK(7, 4)
#define  DITHERTLB_LOW_Y0X1(x)		FIELD_PREP(DITHERTLB_LOW_Y0X1_MASK, (x))
#define  DITHERTLB_LOW_Y0X2_MASK	GENMASK(11, 8)
#define  DITHERTLB_LOW_Y0X2(x)		FIELD_PREP(DITHERTLB_LOW_Y0X2_MASK, (x))
#define  DITHERTLB_LOW_Y0X3_MASK	GENMASK(15, 12)
#define  DITHERTLB_LOW_Y0X3(x)		FIELD_PREP(DITHERTLB_LOW_Y0X3_MASK, (x))
#define  DITHERTLB_LOW_Y1X0_MASK	GENMASK(19, 16)
#define  DITHERTLB_LOW_Y1X0(x)		FIELD_PREP(DITHERTLB_LOW_Y1X0_MASK, (x))
#define  DITHERTLB_LOW_Y1X1_MASK	GENMASK(23, 20)
#define  DITHERTLB_LOW_Y1X1(x)		FIELD_PREP(DITHERTLB_LOW_Y1X1_MASK, (x))
#define  DITHERTLB_LOW_Y1X2_MASK	GENMASK(27, 24)
#define  DITHERTLB_LOW_Y1X2(x)		FIELD_PREP(DITHERTLB_LOW_Y1X2_MASK, (x))
#define  DITHERTLB_LOW_Y1X3_MASK	GENMASK(31, 28)
#define  DITHERTLB_LOW_Y1X3(x)		FIELD_PREP(DITHERTLB_LOW_Y1X3_MASK, (x))

#define DCNANO_DISPLAYDITHERTABLEHIGH	0x13a0
#define  DITHERTLB_HIGH_Y2X0_MASK	GENMASK(3, 0)
#define  DITHERTLB_HIGH_Y2X0(x)		FIELD_PREP(DITHERTLB_HIGH_Y2X0_MASK, (x))
#define  DITHERTLB_HIGH_Y2X1_MASK	GENMASK(7, 4)
#define  DITHERTLB_HIGH_Y2X1(x)		FIELD_PREP(DITHERTLB_HIGH_Y2X1_MASK, (x))
#define  DITHERTLB_HIGH_Y2X2_MASK	GENMASK(11, 8)
#define  DITHERTLB_HIGH_Y2X2(x)		FIELD_PREP(DITHERTLB_HIGH_Y2X2_MASK, (x))
#define  DITHERTLB_HIGH_Y2X3_MASK	GENMASK(15, 12)
#define  DITHERTLB_HIGH_Y2X3(x)		FIELD_PREP(DITHERTLB_HIGH_Y2X3_MASK, (x))
#define  DITHERTLB_HIGH_Y3X0_MASK	GENMASK(19, 16)
#define  DITHERTLB_HIGH_Y3X0(x)		FIELD_PREP(DITHERTLB_HIGH_Y3X0_MASK, (x))
#define  DITHERTLB_HIGH_Y3X1_MASK	GENMASK(23, 20)
#define  DITHERTLB_HIGH_Y3X1(x)		FIELD_PREP(DITHERTLB_HIGH_Y3X1_MASK, (x))
#define  DITHERTLB_HIGH_Y3X2_MASK	GENMASK(27, 24)
#define  DITHERTLB_HIGH_Y3X2(x)		FIELD_PREP(DITHERTLB_HIGH_Y3X2_MASK, (x))
#define  DITHERTLB_HIGH_Y3X3_MASK	GENMASK(31, 28)
#define  DITHERTLB_HIGH_Y3X3(x)		FIELD_PREP(DITHERTLB_HIGH_Y3X3_MASK, (x))

#define DCNANO_PANELCONFIG		0x13c0
#define  PANELCFG_DE_DISABLE		0
#define  PANELCFG_DE_ENABLE		BIT(0)
#define  PANELCFG_DE_POL_POSITIVE	0
#define  PANELCFG_DE_POL_NEGATIVE	BIT(1)
/* double buffered? */
#define  PANELCFG_DATA_DISABLE		0
#define  PANELCFG_DATA_ENABLE		BIT(4)
#define  PANELCFG_DATA_POL_POSITIVE	0
#define  PANELCFG_DATA_POL_NEGATIVE	BIT(5)
#define  PANELCFG_CLOCK_DISABLE		0
#define  PANELCFG_CLOCK_ENABLE		BIT(8)
#define  PANELCFG_CLOCK_POL_POSITIVE	0
#define  PANELCFG_CLOCK_POL_NEGATIVE	BIT(9)
#define  PANELCFG_SEQUENCING_HARDWARE	0
#define  PANELCFG_SEQUENCING_SOFTWARE	BIT(31)

#define DCNANO_PANELTIMING		0x13e0
#define  PANELTIMING_POWER_ENABLE_MASK		GENMASK(3, 0)
#define  PANELTIMING_POWER_ENABLE(x)		\
			FIELD_PREP(PANELTIMING_POWER_ENABLE_MASK, (x))
#define  PANELTIMING_BACKLIGHT_ENABLE_MASK	GENMASK(7, 4)
#define  PANELTIMING_BACKLIGHT_ENABLE(x)	\
			FIELD_PREP(PANELTIMING_BACKLIGHT_ENABLE_MASK, (x))
#define  PANELTIMING_CLOCK_ENABLE_MASK		GENMASK(11, 8)
#define  PANELTIMING_CLOCK_ENABLE(x)		\
			FIELD_PREP(PANELTIMING_CLOCK_ENABLE_MASK, (x))
#define  PANELTIMING_DATA_ENABLE_MASK		GENMASK(15, 12)
#define  PANELTIMING_DATA_ENABLE(x)		\
			FIELD_PREP(PANELTIMING_DATA_ENABLE_MASK, (x))
#define  PANELTIMING_DATA_DISABLE_MASK		GENMASK(19, 16)
#define  PANELTIMING_DATA_DISABLE(x)		\
			FIELD_PREP(PANELTIMING_DATA_DISABLE_MASK, (x))
#define  PANELTIMING_CLOCK_DISABLE_MASK		GENMASK(23, 20)
#define  PANELTIMING_CLOCK_DISABLE(x)		\
			FIELD_PREP(PANELTIMING_CLOCK_DISABLE_MASK, (x))
#define  PANELTIMING_BACKLIGHT_DISABLE_MASK	GENMASK(27, 24)
#define  PANELTIMING_BACKLIGHT_DISABLE(x)	\
			FIELD_PREP(PANELTIMING_BACKLIGHT_DISABLE_MASK, (x))
#define  PANELTIMING_POWER_DISABLE_MASK		GENMASK(31, 28)
#define  PANELTIMING_POWER_DISABLE(x)		\
			FIELD_PREP(PANELTIMING_POWER_DISABLE_MASK, (x))

#define DCNANO_HDISPLAY			0x1400
#define  HDISPLAY_END_MASK		GENMASK(12, 0)
#define  HDISPLAY_END(x)		FIELD_PREP(HDISPLAY_END_MASK, (x))
#define  HDISPLAY_TOTAL_MASK		GENMASK(28, 16)
#define  HDISPLAY_TOTAL(x)		FIELD_PREP(HDISPLAY_TOTAL_MASK, (x))

#define DCNANO_HSYNC			0x1420
#define  HSYNC_START_MASK		GENMASK(12, 0)
#define  HSYNC_START(x)			FIELD_PREP(HSYNC_START_MASK, (x))
#define  HSYNC_END_MASK			GENMASK(28, 16)
#define  HSYNC_END(x)			FIELD_PREP(HSYNC_END_MASK, (x))
/* double buffered? */
#define  HSYNC_PULSE_DISABLE		0
#define  HSYNC_PULSE_ENABLE		BIT(30)
#define  HSYNC_POL_MASK			BIT(31)
#define  HSYNC_POL_POSITIVE		0
#define  HSYNC_POL_NEGATIVE		BIT(31)

#define DCNANO_VDISPLAY			0x1480
#define  VDISPLAY_END_MASK		GENMASK(11, 0)
#define  VDISPLAY_END(x)		FIELD_PREP(VDISPLAY_END_MASK, (x))
#define  VDISPLAY_TOTAL_MASK		GENMASK(27, 16)
#define  VDISPLAY_TOTAL(x)		FIELD_PREP(VDISPLAY_TOTAL_MASK, (x))

#define DCNANO_VSYNC			0x14a0
#define  VSYNC_START_MASK		GENMASK(11, 0)
#define  VSYNC_START(x)			FIELD_PREP(VSYNC_START_MASK, (x))
#define  VSYNC_END_MASK			GENMASK(27, 16)
#define  VSYNC_END(x)			FIELD_PREP(VSYNC_END_MASK, (x))
/* double buffered? */
#define  VSYNC_PULSE_DISABLE		0
#define  VSYNC_PULSE_ENABLE		BIT(30)
#define  VSYNC_POL_MASK			BIT(31)
#define  VSYNC_POL_POSITIVE		0
#define  VSYNC_POL_NEGATIVE		BIT(31)

#define DCNANO_DISPLAYCURRENTLOCATION	0x14c0
#define  CURRENTLOCATION_X_MASK		GENMASK(15, 0)
#define  CURRENTLOCATION_X(x)		FIELD_PREP(CURRENTLOCATION_X_MASK, (x))
#define  CURRENTLOCATION_X_GET(x)	FIELD_GET(CURRENTLOCATION_X_MASK, (x))
#define  CURRENTLOCATION_Y_MASK		GENMASK(31, 16)
#define  CURRENTLOCATION_Y(x)		FIELD_PREP(CURRENTLOCATION_Y_MASK, (x))
#define  CURRENTLOCATION_Y_GET(x)	FIELD_GET(CURRENTLOCATION_Y_MASK, (x))

#define DCNANO_GAMMAINDEX		0x14e0
#define  GAMMAINDEX_MASK		GENMASK(7, 0)
#define  GAMMAINDEX(x)			FIELD_PREP(GAMMAINDEX_MASK, (x))

#define DCNANO_GAMMADATA		0x1500
#define  GAMMADATA_BLUE_MASK		GENMASK(7, 0)
#define  GAMMADATA_BLUE(x)		FIELD_PREP(GAMMADATA_BLUE_MASK, (x))
#define  GAMMADATA_GREEN_MASK		GENMASK(15, 8)
#define  GAMMADATA_GREEN(x)		FIELD_PREP(GAMMADATA_GREEN_MASK, (x))
#define  GAMMADATA_RED_MASK		GENMASK(23, 16)
#define  GAMMADATA_RED(x)		FIELD_PREP(GAMMADATA_RED_MASK, (x))

#define DCNANO_CURSORCONFIG		0x1520
/* double buffered */
#define  CURSORCFG_FORMAT_MASK		GENMASK(1, 0)
#define  CURSORCFG_FORMAT_NONE		FIELD_PREP(CURSORCFG_FORMAT_MASK, 0)
#define  CURSORCFG_FORMAT_MASKED	FIELD_PREP(CURSORCFG_FORMAT_MASK, 1)
#define  CURSORCFG_FORMAT_A8R8G8B8	FIELD_PREP(CURSORCFG_FORMAT_MASK, 2)
#define  CURSORCFG_DISPLAY_MASK		BIT(4)
#define  CURSORCFG_DISPLAY0		0
#define  CURSORCFG_DISPLAY1		BIT(4)
/* double buffered */
#define  CURSORCFG_HOTSPOT_Y_MASK	GENMASK(12, 8)
#define  CURSORCFG_HOTSPOT_Y(x)		FIELD_PREP(CURSORCFG_HOTSPOT_Y_MASK, 0)
/* double buffered */
#define  CURSORCFG_HOTSPOT_X_MASK	GENMASK(20, 16)
#define  CURSORCFG_HOTSPOT_X(x)		FIELD_PREP(CURSORCFG_HOTSPOT_X_MASK, 0)
#define  CURSORCFG_FLIP_INPROGRSS_NO	0
#define  CURSORCFG_FLIP_INPROGRSS_YES	BIT(31)

/* double buffered */
#define DCNANO_CURSORADDRESS		0x1530
#define  CURSORADDRESS_MASK		GENMASK(31, 0)
#define  CURSORADDRESS(x)		FIELD_PREP(CURSORADDRESS_MASK, (x))
#define  CURSORADDRESS_TYPE_SYSTEM	0
#define  CURSORADDRESS_TYPE_VIRTUAL	BIT(31)

/* double buffered */
#define DCNANO_CURSORLOCATION		0x1540
#define  CURSORLOCATION_X_MASK		GENMASK(12, 0)
#define  CURSORLOCATION_X(x)		FIELD_PREP(CURSORLOCATION_X_MASK, (x))
#define  CURSORLOCATION_X_MAX		FIELD_MAX(CURSORLOCATION_X_MASK)
#define  CURSORLOCATION_Y_MASK		GENMASK(27, 16)
#define  CURSORLOCATION_Y(x)		FIELD_PREP(CURSORLOCATION_Y_MASK, (x))
#define  CURSORLOCATION_Y_MAX		FIELD_MAX(CURSORLOCATION_Y_MASK)

/* double buffered */
#define DCNANO_CURSORBACKGROUND		0x1550
/* double buffered */
#define DCNANO_CURSORFOREGROUND		0x1560
#define  CURSOR_BLUE_MASK		GENMASK(7, 0)
#define  CURSOR_BLUE(x)			FIELD_PREP(CURSOR_BLUE_MASK, (x))
#define  CURSOR_GREEN_MASK		GENMASK(15, 8)
#define  CURSOR_GREEN(x)		FIELD_PREP(CURSOR_GREEN_MASK, (x))
#define  CURSOR_RED_MASK		GENMASK(23, 16)
#define  CURSOR_RED(x)			FIELD_PREP(CURSOR_RED_MASK, (x))

#define DCNANO_DISPLAYINTR		0x1600
#define DCNANO_DISPLAYINTRENABLE	0x1610
#define  DISPLAYINTR_DISP0		BIT(0)

#define DCNANO_DBICONFIG		0x1620
#define  DBICFG_DBI_TYPE_MASK		GENMASK(1, 0)
#define  DBICFG_DBI_TYPE_A_FIXED_E	FIELD_PREP(DBICFG_DBI_TYPE_MASK, 0)
#define  DBICFG_DBI_TYPE_A_CLOCK_E	FIELD_PREP(DBICFG_DBI_TYPE_MASK, 1)
#define  DBICFG_DBI_TYPE_B		FIELD_PREP(DBICFG_DBI_TYPE_MASK, 2)
#define  DBICFG_DBI_TYPE_C		FIELD_PREP(DBICFG_DBI_TYPE_MASK, 3)
#define  DBICFG_DATA_FORMAT_MASK	GENMASK(5, 2)

/* 8bit  data bus - D[7 : 0] */
/* 8bpp */
#define  DBICFG_DATA_FORMAT_D8R3G3B2	 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 0)
/* 12bpp */
#define  DBICFG_DATA_FORMAT_D8R4G4B4	 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 1)
/* 16bpp */
#define  DBICFG_DATA_FORMAT_D8R5G6B5	 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 2)
/* 18bpp */
#define  DBICFG_DATA_FORMAT_D8R6G6B6	 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 3)
/* 24bpp */
#define  DBICFG_DATA_FORMAT_D8R8G8B8	 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 4)

/* 9bit  data bus - D[8 : 0] */
/* 18bpp */
#define  DBICFG_DATA_FORMAT_D9R6G6B6	 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 5)

/* 16bit data bus - D[15 : 0] */
/* 8bpp */
#define  DBICFG_DATA_FORMAT_D16R3G3B2	 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 6)
/* 12bpp */
#define  DBICFG_DATA_FORMAT_D16R4G4B4	 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 7)
/* 16bpp */
#define  DBICFG_DATA_FORMAT_D16R5G6B5	 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 8)
/* 18bpp */
#define  DBICFG_DATA_FORMAT_D16R6G6B6OP1 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 9)
#define  DBICFG_DATA_FORMAT_D16R6G6B6OP2 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 10)
/* 24bpp */
#define  DBICFG_DATA_FORMAT_D16R8G8B8OP1 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 11)
#define  DBICFG_DATA_FORMAT_D16R8G8B8OP2 FIELD_PREP(DBICFG_DATA_FORMAT_MASK, 12)

#define  DBICFG_BUS_OUTPUT_SEL_DPI	0
#define  DBICFG_BUS_OUTPUT_SEL_DBI	BIT(6)
#define  DBICFG_DBIX_POLARITY_DEFAULT	0
#define  DBICFG_DBIX_POLARITY_REVERSE	BIT(7)
#define  DBICFG_DBI_AC_TIME_UNIT_MASK	GENMASK(11, 8)
#define  DBICFG_DBI_AC_TIME_UNIT(x)	\
				FIELD_PREP(DBICFG_DBI_AC_TIME_UNIT_MASK, (x))
#define  DBICFG_DBI_TYPEC_OPT_MASK	GENMASK(13, 12)
#define  DBICFG_DBI_TYPEC_OPT1		FIELD_PREP(DBICFG_DBI_TYPEC_OPT_MASK, 0)
#define  DBICFG_DBI_TYPEC_OPT2		FIELD_PREP(DBICFG_DBI_TYPEC_OPT_MASK, 1)
#define  DBICFG_DBI_TYPEC_OPT3		FIELD_PREP(DBICFG_DBI_TYPEC_OPT_MASK, 2)

#define DCNANO_DBIIFRESET		0x1640
#define  DBIIF_LEVEL_NO_RESET		0
#define  DBIIF_LEVEL_RESET		BIT(0)

#define DCNANO_DBIWRCHAR1		0x1660
#define  DBIWR_PERIOD_MASK		GENMASK(7, 0)
#define  DBIWR_PERIOD(x)		FIELD_PREP(DBIWR_PERIOD_MASK, (x))
#define  DBIWR_EOR_WR_ASSERT_MASK	GENMASK(11, 8)
#define  DBIWR_EOR_WR_ASSERT(x)		FIELD_PREP(DBIWR_EOR_WR_ASSERT_MASK, (x))
#define  DBIWR_CS_ASSERT_MASK		GENMASK(15, 12)
#define  DBIWR_CS_ASSERT(x)		FIELD_PREP(DBIWR_CS_ASSERT_MASK, (x))

#define DCNANO_DBIWRCHAR2		0x1680
#define  DBIWR_EOR_WR_DE_ASRT_MASK	GENMASK(7, 0)
#define  DBIWR_EOR_WR_DE_ASRT(x)	\
				FIELD_PREP(DBIWR_EOR_WR_DE_ASRT_MASK, (x))
#define  DBIWR_CS_DE_ASRT_MASK		GENMASK(15, 8)
#define  DBIWR_CS_DE_ASRT(x)		FIELD_PREP(DBIWR_CS_DE_ASRT_MASK, (x))

#define DCNANO_DBICMD			0x16a0
#define  DBICMD_WORD_MASK		GENMASK(15, 0)
#define  DBICMD_WORD(x)			FIELD_PREP(DBICMD_WORD_MASK, (x))
#define  DBICMD_FLAG_MASK		GENMASK(31, 30)
#define  DBICMD_FLAG_ADDRESS		FIELD_PREP(DBICMD_FLAG_MASK, 0)
#define  DBICMD_FLAG_WRITE_MEM_START	FIELD_PREP(DBICMD_FLAG_MASK, 1)
#define  DBICMD_FLAG_PARAMETER_OR_DATA	FIELD_PREP(DBICMD_FLAG_MASK, 2)
/* Read is unused. */
#define  DBICMD_FLAG_READ		FIELD_PREP(DBICMD_FLAG_MASK, 3)

#define DCNANO_DPICONFIG		0x16c0
#define  DPICFG_DATA_FORMAT_MASK	GENMASK(2, 0)
#define  DPICFG_DATA_FORMAT_D16CFG1	FIELD_PREP(DPICFG_DATA_FORMAT_MASK, 0)
#define  DPICFG_DATA_FORMAT_D16CFG2	FIELD_PREP(DPICFG_DATA_FORMAT_MASK, 1)
#define  DPICFG_DATA_FORMAT_D16CFG3	FIELD_PREP(DPICFG_DATA_FORMAT_MASK, 2)
#define  DPICFG_DATA_FORMAT_D18CFG1	FIELD_PREP(DPICFG_DATA_FORMAT_MASK, 3)
#define  DPICFG_DATA_FORMAT_D18CFG2	FIELD_PREP(DPICFG_DATA_FORMAT_MASK, 4)
#define  DPICFG_DATA_FORMAT_D24		FIELD_PREP(DPICFG_DATA_FORMAT_MASK, 5)

#define DCNANO_DCCHIPREV		0x16f0
#define  DCCHIPREV_MASK			GENMASK(31, 0)
#define  DCCHIPREV			0x00005543

#define DCNANO_DCCHIPDATE		0x1700
#define  DCCHIPDATE_MASK		GENMASK(31, 0)
#define  DCCHIPDATE			0x20180612

#define DCNANO_DCCHIPPATCHREV		0x1720
#define  DCCHIPPATCHREV_MASK		GENMASK(31, 0)
#define  DCCHIPPATCHREV			0x00000003

#define DCNANO_DCTILEINCFG		0x1740
/* double buffered */
#define  DCTILEINCFG_TILE_FORMAT_MASK	GENMASK(1, 0)
#define  DCTILEINCFG_TILE_FORMAT_NONE		\
				FIELD_PREP(DCTILEINCFG_TILE_FORMAT_MASK, 0)
#define  DCTILEINCFG_TILE_FORMAT_ARGB8888	\
				FIELD_PREP(DCTILEINCFG_TILE_FORMAT_MASK, 1)
#define  DCTILEINCFG_TILE_FORMAT_YUY2		\
				FIELD_PREP(DCTILEINCFG_TILE_FORMAT_MASK, 2)
#define  DCTILEINCFG_TILE_FORMAT_NV12		\
				FIELD_PREP(DCTILEINCFG_TILE_FORMAT_MASK, 3)
#define  DCTILEINCFG_YUV_STANDARD_MASK	GENMASK(3, 2)
/* double buffered */
#define  DCTILEINCFG_YUV_BT601			\
				FIELD_PREP(DCTILEINCFG_YUV_STANDARD_MASK, 0)
#define  DCTILEINCFG_YUV_BT709			\
				FIELD_PREP(DCTILEINCFG_YUV_STANDARD_MASK, 1)
/* double buffered */
#define  DCTILEINCFG_YUV2_RGB_EN_MASK	BIT(4)
#define  DCTILEINCFG_YUV2_RGB_ENABLE	BIT(4)
#define  DCTILEINCFG_YUV2_RGB_DISABLE	0
#define  DCTILEINCFG_CFG_MODE_EN	BIT(5)
#define  DCTILEINCFG_CFG_MODE_ENABLE	BIT(5)
#define  DCTILEINCFG_CFG_MODE_DISABLE	0

/* double buffered */
#define DCNANO_DCTILEUVFRAMEBUFFERADR	0x1760
#define  DCTILEUVFB_ADDRESS_MASK	GENMASK(31, 0)
#define  DCTILEUVFB_ADDRESS(x)		FIELD_PREP(DCTILEUVFB_ADDRESS_MASK, (x))
#define  DCTILEUVFB_ADDRESS_MAX		FIELD_MAX(DCTILEUVFB_ADDRESS_MASK)

/* double buffered */
#define DCNANO_DCTILEUVFRAMEBUFFERSTR	0x1780
#define  DCTILEUVFB_STRIDE_MASK		GENMASK(15, 0)
#define  DCTILEUVFB_STRIDE(x)		FIELD_PREP(DCTILEUVFB_STRIDE_MASK, (x))
#define  DCTILEUVFB_STRIDE_MAX		FIELD_MAX(DCTILEUVFB_STRIDE_MASK)

#define DCNANO_DCPRODUCTID		0x17b0
#define  DCPRODUCTID_MASK		GENMASK(31, 0)
#define  DCPRODUCTID			0x02000361

#define DCNANO_DCSTATUS			0x1800
#define  DCSTATUS_DBI_TYPEC_FIFO_FULL	BIT(0)

#define DCNANO_DEBUGCOUNTERSELECT	0x1820
#define  DEBUGCOUNTERSELECT_MASK	GENMASK(7, 0)
#define  TOTAL_AXI_RD_REQ_CNT		FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 0)
#define  TOTAL_AXI_RD_LAST_CNT		FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 1)
#define  TOTAL_AXI_REQ_BURST_CNT	FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 2)
#define  TOTAL_AXI_RD_BURST_CNT		FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 3)
#define  TOTAL_PIXEL_CNT		FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 4)
#define  TOTAL_FRAME_CNT		FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 5)
#define  TOTAL_INPUT_DBI_CMD_CNT	FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 6)
#define  TOTAL_OUTPUT_DBI_CMD_CNT	FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 7)
#define  DEBUG_SIGNALS0			FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 8)
#define  RESET_ALL_CNTS			FIELD_PREP(DEBUGCOUNTERSELECT_MASK, 0xFF)

#define DCNANO_DEBUGCOUNTERVALUE	0x1840
#define  DEBUGCOUNTERVALUE_MASK		GENMASK(31, 0)
#define  DEBUGCOUNTERVALUE(x)		FIELD_PREP(DEBUGCOUNTERVALUE_MASK, (x))
#define  DEBUGCOUNTERVALUE_MAX		FIELD_MAX(DEBUGCOUNTERVALUE_MASK)

static inline u32 dcnano_read(struct dcnano_dev *dcnano, unsigned int reg)
{
	return readl(dcnano->mmio_base + reg);
}

static inline void dcnano_write(struct dcnano_dev *dcnano,
				unsigned int reg, u32 value)
{
	writel(value, dcnano->mmio_base + reg);
}

static inline void dcnano_write_mask(struct dcnano_dev *dcnano,
				     unsigned int reg, u32 mask, u32 value)
{
	u32 tmp;

	tmp = dcnano_read(dcnano, reg);
	tmp &= ~mask;
	dcnano_write(dcnano, reg, tmp | value);
}

#endif
