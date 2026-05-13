#include "lat_base.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <cmath>

unsigned int convert_index_to_j(std::vector<unsigned int> vec_xj, int d, int L) {
    size_t vec_size = vec_xj.size();
    if (d != vec_size) {
        std::cout << "BaseLattice::convert_index_to_j ERROR: Index vector dimension doesn't match specified dimension." << std::endl;
    }

    if (d == 1)
    {
        return vec_xj[0];
    } else {
    

    unsigned int j = 1;
    for (int n = 0; n < d; ++n) {
        j += std::pow(L, d-1-n) * (vec_xj[n]-1);
    }
    return j;}
};


std::vector<unsigned int> convert_index_from_j(unsigned int j, int d, int L) {
    if (d == 1) {
        return {j};
    } else {
    std::vector<unsigned int> vec_xj;
    int remainder = j-1;
    for (int n = 0; n < d-1; ++n) {
        int Lpow = std::pow(L, d-1-n);
        int result = (int)remainder / Lpow;
        remainder = remainder % Lpow;
        vec_xj.push_back((result+1));
        if (n == d-2)
        {
            vec_xj.push_back(remainder+1);
        }
        
    }
    return vec_xj;}
};

// probably can be improved
int mod1(int x, int y) {
    int rem = x%y;
    if (x==0)
    {
        return y;
    } else {
    if (rem == 0) {
        return x;
    } else
    {
        /* code */
    }
     {
        return rem;
    }}
};


BaseLattice::BaseLattice(int d, int L, double T, bool is_warm)
    : m_d(d), m_L(L), m_T(T), m_size(std::pow(L, d)),
      m_gen(std::random_device{}()), m_rand_bool(0,1), m_rand_site(1,m_size), m_rand_prob(0.0,1.0),
      tot_num_flips(0), tot_num_attempted(0) {

    if (is_warm == true) {

        // populate lattice with random spins
        for (unsigned int j = 1; j <= m_size; ++j) {
            Spin spin_j(m_rand_bool(m_gen));
            m_lat.push_back(spin_j);
        }

    } else {

        for (unsigned int j = 1; j <= m_size; ++j) {
            Spin spin_j(true);
            m_lat.push_back(spin_j);
        }
    }
};


signed short int BaseLattice::get_spin_j(unsigned int j) const {
    Spin spin_j = m_lat[j-1];
    return spin_j.get_spin();
};


std::vector<unsigned int> BaseLattice::get_pos_nbs_j(unsigned int j) const {
    std::vector<unsigned int> pos_nbs_j;
    std::vector<unsigned int> vec_xj = convert_index_from_j(j, m_d, m_L);
    for (int n = 0; n < m_d; ++n) {
        std::vector<unsigned int> positive_nb = vec_xj;
        positive_nb[n] = mod1((positive_nb[n] + 1), m_L); // respect periodic boundaries
        pos_nbs_j.push_back(convert_index_to_j(positive_nb, m_d, m_L));
    }
    return pos_nbs_j;
};


std::vector<unsigned int> BaseLattice::get_nbs_j(unsigned int j) const {
    std::vector<unsigned int> nbs_j;
    std::vector<unsigned int> vec_xj = convert_index_from_j(j, m_d, m_L);
    for (int n = 0; n < m_d; ++n) {
        std::vector<unsigned int> positive_nb = vec_xj;
        positive_nb[n] = mod1((positive_nb[n] + 1), m_L); // respect periodic boundaries
        std::vector<unsigned int> negative_nb = vec_xj;
        negative_nb[n] = mod1((negative_nb[n] - 1), m_L); // respect periodic boundaries

        nbs_j.push_back(convert_index_to_j(positive_nb, m_d, m_L));
        nbs_j.push_back(convert_index_to_j(negative_nb, m_d, m_L));
    }
    return nbs_j;
};


int BaseLattice::get_M() const {
    int M = 0;
    for (Spin spin_n : m_lat) {
        M += spin_n.get_spin();
    }
    return M;
};

std::vector<bool> BaseLattice::get_lattice() const {
    std::vector<bool> lattice;
    for (Spin spin_j : m_lat) {
        lattice.push_back(spin_j.get_spin_bool());
    }
    return lattice;
};

std::string BaseLattice::str() const {
    std::stringstream ss;
    float mag = get_M();
    float mag_per_spin = mag / m_size;
    if (m_d == 1) {
        for (Spin spin_n : m_lat) {
            ss << spin_n.str() << " ";
        }
        ss << "\n";
    } else if (m_d == 2){
        int counter = 0;
        for (Spin spin_n : m_lat) {
            ss << spin_n.str() << " ";
            ++counter;
            if (counter == m_L) {
                ss << "\n";
                counter = 0;
            }
        }
        ss << "\n";
    } else {
        ss << "<only lattices up to d = 2 can be displayed in text>" << "\n";
    }

    ss << "d = " << m_d << ", L = " << m_L << ", M = " << mag << ", M/L^d = " << mag_per_spin << std::endl;
     
    return ss.str();
};


std::ostream& operator<<(std::ostream& os, const BaseLattice& lat) {
    return os << lat.str();
};