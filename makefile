CXX_FLAGS := -Wall -Werror -std=c++0x
INCLUDES := -I$(CURDIR)/upm

all: lib_loader libdrivers1 libdrivers2

clean:
	rm -rf lib_loader
	$(MAKE) -C example_drivers/libdrivers1 clean
	$(MAKE) -C example_drivers/libdrivers2 clean

# lib_loader executable
lib_loader: main.cpp
	g++ $(CXX_FLAGS) $(INCLUDES) main.cpp -o lib_loader -ldl

libdrivers1:
	$(MAKE) -C example_drivers/libdrivers1

libdrivers2:
	$(MAKE) -C example_drivers/libdrivers2
