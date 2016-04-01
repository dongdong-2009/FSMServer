/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 */

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSMDevice/fsm_statusstruct.h"


#define MY_DEST_MAC0	0x00
#define MY_DEST_MAC1	0x00
#define MY_DEST_MAC2	0x00
#define MY_DEST_MAC3	0x00
#define MY_DEST_MAC4	0x00
#define MY_DEST_MAC5	0x00

#define DEFAULT_IF	"eth0"
#define BUF_SIZ		1024

int main(int argc, char *argv[])
{
	int sockfd;
    char n;
	struct ifreq if_idx;
	struct ifreq if_mac;
	int tx_len = 0;
	char sendbuf[BUF_SIZ];
	struct ether_header *eh = (struct ether_header *) sendbuf;
	struct FSM_DeviceRegistr *regp = (struct FSM_DeviceRegistr *) (sendbuf + sizeof(struct ether_header));
    struct FSM_DeviceDelete *regpd = (struct FSM_DeviceDelete *) (sendbuf + sizeof(struct ether_header));
    struct  FSM_SendCmdTS *regpcmdts = (struct FSM_SendCmdTS *) (sendbuf + sizeof(struct ether_header));
     struct  FSM_SendAudioData *regad = (struct FSM_SendAudioData *) (sendbuf + sizeof(struct ether_header));
	struct sockaddr_ll socket_address;
	char ifName[IFNAMSIZ];
	
	/* Get interface name */
	if (argc > 1)
    {
		strcpy(ifName, argv[1]);
        n= argv[2][0];
    }
	else
		strcpy(ifName, DEFAULT_IF);

	/* Open RAW socket to send on */
	if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
	    perror("socket");
	}

	/* Get the index of the interface to send on */
	memset(&if_idx, 0, sizeof(struct ifreq));
	strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
	    perror("SIOCGIFINDEX");
	/* Get the MAC address of the interface to send on */
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
	    perror("SIOCGIFHWADDR");

	/* Construct the Ethernet header */
	memset(sendbuf, 0, BUF_SIZ);
	/* Ethernet header */
	eh->ether_shost[0] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
	eh->ether_shost[1] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
	eh->ether_shost[2] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
	eh->ether_shost[3] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
	eh->ether_shost[4] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
	eh->ether_shost[5] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];
	eh->ether_dhost[0] = MY_DEST_MAC0;
	eh->ether_dhost[1] = MY_DEST_MAC1;
	eh->ether_dhost[2] = MY_DEST_MAC2;
	eh->ether_dhost[3] = MY_DEST_MAC3;
	eh->ether_dhost[4] = MY_DEST_MAC4;
	eh->ether_dhost[5] = MY_DEST_MAC5;
	/* Ethertype field */
	eh->ether_type = htons(0x1996);
	tx_len += sizeof(struct ether_header);

  
    
	/* Packet data */
	/*sendbuf[tx_len++] = 0x01;
	sendbuf[tx_len++] = 0xad;
	sendbuf[tx_len++] = 0xbe;
	sendbuf[tx_len++] = 0xef;
     * */
     

	/* Index of the network device */
	socket_address.sll_ifindex = if_idx.ifr_ifindex;
	/* Address length*/
	socket_address.sll_halen = ETH_ALEN;
	/* Destination MAC */
	socket_address.sll_addr[0] = MY_DEST_MAC0;
	socket_address.sll_addr[1] = MY_DEST_MAC1;
	socket_address.sll_addr[2] = MY_DEST_MAC2;
	socket_address.sll_addr[3] = MY_DEST_MAC3;
	socket_address.sll_addr[4] = MY_DEST_MAC4;
	socket_address.sll_addr[5] = MY_DEST_MAC5;

      switch(n)  
    {  
        case '1':
        
      /*  regp->IDDevice=10;
        regp->VidDevice=CommunicationDevice;
        regp->PodVidDevice=CCK;
        regp->KodDevice=MN524;
        regp->type=AudioDevice;
        regp->opcode=RegDevice;
        regp->CRC=0;
         * */
            regp->IDDevice=(unsigned short)FSM_StatisicID;
   regp->VidDevice=(unsigned char)FSMDeviceConfig;
   regp->PodVidDevice=(unsigned char)ComputerStatistic;
   regp->KodDevice=(unsigned char)PCx86;
   regp->type=(unsigned char)StatisticandConfig;
   regp->opcode=RegDevice;
   regp->CRC=0;
        
    tx_len += sizeof(struct FSM_DeviceRegistr);
   
	/* Send packet */
	if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
	    printf("Send failed\n");
     break;
     case '2':;
        tx_len += sizeof(struct FSM_DeviceDelete);
    regpd->CRC=0;
    regpd->IDDevice=10;
    regpd->opcode=DelLisr;
    if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
	    printf("Send failed\n");
        break;
        case '3':
        tx_len += sizeof(struct FSM_SendCmdTS);
        regpcmdts->opcode=SendCmdToServer;
        regpcmdts->countparam=1;
        regpcmdts->CRC=0;
        regpcmdts->IDDevice=21;  
        regpcmdts->cmd=1;
 if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
	    printf("Send failed\n");
        break;
        case '4':
        tx_len += sizeof(struct FSM_SendAudioData);
        regad->opcode=SendAudio;
        regad->IDDevice=0;
        regad->CRC=0;
        regad->codec=0;
        regad->len=2;
        regad->Data[0]=0xd0;
        regad->Data[1]=0xd1;
 if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
	    printf("Send failed\n");
        break;
    }
	return 0;
}