#!/bin/sh

export EXEC="main"

./compile.sh
./run.sh

unset EXEC
