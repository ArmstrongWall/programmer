@Platform:   					Friendly Arm tiny6410
@CPU: 		   					S3C6410
@Function: 	 					Init SDRAM Memory,tiny6410 use DDR
@Written by: 					Armstrong Wall
@Start wrirte date:   2016.3.2
@Daily:               2016.3.2 Finish


.text 									@indicate this is code segment
.global mem_init 				@
mem_init:

  @set MEM_SYS_CFG bit 7 Set usage of Xm1DATA[31:16] pins.0 is data field
	ldr r0, =0x7E00F120	
	mov r1, #0x0					
	str r1, [r0]

	ldr r0, =0x7e001004		
	mov r1, #0x4					@Program memc_cmd to 0b100, which makes DRAM Controller enter ¡®Config¡¯ state.
	str r1, [r0]
	
	@next is Write memory timing parameter, chip configuration, and id configuration registers.
	@we follow U-boot\cpu\s3c64xx\s3c6410 cpu_init.S
	
	ldr r0, =0x7e001010   @The Memory address 32-bit DRAM controller refresh period register
  ldr r1, =( ( 7800 / ( 1000000000/133000000 ) + 1 ) )      @ set Memory refresh period in memory clock cycles
  str r1, [r0]

  ldr r0, =0x7e001014  @CAS latency Reg
  mov r1, #(3 << 1)
  str r1, [r0]

  ldr r0, =0x7e001018  @t_DQSS Reg
  mov r1, #0x1
  str r1, [r0]

  ldr r0, =0x7e00101c  @T_MRD Reg
  mov r1, #0x2
  str r1, [r0]

  ldr r0, =0x7e001020   @t_RAS Reg
  ldr r1, =( ( 45 / ( 1000000000 / 133000000 ) + 1 ) )
  str r1, [r0]

  ldr r0, =0x7e001024   @t_RC Reg
  ldr r1, =( ( 68 / ( 1000000000 / 133000000 ) + 1 ) )
  str r1, [r0]

  ldr r0, =0x7e001028   @t_RCD Reg
  ldr r1, =( ( 23 / ( 1000000000 / 133000000 ) + 1 ) )
  str r1, [r0]

  ldr r0, =0x7e00102c   @t_RFC Reg
  ldr r1, =( ( 80 / ( 1000000000 / 133000000 ) + 1 ) )
  str r1, [r0]

  ldr r0, =0x7e001030   @t_RP Reg
  ldr r1, =( ( 23 / ( 1000000000 / 133000000 ) + 1 ) )
  str r1, [r0]

  ldr r0, =0x7e001034   @t_rrd Reg
  ldr r1, =( ( 15 / ( 1000000000 / 133000000 ) + 1 ) )
  str r1, [r0]

  ldr r0, =0x7e001038   @t_wr Reg
  ldr r1, =( ( 15 / ( 1000000000 / 133000000 ) + 1 ) )
@  ldr r2, [r0]
  str r1, [r0]

  ldr r0, =0x7e00103c   @t_wtr Reg
  mov r1, #0x07
  str r1, [r0]

  ldr r0, =0x7e001040   @t_xp Reg
  mov r1, #0x02
  str r1, [r0]

  ldr r0, =0x7e001044   @t_xsr Reg
  ldr r1, =( ( 120 / ( 1000000000 / 133000000 ) + 1 ) )
  str r1, [r0]

  ldr r0, =0x7e001048   @t_esr Reg
  ldr r1, =( ( 120 / ( 1000000000 / 133000000 ) + 1 ) )
  str r1, [r0]

  ldr r0, =0x7e00100c   
  ldr r1, =0x00010012   
  str r1, [r0]

  ldr r0, =0x7e00104c   
  ldr r1, =0x0b45
  str r1, [r0]

  ldr r0, =0x7e001200   @CS Reg
  ldr r1, =0x150f8
  str r1, [r0]

  ldr r0, =0x7e001304   @user config Reg
  mov r1, #0x0
  str r1, [r0]
  
  ldr r0, =0x7e001008   @makes DRAM Controller issue ¡®NOP¡¯ memory command
  mov r1, #0xc0000			@Program mem_cmd in direct_cmd to ¡®2¡¯b11¡¯
  str r1, [r0]
  
  ldr r0, =0x7e001008   @makes DRAM Controller issue ¡®Prechargeall¡¯ memory command
  mov r1, #0x0			    @Program mem_cmd in direct_cmd to ¡®2¡¯b00¡¯
  str r1, [r0]
  
  ldr r0, =0x7e001008   @makes DRAM Controller issue ¡®Prechargeall¡¯ memory command
  mov r1, #0x0			    @Program mem_cmd in direct_cmd to ¡®2¡¯b00¡¯
  str r1, [r0]
  
  @Twice makes DRAM Controller issue ¡®Autorefresh¡¯ memory command
  ldr r0, =0x7e001008   
  mov r1, #0x40000     
  str r1, [r0]     
  str r1, [r0]
  
  ldr r0, =0x7e001008   @makes DRAM Controller issue ¡®MRS¡¯ memory command-Bank address for EMRS must be set.
  mov r1, #0xa0000			    
  str r1, [r0]
  
  ldr r0, =0x7e001008   @makes DRAM Controller issue ¡®MRS¡¯ memory command-Bank address for MRS must be set.
  ldr r1, =0x80032			    
  str r1, [r0]
  
  ldr r0, =0x7e001004		
	mov r1, #0x0					@Program memc_cmd to 0b000,  makes DRAM Controller enter ¡®Ready¡¯ state
	str r1, [r0]
	
check_ready:            @Check memory status field in memc_stat until memory status becomes ¡®2¡¯b01¡¯, which means ¡®Ready¡¯.
 	ldr r0, =0x7e001000
 	ldr r1,[r0]	          @Read memc_stat
	mov r2,#0x3						@set r2=0b11
	and r1,r1,r2					@(value of r1)&& 11,clear other bits influence,only want to know last two bits state
	cmp r1,#0x1						@'ready' state
	bne check_ready				@if r1!=01,not ready,branch to check_ready again.
	
	
	mov pc,lr