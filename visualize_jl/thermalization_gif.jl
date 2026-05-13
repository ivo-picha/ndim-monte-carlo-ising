#!/home/ivoga/.juliaup/bin/julia
using Plots
ENV["GKSwstype"] = "100"  # Set GR backend to headless mode
gr()

args = ARGS
if length(args) != 1
    println("USAGE: thermalization_gif.jl <lattices.txt>")
    exit(1)
end

input = args[1];
#input = "/home/ivoga/Documents/PhD/sc_comp_course/project/mc_out/sT_d2_L10_T2.000_N10000_mh_cl_warm_LATTICE.txt"
name, ext = splitext(input)

# if ext != "txt"
#     println("Wrong data format.")
#     exit(2)
# end

# output a plot of one lattice and add it to an animation
function add_lattice_plot(anim::Animation, boolvec::Vector{Int64})
    L = Int(sqrt(length(boolvec)))
    mat = reshape(boolvec, L, L)
    hm = heatmap(mat, size = (375,400), colormap = :coolwarm, legend = false, framestyle=:box)
    frame(anim, hm)
end

anim = Plots.Animation()

open(input, "r") do io
    for line in eachline(io)
        vec = parse.(Int, split(line, ""))
        add_lattice_plot(anim, vec)
    end
end
outdir = joinpath(@__DIR__, "..", "animations")
mkpath(outdir)
println("Saving animation in $(outdir).")
gif(anim, joinpath(outdir, string(basename(name),".gif")), fps = 20);

