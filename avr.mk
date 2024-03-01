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
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

AVR_MK_FILE		:= $(realpath $(lastword $(MAKEFILE_LIST)))
AVR_PATH		:= $(shell dirname $(AVR_MK_FILE))

# MCU name
MCU			?= atmega128

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
F_CPU			?= 16000000

# Output format. (can be srec, ihex, binary)
FORMAT			?= ihex

# Target file name (without extension).
TARGET			?=

# VPATH variable
VPATH			+=

# List C source files here. (C dependencies are automatically generated.)
CSRCS			+=

# List Assembler source files here.
#     Make them always end in a capital .S.  Files ending in a lowercase .s
#     will not be considered source files but generated files (assembler
#     output from the compiler), and will be deleted upon "make clean"!
#     Even though the DOS/Win* filesystem matches both .s and .S the same,
#     it will preserve the spelling of the filenames, and gcc itself does
#     care about how the name is spelled on its command-line.
ASRCS			+=

# Optimization level, can be [0, 1, 2, 3, s].
#     0 = turn off optimization. s = optimize for size.
#     (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT			?= s

# Debugging format.
#     Native formats for AVR-GCC's -g are dwarf-2 [default] or stabs.
#     AVR Studio 4.10 requires dwarf-2.
#     AVR [Extended] COFF format requires stabs, plus an avr-objcopy run.
DEBUG			?= dwarf-2

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRAINCDIRS		+=

# Compiler flag to set the C Standard level.
#     c89   = "ANSI" C
#     gnu89 = c89 plus GCC extensions
#     c99   = ISO C99 standard (not yet fully implemented)
#     gnu99 = c99 plus GCC extensions
CSTANDARD		?= -std=gnu11

# Place -D or -U options here
CDEFS			+= -DF_CPU=$(F_CPU)UL

# Place -I options here
CINCS			+=

# Output directories
BINDIR			:= bin
OBJDIR			:= obj

# Define all object files.
COBJS			:= $(addprefix $(OBJDIR)/, $(CSRCS:.c=.o))
AOBJS			:= $(addprefix $(OBJDIR)/, $(ASRCS:.S=.o))
CASMS			:= $(COBJS:.o=.s)

# Define all listing files.
CLSTS			:= $(addprefix $(OBJDIR)/, $(CSRCS:.c=.lst))
ALSTS			:= $(addprefix $(OBJDIR)/, $(ASRCS:.S=.lst))

# Define output file
OUTPUT			:= $(addprefix $(BINDIR)/, $(TARGET))

#---------------- Compiler Options ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS			+= -g$(DEBUG)
CFLAGS			+= $(CDEFS) $(CINCS)
CFLAGS			+= -O$(OPT)
CFLAGS			+= -funsigned-char -funsigned-bitfields
CFLAGS			+= -fpack-struct -fshort-enums
CFLAGS			+= -Wall -Wstrict-prototypes -Wno-unused
CFLAGS			+= $(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS			+= $(CSTANDARD)

#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex
#       dump that will be displayed for a given single line of source input.
ASFLAGS			+= -Wa,-gstabs,--listing-cont-lines=100

#---------------- Library Options ----------------
# None pritf options
__PRINTF_LIB_NONE	:=

# Minimalistic printf version
__PRINTF_LIB_MIN	:= -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires MATH_LIB = -lm below)
__PRINTF_LIB_FLOAT	:= -Wl,-u,vfprintf -lprintf_flt

# If this is left blank, then it will use the Standard printf version.
PRINTF_LIB		?= NONE

# None scanf options
__SCANF_LIB_NONE	:=

# Minimalistic scanf version
__SCANF_LIB_MIN		:= -Wl,-u,vfscanf -lscanf_min

# Floating point + %[ scanf version (requires MATH_LIB = -lm below)
__SCANF_LIB_FLOAT	:= -Wl,-u,vfscanf -lscanf_flt

# If this is left blank, then it will use the Standard scanf version.
SCANF_LIB		?= NONE

# Math library options
__MATH_LIB_FALSE	:=
__MATH_LIB_TRUE		:= -lm

MATH_LIB		?= FALSE

#---------------- External Memory Options ----------------

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS	:= -Wl,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS	:= -Wl,--defsym=__heap_start=0x801100,--defsym=__heap_end=0x80ffff
EXTMEMOPTS		+=

#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS			+= -Wl,-Map=$(OUTPUT).map,--cref
LDFLAGS			+= $(EXTMEMOPTS)
LDFLAGS			+= $(__PRINTF_LIB_$(PRINTF_LIB))
LDFLAGS			+= $(__SCANF_LIB_$(SCANF_LIB))
LDFLAGS			+= $(__MATH_LIB_$(MATH_LIB))

#============================================================================

# Define programs and commands.
CROSS_COMPILE		?= avr-
SHELL			:= sh
CC			:= $(CROSS_COMPILE)gcc
OBJCOPY			:= $(CROSS_COMPILE)objcopy
OBJDUMP			:= $(CROSS_COMPILE)objdump
SIZE			:= $(CROSS_COMPILE)size
NM			:= $(CROSS_COMPILE)nm
REMOVE			:= rm -rf
COPY			:= cp

# Define Messages
# English
MSG_ERRORS_NONE		:= Errors: none
MSG_BEGIN		:= -------- begin --------
MSG_END			:= --------  end  --------
MSG_SIZE_BEFORE		:= Size before:
MSG_SIZE_AFTER		:= Size after:
MSG_FLASH		:= Creating load file for Flash:
MSG_EEPROM		:= Creating load file for EEPROM:
MSG_EXTENDED_LISTING	:= Creating Extended Listing:
MSG_SYMBOL_TABLE	:= Creating Symbol Table:
MSG_LINKING		:= Linking:
MSG_COMPILING		:= Compiling:
MSG_ASSEMBLING		:= Assembling:
MSG_CLEANING		:= Cleaning project:

# Compiler flags to generate dependency files.
GENDEPFLAGS		:= -MD -MP -MF .dep/$(@F).d

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS		:= -mmcu=$(MCU) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS		:= -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)

# Default target.
all: build

build: begin gccversion sizebefore $(BINDIR) $(OBJDIR) output sizeafter end

output: elf hex eep lss sym

elf: $(OUTPUT).elf
hex: $(OUTPUT).hex
eep: $(OUTPUT).eep
lss: $(OUTPUT).lss
sym: $(OUTPUT).sym

# Eye candy.
# AVR Studio 3.x does not check make's exit code but relies on
# the following magic strings to be generated by the compile job.
begin:
	@echo
	@echo $(MSG_BEGIN)

end:
	@echo $(MSG_END)
	@echo

$(BINDIR) $(OBJDIR):
	@mkdir $@

# Display size of file.
sizebefore:
	@if test -f $(OUTPUT).elf; then \
		echo; \
		echo $(MSG_SIZE_BEFORE); \
		$(SIZE) --format=berkeley --radix=10 $(OUTPUT).elf 2>/dev/null; \
		echo; \
	fi

sizeafter:
	@if test -f $(OUTPUT).elf; then \
		echo; \
		echo $(MSG_SIZE_AFTER); \
		$(SIZE) --format=berkeley --radix=10 $(OUTPUT).elf 2>/dev/null; \
		echo; \
	fi

# Display compiler version information.
gccversion :
	@$(CC) --version

# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.eep: %.elf
	@echo
	@echo $(MSG_EEPROM) $@
	$(OBJCOPY) -j .eeprom --set-section-flags .eeprom=alloc,load --change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@

# Link: create ELF output file from object files.
.SECONDARY : $(OUTPUT).elf
.PRECIOUS : $(COBJS)
$(BINDIR)/%.elf: $(COBJS) $(AOBJS)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) $^ --output $@ $(LDFLAGS)

# Compile: create object files from C source files.
$(COBJS): $(OBJDIR)/%.o : $(OBJDIR)/%.s
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c -Wa,-adhlns=$(@:.o=.lst) $(ALL_CFLAGS) $< -o $@

# Compile: create assembler files from C source files.
$(CASMS): $(OBJDIR)/%.s : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -S $(ALL_CFLAGS) $< -o $@

# Assemble: create object files from assembler source files.
$(AOBJS): $(OBJDIR)/%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c -Wa,-adhlns=$(@:.o=.lst) $(ALL_ASFLAGS) $< -o $@

# Create preprocessed source for use in sending a bug report.
$(OBJDIR)/%.i : %.c
	$(CC) -E -mmcu=$(MCU) -I. $(CFLAGS) $< -o $@

# Target: clean project.
clean: begin clean_list end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(OBJDIR)
	$(REMOVE) $(BINDIR)
	$(REMOVE) .dep

# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# Listing of phony targets.
.PHONY : all begin end sizebefore sizeafter gccversion \
		build elf hex eep lss sym \
		clean clean_list
