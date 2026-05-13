#ifndef SPIN_H
#define SPIN_H

#include <iostream>

class Spin {
    public:
        // constructor and destructor
        Spin(bool is_up);
        virtual ~Spin() {};

        // getter
        short signed int get_spin() const;

        bool get_spin_bool() const { return m_is_up; };

        // flip spin
        void flip();

        // string method
        std::string str() const;

    private:
        bool m_is_up;
};

std::ostream& operator<<(std::ostream& os, const Spin& s);



#endif