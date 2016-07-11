C_FLAGS := -Wall -Werror
LIB_FLAGS := -fPIC -fvisibility=hidden -shared
INCLUDES := -I$(CURDIR)/../../upm

libdrivers1: accel1.c temp1.c
	gcc $(C_FLAGS) $(LIB_FLAGS) $(INCLUDES) accel1.c temp1.c -o libdrivers1.so

clean:
	rm -rf *.so
