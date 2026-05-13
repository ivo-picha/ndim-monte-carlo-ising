#include "lat_cl.h"

#include <vector>
#include <cmath>


bool is_in_vec(const unsigned int j, const std::vector<unsigned int> vec) {
    for (unsigned int n : vec) {
        if (j == n) {
            return true;
        }
    }
    return false;
};


ClLattice::ClLattice(int d, int L, double T, bool is_warm) : MHLattice(d,L,T,is_warm) {};


std::vector<unsigned int> ClLattice::get_cluster() const {
    // idea: start from random site and check nbs
    // mark nbs to be flipped w/ a probability if they align; skip if nb already checked
    // add the newly added sites to the cluster to another list
    // go over the newly added sites in the same way; remove them from newly added list when finished
    // repeat until nothing is added to the cluster
    // maybe there is a cleaner way using functions i dont know right now

    unsigned int j = m_rand_site(m_gen); // starting site
    std::vector<unsigned int> checked_sites; // list to store sites which have been given a chance to flip
    std::vector<unsigned int> newly_added; // were just checked. will check their nbs next iteration 
    std::vector<unsigned int> to_flip;
    checked_sites.push_back(j);
    newly_added.push_back(j);
    to_flip.push_back(j);

    double prob_add = 1.0 - std::exp(-2.0/m_T);

    while (newly_added.size() != 0) {
        std::vector<unsigned int> copy_na(newly_added); // iterate over copied list to avoid weird business
        for (unsigned int n : copy_na) { 
            bool spin_n = m_lat[n-1].get_spin_bool();
            std::vector<unsigned int> nbs = get_nbs_j(n);
            for (unsigned int m : nbs) {
                if (is_in_vec(m, checked_sites)) {
                    continue;
                } else {
                    bool spin_m = m_lat[m-1].get_spin_bool();
                    if (spin_n == spin_m) {
                        double prob = m_rand_prob(m_gen);
                        if (prob <= prob_add) {
                            to_flip.push_back(m);
                            newly_added.push_back(m);
                        }
                    }
                    checked_sites.push_back(m);
                }
            }
            newly_added.erase(newly_added.begin()); // remove from the newly added because its nbs were already checked
        }
    }

    return to_flip;
};


void ClLattice::flip_cluster(const std::vector<unsigned int> cluster_vec) {
    cluster_sizes.push_back((int)cluster_vec.size());
    for (unsigned int j : cluster_vec) {
        m_lat[j-1].flip();
    }
    set_energy(get_H()); // reset energy from Hamiltonian
};


void ClLattice::get_and_flip_cluster() {
    flip_cluster(get_cluster());
}
