# DIRECTORIES
SRC = src
INC = include
BUILD = build
LIB = lib
OUT = $(LIB)/libclwrapper.so

# COMPILE OPTIONS
CXX = g++
LOG_LEVEL = LOG_WARN
override CXXFLAGS += -O2 -Wall -Wextra -Werror -pedantic -Wno-variadic-macros -DLOG_LEVEL=$(LOG_LEVEL) -fPIC

# OPENCL LIBRARIES BASED ON OS
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
OPENCL = -framework OpenCL
SHARED = -dynamiclib
endif

ifeq ($(UNAME), Linux)
.PHONY: check-env all
AMDAPP ?= /opt/AMDAPP/include
check-env:
	@if [ ! -d "${AMDAPP}" ]; then \
		echo "ERROR: set AMDAPP variable."; exit 1; \
	fi
OPENCL = -l OpenCL -I ${AMDAPP}
endif

# FINALLY THE RULES
_OBJS = log.o clerror.o clwrapper.o
OBJS = $(patsubst %, $(BUILD)/%, $(_OBJS))

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -I $(INC) -c -o $@ $<

$(OUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OPENCL) $(SHARED) -o $@ $^

.PHONY: clean

clean:
	rm -f $(BUILD)/*.o $(OUT)
