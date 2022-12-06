#include "Maquina.h"
#include <iostream>

using namespace std;

Maquina::Maquina(int tipo){

    if(tipo==0){
        this->vp=282;
        this->ge=4.7;
    }else if(tipo==1){
        this->vp=72;
        this->ge=0.2;
    }else if(tipo==2){
        this->vp=72;
        this->ge=0.4;
    }else if(tipo==3){
        this->vp=21;
        this->ge=0.1225;
    }

    this->prox_maquina=NULL;
    this->ant_maquina=NULL;

}


void Maquina::set_prox_Maquina(Maquina* a){
this->prox_maquina=a;
}

void Maquina::set_ant_Maquina(Maquina* a){
this->ant_maquina=a;
}
Maquina* Maquina::get_prox_Maquina(){
return this->prox_maquina;
}
Maquina* Maquina::get_ant_Maquina(){
return this->ant_maquina;
}

float Maquina::get_vp(){
    return this->vp;
}
float Maquina::get_ge(){
    return this->ge;
}
