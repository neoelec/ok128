# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# WinAVR Makefile Template written by Eric B. Weddington, Jörg Wunsch, et al.
#
# Released to the Public Domain
#
# Additional material for this makefile was written by:
# Peter Fleury
# Tim Henigan
# Colin O'Flynn
# Reiner Patommel
# Markus Pfaff
# Sander Pool
# Frederik Rouleau
#
#----------------------------------------------------------------------------
# On command line:
#
# make program = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
#----------------------------------------------------------------------------

#---------------- Programming Options (avrdude) ----------------

# Programming hardware: alf avr910 avrisp bascom bsd
# dt006 pavr picoweb pony-stk200 sp12 stk200 stk500
#
# Type: avrdude -c ?
# to get a full listing.
#
AVRDUDE_PROGRAMMER	?= usbtiny

# com1 = serial port. Use lpt1 to connect to parallel port.
#AVRDUDE_PORT		:= -P com1	# programmer connected to serial device
AVRDUDE_PORT		?=

AVRDUDE_WRITE_FLASH	:= -U flash:w:$(OUTPUT).hex
AVRDUDE_WRITE_EEPROM	:= -U eeprom:w:$(OUTPUT).eep

# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER	:= -y
AVRDUDE_ERASE_COUNTER	?=

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_NO_VERIFY	:= -V
AVRDUDE_NO_VERIFY	?=

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude>
# to submit bug reports.
#AVRDUDE_VERBOSE	:= -v -v
AVRDUDE_VERBOSE		?=

AVRDUDE_FLAGS		+= -p $(MCU) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_FLAGS		+= $(AVRDUDE_PORT)
AVRDUDE_FLAGS		+= $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS		+= $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS		+= $(AVRDUDE_ERASE_COUNTER)

#============================================================================

# Define programs and commands.
AVRDUDE			:= avrdude

#============================================================================

# Program the device.
program: build
	@$(AVRDUDE) $(AVRDUDE_FLAGS) \
		`if [ -f $(OUTPUT).hex ]; then echo "$(AVRDUDE_WRITE_FLASH)"; fi` \
		`if [ -f $(OUTPUT).eep ]; then echo "$(AVRDUDE_WRITE_EEPROM)"; fi`

# Listing of phony targets.
.PHONY : program
