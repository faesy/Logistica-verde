#ifndef Processo_H_INCLUDED
#define Processo_H_INCLUDED

using namespace std;


class Processo{

    // Attributes
    private:
        int id;

        float qt;//quantidade de trabalho cm3

        int num_maquinas;

        Processo* prox_processo;
        Processo* ant_processo;

    public:
        float tempos_processamento[20];
        float custos_energia[20];
        // Constructor
        Processo();
        ~Processo();

        void set_qt(float a);
        void set_id(int a){this->id=a;}
        int get_id(){return this->id;}
        float get_qt();

        void set_num_maquinas(int a);
        int get_num_maquinas();

        void set_prox_Processo(Processo* a);
        void set_ant_Processo(Processo* a);
        Processo* get_prox_Processo();
        Processo* get_ant_Processo();

        

}; 

#endif 