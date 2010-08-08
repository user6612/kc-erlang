#ifndef KC_UTIL_H
#define KC_UTIL_H

#include <erl_driver.h>

void reply_single_ok(ErlDrvPort);
void reply_ok_with_bin(ErlDrvPort, const char* bin, size_t len);
void reply_error_with(ErlDrvPort port, const char * msg);

#endif
