#include "lat_mh.h" 

#include <iostream>
#include <vector>
#include <random>


MHLattice::MHLattice(int d, int L, double T, bool is_warm)
    : BaseLattice(d, L, T, is_warm), m_energy(get_H()) {
    //int m_energy = get_H();
};


int MHLattice::get_H() const {
    int E = 0;
    for (int j = 1; j <= m_size; ++j) {
        int spin_j = m_lat[j-1].get_spin();
        std::vector<unsigned int> pos_nbs = get_pos_nbs_j(j); // no double counting
        for (unsigned int n : pos_nbs) {
            E += -1* spin_j * m_lat[n-1].get_spin();
        }
    }
    return E; 
};


int MHLattice::get_dEj(unsigned int j) const {
    int dE = 0;
    int spin_j = m_lat[j-1].get_spin();
    std::vector<unsigned int> nbs = get_nbs_j(j); // no double counting
    for (unsigned int n : nbs) {
        dE += spin_j * m_lat[n-1].get_spin();
    }
    return 2*dE; 
};


void MHLattice::flip_ran_spin() {
    ++ tot_num_attempted;
    unsigned int j = m_rand_site(m_gen);
    Spin& spin_j = m_lat[j-1];
    int dE = get_dEj(j);
    if (dE < 0) {
        spin_j.flip();
        m_energy += dE;
        ++ tot_num_flips;
    } else {
        double prob = m_rand_prob(m_gen);
        double boltzmann = std::exp(-(double)dE/m_T);
        if (prob <= boltzmann) {
            spin_j.flip();
            m_energy += dE;
            ++ tot_num_flips;
        }
    }
};


void MHLattice::sweep_lattice() {
    for (int i = 0; i < m_size; ++i) {
        flip_ran_spin();
    }
};


void MHLattice::sweep_lattice(int num_to_flip) {
    for (int i = 0; i < num_to_flip; ++i) {
        flip_ran_spin();
    }
};