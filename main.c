/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 



/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usbd_hid_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "stdlib.h"

#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

/** @addtogroup STM32F4-Discovery_USB_HID
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_CDR_Address    ((uint32_t)0x40012308)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment = 4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;
  
__IO uint8_t UserButtonPressed = 0x00;
uint8_t InBuffer[64], OutBuffer[63];



/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

int brightLed1 = 0;
int brightLed2 = 0;
int brightLed3 = 0;
int delta = 1;
int delta2 = 5;
int delta3 = 2;

void init();
void loop();
void delay();
void initLeds();
void initTimer();
void initPWM();



int main(void)
{
  init();
  /*STM32F4_Discovery_LEDInit(LED3);
  STM32F4_Discovery_LEDInit(LED4);
  STM32F4_Discovery_LEDInit(LED5);
  STM32F4_Discovery_LEDInit(LED6);*/
  STM32F4_Discovery_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

 /* STM32F4_Discovery_LEDOn(LED3);
  Delay1(0xFFFF);
  STM32F4_Discovery_LEDOff(LED3);*/

  USBD_Init(&USB_OTG_dev,
#ifdef USE_USB_OTG_HS
  USB_OTG_HS_CORE_ID,
#else
  USB_OTG_FS_CORE_ID,
#endif
  &USR_desc,
  &USBD_HID_cb,
  &USR_cb);
  int val1=0;
  int val2=0;
  int val3=0;
  char button=0;
  while (1)
  {
	  int val;
	  Delay1(0xFF);

	  /*if (OutBuffer[3]&1)  	STM32F4_Discovery_LEDOn(LED3);
		  	  else			STM32F4_Discovery_LEDOff(LED3);
	  if (OutBuffer[3]&2)  	STM32F4_Discovery_LEDOn(LED4);
		  	  else			STM32F4_Discovery_LEDOff(LED4);
	  if (OutBuffer[3]&4)  	STM32F4_Discovery_LEDOn(LED5);
		  	  else			STM32F4_Discovery_LEDOff(LED5);
	  if (OutBuffer[3]&8)  	STM32F4_Discovery_LEDOn(LED6);
		  	  else			STM32F4_Discovery_LEDOff(LED6);*/

	  char hlp1[2];
	  char hlp2[3];
	  char hlp3[1];

	  if(OutBuffer[0]=='0' && OutBuffer[1]=='0')
	  	{
	  		hlp3[0]=OutBuffer[2];
	  		val=atoi(hlp3);
	  	}
	  	else if(OutBuffer[0]=='0' && OutBuffer[1]!='0')
	  	{
	  		hlp1[0]=OutBuffer[1];
	  		hlp1[1]=OutBuffer[2];
	  		val=atoi(hlp1);
	  	}
	  	else
	  	{
	  		hlp2[0]=OutBuffer[0];
	  		hlp2[1]=OutBuffer[1];
	  		hlp2[2]=OutBuffer[2];
	  		val=atoi(hlp2);
	  	}

	  /*switch(brightLed1) {
	        case 499: delta=-1; break;
	        case 1: delta=1; break;
	    }
	    switch(brightLed2) {
	            case 495: delta2=-5; break;
	            case 10: delta2=5; break;
	        }
	    switch(brightLed3) {
	                case 498: delta3=-2; break;
	                case 2: delta3=2; break;
	            }*/

	    if(OutBuffer[3]=='0' && OutBuffer[4]=='1')val1=val;
	    if(OutBuffer[3]=='0' && OutBuffer[4]=='2')val2=val;
	    if(OutBuffer[3]=='0' && OutBuffer[4]=='3')val3=val;

	    brightLed1 = val1;
	    brightLed2 = val2;
	    brightLed3 = val3;

	      TIM_SetCompare4(TIM4, brightLed3);
	      TIM_SetCompare1(TIM4, brightLed2);
	      TIM_SetCompare3(TIM4, brightLed1);

	      delay(4);

	/* if (val>0 && val < 10)
		  {
		  	 STM32F4_Discovery_LEDOn(LED4);
		  	 STM32F4_Discovery_LEDOff(LED3);
		  	 STM32F4_Discovery_LEDOff(LED5);
		   	 STM32F4_Discovery_LEDOff(LED6);
		  }
	  if(val>=10 && val<100)
	  {
		   STM32F4_Discovery_LEDOn(LED3);
		   STM32F4_Discovery_LEDOn(LED4);
		   STM32F4_Discovery_LEDOff(LED5);
		   STM32F4_Discovery_LEDOff(LED6);
	  }
	  if(val>=100 && val<200)
	  {
		  STM32F4_Discovery_LEDOn(LED3);
		  STM32F4_Discovery_LEDOn(LED4);
		  STM32F4_Discovery_LEDOn(LED5);
		  STM32F4_Discovery_LEDOff(LED6);
	  }
	  if(val>=200)
	  {
		  STM32F4_Discovery_LEDOn(LED3);
		  STM32F4_Discovery_LEDOn(LED4);
		  STM32F4_Discovery_LEDOn(LED5);
		  STM32F4_Discovery_LEDOn(LED6);
	  }*/

	  if ((STM32F4_Discovery_PBGetState(BUTTON_USER) == Bit_SET)&&(button==0))

	  {
			  int i=0;

			  Delay1(0xFF);
			  while (i<64)
			  {
				  InBuffer[i]=i+65;
				  i++;
			  }
			  USBD_HID_SendReport (&USB_OTG_dev, InBuffer, 64);
	  }
	  button = STM32F4_Discovery_PBGetState(BUTTON_USER);
  }
}


void init() {
    initLeds();
    initTimer();
    initPWM();
}
void delay(uint32_t ms) {
    ms *= 3360;
    while(ms--) {
        __NOP();
    }
}
void initLeds() {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
}
void initTimer() {
    /* TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    /* Compute the prescaler value */
    u32 PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 21000000) - 1;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 1000;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}

void initPWM() {
    TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    /* PWM1 Mode configuration: Channel2 (GPIOD Pin 13)*/
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel4 (GPIOD Pin 15)*/
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_Cmd(TIM4, ENABLE);
}


/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length.
  * @retval None
  */

void Delay1(__IO uint32_t nTime)
{
  if (nTime != 0x00)
  { 
    nTime--;
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
