/*
@Platform: Friendly Arm tiny6410
@CPU: S3C6410
@Function: Bootloader0 ,init cpu 
@Written by Armstrong Wall
@Start wrirte date: 2016.3.26
@Daily: 		2016.3.25  Finish DM9000
*/
#include "dm9000.h"
#include "arp.h"


#define HON(n) ((((u16)((n) & 0xff)) << 8) | (((n) & 0xff00) >> 8))
//�����ֽ��򣬴�С�˸ߵ��ֽڻ���


u8 host_mac_addr[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
u8 mac_addr[6] = {9,8,7,6,5,4};
u8 ip_addr[4] = {192,168,1,30};
u8 host_ip_addr[4] = {192,168,1,100};
u16 packet_len;


u8 *buffer= &arpbuf;

/*1. ����arp�����*/
void arp_request()
{
			//1.����ARP�����
				
			memcpy(arpbuf.ethhdr.d_mac,host_mac_addr,6);		//��̫��Ŀ�ĵ�ַ
			memcpy(arpbuf.ethhdr.s_mac,mac_addr,6);					//��̫��Դ��ַ
			arpbuf.ethhdr.type = HON(0x0806);								//֡������
			
			arpbuf.hwtype   = HON(1);												//Ӳ������
			arpbuf.protocol = HON(0x0800);									//Э������
			
			arpbuf.hwlen    = 6;														//Ӳ����ַ����
			arpbuf.protolen = 4;														//Э���ַ����
			
			arpbuf.opcode   = HON(1);												//op
			
			memcpy(arpbuf.smac,mac_addr,6); 								//���Ͷ���̫����ַ
			memcpy(arpbuf.sipaddr,ip_addr,4);								//���Ͷ�IP��ַ
			memcpy(arpbuf.dipaddr,host_ip_addr,4);					//Ŀ��IP��ַ

			packet_len = 42;
			
		
			dm9000_tx(buffer,packet_len);
			
		

}





/*2.����ARPӦ���*/
u8 arp_process()
{
	  u32 i;
	  
	  if(packet_len<28)
	  	{
					return 0;
	  		}
	  
	  memcpy(host_ip_addr,arpbuf.sipaddr,4);	
	  printf("host ip is :");
	  for(i=0;i<4;i++)
	    printf("%03d",host_ip_addr[i]);
	  printf("\n\r");

	  
		memcpy(host_mac_addr,arpbuf.smac,6);	
	  printf("host mac is :");
	  for(i=0;i<6;i++)
	    printf("%02x",host_mac_addr[i]);
	  printf("\n\r");
	
	  printf("send MAC OK\n\r");
	
	}



/*2.����ARPӦ���*/
u8 arp_printf()
{
    printf("jhony :");
	
	}




