#include "OperadorSelecao.h"
#include <iostream>

using namespace std;

ListaSol* OperadorSelecao::RealizaSelecao(ListaSol *listaInicial){

ListaSol *novaLista = new ListaSol(listaInicial->instancia);

        //Adiciono A fronteira de Pareto na nova lista
        for(Solucao *a=listaInicial->primeira_sol;a!=NULL;a=a->get_prox_solucao()){//olho sol a sol
        bool flag=true;
                for(Solucao *b=listaInicial->primeira_sol;b!=NULL;b=b->get_prox_solucao()){ //começo a comparar com outras soluções
                        if ((a->makespam < b->makespam /*&& a->custoEnergia <= b->custoEnergia*/) || (/*a->makespam <= b->makespam &&*/ a->custoEnergia < b->custoEnergia) || (a->custoEnergia==b->custoEnergia && a->makespam==b->makespam))
                        {
                        }else{
                            flag=false;
                            break;
                        }
                }
                if(flag==true){
                    Solucao *filho = new Solucao();
                    filho->instancia=a->instancia;

                    for(int i=0;i<a->instancia->get_n();i++){
                        filho->jobs[i]=a->jobs[i];
                    }

                    filho->custoEnergia=a->custoEnergia;
                    filho->makespam=a->makespam;
                    //cout<<"Adicionou na lista"<<endl;
                novaLista->AdicionaSolucao(filho);
                }
        }

        int tamanho = listaInicial->tamanho;

        


    return novaLista;
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


void OperadorSelecao::crossover1(Solucao* parente1,Solucao* parente2,ListaSol *listaNova){

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

    
    this->mutacao(filho,0);
    

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


    int maiorMakespam=0;
    for(int i=0;i<20;i++){
        filho->custoEnergia=filho->custoEnergia+ custos[i];
        if( makespams[i]>maiorMakespam){
            maiorMakespam=makespams[i];
        }
    }
    filho->makespam=maiorMakespam;

    listaNova->AdicionaSolucao(filho);

}

void OperadorSelecao::crossover2(Solucao* parente1,Solucao* parente2,ListaSol *listaNova){

    Solucao *filho = new Solucao();
    filho->instancia=parente1->instancia;

    int n_jobs=parente1->instancia->get_n();

    int pontoDeCorte1;
    int pontoDeCorte2;

    pontoDeCorte1= rand() % n_jobs;

    while(pontoDeCorte1==n_jobs-1){
        pontoDeCorte1= rand() % n_jobs;
    }

    pontoDeCorte2=rand() % n_jobs;

     while(pontoDeCorte2<=pontoDeCorte1){
        pontoDeCorte2= rand() % n_jobs;
    }

    for(int i=0;i<parente1->instancia->get_n();i++){

        if(i<pontoDeCorte1){//se i for par
            filho->jobs[i]=parente1->jobs[i];
        }
        if(i>pontoDeCorte1 && i<pontoDeCorte2){//se i for impar
            filho->jobs[i]=parente2->jobs[i];
        }
        if(i>pontoDeCorte2){//se i for impar
            filho->jobs[i]=parente1->jobs[i];
        }

    }

    this->mutacao(filho,5);

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

    int maiorMakespam=0;
    for(int i=0;i<20;i++){
        filho->custoEnergia=filho->custoEnergia+ custos[i];
        if( makespams[i]>maiorMakespam){
            maiorMakespam=makespams[i];
        }
    }
    filho->makespam=maiorMakespam;

    listaNova->AdicionaSolucao(filho);
}

void OperadorSelecao::mutacao(Solucao* alvo,int chancePorJob){ //chance de acontecer em 1000 possibilidades

    for(int i=0;i<alvo->instancia->get_n();i++){
        int sorteado = (rand() % 1000) + 1;
        if(sorteado<=chancePorJob){
            cout<<"Houve mutacao"<<endl;
            int novaMaq= rand() % alvo->instancia->get_m();
            alvo->jobs[i]=novaMaq;
        }
    }

}