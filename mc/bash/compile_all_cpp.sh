#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "USAGE: ${0} <optimization_option>"
    exit 1
fi

opt=${1}

if [ ${opt} != "-none" ] && [ ${opt} != "-O1" ] && [ ${opt} != "-O2" ] && [ ${opt} != "-O3" ] && [ ${opt} != "-Ofast" ]; then
    echo "Unknown option. Optimization options are -none, -O1/2/3, -Ofast."
    exit 1
fi

PP="/home/ivoga/Documents/PhD/sc_comp_course/project"

app="${PP}/mc/app"
src="${PP}/mc/src"
build="${PP}/mc/build"



str=""
for el in "${src}"/*.cpp ; do
    str="${str}${el} "
done

for el in "${app}"/*.cpp ; do
    basecpp=${el##*/}
    base=${basecpp%.cpp}
    cmd="g++ ${opt} ${el} ${str}-o ${build}/${base}"
    ${cmd}
    echo "Compiled ${base} in build folder."
done

