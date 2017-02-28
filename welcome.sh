#!/usr/bin/bash

read -p "[0]: main program or [1]: tests: " ip
echo "$ip"
if [ "$ip" -eq "0" ]; then
    bin/ai
else
    test/run_tests
fi
