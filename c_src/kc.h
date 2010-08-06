#ifndef KC_C
#define KC_C
#include <erl_driver.h>
#include <kclangc.h>

#define DYLIB_NAME  ("libkcerlang")
#define USE_TABLE   (0x01)              // argument TableName
#define USE_KEY     (0x02)  // argument {TableName, Key}
#define USE_VALUE   (0x04)  // argument {TableName, Key, Value}

#define KC_OPEN     ( 0x80100 | USE_TABLE)
#define KC_CLOSE    ( 0x80200 | USE_TABLE)
#define KC_PUT      ( 0x80300 | USE_TABLE | USE_KEY | USE_VALUE)
#define KC_PKEEP    ( 0x80400 | USE_TABLE | USE_KEY | USE_VALUE)
#define KC_PUTCAT   ( 0x80500 | USE_TABLE | USE_KEY | USE_VALUE)
#define KC_OUT      ( 0x80600 | USE_TABLE | USE_KEY  )
#define KC_GET      ( 0x80700 | USE_TABLE | USE_KEY  )
#define KC_ITERINIT ( 0x80900 | USE_TABLE)
#define KC_ITERNEXT ( 0x81000 | USE_TABLE)

#define KC_ADDINT   ( 0x81200 | USE_TABLE | USE_KEY | USE_VALUE)
#define KC_ADDDOUBLE ( 0x81300 | USE_TABLE | USE_KEY | USE_VALUE)
#define KC_SYNC     ( 0x81400 | USE_TABLE)
#define KC_OPTIMIZE ( 0x81500 | USE_TABLE)
#define KC_VANISH   ( 0x81600 | USE_TABLE)
#define KC_COPY     ( 0x81700 | USE_TABLE)
//#define KC_TX       ( 0x81800 | USE_TABLE)
#define KC_PATH     ( 0x81900 | USE_TABLE)
#define KC_RNUM     ( 0x82200 | USE_TABLE)
#define KC_SIZE     ( 0x82300 | USE_TABLE)

#define KC_TEST     (0x90000)

#endif
