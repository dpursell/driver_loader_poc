#ifndef UPM_H_
#define UPM_H_

#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define UPM_DRIVER_API_VERSION_1 (1)

// All known driver types.
enum DriverType {
  kDriverTypeUnknown = 0,
  kDriverTypeAccelerometer = 1,
  kDriverTypeTemperature = 2,
  // etc.
};

// Generic driver initialization arguments as a potential alternative to
// varargs. This may provide a bit more structure and simplicity and could
// be extended to hold (name, value) keyword args as well. The downside is that
// everything must be a string.
typedef struct {
  const char* args;
  size_t num_args;
} upm_driver_init_args_t;

// Base type common to all drivers.
typedef struct upm_driver_base {
  // Driver information; up to the author how to use these fields.
  int32_t version;
  const char* name;
  const char* author;

  // Actual driver type. Useful to make sure we have the right type before
  // we try to cast pointers.
  int32_t type;

  // Closes the driver and frees up any resources. Returns 0 on success.
  int (*close)(struct upm_driver_base* driver);
} upm_driver_base_t;

// Driver entry point structure.
// Using a structure instead of a function allows us to provide additional
// information (such as a version number). Additionally,
// http://pubs.opengroup.org/onlinepubs/009695399/functions/dlsym.html says
// technically C is not required to support converting from void* to a function
// pointer, so casting void* to a upm_driver_entry_t* is more portable.
typedef struct {
  // API version implemented by this driver. This could allow us to update the
  // driver framework but remain backwards compatible with existing drivers.
  int upm_api_version;

  // Allocates and returns a new driver object.
  upm_driver_base_t* (*init_driver)(const upm_driver_init_args_t* args);
} upm_driver_entry_t;

// Specific accelerometer driver.
typedef struct upm_accelerometer {
  upm_driver_base_t base;
  int (*read)(struct upm_accelerometer* dev, float* x, float* y, float* z);
} upm_accelerometer_t;

// Specific temperature driver.
typedef struct upm_temperature {
  upm_driver_base_t base;
  int (*read)(struct upm_temperature* dev, float* degrees);
} upm_temperature_t;

#if defined(__cplusplus)
}
#endif

#endif  // UPM_H_
