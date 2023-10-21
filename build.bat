@echo off

SET CC=clang
SET CFLAGS=-Wall -Wpedantic -ggdb -std=c11
SET CDEFINES=
SET CINCLUDES=
SET CFILES=main.c
SET CLIBS=

SET EXEC=main.exe

echo "--------COMPILING--------"
echo "%CC% %CFLAGS% %CDEFINES% %CINCLUDES% %CFILES% -o %EXEC% %CLIBS%"
%CC% %CFLAGS% %CDEFINES% %CINCLUDES% %CFILES% -o %EXEC% %CLIBS%

echo "---------RUNNING---------"
echo ".\%EXEC%"
.\%EXEC%
