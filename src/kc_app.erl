%%%-------------------------------------------------------------------
%%% @author UENISHI Kota <kuenishi@gmail.com>
%%% @copyright (C) 2010, UENISHI Kota
%%% @doc
%%%
%%% @end
%%% Created :  6 Aug 2010 by UENISHI Kota <kuenishi@gmail.com>
%%%-------------------------------------------------------------------
-module(kc_app).

-behaviour(application).

%% Application callbacks
-export([start/2, stop/1]).

-include("kc.hrl").
%%%===================================================================
%%% Application callbacks
%%%===================================================================

%%--------------------------------------------------------------------
%% @private
%% @doc
%% This function is called whenever an application is started using
%% application:start/[1,2], and should start the processes of the
%% application. If the application is structured according to the OTP
%% design principles as a supervision tree, this means starting the
%% top supervisor of the tree.
%%
%% @spec start(StartType, StartArgs) -> {ok, Pid} |
%%                                      {ok, Pid, State} |
%%                                      {error, Reason}
%%      StartType = normal | {takeover, Node} | {failover, Node}
%%      StartArgs = term()
%% @end
%%--------------------------------------------------------------------
start(_StartType, _StartArgs) ->
%    LibPath = code:priv_dir(?MODULE)++ "/lib",
    LibPath = filename:join([ filename:absname(""), "priv", "lib" ]),
    case erl_ddll:try_load(LibPath, ?DYLIB_NAME, []) of
	{ok, _Status} ->
%	    io:format("~p ~p: ~p~n", [?FILE, ?LINE, LibPath]),
	    kc_sup:start_link();
	{error, Reason}->
	    io:format("you have to set exactly where ~s.so exists: ~p , ~p~n",
		      [ ?DYLIB_NAME, erl_ddll:format_error(Reason), LibPath ]),
	    {error, Reason};
	Other ->
	    io:format("~p~n", [Other]),
	    {error, Other}
    end.

%%--------------------------------------------------------------------
%% @private
%% @doc
%% This function is called whenever an application has stopped. It
%% is intended to be the opposite of Module:start/2 and should do
%% any necessary cleaning up. The return value is ignored.
%%
%% @spec stop(State) -> void()
%% @end
%%--------------------------------------------------------------------
stop(_State) ->
    case erl_ddll:unload(?DYLIB_NAME) of
	{error, ErrorDesc}->
	    io:format("can't unload ~p: ~p~n", [ ?DYLIB_NAME, erl_ddll:format_error(ErrorDesc) ]);
	ok ->
	    ok
    end.

%%%===================================================================
%%% Internal functions
%%%===================================================================
