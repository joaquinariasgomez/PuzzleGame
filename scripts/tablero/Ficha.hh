#pragma once
#include <string>

class Ficha {
    public:
        virtual std::string print() const = 0;
    private:
        bool oponente;  //true if it is oponent. false if not
};