//char *buf = "hello world";

int gboot_main()
{
    int num;
#ifdef MMU_ON
    mmu_init();
#endif
    led_init();
    button_init();
    init_irq();
    
    uart_init();
    
    ts_init();
    
    //lcd_init(); 
    
    //lcd_test();
    
    dm9000_init();
    dm9000_arp();
   
    while(1)
    {
    	
	printf("\n***************************************\n\r");
    	printf("\n*****************GBOOT*****************\n\r");
    	printf("1:Download Linux Kernel from TFTP Server!\n\r");
    	printf("2:Boot Linux from RAM!\n\r");
    	printf("3:Boor Linux from Nand Flash!\n\r");
    	printf("\n Plese Select:");
    	
    	scanf("%d",&num);
    
        switch (num)
        {
            case 1:
            //tftp_load();
            break;
            
            case 2:
            //boot_linux_ram();
            break;
            
            case 3:
            //boot_linux_nand();
            break;
            
            default:
                printf("Error: wrong selection!\n\r");
            break;	
        }
    	
    }
    return 0;    
}


