#ifndef LAT_BASE_H
#define LAT_BASE_H

#include "spin.h"

#include <iostream>
#include <vector>
#include <random>

// convert systematically d-dim vector of indeces to 1-dim index and vice versa
// all lattice position indeces start from 1
unsigned int convert_index_to_j(std::vector<unsigned int>, int d, int L);
std::vector<unsigned int> convert_index_from_j(unsigned int j, int d, int L);

// analogous func to julia's mod1() but not really; only works for y = x pm 1
int mod1(int x, int y);

class BaseLattice {
    public:
        // constructor and descructor; always creates it random
        BaseLattice(int d, int L, double T, bool is_warm);
        virtual ~BaseLattice() {};

        // getters
        int get_d() const { return m_d; };
        int get_L() const { return m_L; };
        int get_size() const { return m_size; };
        double get_T() const { return m_T; };
        short signed int get_spin_j(unsigned int j) const;
        std::vector<unsigned int> get_nbs_j(unsigned int j) const; // neighbouring indeces; can be made faster without conversions
        std::vector<unsigned int> get_pos_nbs_j(unsigned int j) const; // only positive neigbours; no double counting energy
        int get_M() const; // magnetization
        double get_acceptance() const { return (double)tot_num_flips / (double)tot_num_attempted; };
        std::vector<bool> get_lattice() const; // a vector of bools giving spin up or down

        // set temperature; used for parallel tempering
        void set_T(double T) { m_T = T; };

        // to be polymorphed/implemented by child classes
        virtual int get_H() const = 0; // energy from Hamiltonian
        virtual int get_E() const = 0;
        virtual int get_dEj(unsigned int j) const = 0; // energy diff if spin j is flipped
        virtual void flip_ran_spin() = 0;
        virtual void sweep_lattice() = 0; // gives all spins a chance to flip on average
        virtual void sweep_lattice(int num_to_flip) = 0; // specified number of flips

        // in case of applicable cluster updates
        virtual void get_and_flip_cluster() {};
        virtual std::vector<size_t> get_cluster_sizes() const { return {}; };

        // string method
        virtual std::string str() const;

    protected:
        // lattice params
        int m_d;
        int m_L;
        double m_T;
        int m_size;
        
        // random distributions and generator
        mutable std::mt19937 m_gen;
        mutable std::uniform_int_distribution<> m_rand_bool;
        mutable std::uniform_int_distribution<> m_rand_site;
        mutable std::uniform_real_distribution<> m_rand_prob;

        std::vector<Spin> m_lat; // THE lattice -- vector of spins

        // monitor acceptance rate
        int tot_num_attempted; // # attempted filps
        int tot_num_flips; // number of successful flips
};

std::ostream& operator<<(std::ostream& os, const BaseLattice& lat);


#endif