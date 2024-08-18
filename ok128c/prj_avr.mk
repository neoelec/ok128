PRJ_AVR_MK_FILE		:= $(realpath $(lastword $(MAKEFILE_LIST)))
PRJ_AVR_MK_DIR		:= $(shell dirname $(PRJ_AVR_MK_FILE))

MK_RACCOON_DIR		:= $(HOME)/iHDD00/08.PROJECT/mk-raccoon

MCU			:= atmega128
F_CPU			:= 16000000

CROSS_COMPILE		:= avr-
CSTANDARD		:= -std=gnu11
CXXSTANDARD		:= -std=gnu++11
CDEFS			+= -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL

OK128CLIB		:= $(PRJ_AVR_MK_DIR)/libs
EXTRAINCDIRS		+= $(OK128CLIB)
VPATH			+= $(OK128CLIB)

include $(MK_RACCOON_DIR)/gcc_avr.mk
