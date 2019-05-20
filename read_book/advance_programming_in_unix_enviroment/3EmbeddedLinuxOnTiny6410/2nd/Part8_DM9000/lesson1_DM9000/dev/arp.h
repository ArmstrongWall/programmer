#ifndef ARP_H
#define ARP_H

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;


typedef struct eth_hdr
{
			u8 d_mac[6];			//以太网目的地址
			u8 s_mac[6];			//以太网源地址
			u16 type;					//帧类型名


	}ETH_HDR;

/******************
这里的数据结构要仔细定义，很容易出错

*******************/

typedef struct arp_hdr
{
		ETH_HDR ethhdr;			//类型名
		u16     hwtype;			//硬件类型
		u16      protocol;	//协议类型
		u8      hwlen;			//硬件地址长度
		u8      protolen;		//协议地址长度
		u16     opcode;			//op
		u8      smac[6];		//发送端以太网地址
		u8      sipaddr[4];	//发送端IP地址
		u8      dmac[6];		//目的以太网地址
		u8      dipaddr[4];	//目的IP地址
		
	}ARP_HDR;
	
ARP_HDR arpbuf;	
	
extern u8 host_mac_addr[6];
extern u8 mac_addr[6];
extern u8 ip_addr[4];
extern u8 host_ip_addr[4];
extern u8 *buffer;
extern u16 packet_len;


#endif