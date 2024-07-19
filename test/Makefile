PROG = $(patsubst %.cpp,%,$(wildcard *.cpp))
PHPPROG = $(wildcard *.php)
# OBS = $(wildcard ../obj/*.o)

include $(shell echo $${PREFIX-/usr})/share/smartmet/devel/makefile.inc

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
	rm -rf .obj

test: $(PROG)
	@echo Running tests:
	@failed=; for prog in $(PROG); do \
	 ./$$prog || failed="$$failed $$prog"; \
	done; \
	if test -z "$$failed" ; then true; else echo Test failed:; \
		for test in $$failed; do echo "   $$test"; done; false; fi

$(PROG) : % : .obj/%.o
	$(CXX) $(CFLAGS) -o $@ $@.cpp $(INCLUDES) $(LIBS)

.obj/%.o: %.cpp
	@mkdir -p .obj
	$(CXX) $(CFLAGS) $(INCLUDES) -c -MD -MF $(patsubst obj/%.o, .obj/%.d, $@) -MT $@ -o $@ $<

ifneq ($(wildcard .obj/*.d),)
-include $(wildcard .obj/*.d)
endif
