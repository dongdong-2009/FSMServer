/*!
\file
\brief Файл настрооек
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#ifndef FSM_SETTINGS_H
#define	FSM_SETTINGS_H
/*!
\brief Размер дерва функций
*/
#define FSM_DeviceFunctionTreeSize 100
/*!
\brief Размер дерева устройств
*/
#define FSM_DeviceTreeSize 100
/*!
\brief Размер дерва Ethernet устройств
*/
#define FSM_EthernetDeviceTreeSize 100
/*!
\brief ID Ethernet передатчика
*/
#define FSM_EthernetID2 1
#define FSM_FifoID 0
/*!
\brief ID сервера статистики
*/
#define FSM_StatisicID 21
#define FSM_SettingID setservid
/*!
\brief Размер дерева аудио потоков
*/
#define FSM_AudioStreamDeviceTreeSize 100

#define FSM_FIFOAudioStreamDeviceTreeSize 100
/*!
\brief Размер дерева E1 устройств потоков
*/
#define FSM_E1DeviceTreeSize 6

#define FSM_PO06DeviceTreeSize 6
#define FSM_MN825DeviceTreeSize 6
#define FSM_MN921DeviceTreeSize 6
#define FSM_MN111DeviceTreeSize 6
#define FSM_PO07DeviceTreeSize 6
#define FSM_PO08DeviceTreeSize 6

#define FSM_CryptoAlgoritmNum 6

#define FSM_InterfaceID "esp4"

#define FSM_Conferenc_num 10

#define FSM_Circular_num 10

#define FSM_P2P_abonent_count 2

#define FSM_Conferenc_abonent_count 2

#define FSM_Circulac_abonent_count 2

#define FSM_SkyNetDeviceTreeSize 12

#define FSM_ClientTreeSize 12

#define FSM_E1CasTreeSize 12

#define FSM_EventTreeSize 12

#define FSM_IOCTLTreeSize 12
#define FSM_PropertyTreeSize 12

#define FSM_EventIOCtlId 1
#define FSM_StatistickIOCtlId 2
#endif	/* FSM_SETTINGS_H */

//#define DEBUG_CALL_STACK