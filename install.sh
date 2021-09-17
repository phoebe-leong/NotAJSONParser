#!/bin/bash 

git clone https://github.com/ararslan/termcolor-c

mv termcolor-c/include ./
rm termcolor-c
mv include termcolor-c
