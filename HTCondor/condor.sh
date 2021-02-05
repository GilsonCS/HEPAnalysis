#!/bin/bash

echo $1
echo $2
echo $3

cp -r $3 .
cd HEPAnalysis
make --always-make
python runSelection.py -j $1 -p $2 -t 0
