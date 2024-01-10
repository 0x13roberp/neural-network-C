#!/bin/sh

set -xe

gcc -Wall -Wextra -o twice twice.c -lm
gcc -Wall -Wextra -o gates gates.c -lm
gcc -Wall -Wextra -o xor xor.c -lm
gcc -Wall -Wextra -o nn nn.c -lm
