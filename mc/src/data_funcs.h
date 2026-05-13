#ifndef DATA_FUNCS_H
#define DATA_FUNCS_H

#include <vector>
#include <fstream>
#include <iostream>

// save for animation of thermalization
void save_lattices(const std::vector<std::vector<bool>>& vvb, const std::string wpath);

// save observables as csv
void save_list_int(const std::vector<int>& vi, const std::string wpath);
void save_list_double(const std::vector<double>& vi, const std::string wpath);
void save_list_size_t(const std::vector<size_t>& vst, const std::string wpath);

// generate string base for output files
std::string get_base_name_sT(int d, int L, double T, int N, bool cu, bool warm);


#endif