#pragma once
// ������ͷ�ļ�, ����Ϊ�û��ͳ����ṩ��һ������ġ���ֵ�ģ�����ķ���
// �����������£����ǽ���������ʹ��USB3102A.h�еĽӿں�����(RSV=Reserve)
// ��ͷ�ļ��е����ݣ����ǲ��ṩ����ļ���֧��

#ifndef _USB3102ARSV_DEVICE_
#define _USB3102ARSV_DEVICE_

#include "USB3102A.h"

// ����FILE_Create()�Ĳ���nOptMode���õ��ļ�������ʽ(֧��"��"ָ��ʵ�ֶ��ַ�ʽ���в���)
#define USB3102A_FILE_OPTMODE_CREATE_NEW			1	// �����ļ�,����ļ�����������
#define USB3102A_FILE_OPTMODE_CREATE_ALWAYS		2	// �����ļ��Ƿ���ڣ�����Ҫ������(�����ܸ�дǰһ���ļ�)
#define USB3102A_FILE_OPTMODE_OPEN_EXISTING		3	// �򿪱����Ѿ����ڵ��ļ�
#define USB3102A_FILE_OPTMODE_OPEN_ALWAYS		4	// ���ļ��������ļ����ڣ��򴴽���

// ����FILE_SetOffset()�Ĳ���nBaseMode���õ��ļ�ָ���ƶ��ο�����
#define USB3102A_FILE_BASEMODE_BEGIN				0	// ���ļ������Ϊ�ο�������ƫ��
#define USB3102A_FILE_BASEMODE_CURRENT			1	// ���ļ��ĵ�ǰλ����Ϊ�ο������������ƫ��(nOffsetBytes<0ʱ����ƫ�ƣ�>0ʱ����ƫ��)
#define USB3102A_FILE_BASEMODE_END				2	// ���ļ���β����Ϊ�ο�������ƫ��

// ����AUX_GetCPUTime()�Ĳ���nUnitType���õķ���ֵ��λ����
#define USB3102A_UNIT_TYPE_NS	0	// ��������ʱ��
#define USB3102A_UNIT_TYPE_US	1	// ����΢��ʱ��
#define USB3102A_UNIT_TYPE_MS	2	// ���غ���ʱ��
#define USB3102A_UNIT_TYPE_S		3	// ������ʱ��
#define USB3102A_UNIT_TYPE_M		4	// ���ط�ʱ��
#define USB3102A_UNIT_TYPE_H		5	// ����Сʱʱ��
#define USB3102A_UNIT_TYPE_D		6	// ������ʱ��
#define USB3102A_UNIT_TYPE_AUTO	7   // �Զ���λ(������ڵ���1�죬������Ϊ��λ����������)

// ################################ �������豸�����ӿ����� ################################
#ifndef _USB3102A_DRIVER_
#define DEVLIB __declspec(dllimport)
#else
#define DEVLIB __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	BOOL DEVLIB WINAPI USB3102A_DEV_ConfigDialog(HANDLE hDevice); // �豸���öԻ��򣬾���ͨ���Ի���Ĵ��ڲ�����ʽ�����豸���������á�

	BOOL DEVLIB WINAPI USB3102A_DEV_Find(						// ����ϵͳ�д��ڵ��豸����������Ӧ���б���
		BOOL bLgcIdxList[],		// ������ϵͳ�е��豸�߼���, =NULL:��ʾ�����ղ��ҽ����Ϣ
		BOOL bPhysIdxList[],	// ������ϵͳ�е��豸�����, =NULL:��ʾ�����ղ��ҽ����Ϣ
		BOOL bUsedList[],		// ������ϵͳ�е��豸�Ƿ�������Ӧ�ó���ʹ��, =NULL:��ʾ�����ղ��ҽ����Ϣ
		U32 nDemandCnt,			// ������ҵ��豸������ȡֵ��Χ[1�� 128]�����߼���0Ϊ��㣬��������豸������, ����=5����������߼���Ϊ0,1,2,3,4���豸
		U32* pFoundCnt);		// ����ʵ�����ҵ����豸��������Ҳ�������б�List�е���Ч��Ԫ����

								// ################################ У׼���� ################################
	BOOL DEVLIB WINAPI USB3102A_AI_IsCaled(						// AI�Ƿ��ѱ�����У׼��, �����У׼�����򷵻�TRUE,���򷵻�FALSE
		HANDLE hDevice,			// �豸������,����DEV_Create()��������
		BOOL* pCaled);			// �Ƿ��Ѿ���У׼��=TRUE:��ʾ�Ѿ���У׼��, =FALSE:��ʾδ��У׼��

	BOOL DEVLIB WINAPI USB3102A_AI_SelfCal(						// AI����У׼, �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hDevice);		// �豸������,����DEV_Create()��������

	BOOL DEVLIB WINAPI USB3102A_AO_IsCaled(						// AO�Ƿ��ѱ�����У׼��, �����У׼�����򷵻�TRUE,���򷵻�FALSE
		HANDLE hDevice,			// �豸������,����DEV_Create()��������
		BOOL* pCaled);			// �Ƿ��Ѿ���У׼��=TRUE:��ʾ�Ѿ���У׼��, =FALSE:��ʾδ��У׼��

	BOOL DEVLIB WINAPI USB3102A_AO_SelfCal(						// AO����У׼, �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hDevice);		// �豸������,����DEV_Create()��������

								// ################################ �豸��Ϣ���� ################################
	BOOL DEVLIB WINAPI USB3102A_DEV_GetPhysIdx(					// ����������, �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hDevice,			// �豸������,����DEV_Create()��������
		U32* pPhysIdx);			// ���ص��������

	BOOL DEVLIB WINAPI USB3102A_DEV_SetPhysIdx(					// �����������, �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hDevice,			// �豸������,����DEV_Create()��������
		U32 nPhysIdx);			// �������

	BOOL DEVLIB WINAPI USB3102A_DEV_GetVersion(					// ����豸�汾��Ϣ, �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hDevice,			// �豸������,����DEV_Create()��������
		U32* pDllVer,			// ���صĶ�̬��(.dll)�汾��
		U32* pDriverVer,		// ���ص�����(.sys)�汾��
		U32* pFirmwareVer);		// ���صĹ̼��汾��

	BOOL DEVLIB WINAPI USB3102A_DEV_GetSerialNum(				// ������к�, �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hDevice,			// �豸������,����DEV_Create()��������
		U32* pSerialNum);		// ���ص����к�

	BOOL DEVLIB WINAPI USB3102A_DEV_GetUserPID(					// ����û���ƷID��(User Product Identification), �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hDevice,			// �豸������,����DEV_Create()��������
		U32* pUserPID);			// ���ص��û���ƷID

	BOOL DEVLIB WINAPI USB3102A_DEV_SetUserPID(					// �����û���ƷID��(User Product Identification), �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hDevice,			// �豸������,����DEV_Create()��������
		U32 nUserPID);			// �û���ƷID

	BOOL DEVLIB WINAPI USB3102A_DEV_GetPowerMode(				// ȡ���豸�ĵ�Դģʽ(Get Power Mode), �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hDevice,			// �豸������,����DEV_Create()��������
		U32* pPowerMode,		// ��Դģʽ, =0:��ʾ�豸��USB���߹���, =1:��ʾ�豸���ⲿ��Դ����(7V-24V)
		U32* pOverVoltage);		// �ⲿ��Դ�����Ƿ�ѹ��=0:��ʾ�ⲿ���豸��������, =1:��ʾ�ⲿ���豸��ѹ���磬������[7, 24]V��Χ�������ⲿ����ʱ��Ч��

								// ############################# �ļ�����(֧�ִ���4GB�ļ���д) ##############################
	HANDLE DEVLIB WINAPI USB3102A_FILE_Create(					// ����ָ���ļ��������ļ����(hFile),���ʧ�ܣ��򷵻�ֵΪINVALID_HANDLE_VALUE(-1),�ɵ���GetLastError()��������ԭ��
		LPCTSTR strFileName,// ·�����ļ���,��"C:\\ART\\SampleData.dat" 
		I32 nOptMode);			// �ļ�����ģʽ����������س�������

	U32 DEVLIB WINAPI USB3102A_FILE_Read(						// ��ָ���ļ��ж�ȡ����,����ʵ�ʶ�ȡ���ֽ���, �ɹ�ʱ����ֵ����0,���򷵻�ֵ����0,�ɵ���GetLastError()��������ԭ��
		HANDLE hFile,			// �ļ����,��FILE_Create()��������
		PVOID pDataBuffer,		// ���ݻ���������Ŵ��ļ���ȡ������
		U32 nSizeBytes);		// �����ȡ���ݵ��ֽ���

	U32 DEVLIB WINAPI USB3102A_FILE_Write(						// ��ָ���ļ�д������,����ʵ��д����ֽ���, �ɹ�ʱ����ֵ����0,���򷵻�ֵ����0,�ɵ���GetLastError()��������ԭ��
		HANDLE hFile,			// �ļ����,��FILE_Create()��������
		PVOID pDataBuffer,		// ���ݻ����������Ҫд���ļ�������
		U32 nSizeBytes);		// ����д�����ݵ��ֽ���

	U64 DEVLIB WINAPI USB3102A_FILE_GetLength(HANDLE hFile);		// ��ȡָ���ļ��ĳ���(�ֽ���), �ɹ�ʱ����ֵ����0,���򷵻�ֵ����0,�ɵ���GetLastError()��������ԭ��

	BOOL DEVLIB WINAPI USB3102A_FILE_SetOffset(					// ���ö�д�ļ���ƫ��λ��, �ɹ�ʱ����TRUE,���򷵻�FALSE,�ɵ���GetLastError()��������ԭ��
		HANDLE hFile,			// �ļ����,��FILE_Create()��������
		I64 nOffsetBytes,		// ƫ��λ��(�ֽ�)
		I32 nBaseMode);			// �ο�����ģʽ��������ο��������س�������

	U64 DEVLIB WINAPI USB3102A_FILE_GetDiskFreeBytes(			// ��ȡָ�����̵�ʣ��ռ䣨�ֽ�����,�ɹ�ʱ����ֵ����0,���򷵻�ֵ����0,�ɵ���GetLastError()��������ԭ��
		LPCTSTR strDiskName);	// �������ƣ���"C:\\", "D:\\"

	BOOL DEVLIB WINAPI USB3102A_FILE_Release(HANDLE hFile);		// �ͷ��ļ����

																// ################################ �������� ################################
	BOOL DEVLIB WINAPI USB3102A_AUX_kbhit(void); // ̽���û��Ƿ��м��̶���(��ConsoleӦ�ó�������Ч)
	I8 DEVLIB WINAPI USB3102A_AUX_getch(void); // �ȴ�����ȡ�û����̼�ֵ(��ConsoleӦ�ó�������Ч)
	BOOL DEVLIB WINAPI USB3102A_AUX_DelayTime(U32 nMicrosecond); // ΢����ʱ����
	double DEVLIB WINAPI USB3102A_AUX_GetCPUTime(int nUnitType, int* pRetUnitType = NULL, char* strUnitType = NULL); // ��ȡCPU����ʱ��(1GHz��CPU����ɼ�584�꣬2GHz��CPU����ɼ�292��)

#ifdef __cplusplus
}
#endif

#ifndef _CVIDEF_H
// �Զ������������������
#ifndef _USB3102A_DRIVER_
#ifndef LOAD_USB3102A_LIB // ���û�м���LIB��
#define LOAD_USB3102A_LIB
#pragma comment(lib, "USB3102A.lib")
#pragma message("Welcome to use ART products!")
#pragma message("Linked with USB3102A.lib successfully!")
#pragma message("Linked with USB3102A.dll successfully!")
#endif // LOAD_USB3102A_LIB
#endif // _USB3102A_DRIVER_
#endif // _CVIDEF_H

#endif // _USB3102ARSV_DEVICE_