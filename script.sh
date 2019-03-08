#!/bin/bash

time julia $1 >> julia.txt
echo >> julia.txt
gprof -p -b julia >> julia.txt
echo >> julia.txt
