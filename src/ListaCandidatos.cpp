#include <iostream>
#include "ListaCandidatos.h"

using namespace std;

ListaCandidatos::ListaCandidatos(){

tamanho=0;
this->primeiro_elemento=NULL;
this->ultimo_elemento=NULL;
}

void ListaCandidatos::Zera_Lista(){
Candidato* currNode=this->primeiro_elemento;
Candidato* nextNode=NULL;
while(currNode!=NULL){
    nextNode=currNode->prox_elemento;
    delete currNode;
    currNode=nextNode;
}

this->primeiro_elemento=NULL;
tamanho=0;
this->ultimo_elemento=NULL;

}

void ListaCandidatos::Adicionar_na_Lista(int id_maquina,int qtd){

    for(int i=0;i<qtd;i++){
Candidato* elemento= new Candidato();
elemento->id=id_maquina;
if(this->primeiro_elemento==NULL){
    tamanho++;
    elemento->prox_elemento=NULL;
    elemento->ant_elemento=NULL;
    this->primeiro_elemento=elemento;
    this->ultimo_elemento=elemento;
}else{
    tamanho++;
    elemento->prox_elemento=NULL;
    elemento->ant_elemento=this->ultimo_elemento;
    this->ultimo_elemento->prox_elemento=elemento;
    this->ultimo_elemento=elemento;
}
    }


}

void ListaCandidatos::Remove_na_Lista(int id_maquina,int qtd){

    if (qtd==0)
    {
        return;
    }
    
    if(this->primeiro_elemento==NULL && this->ultimo_elemento==NULL){
        return;
    }
    for(int i=0;i<qtd;i++){
        int contador=0;
    for(Candidato* i=this->primeiro_elemento;i!=NULL;i=i->prox_elemento){
        if(i->id==id_maquina){
            if (tamanho==1)
            {
                this->primeiro_elemento=NULL;
                this->ultimo_elemento=NULL;
                delete i;
                tamanho=0;
                break;
            }
            if(contador==0){
                i->prox_elemento->ant_elemento=NULL;
                this->primeiro_elemento=i->prox_elemento;
                tamanho--;
                delete i;
                break;
            }else if(i->prox_elemento==NULL){
                i->ant_elemento->prox_elemento=NULL;
                this->ultimo_elemento->ant_elemento;
                tamanho--;
                delete i;
                break;
            }else{
            i->ant_elemento->prox_elemento=i->prox_elemento;
            i->prox_elemento->ant_elemento=i->ant_elemento;
            tamanho--;
            delete i;
            break;
            }
        }
        contador++;
    }
    }

}

int ListaCandidatos::Sorteia_na_Lista(){

    int numSort = rand() % tamanho;

    int contador=0;
    for(Candidato* i=this->primeiro_elemento;i!=NULL;i=i->prox_elemento){
        if(contador==numSort){
            return i->id;
        }
        contador++;
    }
    
    return -1;
}

void ListaCandidatos::Imprime(){
    cout<<"LISTA : ";
    for(Candidato* a=this->primeiro_elemento;a!=NULL;a=a->prox_elemento){
        cout<< a->id <<" ";
    }
    cout<<endl;
}