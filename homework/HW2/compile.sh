#! /bin/bash

g++ print_args.c -o print_args
g++ print_env.c -o print_env

./print_args $@
./print_env