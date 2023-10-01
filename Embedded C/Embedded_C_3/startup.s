/* Author Eng : Menna Gabely
 startup_cortex-M3.s */

/* SRAM 0X20000000 */

.section .vectors

.word 0X20001000                                    //Stack Top Address
.word _reset                                        //Reset
.word Vecror_handler                              //NMI
.word Vecror_handler                             //Hard Fault 
.word Vecror_handler                            //MM Fault
.word Vecror_handler                           //Bus Fault      
.word Vecror_handler                          //Usage Fault
.word Vecror_handler                         //RESERVED
.word Vecror_handler                        //RESERVED
.word Vecror_handler                       //RESERVED
.word Vecror_handler                      //RESERVED
.word Vecror_handler                     //SV call
.word Vecror_handler                    //Debug RESERVED       
.word Vecror_handler                   //RESERVED
.word Vecror_handler                  //PandSV
.word Vecror_handler                 //SysTick
.word Vecror_handler                //IRQ0
.word Vecror_handler               //IRQ1
.word Vecror_handler              //IRQ2
.word Vecror_handler             //IRQ.....
                /* ON TO IRQ67 */

.section .text
_reset: 
	bl main
	b .

.thumb_func
Vecror_handler:
	b _reset
	