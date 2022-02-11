#pragma once
// 保留的头文件, 这是为用户和厂商提供的一种特殊的、增值的，额外的服务。
// 绝大多数情况下，我们建议您优先使用USB3102A.h中的接口函数。(RSV=Reserve)
// 本头文件中的内容，我们不提供额外的技术支持

#ifndef _USB3102ARSV_DEVICE_
#define _USB3102ARSV_DEVICE_

#include "USB3102A.h"

// 函数FILE_Create()的参数nOptMode所用的文件操作方式(支持"或"指令实现多种方式并行操作)
#define USB3102A_FILE_OPTMODE_CREATE_NEW			1	// 创建文件,如果文件存在则会出错
#define USB3102A_FILE_OPTMODE_CREATE_ALWAYS		2	// 不管文件是否存在，总是要被创建(即可能改写前一个文件)
#define USB3102A_FILE_OPTMODE_OPEN_EXISTING		3	// 打开必须已经存在的文件
#define USB3102A_FILE_OPTMODE_OPEN_ALWAYS		4	// 打开文件，若该文件不在，则创建它

// 函数FILE_SetOffset()的参数nBaseMode所用的文件指针移动参考基点
#define USB3102A_FILE_BASEMODE_BEGIN				0	// 以文件起点作为参考点往右偏移
#define USB3102A_FILE_BASEMODE_CURRENT			1	// 以文件的当前位置作为参考点往左或往右偏移(nOffsetBytes<0时往左偏移，>0时往右偏移)
#define USB3102A_FILE_BASEMODE_END				2	// 以文件的尾部作为参考点往左偏移

// 函数AUX_GetCPUTime()的参数nUnitType所用的返回值单位类型
#define USB3102A_UNIT_TYPE_NS	0	// 返回纳秒时间
#define USB3102A_UNIT_TYPE_US	1	// 返回微秒时间
#define USB3102A_UNIT_TYPE_MS	2	// 返回毫秒时间
#define USB3102A_UNIT_TYPE_S		3	// 返回秒时间
#define USB3102A_UNIT_TYPE_M		4	// 返回分时间
#define USB3102A_UNIT_TYPE_H		5	// 返回小时时间
#define USB3102A_UNIT_TYPE_D		6	// 返回天时间
#define USB3102A_UNIT_TYPE_AUTO	7   // 自动单位(如果大于等于1天，则以天为单位，依此类推)

// ################################ 保留的设备驱动接口申明 ################################
#ifndef _USB3102A_DRIVER_
#define DEVLIB __declspec(dllimport)
#else
#define DEVLIB __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	BOOL DEVLIB WINAPI USB3102A_DEV_ConfigDialog(HANDLE hDevice); // 设备配置对话框，就是通过对话框的窗口操作方式进行设备的若干配置。

	BOOL DEVLIB WINAPI USB3102A_DEV_Find(						// 查找系统中存在的设备，并建立相应的列表项
		BOOL bLgcIdxList[],		// 存在于系统中的设备逻辑号, =NULL:表示不接收查找结果信息
		BOOL bPhysIdxList[],	// 存在于系统中的设备物理号, =NULL:表示不接收查找结果信息
		BOOL bUsedList[],		// 存在于系统中的设备是否被其他的应用程序使用, =NULL:表示不接收查找结果信息
		U32 nDemandCnt,			// 请求查找的设备数量，取值范围[1， 128]。以逻辑号0为起点，往后查找设备的数量, 比如=5，则仅查找逻辑号为0,1,2,3,4的设备
		U32* pFoundCnt);		// 返回实际已找到的设备数量，它也决定了列表List中的有效单元数量

								// ################################ 校准函数 ################################
	BOOL DEVLIB WINAPI USB3102A_AI_IsCaled(						// AI是否已被自我校准过, 如果已校准过，则返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		BOOL* pCaled);			// 是否已经被校准，=TRUE:表示已经被校准过, =FALSE:表示未被校准过

	BOOL DEVLIB WINAPI USB3102A_AI_SelfCal(						// AI自我校准, 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

	BOOL DEVLIB WINAPI USB3102A_AO_IsCaled(						// AO是否已被自我校准过, 如果已校准过，则返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		BOOL* pCaled);			// 是否已经被校准，=TRUE:表示已经被校准过, =FALSE:表示未被校准过

	BOOL DEVLIB WINAPI USB3102A_AO_SelfCal(						// AO自我校准, 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

								// ################################ 设备信息函数 ################################
	BOOL DEVLIB WINAPI USB3102A_DEV_GetPhysIdx(					// 获得物理序号, 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32* pPhysIdx);			// 返回的物理序号

	BOOL DEVLIB WINAPI USB3102A_DEV_SetPhysIdx(					// 设置物理序号, 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPhysIdx);			// 物理序号

	BOOL DEVLIB WINAPI USB3102A_DEV_GetVersion(					// 获得设备版本信息, 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32* pDllVer,			// 返回的动态库(.dll)版本号
		U32* pDriverVer,		// 返回的驱动(.sys)版本号
		U32* pFirmwareVer);		// 返回的固件版本号

	BOOL DEVLIB WINAPI USB3102A_DEV_GetSerialNum(				// 获得序列号, 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32* pSerialNum);		// 返回的序列号

	BOOL DEVLIB WINAPI USB3102A_DEV_GetUserPID(					// 获得用户产品ID号(User Product Identification), 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32* pUserPID);			// 返回的用户产品ID

	BOOL DEVLIB WINAPI USB3102A_DEV_SetUserPID(					// 设置用户产品ID号(User Product Identification), 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nUserPID);			// 用户产品ID

	BOOL DEVLIB WINAPI USB3102A_DEV_GetPowerMode(				// 取得设备的电源模式(Get Power Mode), 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32* pPowerMode,		// 电源模式, =0:表示设备由USB总线供电, =1:表示设备由外部电源供电(7V-24V)
		U32* pOverVoltage);		// 外部电源供电是否超压，=0:表示外部向设备正常供电, =1:表示外部向设备超压供电，即超出[7, 24]V范围。仅在外部供电时有效。

								// ############################# 文件函数(支持大于4GB文件读写) ##############################
	HANDLE DEVLIB WINAPI USB3102A_FILE_Create(					// 根据指定文件名创建文件句柄(hFile),如果失败，则返回值为INVALID_HANDLE_VALUE(-1),可调用GetLastError()分析错误原因
		LPCTSTR strFileName,// 路径及文件名,如"C:\\ART\\SampleData.dat" 
		I32 nOptMode);			// 文件操作模式，见上面相关常量定义

	U32 DEVLIB WINAPI USB3102A_FILE_Read(						// 从指定文件中读取数据,返回实际读取的字节数, 成功时返回值大于0,否则返回值等于0,可调用GetLastError()分析错误原因
		HANDLE hFile,			// 文件句柄,由FILE_Create()函数创建
		PVOID pDataBuffer,		// 数据缓冲区，存放从文件读取的数据
		U32 nSizeBytes);		// 请求读取数据的字节数

	U32 DEVLIB WINAPI USB3102A_FILE_Write(						// 向指定文件写入数据,返回实际写入的字节数, 成功时返回值大于0,否则返回值等于0,可调用GetLastError()分析错误原因
		HANDLE hFile,			// 文件句柄,由FILE_Create()函数创建
		PVOID pDataBuffer,		// 数据缓冲区，存放要写入文件的数据
		U32 nSizeBytes);		// 请求写入数据的字节数

	U64 DEVLIB WINAPI USB3102A_FILE_GetLength(HANDLE hFile);		// 获取指定文件的长度(字节数), 成功时返回值大于0,否则返回值等于0,可调用GetLastError()分析错误原因

	BOOL DEVLIB WINAPI USB3102A_FILE_SetOffset(					// 设置读写文件的偏移位置, 成功时返回TRUE,否则返回FALSE,可调用GetLastError()分析错误原因
		HANDLE hFile,			// 文件句柄,由FILE_Create()函数创建
		I64 nOffsetBytes,		// 偏移位置(字节)
		I32 nBaseMode);			// 参考基点模式，具体请参考上面的相关常量定义

	U64 DEVLIB WINAPI USB3102A_FILE_GetDiskFreeBytes(			// 获取指定磁盘的剩余空间（字节数）,成功时返回值大于0,否则返回值等于0,可调用GetLastError()分析错误原因
		LPCTSTR strDiskName);	// 磁盘名称，如"C:\\", "D:\\"

	BOOL DEVLIB WINAPI USB3102A_FILE_Release(HANDLE hFile);		// 释放文件句柄

																// ################################ 辅助函数 ################################
	BOOL DEVLIB WINAPI USB3102A_AUX_kbhit(void); // 探测用户是否有键盘动作(在Console应用程序中有效)
	I8 DEVLIB WINAPI USB3102A_AUX_getch(void); // 等待并获取用户键盘键值(在Console应用程序中有效)
	BOOL DEVLIB WINAPI USB3102A_AUX_DelayTime(U32 nMicrosecond); // 微秒延时函数
	double DEVLIB WINAPI USB3102A_AUX_GetCPUTime(int nUnitType, int* pRetUnitType = NULL, char* strUnitType = NULL); // 获取CPU运行时间(1GHz的CPU，则可计584年，2GHz的CPU，则可计292年)

#ifdef __cplusplus
}
#endif

#ifndef _CVIDEF_H
// 自动包含驱动函数导入库
#ifndef _USB3102A_DRIVER_
#ifndef LOAD_USB3102A_LIB // 如果没有加载LIB库
#define LOAD_USB3102A_LIB
#pragma comment(lib, "USB3102A.lib")
#pragma message("Welcome to use ART products!")
#pragma message("Linked with USB3102A.lib successfully!")
#pragma message("Linked with USB3102A.dll successfully!")
#endif // LOAD_USB3102A_LIB
#endif // _USB3102A_DRIVER_
#endif // _CVIDEF_H

#endif // _USB3102ARSV_DEVICE_