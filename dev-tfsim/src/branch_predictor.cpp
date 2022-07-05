#include "branch_predictor.hpp"
#include <iostream>
using namespace std;

branch_predictor::branch_predictor(unsigned int t, unsigned int tp) : n_bits(t),
                                                                      type(tp)
{
    max = (1 << n_bits) - 1;
    state = 0;
    n_acerto = 0;
    n_erro = 0;
    total = 0;
}

bool branch_predictor::predict()
{
    switch (type)
    {
    case 0:
        return state & (1 << (n_bits - 1));
        break;
    case 1:
    case 2:
    default:
        return state;
        break;
    }
}

bool branch_predictor::predict(int dest)
{

    total++;
    cout << "Total de Predição:" << total << "\n";
    switch (type)
    {
    case 0: // dinamico
        return state & (1 << (n_bits - 1));
        break;
    case 1: // desvio taken para cima
        if (dest > 0)
        {
            cout << "Desvio para cima (V1) TAKEN:" << dest << "\n";
            state = 1;
            return true; // taken
        }
        else
        {
            cout << "Desvio para baixo (V1) NOT TAKEN:" << dest << "\n";
            state = 0;
            return false; // not taken
        }
        break;

    case 2: // desvio not taken para cima
        if (dest > 0)
        {
            cout << "Desvio para cima (V2) NOT TAKEN:" << dest << "\n";
            state = 0;
            return false; // not taken
        }
        else
        {
            cout << "Desvio para baixo (V2)  TAKEN: " << dest << "\n";
            state = 1;
            return true; // taken
        }

        break;

    default:
        return state & (1 << (n_bits - 1));
        break;
    }
}

void branch_predictor::update_state(bool taken)
{

    switch (type)
    {
    case 0:
        if (taken)
        {
            state = ++state > max ? max : state;
        }
        else if (state)
        {
            state = --state < 0 ? 0 : state;
        }
        break;
    default:
        break;
    }
}

void branch_predictor::taxa_de_acerto(int pred, int rob_pred)
{
    float taxa_acerto = 0.0;
    if (pred != rob_pred)
        n_erro++;

    n_acerto = total - n_erro;

    taxa_acerto = float(n_acerto) / total;

    cout << "Taxa de Acerto: " << taxa_acerto << " = (Acertos(" << n_acerto << ") / Total (" << total << "))\n";
}
