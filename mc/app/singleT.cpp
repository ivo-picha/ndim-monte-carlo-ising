#include "../src/spin.h"
#include "../src/lat_base.h"
#include "../src/lat_mh.h"
#include "../src/data_funcs.h"
#include "../src/lat_cl.h"

#include <iostream>
#include <vector>



int main(int argc, char* argv[]) {

    // intended usage from command line for basic MH algorithm
    // exec d L T N -opts -warm/cold
    // possible options are:
    // -m : basic metropolis-hastings w/ NN FM exchange
    // -w : MH + Wolff cluster updates


    // process ARGS and parse values
    if (argc != 8) {
        std::cout << "USAGE: " << argv[0] << " <dimension> <length> <temperature> <#sweeps> <opts:-m/-w> <start:-h/-c> <outdir>" << std::endl;
        return 1;
    }

    std::string opt = argv[5];
    if (opt != "-m" && opt != "-w") {
        std::cout << "Unknown option. Known options are -m (Metropolis-Hastings) and -c (MH + Wolff cluster updates)." << std::endl;
        return 1;
    }
    bool cu = (opt == "-w") ? true : false;

    std::string hc = argv[6];
    if (hc != "-c" && hc != "-h") {
        std::cout << "Unknown starting condition. Known conditions are -h (hot/warm) and -c (cold)." << std::endl;
        return 1;
    }
    bool warm = (hc == "-h") ? true : false;

    int d = atoi(argv[1]);
    int L = atoi(argv[2]);
    double T = atof(argv[3]);
    int N = atoi(argv[4]);
    std::string outdir = argv[7];

    if (T <= 0) {
        std::cout << "Temperature must have a positive value." << std::endl;
        return 1;
    }

    std::cout << "Running a Monte Carlo simulation for a system with:"
              << "\ndimension d = " << d
              << "\nlength L = " << L
              << "\ntemperature T/J = " << T
              << "\nnumber of sweeps N = " << N 
              << (cu ? "\nCluster updates included near Tc." : "") << std::endl;



    // initialize lattice and vectors to store observables
    BaseLattice* lat = cu ? new ClLattice(d, L, T, warm) : new MHLattice(d, L, T, warm);
    std::cout << "Initial lattice (E = " << lat->get_E() << "):\n" << *lat << std::endl;


    // lists to store observables
    std::vector<int> list_E;
    std::vector<int> list_M;
    std::vector<double> list_ar;
    
    bool record_lattice = (d == 2) ? true : false; // only record lattice in 2D so it can be visualized nicely
    std::vector<std::vector<bool>> list_lat;

    // for cluster updates; do update once every sc steps;
    int sc = 100;
    int cl_count = 0;

    // dont record after every sweep
    int snap = 4;
    int rec_count = 0;

    // perform N number of lattice sweeps
    for (int n = 0; n < N; ++n) {
        lat->sweep_lattice();

        if (cu) {
            cl_count++;
            if (cl_count == sc) {
                lat->get_and_flip_cluster();
                cl_count = 0;
            }
        }

        list_E.push_back(lat->get_E());
        list_M.push_back(lat->get_M());
        list_ar.push_back(lat->get_acceptance());

        // record 2000 steps at most 
        if (record_lattice && n < 2000 && rec_count%snap == 0) {
            list_lat.push_back(lat->get_lattice());
        }
    }

    std::cout << "Final lattice (E = " << lat->get_E() << "):\n" << *lat << std::endl;

    //get a name base, including sim params
    std::string base_name = get_base_name_sT(d, L, T, N, cu, warm);

    // save data
    save_lattices(list_lat, outdir + "/" + base_name + "_LATTICE.txt");
    save_list_int(list_E, outdir + "/" + base_name + "_ENERGY.csv");
    save_list_int(list_M, outdir + "/" + base_name + "_MAGNET.csv");
    save_list_double(list_ar, outdir + "/" + base_name + "_ACCEPT.csv");
    if (cu) save_list_size_t(lat->get_cluster_sizes(), outdir + "/" + base_name + "_CLUSTERS.csv");
    
    
    return 0;
}