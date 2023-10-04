 // startup.c  "cortex-Mm"
//  Author Eng : Menna Gabely

#include <stdint.h>
#define STACK_Start_SP 0x20001000
extern int main(void);
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;

void Reset_Handler();
void NMI_Handler() __attribute__((weak , alias ("Default_Handler")));
void Hard_Fault_Handler()  __attribute__((weak , alias ("Default_Handler")));
void MM_Fault()  __attribute__((weak , alias ("Default_Handler")));
void Bus_Fault()  __attribute__((weak , alias ("Default_Handler")));
void Usage_Fault()  __attribute__((weak , alias ("Default_Handler")));

void Default_Handler(void){
	Reset_Handler() ;
};

// reserve stack size
static unsigned long Stack_top[256]; // 256*4 =1024 B

void(* const g_p_fun_vectors[])() __attribute__((section(".vectors"))) = {
	
	(void (*)()) ((unsigned long)Stack_top + sizeof(Stack_top)),
	 &Reset_Handler ,
	 &NMI_Handler ,
	 &Hard_Fault_Handler ,
	 &MM_Fault ,
	 &Bus_Fault ,
	 &Usage_Fault
} ;


void Reset_Handler(void){

	// copy data from ROM to RAM 
	unsigned int DATA_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA ;
	unsigned char* P_src = (unsigned char*)&_E_text ;
	unsigned char* P_dst = (unsigned char*)&_S_DATA ;
	for(int i =0 ; i< DATA_size ; i++){
		*((unsigned char*)P_dst++) = *((unsigned char*)P_src++) ;
	}

	// INIT THE .bss with zero
	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss ;
	P_dst = (unsigned char*)&_S_bss ;
	for(int i =0 ; i< bss_size ; i++){
		*((unsigned char*)P_dst++) = (unsigned char)0;
	}

	// jump to main()
	main();
};