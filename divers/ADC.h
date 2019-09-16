/**************************************************************************************************************
 *
 * [FILE NAME]: 	<ADC.h>
 * [AUTHORS]:		<shimaa mahmoud>
 * [DATE CREATED]:	<16/9/2019>
 * [DESCTRIPTION]:	< Header file for the ADC driver >
 *
 **************************************************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

//MUX4:0  = choose channel for initialization
typedef enum
{
	ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7
}ADC_CHANNEL;

typedef enum
{
	RIGHT,LEFT
}ADC_ADJUTMENT;


typedef enum
{
	AREF = 0x00,AVCC = 0x40,INTERNAL_VOLTAGE = 0xc0
}Voltage_Reference;


typedef enum
{
	CLK_2,CLK_2,CLK_4,CLK_8,CLK_16,CLK_32,CLK_64,CLK_128
}ADC_CLK;

typedef enum
{
	DISABLE,ENABLE
}ADC_INTERRUPT;

typedef enum
{
	FREE_RUNNING,ANALOG_COMPARTOR,ENT0,TIMER0_COMP,TIMER0_OVERFLOW,TIMER_COMP_B,TIMER1_OVERFLOW,TIMER1_CAPTURE_EVENT
}ADC_MODE;

typedef struct
{
	Voltage_Reference ref;
	ADC_CLK clock;
	ADC_MODE mode;
	ADC_ADJUTMENT adj;
	ADC_INTERRUPT interrupt;
}Adc_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const Adc_ConfigType * a_Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 a_channel_num)


#endif
