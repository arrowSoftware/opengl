#!/usr/bin/env bash

for arg in "$@"
do
    if [ "$arg" == "--help" ] || [ "$arg" == "-h" ]
    then
        echo "Help argument detected."
    elif [ "$arg" == "" ]
    then
        build=release
    elif [ "$arg" == "release" ]
    then
        build=release
    elif [ "$arg" == "debug" ]
    then
        build=debug
    fi
done

export BUILD=$build
make $build
