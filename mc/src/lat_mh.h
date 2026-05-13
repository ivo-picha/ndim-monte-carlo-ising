#ifndef LAT_MH_H
#define LAT_MH_H

#include "lat_base.h"
#include "spin.h"

#include <iostream>

class MHLattice : public BaseLattice {
    public:
        // constructor and destructor
        MHLattice(int d, int L, double T, bool is_warm);
        virtual ~MHLattice() {};

        // getters
        int get_H() const; // energy from Hamiltonian
        int get_dEj(unsigned int j) const; // energy diff if spin j is flipped
        int get_E() const { return m_energy; };
        
        // setters
        void update_energy(int dE) { m_energy += dE; };

        // MH steps and sweeps
        void flip_ran_spin();
        void sweep_lattice(); // gives all spins a chance to flip on average
        void sweep_lattice(int num_to_flip); // specified number of flips

        // string method -> not necessary? maybe just print energy


    protected:
        int m_energy; // energy from dE accumulation
        void set_energy(const int new_energy) { m_energy = new_energy; };

};










#endif