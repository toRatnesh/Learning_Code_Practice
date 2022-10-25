
MK = Makefile

SRCDIR = ./
OBJDIR = obj/
INCDIR = /usr/include/libxml2
BINDIR = bin/
BINNAME = parse_xml

CSRCFILES := ./parse_xml.c
CSRCDIRS := $(sort $(dir $(wildcard $(CSRCFILES))))

TEMPDIRS = $(CSRCDIRS) 
SRCDIRS = $(sort $(TEMPDIRS))

#$(info ...............)
#$(info C source files are --- $(CSRCFILES))
#$(info ...............)
#$(info C file source directories are -- $(CSRCDIRS))
#$(info ...............)
#$(info Source file directories are -- $(SRCDIRS))
#$(info ...............)

COBJFILES := $(addprefix $(OBJDIR), $(notdir $(CSRCFILES:.c=.o)))
OBJS :=  $(COBJFILES) 

#$(info Object files are -- $(OBJS))
#$(info ...............)

INCDIRS := $(shell find $(INCDIR) -not -path '*/\.*' -type d -name '*')
#$(info Include directories are -- $(INCDIRS))
#$(info ...............)

INCLUDEDIRS := $(foreach dir, $(INCDIRS), -I$(dir)/)

CC = gcc -std=c11 -g -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address
LIBS = -lxml2
.PHONY: ALL
ALL : $(BINDIR)$(BINNAME)

$(BINDIR)$(BINNAME) : $(OBJS)
	$(info Creating and linking executable --- $(BINDIR)$(BINNAME))
	@$(CC) $^ -o $@ $(LIBS) $(PROJLIBS) $(LINKERFLAGS) $(OPTIMIZATIONFLAGS)

vpath %.c $(SRCDIRS)

$(OBJDIR)%.o : %.c
	$(info Compiling source file --- $<)
	@$(CC) $(COMPILATIONFLAGS) $(INCLUDEDIRS) $(OPTIMIZATIONFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(OBJS)
	rm $(BINDIR)$(BINNAME)

#######################
#	END OF FILE
#######################
