#!/bin/bash
bar_size=37
symbol_done='#'
symbol_todo="-"
percentage_scale=1

showProgress()
{
    current="$1"
    total="$2"

    current_percent=$(bc <<< "scale=$percentage_scale; 100*$current/$total")
    # number done and tdo character
    done=$(bc <<< "scale=0; $bar_size * $current_percent / 100")
    todo=$(bc <<< "scale=0; $bar_size - $done")

    # build progres bar
    done_sub_bar=$(printf "%${done}s" | tr " " "${symbol_done}") 
    todo_sub_bar=$(printf "%${todo}s" | tr " " "${symbol_todo}") 
    # output
    echo -ne "\rProgress bar: |${done_sub_bar}${todo_sub_bar}| ${current_percent}%"

    if [[ $current -gt $total ]]; then
        echo -e "\nDONE"
    fi
}

setOptional()
{
    optional="$1"
    value="$2"
    if [[ "$1" =~ "-d" ]]; then
        percentage_scale=$2
    elif [[ "$1" =~ "-l" ]]; then
        bar_size=$2
    else
        symbol_done="$2"
    fi
}


# num_arguments=$#
# if [[ $((num_arguments%2)) != 0 ]]; then
#     echo "Wrong command."
# else
#     current=$2
#     total=$4
#     echo $num_arguments
#     for ((i=5; i<$num_arguments; i+=2));
#     do
#         if [[ "${!i}" =~ -d|-l|-f ]]; then
#             next_index=$((i+1))
#             setOptional "${!i}" "${!next_index}"
#         fi
#     done

    # for ((i=$current; i<=$total; i++))
    # do
    #     sleep 0.2 #simulate the task running
    #     showProgress $i $total
    # done
# fi