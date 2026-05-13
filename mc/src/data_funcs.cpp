#include "data_funcs.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

void save_lattices(const std::vector<std::vector<bool>>& vvb, const std::string wpath) {
    std::ofstream out_file;
    out_file.open(wpath, std::ios_base::out);
    if (!out_file) {
        std::cout << "Could not open output file to write in it." << std::endl;
    } else {
        for (auto vb : vvb) {
            for (auto b : vb) {
                out_file << b ? "1" : "0";
            }
            out_file << "\n";
        }
        out_file.close();
    }
};


void save_list_int(const std::vector<int>& vi, const std::string wpath) {
    std::ofstream out_file;
    out_file.open(wpath, std::ios_base::out);
    if (!out_file) {
        std::cout << "Could not open output file to write in it." << std::endl;
    } else {
        for (auto i : vi) {
                out_file << i << ",";
        }
        out_file.close();
    }
};


void save_list_double(const std::vector<double>& vd, const std::string wpath) {
    std::ofstream out_file;
    out_file.open(wpath, std::ios_base::out);
    if (!out_file) {
        std::cout << "Could not open output file to write in it." << std::endl;
    } else {
        for (auto d : vd) {
                out_file << d << ",";
        }
        out_file.close();
    }
};

void save_list_size_t(const std::vector<size_t>& vst, const std::string wpath) {
    std::ofstream out_file;
    out_file.open(wpath, std::ios_base::out);
    if (!out_file) {
        std::cout << "Could not open output file to write in it." << std::endl;
    } else {
        for (auto st : vst) {
                out_file << st << ",";
        }
        out_file.close();
    }
};

std::string get_base_name_sT(int d, int L, double T, int N, bool cu, bool warm) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << "sT_d" << d 
       << "_L" << L
       << "_T" << T
       << "_N" << N
       << (cu ? "_mh_cl" : "_mh")
       << (warm ? "_warm" : "_cold");
    return ss.str();
};