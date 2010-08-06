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
-export([open/2, close/1]).

-spec start() -> ok.
start()->
    application:start(kc).

-spec stop() -> ok.
stop()->
    application:stop(kc).

-spec open(TableName::atom(), TableType::atom()) -> {ok, pid()}.
open(TableName, TableType) when is_atom(TableName), is_atom(TableType)->
    TableFileName = atom_to_list(TableName) ++ ".kch", TableType,
    supervisor:start_child(kc_sup, [ TableFileName ]).

close(Pid)->
    gen_server:cast(Pid, stop).
