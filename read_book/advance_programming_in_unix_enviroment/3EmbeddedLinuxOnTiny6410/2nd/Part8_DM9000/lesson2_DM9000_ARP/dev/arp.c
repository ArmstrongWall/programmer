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
//网络字节序，大小端高低字节互换


u8 host_mac_addr[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
u8 mac_addr[6] = {9,8,7,6,5,4};
u8 ip_addr[4] = {192,168,1,30};
u8 host_ip_addr[4] = {192,168,1,100};
u16 packet_len;


u8 *buffer= &arpbuf;

/*1. 发送arp请求包*/
void arp_request()
{
			//1.构成ARP请求包
				
			memcpy(arpbuf.ethhdr.d_mac,host_mac_addr,6);		//以太网目的地址
			memcpy(arpbuf.ethhdr.s_mac,mac_addr,6);					//以太网源地址
			arpbuf.ethhdr.type = HON(0x0806);								//帧类型名
			
			arpbuf.hwtype   = HON(1);												//硬件类型
			arpbuf.protocol = HON(0x0800);									//协议类型
			
			arpbuf.hwlen    = 6;														//硬件地址长度
			arpbuf.protolen = 4;														//协议地址长度
			
			arpbuf.opcode   = HON(1);												//op
			
			memcpy(arpbuf.smac,mac_addr,6); 								//发送端以太网地址
			memcpy(arpbuf.sipaddr,ip_addr,4);								//发送端IP地址
			memcpy(arpbuf.dipaddr,host_ip_addr,4);					//目的IP地址

			packet_len = 42;
			
		
			dm9000_tx(buffer,packet_len);
			
		

}





/*2.解析ARP应答包*/
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



/*2.解析ARP应答包*/
u8 arp_printf()
{
    printf("jhony :");
	
	}




