#!/bin/bash
source ex2.sh

content_lenth=10000
current_size=0

# Generate a random number greater than 30,000,000
total_size=$((RANDOM % 70000001 + 30000000))

echo "Creating file: ./$1"
echo "Size of file: $total_size"

while [[ $current_size -lt $total_size ]]; do
    random_string=$(head -c "$content_lenth" /dev/urandom | base64)
    echo "$random_string" >> "$1"
    current_size=$(stat -c %s "$1")
    showProgress $current_size $total_size
done