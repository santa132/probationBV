#!/bin/bash

encode()
{
    local input_string=$1
    echo "$input_string" | tr -d '\n' | sed "s/./&\n/g" | uniq -c | tr -d "\n 1" 
}

decode()
{
    local input_string=$1
    local mystring=""
    length=${#input_string}
    for ((i=0; i<length; i++))
    do
        char="${input_string:i:1}"
        if [[ $char =~ [0-9] ]]; then
            number=$((10#$char))
            behind_char="${input_string:i+1:1}"
            for ((j=0; j<$number; j++)); do
                mystring+="$behind_char"
            done
            ((i++))
        else 
            mystring+="$char"
        fi
    done
    echo "$mystring"
}

input_string="$1"
formatted_string=$(echo "$input_string" | tr -d "\n ")

if [[ $formatted_string =~ [0-9] ]]; then
    decode_string=$(decode "$formatted_string")
    echo "Chuỗi được giải mã: $decode_string"
else 
    encode_string=$(encode "$formatted_string")
    echo "Chuỗi được mã hóa: $encode_string"
fi
