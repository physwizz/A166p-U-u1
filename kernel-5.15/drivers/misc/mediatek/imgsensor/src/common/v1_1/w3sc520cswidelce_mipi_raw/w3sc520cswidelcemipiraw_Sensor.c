/*
 * Copyright (C) 2018 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */

#include <linux/videodev2.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/atomic.h>
#include <linux/types.h>

#include "w3sc520cswidelcemipiraw_Sensor.h"

#define PFX "SC520CS_mipi_raw"
#define LOG_INF(format, args...)    \
	pr_info(PFX "[%s] " format, __func__, ##args)
//extern unsigned char fusion_id_front[96];
//extern unsigned char sn_front[96];
#define MULTI_WRITE 0
static DEFINE_SPINLOCK(imgsensor_drv_lock);
#define SC520CS_OTP_FUNCTION 1
#if SC520CS_OTP_FUNCTION
//+S96818AA1-1936,zhujianjia.wt,ADD,2023/04/28,c8496 otp porting
//static struct i2c_client *g_pstI2CclientG;
#define EEPROM_I2C_MSG_SIZE_READ 2
#define EEPROM_I2C_WRITE_MSG_LENGTH_MAX 32
#define SC520CS_ST_RET_FAIL 1
#define SC520CS_ST_RET_SUCCESS 0
#define SC520CS_ST_PAGE2 2
#define SC520CS_ST_DEBUG_ON 1
#define MODULE_INFO_FLAG 0x8866
#define MODULE_GROUP1_ADDR  0x8867
#define SN_INFO_FLAG 0x886F
#define SN_GROUP1_ADDR  0x8870
#define AWB_INFO_FLAG 0x886F
#define AWB_GROUP1_FLAG  0x887E
#define AWB_GROUP2_FLAG  0x888F
#define LSC_INFO_FLAG 0x88A0
#define LSC_GROUP1_FLAG 0x88A1
#define LSC_GROUP2_FLAG 0x8FEE
#define LSC_GROUP2_PAGE2_END 0x8FFF
#define LSC_GROUP2_PAGE1_START 0x80B6
#define LSC_GROUP2_PAGE1_END 0x87EF
#define LSC_GROUP1_CHECKSUM  0x8FED
#define LSC_GROUP2_CHECKSUM  0x87F0

static int otp_group_1 = 0x01;
static int otp_group_2 = 0x13;
#define MODULE_INFO_SIZE 7
#define SN_INFO_SIZE 12
#define AWB_INFO_SIZE 16
#define LSC_INFO_SIZE 1868
static unsigned char sc520cs_data_lsc[LSC_INFO_SIZE + 1] = {0};/*Add check sum*/
static unsigned char sc520cs_data_awb[AWB_INFO_SIZE + 1] = {0};/*Add check sum*/
static unsigned char sc520cs_data_info[MODULE_INFO_SIZE + 1] = {0};/*Add check sum*/
static unsigned char sc520cs_data_sn[SN_INFO_SIZE + 1] = {0};/*Add check sum*/
static int tempotpthreshold =  0;
#include "cam_cal_define.h"
#include <linux/slab.h>
static struct stCAM_CAL_DATAINFO_STRUCT w3sc520cswidelce_eeprom_data ={
    .sensorID= W3SC520CSWIDELCE_SENSOR_ID,
    .deviceID = 0x04,
    .dataLength = 0x0778,//1903
    .sensorVendorid = 0x02010100,
    .vendorByte = {1,2,3,4},
    .dataBuffer = NULL,
};

extern int imgSensorReadOTPData(struct stCAM_CAL_DATAINFO_STRUCT* pData);
#endif

static struct imgsensor_info_struct imgsensor_info = {
	.sensor_id = W3SC520CSWIDELCE_SENSOR_ID,
	.checksum_value = 0x55e2a82f,
	.pre = {
		.pclk = 90000000,
		.linelength = 1500,
		.framelength = 2000,
		.startx = 0,
		.starty = 0,
		.grabwindow_width = 2592,
		.grabwindow_height = 1944,
		.mipi_data_lp2hs_settle_dc = 14,
		.max_framerate = 300,
		.mipi_pixel_rate = 165600000,
	},
	.cap = {
		.pclk = 90000000,
		.linelength = 1500,
		.framelength = 2000,
		.startx = 0,
		.starty = 0,
		.grabwindow_width = 2592,
		.grabwindow_height = 1944,
		.mipi_data_lp2hs_settle_dc = 14,
		.max_framerate = 300,
		.mipi_pixel_rate = 165600000,
	},
	.normal_video = {
		.pclk = 90000000,
		.linelength = 1500,
		.framelength = 2000,
		.startx = 0,
		.starty = 0,
		.grabwindow_width = 2560,
		.grabwindow_height = 1440,
		.mipi_data_lp2hs_settle_dc = 14,
		.max_framerate = 300,
		.mipi_pixel_rate = 360000000,
	},
	.hs_video = {
		.pclk = 90000000,
		.linelength = 1500,
		.framelength = 2000,
		.startx = 0,
		.starty = 0,
		.grabwindow_width = 2592,
		.grabwindow_height = 1944,
		.mipi_data_lp2hs_settle_dc = 14,
		.max_framerate = 300,
		.mipi_pixel_rate = 165600000,
	},
	.slim_video = {
		.pclk = 90000000,
		.linelength = 1500,
		.framelength = 2000,
		.startx = 0,
		.starty = 0,
		.grabwindow_width = 2592,
		.grabwindow_height = 1944,
		.mipi_data_lp2hs_settle_dc = 14,
		.max_framerate = 300,
		.mipi_pixel_rate = 165600000
	},

	.custom1 = {
		.pclk = 90000000,
		.linelength = 1500,
		.framelength = 2500,
		.startx = 0,
		.starty = 0,
		.grabwindow_width = 2592,
		.grabwindow_height = 1944,
		.mipi_data_lp2hs_settle_dc = 14,
		.max_framerate = 240,
		.mipi_pixel_rate = 165600000,
	},
  	.exp_step = 2,
	.min_gain = BASEGAIN, // 1x gain
	.max_gain = 32 * BASEGAIN, // real again is 32x
	.min_gain_iso = 50,
	.gain_step = 1,
	.gain_type = 1,
	.margin = 6,            //sensor framelength & shutter margin
	.min_shutter = 6,
	.max_frame_length = 0x7FFF,
	.ae_shut_delay_frame = 0,
	.ae_sensor_gain_delay_frame = 0,
	.ae_ispGain_delay_frame = 2,
	.ihdr_support = 0,     // //1, support; 0,not support
	.ihdr_le_firstline = 0, // //1,le first ; 0, se first
	.sensor_mode_num = 6,	  //support sensor mode num

	.cap_delay_frame = 3,
	.pre_delay_frame = 3,
	.video_delay_frame = 3,
	.hs_video_delay_frame = 3,
	.slim_video_delay_frame = 3,
	.custom1_delay_frame = 3,
	.frame_time_delay_frame = 2,
	.isp_driving_current = ISP_DRIVING_4MA,
	.sensor_interface_type = SENSOR_INTERFACE_TYPE_MIPI,
	.mipi_sensor_type = MIPI_OPHY_NCSI2,
	.mipi_settle_delay_mode = MIPI_SETTLEDELAY_MANUAL,//0,MIPI_SETTLEDELAY_AUTO; 1,MIPI_SETTLEDELAY_MANUAL
	.sensor_output_dataformat = SENSOR_OUTPUT_FORMAT_RAW_B,
	.mclk = 24,
	.mipi_lane_num = SENSOR_MIPI_2_LANE,
	.i2c_addr_table = {0x6c, 0xff},
	.i2c_speed = 400,
};

static struct imgsensor_struct imgsensor = {
	.mirror = IMAGE_NORMAL,
	.sensor_mode = IMGSENSOR_MODE_INIT,
	.shutter = 0x3d0,                   //current shutter  
	.gain = 0x40,                      //current gain     
	.dummy_pixel = 0,
	.dummy_line = 0,
//full size current fps : 24fps for PIP, 30fps for Normal or ZSD
	.current_fps = 300,
	.autoflicker_en = KAL_FALSE,
	.test_pattern = KAL_FALSE,
	.current_scenario_id = MSDK_SCENARIO_ID_CAMERA_PREVIEW,
	.ihdr_en = 0,
	.i2c_write_id = 0x6c,
};

/* Sensor output window information */
static struct SENSOR_WINSIZE_INFO_STRUCT imgsensor_winsize_info[6] = {
 { 2592, 1944,	  0,	0, 2592, 1944, 2592, 1944, 0000, 0000, 2592, 1944,    0, 0, 2592, 1944}, // Preview
 { 2592, 1944,	  0,	0, 2592, 1944, 2592, 1944, 0000, 0000, 2592, 1944,    0, 0, 2592, 1944}, // capture
 { 2592, 1944,   16,  252, 2560, 1440, 2560, 1440, 0000, 0000, 2560, 1440,    0, 0, 2560, 1440}, // video
 { 2592, 1944,	  0,	0, 2592, 1944, 2592, 1944, 0000, 0000, 2592, 1944,    0, 0, 2592, 1944}, //hight speed video
 { 2592, 1944,	  0,	0, 2592, 1944, 2592, 1944, 0000, 0000, 2592, 1944,    0, 0, 2592, 1944},// slim video
 { 2592, 1944,    0,    0, 2592, 1944, 2592, 1944, 0000, 0000, 2592, 1944,    0, 0, 2592, 1944},// custom1
};
#if MULTI_WRITE
#define I2C_BUFFER_LEN 765

static kal_uint16 sc520cs_table_write_cmos_sensor(
					kal_uint16 *para, kal_uint32 len)
{
	char puSendCmd[I2C_BUFFER_LEN];
	kal_uint32 tosend, IDX;
	kal_uint16 addr = 0, addr_last = 0, data;

	tosend = 0;
	IDX = 0;
	while (len > IDX) {
		addr = para[IDX];

		{
			puSendCmd[tosend++] = (char)(addr >> 8);
			puSendCmd[tosend++] = (char)(addr & 0xFF);
			data = para[IDX + 1];
			//puSendCmd[tosend++] = (char)(data >> 8);
			puSendCmd[tosend++] = (char)(data & 0xFF);
			IDX += 2;
			addr_last = addr;
		}

		if ((I2C_BUFFER_LEN - tosend) < 4 ||
			len == IDX ||
			addr != addr_last) {
			iBurstWriteReg_multi(puSendCmd, tosend,
				imgsensor.i2c_write_id,
				3, imgsensor_info.i2c_speed);

			tosend = 0;
		}
	}
	return 0;
}
#endif

static kal_uint16 read_cmos_sensor(kal_uint32 addr)
{
	kal_uint16 get_byte = 0;
	char pu_send_cmd[2] = {(char)(addr >> 8), (char)(addr & 0xFF) };

	//iReadRegI2C(pu_send_cmd, 2, (u8 *)&get_byte, 1, imgsensor.i2c_write_id);
	iReadRegI2CTiming(pu_send_cmd, 2, (u8 *) &get_byte, 1,imgsensor.i2c_write_id, imgsensor_info.i2c_speed);

	return get_byte;
}

static void write_cmos_sensor(kal_uint32 addr, kal_uint32 para)
{
	char pu_send_cmd[4] = {(char)(addr >> 8),
		(char)(addr & 0xFF), (char)(para & 0xFF)};

	//iWriteRegI2C(pu_send_cmd, 3, imgsensor.i2c_write_id);
	iWriteRegI2CTiming(pu_send_cmd, 3, imgsensor.i2c_write_id, imgsensor_info.i2c_speed);
}

static void write_cmos_sensor8(kal_uint32 addr, kal_uint32 para)
{
	char pu_send_cmd[4] = {(char)(addr >> 8),
		(char)(addr & 0xFF), (char)(para & 0xFF)};

	//iWriteRegI2C(pu_send_cmd, 3, imgsensor.i2c_write_id);
	iWriteRegI2CTiming(pu_send_cmd, 3, imgsensor.i2c_write_id, imgsensor_info.i2c_speed);
}

static void set_dummy(void)
{
	LOG_INF("dummyline = %d, dummypixels = %d\n",
		imgsensor.dummy_line, imgsensor.dummy_pixel);
	write_cmos_sensor8(0x320e, imgsensor.frame_length >> 8);
	write_cmos_sensor8(0x320f, imgsensor.frame_length & 0xFF);
	write_cmos_sensor8(0x320c, imgsensor.line_length >> 8);
	write_cmos_sensor8(0x320d, imgsensor.line_length & 0xFF);


}	/*	set_dummy  */

static kal_uint32 return_sensor_id(void)
{
	return ((read_cmos_sensor(0x3107) << 8) | read_cmos_sensor(0x3108)); //0xee4b
}


static void set_max_framerate(UINT16 framerate, kal_bool min_framelength_en)
{
	kal_uint32 frame_length = imgsensor.frame_length;

	frame_length = imgsensor.pclk / framerate * 10 / imgsensor.line_length;
	LOG_INF("img.fl:%d, fl:%d, framerate %d line_length%d ",imgsensor.frame_length,frame_length,framerate,imgsensor.line_length );
	spin_lock(&imgsensor_drv_lock);
	imgsensor.frame_length = (frame_length > imgsensor.min_frame_length) ?
			frame_length : imgsensor.min_frame_length;
	imgsensor.dummy_line = imgsensor.frame_length -
		imgsensor.min_frame_length;

	if (imgsensor.frame_length > imgsensor_info.max_frame_length) {
		imgsensor.frame_length = imgsensor_info.max_frame_length;
		imgsensor.dummy_line = imgsensor.frame_length -
			imgsensor.min_frame_length;
	}
	if (min_framelength_en)
		imgsensor.min_frame_length = imgsensor.frame_length;

	spin_unlock(&imgsensor_drv_lock);
	set_dummy();
}	/*	set_max_framerate  */

static void write_shutter(kal_uint32 shutter)
{
	kal_uint16 realtime_fps = 0;

	spin_lock(&imgsensor_drv_lock);

	if (shutter > imgsensor.min_frame_length - imgsensor_info.margin)
		imgsensor.frame_length = shutter + imgsensor_info.margin;
	else
		imgsensor.frame_length = imgsensor.min_frame_length;
	if (imgsensor.frame_length > imgsensor_info.max_frame_length)
		imgsensor.frame_length = imgsensor_info.max_frame_length;
	spin_unlock(&imgsensor_drv_lock);

	shutter = (shutter < imgsensor_info.min_shutter) ?
		imgsensor_info.min_shutter : shutter;
	shutter = (shutter >
		(imgsensor_info.max_frame_length - imgsensor_info.margin)) ?
		(imgsensor_info.max_frame_length - imgsensor_info.margin) :
		shutter;
	if (imgsensor.autoflicker_en) {
		realtime_fps = imgsensor.pclk * 10 /
			(imgsensor.line_length * imgsensor.frame_length);
		if (realtime_fps >= 297 && realtime_fps <= 305)
			set_max_framerate(296, 0);
		else if (realtime_fps >= 147 && realtime_fps <= 150)
			set_max_framerate(146, 0);
		else{
		write_cmos_sensor8(0x320e, (imgsensor.frame_length >> 8) & 0xff);
		write_cmos_sensor8(0x320f, imgsensor.frame_length & 0xFF);
		}

	} else{
		// Extend frame length

		// ADD ODIN
		realtime_fps = imgsensor.pclk * 10 /
			(imgsensor.line_length * imgsensor.frame_length);
		if (realtime_fps > 300 && realtime_fps < 320)
			set_max_framerate(300, 0);
		// ADD END
		write_cmos_sensor8(0x320e, (imgsensor.frame_length >> 8) & 0xff);
		write_cmos_sensor8(0x320f, imgsensor.frame_length & 0xFF);
	}

	// Update Shutter
	shutter = shutter *2;
	//write_cmos_sensor8(0x3e20, (shutter >> 20) & 0x0F);
	write_cmos_sensor8(0x3e00, (shutter >> 12) & 0xFF);
	write_cmos_sensor8(0x3e01, (shutter >> 4)&0xFF);
	write_cmos_sensor8(0x3e02, (shutter<<4) & 0xF0);

	LOG_INF("shutter =%d, framelength =%d",
		shutter, imgsensor.frame_length);
}	/*	write_shutter  */

/*************************************************************************
 * FUNCTION
 *	set_shutter
 *
 * DESCRIPTION
 *	This function set e-shutter of sensor to change exposure time.
 *
 * PARAMETERS
 *	iShutter : exposured lines
 *
 * RETURNS
 *	None
 *
 * GLOBALS AFFECTED
 *
 *************************************************************************/
static void set_shutter(kal_uint32 shutter)
{
	unsigned long flags;

	LOG_INF("set_shutter");
	spin_lock_irqsave(&imgsensor_drv_lock, flags);
	imgsensor.shutter = shutter;
	spin_unlock_irqrestore(&imgsensor_drv_lock, flags);

	write_shutter(shutter);
}	/*	set_shutter */

static void set_shutter_frame_length(kal_uint16 shutter,kal_uint16 frame_length, kal_bool auto_extend_en)
{
	kal_uint16 realtime_fps = 0;
	kal_int32  dummy_line = 0;
	spin_lock(&imgsensor_drv_lock);


	if(frame_length > 1)
		dummy_line = frame_length - imgsensor.frame_length;
	imgsensor.frame_length = imgsensor.frame_length + dummy_line;

	if (shutter > imgsensor.frame_length - imgsensor_info.margin)
		imgsensor.frame_length = shutter + imgsensor_info.margin;

	if (imgsensor.frame_length > imgsensor_info.max_frame_length)
		imgsensor.frame_length = imgsensor_info.max_frame_length;

	shutter = (shutter < imgsensor_info.min_shutter) ?
		imgsensor_info.min_shutter : shutter;
	shutter = (shutter >
		(imgsensor_info.max_frame_length - imgsensor_info.margin)) ?
		(imgsensor_info.max_frame_length - imgsensor_info.margin) :
		shutter;

	realtime_fps = imgsensor.pclk * 10 /
			(imgsensor.line_length * imgsensor.frame_length);

	spin_unlock(&imgsensor_drv_lock);

	if (imgsensor.autoflicker_en) {
		if (realtime_fps >= 297 && realtime_fps <= 305)
			set_max_framerate(296, 0);
		else if (realtime_fps >= 147 && realtime_fps <= 150)
			set_max_framerate(146, 0);
		else{
		write_cmos_sensor8(0x320e, (imgsensor.frame_length >> 8) & 0xff);
		write_cmos_sensor8(0x320f, imgsensor.frame_length & 0xFF);
		}

	} else{
		// Extend frame length

		if (realtime_fps > 300 && realtime_fps < 320)
			set_max_framerate(300, 0);
		write_cmos_sensor8(0x320e, (imgsensor.frame_length >> 8) & 0xff);
		write_cmos_sensor8(0x320f, imgsensor.frame_length & 0xFF);
	}

	// Update Shutter
	shutter = shutter *2;
	//write_cmos_sensor8(0x3e20, (shutter >> 20) & 0x0F);
	write_cmos_sensor8(0x3e00, (shutter >> 12) & 0xFF);
	write_cmos_sensor8(0x3e01, (shutter >> 4)&0xFF);
	write_cmos_sensor8(0x3e02, (shutter<<4) & 0xF0);

	LOG_INF("shutter =%d, fl :%d  info.fl:%d fps:%d", shutter,frame_length, imgsensor.frame_length, realtime_fps);
}	/*	write_shutter  */



/* SENSOR PRIVATE INFO FOR GAIN SETTING */
#define SC520CS_SENSOR_GAIN_BASE             0x400
#define SC520CS_SENSOR_GAIN_MAX              (160 * SC520CS_SENSOR_GAIN_BASE / 10)
#define SC520CS_SENSOR_GAIN_MAP_SIZE  6

static kal_uint16 gain2reg(const kal_uint16 gain)
{
	kal_uint16 reg_gain = gain << 4;

	if (reg_gain < SC520CS_SENSOR_GAIN_BASE)
		reg_gain = SC520CS_SENSOR_GAIN_BASE;
	else if (reg_gain > SC520CS_SENSOR_GAIN_MAX)
		reg_gain = SC520CS_SENSOR_GAIN_MAX;

	return (kal_uint16)reg_gain;
}

/*************************************************************************
 * FUNCTION
 *	set_gain
 *
 * DESCRIPTION
 *	This function is to set global gain to sensor.
 *
 * PARAMETERS
 *	iGain : sensor global gain(base: 0x40)
 *
 * RETURNS
 *	the actually gain set to sensor.
 *
 * GLOBALS AFFECTED
 *
 *************************************************************************/
static kal_uint16 set_gain(kal_uint16 gain)
{
	kal_uint16 reg_gain;
	kal_uint32 temp_gain;
	kal_int16 gain_index;
	kal_uint16 SC520CS_AGC_Param[SC520CS_SENSOR_GAIN_MAP_SIZE][2] = {
		{  1024,  0x00 },
		{  2048,  0x08 },
		{  4096,  0x09 },
		{  8192,  0x0B },
		{ 16384,  0x0f },
		{ 32768,  0x1f },
	};

    reg_gain = gain2reg(gain);

	for (gain_index = SC520CS_SENSOR_GAIN_MAP_SIZE - 1; gain_index > 0; gain_index--)
		if (reg_gain >= SC520CS_AGC_Param[gain_index][0])
			break;

	write_cmos_sensor(0x3e09, SC520CS_AGC_Param[gain_index][1]);
	temp_gain = reg_gain * SC520CS_SENSOR_GAIN_BASE / SC520CS_AGC_Param[gain_index][0];
	write_cmos_sensor(0x3e07, (temp_gain >> 3) & 0xff);

	LOG_INF("Exit! SC520CS_AGC_Param[gain_index][1] = 0x%x, temp_gain = 0x%x, gain = 0x%x, reg_gain = %d\n",
		SC520CS_AGC_Param[gain_index][1], temp_gain, gain, reg_gain);

	return reg_gain;
}				/*      set_gain  */
/*
static void set_mirror_flip(kal_uint8 image_mirror)
{
	LOG_INF("image_mirror = %d", image_mirror);

	switch (image_mirror) {
		case IMAGE_NORMAL:
			write_cmos_sensor8(0x3221,0x00);
			break;
		case IMAGE_H_MIRROR:
			write_cmos_sensor8(0x3221,0x06);
			break;
		case IMAGE_V_MIRROR:
			write_cmos_sensor8(0x3221,0x60);
			break;
		case IMAGE_HV_MIRROR:
			write_cmos_sensor8(0x3221,0x66);

		break;
	default:
		LOG_INF("Error image_mirror setting");
		break;
	}

}
*/
/*************************************************************************
 * FUNCTION
 *	night_mode
 *
 * DESCRIPTION
 *	This function night mode of sensor.
 *
 * PARAMETERS
 *	bEnable: KAL_TRUE -> enable night mode, otherwise, disable night mode
 *
 * RETURNS
 *	None
 *
 * GLOBALS AFFECTED
 *
 *************************************************************************/
#if 0
static void night_mode(kal_bool enable)
{
	/*No Need to implement this function*/
}	/*	night_mode	*/
#endif

static void sensor_init(void)
{
LOG_INF("[%s] sensor_init\n", __func__);

	write_cmos_sensor8(0x0103,0x01);
	write_cmos_sensor8(0x36e9,0x80);
	write_cmos_sensor8(0x37f9,0x80);
	write_cmos_sensor8(0x36ea,0x17);
	write_cmos_sensor8(0x36eb,0x0c);
	write_cmos_sensor8(0x36ec,0x4a);
	write_cmos_sensor8(0x36ed,0x08);
	write_cmos_sensor8(0x36e9,0x23);
	write_cmos_sensor8(0x37f9,0x23);
	write_cmos_sensor8(0x301f,0x77);
	write_cmos_sensor8(0x3205,0x27);
	write_cmos_sensor8(0x3209,0x20);
	write_cmos_sensor8(0x3211,0x04);
	write_cmos_sensor8(0x3301,0x08);
	write_cmos_sensor8(0x3306,0x60);
	write_cmos_sensor8(0x3308,0x10);
	write_cmos_sensor8(0x3309,0x80);
	write_cmos_sensor8(0x330b,0xd0);
	write_cmos_sensor8(0x3314,0x15);
	write_cmos_sensor8(0x331f,0x71);
	write_cmos_sensor8(0x3333,0x10);
	write_cmos_sensor8(0x3334,0x40);
	write_cmos_sensor8(0x3364,0x56);
	write_cmos_sensor8(0x336c,0xcf);
	write_cmos_sensor8(0x3390,0x09);
	write_cmos_sensor8(0x3391,0x0f);
	write_cmos_sensor8(0x3392,0x1f);
	write_cmos_sensor8(0x3393,0x0e);
	write_cmos_sensor8(0x3394,0x15);
	write_cmos_sensor8(0x3395,0x19);
	write_cmos_sensor8(0x33ad,0x1c);
	write_cmos_sensor8(0x33af,0x3f);
	write_cmos_sensor8(0x33b3,0x30);
	write_cmos_sensor8(0x33b5,0x90);
	write_cmos_sensor8(0x349f,0x1e);
	write_cmos_sensor8(0x34a6,0x09);
	write_cmos_sensor8(0x34a7,0x0b);
	write_cmos_sensor8(0x34a8,0x20);
	write_cmos_sensor8(0x34a9,0x20);
	write_cmos_sensor8(0x34f8,0x0f);
	write_cmos_sensor8(0x34f9,0x10);
	write_cmos_sensor8(0x3630,0x88);
	write_cmos_sensor8(0x3633,0x34);
	write_cmos_sensor8(0x3635,0xc0);
	write_cmos_sensor8(0x3637,0x52);
	write_cmos_sensor8(0x3638,0xc1);
	write_cmos_sensor8(0x363a,0x89);
	write_cmos_sensor8(0x3670,0x4a);
	write_cmos_sensor8(0x3674,0x48);
	write_cmos_sensor8(0x3675,0x28);
	write_cmos_sensor8(0x3676,0x18);
	write_cmos_sensor8(0x367c,0x0f);
	write_cmos_sensor8(0x367d,0x1f);
	write_cmos_sensor8(0x3690,0x43);
	write_cmos_sensor8(0x3691,0x43);
	write_cmos_sensor8(0x3692,0x43);
	write_cmos_sensor8(0x3698,0x89);
	write_cmos_sensor8(0x3699,0x92);
	write_cmos_sensor8(0x369a,0xa5);
	write_cmos_sensor8(0x369b,0xca);
	write_cmos_sensor8(0x369c,0x0b);
	write_cmos_sensor8(0x369d,0x0f);
	write_cmos_sensor8(0x36a2,0x09);
	write_cmos_sensor8(0x36a3,0x0b);
	write_cmos_sensor8(0x36a4,0x0f);
	write_cmos_sensor8(0x36b1,0x38);
	write_cmos_sensor8(0x36b2,0xc1);
	write_cmos_sensor8(0x370f,0x01);
	write_cmos_sensor8(0x3724,0xb1);
	write_cmos_sensor8(0x3771,0x02);
	write_cmos_sensor8(0x3772,0x03);
	write_cmos_sensor8(0x3773,0x03);
	write_cmos_sensor8(0x377a,0x0b);
	write_cmos_sensor8(0x377b,0x0f);
	write_cmos_sensor8(0x3901,0x04);
	write_cmos_sensor8(0x3905,0x8d);
	write_cmos_sensor8(0x391d,0x01);
	write_cmos_sensor8(0x3926,0x23);
	write_cmos_sensor8(0x3e00,0x00);
	write_cmos_sensor8(0x3e01,0xf9);
	write_cmos_sensor8(0x3e02,0x70);
	write_cmos_sensor8(0x3e09,0x00);
	write_cmos_sensor8(0x4401,0x13);
	write_cmos_sensor8(0x4402,0x03);
	write_cmos_sensor8(0x4403,0x0b);
	write_cmos_sensor8(0x4404,0x21);
	write_cmos_sensor8(0x4405,0x29);
	write_cmos_sensor8(0x4407,0x0c);
	write_cmos_sensor8(0x440c,0x34);
	write_cmos_sensor8(0x440d,0x34);
	write_cmos_sensor8(0x440e,0x29);
	write_cmos_sensor8(0x440f,0x3f);
	write_cmos_sensor8(0x4412,0x01);
	write_cmos_sensor8(0x4424,0x01);
	write_cmos_sensor8(0x442d,0x00);
	write_cmos_sensor8(0x442e,0x00);
	write_cmos_sensor8(0x4509,0x28);
	write_cmos_sensor8(0x450d,0x19);
	write_cmos_sensor8(0x451d,0x28);
	write_cmos_sensor8(0x4526,0x05);
	write_cmos_sensor8(0x4819,0x0d);
	write_cmos_sensor8(0x481b,0x07);
	write_cmos_sensor8(0x481d,0x1c);
	write_cmos_sensor8(0x481f,0x06);
	write_cmos_sensor8(0x4821,0x0c);
	write_cmos_sensor8(0x4823,0x07);
	write_cmos_sensor8(0x4825,0x06);
	write_cmos_sensor8(0x4827,0x06);
	write_cmos_sensor8(0x4829,0x0b);
	write_cmos_sensor8(0x5000,0x0e);
	write_cmos_sensor8(0x5007,0x00);
	write_cmos_sensor8(0x550e,0x00);
	write_cmos_sensor8(0x550f,0x42);
	write_cmos_sensor8(0x5780,0x66);
	write_cmos_sensor8(0x5787,0x08);
	write_cmos_sensor8(0x5788,0x04);
	write_cmos_sensor8(0x5789,0x01);
	write_cmos_sensor8(0x578d,0x40);
	write_cmos_sensor8(0x5790,0x08);
	write_cmos_sensor8(0x5791,0x04);
	write_cmos_sensor8(0x5792,0x01);
	write_cmos_sensor8(0x5799,0x46);
	write_cmos_sensor8(0x57aa,0xeb);
	write_cmos_sensor8(0x59f0,0x00);
	write_cmos_sensor8(0x5ae0,0xfe);
	write_cmos_sensor8(0x5ae1,0x40);
	write_cmos_sensor8(0x5ae2,0x38);
	write_cmos_sensor8(0x5ae3,0x30);
	write_cmos_sensor8(0x5ae4,0x0c);
	write_cmos_sensor8(0x5ae5,0x38);
	write_cmos_sensor8(0x5ae6,0x30);
	write_cmos_sensor8(0x5ae7,0x28);
	write_cmos_sensor8(0x5ae8,0x3f);
	write_cmos_sensor8(0x5ae9,0x34);
	write_cmos_sensor8(0x5aea,0x2c);
	write_cmos_sensor8(0x5aeb,0x3f);
	write_cmos_sensor8(0x5aec,0x34);
	write_cmos_sensor8(0x5aed,0x2c);
	write_cmos_sensor8(0x3221,0x66);

	if ((read_cmos_sensor(0x800B)&0xFF)==0)
    {
	 write_cmos_sensor8(0x550F,0x42);
    }else {
	 write_cmos_sensor8(0x550F,0x8a);
    }
	write_cmos_sensor8(0x3650,0x61);
	write_cmos_sensor8(0x3651,0x9d);
	write_cmos_sensor8(0x3652,0x33);
	write_cmos_sensor8(0x3654,0x01);
LOG_INF("Smartsens_SC520CS 0X800B = 0x%x, 0X550f = 0x%x, 0X301f = 0x%x \n", read_cmos_sensor(0x800B),read_cmos_sensor(0x550F),read_cmos_sensor(0x301F));

}



static void preview_setting(void)
{
LOG_INF("[%s] preview_setting\n", __func__);
  	write_cmos_sensor8(0x0103,0x01);
	write_cmos_sensor8(0x36e9,0x80);
	write_cmos_sensor8(0x37f9,0x80);
	write_cmos_sensor8(0x36ea,0x17);
	write_cmos_sensor8(0x36eb,0x0c);
	write_cmos_sensor8(0x36ec,0x4a);
	write_cmos_sensor8(0x36ed,0x08);
	write_cmos_sensor8(0x36e9,0x23);
	write_cmos_sensor8(0x37f9,0x23);
	write_cmos_sensor8(0x301f,0x77);
	write_cmos_sensor8(0x3205,0x27);
	write_cmos_sensor8(0x3209,0x20);
	write_cmos_sensor8(0x3211,0x04);
	write_cmos_sensor8(0x3301,0x08);
	write_cmos_sensor8(0x3306,0x60);
	write_cmos_sensor8(0x3308,0x10);
	write_cmos_sensor8(0x3309,0x80);
	write_cmos_sensor8(0x330b,0xd0);
	write_cmos_sensor8(0x3314,0x15);
	write_cmos_sensor8(0x331f,0x71);
	write_cmos_sensor8(0x3333,0x10);
	write_cmos_sensor8(0x3334,0x40);
	write_cmos_sensor8(0x3364,0x56);
	write_cmos_sensor8(0x336c,0xcf);
	write_cmos_sensor8(0x3390,0x09);
	write_cmos_sensor8(0x3391,0x0f);
	write_cmos_sensor8(0x3392,0x1f);
	write_cmos_sensor8(0x3393,0x0e);
	write_cmos_sensor8(0x3394,0x15);
	write_cmos_sensor8(0x3395,0x19);
	write_cmos_sensor8(0x33ad,0x1c);
	write_cmos_sensor8(0x33af,0x3f);
	write_cmos_sensor8(0x33b3,0x30);
	write_cmos_sensor8(0x33b5,0x90);
	write_cmos_sensor8(0x349f,0x1e);
	write_cmos_sensor8(0x34a6,0x09);
	write_cmos_sensor8(0x34a7,0x0b);
	write_cmos_sensor8(0x34a8,0x20);
	write_cmos_sensor8(0x34a9,0x20);
	write_cmos_sensor8(0x34f8,0x0f);
	write_cmos_sensor8(0x34f9,0x10);
	write_cmos_sensor8(0x3630,0x88);
	write_cmos_sensor8(0x3633,0x34);
	write_cmos_sensor8(0x3635,0xc0);
	write_cmos_sensor8(0x3637,0x52);
	write_cmos_sensor8(0x3638,0xc1);
	write_cmos_sensor8(0x363a,0x89);
	write_cmos_sensor8(0x3670,0x4a);
	write_cmos_sensor8(0x3674,0x48);
	write_cmos_sensor8(0x3675,0x28);
	write_cmos_sensor8(0x3676,0x18);
	write_cmos_sensor8(0x367c,0x0f);
	write_cmos_sensor8(0x367d,0x1f);
	write_cmos_sensor8(0x3690,0x43);
	write_cmos_sensor8(0x3691,0x43);
	write_cmos_sensor8(0x3692,0x43);
	write_cmos_sensor8(0x3698,0x89);
	write_cmos_sensor8(0x3699,0x92);
	write_cmos_sensor8(0x369a,0xa5);
	write_cmos_sensor8(0x369b,0xca);
	write_cmos_sensor8(0x369c,0x0b);
	write_cmos_sensor8(0x369d,0x0f);
	write_cmos_sensor8(0x36a2,0x09);
	write_cmos_sensor8(0x36a3,0x0b);
	write_cmos_sensor8(0x36a4,0x0f);
	write_cmos_sensor8(0x36b1,0x38);
	write_cmos_sensor8(0x36b2,0xc1);
	write_cmos_sensor8(0x370f,0x01);
	write_cmos_sensor8(0x3724,0xb1);
	write_cmos_sensor8(0x3771,0x02);
	write_cmos_sensor8(0x3772,0x03);
	write_cmos_sensor8(0x3773,0x03);
	write_cmos_sensor8(0x377a,0x0b);
	write_cmos_sensor8(0x377b,0x0f);
	write_cmos_sensor8(0x3901,0x04);
	write_cmos_sensor8(0x3905,0x8d);
	write_cmos_sensor8(0x391d,0x01);
	write_cmos_sensor8(0x3926,0x23);
	write_cmos_sensor8(0x3e00,0x00);
	write_cmos_sensor8(0x3e01,0xf9);
	write_cmos_sensor8(0x3e02,0x70);
	write_cmos_sensor8(0x3e09,0x00);
	write_cmos_sensor8(0x4401,0x13);
	write_cmos_sensor8(0x4402,0x03);
	write_cmos_sensor8(0x4403,0x0b);
	write_cmos_sensor8(0x4404,0x21);
	write_cmos_sensor8(0x4405,0x29);
	write_cmos_sensor8(0x4407,0x0c);
	write_cmos_sensor8(0x440c,0x34);
	write_cmos_sensor8(0x440d,0x34);
	write_cmos_sensor8(0x440e,0x29);
	write_cmos_sensor8(0x440f,0x3f);
	write_cmos_sensor8(0x4412,0x01);
	write_cmos_sensor8(0x4424,0x01);
	write_cmos_sensor8(0x442d,0x00);
	write_cmos_sensor8(0x442e,0x00);
	write_cmos_sensor8(0x4509,0x28);
	write_cmos_sensor8(0x450d,0x19);
	write_cmos_sensor8(0x451d,0x28);
	write_cmos_sensor8(0x4526,0x05);
	write_cmos_sensor8(0x4819,0x0d);
	write_cmos_sensor8(0x481b,0x07);
	write_cmos_sensor8(0x481d,0x1c);
	write_cmos_sensor8(0x481f,0x06);
	write_cmos_sensor8(0x4821,0x0c);
	write_cmos_sensor8(0x4823,0x07);
	write_cmos_sensor8(0x4825,0x06);
	write_cmos_sensor8(0x4827,0x06);
	write_cmos_sensor8(0x4829,0x0b);
	write_cmos_sensor8(0x5000,0x0e);
	write_cmos_sensor8(0x5007,0x00);
	write_cmos_sensor8(0x550e,0x00);
	write_cmos_sensor8(0x550f,0x42);
	write_cmos_sensor8(0x5780,0x66);
	write_cmos_sensor8(0x5787,0x08);
	write_cmos_sensor8(0x5788,0x04);
	write_cmos_sensor8(0x5789,0x01);
	write_cmos_sensor8(0x578d,0x40);
	write_cmos_sensor8(0x5790,0x08);
	write_cmos_sensor8(0x5791,0x04);
	write_cmos_sensor8(0x5792,0x01);
	write_cmos_sensor8(0x5799,0x46);
	write_cmos_sensor8(0x57aa,0xeb);
	write_cmos_sensor8(0x59f0,0x00);
	write_cmos_sensor8(0x5ae0,0xfe);
	write_cmos_sensor8(0x5ae1,0x40);
	write_cmos_sensor8(0x5ae2,0x38);
	write_cmos_sensor8(0x5ae3,0x30);
	write_cmos_sensor8(0x5ae4,0x0c);
	write_cmos_sensor8(0x5ae5,0x38);
	write_cmos_sensor8(0x5ae6,0x30);
	write_cmos_sensor8(0x5ae7,0x28);
	write_cmos_sensor8(0x5ae8,0x3f);
	write_cmos_sensor8(0x5ae9,0x34);
	write_cmos_sensor8(0x5aea,0x2c);
	write_cmos_sensor8(0x5aeb,0x3f);
	write_cmos_sensor8(0x5aec,0x34);
	write_cmos_sensor8(0x5aed,0x2c);
	write_cmos_sensor8(0x3221,0x66);

	if ((read_cmos_sensor(0x800B)&0xFF)==0)
    {
	 write_cmos_sensor8(0x550F,0x42);
    }else {
	 write_cmos_sensor8(0x550F,0x8a);
    }
	write_cmos_sensor8(0x3650,0x61);
	write_cmos_sensor8(0x3651,0x9d);
	write_cmos_sensor8(0x3652,0x33);
	write_cmos_sensor8(0x3654,0x01);
LOG_INF("Smartsens_SC520CS 0X800B = 0x%x, 0X550f = 0x%x, 0X301f = 0x%x \n", read_cmos_sensor(0x800B),read_cmos_sensor(0x550F),read_cmos_sensor(0x301F));
}

static void capture_setting(kal_uint16 currefps)
{
LOG_INF("[%s] capture_setting\n", __func__);
   	write_cmos_sensor8(0x0103,0x01);
	write_cmos_sensor8(0x36e9,0x80);
	write_cmos_sensor8(0x37f9,0x80);
	write_cmos_sensor8(0x36ea,0x17);
	write_cmos_sensor8(0x36eb,0x0c);
	write_cmos_sensor8(0x36ec,0x4a);
	write_cmos_sensor8(0x36ed,0x08);
	write_cmos_sensor8(0x36e9,0x23);
	write_cmos_sensor8(0x37f9,0x23);
	write_cmos_sensor8(0x301f,0x77);
	write_cmos_sensor8(0x3205,0x27);
	write_cmos_sensor8(0x3209,0x20);
	write_cmos_sensor8(0x3211,0x04);
	write_cmos_sensor8(0x3301,0x08);
	write_cmos_sensor8(0x3306,0x60);
	write_cmos_sensor8(0x3308,0x10);
	write_cmos_sensor8(0x3309,0x80);
	write_cmos_sensor8(0x330b,0xd0);
	write_cmos_sensor8(0x3314,0x15);
	write_cmos_sensor8(0x331f,0x71);
	write_cmos_sensor8(0x3333,0x10);
	write_cmos_sensor8(0x3334,0x40);
	write_cmos_sensor8(0x3364,0x56);
	write_cmos_sensor8(0x336c,0xcf);
	write_cmos_sensor8(0x3390,0x09);
	write_cmos_sensor8(0x3391,0x0f);
	write_cmos_sensor8(0x3392,0x1f);
	write_cmos_sensor8(0x3393,0x0e);
	write_cmos_sensor8(0x3394,0x15);
	write_cmos_sensor8(0x3395,0x19);
	write_cmos_sensor8(0x33ad,0x1c);
	write_cmos_sensor8(0x33af,0x3f);
	write_cmos_sensor8(0x33b3,0x30);
	write_cmos_sensor8(0x33b5,0x90);
	write_cmos_sensor8(0x349f,0x1e);
	write_cmos_sensor8(0x34a6,0x09);
	write_cmos_sensor8(0x34a7,0x0b);
	write_cmos_sensor8(0x34a8,0x20);
	write_cmos_sensor8(0x34a9,0x20);
	write_cmos_sensor8(0x34f8,0x0f);
	write_cmos_sensor8(0x34f9,0x10);
	write_cmos_sensor8(0x3630,0x88);
	write_cmos_sensor8(0x3633,0x34);
	write_cmos_sensor8(0x3635,0xc0);
	write_cmos_sensor8(0x3637,0x52);
	write_cmos_sensor8(0x3638,0xc1);
	write_cmos_sensor8(0x363a,0x89);
	write_cmos_sensor8(0x3670,0x4a);
	write_cmos_sensor8(0x3674,0x48);
	write_cmos_sensor8(0x3675,0x28);
	write_cmos_sensor8(0x3676,0x18);
	write_cmos_sensor8(0x367c,0x0f);
	write_cmos_sensor8(0x367d,0x1f);
	write_cmos_sensor8(0x3690,0x43);
	write_cmos_sensor8(0x3691,0x43);
	write_cmos_sensor8(0x3692,0x43);
	write_cmos_sensor8(0x3698,0x89);
	write_cmos_sensor8(0x3699,0x92);
	write_cmos_sensor8(0x369a,0xa5);
	write_cmos_sensor8(0x369b,0xca);
	write_cmos_sensor8(0x369c,0x0b);
	write_cmos_sensor8(0x369d,0x0f);
	write_cmos_sensor8(0x36a2,0x09);
	write_cmos_sensor8(0x36a3,0x0b);
	write_cmos_sensor8(0x36a4,0x0f);
	write_cmos_sensor8(0x36b1,0x38);
	write_cmos_sensor8(0x36b2,0xc1);
	write_cmos_sensor8(0x370f,0x01);
	write_cmos_sensor8(0x3724,0xb1);
	write_cmos_sensor8(0x3771,0x02);
	write_cmos_sensor8(0x3772,0x03);
	write_cmos_sensor8(0x3773,0x03);
	write_cmos_sensor8(0x377a,0x0b);
	write_cmos_sensor8(0x377b,0x0f);
	write_cmos_sensor8(0x3901,0x04);
	write_cmos_sensor8(0x3905,0x8d);
	write_cmos_sensor8(0x391d,0x01);
	write_cmos_sensor8(0x3926,0x23);
	write_cmos_sensor8(0x3e00,0x00);
	write_cmos_sensor8(0x3e01,0xf9);
	write_cmos_sensor8(0x3e02,0x70);
	write_cmos_sensor8(0x3e09,0x00);
	write_cmos_sensor8(0x4401,0x13);
	write_cmos_sensor8(0x4402,0x03);
	write_cmos_sensor8(0x4403,0x0b);
	write_cmos_sensor8(0x4404,0x21);
	write_cmos_sensor8(0x4405,0x29);
	write_cmos_sensor8(0x4407,0x0c);
	write_cmos_sensor8(0x440c,0x34);
	write_cmos_sensor8(0x440d,0x34);
	write_cmos_sensor8(0x440e,0x29);
	write_cmos_sensor8(0x440f,0x3f);
	write_cmos_sensor8(0x4412,0x01);
	write_cmos_sensor8(0x4424,0x01);
	write_cmos_sensor8(0x442d,0x00);
	write_cmos_sensor8(0x442e,0x00);
	write_cmos_sensor8(0x4509,0x28);
	write_cmos_sensor8(0x450d,0x19);
	write_cmos_sensor8(0x451d,0x28);
	write_cmos_sensor8(0x4526,0x05);
	write_cmos_sensor8(0x4819,0x0d);
	write_cmos_sensor8(0x481b,0x07);
	write_cmos_sensor8(0x481d,0x1c);
	write_cmos_sensor8(0x481f,0x06);
	write_cmos_sensor8(0x4821,0x0c);
	write_cmos_sensor8(0x4823,0x07);
	write_cmos_sensor8(0x4825,0x06);
	write_cmos_sensor8(0x4827,0x06);
	write_cmos_sensor8(0x4829,0x0b);
	write_cmos_sensor8(0x5000,0x0e);
	write_cmos_sensor8(0x5007,0x00);
	write_cmos_sensor8(0x550e,0x00);
	write_cmos_sensor8(0x550f,0x42);
	write_cmos_sensor8(0x5780,0x66);
	write_cmos_sensor8(0x5787,0x08);
	write_cmos_sensor8(0x5788,0x04);
	write_cmos_sensor8(0x5789,0x01);
	write_cmos_sensor8(0x578d,0x40);
	write_cmos_sensor8(0x5790,0x08);
	write_cmos_sensor8(0x5791,0x04);
	write_cmos_sensor8(0x5792,0x01);
	write_cmos_sensor8(0x5799,0x46);
	write_cmos_sensor8(0x57aa,0xeb);
	write_cmos_sensor8(0x59f0,0x00);
	write_cmos_sensor8(0x5ae0,0xfe);
	write_cmos_sensor8(0x5ae1,0x40);
	write_cmos_sensor8(0x5ae2,0x38);
	write_cmos_sensor8(0x5ae3,0x30);
	write_cmos_sensor8(0x5ae4,0x0c);
	write_cmos_sensor8(0x5ae5,0x38);
	write_cmos_sensor8(0x5ae6,0x30);
	write_cmos_sensor8(0x5ae7,0x28);
	write_cmos_sensor8(0x5ae8,0x3f);
	write_cmos_sensor8(0x5ae9,0x34);
	write_cmos_sensor8(0x5aea,0x2c);
	write_cmos_sensor8(0x5aeb,0x3f);
	write_cmos_sensor8(0x5aec,0x34);
	write_cmos_sensor8(0x5aed,0x2c);
	write_cmos_sensor8(0x3221,0x66);

	if ((read_cmos_sensor(0x800B)&0xFF)==0)
    {
	 write_cmos_sensor8(0x550F,0x42);
    }else {
	 write_cmos_sensor8(0x550F,0x8a);
    }
	write_cmos_sensor8(0x3650,0x61);
	write_cmos_sensor8(0x3651,0x9d);
	write_cmos_sensor8(0x3652,0x33);
	write_cmos_sensor8(0x3654,0x01);
LOG_INF("Smartsens_SC520CS 0X800B = 0x%x, 0X550f = 0x%x, 0X301f = 0x%x \n", read_cmos_sensor(0x800B),read_cmos_sensor(0x550F),read_cmos_sensor(0x301F));
	
}

static void normal_video_setting(void)
{
	write_cmos_sensor8(0x0103,0x01);
	write_cmos_sensor8(0x36e9,0x80);
	write_cmos_sensor8(0x37f9,0x80);
	write_cmos_sensor8(0x36e9,0x23);
	write_cmos_sensor8(0x37f9,0x23);
	write_cmos_sensor8(0x301f,0x10);
	write_cmos_sensor8(0x3200,0x00);
	write_cmos_sensor8(0x3201,0x00);
	write_cmos_sensor8(0x3202,0x00);
	write_cmos_sensor8(0x3203,0xfc);
	write_cmos_sensor8(0x3204,0x0a);
	write_cmos_sensor8(0x3205,0x27);
	write_cmos_sensor8(0x3206,0x06);
	write_cmos_sensor8(0x3207,0xab);
	write_cmos_sensor8(0x3208,0x0a);
	write_cmos_sensor8(0x3209,0x00);
	write_cmos_sensor8(0x320a,0x05);
	write_cmos_sensor8(0x320b,0xa0);
	write_cmos_sensor8(0x3210,0x00);
	write_cmos_sensor8(0x3211,0x14);
	write_cmos_sensor8(0x3212,0x00);
	write_cmos_sensor8(0x3213,0x08);
	write_cmos_sensor8(0x3301,0x08);
	write_cmos_sensor8(0x3306,0x60);
	write_cmos_sensor8(0x3308,0x10);
	write_cmos_sensor8(0x3309,0x80);
	write_cmos_sensor8(0x330b,0xd0);
	write_cmos_sensor8(0x3314,0x15);
	write_cmos_sensor8(0x331f,0x71);
	write_cmos_sensor8(0x3333,0x10);
	write_cmos_sensor8(0x3334,0x40);
	write_cmos_sensor8(0x3364,0x56);
	write_cmos_sensor8(0x336c,0xcf);
	write_cmos_sensor8(0x3390,0x09);
	write_cmos_sensor8(0x3391,0x0f);
	write_cmos_sensor8(0x3392,0x1f);
	write_cmos_sensor8(0x3393,0x0e);
	write_cmos_sensor8(0x3394,0x15);
	write_cmos_sensor8(0x3395,0x19);
	write_cmos_sensor8(0x33ad,0x1c);
	write_cmos_sensor8(0x33af,0x3f);
	write_cmos_sensor8(0x33b3,0x30);
	write_cmos_sensor8(0x33b5,0x90);
	write_cmos_sensor8(0x349f,0x1e);
	write_cmos_sensor8(0x34a6,0x09);
	write_cmos_sensor8(0x34a7,0x0b);
	write_cmos_sensor8(0x34a8,0x20);
	write_cmos_sensor8(0x34a9,0x20);
	write_cmos_sensor8(0x34f8,0x0f);
	write_cmos_sensor8(0x34f9,0x10);
	write_cmos_sensor8(0x3630,0x88);
	write_cmos_sensor8(0x3633,0x34);
	write_cmos_sensor8(0x3635,0xc0);
	write_cmos_sensor8(0x3637,0x52);
	write_cmos_sensor8(0x3638,0xc1);
	write_cmos_sensor8(0x363a,0x89);
	write_cmos_sensor8(0x3670,0x4a);
	write_cmos_sensor8(0x3674,0x48);
	write_cmos_sensor8(0x3675,0x28);
	write_cmos_sensor8(0x3676,0x18);
	write_cmos_sensor8(0x367c,0x0f);
	write_cmos_sensor8(0x367d,0x1f);
	write_cmos_sensor8(0x3690,0x43);
	write_cmos_sensor8(0x3691,0x43);
	write_cmos_sensor8(0x3692,0x43);
	write_cmos_sensor8(0x3698,0x89);
	write_cmos_sensor8(0x3699,0x92);
	write_cmos_sensor8(0x369a,0xa5);
	write_cmos_sensor8(0x369b,0xca);
	write_cmos_sensor8(0x369c,0x0b);
	write_cmos_sensor8(0x369d,0x0f);
	write_cmos_sensor8(0x36a2,0x09);
	write_cmos_sensor8(0x36a3,0x0b);
	write_cmos_sensor8(0x36a4,0x0f);
	write_cmos_sensor8(0x36b1,0x38);
	write_cmos_sensor8(0x36b2,0xc1);
	write_cmos_sensor8(0x370f,0x01);
	write_cmos_sensor8(0x3724,0xb1);
	write_cmos_sensor8(0x3771,0x02);
	write_cmos_sensor8(0x3772,0x03);
	write_cmos_sensor8(0x3773,0x03);
	write_cmos_sensor8(0x377a,0x0b);
	write_cmos_sensor8(0x377b,0x0f);
	write_cmos_sensor8(0x3901,0x04);
	write_cmos_sensor8(0x3905,0x8d);
	write_cmos_sensor8(0x391d,0x01);
	write_cmos_sensor8(0x3926,0x23);
	write_cmos_sensor8(0x3e00,0x00);
	write_cmos_sensor8(0x3e01,0xf9);
	write_cmos_sensor8(0x3e02,0x70);
	write_cmos_sensor8(0x3e09,0x00);
	write_cmos_sensor8(0x4401,0x13);
	write_cmos_sensor8(0x4402,0x02);
	write_cmos_sensor8(0x4403,0x09);
	write_cmos_sensor8(0x4404,0x1b);
	write_cmos_sensor8(0x4405,0x24);
	write_cmos_sensor8(0x4407,0x0c);
	write_cmos_sensor8(0x440c,0x2d);
	write_cmos_sensor8(0x440d,0x2d);
	write_cmos_sensor8(0x440e,0x22);
	write_cmos_sensor8(0x440f,0x39);
	write_cmos_sensor8(0x4412,0x01);
	write_cmos_sensor8(0x4424,0x01);
	write_cmos_sensor8(0x442d,0x00);
	write_cmos_sensor8(0x442e,0x00);
	write_cmos_sensor8(0x4509,0x28);
	write_cmos_sensor8(0x450d,0x19);
	write_cmos_sensor8(0x451d,0x28);
	write_cmos_sensor8(0x4526,0x05);
	write_cmos_sensor8(0x5000,0x0e);
	write_cmos_sensor8(0x5007,0x00);
	write_cmos_sensor8(0x550e,0x00);
	write_cmos_sensor8(0x550f,0x8a);
	write_cmos_sensor8(0x5780,0x66);
	write_cmos_sensor8(0x5787,0x08);
	write_cmos_sensor8(0x5788,0x04);
	write_cmos_sensor8(0x5789,0x01);
	write_cmos_sensor8(0x578d,0x40);
	write_cmos_sensor8(0x5790,0x08);
	write_cmos_sensor8(0x5791,0x04);
	write_cmos_sensor8(0x5792,0x01);
	write_cmos_sensor8(0x5799,0x46);
	write_cmos_sensor8(0x57aa,0xeb);
	write_cmos_sensor8(0x59f0,0x00);
	write_cmos_sensor8(0x5ae0,0xfe);
	write_cmos_sensor8(0x5ae1,0x40);
	write_cmos_sensor8(0x5ae2,0x38);
	write_cmos_sensor8(0x5ae3,0x30);
	write_cmos_sensor8(0x5ae4,0x0c);
	write_cmos_sensor8(0x5ae5,0x38);
	write_cmos_sensor8(0x5ae6,0x30);
	write_cmos_sensor8(0x5ae7,0x28);
	write_cmos_sensor8(0x5ae8,0x3f);
	write_cmos_sensor8(0x5ae9,0x34);
	write_cmos_sensor8(0x5aea,0x2c);
	write_cmos_sensor8(0x5aeb,0x3f);
	write_cmos_sensor8(0x5aec,0x34);
	write_cmos_sensor8(0x5aed,0x2c);
	write_cmos_sensor8(0x3221,0x66);

	if ((read_cmos_sensor(0x800B)&0xFF)==0)
    {
	 write_cmos_sensor8(0x550F,0x42);
    }else {
	 write_cmos_sensor8(0x550F,0x8a);
    }
}
static void hs_video_setting(void)
{
  sensor_init();

}


static void slim_video_setting(void)
{
  sensor_init();

}

static void custom1_setting(void)
{
	write_cmos_sensor8(0x0103,0x01);
	write_cmos_sensor8(0x36e9,0x80);
	write_cmos_sensor8(0x37f9,0x80);
	write_cmos_sensor8(0x36ea,0x17);
	write_cmos_sensor8(0x36eb,0x0c);
	write_cmos_sensor8(0x36ec,0x4a);
	write_cmos_sensor8(0x36ed,0x08);
	write_cmos_sensor8(0x36e9,0x23);
	write_cmos_sensor8(0x37f9,0x23);
	write_cmos_sensor8(0x301f,0x77);
	write_cmos_sensor8(0x3205,0x27);
	write_cmos_sensor8(0x3209,0x20);
	write_cmos_sensor8(0x3211,0x04);
	write_cmos_sensor8(0x3301,0x08);
	write_cmos_sensor8(0x3306,0x60);
	write_cmos_sensor8(0x3308,0x10);
	write_cmos_sensor8(0x3309,0x80);
	write_cmos_sensor8(0x330b,0xd0);
	write_cmos_sensor8(0x3314,0x15);
	write_cmos_sensor8(0x331f,0x71);
	write_cmos_sensor8(0x3333,0x10);
	write_cmos_sensor8(0x3334,0x40);
	write_cmos_sensor8(0x3364,0x56);
	write_cmos_sensor8(0x336c,0xcf);
	write_cmos_sensor8(0x3390,0x09);
	write_cmos_sensor8(0x3391,0x0f);
	write_cmos_sensor8(0x3392,0x1f);
	write_cmos_sensor8(0x3393,0x0e);
	write_cmos_sensor8(0x3394,0x15);
	write_cmos_sensor8(0x3395,0x19);
	write_cmos_sensor8(0x33ad,0x1c);
	write_cmos_sensor8(0x33af,0x3f);
	write_cmos_sensor8(0x33b3,0x30);
	write_cmos_sensor8(0x33b5,0x90);
	write_cmos_sensor8(0x349f,0x1e);
	write_cmos_sensor8(0x34a6,0x09);
	write_cmos_sensor8(0x34a7,0x0b);
	write_cmos_sensor8(0x34a8,0x20);
	write_cmos_sensor8(0x34a9,0x20);
	write_cmos_sensor8(0x34f8,0x0f);
	write_cmos_sensor8(0x34f9,0x10);
	write_cmos_sensor8(0x3630,0x88);
	write_cmos_sensor8(0x3633,0x34);
	write_cmos_sensor8(0x3635,0xc0);
	write_cmos_sensor8(0x3637,0x52);
	write_cmos_sensor8(0x3638,0xc1);
	write_cmos_sensor8(0x363a,0x89);
	write_cmos_sensor8(0x3670,0x4a);
	write_cmos_sensor8(0x3674,0x48);
	write_cmos_sensor8(0x3675,0x28);
	write_cmos_sensor8(0x3676,0x18);
	write_cmos_sensor8(0x367c,0x0f);
	write_cmos_sensor8(0x367d,0x1f);
	write_cmos_sensor8(0x3690,0x43);
	write_cmos_sensor8(0x3691,0x43);
	write_cmos_sensor8(0x3692,0x43);
	write_cmos_sensor8(0x3698,0x89);
	write_cmos_sensor8(0x3699,0x92);
	write_cmos_sensor8(0x369a,0xa5);
	write_cmos_sensor8(0x369b,0xca);
	write_cmos_sensor8(0x369c,0x0b);
	write_cmos_sensor8(0x369d,0x0f);
	write_cmos_sensor8(0x36a2,0x09);
	write_cmos_sensor8(0x36a3,0x0b);
	write_cmos_sensor8(0x36a4,0x0f);
	write_cmos_sensor8(0x36b1,0x38);
	write_cmos_sensor8(0x36b2,0xc1);
	write_cmos_sensor8(0x370f,0x01);
	write_cmos_sensor8(0x3724,0xb1);
	write_cmos_sensor8(0x3771,0x02);
	write_cmos_sensor8(0x3772,0x03);
	write_cmos_sensor8(0x3773,0x03);
	write_cmos_sensor8(0x377a,0x0b);
	write_cmos_sensor8(0x377b,0x0f);
	write_cmos_sensor8(0x3901,0x04);
	write_cmos_sensor8(0x3905,0x8d);
	write_cmos_sensor8(0x391d,0x01);
	write_cmos_sensor8(0x3926,0x23);
	write_cmos_sensor8(0x3e00,0x00);
	write_cmos_sensor8(0x3e01,0xf9);
	write_cmos_sensor8(0x3e02,0x70);
	write_cmos_sensor8(0x3e09,0x00);
	write_cmos_sensor8(0x4401,0x13);
	write_cmos_sensor8(0x4402,0x03);
	write_cmos_sensor8(0x4403,0x0b);
	write_cmos_sensor8(0x4404,0x21);
	write_cmos_sensor8(0x4405,0x29);
	write_cmos_sensor8(0x4407,0x0c);
	write_cmos_sensor8(0x440c,0x34);
	write_cmos_sensor8(0x440d,0x34);
	write_cmos_sensor8(0x440e,0x29);
	write_cmos_sensor8(0x440f,0x3f);
	write_cmos_sensor8(0x4412,0x01);
	write_cmos_sensor8(0x4424,0x01);
	write_cmos_sensor8(0x442d,0x00);
	write_cmos_sensor8(0x442e,0x00);
	write_cmos_sensor8(0x4509,0x28);
	write_cmos_sensor8(0x450d,0x19);
	write_cmos_sensor8(0x451d,0x28);
	write_cmos_sensor8(0x4526,0x05);
	write_cmos_sensor8(0x4819,0x0d);
	write_cmos_sensor8(0x481b,0x07);
	write_cmos_sensor8(0x481d,0x1c);
	write_cmos_sensor8(0x481f,0x06);
	write_cmos_sensor8(0x4821,0x0c);
	write_cmos_sensor8(0x4823,0x07);
	write_cmos_sensor8(0x4825,0x06);
	write_cmos_sensor8(0x4827,0x06);
	write_cmos_sensor8(0x4829,0x0b);
	write_cmos_sensor8(0x5000,0x0e);
	write_cmos_sensor8(0x5007,0x00);
	write_cmos_sensor8(0x550e,0x00);
	write_cmos_sensor8(0x550f,0x42);
	write_cmos_sensor8(0x5780,0x66);
	write_cmos_sensor8(0x5787,0x08);
	write_cmos_sensor8(0x5788,0x04);
	write_cmos_sensor8(0x5789,0x01);
	write_cmos_sensor8(0x578d,0x40);
	write_cmos_sensor8(0x5790,0x08);
	write_cmos_sensor8(0x5791,0x04);
	write_cmos_sensor8(0x5792,0x01);
	write_cmos_sensor8(0x5799,0x46);
	write_cmos_sensor8(0x57aa,0xeb);
	write_cmos_sensor8(0x59f0,0x00);
	write_cmos_sensor8(0x5ae0,0xfe);
	write_cmos_sensor8(0x5ae1,0x40);
	write_cmos_sensor8(0x5ae2,0x38);
	write_cmos_sensor8(0x5ae3,0x30);
	write_cmos_sensor8(0x5ae4,0x0c);
	write_cmos_sensor8(0x5ae5,0x38);
	write_cmos_sensor8(0x5ae6,0x30);
	write_cmos_sensor8(0x5ae7,0x28);
	write_cmos_sensor8(0x5ae8,0x3f);
	write_cmos_sensor8(0x5ae9,0x34);
	write_cmos_sensor8(0x5aea,0x2c);
	write_cmos_sensor8(0x5aeb,0x3f);
	write_cmos_sensor8(0x5aec,0x34);
	write_cmos_sensor8(0x5aed,0x2c);
	write_cmos_sensor8(0x550f,0x8a);
	write_cmos_sensor8(0x320e,0x09);
	write_cmos_sensor8(0x320f,0xc4);
	write_cmos_sensor8(0x3e00,0x01);
	write_cmos_sensor8(0x3e01,0x37);
	write_cmos_sensor8(0x3e02,0xf0);
	write_cmos_sensor8(0x3221,0x66);
}
/*
static kal_uint16 read_cmos_sensor_sc520cs(kal_uint32 addr)
{
	kal_uint16 get_byte = 0;
	char pu_send_cmd[2] = {(char)(addr >> 8), (char)(addr & 0xFF) };
	iReadRegI2C(pu_send_cmd, 2, (u8 *)&get_byte, 1, 0xA2);
	return get_byte;
}

static void sc520cs_fusion_id_read(void)
{
	int i;
	for (i=0; i<11; i++) {
		fusion_id_front[i] = read_cmos_sensor_sc520cs(0x10+i);
	pr_err("%s %d lss fusion_id_front[%d]=0x%2x\n",__func__, __LINE__, i, fusion_id_front[i]);
	}
}
static void sc520cs_sn_id_read(void)
{
	int i;
	for (i=0; i<14; i++) {
	        sn_front[i] = read_cmos_sensor_sc520cs(0x1F92+i);
		pr_err("%s %d lss fusion_id_front[%d]=0x%2x\n",__func__, __LINE__, i, sn_front[i]);
	}
}*/
/*
static void get_sensor_module_info(void)
{
    int i;
    u8 calmoduleversion[16] = {0};
    for (i = 0; i < 15; i++) {
        calmoduleversion[i] = read_cmos_sensor_sc520cs(0x01+i);
        //pr_err("%s %d sc520cs module_id[%d]=0x%2x\n",__func__, __LINE__, i, calmoduleversion[i]);
    }
    pr_err("======================module version==================\n");
    pr_err("[vendor id] = 0x%x\n", calmoduleversion[0]);
    pr_err("[yy/mm/dd] = %d/%d/%d \n", calmoduleversion[1], calmoduleversion[2], calmoduleversion[3]);
    pr_err("[hh/mm/sec] = %d:%d:%d \n", calmoduleversion[4], calmoduleversion[5], calmoduleversion[6]);
    pr_err("[lens_id/vcmid/drive id] = 0x%x/0x%x/0x%x \n", calmoduleversion[7], calmoduleversion[8], calmoduleversion[9]);
    pr_err("======================module version==================\n");
}
*/

void sc520cs_sensor_otp_init(int section, kal_uint8 threshold)
{
	/*0x4412, 0xxx, read 0x8000-0x87FF data£¬0x4412,0x01
	 read 0x8800-0x8FFF£¬0x4412,0x03
	 0x4407, 0xxx, read 0x8000-0x87FF £¬0x4407,0x0c
	 read 0x8800-0x8FFF £¬0x4407,0x00
	*/
	write_cmos_sensor8(0x36b0, 0x4c);
	write_cmos_sensor8(0x36b1, threshold);	/* set threshold */
	write_cmos_sensor8(0x36b2, 0xc1);
	if (section == 1) {
		write_cmos_sensor8(0x4408, (0x8000 >> 8)&0xff);        /* High byte start address for OTP load Group1 */
		write_cmos_sensor8(0x4409, (0x8000)&0xff);             /* Low byte start address for OTP load  Group1 */
		write_cmos_sensor8(0x440a, (0x87FF >> 8)&0xff);        /* High byte end address for OTP load Group1 */
		write_cmos_sensor8(0x440b, (0x87FF)&0xff);             /* Low byte end address for OTP load Group1 */
		write_cmos_sensor8(0x4401, 0x13);
		write_cmos_sensor8(0x4412, 0x01);
		write_cmos_sensor8(0x4407, 0x0c);
		write_cmos_sensor8(0x4400, 0x11);                      /* 0x4400, 0x11 manual load */
		LOG_INF("load section 1 \n");
	} else if (section == 2) {
		write_cmos_sensor8(0x4408, (0x8800 >> 8)&0xff);        /* High byte start address for OTP load Group1 */
		write_cmos_sensor8(0x4409, (0x8800)&0xff);             /* Low byte start address for OTP load  Group1 */
		write_cmos_sensor8(0x440a, (0x8FFF >> 8)&0xff);        /* High byte end address for OTP load Group1 */
		write_cmos_sensor8(0x440b, (0x8FFF)&0xff);             /* Low byte end address for OTP load Group1 */
		write_cmos_sensor8(0x4401, 0x13);
		write_cmos_sensor8(0x4412, 0x03);
		write_cmos_sensor8(0x4407, 0x00);
		write_cmos_sensor8(0x4400, 0x11);	                     /* 0x4400, 0x11 manual load */
		LOG_INF("load section 2 \n");
	} else {
		LOG_INF("section input error \n");
	}
	mdelay(30);                                              /* wait page load finished */
}

static int sc520cs_sensor_otp_read_data(unsigned int ui4_offset,unsigned int ui4_length, unsigned char *pinputdata)
{
	int i;
	unsigned int checksum_cal = 0;
	unsigned int checksum = 0;

	for(i=0; i<ui4_length; i++)
	{
		pinputdata[i] = read_cmos_sensor(ui4_offset + i);
		checksum_cal += pinputdata[i];
		#if SC520CS_ST_DEBUG_ON
		LOG_INF("sc520cs_sensor_otp_read_data addr=0x%x, data=0x%x\n", ui4_offset + i, pinputdata[i]);
		#endif
	}

	checksum = pinputdata[i-1];
	checksum_cal -= checksum;
	checksum_cal = checksum_cal%255+1;
	if(checksum_cal != checksum)
	{
		LOG_INF("sc520cs_sensor_otp_read_data checksum fail, checksum_cal=0x%x, checksum=0x%x\n", checksum_cal, checksum);
		return SC520CS_ST_RET_FAIL;
	}
	LOG_INF("sc520cs_sensor_otp_read_data success\n");
	return SC520CS_ST_RET_SUCCESS;
}

//read otp module_info
static int sc520cs_sensor_otp_read_module_info(void)
{
	int ret = SC520CS_ST_RET_FAIL;
	LOG_INF("sc520cs_sensor_otp_read_module_info begin!\n");
	if(read_cmos_sensor(MODULE_INFO_FLAG) == otp_group_1){
		ret = sc520cs_sensor_otp_read_data(MODULE_GROUP1_ADDR, MODULE_INFO_SIZE + 1, &sc520cs_data_info[0]);
		LOG_INF("sc520cs_sensor_otp_read_module_info group1 checksum success!\n");
	  }
	else{
		LOG_INF("sc520cs_sensor_otp_read_module_info flag failed:%d\n",read_cmos_sensor(MODULE_INFO_FLAG));
	}
	LOG_INF("sc520cs_sensor_otp_read_module_info end!\n");
	return ret;
}

//read otp sn
static int sc520cs_sensor_otp_read_sn_info(void)
{
	int ret = SC520CS_ST_RET_FAIL;
	LOG_INF("sc520cs_sensor_otp_read_sn_info begin!\n");
	if(read_cmos_sensor(SN_INFO_FLAG) == otp_group_1){
		ret = sc520cs_sensor_otp_read_data(SN_GROUP1_ADDR, SN_INFO_SIZE + 1, &sc520cs_data_sn[0]);
		LOG_INF("sc520cs_sensor_otp_read_sn_info group1 checksum success!\n");
	   }
	else{
		LOG_INF("sc520cs_sensor_otp_read_sn_info flag failed:%d\n",read_cmos_sensor(SN_INFO_FLAG));
	   }
	LOG_INF("sc520cs_sensor_otp_read_sn_info end!\n");
	return ret;
}

static int sc520cs_sensor_otp_read_awb_info(void)
{
	int ret = SC520CS_ST_RET_FAIL;
	LOG_INF("sc520cs_sensor_otp_read_awb_info begin!\n");
	if(read_cmos_sensor(AWB_INFO_FLAG) == otp_group_1){
		ret = sc520cs_sensor_otp_read_data(AWB_GROUP1_FLAG, AWB_INFO_SIZE + 1, &sc520cs_data_awb[0]);
		LOG_INF("sc520cs_sensor_otp_read_awb group1 checksum success!\n");
	   }
	else if(read_cmos_sensor(AWB_INFO_FLAG) == otp_group_2){
		ret = sc520cs_sensor_otp_read_data(AWB_GROUP2_FLAG, AWB_INFO_SIZE + 1, &sc520cs_data_awb[0]);
		LOG_INF("sc520cs_sensor_otp_read_awb group2 checksum success!\n");
	   }
	else{
		LOG_INF("sc520cs_sensor_otp_read_awb flag failed:%d\n",read_cmos_sensor(AWB_INFO_FLAG));
	   }
	LOG_INF("sc520cs_sensor_otp_read_awb_info end!\n");
	return ret;
}

static int sc520cs_sensor_otp_read_lsc_info_group1(void)
{
	int ret = SC520CS_ST_RET_FAIL;
	LOG_INF("sc520cs_sensor_otp_read_lsc_info_group1 begin!\n");
	if(read_cmos_sensor(AWB_INFO_FLAG) == otp_group_1){
		ret = sc520cs_sensor_otp_read_data(LSC_GROUP1_FLAG, LSC_INFO_SIZE + 1, &sc520cs_data_lsc[0]);
		LOG_INF("sc520cs_sensor_otp_read_lsc_info_group1 group1 checksum success!\n");
	   }
	else{
		LOG_INF("sc520cs_sensor_otp_read_awb flag failed:%d\n",read_cmos_sensor(AWB_INFO_FLAG));
	   }
	LOG_INF("sc520cs_sensor_otp_read_awb_info end!\n");
	return ret;
}

static int sc520cs_sensor_otp_read_lsc_info_group2(void)
{
	int ret = SC520CS_ST_RET_FAIL;
	unsigned int checksum_cal = 0;
	unsigned int checksum = 0;
	unsigned int addr = 0;
	unsigned int i;
	pr_info("sc520cs_sensor_otp_read_lsc_info group2 begin!\n");
	for(addr = LSC_GROUP2_FLAG, i = 0;addr <= LSC_GROUP2_PAGE2_END;addr++) //read lsc data page 2
	{
		sc520cs_data_lsc[i] = read_cmos_sensor(addr);
		checksum_cal += sc520cs_data_lsc[i];
		#if SC520CS_ST_DEBUG_ON
		LOG_INF("sc520cs_sensor_otp_read_data addr=0x%x, data=0x%x\n", addr, sc520cs_data_lsc[i]);
		#endif
		i++;
	}
	
	sc520cs_sensor_otp_init(1, tempotpthreshold);//read lsc data page 1
	for(addr = LSC_GROUP2_PAGE1_START; addr <= LSC_GROUP2_PAGE1_END; addr ++)
	{
		sc520cs_data_lsc[i] = read_cmos_sensor(addr);
		checksum_cal += sc520cs_data_lsc[i];
		#if SC520CS_ST_DEBUG_ON
		LOG_INF("sc520cs_sensor_otp_read_data addr=0x%x, data=0x%x\n", addr, sc520cs_data_lsc[i]);
		#endif
		i++;
	}
	checksum  = read_cmos_sensor(LSC_GROUP2_CHECKSUM);

	checksum_cal = checksum_cal%255 + 1;
	if(checksum_cal == checksum)
	{
		pr_info("sc520cs_sensor_otp_read_lsc_info group2 checksum pass!\n");
		ret = SC520CS_ST_RET_SUCCESS;
	}
	else
	{
		pr_info("sc520cs_sensor_otp_read_lsc_info group2 checksum fail,checksum_cal:0x%x,checksum:0x%x!\n",checksum_cal,checksum);
        ret = SC520CS_ST_RET_FAIL;
	}

	pr_info("sc520cs_sensor_otp_read_lsc_info group2 end!\n");
    return ret;
}

//read otp lsc
static int sc520cs_sensor_otp_read_lsc_info(void)
{
	int ret = SC520CS_ST_RET_FAIL;
	LOG_INF("sc520cs_sensor_otp_read_lsc_info begin!\n");
	if(read_cmos_sensor(LSC_INFO_FLAG) == otp_group_1){
		ret = sc520cs_sensor_otp_read_lsc_info_group1();
		LOG_INF("sc520cs_sensor_otp_read_lsc group1 checksum success!\n");
	   }
	else if(read_cmos_sensor(LSC_INFO_FLAG) == otp_group_2){
		ret = sc520cs_sensor_otp_read_lsc_info_group2();
		LOG_INF("sc520cs_sensor_otp_read_lsc group2 checksum success!\n");
	   }
	else{
		LOG_INF("sc520cs_sensor_otp_read_lsc flag failed:%d\n",read_cmos_sensor(LSC_INFO_FLAG));
	   }
	LOG_INF("sc520cs_sensor_otp_read_lsc_info end!\n");
	return ret;
}

static int sc520cs_sensor_otp_info(){
	int ret = 0;
	int i;
	int otpThreshold[3] = {0x38, 0x28, 0x48}; /* the Threshold for sc520cs*/

	//read module info to judge the otp data which group
    for(i = 0;i < 3;i++)
	{
		tempotpthreshold = otpThreshold[i];
		sc520cs_sensor_otp_init(2, tempotpthreshold);  /*we need reload the data page before read anther page data.*/
		ret = sc520cs_sensor_otp_read_module_info();
		if(ret == SC520CS_ST_RET_FAIL){
		LOG_INF("sc520cs read module info  failed!!!\n");
		continue;
	       }
        ret = sc520cs_sensor_otp_read_sn_info();
		if(ret == SC520CS_ST_RET_FAIL){
		LOG_INF("sc520cs read sn info  failed!!!\n");
		continue;
	       }
		ret = sc520cs_sensor_otp_read_awb_info();
		if(ret == SC520CS_ST_RET_FAIL){
		LOG_INF("sc520cs read awb info  failed!!!\n");
		continue;
	       }
		ret = sc520cs_sensor_otp_read_lsc_info();
		if(ret == SC520CS_ST_RET_FAIL){
		LOG_INF("sc520cs read lsc info  failed!!!\n");
		continue;
	    } else {
		LOG_INF("sc520cs read lsc info  success!!!\n");
		break;
		}
	}
	if(ret == SC520CS_ST_RET_FAIL)
	{
		pr_info("sc520cs read lsc info in treshold R1 R2 R3 all failed!!!\n");
		return ret;
	}
	pr_info("read sc520cs otp data success\n");
    return ret;
}


static kal_uint32 get_imgsensor_id(UINT32 *sensor_id)
{
	kal_uint8 i = 0;
	kal_uint8 retry = 2;
#if SC520CS_OTP_FUNCTION
    kal_uint8 ret = 0;
#endif
	LOG_INF("[get_imgsensor_id] ");
	while (imgsensor_info.i2c_addr_table[i] != 0xff) {
			spin_lock(&imgsensor_drv_lock);
			imgsensor.i2c_write_id = imgsensor_info.i2c_addr_table[i];
			spin_unlock(&imgsensor_drv_lock);
			do {
				*sensor_id =return_sensor_id();
				if (*sensor_id == imgsensor_info.sensor_id) {
#if SC520CS_OTP_FUNCTION
                    //+S96818AA1-1936,zhujianjia.wt,ADD,2023/04/28,sc520cs otp porting
				ret = sc520cs_sensor_otp_info();
                if(ret != 0){
                *sensor_id = 0xFFFFFFFF;
                LOG_INF("w3sc520cswidelce read OTP failed ret:%d, \n",ret);
                return ERROR_SENSOR_CONNECT_FAIL;
                }else{
                LOG_INF("w3sc520cswidelce read OTP successed: ret: %d \n",ret);
                w3sc520cswidelce_eeprom_data.dataBuffer = kmalloc(w3sc520cswidelce_eeprom_data.dataLength, GFP_KERNEL);
                 if (w3sc520cswidelce_eeprom_data.dataBuffer == NULL) {
                     LOG_INF("w3sc520cswidelce_eeprom_data->dataBuffer is malloc fail\n");
                     return -EFAULT;
                }
                memcpy(w3sc520cswidelce_eeprom_data.dataBuffer, (u8 *)&sc520cs_data_info, MODULE_INFO_SIZE);
                memcpy(w3sc520cswidelce_eeprom_data.dataBuffer+MODULE_INFO_SIZE, (u8 *)&sc520cs_data_sn, SN_INFO_SIZE);
                memcpy(w3sc520cswidelce_eeprom_data.dataBuffer+SN_INFO_SIZE+MODULE_INFO_SIZE, (u8 *)&sc520cs_data_awb, AWB_INFO_SIZE);
                memcpy(w3sc520cswidelce_eeprom_data.dataBuffer+SN_INFO_SIZE+MODULE_INFO_SIZE+AWB_INFO_SIZE, (u8 *)&sc520cs_data_lsc, LSC_INFO_SIZE);
                imgSensorReadOTPData(&w3sc520cswidelce_eeprom_data);
             }
					//-S96818AA1-1936,zhujianjia.wt,ADD,2023/04/28,sc520cs otp porting
#endif
					LOG_INF("i2c write id  : 0x%x, sensor id: 0x%x\n", imgsensor.i2c_write_id,*sensor_id);
					//sc520cs_fusion_id_read();
					//sc520cs_sn_id_read();
                                        //get_sensor_module_info();
					return ERROR_NONE;
				}
				LOG_INF("Smartsens_SC520CS get_imgsensor_id Read sensor id fail, i2c write id: 0x%x,sensor id: 0x%x\n", imgsensor.i2c_write_id,*sensor_id);
				retry--;
			} while(retry > 0);
			i++;
			retry = 2;
	}
	if (*sensor_id != imgsensor_info.sensor_id) {
		*sensor_id = 0xFFFFFFFF;
		return ERROR_SENSOR_CONNECT_FAIL;
	}
	return ERROR_NONE;
}

/*************************************************************************
 * FUNCTION
 *	open
 *
 * DESCRIPTION
 *	This function initialize the registers of CMOS sensor
 *
 * PARAMETERS
 *	None
 *
 * RETURNS
 *	None
 *
 * GLOBALS AFFECTED
 *
 *************************************************************************/
static kal_uint32 open(void)
{
	kal_uint8 i = 0;
	kal_uint8 retry = 2;
	kal_uint16 sensor_id = 0;
	while (imgsensor_info.i2c_addr_table[i] != 0xff) {
		spin_lock(&imgsensor_drv_lock);
		imgsensor.i2c_write_id = imgsensor_info.i2c_addr_table[i];
		spin_unlock(&imgsensor_drv_lock);
		do {
			sensor_id = return_sensor_id();
			if (sensor_id == imgsensor_info.sensor_id) {
				LOG_INF("i2c write id: 0x%x, sensor id: 0x%x\n",
					imgsensor.i2c_write_id, sensor_id);
				break;
			}

			retry--;
		} while (retry > 0);
		i++;
		if (sensor_id == imgsensor_info.sensor_id)
			break;
		retry = 2;
	}
	if (imgsensor_info.sensor_id != sensor_id) {
		LOG_INF("open sensor id fail: 0x%x\n", sensor_id);

		return ERROR_SENSOR_CONNECT_FAIL;
	}
	/* initail sequence write in  */
	sensor_init();

	spin_lock(&imgsensor_drv_lock);
	imgsensor.autoflicker_en = KAL_FALSE;
	imgsensor.sensor_mode = IMGSENSOR_MODE_INIT;
	imgsensor.pclk = imgsensor_info.pre.pclk;
	imgsensor.frame_length = imgsensor_info.pre.framelength;
	imgsensor.line_length = imgsensor_info.pre.linelength;
	imgsensor.min_frame_length = imgsensor_info.pre.framelength;
	imgsensor.dummy_pixel = 0;
	imgsensor.dummy_line = 0;
	imgsensor.ihdr_en = 0;
	imgsensor.test_pattern = KAL_FALSE;
	imgsensor.current_fps = imgsensor_info.pre.max_framerate;
	spin_unlock(&imgsensor_drv_lock);
	return ERROR_NONE;
}	/*	open  */
static kal_uint32 close(void)
{
	return ERROR_NONE;
}	/*	close  */


/*************************************************************************
 * FUNCTION
 * preview
 *
 * DESCRIPTION
 *	This function start the sensor preview.
 *
 * PARAMETERS
 *	*image_window : address pointer of pixel numbers in one period of HSYNC
 *  *sensor_config_data : address pointer of line numbers in one period of VSYNC
 *
 * RETURNS
 *	None
 *
 * GLOBALS AFFECTED
 *
 *************************************************************************/
static kal_uint32 preview(MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *image_window,
			MSDK_SENSOR_CONFIG_STRUCT *sensor_config_data)
{
	LOG_INF("E");
	spin_lock(&imgsensor_drv_lock);
	imgsensor.sensor_mode = IMGSENSOR_MODE_PREVIEW;
	imgsensor.pclk = imgsensor_info.pre.pclk;
	imgsensor.line_length = imgsensor_info.pre.linelength;
	imgsensor.frame_length = imgsensor_info.pre.framelength;
	imgsensor.min_frame_length = imgsensor_info.pre.framelength;
	imgsensor.current_fps = imgsensor_info.pre.max_framerate;
	imgsensor.autoflicker_en = KAL_FALSE;
	spin_unlock(&imgsensor_drv_lock);
	preview_setting();
	return ERROR_NONE;
}	/*	preview   */

/*************************************************************************
 * FUNCTION
 *	capture
 *
 * DESCRIPTION
 *	This function setup the CMOS sensor in capture MY_OUTPUT mode
 *
 * PARAMETERS
 *
 * RETURNS
 *	None
 *
 * GLOBALS AFFECTED
 *
 *************************************************************************/
static kal_uint32 capture(MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *image_window,
			MSDK_SENSOR_CONFIG_STRUCT *sensor_config_data)
{
	spin_lock(&imgsensor_drv_lock);
	imgsensor.sensor_mode = IMGSENSOR_MODE_CAPTURE;

	if (imgsensor.current_fps == imgsensor_info.cap.max_framerate)	{
		imgsensor.pclk = imgsensor_info.cap.pclk;
		imgsensor.line_length = imgsensor_info.cap.linelength;
		imgsensor.frame_length = imgsensor_info.cap.framelength;
		imgsensor.min_frame_length = imgsensor_info.cap.framelength;
		imgsensor.autoflicker_en = KAL_FALSE;
	} else {
	 //PIP capture: 24fps for less than 13M, 20fps for 16M,15fps for 20M

		imgsensor.pclk = imgsensor_info.cap.pclk;
		imgsensor.line_length = imgsensor_info.cap.linelength;
		imgsensor.frame_length = imgsensor_info.cap.framelength;
		imgsensor.min_frame_length = imgsensor_info.cap.framelength;
		imgsensor.autoflicker_en = KAL_FALSE;
	}

	spin_unlock(&imgsensor_drv_lock);
	LOG_INF("Caputre fps:%d,img_fl:%d\n", imgsensor.current_fps, imgsensor.frame_length);
	capture_setting(imgsensor.current_fps);

	return ERROR_NONE;

}	/* capture() */
static kal_uint32 normal_video(MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *image_window,
			  MSDK_SENSOR_CONFIG_STRUCT *sensor_config_data)
{
	spin_lock(&imgsensor_drv_lock);
	imgsensor.sensor_mode = IMGSENSOR_MODE_VIDEO;
	imgsensor.pclk = imgsensor_info.normal_video.pclk;
	imgsensor.line_length = imgsensor_info.normal_video.linelength;
	imgsensor.frame_length = imgsensor_info.normal_video.framelength;
	imgsensor.min_frame_length = imgsensor_info.normal_video.framelength;
	imgsensor.current_fps = 300;
	imgsensor.autoflicker_en = KAL_FALSE;
	spin_unlock(&imgsensor_drv_lock);
	normal_video_setting();
	return ERROR_NONE;
}	/*	normal_video   */

static kal_uint32 hs_video(MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *image_window,
			MSDK_SENSOR_CONFIG_STRUCT *sensor_config_data)
{
	spin_lock(&imgsensor_drv_lock);
	imgsensor.sensor_mode = IMGSENSOR_MODE_HIGH_SPEED_VIDEO;
	imgsensor.pclk = imgsensor_info.hs_video.pclk;
	//imgsensor.video_mode = KAL_TRUE;
	imgsensor.line_length = imgsensor_info.hs_video.linelength;
	imgsensor.frame_length = imgsensor_info.hs_video.framelength;
	imgsensor.min_frame_length = imgsensor_info.hs_video.framelength;
	imgsensor.dummy_line = 0;
	imgsensor.dummy_pixel = 0;
	imgsensor.autoflicker_en = KAL_FALSE;
	spin_unlock(&imgsensor_drv_lock);
	hs_video_setting();
	return ERROR_NONE;
}    /*    hs_video   */

static kal_uint32 slim_video(MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *image_window,
		      MSDK_SENSOR_CONFIG_STRUCT *sensor_config_data)
{
	spin_lock(&imgsensor_drv_lock);
	imgsensor.sensor_mode = IMGSENSOR_MODE_SLIM_VIDEO;
	imgsensor.pclk = imgsensor_info.slim_video.pclk;
	imgsensor.line_length = imgsensor_info.slim_video.linelength;
	imgsensor.frame_length = imgsensor_info.slim_video.framelength;
	imgsensor.min_frame_length = imgsensor_info.slim_video.framelength;
	imgsensor.dummy_line = 0;
	imgsensor.dummy_pixel = 0;
	imgsensor.autoflicker_en = KAL_FALSE;
	spin_unlock(&imgsensor_drv_lock);
	slim_video_setting();

	return ERROR_NONE;
}    /*    slim_video     */

static kal_uint32 custom1(MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *image_window,
		      MSDK_SENSOR_CONFIG_STRUCT *sensor_config_data)
{
	spin_lock(&imgsensor_drv_lock);
	imgsensor.sensor_mode = IMGSENSOR_MODE_CUSTOM1;
	imgsensor.pclk = imgsensor_info.custom1.pclk;
	imgsensor.line_length = imgsensor_info.custom1.linelength;
	imgsensor.frame_length = imgsensor_info.custom1.framelength;
	imgsensor.min_frame_length = imgsensor_info.custom1.framelength;
	imgsensor.dummy_line = 0;
	imgsensor.dummy_pixel = 0;
	imgsensor.autoflicker_en = KAL_FALSE;
	spin_unlock(&imgsensor_drv_lock);
	custom1_setting();

	return ERROR_NONE;
}    /*    custom1     */

static kal_uint32 get_resolution(
		MSDK_SENSOR_RESOLUTION_INFO_STRUCT * sensor_resolution)
{
	sensor_resolution->SensorFullWidth =
		imgsensor_info.cap.grabwindow_width;
	sensor_resolution->SensorFullHeight =
		imgsensor_info.cap.grabwindow_height;

	sensor_resolution->SensorPreviewWidth =
		imgsensor_info.pre.grabwindow_width;
	sensor_resolution->SensorPreviewHeight =
		imgsensor_info.pre.grabwindow_height;

	sensor_resolution->SensorVideoWidth =
		imgsensor_info.normal_video.grabwindow_width;
	sensor_resolution->SensorVideoHeight =
		imgsensor_info.normal_video.grabwindow_height;


	sensor_resolution->SensorHighSpeedVideoWidth =
		imgsensor_info.hs_video.grabwindow_width;
	sensor_resolution->SensorHighSpeedVideoHeight =
		imgsensor_info.hs_video.grabwindow_height;

	sensor_resolution->SensorSlimVideoWidth =
		imgsensor_info.slim_video.grabwindow_width;
	sensor_resolution->SensorSlimVideoHeight =
		imgsensor_info.slim_video.grabwindow_height;
		
		sensor_resolution->SensorCustom1Width = 
		imgsensor_info.custom1.grabwindow_width;
	sensor_resolution->SensorCustom1Height = 
		imgsensor_info.custom1.grabwindow_height;	
		
	return ERROR_NONE;
}    /*    get_resolution    */


static kal_uint32 get_info(enum MSDK_SCENARIO_ID_ENUM scenario_id,
			MSDK_SENSOR_INFO_STRUCT *sensor_info,
			MSDK_SENSOR_CONFIG_STRUCT *sensor_config_data)
{
	LOG_INF("scenario_id = %d\n", scenario_id);

	sensor_info->SensorClockPolarity = SENSOR_CLOCK_POLARITY_LOW;
	sensor_info->SensorClockFallingPolarity = SENSOR_CLOCK_POLARITY_LOW;
	sensor_info->SensorHsyncPolarity = SENSOR_CLOCK_POLARITY_LOW;
	sensor_info->SensorVsyncPolarity = SENSOR_CLOCK_POLARITY_LOW;
	sensor_info->SensorInterruptDelayLines = 4; /* not use */
	sensor_info->SensorResetActiveHigh = FALSE; /* not use */
	sensor_info->SensorResetDelayCount = 5; /* not use */

	sensor_info->SensroInterfaceType =
	imgsensor_info.sensor_interface_type;
	sensor_info->MIPIsensorType = imgsensor_info.mipi_sensor_type;
	sensor_info->SettleDelayMode = imgsensor_info.mipi_settle_delay_mode;
	sensor_info->SensorOutputDataFormat =
		imgsensor_info.sensor_output_dataformat;

	sensor_info->CaptureDelayFrame = imgsensor_info.cap_delay_frame;
	sensor_info->PreviewDelayFrame = imgsensor_info.pre_delay_frame;
	sensor_info->VideoDelayFrame =
		imgsensor_info.video_delay_frame;
	sensor_info->HighSpeedVideoDelayFrame =
		imgsensor_info.hs_video_delay_frame;
	sensor_info->SlimVideoDelayFrame =
		imgsensor_info.slim_video_delay_frame;
	sensor_info->Custom1DelayFrame = imgsensor_info.custom1_delay_frame;

	sensor_info->SensorMasterClockSwitch = 0; /* not use */
	sensor_info->SensorDrivingCurrent =
		imgsensor_info.isp_driving_current;
/* The frame of setting shutter default 0 for TG int */
	sensor_info->AEShutDelayFrame =
		imgsensor_info.ae_shut_delay_frame;
/* The frame of setting sensor gain */
	sensor_info->AESensorGainDelayFrame =
		imgsensor_info.ae_sensor_gain_delay_frame;
	sensor_info->AEISPGainDelayFrame =
		imgsensor_info.ae_ispGain_delay_frame;
	sensor_info->IHDR_Support = imgsensor_info.ihdr_support;
	sensor_info->IHDR_LE_FirstLine =
		imgsensor_info.ihdr_le_firstline;
	sensor_info->SensorModeNum =
		imgsensor_info.sensor_mode_num;

	sensor_info->SensorMIPILaneNumber =
		imgsensor_info.mipi_lane_num;
	sensor_info->SensorClockFreq = imgsensor_info.mclk;
	sensor_info->SensorClockDividCount = 3; /* not use */
	sensor_info->SensorClockRisingCount = 0;
	sensor_info->SensorClockFallingCount = 2; /* not use */
	sensor_info->SensorPixelClockCount = 3; /* not use */
	sensor_info->SensorDataLatchCount = 2; /* not use */

	sensor_info->MIPIDataLowPwr2HighSpeedTermDelayCount = 0;
	sensor_info->MIPICLKLowPwr2HighSpeedTermDelayCount = 0;
	sensor_info->SensorWidthSampling = 0;  // 0 is default 1x
	sensor_info->SensorHightSampling = 0;    // 0 is default 1x
	sensor_info->SensorPacketECCOrder = 1;

	switch (scenario_id) {
	case MSDK_SCENARIO_ID_CAMERA_PREVIEW:
	    sensor_info->SensorGrabStartX = imgsensor_info.pre.startx;
	    sensor_info->SensorGrabStartY = imgsensor_info.pre.starty;

	    sensor_info->MIPIDataLowPwr2HighSpeedSettleDelayCount =
				imgsensor_info.pre.mipi_data_lp2hs_settle_dc;
	break;
	case MSDK_SCENARIO_ID_CAMERA_CAPTURE_JPEG:
	    sensor_info->SensorGrabStartX = imgsensor_info.cap.startx;
	    sensor_info->SensorGrabStartY = imgsensor_info.cap.starty;

	    sensor_info->MIPIDataLowPwr2HighSpeedSettleDelayCount =
			imgsensor_info.cap.mipi_data_lp2hs_settle_dc;
	break;
	case MSDK_SCENARIO_ID_VIDEO_PREVIEW:
	    sensor_info->SensorGrabStartX = imgsensor_info.normal_video.startx;
	    sensor_info->SensorGrabStartY = imgsensor_info.normal_video.starty;

	    sensor_info->MIPIDataLowPwr2HighSpeedSettleDelayCount =
			imgsensor_info.normal_video.mipi_data_lp2hs_settle_dc;
	break;
	case MSDK_SCENARIO_ID_HIGH_SPEED_VIDEO:
	    sensor_info->SensorGrabStartX = imgsensor_info.hs_video.startx;
	    sensor_info->SensorGrabStartY = imgsensor_info.hs_video.starty;
	    sensor_info->MIPIDataLowPwr2HighSpeedSettleDelayCount =
			imgsensor_info.hs_video.mipi_data_lp2hs_settle_dc;
	break;
	case MSDK_SCENARIO_ID_SLIM_VIDEO:
	    sensor_info->SensorGrabStartX = imgsensor_info.slim_video.startx;
	    sensor_info->SensorGrabStartY = imgsensor_info.slim_video.starty;
	    sensor_info->MIPIDataLowPwr2HighSpeedSettleDelayCount =
			imgsensor_info.slim_video.mipi_data_lp2hs_settle_dc;
	break;
	case MSDK_SCENARIO_ID_CUSTOM1:
		sensor_info->SensorGrabStartX = imgsensor_info.custom1.startx;
		sensor_info->SensorGrabStartY = imgsensor_info.custom1.starty;
		sensor_info->MIPIDataLowPwr2HighSpeedSettleDelayCount =
			imgsensor_info.custom1.mipi_data_lp2hs_settle_dc;
	break;
	default:
	    sensor_info->SensorGrabStartX = imgsensor_info.pre.startx;
	    sensor_info->SensorGrabStartY = imgsensor_info.pre.starty;

	    sensor_info->MIPIDataLowPwr2HighSpeedSettleDelayCount =
			imgsensor_info.pre.mipi_data_lp2hs_settle_dc;
	break;
	}

	return ERROR_NONE;
}    /*    get_info  */


static kal_uint32 control(enum MSDK_SCENARIO_ID_ENUM scenario_id,
			MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *image_window,
			MSDK_SENSOR_CONFIG_STRUCT *sensor_config_data)
{
	LOG_INF("scenario_id = %d\n", scenario_id);
	spin_lock(&imgsensor_drv_lock);
	imgsensor.current_scenario_id = scenario_id;
	spin_unlock(&imgsensor_drv_lock);
	switch (scenario_id) {
	case MSDK_SCENARIO_ID_CAMERA_PREVIEW:
		preview(image_window, sensor_config_data);
		break;
	case MSDK_SCENARIO_ID_CAMERA_CAPTURE_JPEG:
	case MSDK_SCENARIO_ID_CAMERA_ZSD:
		capture(image_window, sensor_config_data);
		break;
	case MSDK_SCENARIO_ID_VIDEO_PREVIEW:
		normal_video(image_window, sensor_config_data);
		break;
	case MSDK_SCENARIO_ID_HIGH_SPEED_VIDEO:
	hs_video(image_window, sensor_config_data);
		break;
	case MSDK_SCENARIO_ID_SLIM_VIDEO:
	    slim_video(image_window, sensor_config_data);
		break;
	case MSDK_SCENARIO_ID_CUSTOM1:
		custom1(image_window, sensor_config_data);
	    break;	
	default:
		preview(image_window, sensor_config_data);
		return ERROR_INVALID_SCENARIO_ID;
	}
	return ERROR_NONE;
}	/* control() */



static kal_uint32 set_video_mode(UINT16 framerate)
{
	LOG_INF("framerate = %d ", framerate);
	// SetVideoMode Function should fix framerate
	if (framerate == 0)
		// Dynamic frame rate
		return ERROR_NONE;
	spin_lock(&imgsensor_drv_lock);

	if ((framerate == 30) && (imgsensor.autoflicker_en == KAL_TRUE))
		imgsensor.current_fps = 296;
	else if ((framerate == 15) && (imgsensor.autoflicker_en == KAL_TRUE))
		imgsensor.current_fps = 146;
	else
		imgsensor.current_fps = 10 * framerate;
	spin_unlock(&imgsensor_drv_lock);
	set_max_framerate(imgsensor.current_fps, 1);
	set_dummy();
	return ERROR_NONE;
}


static kal_uint32 set_auto_flicker_mode(kal_bool enable,
			UINT16 framerate)
{
	LOG_INF("enable = %d, framerate = %d ", enable, framerate);
	spin_lock(&imgsensor_drv_lock);
	if (enable)
		imgsensor.autoflicker_en = KAL_FALSE;
	else //Cancel Auto flick
		imgsensor.autoflicker_en = KAL_FALSE;
	spin_unlock(&imgsensor_drv_lock);
	return ERROR_NONE;
}


static kal_uint32 set_max_framerate_by_scenario(
			enum MSDK_SCENARIO_ID_ENUM scenario_id,
			MUINT32 framerate)
{
	kal_uint32 frame_length;

	LOG_INF("scenario_id = %d, framerate = %d\n",scenario_id, framerate);

	switch (scenario_id) {
	case MSDK_SCENARIO_ID_CAMERA_PREVIEW:
	    frame_length = imgsensor_info.pre.pclk / framerate * 10 /
			imgsensor_info.pre.linelength;
	    spin_lock(&imgsensor_drv_lock);
	    imgsensor.dummy_line = (frame_length >
			imgsensor_info.pre.framelength) ?
			(frame_length - imgsensor_info.pre.framelength) : 0;
			imgsensor.frame_length = imgsensor_info.pre.framelength + imgsensor.dummy_line;
	    imgsensor.min_frame_length = imgsensor.frame_length;
	    spin_unlock(&imgsensor_drv_lock);
		if (imgsensor.frame_length > imgsensor.shutter)
			set_dummy();
	break;
	case MSDK_SCENARIO_ID_VIDEO_PREVIEW:
		if (framerate == 0)
			return ERROR_NONE;
	    frame_length = imgsensor_info.normal_video.pclk /
			framerate * 10 / imgsensor_info.normal_video.linelength;
	    spin_lock(&imgsensor_drv_lock);
	    imgsensor.dummy_line = (frame_length >
			imgsensor_info.normal_video.framelength) ?
		(frame_length - imgsensor_info.normal_video.framelength) : 0;
	    imgsensor.frame_length = imgsensor_info.normal_video.framelength +
			imgsensor.dummy_line;
	    imgsensor.min_frame_length = imgsensor.frame_length;
	    spin_unlock(&imgsensor_drv_lock);
		if (imgsensor.frame_length > imgsensor.shutter)
			set_dummy();
	break;
	case MSDK_SCENARIO_ID_CAMERA_CAPTURE_JPEG:
		if (imgsensor.current_fps ==
				imgsensor_info.cap.max_framerate) {
		frame_length = imgsensor_info.cap.pclk / framerate * 10 /
				imgsensor_info.cap.linelength;
		spin_lock(&imgsensor_drv_lock);
		imgsensor.dummy_line = (frame_length >
			imgsensor_info.cap.framelength) ?
			(frame_length - imgsensor_info.cap.framelength) : 0;
		imgsensor.frame_length = imgsensor_info.cap.framelength +
				imgsensor.dummy_line;
		imgsensor.min_frame_length = imgsensor.frame_length;
		spin_unlock(&imgsensor_drv_lock);
		} else {
			if (imgsensor.current_fps !=
				imgsensor_info.cap.max_framerate)
			LOG_INF("fps %d fps not support,use cap: %d fps!\n",
			framerate, imgsensor_info.cap.max_framerate/10);
			frame_length = imgsensor_info.cap.pclk /
				framerate * 10 / imgsensor_info.cap.linelength;
			spin_lock(&imgsensor_drv_lock);
			imgsensor.dummy_line = (frame_length >
				imgsensor_info.cap.framelength) ?
			(frame_length - imgsensor_info.cap.framelength) : 0;
			imgsensor.frame_length =
				imgsensor_info.cap.framelength +
				imgsensor.dummy_line;
			imgsensor.min_frame_length = imgsensor.frame_length;
			spin_unlock(&imgsensor_drv_lock);
		}
		if (imgsensor.frame_length > imgsensor.shutter)
			set_dummy();
	break;
	case MSDK_SCENARIO_ID_HIGH_SPEED_VIDEO:
	    frame_length = imgsensor_info.hs_video.pclk /
			framerate * 10 / imgsensor_info.hs_video.linelength;
	    spin_lock(&imgsensor_drv_lock);
	    imgsensor.dummy_line = (frame_length >
			imgsensor_info.hs_video.framelength) ? (frame_length -
			imgsensor_info.hs_video.framelength) : 0;
	    imgsensor.frame_length = imgsensor_info.hs_video.framelength +
			imgsensor.dummy_line;
	    imgsensor.min_frame_length = imgsensor.frame_length;
	    spin_unlock(&imgsensor_drv_lock);
		if (imgsensor.frame_length > imgsensor.shutter)
			set_dummy();
	break;
	case MSDK_SCENARIO_ID_SLIM_VIDEO:
	    frame_length = imgsensor_info.slim_video.pclk /
			framerate * 10 / imgsensor_info.slim_video.linelength;
	    spin_lock(&imgsensor_drv_lock);
	    imgsensor.dummy_line = (frame_length >
			imgsensor_info.slim_video.framelength) ? (frame_length -
			imgsensor_info.slim_video.framelength) : 0;
	    imgsensor.frame_length =
			imgsensor_info.slim_video.framelength +
			imgsensor.dummy_line;
	    imgsensor.min_frame_length = imgsensor.frame_length;
	    spin_unlock(&imgsensor_drv_lock);
		if (imgsensor.frame_length > imgsensor.shutter)
			set_dummy();
	break;
	case MSDK_SCENARIO_ID_CUSTOM1:
		 frame_length = imgsensor_info.custom1.pclk /
			framerate * 10 / imgsensor_info.custom1.linelength;
	    spin_lock(&imgsensor_drv_lock);
	    imgsensor.dummy_line = (frame_length >
			imgsensor_info.custom1.framelength) ? (frame_length -
			imgsensor_info.custom1.framelength) : 0;
	    imgsensor.frame_length =
			imgsensor_info.custom1.framelength +
			imgsensor.dummy_line;
	    imgsensor.min_frame_length = imgsensor.frame_length;
	    spin_unlock(&imgsensor_drv_lock);
		if (imgsensor.frame_length > imgsensor.shutter)
			set_dummy();
	break;
	default:  //coding with  preview scenario by default
	    frame_length = imgsensor_info.pre.pclk / framerate * 10 /
						imgsensor_info.pre.linelength;
	    spin_lock(&imgsensor_drv_lock);
	    imgsensor.dummy_line = (frame_length >
			imgsensor_info.pre.framelength) ?
			(frame_length - imgsensor_info.pre.framelength) : 0;
	    imgsensor.frame_length = imgsensor_info.pre.framelength +
				imgsensor.dummy_line;
	    imgsensor.min_frame_length = imgsensor.frame_length;
	    spin_unlock(&imgsensor_drv_lock);
		if (imgsensor.frame_length > imgsensor.shutter)
			set_dummy();
	    LOG_INF("error scenario_id = %d, we use preview scenario\n",
				scenario_id);
	break;
	}

	LOG_INF("scenario_id = %d, frame_length = %d\n",scenario_id,imgsensor.frame_length);
	return ERROR_NONE;
}


static kal_uint32 get_default_framerate_by_scenario(
				enum MSDK_SCENARIO_ID_ENUM scenario_id,
				MUINT32 *framerate)
{
	LOG_INF("scenario_id = %d\n", scenario_id);

	switch (scenario_id) {
	case MSDK_SCENARIO_ID_CAMERA_PREVIEW:
	    *framerate = imgsensor_info.pre.max_framerate;
	break;
	case MSDK_SCENARIO_ID_VIDEO_PREVIEW:
	    *framerate = imgsensor_info.normal_video.max_framerate;
	break;
	case MSDK_SCENARIO_ID_CAMERA_CAPTURE_JPEG:
	    *framerate = imgsensor_info.cap.max_framerate;
	break;
	case MSDK_SCENARIO_ID_HIGH_SPEED_VIDEO:
	    *framerate = imgsensor_info.hs_video.max_framerate;
	break;
	case MSDK_SCENARIO_ID_SLIM_VIDEO:
	    *framerate = imgsensor_info.slim_video.max_framerate;
	break;
	case MSDK_SCENARIO_ID_CUSTOM1:
		*framerate = imgsensor_info.custom1.max_framerate;
	break;
	default:
	break;
	}

	return ERROR_NONE;
}

static kal_uint32 set_test_pattern_mode(kal_bool enable)
{
	LOG_INF("set_test_pattern_mode enable: %d", enable);

	if (enable) {
		write_cmos_sensor8(0x3337,0x30);
		write_cmos_sensor8(0x5000,0x00);
		write_cmos_sensor8(0x391d,0x10);
		write_cmos_sensor8(0x3e06,0x00);
		write_cmos_sensor8(0x3e07,0x80);
		write_cmos_sensor8(0x3e09,0x00);
	
	} else {
		write_cmos_sensor8(0x3337,0x00);
		write_cmos_sensor8(0x5000,0x0e);
		write_cmos_sensor8(0x391d,0x04);

	}
	spin_lock(&imgsensor_drv_lock);
	imgsensor.test_pattern = enable;
	spin_unlock(&imgsensor_drv_lock);
	return ERROR_NONE;
}

static kal_uint32 streaming_control(kal_bool enable)
{
	LOG_INF("streaming_enable(0=Sw Standby,1=streaming): %d\n", enable);

	if (enable) {
		write_cmos_sensor8(0x0100, 0x01); // stream on
	} else {
		write_cmos_sensor8(0x0100, 0x00); // stream off
		mdelay(10);
	}

	return ERROR_NONE;
}


static kal_uint32 feature_control(
			MSDK_SENSOR_FEATURE_ENUM feature_id,
			UINT8 *feature_para, UINT32 *feature_para_len)
{
	UINT16 *feature_return_para_16 = (UINT16 *) feature_para;
	UINT16 *feature_data_16 = (UINT16 *) feature_para;
	UINT32 *feature_return_para_32 = (UINT32 *) feature_para;
	UINT32 *feature_data_32 = (UINT32 *) feature_para;
	INT32 *feature_return_para_i32 = (INT32 *) feature_para;
	unsigned long long *feature_data =
		(unsigned long long *) feature_para;

	struct SENSOR_WINSIZE_INFO_STRUCT *wininfo;
	MSDK_SENSOR_REG_INFO_STRUCT *sensor_reg_data =
		(MSDK_SENSOR_REG_INFO_STRUCT *) feature_para;

	LOG_INF("feature_id = %d\n", feature_id);
	switch (feature_id) {
	case SENSOR_FEATURE_GET_PERIOD:
	    *feature_return_para_16++ = imgsensor.line_length;
	    *feature_return_para_16 = imgsensor.frame_length;
	    *feature_para_len = 4;
	break;
	case SENSOR_FEATURE_GET_PIXEL_CLOCK_FREQ:
	    *feature_return_para_32 = imgsensor.pclk;
	    *feature_para_len = 4;
	break;
	case SENSOR_FEATURE_GET_GAIN_RANGE_BY_SCENARIO:
		*(feature_data + 1) = imgsensor_info.min_gain;
		*(feature_data + 2) = imgsensor_info.max_gain;
		break;
	case SENSOR_FEATURE_GET_BASE_GAIN_ISO_AND_STEP:
		*(feature_data + 0) = imgsensor_info.min_gain_iso;
		*(feature_data + 1) = imgsensor_info.gain_step;
		*(feature_data + 2) = imgsensor_info.gain_type;
		break;
	case SENSOR_FEATURE_GET_MIN_SHUTTER_BY_SCENARIO:
		*(feature_data + 1) = imgsensor_info.min_shutter;
		*(feature_data + 2) = imgsensor_info.exp_step;
		break;
	case SENSOR_FEATURE_GET_BINNING_TYPE:
		switch (*(feature_data + 1)) {
		case MSDK_SCENARIO_ID_CAMERA_CAPTURE_JPEG:
			*feature_return_para_32 = 1; /*BINNING_NONE*/
			break;
		case MSDK_SCENARIO_ID_CAMERA_PREVIEW:
		case MSDK_SCENARIO_ID_VIDEO_PREVIEW:
			if (*(feature_data + 2))/* HDR on */
				*feature_return_para_32 = 1;/*BINNING_NONE*/
			else
				*feature_return_para_32 = 1;/*BINNING_AVERAGED*/
			break;
		case MSDK_SCENARIO_ID_HIGH_SPEED_VIDEO:
		case MSDK_SCENARIO_ID_SLIM_VIDEO:
		default:
			*feature_return_para_32 = 1; /*BINNING_AVERAGED*/
			break;
		}
		LOG_INF("SENSOR_FEATURE_GET_BINNING_TYPE AE_binning_type:%d\n",
			*feature_return_para_32);

		*feature_para_len = 4;
		break;
	case SENSOR_FEATURE_GET_FRAME_CTRL_INFO_BY_SCENARIO:
		/*
		* 1, if driver support new sw frame sync
		* set_shutter_frame_length() support third para auto_extend_en
		*/
		*(feature_data + 1) = 1;
		/* margin info by scenario */
		*(feature_data + 2) = imgsensor_info.margin;
		break;
	case SENSOR_FEATURE_SET_ESHUTTER:
	    set_shutter(*feature_data);
	break;

	case SENSOR_FEATURE_SET_SHUTTER_FRAME_TIME:
		LOG_INF("set FRAME_length shutter:%d framelength:%d,auto_en:%d \n",
			(UINT16)(*feature_data),(UINT16)(*(feature_data + 1)), (UINT16)(*(feature_data + 2)) );
		set_shutter_frame_length((UINT16) (*feature_data),
			(UINT16) (*(feature_data + 1)),(UINT16) (*(feature_data + 2)));

	case SENSOR_FEATURE_SET_NIGHTMODE:
	    /*night_mode((BOOL) * feature_data);*/
	break;
	case SENSOR_FEATURE_SET_GAIN:
	    set_gain((UINT16) *feature_data);
	break;
	case SENSOR_FEATURE_SET_FLASHLIGHT:
	break;
	case SENSOR_FEATURE_SET_ISP_MASTER_CLOCK_FREQ:
	break;
	case SENSOR_FEATURE_SET_REGISTER:
	    write_cmos_sensor(sensor_reg_data->RegAddr,
						sensor_reg_data->RegData);
	break;
	case SENSOR_FEATURE_GET_REGISTER:
	    sensor_reg_data->RegData =
				read_cmos_sensor(sensor_reg_data->RegAddr);
	break;
	case SENSOR_FEATURE_GET_LENS_DRIVER_ID:
	    *feature_return_para_32 = LENS_DRIVER_ID_DO_NOT_CARE;
	    *feature_para_len = 4;
	break;
	case SENSOR_FEATURE_SET_VIDEO_MODE:
	    set_video_mode(*feature_data);
	break;
	case SENSOR_FEATURE_CHECK_SENSOR_ID:
	    get_imgsensor_id(feature_return_para_32);
	break;
	case SENSOR_FEATURE_SET_AUTO_FLICKER_MODE:
	    set_auto_flicker_mode((BOOL)*feature_data_16,
			*(feature_data_16+1));
	break;
	case SENSOR_FEATURE_SET_MAX_FRAME_RATE_BY_SCENARIO:
	    set_max_framerate_by_scenario(
			(enum MSDK_SCENARIO_ID_ENUM)*feature_data,
			*(feature_data+1));
	break;
	case SENSOR_FEATURE_GET_DEFAULT_FRAME_RATE_BY_SCENARIO:
	    get_default_framerate_by_scenario(
			(enum MSDK_SCENARIO_ID_ENUM)*(feature_data),
			(MUINT32 *)(uintptr_t)(*(feature_data+1)));
	break;
	case SENSOR_FEATURE_SET_TEST_PATTERN:
	    set_test_pattern_mode((BOOL)*feature_data);
	break;
	case SENSOR_FEATURE_GET_TEST_PATTERN_CHECKSUM_VALUE:
	    *feature_return_para_32 = imgsensor_info.checksum_value;
	    *feature_para_len = 4;
	break;
	case SENSOR_FEATURE_SET_FRAMERATE:
	    LOG_INF("current fps :%d\n", (UINT32)*feature_data);
	    spin_lock(&imgsensor_drv_lock);
	    imgsensor.current_fps = *feature_data;
	    spin_unlock(&imgsensor_drv_lock);
	break;

	case SENSOR_FEATURE_SET_HDR:
	    LOG_INF("ihdr enable :%d\n", (BOOL)*feature_data);
	    spin_lock(&imgsensor_drv_lock);
	    imgsensor.ihdr_en = (BOOL)*feature_data;
	    spin_unlock(&imgsensor_drv_lock);
	break;
	case SENSOR_FEATURE_GET_CROP_INFO:
	    LOG_INF("SENSOR_FEATURE_GET_CROP_INFO scenarioId:%d\n",
				(UINT32)*feature_data);

	    wininfo = (struct SENSOR_WINSIZE_INFO_STRUCT *)
			(uintptr_t)(*(feature_data+1));

		switch (*feature_data_32) {
		case MSDK_SCENARIO_ID_CAMERA_CAPTURE_JPEG:
			memcpy((void *)wininfo,
				(void *)&imgsensor_winsize_info[1],
				sizeof(struct SENSOR_WINSIZE_INFO_STRUCT));
		break;
		case MSDK_SCENARIO_ID_VIDEO_PREVIEW:
			memcpy((void *)wininfo,
				(void *)&imgsensor_winsize_info[2],
				sizeof(struct SENSOR_WINSIZE_INFO_STRUCT));
		break;
		case MSDK_SCENARIO_ID_HIGH_SPEED_VIDEO:
			memcpy((void *)wininfo,
				(void *)&imgsensor_winsize_info[3],
				sizeof(struct SENSOR_WINSIZE_INFO_STRUCT));
		break;
		case MSDK_SCENARIO_ID_SLIM_VIDEO:
			memcpy((void *)wininfo,
				(void *)&imgsensor_winsize_info[4],
				sizeof(struct SENSOR_WINSIZE_INFO_STRUCT));
		break;
		case MSDK_SCENARIO_ID_CUSTOM1:
			memcpy((void *)wininfo, 
			(void *)&imgsensor_winsize_info[5], 
			sizeof(struct SENSOR_WINSIZE_INFO_STRUCT));
		break;
		case MSDK_SCENARIO_ID_CAMERA_PREVIEW:
		default:
			memcpy((void *)wininfo,
				(void *)&imgsensor_winsize_info[0],
				sizeof(struct SENSOR_WINSIZE_INFO_STRUCT));
		break;
		}
	break;
	case SENSOR_FEATURE_SET_IHDR_SHUTTER_GAIN:
	    LOG_INF("SENSOR_SET_SENSOR_IHDR LE=%d, SE=%d, Gain=%d\n",
			(UINT16)*feature_data, (UINT16)*(feature_data+1),
			(UINT16)*(feature_data+2));
	#if 0
	    ihdr_write_shutter_gain((UINT16)*feature_data,
			(UINT16)*(feature_data+1), (UINT16)*(feature_data+2));
	#endif
	break;
	case SENSOR_FEATURE_GET_PIXEL_CLOCK_FREQ_BY_SCENARIO:
		switch (*feature_data) {
    		case MSDK_SCENARIO_ID_CAMERA_CAPTURE_JPEG:
    			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
    				= imgsensor_info.cap.pclk;
    			break;
    		case MSDK_SCENARIO_ID_VIDEO_PREVIEW:
    			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
    				= imgsensor_info.normal_video.pclk;
    			break;
    		case MSDK_SCENARIO_ID_HIGH_SPEED_VIDEO:
    			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
    				= imgsensor_info.hs_video.pclk;
    			break;
    		case MSDK_SCENARIO_ID_SLIM_VIDEO:
    			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
    				= imgsensor_info.slim_video.pclk;
    			break;
    		case MSDK_SCENARIO_ID_CUSTOM1:
    			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
    				= imgsensor_info.custom1.pclk;
    			break;
    		case MSDK_SCENARIO_ID_CUSTOM2:
    			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
    				= imgsensor_info.custom2.pclk;
    			break;
    		case MSDK_SCENARIO_ID_CUSTOM3:
    			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
    				= imgsensor_info.custom3.pclk;
    			break;
    		case MSDK_SCENARIO_ID_CAMERA_PREVIEW:
    		default:
    			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
    				= imgsensor_info.pre.pclk;
    			break;
		}
		break;
	case SENSOR_FEATURE_GET_PERIOD_BY_SCENARIO:
		switch (*feature_data) {
		case MSDK_SCENARIO_ID_CAMERA_CAPTURE_JPEG:
			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
			= (imgsensor_info.cap.framelength << 16)
				+ imgsensor_info.cap.linelength;
			break;
		case MSDK_SCENARIO_ID_VIDEO_PREVIEW:
			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
			= (imgsensor_info.normal_video.framelength << 16)
				+ imgsensor_info.normal_video.linelength;
			break;
		case MSDK_SCENARIO_ID_HIGH_SPEED_VIDEO:
			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
			= (imgsensor_info.hs_video.framelength << 16)
				+ imgsensor_info.hs_video.linelength;
			break;
		case MSDK_SCENARIO_ID_SLIM_VIDEO:
			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
			= (imgsensor_info.slim_video.framelength << 16)
				+ imgsensor_info.slim_video.linelength;
			break;
		case MSDK_SCENARIO_ID_CUSTOM1:
			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
			= (imgsensor_info.custom1.framelength << 16)
				+ imgsensor_info.custom1.linelength;
			break;
		case MSDK_SCENARIO_ID_CUSTOM2:
			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
			= (imgsensor_info.custom2.framelength << 16)
				+ imgsensor_info.custom2.linelength;
			break;
		case MSDK_SCENARIO_ID_CUSTOM3:
			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
			= (imgsensor_info.custom3.framelength << 16)
				+ imgsensor_info.custom3.linelength;
			break;
		case MSDK_SCENARIO_ID_CAMERA_PREVIEW:
		default:
			*(MUINT32 *)(uintptr_t)(*(feature_data + 1))
			= (imgsensor_info.pre.framelength << 16)
				+ imgsensor_info.pre.linelength;
			break;
		}
		break;
	case SENSOR_FEATURE_GET_MIPI_PIXEL_RATE:
	{
		kal_uint32 rate;

		switch (*feature_data) {
		case MSDK_SCENARIO_ID_CAMERA_CAPTURE_JPEG:
			rate = imgsensor_info.cap.mipi_pixel_rate;
			break;
		case MSDK_SCENARIO_ID_VIDEO_PREVIEW:
			rate = imgsensor_info.normal_video.mipi_pixel_rate;
			break;
		case MSDK_SCENARIO_ID_HIGH_SPEED_VIDEO:
			rate = imgsensor_info.hs_video.mipi_pixel_rate;
			break;
		case MSDK_SCENARIO_ID_SLIM_VIDEO:
			rate = imgsensor_info.slim_video.mipi_pixel_rate;
			break;
		case MSDK_SCENARIO_ID_CUSTOM1:
			rate = imgsensor_info.custom1.mipi_pixel_rate;
		break;	
		case MSDK_SCENARIO_ID_CAMERA_PREVIEW:
		default:
			rate = imgsensor_info.pre.mipi_pixel_rate;
			break;
		}
		LOG_INF("sc500sc SENSOR_FEATURE_GET_MIPI_PIXEL_RATE");
		*(MUINT32 *) (uintptr_t) (*(feature_data + 1)) = rate;
	}
    	break;
	case SENSOR_FEATURE_GET_TEMPERATURE_VALUE:
		*feature_return_para_i32 = 0;
		*feature_para_len = 4;
	break;
	case SENSOR_FEATURE_SET_STREAMING_SUSPEND:
		streaming_control(KAL_FALSE);
	break;
	case SENSOR_FEATURE_SET_STREAMING_RESUME:
		if (*feature_data != 0)
			set_shutter(*feature_data);
		streaming_control(KAL_TRUE);
	break;
	default:
	break;
	}

	return ERROR_NONE;
}    /*    feature_control()  */

static struct SENSOR_FUNCTION_STRUCT sensor_func = {
	open,
	get_info,
	get_resolution,
	feature_control,
	control,
	close
};

UINT32 W3SC520CSWIDELCE_MIPI_RAW_SensorInit(struct SENSOR_FUNCTION_STRUCT **pfFunc)
{
	/* To Do : Check Sensor status here */
	if (pfFunc != NULL)
		*pfFunc =  &sensor_func;
	return ERROR_NONE;
}	/*	SC520CS_MIPI_RAW_SensorInit	*/
