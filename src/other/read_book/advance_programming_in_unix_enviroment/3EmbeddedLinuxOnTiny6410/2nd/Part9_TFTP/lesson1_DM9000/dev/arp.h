#ifndef ARP_H
#define ARP_H

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;


typedef struct eth_hdr
{
			u8 d_mac[6];			//��̫��Ŀ�ĵ�ַ
			u8 s_mac[6];			//��̫��Դ��ַ
			u16 type;					//֡������


	}ETH_HDR;

/******************
��������ݽṹҪ��ϸ���壬�����׳���

*******************/

typedef struct arp_hdr
{
		ETH_HDR ethhdr;			//������
		u16     hwtype;			//Ӳ������
		u16      protocol;	//Э������
		u8      hwlen;			//Ӳ����ַ����
		u8      protolen;		//Э���ַ����
		u16     opcode;			//op
		u8      smac[6];		//���Ͷ���̫����ַ
		u8      sipaddr[4];	//���Ͷ�IP��ַ
		u8      dmac[6];		//Ŀ����̫����ַ
		u8      dipaddr[4];	//Ŀ��IP��ַ
		
	}ARP_HDR;
	
ARP_HDR arpbuf;	
	
extern u8 host_mac_addr[6];
extern u8 mac_addr[6];
extern u8 ip_addr[4];
extern u8 host_ip_addr[4];
extern u8 *buffer;
extern u16 packet_len;


#endif