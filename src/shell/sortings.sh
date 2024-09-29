#!/bin/bash

sorting_modes=(
    "TAB"
    "ABR"
    "AVL"
)

get_tri()
{
    SORTING_OPTION=${sorting_modes[2]}

    case $1 in
        
        --tab) SORTING_OPTION=${sorting_modes[0]}  ;;
        --abr) SORTING_OPTION=${sorting_modes[1]}  ;;
        --avl) SORTING_OPTION=${sorting_modes[2]}  ;;

    esac
}