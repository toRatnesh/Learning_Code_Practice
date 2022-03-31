
MK = Makefile

SRCDIR = src/
OBJDIR = obj/
INCDIR = include/
BINDIR = bin/
BINNAME1 = server 
BINNAME2 = client_01 
BINNAME3 = client_02

CPPSRCFILES := $(shell find $(SRCDIR) -type f -name '*.cpp')
CPPSRCDIRS := $(sort $(dir $(wildcard $(CPPSRCFILES))))

TEMPDIRS = $(CPPSRCDIRS) 
SRCDIRS = $(sort $(TEMPDIRS))

#$(info ...............)
$(info CPP source files are --- $(CPPSRCFILES))
#$(info ...............)
#$(info CPP file source directories are -- $(CPPSRCDIRS))
#$(info ...............)
#$(info Source file directories are -- $(SRCDIRS))
#$(info ...............)

CPPOBJFILES := $(addprefix $(OBJDIR), $(notdir $(CPPSRCFILES:.cpp=.o)))
OBJS :=  $(CPPOBJFILES) 

$(info Object files are -- $(OBJS))
#$(info ...............)

INCDIRS := $(shell find $(INCDIR) -not -path '*/\.*' -type d -name '*')
#$(info Include directories are -- $(INCDIRS))
#$(info ...............)

INCLUDEDIRS := $(foreach dir, $(INCDIRS), -I$(dir)/)

CXX = g++ -std=c++17 -g -Wall -Wextra -Wpedantic -Wconversion
LIBS = -lzmq

.PHONY: ALL
ALL : $(BINDIR)$(BINNAME1) $(BINDIR)$(BINNAME2) $(BINDIR)$(BINNAME3) 

$(BINDIR)$(BINNAME1) : $(OBJDIR)server.o
	$(info Creating and linking executable --- $@)
	$(CXX) $^ -o $@ $(LIBS) $(PROJLIBS) $(LINKERFLAGS) $(OPTIMIZATIONFLAGS)

$(BINDIR)$(BINNAME2) : $(OBJDIR)client_01.o
	$(info Creating and linking executable --- $@)
	$(CXX) $^ -o $@ $(LIBS) $(PROJLIBS) $(LINKERFLAGS) $(OPTIMIZATIONFLAGS)

$(BINDIR)$(BINNAME3) : $(OBJDIR)client_02.o
	$(info Creating and linking executable --- $@)
	$(CXX) $^ -o $@ $(LIBS) $(PROJLIBS) $(LINKERFLAGS) $(OPTIMIZATIONFLAGS)

vpath %.cpp $(SRCDIRS)

$(OBJDIR)%.o : %.cpp
	$(info Compiling source file --- $<)
	@$(CXX) $(COMPILATIONFLAGS) $(INCLUDEDIRS) $(OPTIMIZATIONFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(OBJS)
	rm  $(BINDIR)*

#######################
#
#	EOF
#
#######################
