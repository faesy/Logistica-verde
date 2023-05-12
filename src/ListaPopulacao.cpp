#include <iostream>
#include "ListaPopulacao.h"
#include <fstream>

using namespace std;

void ListaPopulacao::ConstruirSolucoes(int qtd_sol,ofstream &output_file,Instancia* instancia)
{
    Construtivo *construtivo;
    for(int i=0;i<qtd_sol;i++){
        this->AdicionaSolucao(construtivo->criaSol(instancia));
}
}

void ListaPopulacao::Imprimir(Solucao *solucao,ofstream &output_file,Instancia* instancia){

    for (int i = 0; i < instancia->get_m(); i++)
    {
        output_file << "Maquina " << i << " : ";
        for (int j = 0; j < instancia->get_n(); j++)
        {
            if(solucao->jobs[j]==i){
            output_file << j << " -> ";
            }
        }
        output_file <<endl;
    }
    output_file << "Makespam: " << solucao->makespam << endl;
    output_file << "Custo Energetico: " << solucao->custoEnergia << endl;
}

void ListaPopulacao::ImprimirPython(ofstream &output_file,int num){

    output_file << "makespam"<<num<<" = [";
    for (Solucao* i = this->primeira_sol;i!=NULL;i=i->get_prox_solucao())
    {
        if(i->get_prox_solucao()==NULL){
            output_file <<i->makespam;
        }else{
            output_file <<i->makespam<<",";
        }
    }
    output_file <<"]"<<endl;

    output_file << "custo_energetico"<<num<<" = [";
    for (Solucao* i = this->primeira_sol;i!=NULL;i=i->get_prox_solucao())
    {
        if(i->get_prox_solucao()==NULL){
            output_file <<i->custoEnergia;
        }else{
            output_file <<i->custoEnergia<<",";
        }
    }
    output_file <<"]"<<endl;

}


ListaPopulacao::ListaPopulacao(Instancia *instancia)
{
    this->primeira_sol=NULL;
    this->ultima_sol=NULL;
    this->tamanho=0;
}

void ListaPopulacao::AdicionaSolucao(Solucao *sol)
{
    this->tamanho++;
    if(this->primeira_sol==NULL){

        this->primeira_sol=sol;
        this->ultima_sol=sol;

        sol->set_ant_solucao(NULL);
        sol->set_prox_solucao(NULL);

        sol->pos=0;

    }else{

        sol->set_ant_solucao(this->ultima_sol);
        this->ultima_sol->set_prox_solucao(sol);
        this->ultima_sol=sol;

        sol->set_prox_solucao(NULL);

        sol->pos=sol->get_ant_solucao()->pos + 1;

    }
}


Solucao* ListaPopulacao::BuscaSol(int pos){

    for(Solucao *a = this->primeira_sol;a!=NULL;a=a->get_prox_solucao()){
        if (a->pos==pos){
            return a;
        }
    }
     
     return NULL;
}

