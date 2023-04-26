#include "OperadorSelecao.h"
#include <iostream>

using namespace std;

ListaSol* OperadorSelecao::RealizaSelecao(ListaSol *listaInicial){

ListaSol *novaLista = new ListaSol(listaInicial->instancia);

        //Adiciono A fronteira de Pareto na nova lista
        for(Solucao *a=listaInicial->primeira_sol;a!=NULL;a=a->get_prox_solucao()){//olho sol a sol
        bool flag=true;
                for(Solucao *b=listaInicial->primeira_sol;b!=NULL;b=b->get_prox_solucao()){ //começo a comparar com outras soluções
                        if ((a->makespam < b->makespam && a->custoEnergia <= b->custoEnergia) || (a->makespam <= b->makespam && a->custoEnergia < b->custoEnergia)) //se a sol for melhor
                        {

                        }else{
                            flag=false;
                            break;
                        }
                }
                if(flag==true){
                novaLista->AdicionaSolucao(a);
                }
        }

        int tamanho = listaInicial->tamanho;

        



}

Solucao* OperadorSelecao::Vaga(ListaSol *listaInicial, int numContestantes){//sorteio de vaga 

int tamanho = listaInicial->tamanho;

int melhorContestante = rand() % tamanho;

for(int i=0;i<numContestantes-1;i++){
        
int novoContestante = rand() % tamanho;

if ((listaInicial->BuscaSol(melhorContestante)->makespam < listaInicial->BuscaSol(novoContestante)->makespam && listaInicial->BuscaSol(melhorContestante)->custoEnergia <= listaInicial->BuscaSol(novoContestante)->custoEnergia) || (listaInicial->BuscaSol(melhorContestante)->makespam <= listaInicial->BuscaSol(novoContestante)->makespam && listaInicial->BuscaSol(melhorContestante)->custoEnergia < listaInicial->BuscaSol(novoContestante)->custoEnergia)) 
{//se melhor contestante ainda for não dominado

}else{
melhorContestante=novoContestante;
}



}

return listaInicial->BuscaSol(melhorContestante);

}


Solucao* OperadorSelecao::crossover1(Solucao* parente1,Solucao* parente2){

    Solucao *filho = new Solucao();
    filho->instancia=parente1->instancia;

    for(int i=0;i<parente1->instancia->get_n();i++){

        if(i%2==0){//se i for par
            filho->jobs[i]=parente1->jobs[i];
        }
        if(i%2==1){//se i for impar
            filho->jobs[i]=parente2->jobs[i];
        }
    }

    int makespams[20];
    int custos[20];

    for(int i=0;i<20;i++){
        makespams[i]=0;
        custos[i]=0;
    }

    for(int i=0;i<parente1->instancia->get_n();i++){

        makespams[filho->jobs[i]]= makespams[filho->jobs[i]] + filho->instancia->buscaProcesso(i)->tempos_processamento[filho->jobs[i]];

        custos[filho->jobs[i]] = custos[filho->jobs[i]] + filho->instancia->buscaProcesso(i)->custos_energia[filho->jobs[i]];

    }

}