include ../../Makefile.common

vsel: main.cpp ../../lib/libclwrapper.so
	$(CXX) $(CXXFLAGS) $(OPENCL_INC) -I ../../include -o $@ $< -L../../lib -lclwrapper $(OPENCL_LIB)

clean:
	rm -f vsel
