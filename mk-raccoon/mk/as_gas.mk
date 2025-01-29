# SPDX-License-Identifier: GPL-2.0+
# Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

AS_GAS_FILE		:= $(realpath $(lastword $(MAKEFILE_LIST)))
AS_GAS_DIR		:= $(shell dirname $(AS_GAS_FILE))

# Assemble: create object files from assembler source files.
define RULES_AS
AOBJS_$(1)		:= $(addprefix $(OBJDIR)/,\
	$(patsubst %.$(1),%.o,$(filter %.$(1),$(ASRCS))))
AOBJS			+= $$(AOBJS_$(1))
$$(AOBJS_$(1)): $(OBJDIR)/%.o : %.$(1) | $(OBJDIR)
	@echo
	@echo $(MSG_COMPILING) $$<
	$(CC) -c -Wa,-adhlns=$$(@:.o=.lst) $(ALL_ASFLAGS) $$< -o $$@
endef

$(foreach EXT, $(EXT_AS), $(eval $(call RULES_AS,$(EXT))))
