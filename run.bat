@echo off

set CC=tcc
set CC_FLAGS=-Wall -Wextra -pedantic -std=c99

%CC% -run src/day%1.c -o day%1.exe %CC_FLAGS%

@echo on
