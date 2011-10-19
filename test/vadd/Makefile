include ../../Makefile.common

vadd: main.cpp ../../lib/libclwrapper.so
	$(CXX) $(CXXFLAGS) $(OPENCL_INC) -I ../../include -o $@ $< -L../../lib -lclwrapper

clean:
	rm -f vadd
