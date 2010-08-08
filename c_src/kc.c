#include "kc.h"
#include "kc_util.h"


static ErlDrvData kc_drv_start(ErlDrvPort, char *);
static void kc_drv_stop(ErlDrvData );
static void kc_drv_outputv(ErlDrvData, ErlIOVec *);

// for details, see http://erlang.org/doc/man/driver_entry.html
ErlDrvEntry kc_driver_entry = {
  .start    = kc_drv_start,          /* L_PTR start, called when port is opened */
  .stop     = kc_drv_stop,           /* F_PTR stop, called when port is closed */
  .driver_name  = DYLIB_NAME,
  // char *driver_name, the argument to open_port, must be same as dynamic library file name without suffix
  .output   = NULL,
  .outputv  = kc_drv_outputv,
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
  kc_drv_t * drv_data = driver_alloc(sizeof(kc_drv_t));
  drv_data->db = kcdbnew();
  drv_data->port = port;
  kcdbopen(drv_data->db, "test.kch", KCOWRITER|KCOCREATE);
  return (ErlDrvData)drv_data;
}

static void kc_drv_stop(ErlDrvData handle){
  kc_drv_t * drv_data = (kc_drv_t*)handle;
  kcdbclose(drv_data->db);
  kcdbdel(drv_data->db);
  driver_free(drv_data);
  return;
}


/*
static void kc_print(ErlIOVec *ev){
  int i;
  printf("argument: ErlIOVec vsize - %d, size - %d , %p %p\n",
	 ev->vsize, ev->size, ev->iov, ev->binv );
  printf("%p (%d)\n", ev->binv[1]->orig_bytes, ev->binv[1]->orig_size);
  for(i=0;i<ev->binv[1]->orig_size;++i){
    printf("%.2x ", ev->binv[1]->orig_bytes[i]);
  }
  printf("\n");
}
*/

// {Pid, {command, { Op/integer, Operand }}}
static void kc_drv_outputv(ErlDrvData p, ErlIOVec *ev){
  kc_drv_t * drv_data = (kc_drv_t*)p;
  uint64_t *klen;
  uint64_t *vlen;
  char * kp;
  char * vp;
  char * buf = ev->binv[1]->orig_bytes;
  size_t s;
  switch(buf[0]){
  case KC_SET:
    klen = (uint64_t*)(&buf[1]);
    vlen = (uint64_t*)(&buf[1+sizeof(uint64_t)+*klen]);
    kp = &buf[1+sizeof(uint64_t)];
    vp = &buf[1+sizeof(uint64_t) + *klen + sizeof(uint64_t) ];
    if( kcdbset(drv_data->db, kp, (size_t)*klen, vp, (size_t)*vlen) ){
      reply_single_ok(drv_data->port);
    }else{
      reply_error_with(drv_data->port, kcdbemsg(drv_data->db));
    }
    break;
  case KC_GET:
    //    kc_print(ev);
    klen = (uint64_t*)(&buf[1]);
    kp = &buf[1+sizeof(uint64_t)];
    vp = kcdbget(drv_data->db, kp, (size_t)*klen, &s);
    if( vp != NULL){  //ok
      reply_ok_with_bin(drv_data->port, vp, s);
      kcfree(vp);
    }else { //ng
      reply_error_with(drv_data->port, "someerror");
    }
    break;
  default:
    //ignore any message
    break;
  }
  //  return;
}
