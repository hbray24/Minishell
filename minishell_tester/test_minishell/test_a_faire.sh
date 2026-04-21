#!/bin/bash

echo hello world
echo $?

echo "hello world"
echo $?

echo 'hello world'
echo $?

echo hello'world'
echo $?

echo hello""world
echo $?

echo ''
echo $?

echo ""
echo $?

echo "$PWD"
echo $?

echo '$PWD'
echo $?

echo $USER
echo $?

echo "$USER"
echo $?

echo '$USER'
echo $?

echo "aspas ->'"
echo $?

echo "aspas -> ' "
echo $?

echo 'aspas ->"'
echo $?

echo 'aspas -> " '
echo $?

echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<"
echo $?

echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<'
echo $?

echo "exit_code ->$? user ->$USER home -> $HOME"
echo $?

echo 'exit_code ->$? user ->$USER home -> $HOME'
echo $?

echo "$"
echo $?

echo '$'
echo $?

echo $
echo $?

echo $?
echo $?

echo $?HELLO
echo $?

pwd
echo $?

pwd oi
echo $?

export hello
echo $?

export HELLO=123
echo $?

export A-
echo $?

export HELLO=123 A
echo $?

export HELLO="123 A-"
echo $?

export hello world
echo $?

export HELLO-=123
echo $?

export =
echo $?

export 123
echo $?

unset
echo $?

unset HELLO
echo $?

unset HELLO1 HELLO2
echo $?

unset HOME
echo $?

unset PATH
echo $?

unset SHELL
echo $?

cd $PWD
echo $?

cd $PWD hi
echo $?

cd 123123
echo $?


#==================pipe======================
env | sort | grep -v SHLVL | grep -v ^_
echo $?

cat ./test_files/infile_big | grep oi
echo $?

cat minishell.h | grep ");"$
echo $?

export GHOST=123 | env | grep GHOST
echo $?


#====================redirects===============
grep hi <./test_files/infile
echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


echo $?


