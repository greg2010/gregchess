#!/usr/bin/env bash

rm ./gregchess
mkdir build
cd build/

cmake ../ || exit
make -j"$(nproc)" || exit
cp gregchess ../