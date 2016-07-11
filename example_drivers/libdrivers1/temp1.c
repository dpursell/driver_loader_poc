#include <stddef.h>

#include "upm.h"

// Custom type can hold additional data needed by the driver (pins/buses/etc.)
typedef struct {
  upm_temperature_t temp_base;
} temp1_t;

static int close_temp1(upm_driver_base_t* driver) {
  free(driver);
  return 0;
}

static int read_temp1(upm_temperature_t* dev, float* degrees) {
  // Do whatever is needed to actually read the sensor.
  *degrees = 20.0;

  return 0;
}

static upm_driver_base_t* init_temp1(const upm_driver_init_args_t* args) {
  temp1_t* temp = (temp1_t*)malloc(sizeof(temp1_t));
  if (temp == NULL) {
    return NULL;
  }

  // Fill in upm_driver_base_t.
  temp->temp_base.base.version = 1;
  temp->temp_base.base.name = "Temp1 Driver";
  temp->temp_base.base.author = "Author 1";
  temp->temp_base.base.type = kDriverTypeTemperature;
  temp->temp_base.base.close = &close_temp1;

  // Fill in upm_temperature_t.
  temp->temp_base.read = &read_temp1;

  return (upm_driver_base_t*)temp;
}

upm_driver_entry_t temp1_entry __attribute__((visibility("default"))) = {
    .upm_api_version = UPM_DRIVER_API_VERSION_1,
    .init_driver = &init_temp1
};
