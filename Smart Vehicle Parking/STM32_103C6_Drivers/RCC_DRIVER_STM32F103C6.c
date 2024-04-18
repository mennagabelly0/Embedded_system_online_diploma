/*
 * debugRCC.c
 *
 *  Created on: Apr 3, 2024
 *      Author: HFCS
 */


#include "RCC_DRIVER_STM32F103C6.h"

/*
Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
Set and cleared by software to control the division factor of the APB low-speed clock
(PCLK1).
Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16
*/
/*
 *
Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
Set and cleared by software to control the division factor of the APB high-speed clock
(PCLK2).
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16
 */
const uint8_t APB_prescaler_Table[8U] = { 0 , 0 , 0 , 0 , 1 , 2 , 3 , 4 } ; // Shift 1 Right == Multiply by 2

/*
Bits 7:4 HPRE: AHB prescaler
Set and cleared by software to control the division factor of the AHB clock.
0xxx: SYSCLK not divided
1000: SYSCLK divided by 2
1001: SYSCLK divided by 4
1010: SYSCLK divided by 8
1011: SYSCLK divided by 16
1100: SYSCLK divided by 64
1101: SYSCLK divided by 128
1110: SYSCLK divided by 256
1111: SYSCLK divided by 512
Note: The prefetch buffer must be kept on when using a prescaler different from 1 on the
AHB clock. Refer to Reading the Flash memory section for more details.
 */
const uint8_t AHB_prescaler_Table[16U] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 } ; // Shift 1 Right == Multiply by 2


/*
 * ===============================================
 * APIs Supported by "MCAL RCC DRIVER"
 * ===============================================
 */

/**================================================================
 * @Fn					-
 * @brief 				-
 * @param[in] 			-
 * @param[in] 			-
 * @retval				-
 * Note					-
 *
 *
 */

uint32_t MCAL_RCC_Get_System_CLK_Frequency(void)
{
/*
Bits 3:2 SWS: System clock switch status
Set and cleared by hardware to indicate which clock source is used as system clock.
00: HSI oscillator used as system clock
01: HSE oscillator used as system clock
10: PLL used as system clock
11: not applicable
*/
	switch((RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		return HSI_RC_CLK ;
		break ;
	case 1:
		//todo need to calculate it HSE user should specify
		return HSE_Clock ;
		break ;
	case 2:
		//todo need to calculate , PLLCLK , PLLMUL , PLL source MUX
		return 16000000 ;
		break ;
	default:
		return 0 ;
		break;
	}
	return 0 ;
}

/**================================================================
 * @Fn					-
 * @brief 				-
 * @param[in] 			-
 * @param[in] 			-
 * @retval				-
 * Note					-
 *
 *
 */

uint32_t MCAL_RCC_Get_HCLK_Frequency(void)
{
	// Bits 7:4 HPRE: AHB prescaler
	/*
	Set and cleared by software to control the division factor of the AHB clock.
	0xxx: SYSCLK not divided
	1000: SYSCLK divided by 2
	1001: SYSCLK divided by 4
	1010: SYSCLK divided by 8
	1011: SYSCLK divided by 16
	1100: SYSCLK divided by 64
	1101: SYSCLK divided by 128
	1110: SYSCLK divided by 256
	1111: SYSCLK divided by 512 */

	return (MCAL_RCC_Get_System_CLK_Frequency() >> AHB_prescaler_Table[ ( ( RCC->CFGR >> 7 )& 0b1111 )] ) ; // The First Shift is Multiplication.
	//*(( RCC->CFGR >>8) & 0b1111) This Is Read Value of AHB  prescaler To Determine index On 2d Upper Array */

}

/**================================================================
 * @Fn					-
 * @brief 				-
 * @param[in] 			-
 * @param[in] 			-
 * @retval				-
 * Note					-
 *
 *
 */

uint32_t MCAL_RCC_Get_PCLK1_Frequency(void)
{
	// Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	return (MCAL_RCC_Get_HCLK_Frequency() >> APB_prescaler_Table[ ( ( RCC->CFGR >> 8 )& 0b111 )] ) ; // The First Shift is Multiplication.


}

/**================================================================
 * @Fn					-
 * @brief 				-
 * @param[in] 			-
 * @param[in] 			-
 * @retval				-
 * Note					-
 *
 *
 */

uint32_t MCAL_RCC_Get_PCLK2_Frequency(void)
{
	//Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	return (MCAL_RCC_Get_HCLK_Frequency() >> APB_prescaler_Table[ ( ( RCC->CFGR >> 11 )& 0b111 )] ) ; // The First Shift is Multiplication.


}
