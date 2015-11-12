#!/usr/bin/python 

# Usage: > ./driver.py

import os,sys

n = 0

for x in range(1, 6):
   n = str(x)
   os.system('echo test \#'+n)
   os.system('cp test'+n+'.h input.h')
   os.system('make clean')
   os.system('make')
   os.system('./hist > myOut'+n+'.txt')
   os.system('diff -w myOut'+n+'.txt out'+n+'.txt')

