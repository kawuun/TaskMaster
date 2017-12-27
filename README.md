# TaskMaster

My job here was to make a fully-fledged job control daemon.
  It will be started via shell, and do its job while providing a
control shell to the user.
  Client/server archictecture to allow for two separate programs : A daemon, that
does the actual job control, and a control program, that provides a shell for the
user, and communicates with the daemon over UNIX or TCP sockets. 
