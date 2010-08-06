%%%-------------------------------------------------------------------
%%% @author UENISHI Kota <kuenishi@gmail.com>
%%% @copyright (C) 2010, UENISHI Kota
%%% @doc
%%%
%%% @end
%%% Created :  6 Aug 2010 by UENISHI Kota <kuenishi@gmail.com>
%%%-------------------------------------------------------------------
-module(kc).
-author('kuenishi@gmail.com').

-export([start/0, stop/0]).

-spec start() -> ok.
start()->
    application:start(kc).

-spec stop() -> ok.		   
stop()->
    application:stop(kc).
