#ifndef KC_C
#define KC_C
#include <erl_driver.h>
#include <kclangc.h>

#define DYLIB_NAME  ("libkcerlang")

#define KC_SET      (1)
#define KC_GET      (101)

typedef struct {
  KCDB * db;
  ErlDrvPort port;
} kc_drv_t;

#endif
