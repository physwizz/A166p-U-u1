#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#define HARDWARE_MAX_ITEM_LONGTH		64

enum{
	HARDWARE_LCD = 0,
	HARDWARE_TP,
	HARDWARE_FLASH,
	HARDWARE_FRONT_CAM,
	HARDWARE_BACK_CAM,
	HARDWARE_BACK_SUB_CAM,
	//+bug604664,zhouyikuan.wt,ADD,2020/12/17,add wide angle info for mmigroup apk
	HARDWARE_WIDE_ANGLE_CAM,
	HARDWARE_MACRO_CAM,//+S96818AA1-1936,lijiazhen2.wt,ADD,2024/05/06, add camera module info for factory apk
	HARDWARE_BT,
	HARDWARE_WIFI,
	HARDWARE_ACCELEROMETER,
	HARDWARE_ALSPS,
	HARDWARE_GYROSCOPE,
	HARDWARE_MAGNETOMETER,
	HARDWARE_SAR,//bug 417945 , add sar info, chenrongli.wt, 20181218
	HARDWARE_GPS,
	HARDWARE_FM,
        HARDWARE_NFC,//bug 604665,lulinliang.wt,2020.12.18,add nfc info
	HARDWARE_SMARTPA,//S98901AA1-827, zhouweijie.wt, add, 2024/04/15, sia81xx bring up
	HARDWARE_BATTERY_ID,
	HARDWARE_CHARGER_IC_INFO,  //bug 436809  modify getian.wt 20190403 Add charger IC model information in factory mode
	HARDWARE_PD_CHARGER,
	HARDWARE_CHARGER_PUMP,
	HARDWARE_BACK_CAM_MOUDULE_ID,
	HARDWARE_BACK_SUBCAM_MOUDULE_ID,
	HARDWARE_FRONT_CAM_MOUDULE_ID,
	//+bug604664,zhouyikuan.wt,ADD,2020/12/17,add wide angle info for mmigroup apk
	HARDWARE_WIDE_ANGLE_CAM_MOUDULE_ID,
	HARDWARE_MACRO_CAM_MOUDULE_ID,//+S96818AA1-1936,lijiazhen2.wt,ADD,2024/05/06, add camera module info for factory apk
	HARDWARE_BOARD_ID,
	HARDWARE_HARDWARE_ID,
	HARDWARE_BMS_GAUGE_ID, //zhaosidong.wt, add bms id
	HARDWARE_LCD_SERIALNUM,
	HARDWARE_MAX_ITEM
};


#define HARDWARE_ID                               'H'
#define HARDWARE_LCD_GET                          _IOWR(HARDWARE_ID, 0x01, char[HARDWARE_MAX_ITEM_LONGTH])      //  LCD
#define HARDWARE_TP_GET                           _IOWR(HARDWARE_ID, 0x02, char[HARDWARE_MAX_ITEM_LONGTH])      //  TP
#define HARDWARE_FLASH_GET                        _IOWR(HARDWARE_ID, 0x03, char[HARDWARE_MAX_ITEM_LONGTH])      //  FLASH
#define HARDWARE_FRONT_CAM_GET                    _IOWR(HARDWARE_ID, 0x04, char[HARDWARE_MAX_ITEM_LONGTH])      //  前摄
#define HARDWARE_BACK_CAM_GET                     _IOWR(HARDWARE_ID, 0x05, char[HARDWARE_MAX_ITEM_LONGTH])      //  后摄
#define HARDWARE_ACCELEROMETER_GET                _IOWR(HARDWARE_ID, 0x06, char[HARDWARE_MAX_ITEM_LONGTH])      //  加速度传感器
#define HARDWARE_ALSPS_GET                        _IOWR(HARDWARE_ID, 0x07, char[HARDWARE_MAX_ITEM_LONGTH])      //  距离光感
#define HARDWARE_GYROSCOPE_GET                    _IOWR(HARDWARE_ID, 0x08, char[HARDWARE_MAX_ITEM_LONGTH])      //  陀螺仪
#define HARDWARE_MAGNETOMETER_GET                 _IOWR(HARDWARE_ID, 0x09, char[HARDWARE_MAX_ITEM_LONGTH])      //  地磁
#define HARDWARE_BT_GET                           _IOWR(HARDWARE_ID, 0x10, char[HARDWARE_MAX_ITEM_LONGTH])      //  蓝牙
#define HARDWARE_WIFI_GET                         _IOWR(HARDWARE_ID, 0x11, char[HARDWARE_MAX_ITEM_LONGTH])      //  WIFI
#define HARDWARE_GPS_GET                          _IOWR(HARDWARE_ID, 0x12, char[HARDWARE_MAX_ITEM_LONGTH])      //  GPS
#define HARDWARE_FM_GET                           _IOWR(HARDWARE_ID, 0x13, char[HARDWARE_MAX_ITEM_LONGTH])      //  FM
#define HARDWARE_BATTERY_ID_GET                   _IOWR(HARDWARE_ID, 0x15, char[HARDWARE_MAX_ITEM_LONGTH])      //  电池
#define HARDWARE_BACK_CAM_MOUDULE_ID_GET          _IOWR(HARDWARE_ID, 0x16, char[HARDWARE_MAX_ITEM_LONGTH])      //  后摄模组厂
#define HARDWARE_FRONT_CAM_MODULE_ID_GET          _IOWR(HARDWARE_ID, 0x17, char[HARDWARE_MAX_ITEM_LONGTH])      //  前摄模组厂
#define HARDWARE_BOARD_ID_GET                     _IOWR(HARDWARE_ID, 0x18, char[HARDWARE_MAX_ITEM_LONGTH])      //  board id
#define HARDWARE_FRONT_FISH_CAM_GET               _IOWR(HARDWARE_ID, 0x19, char[HARDWARE_MAX_ITEM_LONGTH])      // 前鱼眼
#define HARDWARE_BACK_FISH_CAM_GET                _IOWR(HARDWARE_ID, 0x1A, char[HARDWARE_MAX_ITEM_LONGTH])      //  后鱼眼
#define HARDWARE_HALL_GET                         _IOWR(HARDWARE_ID, 0x1B, char[HARDWARE_MAX_ITEM_LONGTH])      //  hall sensor
#define HARDWARE_PRESSURE_GET                     _IOWR(HARDWARE_ID, 0x1C, char[HARDWARE_MAX_ITEM_LONGTH])      //  气压传感器
#define HARDWARE_NFC_GET                          _IOWR(HARDWARE_ID, 0x1D, char[HARDWARE_MAX_ITEM_LONGTH])      //  NFC
#define HARDWARE_FRONT_SUBCAM_GET                 _IOWR(HARDWARE_ID, 0x1E, char[HARDWARE_MAX_ITEM_LONGTH])      //  前摄是双摄，前副摄像头
#define HARDWARE_BACK_SUBCAM_GET                  _IOWR(HARDWARE_ID, 0x1F, char[HARDWARE_MAX_ITEM_LONGTH])      //  后摄是双摄，后副摄像头
#define HARDWARE_FRONT_FISH_CAM_MOUDULE_ID_GET    _IOWR(HARDWARE_ID, 0x20, char[HARDWARE_MAX_ITEM_LONGTH])      //  前鱼眼模组厂
#define HARDWARE_BACK_FISH_CAM_MOUDULE_ID_GET     _IOWR(HARDWARE_ID, 0x21, char[HARDWARE_MAX_ITEM_LONGTH])      // 后鱼眼模组厂
#define HARDWARE_HARDWARE_ID_GET                  _IOWR(HARDWARE_ID, 0x22, char[HARDWARE_MAX_ITEM_LONGTH])      //hardwareid

#define HARDWARE_FRONT_SUBCAM_MODULEID_GET        _IOWR(HARDWARE_ID, 0x23, char[HARDWARE_MAX_ITEM_LONGTH])      //  前摄是双摄，前副摄像头
#define HARDWARE_BACK_SUBCAM_MODULEID_GET         _IOWR(HARDWARE_ID, 0x24, char[HARDWARE_MAX_ITEM_LONGTH])      //  后摄是双摄，后副摄像头
#define HARDWARE_BACK_CAM_EFUSEID_GET             _IOWR(HARDWARE_ID, 0x25, char[HARDWARE_MAX_ITEM_LONGTH])      //  后摄efuseId
#define HARDWARE_BCAK_SUBCAM_EFUSEID_GET          _IOWR(HARDWARE_ID, 0x26, char[HARDWARE_MAX_ITEM_LONGTH])      //  后副摄efuseId
#define HARDWARE_FRONT_CAME_EFUSEID_GET           _IOWR(HARDWARE_ID, 0x27, char[HARDWARE_MAX_ITEM_LONGTH])      //  前摄efuseId
#define HARDWARE_FRONT_SUBCAME_EFUSEID_GET        _IOWR(HARDWARE_ID, 0x28, char[HARDWARE_MAX_ITEM_LONGTH])      //  前副摄efuseId
#define HARDWARE_BACK_CAM_SENSORID_GET            _IOWR(HARDWARE_ID, 0x29, char[HARDWARE_MAX_ITEM_LONGTH])      //  后摄sensorId
#define HARDWARE_BACK_SUBCAM_SENSORID_GET         _IOWR(HARDWARE_ID, 0x30, char[HARDWARE_MAX_ITEM_LONGTH])      //  后副摄sensorId
#define HARDWARE_FRONT_CAM_SENSORID_GET           _IOWR(HARDWARE_ID, 0x31, char[HARDWARE_MAX_ITEM_LONGTH])      //  前摄sensorId
#define HARDWARE_FRONT_SUBCAM_SENSORID_GET        _IOWR(HARDWARE_ID, 0x32, char[HARDWARE_MAX_ITEM_LONGTH])      //  前副摄sensorId
//bug 349613,20180409,huwei2,add Sar in hardwareInfo
#define HARDWARE_SAR_GET                          _IOWR(HARDWARE_ID, 0x33, char[HARDWARE_MAX_ITEM_LONGTH])      //sar

//+bug604664,zhouyikuan.wt,ADD,2020/12/17,add wide angle info for mmigroup apk
#define HARDWARE_WIDE_ANGLE_CAM_GET                     _IOWR(HARDWARE_ID, 0x34, char[HARDWARE_MAX_ITEM_LONGTH])      //  广角CAM
#define HARDWARE_WIDE_ANGLE_CAM_MOUDULE_ID_GET          _IOWR(HARDWARE_ID, 0x35, char[HARDWARE_MAX_ITEM_LONGTH])      //  广角CAM模组厂
#define HARDWARE_WIDE_ANGLE_CAM_EFUSEID_GET             _IOWR(HARDWARE_ID, 0x36, char[HARDWARE_MAX_ITEM_LONGTH])      //  广角CAM efuseId
#define HARDWARE_WIDE_ANGLE_CAM_SENSORID_GET            _IOWR(HARDWARE_ID, 0x37, char[HARDWARE_MAX_ITEM_LONGTH])      //  广角CAM sensorId
//-bug604664,zhouyikuan.wt,ADD,2020/12/17,add wide angle info for mmigroup apk

#define HARDWARE_MACRO_CAM_GET                      _IOWR(HARDWARE_ID, 0x3C, char[HARDWARE_MAX_ITEM_LONGTH])      //  微距CAM
#define HARDWARE_MACRO_CAM_MOUDULE_ID_GET           _IOWR(HARDWARE_ID, 0x3D, char[HARDWARE_MAX_ITEM_LONGTH])      //  微距CAM模组厂
#define HARDWARE_MACRO_CAM_EFUSEID_GET              _IOWR(HARDWARE_ID, 0x3E, char[HARDWARE_MAX_ITEM_LONGTH])      //  微距CAM efuseId
#define HARDWARE_MACRO_CAM_SENSORID_GET             _IOWR(HARDWARE_ID, 0x3F, char[HARDWARE_MAX_ITEM_LONGTH])      //  微距CAM sensorId

#define HARDWARE_PD_CHARGER_GET              	_IOWR(HARDWARE_ID, 0x47, char[HARDWARE_MAX_ITEM_LONGTH])
#define HARDWARE_CHARGER_PUMP_GET              	_IOWR(HARDWARE_ID, 0x48, char[HARDWARE_MAX_ITEM_LONGTH])

#define HARDWARE_BACK_CAM_MOUDULE_ID_SET          _IOWR(HARDWARE_ID, 0x81, char[HARDWARE_MAX_ITEM_LONGTH])
#define HARDWARE_FRONT_CAM_MODULE_ID_SET          _IOWR(HARDWARE_ID, 0x82, char[HARDWARE_MAX_ITEM_LONGTH])
#define HARDWARE_SDCARD_STATUS                    _IOWR(HARDWARE_ID, 0x83, char[HARDWARE_MAX_ITEM_LONGTH])
#define HARDWARE_FINGER_GET                       _IOWR(HARDWARE_ID, 0x84, char[HARDWARE_MAX_ITEM_LONGTH])


/*+Bug 313110 -  guojunbo.wt;add;20171026;add for lg sku */
#define HARDWARE_SKU_INFO_GET                     _IOWR(HARDWARE_ID, 0x85, char[HARDWARE_MAX_ITEM_LONGTH])
#define HARDWARE_CHARGER_IC_INFO_GET              _IOWR(HARDWARE_ID, 0x86, char[HARDWARE_MAX_ITEM_LONGTH])
#define HARDWARE_BMS_GAUGE_GET                    _IOWR(HARDWARE_ID, 0x41, char[HARDWARE_MAX_ITEM_LONGTH])
/*-Bug 313110 -  guojunbo.wt;add;20171026;add for lg sku */

#define HARDWARE_SECURE_INFO_GET                  _IOWR(HARDWARE_ID, 0x87, char[HARDWARE_MAX_ITEM_LONGTH])
#define SOFTWARE_SECURE_INFO_GET                  _IOWR(HARDWARE_ID, 0x88, char[HARDWARE_MAX_ITEM_LONGTH])
#define HARDWARE_LCD_SERIALNUM_GET                _IOWR(HARDWARE_ID, 0x89, char[HARDWARE_MAX_ITEM_LONGTH])

//+S98901AA1-827, zhouweijie.wt, add, 2024/04/15, sia81xx bring up
#define HARDWARE_SMARTPA_IC_GET                    _IOWR(HARDWARE_ID, 0x40, char[HARDWARE_MAX_ITEM_LONGTH])
enum{
	INVALD = -1,
	FS16XX,
	AW88261,
	AW88266,
	TAS2558,
	FS1962,
	AW88257,
	sia81xx,
	aw88394,
	MAX_NUM,
};
int snd_soc_set_smartpa_type(const char * name,int pa_type);
//-S98901AA1-827, zhouweijie.wt, add, 2024/04/15, sia81xx bring up

/* +S98901AA1-8583, zhouweijie.wt, 20240713, add get hardwareinfo */
char* hardwareinfo_get_prop(int cmd);
/* -S98901AA1-8583, zhouweijie.wt, 20240713, add get hardwareinfo */

int hardwareinfo_set_prop(int cmd, const char *name);

#endif //__HARDWARE_H__
