#! /bin/bash

gcc print_args.c -o print_args
gcc print_env.c -o print_env

./print_args $@
./print_env