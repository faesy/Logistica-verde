#include "Processo.h"
#include <iostream>

using namespace std;

Processo::Processo(){

    for(int i=0;i<20;i++){
        tempos_processamento[i]=-1;
        custos_energia[i]=-1;
    }

}

Processo::~Processo(){

}

void Processo::set_qt(float a){
    this->qt=a;
}
float Processo::get_qt(){
return this->qt;
}

void Processo::set_num_maquinas(int a){
this->num_maquinas=a;
}
int Processo::get_num_maquinas(){
return this->num_maquinas;
}

void Processo::set_prox_Processo(Processo* a){
this->prox_processo=a;
}
void Processo::set_ant_Processo(Processo* a){
this->ant_processo=a;
}
Processo* Processo::get_prox_Processo(){
return this->prox_processo;
}
Processo* Processo::get_ant_Processo(){
return this->ant_processo;
}