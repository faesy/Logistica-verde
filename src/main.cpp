/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Construtivo.h"
#include "Instancia.h"
#include <chrono>
#include <thread>
#include <time.h>
#include "ListaPopulacao.h"
#include "BL.h"
#include "OperadorSelecao.h"

using namespace std;

int main(int argc, char const *argv[])
{

    // string nomeArquivo;
    // cout << "Digite o nome do arquivo" << endl;
    // cin >> nomeArquivo;
    ofstream output_file;

    output_file.open("teste2.txt", ios::out | ios::trunc);

    int cod_instancia = 0;
    // cout << "Digite o codigo da Instancia: ";
    // cin >> instancia;
    // 1670879965
    // 1670879893
    // 1670879957
    cod_instancia = 1670879895;
    srand(cod_instancia);


    Instancia *instancia = new Instancia();


    srand(time(NULL));


    int numDeIter=200;
    int numDeSol=100;
    float numDeNovasSol=0.05; //porcentagem de novas soluções a cada iteração
    int chanceDeMut=30; //a cada 1000
    int chanceDeBl=100;//a cada 1000


    ListaPopulacao *listaInicial = new ListaPopulacao(instancia);

    listaInicial->ConstruirSolucoes(numDeSol,output_file,instancia);

    BL *buscaLocal = new BL();

    OperadorSelecao *operador;

    for(int i=0;i<numDeIter;i++){

        for(Solucao *itr=listaInicial->primeira_sol; itr != NULL; itr=itr->get_prox_solucao()){

                int sorteado = (rand() % 1000) + 1;
                if(sorteado<=chanceDeBl){
                    buscaLocal->ChamadaDaBL(itr,instancia);
                }

        }

        //output_file<<endl;
        //output_file<<endl;
        //output_file<<" Iteração "<<i<<endl;
        //for(Solucao *p = listaInicial->primeira_sol;p!=NULL;p=p->get_prox_solucao()){
        //listaInicial->Imprimir(p,output_file);
        //}

    ListaPopulacao *novaLista = new ListaPopulacao(instancia);


    novaLista=operador->RealizaSelecao(listaInicial,instancia);//adiciona a fronteira de pareto na nova lista
    output_file<<"Iteracao "<<i<<endl;
    output_file<<"Tamanho da Fronteira de pareto = "<<novaLista->tamanho<<endl;
    novaLista->ImprimirPython(output_file,i);


    int numDeFilhos= (numDeSol-novaLista->tamanho) * (1-numDeNovasSol);

    

        for(int j=0;j<numDeFilhos;j++){
        Solucao *sol1=operador->Vaga(listaInicial,2,instancia);
        Solucao *sol2=operador->Vaga(listaInicial,2,instancia);

        int crossover = (rand() % 2);
        if(crossover==0){
        operador->crossover1(sol1,sol2,novaLista,chanceDeMut,instancia);
        }else{
        operador->crossover2(sol1,sol2,novaLista,chanceDeMut,instancia);
        }
        }

        int novasSolucoes=numDeSol-novaLista->tamanho;

        novaLista->ConstruirSolucoes(novasSolucoes,output_file,instancia);

        listaInicial=novaLista;
    }




    //sol->Imprimir(sol->BuscaSol(0),output_file);


    //BL *bl = new BL(a);
   // ConjuntoPopulacional *populacao = new ConjuntoPopulacional(numeroDeSolucoesTotais);
    //for (int i = 0; i < numeroDeSolucoesTotais; i++)
    //{

        //Construtor *b = new Construtor(instancia);
        //b->solucao->id = i;

        // b->Imprime();
        // bl->AdicionaProcesso(b->solucao->primeira_maquina,a->buscaProcesso(b->solucao->primeira_maquina->primeiro_processoSol->id),1);
        // b->Imprime();

        //bl->AtualizaCustos(b->solucao);
        // b->Imprime();

        // b->Imprime();
        // bl->AtualizaCustos(b->solucao);
        // cout<<b->solucao->makespam<<endl;
        //populacao->preencheListasPorRequisito(b->solucao);
    //}


    return 0;
}
