#ifndef Intervalo_H_INCLUDED
#define Intervalo_H_INCLUDED

using namespace std;


class Intervalo{

    // Attributes
    private:
        int tk; //duração do intervalo
        float prk; //custo durante o intervalo

        Intervalo* prox_Intervalo;
        Intervalo* ant_Intervalo;

    public:
        // Constructor
        Intervalo(){}
        ~Intervalo(){}

        void set_prox_Intervalo(Intervalo* a);
        void set_ant_Intervalo(Intervalo* a);
        Intervalo* get_prox_Intervalo();
        Intervalo* get_ant_Intervalo();

        void set_tk(int a);
        int get_tk();
        void set_prk(float a);
        float get_prk();


    

}; 

#endif 