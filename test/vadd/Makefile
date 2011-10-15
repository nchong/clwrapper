include ../../Makefile.common

vadd: main.cpp ../../lib/libclwrapper.so
	$(CXX) $(CXXFLAGS) -I ../../include -o $@ $< -L../../lib -lclwrapper

clean:
	rm -f vadd
