#!/usr/bin/env bash

set -e

g++ -std=c++23 \
    src/core/core.cpp \
    src/split/split.cpp \
    src/nodes/nodo_transistor/nodo_transistor.cpp \
    src/merge/merge.cpp \
    src/diamond/graph.cpp \
    src/diamond/diamond.cpp \
    "$1" \
    -o test_out
