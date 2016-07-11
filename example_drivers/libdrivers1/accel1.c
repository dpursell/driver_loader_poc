#include <stddef.h>

#include "upm.h"

// Custom type can hold additional data needed by the driver (pins/buses/etc.)
typedef struct {
  upm_accelerometer_t accel_base;
} accel1_t;

static int close_accel1(upm_driver_base_t* driver) {
  free(driver);
  return 0;
}

static int read_accel1(upm_accelerometer_t* dev, float* x, float* y, float* z) {
  // Do whatever is needed to actually read the sensor.
  *x = 0.f;
  *y = 0.f;
  *z = -9.8f;

  return 0;
}

static upm_driver_base_t* init_accel1(const upm_driver_init_args_t* args) {
  accel1_t* temp = (accel1_t*)malloc(sizeof(accel1_t));
  if (temp == NULL) {
    return NULL;
  }

  // Fill in upm_driver_base_t.
  temp->accel_base.base.version = 1;
  temp->accel_base.base.name = "Accel1 Driver";
  temp->accel_base.base.author = "Author 1";
  temp->accel_base.base.type = kDriverTypeAccelerometer;
  temp->accel_base.base.close = &close_accel1;

  // Fill in upm_accelerometer_t.
  temp->accel_base.read = &read_accel1;

  return (upm_driver_base_t*)temp;
}

upm_driver_entry_t accel1_entry __attribute__((visibility("default"))) = {
    .upm_api_version = UPM_DRIVER_API_VERSION_1,
    .init_driver = &init_accel1
};
