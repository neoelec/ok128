PRJ_FRTOS_MK_FILE	:= $(realpath $(lastword $(MAKEFILE_LIST)))
PRJ_FRTOS_MK_DIR	:= $(shell dirname $(PRJ_FRTOS_MK_FILE))

MCU			:= atmega128
F_CPU			:= 16000000

FRTOSLIB		:= $(PRJ_FRTOS_MK_DIR)/libs
EXTRAINCDIRS		+= $(FRTOSLIB)
VPATH			+= $(FRTOSLIB)

FREERTOS_PATH		:= $(HOME)/iHDD00/07.WORKSPACE/FreeRTOS-LTS/FreeRTOS
FREERTOS_KERNEL_PATH	:= $(FREERTOS_PATH)/FreeRTOS-Kernel
EXTRAINCDIRS		+= $(FREERTOS_KERNEL_PATH)/include
VPATH			+= $(FREERTOS_KERNEL_PATH)
VPATH			+= $(FREERTOS_KERNEL_PATH)/portable/MemMang
CSRCS			+= croutine.c event_groups.c list.c queue.c stream_buffer.c tasks.c timers.c
CSRCS			+= heap_1.c

FREERTOS_PORT_PATH	:= $(FREERTOS_KERNEL_PATH)/portable/GCC/ATMega323
EXTRAINCDIRS		+= $(FREERTOS_PORT_PATH)
VPATH			+= $(FREERTOS_PORT_PATH)
CSRCS			+= port.c

include $(MK_RACCOON_DIR)/gcc_avr.mk
