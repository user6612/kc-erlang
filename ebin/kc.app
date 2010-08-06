{application, kc,
 [{description, "KyotoCabinet-Erlang"},
  {vsn, "0.0.1"},

  % All modules introduced by this application. systools uses this 
  % list when generating boot scripts and tar files. A module must
  % be defined in one and only one application. Defaults to [].
  {modules,
   [ kc, kc_app, kc_sup,
     kc_polydb]},

  % All names of registered processes in the application. systools
  % uses this list to detect name clashes between applications. Defaults to [].
  {registered, [ kc_sup ]},

  {applications, [kernel, stdlib]},
  {mod, {kc_app, []}}
 ]
}.
