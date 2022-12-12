#include <iostream>
#include "Solucao.h"

using namespace std;

void Solucao::set_prox_solucao(Solucao* a){
this->prox_Solucao=a;
}

void Solucao::set_ant_solucao(Solucao* a){
this->ant_Solucao=a;
}
Solucao* Solucao::get_prox_solucao(){
return this->prox_Solucao;
}
Solucao* Solucao::get_ant_solucao(){
return this->ant_Solucao;
}