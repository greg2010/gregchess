#!/usr/bin/env bash

mkdir build
cd build/

cmake ../ || exit
make -j"$(nproc)" || exit
cp gregchess ../