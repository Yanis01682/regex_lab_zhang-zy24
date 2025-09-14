#!/bin/sh
cmake -G "Unix Makefiles" -S . -B build && cd build && make all
./regex_lab_std_test
./CYK_algorithm
