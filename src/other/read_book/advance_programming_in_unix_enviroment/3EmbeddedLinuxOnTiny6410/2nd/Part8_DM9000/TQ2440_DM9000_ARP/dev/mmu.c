/* 
 * 用于段描述符的一些宏定义
 */ 
#define MMU_FULL_ACCESS     (3 << 10)   /* 访问权限 */
#define MMU_DOMAIN          (0 << 5)    /* 属于哪个域 */
#define MMU_SPECIAL         (1 << 4)    /* 必须是1 */
#define MMU_CACHEABLE       (1 << 3)    /* cacheable */
#define MMU_BUFFERABLE      (1 << 2)    /* bufferable */
#define MMU_SECTION         (2 << 0)         /* 段描述符 */
#define MMU_SECDESC         (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_SECTION)
#define MMU_SECDESC_WB      (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_CACHEABLE | MMU_BUFFERABLE | MMU_SECTION)


void create_page_table(void)
{
    unsigned long *ttb = (unsigned long *)0x31000000;
    unsigned long vaddr, paddr;
    
    vaddr = 0x00000000;
    paddr = 0x30000000;
    *(ttb + (vaddr >> 20))= (paddr & 0xfff00000) | MMU_SECDESC_WB; 

    vaddr = 0x56000000;
    paddr = 0x56000000;
    *(ttb + (vaddr >> 20)) = (paddr & 0xFFF00000) | MMU_SECDESC;
    
    vaddr = 0x4A000000;
    paddr = 0x4A000000;
    *(ttb + (vaddr >> 20)) = (paddr & 0xfff00000) | MMU_SECDESC;

    vaddr = 0x30000000;
    paddr = 0x30000000;
    while (vaddr < 0x34000000)
    {
        *(ttb + (vaddr >> 20)) = (paddr & 0xFFF00000) | MMU_SECDESC_WB;
        vaddr += 0x100000;
        paddr += 0x100000;
    }
}

void mmu_enable()
{
   __asm__(
    
    /*设置TTB*/
    "ldr    r0, =0x31000000\n"                  
    "mcr    p15, 0, r0, c2, c0, 0\n"  
    
    /*不进行权限检查*/
    "mvn    r0, #0\n"                   
    "mcr    p15, 0, r0, c3, c0, 0\n"   
    
   /*使能MMU*/
    "mrc    p15, 0, r0, c1, c0, 0\n"    
    "orr    r0, r0, #0x0001\n"          
    "mcr    p15, 0, r0, c1, c0, 0\n"    
    : 
    : 
  );		
}

void mmu_init()
{
    create_page_table();
    mmu_enable();
}


