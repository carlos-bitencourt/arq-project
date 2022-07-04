#include "branch_predictor.hpp"
#include <iostream>
using namespace std;

branch_predictor::branch_predictor(unsigned int t, unsigned int tp) : n_bits(t),
                                                                      type(tp)
{
    max = (1 << n_bits) - 1;
    state = 0;
}

bool branch_predictor::predict(int dest)
{

    switch (type)
    {
    case 0: // dinamico
        return state & (1 << (n_bits - 1));
        break;
    case 1: // desvio taken para cima
        if (dest > 0)
        {
            cout << "Desvio para cima (V1) TAKEN: " << dest << "\n";
            return true; // taken
        }
        else
        {
            cout << "Desvio para baixo (V1) NOT TAKEN: " << dest << "\n";
            return false; // not taken
        }
        break;

    case 2: // desvio not taken para cima
        if (dest > 0)
        {
            cout << "Desvio para cima (V2) NOT TAKEN: " << dest << "\n";
            return false; // not taken
        }
        else
        {
            cout << "Desvio para baixo (V2)  TAKEN: " << dest << "\n";
            return true; // taken
        }

        break;

    default:
        break;
    }
}

void branch_predictor::update_state(bool taken)
{
    if (taken)
    {
        state = ++state > max ? max : state;
    }
    else if (state)
    {
        state = --state < 0 ? 0 : state;
    }
}

void branch_predictor::set_type(int tp)
{
    if (tp >= 0 || tp <= 3)
        type = tp;
    else
        cout << "Falha ao configurar o preditor. \n";
}