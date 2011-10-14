include Makefile.common

# DIRECTORIES
SRC = src
INC = include
BUILD = build
LIB = lib
OUT = $(LIB)/libclwrapper.so

override CXXFLAGS += -fPIC

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
