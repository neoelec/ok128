OK128C_MK_FILE	:= $(realpath $(lastword $(MAKEFILE_LIST)))
OK128C_PATH	:= $(shell dirname $(OK128C_MK_FILE))

MCU		:= atmega128
F_CPU		:= 16000000

OK128CLIB	:= $(OK128C_PATH)/libs
EXTRAINCDIRS	+= $(OK128CLIB)
VPATH		+= $(OK128CLIB)

include $(OK128C_PATH)/../avr.mk
