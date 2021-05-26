# Usage: average int1 int2 ...
function average () {
    local sum=0
    for int in $@; do
        ((sum += int))
    done
    echo $((sum / $#))
}

function random() {
    result=$(($1 + RANDOM % $(($2-$1))))
    echo "$?"
}


echo random 10 100





#./a.out 1234 -- input1.txt & ./a.out 1234 localhost input2.txt 