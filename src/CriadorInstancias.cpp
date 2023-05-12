

#include "CriadorInstancias.h"
#include <iostream>

using namespace std;

CriadorInstancias::~CriadorInstancias()
{
}

// Constructor
CriadorInstancias::CriadorInstancias()
{
    primeira_maquina = NULL;
    ultima_maquina = NULL;

    primeiro_processo = NULL;
    ultimo_processo = NULL;

    SorteiaNumProcessos();
    // cout<<"Num de Processos Sorteados: "<<n<<endl;
    SorteiaNumMaquinas();
    /// cout<<"Num de maquinas Sorteadas: "<<m<<endl;
    GeraMaquinas();
    // int i=1;
    // for(Maquina* a=this->primeira_maquina;a!=NULL;a=a->get_prox_Maquina()){
    //     cout<<"Maquina: "<<i<< " Velocidade de Processamento: "<<a->get_vp()<<" Gasto de Energia: "<<a->get_ge()<<endl;
    //     i++;
    // }
    GeraProcesos();
    // i=1;
    // for(Processo* b=this->primeiro_processo;b!=NULL;b=b->get_prox_Processo()){
    //     cout<<"Processo: "<<b->get_id()<<" Quantidade de trabalho: "<<b->get_qt()<<endl;
    // for(k=0;k<m;k++){
    //     cout<<"Tempo de processamento na maquina "<<k<<" : "<<b->tempos_processamento[k]<<endl;
    //     cout<<"Gasto de energia na maquina "<<k<<" : "<<b->custos_energia[k]<<endl;
    // }
    // i++;
    //}
    //GeraKpadrao();
    //Calcula_b();
    // cout<<"Tempo limite da instancia: "<<b<<endl;
    int instanteDeInicio = 0;
    //cout<<"M: "<<this->get_m()<<" || N: "<<this->get_n()<<endl;
}

void CriadorInstancias::GeraProcesos()
{

    int quantidadeTrabalho;
    Maquina *maquina;

    for (int i = 0; i < n; i++)
    { // para cada processo
        quantidadeTrabalho = 100 + rand() % 4900;
        Processo *processo = new Processo();
        processo->set_id(i);
        processo->set_qt(quantidadeTrabalho);

        int j = 0;

        for (maquina = this->primeira_maquina; maquina != NULL; maquina = maquina->get_prox_Maquina())
        { // para cada maquina
            // Calculo tempo de Processamento e Gasto de energia
            float tempo_esperado = quantidadeTrabalho / maquina->get_vp();

            int t_Max = ((tempo_esperado * e1) + (tempo_esperado)) * 1000.0;
            int t_Min = ((tempo_esperado) - (tempo_esperado * e1)) * 1000.0;

            float tempo_real = (rand() % (t_Max - t_Min + 1) + t_Min) / 1000.0;

            processo->tempos_processamento[j] = tempo_real;

            float gasto_esperado = tempo_real * maquina->get_ge();

            int g_Max = ((gasto_esperado * e2) + (gasto_esperado)) * 1000.0;
            int g_Min = ((gasto_esperado) - (gasto_esperado * e2)) * 1000.0;

            float gasto_real = (rand() % (g_Max - g_Min + 1) + g_Min) / 1000.0;

            processo->custos_energia[j] = gasto_real;

            if (this->primeiro_processo == NULL)
            {
                this->primeiro_processo = processo;
                this->ultimo_processo = processo;
                processo->set_prox_Processo(NULL);
                processo->set_ant_Processo(NULL);
            }
            else
            {
                this->ultimo_processo->set_prox_Processo(processo);
                processo->set_ant_Processo(this->ultimo_processo);
                processo->set_prox_Processo(NULL);
                this->ultimo_processo = processo;
            }

            j++;
        }
    }
}

void CriadorInstancias::Calcula_b()
{

    float soma = 0;
    float soma2 =0;
    float soma3=0;

    for (Processo *processo = this->primeiro_processo; processo != NULL; processo = processo->get_prox_Processo())
    { // para todos processos

        for (int i = 0; i < m; i++)
        { // em todas as maquinas
            soma = soma + processo->tempos_processamento[i];
            soma2=soma2 + processo->custos_energia[i];
        }
    }

    this->b = alfa * (soma / (m * m));

    this->media_MS= (soma / (m * m));

    this->media_CE=(soma2 / m);

}

// sortear numero de processos
void CriadorInstancias::SorteiaNumProcessos()
{
    int parametro;

    do
    {
        parametro = rand() % 4;

    } while (parametro != 0 && parametro != 1 && parametro != 2 && parametro != 3);

    if (parametro == 0)
    {
        this->n = 50;
    }
    else if (parametro == 1)
    {
        this->n = 100;
    }
    else if (parametro == 2)
    {
        this->n = 150;
    }
    else if (parametro == 3)
    {
        this->n = 200;
    }
}

// sortear numero de maquinas
void CriadorInstancias::SorteiaNumMaquinas()
{

    int parametro;

    do
    {
        parametro = rand() % 3;

    } while (parametro != 0 && parametro != 1 && parametro != 2);

    if (parametro == 0)
    {
        this->m = 5;
    }
    else if (parametro == 1)
    {
        this->m = 10;
    }
    else if (parametro == 2)
    {
        this->m = 20;
    }
}

// Gera as maquinas
void CriadorInstancias::GeraMaquinas()
{

    for (int i = 0; i < m; i++)
    {

        int tipoMaquina;

        do
        {
            tipoMaquina = rand() % 4;

        } while (tipoMaquina != 0 && tipoMaquina != 1 && tipoMaquina != 2 && tipoMaquina != 3);

        Maquina *maquina = new Maquina(tipoMaquina);
        maquina->set_id(i);

        if (this->primeira_maquina == NULL)
        {                                     // caso essa seja a primeira maquina adicionada
            this->primeira_maquina = maquina; // essa maquina = primeira maquina
            this->ultima_maquina = maquina;   // essa maquina = ultima maquina

            maquina->set_prox_Maquina(NULL); // maquina seguinte n existe
            maquina->set_ant_Maquina(NULL);  // maquina anterior não existe
        }
        else
        { // caso essa não seja a primera maquina adicionada

            this->ultima_maquina->set_prox_Maquina(maquina); // ultima maquina adiciona recebe como prox maquina essa
            maquina->set_ant_Maquina(this->ultima_maquina);  // essa maquina recebe a ultima maquina adicionada como ant maquina
            maquina->set_prox_Maquina(NULL);                 ////maquina seguinte n existe
            this->ultima_maquina = maquina;                  // essa maquina se torna a ultima maquina
        }
    }
}
