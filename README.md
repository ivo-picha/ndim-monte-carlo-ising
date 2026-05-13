# Description
This repo contains a Monte Carlo simulation with various algorithms on the Ising model in arbitrary dimensions. Can also work on an extended MC with diagonal exchange. 

This is a project for the Scientific Computation and program design for Physicists course of the University of Geneva.

# Contents
- analysis: Python functions, which analyze output
- analysis\_out\_obs: Data files containing processed observables (heat capacity, etc.)
- analysis\_out\_Tc: Data files containing critical temperature information
- animations: Gifs of thermalization processes at the beginning of a simulation
- mc: Main Monte Carlo algorithms
    - app: Main cpp files performing the simulation
    - **bash: Bash scripts to launch simulations and compile code**
    - build: Mompiled code
    - src: Modules with functions and classes
- mc\_logs: Log files containing simulation summaries, terminal output and runtime
- mc\_out: Data files output from Monte Carlo
- plots: Self-explanatory
- visualize\_jl: Julia scripts for plotting and animating
