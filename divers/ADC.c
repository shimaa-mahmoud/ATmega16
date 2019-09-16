/**************************************************************************************************************
 *
 * [FILE NAME]: 	<ADC.C>
 * [AUTHORS]:		<shimaa mahmoud>
 * [DATE CREATED]:	<16/9/2019>
 * [DESCTRIPTION]:	< source file for the ADC driver >
 *
 **************************************************************************************************************/

#include "adc.h"

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

volatile uint16 g_adcResult = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void ADC_init(const Adc_ConfigType * a_Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX |= ((a_Config_Ptr->mode)<<5) | (a_Config_Ptr->ref);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 1 Enable ADC Interrupt
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN) |((a_Config_Ptr->interrupt)<<3) | (a_Config_Ptr->clock)  ;
}

uint16 ADC_readChannel(uint8 a_channel_num)
{
	ADMUX = (ADMUX & 0XE0) | (a_channel_num & 0X07);
	SET_BIT(ADCSRA,ADSC); /* start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* wait for conversion to complete ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* clear ADIF by write '1' to it :) */
	return ADC; /* return the data register */
}
