#include <iostream>
#include "ListaSol.h"
#include <fstream>

using namespace std;

void ListaSol::ConstruirSolucoes(int qtd_sol,ofstream &output_file)
{
    for(int i=0;i<qtd_sol;i++){
        Construtor *construtor= new Construtor(this->instancia);
        construtor->solucao->id=i;
        this->AdicionaSolucao(construtor->solucao);
        //output_file<<"Sol "<<i<<" Construida"<<endl;
        //this->Imprimir(construtor->solucao,output_file);
       // output_file<< construtor->solucao->makespam <<"   "<<construtor->solucao->custoEnergia<< endl;
    //output_file << "Custo Energetico: " << construtor->solucao->custoEnergia << endl;

}
}

void ListaSol::Imprimir(Solucao *solucao,ofstream &output_file){

    for (int i = 0; i < solucao->instancia->get_m(); i++)
    {
        output_file << "Maquina " << i << " : ";
        for (int j = 0; j < solucao->instancia->get_n(); j++)
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

void ListaSol::ImprimirPython(ofstream &output_file,int num){

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

// void ListaSol::Imprimir(Solucao *solucao,ofstream &output_file){

//     for (MaquinaSol *a = solucao->primeira_maquina; a != NULL; a = a->prox_maquinaSol)
//     {
//         output_file << "Maquina " << a->id << " : ";
//         for (ProcessoSol *b = a->primeiro_processoSol; b != NULL; b = b->prox_processoSol)
//         {
//             output_file << b->id << " -> ";
//         }
//         output_file << "Tempo final: " << a->min_Atual << " || Custo Energetico: "<<a->CE<<endl;
//     }
//     output_file << "Makespam: " << solucao->makespam << endl;
//     output_file << "Custo Energetico: " << solucao->custoEnergia << endl;
// }


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
