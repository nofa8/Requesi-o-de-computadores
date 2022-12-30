#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXIMUS 9999
#define MAXX 30
#define NMAXX 15
#define UM 1
#define ZERO 0

#define RAM 32

#define I3 "i3"
#define I5 "i5"
#define I7 "i7"

#define STAT_DISP "disponivel"
#define STAT_REQ "requisitado"
#define STAT_AVA "avariado"

#define STAT_TEMP "temporaria"
#define STAT_PERM "permanente"

#define STAT_ATIV "ativo"
#define STAT_CONC "concluido"

#define MAX_DESIG 20
#define MAX_NOME 80
#define MENOR_ANO 2010
#define MAIOR_ANO 2023

#define CAMPUS1 "campus1"
#define CAMPUS2 "campus2"
#define CAMPUS5 "campus5"
#define RESID "residencias"

#define TIPO_ESTUD "estudante"
#define TIPO_DOCE  "docente"
#define TIPO_ADM  "tecnico administrativo"

 //Structures for storing the information!
typedef struct{
    //Basic Structure for storing the DAY of something happening!
    int dia;
    int mes;
    int ano;
}DATa;


typedef struct{
    char requiscode[NMAXX];
    DATa requis;
    int numpraz;     //prazo days
    DATa praz;      // prazo requisicao
    //state of a pc?
    //estado de requesição
    char statreq[NMAXX];

    //Devolução
    DATa devol;
    char local[NMAXX];
    float finee;
    int prazreal;

    //UTENTE STUFF
    char typeut[25];
    int numutent;
    char nomedoutente[MAX_NOME];
}REQUi;

typedef struct{
    char tipoavaria[NMAXX];
    DATa dataavaria;
    //________________
    DATa fimavaria;
    int duracaoavaria;
} AVARIAs;

typedef struct{
    REQUi *requisition;
    int quantReq;
    int indicereq;
    int quantDiasReq;
    //______________
    int portId;
    char desig[MAX_DESIG];
    char process[4]; 
    int  memoria;
    //_____________
    AVARIAs *avarias;
    int quantAvarias;
    int indiceavarias;
    char stat[NMAXX];
    //_______________
    char local[NMAXX];
    DATa aquis;
    float valuequi;
}PORTATIl;

typedef struct{
    int portatexist;        // Portateis existentes
    int portatedisp;        //Portateis disponiveis
    int totalderequisefet;  // Total de requisiçoes feitas
    int requisativas;       // Requisiçoes ativas
} CONTADOREs;
















void limpaBufferStdin(void);
int lerInteiro(int min, int max);
void lerString(char vetor[], int max);
float lerFloat(float min, float max);
DATa lerData(void);
int subtrairDatas(DATa d1, DATa d2);

char menu(CONTADOREs *cont,PORTATIl port[MAXX]);
void subListar(CONTADOREs *cont, PORTATIl port1[MAXX]);

void lePortate(CONTADOREs *cont, PORTATIl port2[MAXX]);
void regAva(CONTADOREs *cont, PORTATIl port[MAXX], int indice);
void regRep(CONTADOREs *cont, PORTATIl port[MAXX], int indice);
void regRq(CONTADOREs *cont, PORTATIl port[MAXX]);
void listaReq(CONTADOREs *cont, PORTATIl port[MAXX]);
void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX]);
void dadosEstatisticos(CONTADOREs *cont, PORTATIl port[MAXX]);
int procurarReq(CONTADOREs *cont, PORTATIl port[MAXX], int *sitio);


int lerID(CONTADOREs *cont, PORTATIl port[MAXX], int idtemp);
int lerUtente(CONTADOREs *cont, PORTATIl port[MAXX]);
int lerDesignacao( CONTADOREs *cont, PORTATIl port[MAXX], int pos);

void gravarFicheiroBinario(CONTADOREs cont, PORTATIl port[MAXX]);
void lerFicheiroBinario(CONTADOREs *cont, PORTATIl port[MAXX]);


int main()
{
    PORTATIl portateis[30];
    CONTADOREs oscontadores;
    char escolha;
    int i = 0, pc = 0, conf=-1, confoutro = -1;
    oscontadores.portatexist = 0;
    oscontadores.portatedisp = 0;
    oscontadores.requisativas = 0;
    oscontadores.totalderequisefet = 0;
    for(i = 0;i<MAXX;i++){
        portateis[i].requisition = malloc(20*sizeof(REQUi));
        portateis[i].avarias = malloc(20*sizeof(AVARIAs));
    }
    
    do{
        escolha = menu(&oscontadores,portateis);
        switch(escolha){
            case 'I':
                insertPCs(&oscontadores, portateis);
                break;
            case 'L':
                subListar(&oscontadores, portateis);
                break;
            case 'R':
                regRq(&oscontadores, portateis);
                break;
            case 'V':
                if((oscontadores.portatexist == 0)){
                    printf("\nNao ha computadores, comece por registar computadores!\n");
                }
                else{
                    printf("\n\tId: ");
                    do{
                        pc = lerInteiro(UM,MAXIMUS);
                        conf = lerID(&oscontadores, portateis, pc);
                        if(conf == -1){
                            printf("\n\tErro id invalido.Insira novamente: ");
                        }
                    }while(conf == -1);
                    if(strcmp(portateis[conf].stat,STAT_AVA)==0){
                        regRep(&oscontadores,portateis,conf);
                        strcpy(portateis[conf].stat,STAT_DISP);
                        oscontadores.portatedisp++;

                    }
                    else{
                        if(strcmp(portateis[conf].stat,STAT_DISP)==0){
                            regAva(&oscontadores,portateis,conf);
                            strcpy(portateis[conf].stat,STAT_AVA);
                            oscontadores.portatedisp--;
                        }
                    }
                }
                break;
            case 'D':

                break;
            case 'A':

                break;
            case 'Y':

                break;
            case 'G':
                gravarFicheiroBinario(oscontadores, portateis);
                //gravarFicheiroTexto(oscontadores,portateis);

                break;
            case 'E':
                lerFicheiroBinario(&oscontadores, portateis);
                break;
            case 'Z':

                break;
            
            case 'S':
                printf("\nA sair ...\n");
                
        }
    }while(escolha != 'S');



    return 0;
}



char menu(CONTADOREs *cont,PORTATIl port[MAXX]){
    char opcao;

    printf("\n\n==========================Menu Principal==========================\n\n");
    printf("\tQuantidade de portateis: %d", cont->portatexist);
    printf("\t\tQuantidade de portateis disponiveis: %d \n\tTotal de requisicoes efetuadas: %d\tQuantidade de requisicoes ativas: %d\n", cont->portatedisp, cont->totalderequisefet, cont->requisativas);

    printf("\nI - Inserir Portateis\n");//s
    printf("L - Listar Informacao\n\n");      //adicionar dados de requisicoes

    printf("R - Registar Requisicao\n");// s
    printf("V - Registar Avaria / Reparacao\n"); // s
    printf("D - Registar Devolucao \n\n");

    printf("A - Alteracao da Localizacao de um portatil\n");
    printf("Y - Renovar requisicao\n");

    printf("G - Gravar dados nos Ficheiros\n"); // s e n
    printf("E - Extrair dados dos Ficheiros\n\n");//s
    printf("Z - Apresentacao de dados estatisticos\n");//s quase
    printf("\tS - Sair\n\t\t\tOpcao --> "); //s

    do{
        opcao = getchar();
        limpaBufferStdin();
        opcao = toupper(opcao);
        if(opcao != 'M'&& opcao != 'Y'&& opcao != 'Z'&& opcao != 'A'&& opcao != 'D'&& opcao != 'V'&& opcao != 'I'&& opcao != 'L' && opcao != 'G' && opcao != 'E' && opcao != 'R' && opcao != 'S'){
            printf("Opcao invalida!\n\nInsira Novamente: ");
        }
    }while(opcao != 'M'&& opcao != 'Y'&& opcao != 'Z'&& opcao != 'A'&& opcao != 'D'&& opcao != 'V'&& opcao != 'I'&& opcao != 'L' && opcao != 'G' && opcao != 'E' && opcao != 'R' && opcao != 'S');



    return opcao;
}
void subListar(CONTADOREs *cont, PORTATIl port1[MAXX]){     //passar quantPortateis nos ()
    int i,u,conf = -1,indiceREQ = -1;
    char opcao1;

    printf("\n\n\n\n\n\n\n\n==========================Listar Informacao==========================\n\n");
    printf("\tP - Informacao de Portateis\n\n");
    printf("\tT - Listar dados de Todas Requisicoes\n\n");
    printf("\tR - Apresentar informacao de uma requisicao\n\n");
    printf("\tA - Apresentar listagem de todas as avarias ocorridas\n\n");
    printf("\tS - Sair\n");
    printf("\t\tOpcao: ");
    do{
        opcao1 = getchar();
        limpaBufferStdin();
        opcao1 = toupper(opcao1);
        if(opcao1 != 'P'&& opcao1 != 'T'&& opcao1 != 'R'&& opcao1 != 'A' && opcao1 != 'S'){
            printf("\nOpcao invalida!\nInsira Novamente: ");
        }
    }while(opcao1 != 'P'&& opcao1 != 'T'&& opcao1 != 'R'&& opcao1 != 'A' && opcao1 != 'S');

    switch(opcao1){
    case 'P':
        lePortate(cont,port1);
        break;
    case 'T':
        listaReq(cont,port1);
        break;
    case 'R':
        printf("\n\tCodigo da requisicao: ");
        do{
            conf = procurarReq(cont,port1,&indiceREQ);
            if(conf == -1){
                printf("\n\tErro codigo de requisicao invalido.Insira novamente: ");
            }
        }while(conf == -1);
        // port1[conf].requisition[indiceREQ]
        printf("\n\n\tDesignacao do portatil: %s", port1[conf].desig);
        printf("\n\tEstado do portatil: %s",port1[conf].stat);
        //Quantidade total de dias requisitados do pc ou requisicao Falar com a Eunice
        //voltaremos ...
        printf("\n\tQuantidade total de dias requisitado: %d dias",port1[conf].quantDiasReq);
        printf("\n\tData requisicao: %d/%d/%d",port1[conf].requisition[indiceREQ].requis.dia,port1[conf].requisition[indiceREQ].requis.mes,port1[conf].requisition[indiceREQ].requis.ano);
        printf("\n\tEstado da requisicao: %s",port1[conf].requisition[indiceREQ].statreq);
        if(strcmp(port1[conf].requisition[indiceREQ].statreq, STAT_ATIV)==0){
            printf("\n\tDia maximo de Devolucao: %d/%d/%d",port1[conf].requisition[indiceREQ].praz.dia,port1[conf].requisition[indiceREQ].praz.mes,port1[conf].requisition[indiceREQ].praz.ano);
            printf("\n\tDuracao maxima da requisicao: %d",port1[conf].requisition[indiceREQ].numpraz);
            printf("\n\tLocal: ---\n\tMulta: ---\n");
        }
        else{
            printf("\n\tDevolucao: %d/%d/%d",port1[conf].requisition[indiceREQ].devol.dia,port1[conf].requisition[indiceREQ].devol.mes,port1[conf].requisition[indiceREQ].devol.ano);
            printf("\n\tDuracao da  requisicao: %d",port1[conf].requisition[indiceREQ].prazreal);
            printf("\n\tLocal: %s\n\tMulta: %f\n",port1[conf].requisition[indiceREQ].local,port1[conf].requisition[indiceREQ].finee);
        }
        printf("\n\tTipo de utente: %s.\n\tNumero de utente: %d.\n\tNome de utente: %s",port1[conf].requisition[indiceREQ].typeut,port1[conf].requisition[indiceREQ].numutent,port1[conf].requisition[indiceREQ].nomedoutente);
        break;
    case 'A':
    // dados do portátil, tipo de avaria data da avaria e tempo de duração
        printf("\n\t\tDados de avarias: ");
        if(cont->portatexist!=0){
            for(i=0; i < cont->portatexist; i++){
                if(port1[i].quantAvarias == 0){
                    printf("\n\tO Pc, %s (%d) nao tem avarias registadas.",port1[i].desig, port1[i].portId);
                }
                else{
                    printf("\nId: %d\n", port1[i].portId);
                    printf("Portatil %s: \n", port1[i].desig);
                    printf("\t\tProcessador: %s", port1[i].process);
                    printf("\t\t\tEstado: %s\n", port1[i].stat);
                    printf("\t\tLocalizacao: %s", port1[i].local);
                    printf("\t\tData de aquisicao: %d / %d / %d\n", port1[i].aquis.dia,port1[i].aquis.mes,port1[i].aquis.ano);
                    printf("\t\tValor do equipamento: %.2f", port1[i].valuequi);
                    printf("\tQuantidade de avarias: %d\n", port1[i].quantAvarias);
                    printf("\t\tQuantidade de requisicoes: %d\n", port1[i].quantReq);
                    for(u = 0;u < port1[i].quantAvarias; u++){
                        printf("\n\tTipo de avaria: %s.", port1[i].avarias[u].tipoavaria);
                        printf("\n\tData de avaria: %d-%d-%d",port1[i].avarias[u].dataavaria.dia,port1[i].avarias[u].dataavaria.mes,port1[i].avarias[u].dataavaria.ano);
                        if(strcmp(port1[i].avarias[u].tipoavaria,STAT_PERM)==0){
                            printf("\n\tAvaria permanente");
                        }
                        else{
                            if(u == port1[i].indiceavarias){    //ultima avaria ligada ao estado do pc
                                if(strcmp(port1[i].stat,STAT_AVA)==0){
                                    printf("\n\tAvaria continua");
                                }
                            }
                            else{
                                printf("\n\tFim da avaria: %d-%d-%d",port1[i].avarias[u].fimavaria.dia,port1[i].avarias[u].fimavaria.mes,port1[i].avarias[u].fimavaria.ano);
                                printf("\n\tDuracao da avaria: %d", port1[i].avarias[u].duracaoavaria);
                            }
                        }    
                    }
                }
            }
        }
        else{
            printf("\nNao ha computadores!\n");
        }
        break;
    case 'S':
        printf("\n\t.\n");
        break;
    }
 }

void lePortate(CONTADOREs *cont, PORTATIl port2[MAXX]){
    int i, u;
    if(cont->portatexist!=0){
        for(i=0; i < cont->portatexist; i++){
            printf("\nId: %d\n", port2[i].portId);
            printf("Portatil %s: \n", port2[i].desig);
            printf("\t\tProcessador: %s", port2[i].process);
            printf("\t\t\tEstado: %s\n", port2[i].stat);
            printf("\t\tLocalizacao: %s", port2[i].local);
            printf("\t\tData de aquisicao: %d / %d / %d\n", port2[i].aquis.dia,port2[i].aquis.mes,port2[i].aquis.ano);
            printf("\t\tValor do equipamento: %.2f", port2[i].valuequi);
            printf("\tQuantidade de avarias: %d\n", port2[i].quantAvarias);
            printf("\t\tQuantidade de requisicoes: %d\n", port2[i].quantReq);
            if(port2[i].quantReq == 0){
                printf("\t\tTipo de utente: ----\tPrazo de requisicao: ---- dias");
            }
            else{
                printf("\t\tTipo de utente: %15s\tPrazo de requisicao: %d dias", port2[i].requisition[port2[i].indicereq].typeut,port2[i].requisition[port2[i].indicereq].numpraz);
            }
        }

    }
    else{
        printf("\nNao ha computadores!\n");
    }
}

void regRep(CONTADOREs *cont, PORTATIl port[MAXX], int indice){
    char conf = 'S';
    if(strcmp(port[indice].avarias[port[indice].indiceavarias].tipoavaria,STAT_PERM)==0){
        printf("\n\tTipo de avaria permanente.Deseja continuar(S/N)");
        do{
            conf = getchar();
            conf = toupper(conf);
        }while(conf!='S'&&conf!='N');
    }
    if(conf =='S'){
        do{
            port[indice].avarias[port[indice].indiceavarias].fimavaria = lerData();
            if(port[indice].avarias[port[indice].indiceavarias].fimavaria.ano <  port[indice].avarias[port[indice].indiceavarias].dataavaria.ano || (port[indice].avarias[port[indice].indiceavarias].fimavaria.ano ==  port[indice].avarias[port[indice].indiceavarias].dataavaria.ano && port[indice].avarias[port[indice].indiceavarias].fimavaria.mes <  port[indice].avarias[port[indice].indiceavarias].dataavaria.mes)||(port[indice].avarias[port[indice].indiceavarias].fimavaria.ano ==  port[indice].avarias[port[indice].indiceavarias].dataavaria.ano && port[indice].avarias[port[indice].indiceavarias].fimavaria.mes ==  port[indice].avarias[port[indice].indiceavarias].dataavaria.mes && port[indice].avarias[port[indice].indiceavarias].fimavaria.dia <  port[indice].avarias[port[indice].indiceavarias].dataavaria.dia)){
                printf("\nData invalida.Data: ");
            }
        }while(port[indice].avarias[port[indice].indiceavarias].fimavaria.ano <  port[indice].avarias[port[indice].indiceavarias].dataavaria.ano || (port[indice].avarias[port[indice].indiceavarias].fimavaria.ano ==  port[indice].avarias[port[indice].indiceavarias].dataavaria.ano && port[indice].avarias[port[indice].indiceavarias].fimavaria.mes <  port[indice].avarias[port[indice].indiceavarias].dataavaria.mes)||(port[indice].avarias[port[indice].indiceavarias].fimavaria.ano ==  port[indice].avarias[port[indice].indiceavarias].dataavaria.ano && port[indice].avarias[port[indice].indiceavarias].fimavaria.mes ==  port[indice].avarias[port[indice].indiceavarias].dataavaria.mes && port[indice].avarias[port[indice].indiceavarias].fimavaria.dia <  port[indice].avarias[port[indice].indiceavarias].dataavaria.dia));
        port[indice].avarias[port[indice].indiceavarias].duracaoavaria = subtrairDatas(port[indice].avarias[port[indice].indiceavarias].dataavaria, port[indice].avarias[port[indice].indiceavarias].fimavaria);
    }

}


void regAva(CONTADOREs *cont, PORTATIl port[MAXX],int indice){
    int i=0,u=0;
    printf("\n\tTipo de avaria: ");
    do{
        lerString(port[indice].avarias[port[indice].quantAvarias].tipoavaria, NMAXX);
        for(i = 0; i<strlen(port[indice].avarias[port[indice].quantAvarias].tipoavaria);i++){
            port[indice].avarias[port[indice].quantAvarias].tipoavaria[i] = tolower(port[indice].avarias[port[indice].quantAvarias].tipoavaria[i]);
        }
        if(strcmp(port[indice].avarias[port[indice].quantAvarias].tipoavaria, STAT_TEMP)!= 0 && strcmp(port[indice].avarias[port[indice].quantAvarias].tipoavaria, STAT_PERM)!= 0){
            printf("\nErro tipo de avaria invalido (temporaria ou permanente).Insira novamente: ");
        }
    }while(strcmp(port[indice].avarias[port[indice].quantAvarias].tipoavaria, STAT_TEMP)!= 0 && strcmp(port[indice].avarias[port[indice].quantAvarias].tipoavaria, STAT_PERM)!= 0);
    
    printf("\n\tData de avaria: ");
    do{
        port[indice].avarias[port[indice].quantAvarias].dataavaria = lerData();
        if(port[indice].avarias[port[indice].quantAvarias].dataavaria.ano < port[indice].aquis.ano ||(port[indice].avarias[port[indice].quantAvarias].dataavaria.ano == port[indice].aquis.ano && port[indice].avarias[port[indice].quantAvarias].dataavaria.mes < port[indice].aquis.mes)||(port[indice].avarias[port[indice].quantAvarias].dataavaria.ano == port[indice].aquis.ano && port[indice].avarias[port[indice].quantAvarias].dataavaria.mes == port[indice].aquis.mes && port[indice].avarias[port[indice].quantAvarias].dataavaria.dia < port[indice].aquis.dia)){
            printf("\n\tErro, dia de avaria nao pode ser inferior ao dia de aquisicao.\n\t\tData:");
        }
    }while(port[indice].avarias[port[indice].quantAvarias].dataavaria.ano < port[indice].aquis.ano ||(port[indice].avarias[port[indice].quantAvarias].dataavaria.ano == port[indice].aquis.ano && port[indice].avarias[port[indice].quantAvarias].dataavaria.mes < port[indice].aquis.mes)||(port[indice].avarias[port[indice].quantAvarias].dataavaria.ano == port[indice].aquis.ano && port[indice].avarias[port[indice].quantAvarias].dataavaria.mes == port[indice].aquis.mes && port[indice].avarias[port[indice].quantAvarias].dataavaria.dia < port[indice].aquis.dia));
    port[indice].quantAvarias++;
    port[indice].indiceavarias++;

}

void regRq(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i= 0,l=0,h = 0,u = 0,idTemporario = 0, indice=-1, numutente = 0, date = 0;
    if((*cont).portatedisp >0){
            printf("\nInsira o numero de identificacao do portatil: ");
            idTemporario = lerInteiro(UM,MAXIMUS);
            for (l=0;i<(*cont).portatexist;l++){
                if(port[l].portId == idTemporario){
                    indice = l;
                    if(strcmp(port[indice].stat,STAT_DISP)==0){

                        //Codigo de Requisicao
                        printf("\nCodigo de requisicao: ");
                        do{
                            lerString(port[indice].requisition[port[indice].quantReq].requiscode,NMAXX);
                            for(i = 0; i <(*cont).portatexist;i++){
                                    if(strcmp(port[indice].requisition[port[indice].quantReq].requiscode,port[i].requisition[port[i].quantReq].requiscode)==0){
                                        //"Podiamos deixar ai um comentario para depois falar à professora", Gonçalo 21/12/2022
                                        if(strcmp(port[i].requisition[port[i].quantReq].statreq,STAT_ATIV)==0){
                                            printf("\nCodigo de requisicao indisponivel.\n");
                                            u = -1;
                                            i = cont->portatexist;
                                        }  
                                    }
                            }
                        }while(u == -1);
                        //Data Requisição
                        printf("\nData de Requisicao: ");
                        do{
                            port[indice].requisition[port[indice].quantReq].requis = lerData();
                            if((port[indice].aquis.ano > port[indice].requisition[port[indice].quantReq].requis.ano) || (port[indice].aquis.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].aquis.mes > port[indice].requisition[port[indice].quantReq].requis.mes) || ( port[indice].aquis.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].aquis.mes == port[indice].requisition[port[indice].quantReq].requis.mes && port[indice].aquis.dia > port[indice].requisition[port[indice].quantReq].requis.dia)){
                                printf("\n\tErro data invalida nao pode ser inferior ao dia de aquisicao.");
                            }
                        }while((port[indice].aquis.ano > port[indice].requisition[port[indice].quantReq].requis.ano) || (port[indice].aquis.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].aquis.mes > port[indice].requisition[port[indice].quantReq].requis.mes) || ( port[indice].aquis.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].aquis.mes == port[indice].requisition[port[indice].quantReq].requis.mes && port[indice].aquis.dia > port[indice].requisition[port[indice].quantReq].requis.dia));
                        //PRazo e cenas...
                        printf("\nPrazo de Devolucao: ");
                        do{
                            port[indice].requisition[port[indice].quantReq].praz = lerData();
                            if(!((port[indice].requisition[port[indice].quantReq].praz.ano > port[indice].requisition[port[indice].quantReq].requis.ano) || (port[indice].requisition[port[indice].quantReq].praz.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].requisition[port[indice].quantReq].praz.mes > port[indice].requisition[port[indice].quantReq].requis.mes) || ( port[indice].requisition[port[indice].quantReq].praz.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].requisition[port[indice].quantReq].praz.mes == port[indice].requisition[port[indice].quantReq].requis.mes&&port[indice].requisition[port[indice].quantReq].praz.dia >= port[indice].requisition[port[indice].quantReq].requis.dia))){
                                printf("\n\tData invalida.\n");
                            }
                            port[indice].requisition[port[indice].quantReq].numpraz = subtrairDatas(port[indice].requisition[port[indice].quantReq].requis,port[indice].requisition[port[indice].quantReq].praz);
                            if(port[indice].requisition[port[indice].quantReq].numpraz >30 ){
                                    date = -1;
                                    printf("\nErro. O prazo maximo sao 30 dias.");
                            }
                        }while( (date == -1)||(!((port[indice].requisition[port[indice].quantReq].praz.ano > port[indice].requisition[port[indice].quantReq].requis.ano) || (port[indice].requisition[port[indice].quantReq].praz.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].requisition[port[indice].quantReq].praz.mes > port[indice].requisition[port[indice].quantReq].requis.mes) || ( port[indice].requisition[port[indice].quantReq].praz.ano == port[indice].requisition[port[indice].quantReq].requis.ano && port[indice].requisition[port[indice].quantReq].praz.mes == port[indice].requisition[port[indice].quantReq].requis.mes&&port[indice].requisition[port[indice].quantReq].praz.dia >= port[indice].requisition[port[indice].quantReq].requis.dia))));
                        //Prazo de devolução tem de ser superior ao dia de requisição
                        
                        
                        //Nome Utente
                        printf("\nNome do utente: ");
                        lerString(port[indice].requisition[port[indice].quantReq].nomedoutente, MAX_NOME);
                        
                        //Typo Utente
                        printf("\nTipo de utente: ");
                        do{
                            lerString(port[indice].requisition[port[indice].quantReq].typeut, 25);
                            for(h = 0; h < strlen(port[indice].requisition[port[indice].quantReq].typeut);h++){
                                port[indice].requisition[port[indice].quantReq].typeut[h] = tolower(port[indice].requisition[port[indice].quantReq].typeut[h]);
                            }
                            if(strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_ESTUD)!= 0 && strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_DOCE)!= 0 && strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_ADM)!= 0){
                                printf("\nErro tipo de utente invalido (estudante, docente, tecnico administrativo).Insira novamente: ");
                            }
                        }while(strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_ESTUD)!= 0 && strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_DOCE)!= 0 && strcmp(port[indice].requisition[port[indice].quantReq].typeut, TIPO_ADM)!= 0);
                        
                        // Numero de utente
                        printf("\nNumero do utente: ");
                        do{
                            numutente = lerUtente(cont, port);
                        }while(numutente == -1);
                        if(numutente == -2){
                            printf("\n\t\t\t\tRegisto cancelado!\n");
                        }
                        else{       
                            port[indice].requisition[port[indice].quantReq].numutent = numutente;
                            (port[indice].quantReq)++;
                            (port[indice].indicereq)++;
                            ((*cont).requisativas)++;
                            (cont->totalderequisefet)++;
                            (cont->portatedisp)--;
                            strcpy(port[indice].requisition[port[indice].indicereq].statreq, STAT_ATIV);
                            strcpy(port[indice].stat, STAT_REQ);
                        }
                    }
                    else{
                        printf("\nPortatil indisponivel\n");
                    }
                    i = (*cont).portatexist;
                }

            }
            if(indice == -1){
                printf("\nId nao existe\n");
            }

    }
    else{
        printf("\nNao ha computadores disponiveis!\n");
    }
}
void listaReq(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i=0,u=0,o=0;
    for(i=0; i<cont->portatexist;i++){
        if(port[i].quantReq != 0){
            printf("\nComputador: %s",port[i].desig);
            for(u=0; u< port[i].quantReq;u++){      // requi e um vetor, logo temos de fazer outro for
                printf("\n\tData requisicao: %d/%d/%d",port[i].requisition[u].requis.dia,port[i].requisition[u].requis.mes,port[i].requisition[u].requis.ano);
                printf("\n\tEstado da requisicao: %s",port[i].requisition[u].statreq);
                if(strcmp(port[i].requisition[u].statreq, STAT_ATIV)==0){
                    printf("\n\tDia maximo de Devolucao: %d/%d/%d",port[i].requisition[u].praz.dia,port[i].requisition[u].praz.mes,port[i].requisition[u].praz.ano);
                    printf("\n\tDuracao maxima da requisicao: %d",port[i].requisition[u].numpraz);
                    printf("\n\tLocal: ---\n\tMulta: ---\n");
                }
                else{
                    printf("\n\tDevolucao: %d/%d/%d",port[i].requisition[u].devol.dia,port[i].requisition[u].devol.mes,port[i].requisition[u].devol.ano);
                    printf("\n\tDuracao da  requisicao: %d",port[i].requisition[u].prazreal);
                    printf("\n\tLocal: %s\n\tMulta: %d\n",port[i].requisition[u].local,port[i].requisition[u].finee);
                }
            }
        }
    }
}


void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i,u,desig=0, aux = 0,prob = -1, tempid = -1;
    printf("\nQuantos pcs deseja inserir: ");
    u = lerInteiro(0,MAXX);
    u += cont->portatexist;
    if(u>30){
        u -= 30;
        printf("Nao e possivel adicionar mais computadores.\n%d a mais do numero limite.\n",u);
    }
    else{
        for(i = (*cont).portatexist; i<u; i++){
            port[i].quantAvarias = 0;
            port[i].indiceavarias = -1;
            printf("\n\n\tId: ");
            do{    
                tempid = lerInteiro(UM,MAXIMUS);
                prob = lerID(cont,port,tempid);
                if(prob != -1){
                    printf("\nID invalido, ja existe!\n");
                }
            }while(prob != -1);
            port[i].portId = tempid;
            
            do{   
                printf("\nDesignacao do portatil: ");
                desig = lerDesignacao(cont,port,i);
            }while(desig == -1);

            printf("\n\tProcessador: ");
            do{
                lerString(port[i].process, 4);
                if(strcmp(I3, port[i].process) != 0 && strcmp(I5, port[i].process) != 0 && strcmp(I7, port[i].process) != 0){
                    printf("O processador inserido nao e valido. Insira novamente (i3, i5 ou i7): ");
                }
            }while(strcmp(I3, port[i].process) != 0 && strcmp(I5, port[i].process) != 0 && strcmp(I7, port[i].process) != 0);
            
            

            printf("\n\tLocalizacao: ");
            do{
                lerString(port[i].local,NMAXX);
                for(aux = 0; aux < strlen(port[i].local); aux++){
                    port[i].local[aux] = tolower(port[i].local[aux]);
                }
                if(strcmp(CAMPUS1 , port[i].local)!=0 && strcmp(CAMPUS2, port[i].local)!=0 && strcmp(CAMPUS5, port[i].local)!=0 && strcmp(RESID, port[i].local)!=0 ){
                    printf("\nLocalizacao invalida (Campus1, Campus2, Campus5 ou Residencias). Insira novamente: ");
                }
            }while(strcmp(CAMPUS1 , port[i].local)!=0 && strcmp(CAMPUS2, port[i].local)!=0 && strcmp(CAMPUS5, port[i].local)!=0 && strcmp(RESID, port[i].local)!=0);
            
            printf("\n\tData de aquisicao: ");
            port[i].aquis = lerData();
            
            printf("\n\tEstado: ");
            do{
                lerString(port[i].stat,NMAXX);
                for(aux = 0; aux < strlen(port[i].stat); aux++){
                    port[i].stat[aux] = tolower(port[i].stat[aux]);
                }
                if(strcmp(STAT_DISP, port[i].stat)!=0 && strcmp(STAT_REQ, port[i].stat)!=0 && strcmp(STAT_AVA, port[i].stat)!=0){
                    printf("\nEstado invalido (avariado, requisitado, disponivel). Insira novamente: ");
                    
                }
            }while(strcmp(STAT_DISP, port[i].stat)!=0 && strcmp(STAT_REQ, port[i].stat)!=0 && strcmp(STAT_AVA, port[i].stat)!=0);
            if(strcmp(STAT_AVA, port[i].stat)==0){
                regAva(cont, port, i);
            }
            
            printf("\n\tValor do equipamento: ");
            port[i].valuequi = lerFloat(MAXX,MAXIMUS);
            
            port[i].quantReq = 0;
            port[i].indicereq = -1;
            (*cont).portatexist = i + 1 ;

        }
        (*cont).portatexist = i ;
        (*cont).portatedisp = 0;
        for(i = 0; i< (*cont).portatexist;i++){
            if(strcmp(port[i].stat,STAT_DISP)==0){
                (*cont).portatedisp++;
            }
        }
    }
    
}

void dadosEstatisticos(CONTADOREs *cont, PORTATIl port[MAXX]){      //funcao so e acionada se houverem pcs
    int opcao, quant = 0, i,u=0;
    char processador[3];
    float percentagem;
    printf("\n\t1 - %% de portateis com um processador\n\t2 - Custo medio de cada multa\n\t3 - Tipo(s) de utente(s) com a menor quantidade de requisicoes efetuadas\n\t4 - Devolucao(coes) mais recente(s)\n\t0 - Sair\n");
    printf("\t\tOpcao -> ");
    opcao = lerInteiro(0, 4);
    switch(opcao){

    case 1:
        printf("\nIndique o processador: ");
        do{
            lerString(processador, 3);
            if(strcmp(I3, processador) != 0 && strcmp(I5, processador) != 0 && strcmp(I7, processador) != 0){
                printf("O processador inserido nao e valido. Insira novamente (i3, i5 ou i7): ");
            }
        }while(strcmp(I3, processador) != 0 && strcmp(I5, processador) != 0 && strcmp(I7, processador) != 0);
        for(i=0; i < (*cont).portatexist; i++){
            if(strcmp(processador, port[i].process)==0){
                quant++;
            }
        }
        percentagem = 100 * quant / ((*cont).portatexist);
        printf("A percentagem de processadores %s e %.2f.\n", processador, percentagem);
        break;
    case 2:

        break;
    case 3:                                     // ainda nao terminado!!!! /////
        if( (cont->totalderequisefet) == 0){
            printf("\nAinda nao foram realizadas requisicoes.\n");
        }
        else{
            int quantEst = 0, quantDoce = 0, quantTec = 0;
            //indiceEst = ;
            for(i=0; i < (cont->portatexist); i++){
                for(u = 0; u < port[i].quantReq; u++){        
                    if(strcmp(TIPO_ESTUD, port[i].requisition[u].typeut) == 0){       
                        quantEst ++;
                    }
                    if(strcmp(TIPO_DOCE, port[i].requisition[u].typeut) == 0){       
                        quantDoce ++;
                    }
                    if(strcmp(TIPO_ADM, port[i].requisition[u].typeut) == 0){       
                        quantTec ++;
                    }
                }
            }
            if(quantEst < quantDoce){
                if(quantEst < quantTec){
                    printf("\n\tO tipo de utente em minoria e o estudante: %d requisicao(coes).",quantEst);
                }
                else{
                    if(quantEst > quantTec){
                        printf("\n\tO tipo de utente em minoria e o tecnico administrativo: %d requisicao(coes).",quantTec);
                    }
                    else{
                        printf("\n\tOs tipos de utente em minoria sao neste caso o tecnico administrativo e o estudante: %d requisicao(coes).",quantTec);
                    }
                }
            }
            else{
                if(quantDoce == quantEst){
                    if(quantEst < quantTec){
                    printf("\n\tOs tipos de utente em minoria sao o estudante e o docente: %d requisicao(coes).",quantEst);
                    }
                    else{
                        if(quantEst == quantTec){
                            printf("\n\tOs utentes estudante, docente e tecnico administrativo tem a mesma quantidade de requisicoes : %d requisicao(coes).",quantTec);
                        }
                        else{
                            printf("\n\tO tipo de utente em minoria e o tecnico administrativo: %d requisicao(coes).",quantTec); 
                        }
                    }
                }
                else{
                    if(quantDoce < quantTec){
                        printf("\n\tO tipo de utente em minoria e o docente: %d requisicao(coes).",quantDoce);
                    }
                    else{
                        if(quantDoce == quantTec){
                            printf("\n\tOs tipos de utente em minoria sao o tecnico administrativo e docente: %d requisicao(coes).",quantTec);
                        }
                        else{
                            printf("\n\tO tipo de utente em minoria e o tecnico administrativo: %d requisicao(coes).",quantTec);
                        }
                    }
                }
            }
        }    
        break;
    case 4:

        break;
    default:
        printf("\n\n\n\n");
    }
}

//________________________________________________________________________________________________________________________________________________________________
void gravarFicheiroBinario(CONTADOREs cont, PORTATIl port[MAXX]){
    FILE *fc,*fp;
    //ficheiro contadores, ficheiro portateis
    int confirmacao = 1;
    char continuar;

    if(cont.portatexist == 0){
        printf("\nNão há registo(gravar nada), pretende continuar?(Y/N) ");
        do{
            continuar = getchar();
            continuar = toupper(continuar);
        }while(continuar != 'Y' && continuar != 'N');
        switch (continuar){

        case 'Y':
            confirmacao = 1 ;
            break;
        
        case 'N':
            confirmacao = 0 ;
            break;

        }
    }
    if(confirmacao == 0){
        printf("\nPor favor comece por registar computadores!");
    }
    else{
        fc = fopen("contadores.dat", "wb");
        if (fc==NULL){
            printf("\nErro ao abrir o ficheiro!\n");
        }
        else{
            fwrite(&cont,sizeof(CONTADOREs),1,fc);
            fclose(fc);
        }

        fp = fopen("portateis.dat", "wb");
        if(fp == NULL){
            printf("\nErro ao abrir o ficheiro!\n");
        }
        else{
            fwrite(port,sizeof(PORTATIl),cont.portatexist,fp);
            fclose(fp);
        }
    }
}

void lerFicheiroBinario(CONTADOREs *cont, PORTATIl port[MAXX]){
    FILE *fc,*fp;
    char problem = 'K';
    fc = fopen("contadores.dat", "rb");
    if (fc==NULL){
        printf("\nErro ao abrir o ficheiro!\n");
        problem = 'O';
    }
    else{
        fread(&(*cont),sizeof(CONTADOREs),1,fc);
        
    }
    fclose(fc);

    fp = fopen("portateis.dat", "rb");
    if (fp==NULL){
        printf("\nErro ao abrir o ficheiro!\n");
    }
    else{
        if(problem == 'O'){
            fread(port,sizeof(PORTATIl),30,fp);
        }
        else{
            fread(port,sizeof(PORTATIl),30,fp);
            
        }
        
    }
    fclose(fp);
}

/*_________________________________________________________________________________________________*/



void limpaBufferStdin(void){
    char lixo;
    do
    {
        lixo=getchar();
    }
    while (lixo!='\n' && lixo!=EOF);
}

int lerID(CONTADOREs *cont, PORTATIl port[MAXX], int idtemp){
    int i, id=-1;
    for (i=0; i<(*cont).portatexist; i++){
        if( idtemp == port[i].portId){
            id = i;
            i = (*cont).portatexist;
        }
    }
    return id;
}

int lerUtente(CONTADOREs *cont, PORTATIl port[MAXX]){
    int i, ut=0,u=0;
    char conf, confdoconf;
    ut = lerInteiro(UM,MAXIMUS);
    for (i=0; i<(*cont).portatexist; i++){
        for(u=0; u<port[i].quantReq; u++){
            if( ut == port[i].requisition[u].numutent && strcmp(port[i].requisition[u].statreq,STAT_ATIV)==0){
                printf("\nO utente com o numero %d, ja tem uma requisicao ativa!",port[i].requisition[u].numutent);
                u = port[i].quantReq;
                i = (*cont).portatexist;
                printf("\n\tDeseja continuar com o registo com este numero?(S/N)");
                do{
                    conf = getchar();
                    conf = toupper(conf);
                }while(conf != 'S'&& conf != 'N');
            }
        }
    }
    if(conf == 'N'){
        ut = -2;
    }
    if(conf == 'S'){
        printf("\n\t\tDeseja utilizar este numero mesmo com os avisos previamente alertados?(S/N)");
        do{
            confdoconf = getchar();
            confdoconf = toupper(confdoconf);
        }while(confdoconf != 'S' && confdoconf != 'N');
        if(confdoconf == 'S'){}
        else{
            ut = -1;
        }
    }
    return ut;
}

int procurarReq(CONTADOREs *cont, PORTATIl port[MAXX], int *sitio){
    int i, cod = -1, u;
    char code[NMAXX];
    lerString(code, NMAXX);
    for (i=0; i < (*cont).portatexist; i++){
        for(u = 0; u < port[i].quantReq; u++) {
            if (strcmp(port[i].requisition[u].requiscode, code)==0){  
                cod = i;
                *sitio = u;

                i = (*cont).portatexist;
                u = port[i].quantReq;
            }
        }
    }
    return cod;
}

int lerDesignacao(CONTADOREs *cont, PORTATIl port[MAXX], int pos){
    int i, des = 0;
    char design[MAX_DESIG];
    lerString(design, MAX_DESIG);
    for (i=0; i < (*cont).portatexist; i++){
        if (strcmp(port[i].desig, design)==0){  
            des = -1;
            i = (*cont).portatexist;
            printf("\nErro, designacao existente.\n");
        }
    }
    if(des != -1){
        strcpy(port[pos].desig, design);
    }
    return des;
}
int subtrairDatas(DATa d1, DATa d2){
    int numerodedias=0,numerodedias1=0,numerodedias2 =0, numerodemeses =0, numerodeanos = 0, diffdias = 0;
    
    if((d2.ano > d1.ano )|| (d2.ano==d1.ano && d2.mes > d1.mes )|| (d2.ano==d1.ano && d2.mes==d1.mes && d2.dia >d1.dia)){
        if(d2.ano==d1.ano && d2.mes==d1.mes && d2.dia >d1.dia){
            numerodedias = d2.dia - d1.dia;
        }
        if(d2.ano==d1.ano && d2.mes > d1.mes){
            for(numerodemeses = d1.mes; numerodemeses<d2.mes; numerodemeses++){
                switch(numerodemeses){
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        numerodedias+=31;
                        break;
                    case 2:
                        if((d2.ano%400==0) || (d2.ano%4==0 && d2.ano%100!=0)){
                            numerodedias+= 29;
                        }       
                        else{
                            numerodedias+= 28;
                        }
                        break;
                    default:
                        numerodedias += 30;
                }
            }
            numerodedias += (d2.dia-d1.dia);
        }
        if(d2.ano > d1.ano ){
            for(numerodeanos = d1.ano; numerodeanos < d2.ano; numerodeanos++){
                if((numerodeanos%400==0) || (numerodeanos%4==0 && numerodeanos%100!=0)){
                    numerodedias += 366;
                }
                else{
                    numerodedias += 365;
                }
            }
            if(d2.mes > d1.mes){
                for(numerodemeses = d1.mes; numerodemeses<d2.mes; numerodemeses++){
                    switch(numerodemeses){
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12:
                            numerodedias+=31;
                            break;
                        case 2:
                            if((d2.ano%400==0) || (d2.ano%4==0 && d2.ano%100!=0)){
                                numerodedias+= 29;
                            }       
                            else{
                                numerodedias+= 28;
                            }
                            break;
                        default:
                            numerodedias += 30;
                    }
                }
                numerodedias += (d2.dia-d1.dia);
            }
            else{
                for(numerodemeses = d1.mes; numerodemeses!=0; numerodemeses--){
                    switch(numerodemeses){
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12:
                            numerodedias1+=31;
                            break;
                        case 2:
                            if((d1.ano%400==0) || (d1.ano%4==0 && d1.ano%100!=0)){
                                numerodedias1+= 29;
                            }       
                            else{
                                numerodedias1+= 28;
                            }
                            break;
                        default:
                            numerodedias1 += 30;
                    }
                }
                numerodedias1 += d1.dia;
                for(numerodemeses = d2.mes; numerodemeses!=0; numerodemeses--){
                    switch(numerodemeses){
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12:
                            numerodedias2+=31;
                            break;
                        case 2:
                            if((d2.ano%400==0) || (d2.ano%4==0 && d2.ano%100!=0)){
                                numerodedias2+= 29;
                            }       
                            else{
                                numerodedias2+= 28;
                            }
                            break;
                        default:
                            numerodedias += 30;
                    }
                }
                numerodedias2 += d2.dia;
                numerodedias += (numerodedias2 - numerodedias1);
            }

        }
 
    }
    else{
        numerodedias = -1;
    }
    return numerodedias;
}

DATa lerData(void){
    DATa data;
    int maxDias=31;
    printf("-Indique a Data-\n");
    printf("Ano: ");
    data.ano = lerInteiro(MENOR_ANO, MAIOR_ANO);

    printf("Mes: ");
    data.mes = lerInteiro(UM,12);
    switch(data.mes){
    case 2:
        if((data.ano%400==0) || (data.ano%4==0 && data.ano%100!=0)){
            maxDias = 29;       //ano bissexto
        }
        else{
            maxDias = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDias = 30;
    }

    printf("Dia: ");
    data.dia = lerInteiro(UM, maxDias);

    return data;
}

int lerInteiro(int min, int max){
    int numero, controlo;
    do
    {
        controlo = scanf("%d", &numero);
        limpaBufferStdin(); 
        if (numero<min || numero>max || controlo==0){
            printf("\nValor invalido! Insira novamente: ");
        }
    }
    while (numero<min || numero>max || controlo==0);
    return numero;
}



float lerFloat(float min, float max)
{
    float numero;
    int controlo;
    do{
        controlo = scanf("%f", &numero); // scanf devolve quantidade de valores válidos obtidos
        limpaBufferStdin(); /* elimina caracteres que ficaram no buffer stdin */
        if(numero<min || numero>max || controlo==0){
            printf("\nValor invalido! Insira novamente: ");
        }
    }while (numero<min || numero>max || controlo==0);
    return numero;
}



void lerString(char vetor[], int max)
{
    int tamanhoString;
    do  /*Repete leitura caso sejam introduzidas strings apenas com o \n (tamanhoString == 1) */
    {
        fgets(vetor, max, stdin);
        tamanhoString = strlen(vetor);
    }
    while(tamanhoString == 1);
    if (vetor[tamanhoString-1] != '\n'){
        /* armazenados no vetor todos os caracteres */
        limpaBufferStdin(); /* elimina caracteres que ficaram no buffer stdin */
    }
    else {
        vetor[tamanhoString-1] ='\0'; /*substitui \n da string armazenada em vetor por \0 */
    }
}

