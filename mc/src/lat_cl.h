#ifndef LAT_CL_H
#define LAT_CL_H

#include "lat_base.h"
#include "lat_mh.h"
#include "spin.h"

#include <vector>

// check if int is in a vec
bool is_in_vec(const unsigned int j, const std::vector<unsigned int> vec);

class ClLattice : public MHLattice {
    public:
        // constructor and destructor
        ClLattice(int d, int L, double T, bool is_warm);
        virtual ~ClLattice() {};

        std::vector<unsigned int> get_cluster() const;
        void flip_cluster(const std::vector<unsigned int> cluster_vec);
        std::vector<size_t> get_cluster_sizes() const { return cluster_sizes; };

        void get_and_flip_cluster();
        

    private:
        std::vector<size_t> cluster_sizes; // cluster size each time it is constructed.
};





#endif