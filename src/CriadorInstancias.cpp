

#include "CriadorInstancias.h"
#include <iostream>
#include "Maquina.h"

using namespace std;

CriadorInstancias::~CriadorInstancias(){

}

// Constructor
CriadorInstancias::CriadorInstancias(){
    primeira_maquina=NULL;
    ultima_maquina=NULL;

    primeiro_processo=NULL;
    ultimo_processo=NULL;

    primeiro_intervalo=NULL;
    ultimo_intervalo=NULL;

    SorteiaNumProcessos();
    cout<<"Num de Processos Sorteados: "<<n<<endl;
    SorteiaNumMaquinas();
    cout<<"Num de maquinas Sorteadas: "<<m<<endl;
    GeraMaquinas();
    int i=1;
    for(Maquina* a=this->primeira_maquina;a!=NULL;a=a->get_prox_Maquina()){
        cout<<"Maquina: "<<i<< " Velocidade de Processamento: "<<a->get_vp()<<" Gasto de Energia: "<<a->get_ge()<<endl;
        i++;
    }
    GeraProcesos();
    i=1;
    for(Processo* b=this->primeiro_processo;b!=NULL;b=b->get_prox_Processo()){
        cout<<"Processo: "<<i<<" Quantidade de trabalho: "<<b->get_qt()<<endl;
        //for(k=0;k<m;k++){
        //    cout<<"Tempo de processamento na maquina "<<k<<" : "<<b->tempos_processamento[k]<<endl; 
        //    cout<<"Gasto de energia na maquina "<<k<<" : "<<b->custos_energia[k]<<endl; 
        //}
        //i++;
    }
    GeraKpadrao();
    Calcula_b();
    cout<<"Tempo limite da instancia: "<<b<<endl;
    int instanteDeInicio = calcInicioDia();

}

void CriadorInstancias::GeraProcesos(){

    int quantidadeTrabalho;
    Maquina* maquina;

    for(int i=0; i<n;i++){//para cada processo
        quantidadeTrabalho = 100 + rand() % 4900;
        Processo* processo = new Processo();
        processo->set_id(i);
        processo->set_qt(quantidadeTrabalho);

        int j=0;

        for(maquina = this->primeira_maquina; maquina != NULL ; maquina = maquina->get_prox_Maquina()){//para cada maquina
            //Calculo tempo de Processamento e Gasto de energia
            float tempo_esperado= quantidadeTrabalho/maquina->get_vp();

            int t_Max=((tempo_esperado*e1) + (tempo_esperado)) * 1000.0;
            int t_Min=((tempo_esperado)-(tempo_esperado*e1)) * 1000.0;


            float tempo_real= (rand() % (t_Max - t_Min + 1) + t_Min)/1000.0;

            processo->tempos_processamento[j]=tempo_real;

            
            float gasto_esperado = tempo_real*maquina->get_ge();


            int g_Max=((gasto_esperado*e2) + (gasto_esperado)) * 1000.0;
            int g_Min=((gasto_esperado)-(gasto_esperado*e2)) * 1000.0;


            float gasto_real= (rand() % (g_Max - g_Min + 1) + g_Min)/1000.0;


            processo->custos_energia[j]=gasto_real;

            

            if(this->primeiro_processo==NULL){
                this->primeiro_processo=processo; 
                this->ultimo_processo=processo; 
                processo->set_prox_Processo(NULL); 
                processo->set_ant_Processo(NULL); 

            }else{
                this->ultimo_processo->set_prox_Processo(processo);
                processo->set_ant_Processo(this->ultimo_processo);
                processo->set_prox_Processo(NULL);
                this->ultimo_processo=processo; 


            }

            j++;

        }

    }

}

void CriadorInstancias::Calcula_b(){

    float soma=0;

for(Processo* processo=this->primeiro_processo; processo!=NULL ; processo=processo->get_prox_Processo()){//para todos processos

    for(int i=0;i<m;i++){//em todas as maquinas
        soma=soma+processo->tempos_processamento[i];
    }

}

this->b=alfa*(soma/(m*m));

}

void CriadorInstancias::GeraKpadrao(){

this->k=6;


for(int i=0;i<1440;i++){
    if(i>=0 && i <200){
    this->intervalos[i]=0.140;
    }

    if(i>=200 && i <500){
    this->intervalos[i]=0.220;
    }

    if(i>=500 && i <650){
    this->intervalos[i]=0.140;
    }

    if(i>=650 && i <800){
    this->intervalos[i]=0.220;
    }

    if(i>=800 && i <900){
    this->intervalos[i]=0.140;
    }

    if(i>=900 && i <1440){
    this->intervalos[i]=0.140;
    }
}

Intervalo* intervalo1 = new Intervalo();
intervalo1->set_tk(200);
intervalo1->set_prk(0.140);

Intervalo* intervalo2 = new Intervalo();
intervalo2->set_tk(300);
intervalo2->set_prk(0.220);

Intervalo* intervalo3 = new Intervalo();
intervalo3->set_tk(150);
intervalo3->set_prk(0.140);

Intervalo* intervalo4 = new Intervalo();
intervalo4->set_tk(150);
intervalo4->set_prk(0.220);

Intervalo* intervalo5 = new Intervalo();
intervalo5->set_tk(100);
intervalo5->set_prk(0.140);

Intervalo* intervalo6 = new Intervalo();
intervalo6->set_tk(540);
intervalo6->set_prk(0.060);

intervalo1->set_prox_Intervalo(intervalo2);
intervalo2->set_prox_Intervalo(intervalo3);
intervalo3->set_prox_Intervalo(intervalo4);
intervalo4->set_prox_Intervalo(intervalo5);
intervalo5->set_prox_Intervalo(intervalo6);
intervalo6->set_prox_Intervalo(NULL);

intervalo6->set_ant_Intervalo(intervalo5);
intervalo5->set_ant_Intervalo(intervalo4);
intervalo4->set_ant_Intervalo(intervalo3);
intervalo3->set_ant_Intervalo(intervalo2);
intervalo2->set_ant_Intervalo(intervalo1);
intervalo1->set_ant_Intervalo(NULL);

intervalo1=this->primeiro_intervalo;
intervalo6=this->ultimo_intervalo;

}


//sortear numero de processos
void CriadorInstancias::SorteiaNumProcessos(){
int parametro;

do{
parametro = rand() % 4;

}while(parametro != 0 && parametro != 1 && parametro != 2 && parametro != 3);

if(parametro==0){
    this->n=50;
}else if(parametro==1){
    this->n=100;
}else if(parametro==2){
    this->n=150;
}else if(parametro==3){
    this->n=200;
}

}


//sortear numero de maquinas
void CriadorInstancias::SorteiaNumMaquinas(){

    int parametro;

do{
parametro = rand() % 3;

}while(parametro != 0 && parametro != 1 && parametro != 2);

if(parametro==0){
    this->m=5;
}else if(parametro==1){
    this->m=10;
}else if(parametro==2){
    this->m=20;
}

}

//Gera as maquinas
void CriadorInstancias::GeraMaquinas(){

for(int i=0;i<m;i++){

    int tipoMaquina;

    do{
tipoMaquina = rand() % 4;

}while(tipoMaquina != 0 && tipoMaquina != 1 && tipoMaquina != 2 && tipoMaquina != 3);

Maquina* maquina = new Maquina(tipoMaquina);

if(this->primeira_maquina==NULL){ //caso essa seja a primeira maquina adicionada
    this->primeira_maquina=maquina; //essa maquina = primeira maquina
    this->ultima_maquina=maquina; //essa maquina = ultima maquina

    maquina->set_prox_Maquina(NULL); //maquina seguinte n existe
    maquina->set_ant_Maquina(NULL); //maquina anterior não existe
}else{ //caso essa não seja a primera maquina adicionada

this->ultima_maquina->set_prox_Maquina(maquina);//ultima maquina adiciona recebe como prox maquina essa
maquina->set_ant_Maquina(this->ultima_maquina);//essa maquina recebe a ultima maquina adicionada como ant maquina
maquina->set_prox_Maquina(NULL);////maquina seguinte n existe
this->ultima_maquina=maquina; //essa maquina se torna a ultima maquina
}

}

}

 int CriadorInstancias::calcInicioDia(){
    //calcular o melhor instante do dia dos 1440 mins para começar o trabalho dado todas as maquinas.
    return 900;
 }