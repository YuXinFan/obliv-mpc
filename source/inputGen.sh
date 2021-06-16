#!/usr/bin/env bash

# min max
function random() {
    result=$(($1 + RANDOM % $(($2-$1))))
    echo ${result}
}

# path-to-file size min max
function GenInput() {
    echo $2 > "$1"
    for((i=0;i<$2;i++)); do
        ran=`random $3 $4`
        echo "${ran}" >> "$1"
    done
}

# prefix size 
function GenInputs() {
    GenInput ./input1.txt $1 $2 $3
    GenInput ./input2.txt $1 $2 $3
}

GenInputs $1 $2 $3

