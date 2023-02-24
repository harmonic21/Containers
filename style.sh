#!/bin/bash

cp ../../materials/linters/.clang-format .

clang-format -n *.h *.cc

clang-format -i *.h *.cc

rm .clang-format


