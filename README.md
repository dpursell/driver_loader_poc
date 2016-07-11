lib_loader example program
--------------------------

The purpose of this program is to demonstrate how loading shared libraries
containing UPM drivers might be done at runtime.

The high-level overview of how this works is that each driver must expose
a single struct of type upm_driver_entry_t. The user code loads this entry
point, then uses it to initialize and control the driver.

-- Building --
Build by running `make` in this top-level folder. The executable built will
be named "lib_loader".

Only verified on Ubuntu 14.04, but I think it should compile and run on most
Linux distributions.

-- Structure --
The project is broken up into a few parts:

./main.cpp
  A simple test program to load and print some info about a few drivers from
  the example_drivers libraries.

upm/
  A collection of types meant to demonstrate the foundations of what the driver
  API might look like.

  The general idea is to have a single generic driver base type, then a
  collection of driver types (e.g. accelerometers or temp sensors) which add
  to it, then each specific driver itself add to those types:

    upm_base_t {
      // Common stuff.
    }

    upm_accelerometer_t {
      upm_base_t;
      // Generic accelerometer stuff.
    }

    mpu_9050_accelerometer_t {
      upm_accelerometer_t;
      // MPU9050-specific stuff.
    }

example_drivers/
  A few simple example implementations of drivers in this model. libdrivers1
  contains an accelerometer and a temperature sensor, libdrivers2 contains
  an accelerometer.
