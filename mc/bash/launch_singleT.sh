#!/bin/bash

if [ "$#" -ne 6 ]; then
    echo "USAGE: ${0} <dimension> <length> <temperature> <#sweeps> <opts:-m/-w/-d> <start:-h/-c>"
    exit 1
fi

PP="/home/ivoga/Documents/PhD/sc_comp_course/project"

outdir="${PP}/mc_out"

d="${1}"
L="${2}"
T="${3}"
N="${4}"
opt="${5}"
hc="${6}"

if [ "$opt" != "-m" ] && [ "$opt" != "-w" ] && [ "$opt" != "-d" ]; then
    echo "Unknown option. Known options are -m (Metropolis-Hastings), -w (MH + Wolff cluster updates), and -d (MH w/ diagonal exchange)."
    exit 1
fi

if [ "$opt" = "-w" ]; then
    mw="mh_cl"
else
    mw="mh"
fi

if [ "$hc" != "-c" ] && [ "$hc" != "-h" ]; then
    echo "Unknown starting condition. Known conditions are -h (hot/warm) and -c (cold)."
    exit 1
fi

if [ "$hc" = "-h" ]; then
    hcs="warm"
else
    hcs="cold"
fi

cd

${PP}/mc/build/singleT ${d} ${L} ${T} ${N} ${opt} ${hc} ${outdir}

if [ "${d}" == "2" ]; then
    thermaljl="${PP}/visualize_jl/thermalization_gif.jl"
    chmod +x ${thermaljl}
    configtxt=$(ls -t "${PP}/mc_out/" | grep "LATTICE.txt" | head -n 1)

    ${thermaljl} "${PP}/mc_out/${configtxt}"
fi
