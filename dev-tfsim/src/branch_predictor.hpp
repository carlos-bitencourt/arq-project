class branch_predictor
{
public:
    branch_predictor(unsigned int t, unsigned int tp);
    bool predict();
    bool predict(int dest);
    void update_state(bool taken);
    void taxa_de_acerto(int pred, int rob_pred);
    void taxa_de_acerto();

private:
    int n_bits, max, state;
    int type;                    // 0 - Dynamic, 1 - Taken Desvio pra cima, 2 - Not Taken Devio pra cima
    int n_acerto, n_erro, total; // para calculo da taxa de acerto.
    float taxa_acerto;
};
