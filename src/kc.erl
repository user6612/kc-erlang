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
-include("kc.hrl").

-export([start/0, stop/0]).
-export([open/2, close/1, set/3, add/3, append/3, incrint/3, incrdouble/3, cas/4,
	 remove/2, get/2, clear/1, sync/1, dumpsnap/2, loadsnap/2, count/1,
	size/1, path/1, status/1 ]).

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

-spec close(Pid::pid())-> ok.
close(Pid)->
    gen_server:cast(Pid, stop).

-spec set(Pid::pid(), binary(), binary())-> ok | {error, reason()}.
set(Table, Key, Value) when is_binary(Key), is_binary(Value)->
    {ok, Port}=gen_server:call(Table, port),
    erlang:port_command(Port, <<?KC_SET/native,
				(byte_size(Key)):64/native, Key/binary,
				(byte_size(Value)):64/native, Value/binary>>),
    receive Reply -> Reply end.

add(_Table, Key, Value) when is_binary(Key), is_binary(Value)->
    not_yet.

append(_Table, Key, Value) when is_binary(Key), is_binary(Value)->
    not_yet.

incrint(_Table, Key, Num) when is_binary(Key), is_integer(Num)->
    not_yet.

incrdouble(_Table, Key, Value) when is_binary(Key), is_float(Value)->
    not_yet.

cas(_Table, Key, OldValue, NewValue) when is_binary(Key), is_binary(OldValue), is_binary(NewValue)->
    not_yet.

remove(_Table, Key) when is_binary(Key)->
    not_yet.

-spec get(Pid::pid(), binary()) -> {ok, Value::binary()} | {error, reason()}.
get(Table, Key) when is_binary(Key)->
    {ok, Port}=gen_server:call(Table, port),
    true=erlang:port_command(Port, <<?KC_GET/native, (byte_size(Key)):64/native, Key/binary>>),
    receive Reply -> Reply end.
    % Same as Port ! {self(), {command, Data}} except for the error behaviour

clear(_Table)->
    not_yet.

sync(_Table)->
    not_yet.

dumpsnap(_Table, Dest) when is_list(Dest)->
    not_yet.
loadsnap(_Table, Src) when is_list(Src)->
    not_yet.

count(_Table)->
    not_yet.

size(_Table)->
    not_yet.

path(_Table)->
    not_yet.

status(_Table)->
    not_yet.

% cursor(_Table)->
%     not_yet.
