#include <iostream>
#include "ConjuntoPopulacional.h"

using namespace std;

ConjuntoPopulacional::ConjuntoPopulacional(int tamanhoLista)
{
    this->lista1 = new int[tamanhoLista];
    this->lista2 = new int[tamanhoLista];
    this->lista3 = new int[tamanhoLista];
    int tamanhoListaPop = (tamanhoLista * 0.9);
    this->populacao = new int[tamanhoListaPop];
    this->primeira_Solucao = NULL;
    this->ultima_Solucao = NULL;
    for (int i = 0; i < tamanhoLista; i++)
    {
        this->lista1[i] = -1;
        this->lista2[i] = -1;
        this->lista3[i] = -1;
    }
    for (int j = 0; j < tamanhoListaPop; j++)
    {
        this->populacao[j] = -1;
    }
    this->tamanhoPop = 0;
    this->tamanhoLista = tamanhoLista;
    this->tamanhoMaxPop = tamanhoListaPop;
}

void ConjuntoPopulacional::preencheListasPorRequisito(Solucao *solucao)
{

    addSolucaoAListaIndexada(solucao); // adiciona numa lista com todas as soluções em ordem de criação

    bool jaFezInsercao1 = false; // verificadores de inserção para que o sistema de inserção não quebre, como tem apenas 1 inserção
    bool jaFezInsercao2 = false; //  por iteração do construtor de solução na main uma vez feita a inserção não há mais atividade,
    bool jaFezInsercao3 = false; //  assim com esses bools posso realizar um break para diminuir o tempo de execução

    for (int i = 0; i < tamanhoLista; i++) // for responsavel por criar as listas ordenadas.
    {
        if (jaFezInsercao1 == false)
        {

            if (this->lista1[i] == -1)
            {
                this->lista1[i] = solucao->id; // insere logo no final, assim não é necessario nenhum movimento a mais que sobreposição num espaço anteriormente vazio
                jaFezInsercao1 = true;
            }
            else if (solucao->custoEnergia < getSolucaoPorIndex(this->lista1[i])->custoEnergia) // verifica se é melhor em custoEnergia do que outra solução
            {

                insereEmLista1(solucao->id, i); // insere ja fazendo os movimentos necessarios dentro do array
                jaFezInsercao1 = true;
            }
        }

        if (jaFezInsercao2 == false)
        {

            if (this->lista2[i] == -1)
            {
                this->lista2[i] = solucao->id; // insere logo no final, assim não é necessario nenhum movimento a mais que sobreposição num espaço anteriormente vazio
                jaFezInsercao2 = true;
            }
            else if (solucao->makespam < getSolucaoPorIndex(this->lista2[i])->makespam) // verifica se é melhor em makespam do que outra solução
            {

                insereEmLista2(solucao->id, i); // insere ja fazendo os movimentos necessarios dentro do array
                jaFezInsercao2 = true;
            }
        }

        if (jaFezInsercao3 == false)
        {

            if (this->lista3[i] == -1)
            {
                this->lista3[i] = solucao->id; // insere logo no final, assim não é necessario nenhum movimento a mais que sobreposição num espaço anteriormente vazio
                jaFezInsercao3 = true;
            }
            else if (solucao->custoMonetario < getSolucaoPorIndex(this->lista3[i])->custoMonetario) // verifica se é melhor em custoMonetario do que outra solução
            {

                insereEmLista3(solucao->id, i); // insere ja fazendo os movimentos necessarios dentro do array
                jaFezInsercao3 = true;
            }
        }

        if (jaFezInsercao1 == true && jaFezInsercao2 == true && jaFezInsercao3 == true)
        {
            break; // finalizador de atividade de inserção
        }
    }
}

void ConjuntoPopulacional::addSolucaoAListaIndexada(Solucao *solucao)
{

    if (this->primeira_Solucao == NULL)
    {                                     // caso essa seja a primeira maquina adicionada
        this->primeira_Solucao = solucao; // essa solucao = primeira solucao
        this->ultima_Solucao = solucao;   // essa solucao = ultima solucao

        solucao->set_prox_solucao(NULL); // solucao seguinte n existe
        solucao->set_ant_solucao(NULL);  // solucao anterior não existe
    }
    else
    { // caso essa não seja a primera solucao adicionada

        this->ultima_Solucao->set_prox_solucao(solucao); // ultima solucao adiciona recebe como prox solucao essa
        solucao->set_ant_solucao(this->ultima_Solucao);  // essa solucao recebe a ultima solucao adicionada como ant solucao
        solucao->set_prox_solucao(NULL);                 ////solucao seguinte n existe
        this->ultima_Solucao = solucao;                  // essa solucao se torna a ultima solucao
    }
}

Solucao *ConjuntoPopulacional::getSolucaoPorIndex(int id)
{

    Solucao *sol;
    for (sol = this->primeira_Solucao; sol != NULL; sol = sol->get_prox_solucao()) // só um trem pra percorrer a lista e pegar a solução pelo index
    {
        if (sol->id == id)
        {
            return sol;
        }
    }

    return NULL;
}

void ConjuntoPopulacional::insereEmLista1(int id, int posicao)
{
    int valorNovo = id;                          // o valor novo na posição sera o novo id
    int valorVelho = this->lista1[posicao];      // o antigo id naquela posição é salvo como um valor velho
    for (int i = posicao; i < tamanhoLista; i++) // apartir da posição olhada se realiza a atualizaçao dos dados no array
    {

        this->lista1[i] = valorNovo; // abaixo é como ocorre o processo de substituição de um valor na posição anterior para uma posterior
        if (i + 1 < tamanhoLista)    // esse if existe só por precaução, teoricamente nunca chegara a ser falso
        {
            valorNovo = valorVelho; // atualização do ultimo valor
            valorVelho = this->lista1[i + 1];
        }
    }
}
void ConjuntoPopulacional::insereEmLista2(int id, int posicao)
{
    int valorNovo = id;                     // o valor novo na posição sera o novo id
    int valorVelho = this->lista2[posicao]; // o antigo id naquela posição é salvo como um valor velho

    for (int i = posicao; i < tamanhoLista; i++) // apartir da posição olhada se realiza a atualizaçao dos dados no array
    {

        this->lista2[i] = valorNovo; // abaixo é como ocorre o processo de substituição de um valor na posição anterior para uma posterior
        if (i + 1 < tamanhoLista)    // esse if existe só por precaução, teoricamente nunca chegara a ser falso
        {
            valorNovo = valorVelho; // atualização do ultimo valor
            valorVelho = this->lista2[i + 1];
        }
    }
}
void ConjuntoPopulacional::insereEmLista3(int id, int posicao)
{
    int valorNovo = id;                     // o valor novo na posição sera o novo id
    int valorVelho = this->lista3[posicao]; // o antigo id naquela posição é salvo como um valor velho

    for (int i = posicao; i < tamanhoLista; i++) // apartir da posição olhada se realiza a atualizaçao dos dados no array
    {

        this->lista3[i] = valorNovo; // abaixo é como ocorre o processo de substituição de um valor na posição anterior para uma posterior
        if (i + 1 < tamanhoLista)    // esse if existe só por precaução, teoricamente nunca chegara a ser falso
        {
            valorNovo = valorVelho; // atualização do ultimo valor
            valorVelho = this->lista3[i + 1];
        }
    }
}

void ConjuntoPopulacional::selecionaPopulacao2()
{

    bool *lista1bool = new bool[this->tamanhoLista];
    bool *lista2bool = new bool[this->tamanhoLista];
    bool *lista3bool = new bool[this->tamanhoLista];

    for (int i = 0; i < this->tamanhoLista; i++)
    {
        lista1bool[i] = false;
        lista2bool[i] = false;
        lista3bool[i] = false;
    }
    for (int k = 0; k < (alfa * tamanhoLista); k++)
    {

        lista1bool[this->lista1[k]] = true;
        lista2bool[this->lista2[k]] = true;
        lista3bool[this->lista3[k]] = true;
    }
    int j = 0;
    for (int l = 0; l < this->tamanhoLista; l++)
    {
        if (lista1bool[l] && lista2bool[l] && lista3bool[l])
        {
           
           j = insereSolNaPopDadoPosicaoJaConhecida(j, l);
           this->tamanhoPop = j;
        }
    }
}

void ConjuntoPopulacional::selecionaPopulacao()
{
    float alpha = 0.3;
    int ondeParou = 0;
    int i = 0;
    int j = 0;
    while (j < (alpha * tamanhoLista))
    {
        if (this->lista1[j] == this->lista2[j] && this->lista1[j] == this->lista3[j] && this->lista2[j] == this->lista3[j])
        {
            i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista1[j]);
        }
        else if (this->lista1[j] == this->lista2[j] && this->lista1[j] != this->lista3[j] && this->lista2[j] != this->lista3[j])
        {
            i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista1[j]);

            i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista3[j]);
        }
        else if (this->lista1[j] != this->lista2[j] && this->lista1[j] != this->lista3[j] && this->lista2[j] == this->lista3[j])
        {
            i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista1[j]);

            i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista3[j]);
        }
        else if (this->lista1[j] != this->lista2[j] && this->lista1[j] == this->lista3[j] && this->lista2[j] != this->lista3[j])
        {
            i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista1[j]);

            i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista2[j]);
        }
        // else
        // {
        //     i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista1[j]);

        //     i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista2[j]);

        //     i = insereSolNaPopDadoPosicaoJaConhecida(i, this->lista3[j]);

        // }
        this->tamanhoPop = i;
        j++;
    }
}

bool ConjuntoPopulacional::verificaSeJaTem(int id)
{
    for (int i = 0; i < this->tamanhoMaxPop; i++)
    {
        if (this->populacao[i] == id)
        {
            return true;
        }
    }
    return false;
}

int ConjuntoPopulacional::insereSolNaPopDadoPosicaoJaConhecida(int posicaoOndeSeraAdicionado, int idASerAdicionado)
{
    
    if (!verificaSeJaTem(idASerAdicionado))
    {
       
        this->populacao[posicaoOndeSeraAdicionado] = idASerAdicionado;
        return posicaoOndeSeraAdicionado + 1;
    }
    else
    {
       
        return posicaoOndeSeraAdicionado;
    }
}

void ConjuntoPopulacional::printPopListaIndexSol()
{
    cout << "Populacao composta pelas solucoes: ";
    for (int i = 0; i < getTamanhoPop(); i++)
    {
        if (i + 1 == getTamanhoPop())
        {
            cout << this->populacao[i] << endl;
        }
        else
        {
            cout << this->populacao[i] << ", ";
        }
    }


    for (int i = 0; i < getTamanhoPop(); i++){

        for(Solucao* a=this->primeira_Solucao;a!=NULL;a=a->get_prox_solucao()){
            if(a->id==this->populacao[i]){
        cout<<this->populacao[i]<<endl<<"Possui Makespam = "<<a->makespam<<endl<<"Custo de Energia= "<<a->custoEnergia<<endl<<"Custo Monetario= "<<a->custoMonetario<<endl<<endl;
            }
        }
    }
}

void ConjuntoPopulacional::printListas123()
{
    cout << "Lista1 composta pelas solucoes: ";
    for (int i = 0; i < this->tamanhoLista; i++)
    {
        if (i + 1 == this->tamanhoLista)
        {
            cout << this->lista1[i] << endl;
        }
        else
        {
            cout << this->lista1[i] << ", ";
        }
    }
    cout << "Lista2 composta pelas solucoes: ";
    for (int i = 0; i < this->tamanhoLista; i++)
    {
        if (i + 1 == this->tamanhoLista)
        {
            cout << this->lista2[i] << endl;
        }
        else
        {
            cout << this->lista2[i] << ", ";
        }
    }
    cout << "Lista3 composta pelas solucoes: ";
    for (int i = 0; i < this->tamanhoLista; i++)
    {
        if (i + 1 == this->tamanhoLista)
        {
            cout << this->lista3[i] << endl;
        }
        else
        {
            cout << this->lista3[i] << ", ";
        }
    }
}

int ConjuntoPopulacional::getTamanhoPop()
{
    return this->tamanhoPop;
}

int *ConjuntoPopulacional::getPopulacao()
{
    return this->populacao;
}