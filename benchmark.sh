#!/bin/bash
#------------------------------------------------------------------------------
# File:     benchmark.sh
# Author:   koromodako
# Date:     2016-10-21
# Purpose:
#       This file tests matrix norm program for 2^x values both in serial and 
#       parallel mode
#------------------------------------------------------------------------------
VAL="4 8 16 32 64 128 256 512 1024 2048 4096 8192"

for val in ${VAL}; do ./distmatnorm ${val} serial; ./distmatnorm ${val} parallel; done
