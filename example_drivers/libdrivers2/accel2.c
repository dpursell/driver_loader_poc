#include <stddef.h>

#include "upm.h"

// Custom type can hold additional data needed by the driver (pins/buses/etc.)
typedef struct {
  upm_accelerometer_t accel_base;
} accel2_t;

static int close_accel2(upm_driver_base_t* driver) {
  free(driver);
  return 0;
}

static int read_accel2(upm_accelerometer_t* dev, float* x, float* y, float* z) {
  // Do whatever is needed to actually read the sensor.
  *x = 4.f;
  *y = 0.f;
  *z = 0.f;

  return 0;
}

static upm_driver_base_t* init_accel2(const upm_driver_init_args_t* args) {
  accel2_t* temp = (accel2_t*)malloc(sizeof(accel2_t));
  if (temp == NULL) {
    return NULL;
  }

  // Fill in upm_driver_base_t.
  temp->accel_base.base.version = 2;
  temp->accel_base.base.name = "Accel2 Driver";
  temp->accel_base.base.author = "Author 2";
  temp->accel_base.base.type = kDriverTypeAccelerometer;
  temp->accel_base.base.close = &close_accel2;

  // Fill in upm_accelerometer_t.
  temp->accel_base.read = &read_accel2;

  return (upm_driver_base_t*)temp;
}

upm_driver_entry_t accel2_entry __attribute__((visibility("default"))) = {
    .upm_api_version = UPM_DRIVER_API_VERSION_1,
    .init_driver = &init_accel2
};
