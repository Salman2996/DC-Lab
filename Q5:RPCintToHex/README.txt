$sudo apt-get install rpcbind
$rpcinfo

-create file.x

$rpcgen -a -C file.x

-edit prog_client.c prog_server.c

$make -f Makefile.file

$sudo ./prog_server
$./prog_client localhost