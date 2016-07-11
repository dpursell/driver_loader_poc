C_FLAGS := -Wall -Werror
LIB_FLAGS := -fPIC -fvisibility=hidden -shared
INCLUDES := -I$(CURDIR)/../../upm

libdrivers2: accel2.c
	gcc $(C_FLAGS) $(LIB_FLAGS) $(INCLUDES) accel2.c -o libdrivers2.so

clean:
	rm -rf *.so
