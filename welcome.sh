#!/usr/bin/env sh
cd $(dirname $0)
read -p "[0]: main program or [1]: tests: " ip
if [ "$ip" -eq "0" ]; then
    bin/ai
else
    test/run_tests
fi
