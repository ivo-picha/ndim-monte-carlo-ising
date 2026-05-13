#include "spin.h"

#include <iostream>
#include <sstream>

Spin::Spin(bool is_up) : m_is_up(is_up) {};

short signed int Spin::get_spin() const {
    return m_is_up ? 1 : -1;
};

void Spin::flip() {
    m_is_up = !m_is_up;
};

std::string Spin::str() const {
    std::stringstream ss;
    ss << (get_spin_bool() ? "↑" : "↓");
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Spin& s) {
    return os << s.str();
}