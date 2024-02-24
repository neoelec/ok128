// refernece : https://blackinkgj.github.io/atmega128-freertos/

#include <avr/io.h>

#include <FreeRTOS.h>
#include <task.h>

static void prvLEDinit( void )
{
	DDRB = 0xFF;
	PORTB = 0x00;
}

static void prvLEDtoggle( unsigned int num )
{
	PORTB ^= ( 0x1 << ( 0x4 + num ) );
}

static void prvLEDFlashTask0( void *pvParameters )
{
portTickType xLastWakeTime;
const portTickType xFrequency = 200;

	xLastWakeTime = xTaskGetTickCount();
	while ( 1 )
	{
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		prvLEDtoggle( 0 );
	}
}

static void prvLEDFlashTask1( void *pvParameters )
{
portTickType xLastWakeTime;
const portTickType xFrequency = 300;

	xLastWakeTime = xTaskGetTickCount();
	while ( 1 )
	{
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		prvLEDtoggle( 1 );
	}
}

static void prvLEDFlashTask2( void *pvParameters )
{
portTickType xLastWakeTime;
const portTickType xFrequency = 400;

	xLastWakeTime = xTaskGetTickCount();
	while ( 1 )
	{
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		prvLEDtoggle( 2 );
	}
}

static void prvLEDFlashTask3( void *pvParameters )
{
portTickType xLastWakeTime;
const portTickType xFrequency = 500;

	xLastWakeTime = xTaskGetTickCount();
	while ( 1 )
	{
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		prvLEDtoggle( 3 );
	}
}

int main(void)
{
	prvLEDinit();

	xTaskCreate( prvLEDFlashTask0, "LED0", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( prvLEDFlashTask1, "LED1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( prvLEDFlashTask2, "LED2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( prvLEDFlashTask3, "LED3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );

	vTaskStartScheduler();

	return 0;
}
