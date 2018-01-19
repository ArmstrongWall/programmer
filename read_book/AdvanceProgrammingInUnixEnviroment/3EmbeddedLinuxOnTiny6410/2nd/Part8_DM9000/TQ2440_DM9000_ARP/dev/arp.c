#include "arp.h"

#define HON(n) ((((u16)((n) & 0xff)) << 8) | (((n) & 0xff00) >> 8))

/*1.发送arp请求包*/
void arp_request()
{
     /*1.构成arp请求包*/
     memcpy(arpbuf.ethhdr.d_mac,host_mac_addr,6);
     memcpy(arpbuf.ethhdr.s_mac,mac_addr,6);
     arpbuf.ethhdr.type = HON(0x0806);
       
     arpbuf.hwtype = HON(1);
     arpbuf.protocol = HON(0x0800);
     
     arpbuf.hwlen = 6;
     arpbuf.protolen = 4;
        
     arpbuf.opcode = HON(1);
 
     memcpy(arpbuf.smac,mac_addr,6);
     memcpy(arpbuf.sipaddr,ip_addr,4);
     memcpy(arpbuf.dipaddr,host_ip_addr,4);

     packet_len = 14+28;
     
     /*2.调用dm9000发送函数，发送应答包*/	
     dm9000_tx(buffer,packet_len);
}


/*2.解析arp应答包，提取mac*/
u8 arp_process()
{

    u32 i;
    
    if (packet_len<28)
        return 0;
    
    memcpy(host_ip_addr,arpbuf.sipaddr,4);
    printf("host ip is : ");
    for(i=0;i<4;i++)
        printf("%03d ",host_ip_addr[i]);
    printf("\n\r");
    
    memcpy(host_mac_addr,arpbuf.smac,6);
    printf("host mac is : ");
    for(i=0;i<6;i++)
        printf("%02x ",host_mac_addr[i]);
    printf("\n\r");

}