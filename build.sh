#!/bin/sh

set -xe

gcc -Wall -Wextra -o twice twice.c -lm
gcc -Wall -Wextra -o single single.c -lm
