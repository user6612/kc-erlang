#include "kc_util.h"

void reply_single_ok(ErlDrvPort port){
  ErlDrvTermData reply[] = {
    ERL_DRV_ATOM, driver_mk_atom("ok")
  };
  driver_send_term(port, driver_caller(port), reply, sizeof(reply) / sizeof(reply[0]));
}

void reply_ok_with_bin(ErlDrvPort port, const char* bin, size_t len){
  ErlDrvTermData reply[] = {
    ERL_DRV_ATOM, driver_mk_atom("ok"),
    ERL_DRV_BUF2BINARY, bin, len,
    ERL_DRV_TUPLE, 2
  };
  driver_send_term(port, driver_caller(port), reply, sizeof(reply) / sizeof(reply[0]));
  
}

void reply_error_with(ErlDrvPort port, const char * msg){
  ErlDrvTermData reply[] = {
    ERL_DRV_ATOM, driver_mk_atom("error"),
    ERL_DRV_ATOM, driver_mk_atom(msg), //kcdbemsg(drv_data->db)),
    ERL_DRV_TUPLE, 2,
  };
  driver_send_term(port, driver_caller(port), reply, sizeof(reply) / sizeof(reply[0]));

}
