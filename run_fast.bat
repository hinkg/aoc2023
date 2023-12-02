@echo off

set CC=clang
set CC_FLAGS=-Ofast -std=c99

%CC% src/day%1.c -o day%1.exe %CC_FLAGS%
call .\\day%1.exe
del .\\day%1.exe

@echo on
