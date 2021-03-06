//------------------------------------------------------------------------------
//------------------------------INCLUDES----------------------------------------
//------------------------------------------------------------------------------
#include "analog_reading_manager.h"
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES PRIVADAS-------------------------
//------------------------------------------------------------------------------
#define ADC1_DR_Address           ((uint32_t)0x4001244C)
#define NUM_ADC_READ_CHANNELS     3
#define BATTERY_VOLTAGE           ADCConvertedValue[0]
#define WIRED_LDR1_READING_VALUE  ADCConvertedValue[1]
#define WIRED_LDR2_READING_VALUE  ADCConvertedValue[2]
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES INTERNAS-------------------------
//------------------------------------------------------------------------------
ADC_InitTypeDef ADC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
__IO uint16_t   ADCConvertedValue[NUM_ADC_READ_CHANNELS];
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES EXTERNAS-------------------------
//------------------------------------------------------------------------------
 
//------------------------------------------------------------------------------
//-----------------PROTOTIPOS DE FUNCIONES PRIVADAS-----------------------------
//------------------------------------------------------------------------------
void RCC_Configuration(void);
void GPIO_Configuration(void);
//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES PRIVADAS-----------------------------
//------------------------------------------------------------------------------
/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* ADCCLK = PCLK2/4 */
  RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
  /* Enable peripheral clocks ------------------------------------------------*/
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Enable ADC1 and GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
}
//------------------------------------------------------------------------------
/**
  * @brief  Configures the different GPIO ports as analog inputs.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure BATTERY_READING_PIN and LDR_PIN as analog input ---------------*/
  GPIO_InitStructure.GPIO_Pin  = BATTERY_READING_PIN | WIRED_LDR1_PIN | 
                                 WIRED_LDR2_PIN;
  GPIO_InitStructure.GPIO_Mode = ANALOG_READING_MODE;
  GPIO_Init(ANALOG_READING_PORT, &GPIO_InitStructure);
}
//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES PUBLICAS----------------------------
//------------------------------------------------------------------------------
void analog_reading__init(void)
{
  /* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();
  
  /* DMA1 channel1 configuration----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 3;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /* --------------------------- ADC1 configuration --------------------------*/
  
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 3;
  ADC_Init(ADC1, &ADC_InitStructure);
  
   /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, BATTERY_ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, WIRED_LDR1_ADC_CHANNEL, 2, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, WIRED_LDR2_ADC_CHANNEL, 3, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  
  /* -------------------- Start ADCs calibrations --------------------------- */
  
  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));

  /* --------------------- Start ADCs convertions ----------------------------*/
  
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
//------------------------------------------------------------------------------
uint8_t analog_reading__get_battery_voltage(uint16_t *battery_voltage)
{
  *battery_voltage = BATTERY_VOLTAGE;
  return(1);
}
//------------------------------------------------------------------------------
uint8_t analog_reading__get_ldr1_reading(uint16_t *wired_ldr1_reading_value)
{
  *wired_ldr1_reading_value = WIRED_LDR1_READING_VALUE;
  return(1);
}
//------------------------------------------------------------------------------
uint8_t analog_reading__get_ldr2_reading(uint16_t *wired_ldr2_reading_value)
{
  *wired_ldr2_reading_value = WIRED_LDR2_READING_VALUE;
  return(1);
}
//------------------------------------------------------------------------------
//----------------------------END OF FILE---------------------------------------
//------------------------------------------------------------------------------