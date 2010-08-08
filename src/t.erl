-module(t).
-compile(export_all).

main()->
    kc:start(),
    {ok,S}=kc:open(h,h),
    io:format("data: ~p~n", [{Key,Value}={<<"asdfas">>, <<"asfasdfsfd">>}]),
    erlang:display(kc:set(S, Key,Value)),
    erlang:display({ok,Value}=kc:get(S, Key)),
    kc:close(S),
    kc:stop().

