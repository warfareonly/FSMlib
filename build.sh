#!/bin/sh

mkdir -p build 
cd build
cmake ..
make -j8
cp FSMdevel/FSMdevel ../fsm_lib