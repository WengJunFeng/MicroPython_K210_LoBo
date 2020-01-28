/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
* FreeRTOS Kernel V10.0.1
* Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* http://www.FreeRTOS.org
* http://aws.amazon.com/freertos
*
* 1 tab == 4 spaces!
*/

/*
 * LoBo: various changes for use with MicroPython
 * 
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H
/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#include <stdint.h>

#define configSYSLOG_EXTERNAL_SYS_TICKS

/* clock */
#define configCPU_CLOCK_HZ					    sysctl_clock_get_freq(SYSCTL_CLOCK_CPU)
#define configTICK_CLOCK_HZ					    ( configCPU_CLOCK_HZ / 50 )
#define configTICK_RATE_HZ					    ( ( TickType_t ) 1000 )

/* multithreading */
#define configUSE_NEWLIB_REENTRANT				1

#define configUSE_PREEMPTION					1
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1   //ToDo: set to 1 ?
#endif
#define configMAX_PRIORITIES					( 16 )
#define configMAX_TASK_NAME_LEN					( 16 )
#define configUSE_TRACE_FACILITY				1
#define configUSE_16_BIT_TICKS					0
#define configIDLE_SHOULD_YIELD					0
#define configQUEUE_REGISTRY_SIZE				8

/* TLS */
enum
{
    PTHREAD_TLS_INDEX = 0
};

#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 2

/* mutex */
#define configUSE_MUTEXES						1
#define configUSE_RECURSIVE_MUTEXES				1

/* hooks */
#define configUSE_MALLOC_FAILED_HOOK			0
#define configUSE_IDLE_HOOK						1
#define configUSE_TICK_HOOK						0
#define configUSE_DAEMON_TASK_STARTUP_HOOK		0

/* memory */

/* If configAPPLICATION_ALLOCATED_HEAP is set to 1,
   the application writer must provide a HeapRegion_t structure
   and call vPortDefineHeapRegions() to initialize the heap.
   If set to 0, configTOTAL_HEAP_SIZE must be defined here
   and the heap array of that size will be created internally
   and one-region heap will be created on first execution of pvPortMalloc
 */
#define configAPPLICATION_ALLOCATED_HEAP        1
#if ( configAPPLICATION_ALLOCATED_HEAP == 0 )
#define configTOTAL_HEAP_SIZE                   ( ( size_t ) ( 1024 * 1024 ) )
#endif

#define configMINIMAL_STACK_SIZE			    ( ( unsigned short ) 1024 )
#define configSUPPORT_STATIC_ALLOCATION			1
#define configSUPPORT_DYNAMIC_ALLOCATION		1

#define configUSE_APPLICATION_TASK_TAG			1
#define configUSE_COUNTING_SEMAPHORES			1
#define configUSE_TICKLESS_IDLE					1
#define configUSE_STATS_FORMATTING_FUNCTIONS	1

/* If set to 1, external functions must be provided:
 * vConfigureTimerForRunTimeStats & vGetRunTimeCounterValue
 */
#define configGENERATE_RUN_TIME_STATS           1
#if ( configGENERATE_RUN_TIME_STATS == 1 )
extern void vConfigureTimerForRunTimeStats( void );
extern uint64_t vGetRunTimeCounterValue();
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() vGetRunTimeCounterValue()
#endif

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 					0
#define configMAX_CO_ROUTINE_PRIORITIES			( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS						0
#define configTIMER_TASK_PRIORITY				( 0 )
#define configTIMER_QUEUE_LENGTH				2
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE )

/* Main task */
#define configMAIN_TASK_PRIORITY				1
#define configMAIN_TASK_STACK_SIZE				(4096 * 2)

/* Set the following definitions to 1 to include the API function, or zero to exclude the API function. */
#define INCLUDE_vTaskPrioritySet				1
#define INCLUDE_uxTaskPriorityGet				1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskCleanUpResources			1
#define INCLUDE_vTaskSuspend					1
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_eTaskGetState					1
#define INCLUDE_xTaskAbortDelay					1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTimerPendFunctionCall          0
#define INCLUDE_uxTaskGetStackHighWaterMark     1
#define INCLUDE_pxTaskGetStackStart             1

#define configRECORD_STACK_HIGH_ADDRESS         1

#define INCLUDE_xSemaphoreGetMutexHolder        1

/* Diagnostics */
#define configCHECK_FOR_STACK_OVERFLOW          1

/* configASSERT behaviour */
extern void vPortFatal(const char* file, int line, const char* message);
/* Normal assert() semantics without relying on the provision of an assert.h header file. */
#define configASSERT( x ) if( ( x ) == 0 ) {           \
    vPortFatal(__FILE__, __LINE__, #x);				   \
}

#endif /* FREERTOS_CONFIG_H */
