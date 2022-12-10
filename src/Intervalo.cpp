
#include "Intervalo.h"
#include <iostream>

using namespace std;

void Intervalo::set_prox_Intervalo(Intervalo* a){
this->prox_Intervalo=a;
}
void Intervalo::set_ant_Intervalo(Intervalo* a){
this->ant_Intervalo=a;
}
Intervalo* Intervalo::get_prox_Intervalo(){
return this->prox_Intervalo;
}
Intervalo* Intervalo::get_ant_Intervalo(){
return this->ant_Intervalo;
}


void Intervalo::set_tk(int a){
this->tk=a;
}
int Intervalo::get_tk(){
return this->tk;
}
void Intervalo::set_prk(float a){
this->prk=a;
}
float Intervalo::get_prk(){
return this->prk;
}