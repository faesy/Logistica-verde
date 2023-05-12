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
#include "Construtor.h"
#include "CriadorInstancias.h"
#include <chrono>
#include <thread>
#include <time.h>
#include "ListaSol.h"
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


    CriadorInstancias *instancia = new CriadorInstancias();


    srand(time(NULL));


    int numDeIter=100;
    int numDeSol=100;
    float numDeNovasSol=0.1; //porcentagem de novas soluções a cada iteração
    int chanceDeMut=30; //a cada 1000
    int chanceDeBl=100;//a cada 1000

    

    ListaSol *listaInicial = new ListaSol(instancia);


    listaInicial->ConstruirSolucoes(numDeSol,output_file);
    BL *buscaLocal = new BL(instancia);


    OperadorSelecao *operador = new OperadorSelecao();

    for(int i=0;i<numDeIter;i++){

        for(Solucao *itr=listaInicial->primeira_sol; itr != NULL; itr=itr->get_prox_solucao()){

                int sorteado = (rand() % 1000) + 1;
                if(sorteado<=chanceDeBl){
                    buscaLocal->ChamadaDaBL1(itr,instancia->get_n()*2);
                    buscaLocal->ChamadaDaBL2(itr,instancia->get_n()/2);
                }

        }

        //output_file<<endl;
        //output_file<<endl;
        //output_file<<" Iteração "<<i<<endl;
        //for(Solucao *p = listaInicial->primeira_sol;p!=NULL;p=p->get_prox_solucao()){
        //listaInicial->Imprimir(p,output_file);
        //}

    ListaSol *novaLista = new ListaSol(instancia);


    novaLista=operador->RealizaSelecao(listaInicial);//adiciona a fronteira de pareto na nova lista
    output_file<<"Iteracao "<<i<<endl;
    output_file<<"Tamanho da Fronteira de pareto = "<<novaLista->tamanho<<endl;
    novaLista->ImprimirPython(output_file,i);


    int numDeFilhos= (numDeSol-novaLista->tamanho) * (1-numDeNovasSol);

    

        for(int j=0;j<numDeFilhos;j++){
        Solucao *sol1=operador->Vaga(listaInicial,2);
        Solucao *sol2=operador->Vaga(listaInicial,4);

        operador->crossover1(sol1,sol2,novaLista,chanceDeMut);
        }

        int novasSolucoes=numDeSol-novaLista->tamanho;

        novaLista->ConstruirSolucoes(novasSolucoes,output_file);

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
