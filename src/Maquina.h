#ifndef Maquina_H_INCLUDED
#define Maquina_H_INCLUDED

using namespace std;


class Maquina{

    // Attributes
    private:
    int id;
        Maquina* prox_maquina;
        Maquina* ant_maquina;

        float vp;//velocidade de processamento
        float ge;//gasto de energia


    public:
        // Constructor
    Maquina(int tipo);

    void set_prox_Maquina(Maquina* a);
    void set_ant_Maquina(Maquina* a);
    Maquina* get_prox_Maquina();
    Maquina* get_ant_Maquina();
    void set_id(int id){this->id=id;}
    int get_id(){return this->id;}

    float get_vp();
    float get_ge();
}; 

#endif 