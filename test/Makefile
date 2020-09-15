PROG = $(patsubst %.cpp,%,$(wildcard *.cpp))
PHPPROG = $(wildcard *.php)
# OBS = $(wildcard ../obj/*.o)

include ../common.mk

FLAGS = -std=$(CXX_STD) -Wall -W -Wno-unused-parameter

EXTRAFLAGS = -Werror -pedantic -Wpointer-arith -Wcast-qual \
	-Wcast-align -Wwrite-strings -Wconversion -Winline \
	-Wctor-dtor-privacy -Wnon-virtual-dtor -Wno-pmf-conversions \
	-Wsign-promo -Wchar-subscripts -Wold-style-cast \
	-Wshadow -Woverloaded-virtual

DIFFICULTFLAGS = -Weffc++ -Wunreachable-code -Wredundant-decls

UNAME_S := $(shell uname -s)

ifeq ($(TSAN), yes)
  FLAGS += -fsanitize=thread
endif
ifeq ($(ASAN), yes)
  FLAGS += -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=undefined -fsanitize-address-use-after-scope
endif

CFLAGS = -DUNIX -O0 -g $(FLAGS)

INCLUDES += \
	-I/usr/include/smartmet

LIBS += \
	../libsmartmet-calculator.so \
	-lsmartmet-newbase \
	-lsmartmet-macgyver \
	-lboost_iostreams \
	-lboost_locale \
	-lboost_system


INCLUDES += -I ../calculator

all: $(PROG)
clean:
	rm -f $(PROG) *~

test: $(PROG)
	@echo Running tests:
	@for prog in $(PROG); do \
	 ./$$prog; \
	done

$(PROG) : % : %.cpp ../libsmartmet-calculator.so
	$(CXX) $(CFLAGS) -o $@ $@.cpp $(INCLUDES) $(LIBS)

