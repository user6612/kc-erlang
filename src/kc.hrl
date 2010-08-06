%% -*- coding: utf-8 -*-

-define(DYLIB_NAME, "libkcerlang").
% -define(IS_LOADED, erl_kc_driver_process).

-define(IS_ATOM,   101).
-define(IS_LIST,   102). %% a simple string
-define(IS_RAW,    103).

-define(KC_CLOSE,  1).
-define(KC_DELETE, 2).
-define(KC_FOLDL,  3).
%4
-define(KC_INFO, 5).
%6
-define(KC_OPEN_FILE, 7).
-define(KC_LOOKUP   , 8).
% 9-16(ry
-define(KC_INSERT,   17).
-define(KC_INSERT_NEW, 18).
