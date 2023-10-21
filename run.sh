#!/bin/sh

if [ -z "$EXEC" ]; then
    EXEC="main"
fi

echo "---------RUNNING---------"
echo "./${EXEC}"
./${EXEC}
