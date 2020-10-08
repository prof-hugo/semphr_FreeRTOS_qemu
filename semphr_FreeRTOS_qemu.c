/*==================================================================================================

  semphr_FreeRTOS_qemu.c

  Used hardware: STM32F4-Discovery evaluation board (QEMU)

  Example of using the FreeRTOS Real-Time Operating System on the STM32F4-Discovery board.

  ==================================================================================================
*/

#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


#define BUFFER_SIZE 8


SemaphoreHandle_t xSemFree = NULL;
SemaphoreHandle_t xSemFull = NULL;
uint8_t buffer[BUFFER_SIZE];


void xProdTask(void *pvParam){
  const TickType_t xPeriod = 500 / portTICK_PERIOD_MS;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  uint8_t index_i = 0, data_i = 0;

  while(1){
	xSemaphoreTake(xSemFree, portMAX_DELAY); // is there any free space?
    buffer[index_i] = data_i; // put data
	xSemaphoreGive(xSemFull); // data available

    index_i++; // update input index
    if(index_i >= BUFFER_SIZE)
      index_i = 0;

    // data production
    data_i++;
    data_i &= 0x0F;

	vTaskDelayUntil(&xLastWakeTime, xPeriod);
  } // while
} // xProdTask


void xConsTask(void *pvParam){
  const TickType_t xPeriod = 500 / portTICK_PERIOD_MS;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  uint8_t index_o = 0, data_o;

  while(1){
    xSemaphoreTake(xSemFull, portMAX_DELAY); // is there any data available?
    data_o = buffer[index_o]; // get data
	xSemaphoreGive(xSemFree); // free space

    index_o++; // update output index
    if(index_o >= BUFFER_SIZE)
      index_o = 0;

    // data consumption
    if (data_o & 0x01) BSP_LED_On(LED3);
    else BSP_LED_Off(LED3);

    if (data_o & 0x02) BSP_LED_On(LED4);
    else BSP_LED_Off(LED4);

    if (data_o & 0x04) BSP_LED_On(LED6);
    else BSP_LED_Off(LED6);

    if (data_o & 0x08) BSP_LED_On(LED5);
    else BSP_LED_Off(LED5);

	vTaskDelayUntil(&xLastWakeTime, xPeriod);
  } // while
} // xConsTask


void main(void){
  __HAL_RCC_GPIOD_CLK_ENABLE();
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED6);
  BSP_LED_Init(LED5);

  xTaskCreate(xProdTask, "Producer", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
  xTaskCreate(xConsTask, "Consumer", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
  xSemFree = xSemaphoreCreateCounting(BUFFER_SIZE, BUFFER_SIZE);
  xSemFull = xSemaphoreCreateCounting(BUFFER_SIZE, 0);

  vTaskStartScheduler();
  while(1);
} // main
