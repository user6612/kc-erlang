#include "kc.h"

static ErlDrvData kc_drv_start(ErlDrvPort port, char *buff);
static void kc_drv_stop(ErlDrvData handle);
// inspired by http://rakuto.blogspot.com/2008/07/manipulate-erlang-binary-term-format-in.html
static int kc_drv_control(ErlDrvData handle, unsigned int command, 
			  char * buf, int len, char ** rbuf, int rlen );

// for details, see http://erlang.org/doc/man/driver_entry.html
ErlDrvEntry kc_driver_entry = {
  .start    = kc_drv_start,          /* L_PTR start, called when port is opened */
  .stop     = kc_drv_stop,           /* F_PTR stop, called when port is closed */
  .driver_name  = DYLIB_NAME,
  // char *driver_name, the argument to open_port, must be same as dynamic library file name without suffix
  .control= kc_drv_control,             /* control, F_PTR control, port_command callback */
  .event = NULL,      // 			  Called when an event selected by driver_event() has occurred  */
  .extended_marker = ERL_DRV_EXTENDED_MARKER,  //       int extended_marker;        // ERL_DRV_EXTENDED_MARKER
  .major_version   = ERL_DRV_EXTENDED_MAJOR_VERSION, //    int major_version;          // ERL_DRV_EXTENDED_MAJOR_VERSION
  .minor_version   = ERL_DRV_EXTENDED_MINOR_VERSION, //    int minor_version;          // ERL_DRV_EXTENDED_MINOR_VERSION
  .driver_flags    = ERL_DRV_FLAG_USE_PORT_LOCKING,//    int driver_flags;           // ERL_DRV_FLAGs 
};

//DRIVER_INIT(example_drv) <- though wrong argument allowed, duplicate of DRIVER_INIT is not allowed.
DRIVER_INIT( DYLIB_NAME ) /* must match name in driver_entry */
{
  return &kc_driver_entry;
}

#include <stdio.h>

static ErlDrvData kc_drv_start(ErlDrvPort port, char *buff){
  KCDB * kcdb = kcdbnew();
  kcdbopen(kcdb, "test.kch", KCOWRITER|KCOCREATE);
  puts(__func__);
  return (ErlDrvData)kcdb;
}

static void kc_drv_stop(ErlDrvData handle){
  KCDB * kcdb = (KCDB*)handle;
  kcdbclose(kcdb);
  kcdbdel(kcdb);
  puts(__func__);
  return;
}

static int kc_drv_control(ErlDrvData handle, unsigned int command, 
			  char * buf, int len, char ** rbuf, int rlen ){
  puts(__func__);
  return 0;
}
