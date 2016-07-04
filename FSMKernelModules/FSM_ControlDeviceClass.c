#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSM_Client/FSM_client.h"
#include "FSM/FSMDevice/fsm_statusstruct.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_DeviceFunctionTree dft;

void FSM_ControlDeviceRecive(char* data,short len, struct FSM_DeviceTree* fsmdt)
{
    
}
static int __init FSMControlDevice_init(void)
{
   dft.aplayp=0;
   dft.type=(unsigned char)ControlMachine;
   dft.VidDevice=(unsigned char)Computer;
   dft.PodVidDevice=(unsigned char)PC;
   dft.KodDevice=(unsigned char)ARM;
   dft.Proc=FSM_ControlDeviceRecive;
   dft.config_len=0;
   FSM_DeviceClassRegister(dft);
   printk( KERN_INFO "FSM ControlDevice loaded\n" ); 

   return 0;  
}
static void __exit FSMControlDevice_exit(void)
{  
   FSM_ClassDeRegister(dft);
   printk( KERN_INFO "FSM ControlDevice module unloaded\n" );
}

module_init(FSMControlDevice_init);
module_exit(FSMControlDevice_exit);