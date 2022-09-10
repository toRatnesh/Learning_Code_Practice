
MK = Makefile

SRCDIR = ./
OBJDIR = ./
INCDIR = ./
BINDIR = ./
BINNAME = constexpr

CPPSRCFILES := main.cpp fun.cpp
CPPSRCDIRS := $(sort $(dir $(wildcard $(CPPSRCFILES))))

TEMPDIRS = $(CPPSRCDIRS) 
SRCDIRS = $(sort $(TEMPDIRS))

CPPOBJFILES := $(addprefix $(OBJDIR), $(notdir $(CPPSRCFILES:.cpp=.o)))
OBJS :=  $(CPPOBJFILES) 

CXX = g++ -std=c++17 -g -Wall -Wextra -Wpedantic -Wconversion
.PHONY: ALL
ALL : $(BINDIR)$(BINNAME)

$(BINDIR)$(BINNAME) : $(OBJS)
	$(info Creating and linking executable --- $(BINDIR)$(BINNAME))
	@$(CXX) $^ -o $@ 

vpath %.cpp $(SRCDIRS)

$(OBJDIR)%.o : %.cpp
	$(info Compiling source file --- $<)
	@$(CXX) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(BINDIR)$(BINNAME)

#######################
#	END OF FILE
#######################
