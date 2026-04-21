#!/bin/bash

# Check arguments
if [ $# -lt 1 ]; then
    echo "Error. Usage: $0 <0|1> [test_name]"
    exit 1
fi

MODE=$1
TEST=$2

# Compile
if [ -z "$TEST" ]; then
    echo ">>>> Compiling all tests"
    make tests
else
    echo ">>>> Compiling $TEST"
    make $TEST
fi

# Execute
if [ -z "$TEST" ]; then
    echo ">>>> Running all tests"

    for t in *_test; do
        if [ -x "$t" ]; then
            echo "---- Running $t ----"

            if [ "$MODE" -eq 0 ]; then
                ./$t
            else
                valgrind --leak-check=full ./$t
            fi

            echo ""
        fi
    done

else
    echo ">>>> Running $TEST"

    if [ "$MODE" -eq 0 ]; then
        ./$TEST
    else
        valgrind --leak-check=full ./$TEST
    fi
fi