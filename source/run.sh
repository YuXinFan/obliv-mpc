#!/usr/bin/env bash

./$1/a.out 1234 -- input1.txt & ./$1/a.out 1234 localhost input2.txt 

./$2/a.out 1234 -- input1.txt & ./$2/a.out 1234 localhost input2.txt 