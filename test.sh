#!/bin/bash

gcc -Wall a.c analyse.c misc.c -o prog && ./prog -c analyse.c a.z && wc -c analyse.c && xxd a.z && wc -c a.z && ./prog -d a.z an.out && xxd an.out && wc -c an.out
