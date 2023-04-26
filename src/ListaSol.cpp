#include <iostream>
#include "Construtor.h"
#include "ListaSol.h"
#include "Construtor.h"


using namespace std;

void ListaSol::ConstruirSolucoes(int qtd_sol)
{
    for(int i=0;i<qtd_sol;i++){
        Construtor *construtor= new Construtor(this->instancia);
        construtor->solucao->id=i;
        this->AdicionaSolucao(construtor->solucao);
    }

    //zera frente 
    //Analise de frentes de pareto
    //remove as X piores

    //Reproduz as restantes
    //repete
}


ListaSol::ListaSol(CriadorInstancias *instancia)
{
    this->instancia=instancia;
    this->primeira_sol=NULL;
    this->ultima_sol=NULL;
    this->tamanho=0;
}

void ListaSol::AdicionaSolucao(Solucao *sol)
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

void ListaSol::RemoveSolucao(int id)
{
    for(Solucao *a = this->primeira_sol;a!=NULL;a=a->get_prox_solucao()){
        if(a->id = id){
            this->tamanho--;
            if(a=this->primeira_sol){
                this->primeira_sol=a->get_prox_solucao();
                this->primeira_sol->set_ant_solucao(NULL);
                a->set_prox_solucao(NULL);
                cout<<"travou no delete"<<endl;
                delete a;
                break;
            }
            if(a=this->ultima_sol){
                this->ultima_sol=a->get_ant_solucao();
                this->ultima_sol->set_prox_solucao(NULL);
                a->set_ant_solucao(NULL);
                cout<<"travou no delete"<<endl;
                delete a;
                break;
            }else{
                a->get_ant_solucao()->set_prox_solucao(a->get_prox_solucao());
                a->get_prox_solucao()->set_ant_solucao(a->get_ant_solucao());
                a->set_prox_solucao(NULL);
                a->set_ant_solucao(NULL);
                cout<<"travou no delete"<<endl;
                delete a;
                break;
            }
        }
        cout<<"tentou remover um id que não existe"<<endl;
    }
    
}

Solucao* ListaSol::BuscaSol(int pos){

    for(Solucao *a = this->primeira_sol;a!=NULL;a=a->get_prox_solucao()){
        if (a->pos==pos){
            return a;
        }
    }
     
     return NULL;
}

// void ListaSol::ZeraFrentes(){
//     for(Solucao *a=this->primeira_sol;a!=NULL;a=a->get_prox_solucao()){
//         a->frente=-1;
//     }
// }

// void ListaSol::RemoveXsol(int x){
//     int ultimaFrente=-1;
//     for(Solucao *a=this->primeira_sol;a!=NULL;a=a->get_prox_solucao()){
//         if(a->frente>ultimaFrente){
//         ultimaFrente=a->frente;
//         }
//     }

//     int contador=0;

//     while(contador != x){
//         for(Solucao *a=this->primeira_sol;a!=NULL;a=a->get_prox_solucao()){
//             if (a->frente==ultimaFrente)
//             {
//                 this->RemoveSolucao(a->id);
//                 break;
//             }
//         }
//         ultimaFrente--;
//     }

// }



// void ListaSol::AnaliseDeFrentes()
// {
//     int frente_encontradas=0;
//     for(int i=0;;i++){
//         for(Solucao *a=this->primeira_sol;a!=NULL;a=a->get_prox_solucao()){//olho sol a sol
//             bool flag =true; //marco como se não tivesse melhores
//             if(a->frente==-1){ //verifico se ela ja não foi analisada
//                 for(Solucao *b=this->primeira_sol;b!=NULL;b=b->get_prox_solucao()){ //começo a comparar com outras soluções
//                 if(b->frente==-1){//se a solução que estou a comparar ainda não tiver sido analisada
//                         if ((a->makespam < b->makespam && a->custoEnergia <= b->custoEnergia) || (a->makespam <= b->makespam && a->custoEnergia < b->custoEnergia)) //se a sol for melhor
//                         {
//                             //contina marcada 
//                         }else{ //caso contrario
//                             flag =false;//desmarco e passo pra proxima
//                             break;
//                         }
//                     }
//                 }
//                 if(flag==true){// se ao final não houver melhores é pq ela pertence a essa frente
//                     a->frente=i;
//                     frente_encontradas++;
//                 }
//             }
//         }
//         if(frente_encontradas==this->tamanho){
//             break;
//         }
//     }

// }