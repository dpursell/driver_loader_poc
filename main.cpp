
#include <dlfcn.h>
#include <stdio.h>

#include "upm.h"

#define LIBDRIVERS1_PATH "example_drivers/libdrivers1/libdrivers1.so"
#define LIBDRIVERS2_PATH "example_drivers/libdrivers2/libdrivers2.so"

// Loads a driver from |path| with entry point |name| and prints some
// general information.
upm_driver_base_t* load_and_print_driver(const char* path, const char* name,
                                         upm_driver_init_args_t* args) {
  void* handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
  if (handle == NULL) {
    fprintf(stderr, "Error dlopen'ing %s: %s\n", path, dlerror());
    return NULL;
  }

  upm_driver_entry_t* entry = (upm_driver_entry_t*)dlsym(handle, name);
  if (entry == NULL) {
    fprintf(stderr, "Error dlsym'ing %s: %s\n", name, dlerror());
    return NULL;
  }

  upm_driver_base_t* base = entry->init_driver(args);

  if (base == NULL) {
    fprintf(stderr, "Error init'ing driver %s\n", path);
    return NULL;
  }

  printf("'%s' loaded: author = '%s', version = %d, type = %d\n", base->name,
         base->author, base->version, base->type);

  return base;
}

// Loads an accelerometer driver from |path| and prints a reading.
void test_accel_driver(const char* path, const char* name,
                       upm_driver_init_args_t* args) {
  upm_driver_base_t* base = load_and_print_driver(path, name, args);
  if (base == nullptr) {
    return;
  }

  if (base->type != kDriverTypeAccelerometer) {
    printf("  Error: driver is not an accelerometer\n");
  } else {
    upm_accelerometer_t* accel = reinterpret_cast<upm_accelerometer_t*>(base);
    float x, y, z;
    accel->read(accel, &x, &y, &z);
    printf("  Accelerometer reading: [%0.2f, %0.2f, %0.2f]\n", x, y, z);
  }

  base->close(base);
}

// Loads a temperature driver from |path| and prints a reading.
void test_temp_driver(const char* path, const char* name,
                       upm_driver_init_args_t* args) {
  upm_driver_base_t* base = load_and_print_driver(path, name, args);
  if (base == nullptr) {
    return;
  }

  if (base->type != kDriverTypeTemperature) {
    printf("  Error: driver is not a temperature sensor\n");
  } else {
    upm_temperature_t* temp = reinterpret_cast<upm_temperature_t*>(base);
    float degrees;
    temp->read(temp, &degrees);
    printf("  Temperature reading: %0.2f degrees\n", degrees);
  }

  base->close(base);
}

int main() {
  printf("Lib Loader\n");

  test_accel_driver(LIBDRIVERS1_PATH, "accel1_entry", nullptr);
  test_accel_driver(LIBDRIVERS2_PATH, "accel2_entry", nullptr);
  test_temp_driver(LIBDRIVERS1_PATH, "temp1_entry", nullptr);

  return 0;
}
