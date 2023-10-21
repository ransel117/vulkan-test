#!/bin/sh

CC="clang"
CFLAGS="-Wall -Wpedantic -ggdb -std=c11"
CDEFINES=""
CINCLUDES=""
CFILES="main.c"
CLIBS="-lSDL2 -lvulkan"

if [ -z "${EXEC}" ]; then
    EXEC="main"
fi

echo "--------COMPILING--------"
echo "${CC} ${CFLAGS} ${CDEFINES} ${CINCLUDES} ${CFILES} -o ${EXEC} ${CLIBS}"
${CC} ${CFLAGS} ${CDEFINES} ${CINCLUDES} ${CFILES} -o ${EXEC} ${CLIBS}
