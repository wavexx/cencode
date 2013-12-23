# Makefile for cencode (for pmake or gmake)
# Copyright(c) 2006-2008 by wave++ (Yuri D'Elia) <wavexx@thregr.org>
# Distributed under Revised BSD license without ANY warranty.

# configuration
TARGETS := cencode
all: $(TARGETS)

CENCODE_OBJECTS := cencode.o


# parameters
CPPFLAGS += -MD
CXXFLAGS += $(CWARN)


# suffixes, rules
CXXCOMPILE = $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
CXXLINK = $(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@

.SUFFIXES: .cc .o

.cc.o:
	$(CXXCOMPILE)


# targets
cencode: $(CENCODE_OBJECTS)
	$(CXXLINK) $(CENCODE_OBJECTS)


# stubs
.PHONY: all clean distclean
clean:
	rm -rf $(TARGETS) core *.[do]

distclean: clean
	rm -rf *[#~]

sinclude *.d
