#!/bin/bash
echo Summary result
echo "File: ./$1"

Red='\033[0;31m'    # Red
Green='\033[0;32m'  # Green
NC='\033[0m'        # No Color


failed_count=$(grep -c "FAILED" "$1")
ok_count=$(grep -c "OK" "$1")
total=$((failed_count + ok_count))
if (($total != 0)); then
    echo "[Total]     case: $total"
    echo -e "${Green}[ OK ]      case: $ok_count"
    echo -e "${Red}[ FAILED ]  case: $failed_count"
else 
    echo ""