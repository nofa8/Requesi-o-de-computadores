#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXIMUS 9999
#define MAXX 30
#define NMAXX 15
#define SETE 7
#define UM 1
#define ZERO 0

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
#define MAIOR_ANO 2025

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
    int quantReq;
    int indicereq;
    int quantDiasReq;
    //______________
    int portId;
    char desig[MAX_DESIG];
    char process[4];
    int  memoria;
    //_____________
    int quantAvarias;
    char stat[NMAXX];
    //_______________
    char local[NMAXX];
    DATa aquis;
    float valuequi;
    //_______________
    int quantDev;
    DATa ultimadev;
}PORTATIl;
typedef struct{
    int portid;
    int indiceport;
    char tipoavaria[NMAXX];
    DATa dataavaria;
    //________________
    char statavaria[NMAXX];
    DATa fimavaria;
    int duracaoavaria;
} AVARIAs;
typedef struct{
    int indiceport;
    int portid;
    char requiscode[NMAXX];
    DATa requis;
    int numpraz;     //prazo em dias
    DATa praz;      // prazo requisicao
    //state of a pc?
    //estado de requesição
    char statreq[NMAXX];

    //Devolução
    DATa devol;
    char local[NMAXX];
    //Fine = multa
    float finee;
    int prazreal;

    //UTENTE STUFF
    char typeut[25];
    int numutent;
    char nomedoutente[MAX_NOME];
}REQUi;
typedef struct{
    int portatexist;        // Portateis existentes
    int portatedisp;        //Portateis disponiveis
    int totalderequisefet;  // Total de requisiçoes feitas
    int requisativas;       // Requisiçoes ativas
    int totaldeavarias;
} CONTADOREs;
















void limpaBufferStdin(void);
int lerInteiro(int min, int max);
void lerString(char vetor[], int max);
float lerFloat(float min, float max);
DATa lerData(void);
int subtrairDatas(DATa d1, DATa d2);
DATa sumD(DATa d1, int d);

char menu(CONTADOREs *cont,PORTATIl port[MAXX]);
void subListar(CONTADOREs *cont, PORTATIl port1[MAXX], REQUi *req, AVARIAs *ava);

void lePortate(CONTADOREs *cont, PORTATIl port2[MAXX], REQUi *req);
void regAva(CONTADOREs *cont, PORTATIl port[MAXX],int ind, AVARIAs *ava);
void regRep(CONTADOREs *cont, PORTATIl port[MAXX], int indice, AVARIAs *ava);
void regRq(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);
void listaReq(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);
void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava);
void dadosEstatisticos(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);
int procurarReq(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);


int lerID(CONTADOREs *cont, PORTATIl port[MAXX], int idtemp);
int lerUtente(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);
int lerDesignacao( CONTADOREs *cont, PORTATIl port[MAXX], int pos);

void gravarFicheiroBinario(CONTADOREs cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava);
void lerFicheiroBinario(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava);


int main()
{
    REQUi *req;
    AVARIAs *ava;
    req = NULL;
    ava = NULL;
    CONTADOREs oscontadores;
    PORTATIl portateis[MAXX];
    char escolha, outrolocal[NMAXX],rqcode[NMAXX];
    int i = 0, pc = 0, confoutro = -1, aux = 0, aux1 = -1,aux2=-1;
    oscontadores.portatexist = 0;
    oscontadores.portatedisp = 0;
    oscontadores.requisativas = 0;
    oscontadores.totalderequisefet = 0;
    oscontadores.totaldeavarias =0;
    do{
        int conf = -1;
        escolha = menu(&oscontadores,portateis);
        switch(escolha){
            case 'I':
                insertPCs(&oscontadores, portateis,req,ava);
                break;
            case 'L':
                subListar(&oscontadores, portateis, req,ava);
                break;
            case 'R':
                regRq(&oscontadores, portateis,req);
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
                    if(strcmp(portateis[conf].stat,STAT_REQ)==0){
                        printf("\n\tErro portatil requisitado.Nao e possivel registar avaria.");
                    }
                    if(strcmp(portateis[conf].stat,STAT_AVA)==0){
                        regRep(&oscontadores,portateis,conf,ava);
                        strcpy(portateis[conf].stat,STAT_DISP);
                        oscontadores.portatedisp++;

                    }
                    else{
                        if(strcmp(portateis[conf].stat,STAT_DISP)==0){  // conf indica o vetor do port
                            regAva(&oscontadores,portateis,conf,ava);
                            strcpy(portateis[conf].stat,STAT_AVA);
                            oscontadores.portatedisp--;
                        }
                        if(strcmp(portateis[conf].stat,STAT_REQ)==0){
                            regAva(&oscontadores,portateis,conf,ava);
                            strcpy(portateis[conf].stat,STAT_AVA);
                            for( i = oscontadores.totalderequisefet; i >=0;i--){
                                if(req[i].portid == portateis[conf].portId){
                                    if(strcmp(req[i].statreq,STAT_ATIV)==0){
                                        strcpy(req[i].statreq,STAT_CONC);
                                        
                                    }
                                    oscontadores.requisativas--;
                                    i = -1;
                                }
                            }
                        }
                    }
                }
                break;
            case 'D':
                if((oscontadores.portatexist == 0)){
                    printf("\nNao ha computadores, comece por registar computadores!\n");
                }
                else{
                    if(oscontadores.requisativas == 0){
                        printf("\nNao ha requisicoes ativas.\n");
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
                        pc = -1;
                        for(aux1 = (oscontadores.totalderequisefet-1);aux1!=0; aux1--){
                            if(req[aux1].indiceport == conf){
                                pc = aux1;
                                //indice do portatil
                                aux1 = 0;
                            }
                        }
                        if(pc == -1){
                            printf("\n\tErro nao ha requisicoes do portatil.\n");
                        }
                        else{
                            if(strcmp(req[pc].statreq,STAT_ATIV)==0){
                                printf("\n\tData da devolucao: ");
                                do{
                                    req[pc].devol = lerData();
                                    req[pc].prazreal = subtrairDatas(req[pc].requis,req[pc].devol);
                                    if(req[pc].prazreal < 0){
                                        printf("\n\tErro data de devolucao nao pode ser inferior a data de requisicao.\nInsira novamente: ");
                                    }
                                }while(req[pc].prazreal < 0);
                                portateis[req[pc].indiceport].ultimadev = req[pc].devol;
                                portateis[req[pc].indiceport].quantDiasReq +=req[pc].prazreal;
                                printf("\n\tLocal de devolucao: ");
                                do{
                                    lerString(req[pc].local,NMAXX);
                                    for(aux = 0; aux < strlen(req[pc].local); aux++){
                                        req[pc].local[aux] = tolower(req[pc].local[aux]);
                                    }
                                    if(strcmp(CAMPUS1 , req[pc].local)!=0 && strcmp(CAMPUS2, req[pc].local)!=0 && strcmp(CAMPUS5, req[pc].local)!=0 && strcmp(RESID, req[pc].local)!=0 ){
                                        printf("\nLocalizacao invalida (Campus1, Campus2, Campus5 ou Residencias). Insira novamente: ");
                                    }
                                }while(strcmp(CAMPUS1 , req[pc].local)!=0 && strcmp(CAMPUS2, req[pc].local)!=0 && strcmp(CAMPUS5, req[pc].local)!=0 && strcmp(RESID, req[pc].local)!=0 );

                                if(req[pc].prazreal > req[pc].numpraz){
                                    //10€ por dia
                                    req[pc].finee = 10*(req[pc].prazreal - req[pc].numpraz);
                                    printf("\n\tO valor a pagar e %d€.\n",req[pc].finee);
                                }
                                else{
                                    req[pc].finee= 0;
                                    printf("\n\tNao ha multa.\n");
                                }
                            }
                            else{
                                printf("\n\tErro requisicao concluida.");
                            }
                        }
                    }
                }
                break;
            case 'A':
                if(oscontadores.portatexist ==0){
                    printf("\n\tComece por registar computadores.\n");
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
                    printf("\n\tLocalizacao: ");
                    if(strcmp(portateis[conf].stat, STAT_DISP)==0){
                        do{
                            lerString(outrolocal, NMAXX);
                            for(aux = 0; aux < strlen(outrolocal); aux++){
                                outrolocal[aux] = tolower(outrolocal[aux]);
                            }
                            if((strcmp(outrolocal, portateis[conf].local)==0)||(strcmp(CAMPUS1 , outrolocal)!=0 && strcmp(CAMPUS2, outrolocal)!=0 && strcmp(CAMPUS5, outrolocal)!=0 && strcmp(RESID, outrolocal)!=0)){
                                printf("\nLocalizacao atual ,%s, opcoes: (Campus1, Campus2, Campus5 ou Residencias). Insira novamente: ",portateis[conf].stat);
                            }
                        }while((strcmp(outrolocal, portateis[conf].local)==0)||(strcmp(CAMPUS1 , outrolocal)!=0 && strcmp(CAMPUS2, outrolocal)!=0 && strcmp(CAMPUS5, outrolocal)!=0 && strcmp(RESID, outrolocal)!=0));
                        strcpy(portateis[conf].local,outrolocal);
                    }
                    else{
                        printf("\n\tErro portatil nao se encontra disponivel!\n\n");
                    }
                }
                break;
            case 'Y':
                if(oscontadores.portatedisp >0){
                    printf("\n\tID da requisicao: ");
                    lerString(rqcode,NMAXX);
                    for(aux = oscontadores.totalderequisefet-1;aux >=0;aux--){
                        if(rqcode == req[aux].requiscode){
                            if(strcmp(portateis[req[aux].indiceport].stat,STAT_REQ)==0){
                                if(strcmp(req[aux].statreq,STAT_ATIV)==0){

                                    req[aux].requis = sumD(req[aux].requis,SETE);
                                    req[aux].numpraz = req[aux].numpraz + 7;
                                    printf("\n\tNova Data Prazo: %d - %d - %d",req[aux].requis.dia,req[aux].requis.mes,req[aux].requis.ano);
                                    aux = -1;
                                }
                                else{
                                    printf("\n\tErro requisicao concluida.\n");
                                }
                            }
                            else{
                                printf("\n\tErro portatil nao requisitado!\n");
                            }
                        }
                    }
                }
                break;
            case 'G':
                gravarFicheiroBinario(oscontadores, portateis,req,ava);
                //gravarFicheiroTexto(oscontadores,portateis);

                break;
            case 'E':
                lerFicheiroBinario(&oscontadores, portateis,req,ava);
                break;
            case 'Z':
                if(oscontadores.portatexist==0){
                    printf("\nNao existem portateis inseridos. Nao e possivel apresentar estatisticas.\n\n");
                }
                else{
                    dadosEstatisticos(&oscontadores, portateis,req);
                }
                break;

            case 'S':
                printf("\nA sair ...\n");

        }
    }while(escolha != 'S');


    free(req);
    free(ava);
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
void subListar(CONTADOREs *cont, PORTATIl port1[MAXX], REQUi *req, AVARIAs *ava){
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
        lePortate(cont,port1,req);
        break;
    case 'T':
        listaReq(cont,port1,req);
        break;
    case 'R':
        printf("\n\tCodigo da requisicao: ");
        do{
            conf = procurarReq(cont,port1,req);
            if(conf == -1){
                printf("\n\tErro codigo de requisicao invalido.Insira novamente: ");
            }
        }while(conf == -1);
        // port1[conf].requisition[indiceREQ]
        printf("\n\n\tDesignacao do portatil: %s", port1[conf].desig);
        printf("\n\tEstado do portatil: %s",port1[conf].stat);
        //Quantidade total de dias requisitados do pc ou requisicao Falar com a Eunice
        //voltaremos ...
        printf("\n\tQuantidade total de dias requisitado: %d dias",port1[req[conf].indiceport].quantDiasReq);
        printf("\n\tData requisicao: %d/%d/%d",req[conf].requis.dia,req[conf].requis.mes,req[conf].requis.ano);
        printf("\n\tEstado da requisicao: %s",req[conf].statreq);
        if(strcmp(req[conf].statreq, STAT_ATIV)==0){
            printf("\n\tDia maximo de Devolucao: %d/%d/%d",req[conf].praz.dia,req[conf].praz.mes,req[conf].praz.ano);
            printf("\n\tDuracao maxima da requisicao: %d",req[conf].numpraz);
            printf("\n\tLocal: ---\n\tMulta: ---\n");
        }
        else{
            printf("\n\tDevolucao: %d/%d/%d",req[conf].devol.dia,req[conf].devol.mes,req[conf].devol.ano);
            printf("\n\tDuracao da  requisicao: %d",req[conf].prazreal);
            printf("\n\tLocal: %s\n\tMulta: %f\n",req[conf].local,req[conf].finee);
        }
        printf("\n\tTipo de utente: %s.\n\tNumero de utente: %d.\n\tNome de utente: %s",req[conf].typeut,req[conf].numutent,req[conf].nomedoutente);
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
                    for(u = 0;u < cont->totaldeavarias; u++){
                        if(port1[i].portId == ava[u].portid){       //confirmar que avaria esta associada ao pc escolhido
                            printf("\n\tTipo de avaria: %s.", ava[u].tipoavaria);
                            printf("\n\tData de avaria: %d-%d-%d", ava[u].dataavaria.dia, ava[u].dataavaria.mes, ava[u].dataavaria.ano);
                            if(strcmp(ava[u].tipoavaria,STAT_PERM)==0){
                                printf("\n\tAvaria permanente");
                            }
                            else{
                                if(strcmp(ava[u].statavaria,STAT_ATIV)==0){    //ultima avaria ligada ao estado do pc
                                    if(strcmp(port1[i].stat,STAT_AVA)==0){
                                        printf("\n\tAvaria continua");
                                    }
                                }
                                else{
                                    printf("\n\tFim da avaria: %d-%d-%d",ava[u].fimavaria.dia,ava[u].fimavaria.mes,ava[u].fimavaria.ano);
                                    printf("\n\tDuracao da avaria: %d", ava[u].duracaoavaria);
                                }
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
// looks good !!!
void lePortate(CONTADOREs *cont, PORTATIl port2[MAXX],REQUi *req){
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
                for(u = 0; u < cont->totalderequisefet; u++){
                    if(req[u].portid == port2[i].portId){
                        printf("\t\tTipo de utente: %15s\tPrazo de requisicao: %d dias\n", req[u].typeut, req[u].numpraz);
                    }
                }
            }
        }

    }
    else{
        printf("\nNao ha computadores!\n");
    }
}

void regRep(CONTADOREs *cont, PORTATIl port[MAXX], int indice, AVARIAs *ava){     //confirmar valor do indice
    int i=0;
    for(i= (cont->totaldeavarias-1); i >=0;i--){
        if(ava[i].indiceport == indice){
            indice = i;
            i = 0;
            printf("%d",indice);
        }
    }
    if(strcmp(ava[indice].tipoavaria,STAT_PERM)==0){
        printf("\n\tTipo de avaria permanente.\n");
    }
    else{
        do{
            ava[indice].fimavaria = lerData();
            if(ava[indice].fimavaria.ano <  ava[indice].dataavaria.ano || (ava[indice].fimavaria.ano ==  ava[indice].dataavaria.ano && ava[indice].fimavaria.mes <  ava[indice].dataavaria.mes)||(ava[indice].fimavaria.ano ==  ava[indice].dataavaria.ano && ava[indice].fimavaria.mes ==  ava[indice].dataavaria.mes && ava[indice].fimavaria.dia <  ava[indice].dataavaria.dia)){
                printf("\nData invalida.Data: ");
            }
        }while(ava[indice].fimavaria.ano <  ava[indice].dataavaria.ano || (ava[indice].fimavaria.ano ==  ava[indice].dataavaria.ano && ava[indice].fimavaria.mes <  ava[indice].dataavaria.mes)||(ava[indice].fimavaria.ano ==  ava[indice].dataavaria.ano && ava[indice].fimavaria.mes ==  ava[indice].dataavaria.mes && ava[indice].fimavaria.dia <  ava[indice].dataavaria.dia));
        ava[indice].duracaoavaria = subtrairDatas(ava[indice].dataavaria, ava[indice].fimavaria);
        strcpy(ava[indice].statavaria, STAT_CONC);      //avaria reparada
    }

}

//falta so ver o comentario
void regAva(CONTADOREs *cont, PORTATIl port[MAXX],int ind, AVARIAs *ava){     //confirmar valor de indice
    int i=0,u=0,indice = -1;
    AVARIAs *a;
    a = ava;
    
    ava = realloc(ava , (cont->totaldeavarias+1)*sizeof(AVARIAs));
    if(ava == NULL){
        printf("\nMemoria indisponivel.\n ");
        ava = a;
    }
    else{
        indice = cont->totaldeavarias;
        ava[indice].indiceport = ind;
        ava[indice].portid = port[ava[indice].indiceport].portId;
        
        printf("\n\tTipo de avaria: ");
        do{
            lerString(ava[indice].tipoavaria, NMAXX);
            for(i = 0; i < strlen(ava[indice].tipoavaria); i++){
                ava[indice].tipoavaria[i] = tolower(ava[indice].tipoavaria[i]);
            }
            if(strcmp(ava[indice].tipoavaria, STAT_TEMP)!= 0 && strcmp(ava[indice].tipoavaria, STAT_PERM)!= 0){
                printf("\nErro tipo de avaria invalido (temporaria ou permanente).Insira novamente: ");
            }
        }while(strcmp(ava[indice].tipoavaria, STAT_TEMP)!= 0 && strcmp(ava[indice].tipoavaria, STAT_PERM)!= 0);

        printf("\n\tData de avaria: ");
        do{
            ava[indice].dataavaria = lerData();
            if(ava[indice].dataavaria.ano < port[ava[indice].indiceport].aquis.ano ||(ava[indice].dataavaria.ano == port[ava[indice].indiceport].aquis.ano && ava[indice].dataavaria.mes < port[ava[indice].indiceport].aquis.mes)||ava[indice].dataavaria.ano == port[ava[indice].indiceport].aquis.ano && ava[indice].dataavaria.mes == port[ava[indice].indiceport].aquis.mes && ava[indice].dataavaria.dia < port[ava[indice].indiceport].aquis.dia){
                printf("\n\tErro, dia de avaria nao pode ser inferior ao dia de aquisicao.\n\t\tData:");
            }
        }while((ava[indice].dataavaria.ano < port[ava[indice].indiceport].aquis.ano ||(ava[indice].dataavaria.ano == port[ava[indice].indiceport].aquis.ano && ava[indice].dataavaria.mes < port[ava[indice].indiceport].aquis.mes)||ava[indice].dataavaria.ano == port[ava[indice].indiceport].aquis.ano && ava[indice].dataavaria.mes == port[ava[indice].indiceport].aquis.mes && ava[indice].dataavaria.dia < port[ava[indice].indiceport].aquis.dia));
        strcpy(ava[indice].statavaria, STAT_ATIV);      //avaria nao esta reparada
        port[indice].quantAvarias++;
        (cont->totaldeavarias)++;
    }
}
//parece que sim
void regRq(CONTADOREs *cont, PORTATIl port[MAXX],REQUi *req){
    int i= 0,l=0,h = 0,u = 0,idTemporario = 0, indice=-1, numutente = 0, date = 0;
    REQUi *r;
    r = req;
    if(cont->totalderequisefet != 0){
        
            if((*cont).portatedisp >0){
                printf("\nInsira o numero de identificacao do portatil: ");
                idTemporario = lerInteiro(UM,MAXIMUS);
                for (l=0;l<(*cont).portatexist;l++){
                    if(port[l].portId == idTemporario){
                        indice = l;

                        if(strcmp(port[indice].stat,STAT_DISP)==0){
                            printf("\n\t%d",cont->totalderequisefet+1);
                            req = realloc(req, (cont->totalderequisefet+1)*sizeof(REQUi));
                            if(req == NULL){
                                printf("\nMemoria indisponivel.\n");
                                req = r;
                            }
                            else{
                                //Codigo de Requisicao

                                printf("\nCodigo de requisicao: ");
                                do{
                                    lerString(req[(*cont).totalderequisefet].requiscode,NMAXX);
                                    for(i = 0; i <(*cont).totalderequisefet;i++){
                                            if(strcmp(req[(*cont).totalderequisefet].requiscode,req[i].requiscode)==0){
                                                    printf("\nCodigo de requisicao indisponivel.\n");
                                                    u = -1;
                                                    i = cont->portatexist;
                                            }
                                    }
                                }while(u == -1);
                                //Data Requisição
                                printf("\nData de Requisicao: ");
                                do{
                                    req[cont->totalderequisefet].requis = lerData();
                                    if(port[indice].quantReq != 0){
                                        if((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia)){
                                            printf("\n\tErro data invalida nao pode ser inferior ao dia de aquisicao.");
                                        }
                                    }
                                    else{
                                        if((port[indice].ultimadev.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes == req[cont->totalderequisefet].requis.mes && port[indice].ultimadev.dia > req[cont->totalderequisefet].requis.dia)){
                                            printf("\n\tErro data invalida nao pode ser inferior ao dia da ultima devolucao. Insira Novamente: ");
                                        }
                                    }

                                }while((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia) || (port[indice].ultimadev.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes == req[cont->totalderequisefet].requis.mes && port[indice].ultimadev.dia > req[cont->totalderequisefet].requis.dia));
                                //PRazo e cenas...
                                printf("\nPrazo de Devolucao: ");
                                do{
                                    date = 0;
                                    req[cont->totalderequisefet].praz = lerData();
                                    if(!((req[cont->totalderequisefet].praz.ano > req[cont->totalderequisefet].requis.ano) || (req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes > req[cont->totalderequisefet].requis.mes) || ( req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes == req[cont->totalderequisefet].requis.mes&&req[cont->totalderequisefet].praz.dia >= req[cont->totalderequisefet].requis.dia))){
                                        printf("\n\tData invalida.\n");
                                    }
                                    req[cont->totalderequisefet].numpraz = subtrairDatas(req[cont->totalderequisefet].requis,req[cont->totalderequisefet].praz);
                                    if(req[cont->totalderequisefet].numpraz >30 ){
                                            date = -1;
                                            printf("\nErro. O prazo maximo sao 30 dias.");
                                    }
                                }while((date == -1)||((req[cont->totalderequisefet].praz.ano < req[cont->totalderequisefet].requis.ano) || (req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes < req[cont->totalderequisefet].requis.mes) || ( req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes == req[cont->totalderequisefet].requis.mes&&req[cont->totalderequisefet].praz.dia < req[cont->totalderequisefet].requis.dia)));
                                //Prazo de devolução tem de ser superior ao dia de requisição


                                //Nome Utente
                                printf("\nNome do utente: ");
                                lerString(req[cont->totalderequisefet].nomedoutente, MAX_NOME);

                                //Typo Utente
                                printf("\nTipo de utente: ");
                                do{
                                    lerString(req[cont->totalderequisefet].typeut, 25);
                                    for(h = 0; h < strlen(req[cont->totalderequisefet].typeut);h++){
                                        req[cont->totalderequisefet].typeut[h] = tolower(req[cont->totalderequisefet].typeut[h]);
                                    }
                                    if( strcmp(req[cont->totalderequisefet].typeut, TIPO_ESTUD)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_DOCE)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_ADM)!= 0){
                                        printf("\nErro tipo de utente invalido (estudante, docente, tecnico administrativo).Insira novamente: ");
                                    }
                                }while(strcmp(req[cont->totalderequisefet].typeut, TIPO_ESTUD)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_DOCE)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_ADM)!= 0);

                                // Numero de utente
                                printf("\nNumero do utente: ");
                                do{
                                    numutente = lerUtente(cont, port,req);
                                }while(numutente == -1);
                                if(numutente == -2){
                                    printf("\n\t\t\t\tRegisto cancelado!\n");
                                }
                                else{
                                    req[cont->totalderequisefet].numutent = numutente;
                                    (port[indice].quantReq)++;
                                    strcpy(req[cont->totalderequisefet].statreq, STAT_ATIV);
                                    req[cont->totalderequisefet].portid = port[indice].portId;
                                    req[cont->totalderequisefet].indiceport = indice;
                                    ((*cont).requisativas)++;
                                    (cont->totalderequisefet)++;
                                    (cont->portatedisp)--;
                                    strcpy(port[indice].stat, STAT_REQ);

                                }
                            }
                        }
                        else{
                            printf("\nPortatil indisponivel\n");
                        }
                        l = (*cont).portatexist;
                        //fim do ciclo
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
    else{
        if((*cont).portatedisp >0){
                printf("\nInsira o numero de identificacao do portatil: ");
                idTemporario = lerInteiro(UM,MAXIMUS);
                for (l=0;l<(*cont).portatexist;l++){
                    if(port[l].portId == idTemporario){
                        indice = l;

                        if(strcmp(port[indice].stat,STAT_DISP)==0){

                            req = realloc(req,((*cont).totalderequisefet+1)*sizeof(REQUi));
                            //adiciona espaço
                            //Codigo de Requisicao

                            printf("\nCodigo de requisicao: ");
                            do{
                                lerString(req[(*cont).totalderequisefet].requiscode,NMAXX);
                                for(i = 0; i <(*cont).totalderequisefet;i++){
                                        if(strcmp(req[(*cont).totalderequisefet].requiscode,req[i].requiscode)==0){
                                                printf("\nCodigo de requisicao indisponivel.\n");
                                                u = -1;
                                                i = cont->portatexist;
                                        }
                                }
                            }while(u == -1);
                            //Data Requisição
                            printf("\nData de Requisicao: ");
                            do{
                                req[cont->totalderequisefet].requis = lerData();
                                if(port[indice].quantReq != 0){
                                    if((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia)){
                                        printf("\n\tErro data invalida nao pode ser inferior ao dia de aquisicao.");
                                    }
                                }
                                else{
                                    if((port[indice].ultimadev.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes == req[cont->totalderequisefet].requis.mes && port[indice].ultimadev.dia > req[cont->totalderequisefet].requis.dia)){
                                        printf("\n\tErro data invalida nao pode ser inferior ao dia da ultima devolucao. Insira Novamente: ");
                                    }
                                }

                            }while((port[indice].aquis.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].aquis.ano == req[cont->totalderequisefet].requis.ano && port[indice].aquis.mes == req[cont->totalderequisefet].requis.mes && port[indice].aquis.dia > req[cont->totalderequisefet].requis.dia) || (port[indice].ultimadev.ano > req[cont->totalderequisefet].requis.ano) || (port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes > req[cont->totalderequisefet].requis.mes) || ( port[indice].ultimadev.ano == req[cont->totalderequisefet].requis.ano && port[indice].ultimadev.mes == req[cont->totalderequisefet].requis.mes && port[indice].ultimadev.dia > req[cont->totalderequisefet].requis.dia));
                            //PRazo e cenas...
                            printf("\nPrazo de Devolucao: ");
                            do{
                                req[cont->totalderequisefet].praz = lerData();
                                if(!((req[cont->totalderequisefet].praz.ano > req[cont->totalderequisefet].requis.ano) || (req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes > req[cont->totalderequisefet].requis.mes) || ( req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes == req[cont->totalderequisefet].requis.mes&&req[cont->totalderequisefet].praz.dia >= req[cont->totalderequisefet].requis.dia))){
                                    printf("\n\tData invalida.\n");
                                }
                                req[cont->totalderequisefet].numpraz = subtrairDatas(req[cont->totalderequisefet].requis,req[cont->totalderequisefet].praz);
                                if(req[cont->totalderequisefet].numpraz >30 ){
                                        date = -1;
                                        printf("\nErro. O prazo maximo sao 30 dias.");
                                }
                            }while( (date == -1)||(!((req[cont->totalderequisefet].praz.ano > req[cont->totalderequisefet].requis.ano) || (req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes > req[cont->totalderequisefet].requis.mes) || ( req[cont->totalderequisefet].praz.ano == req[cont->totalderequisefet].requis.ano && req[cont->totalderequisefet].praz.mes == req[cont->totalderequisefet].requis.mes&&req[cont->totalderequisefet].praz.dia >= req[cont->totalderequisefet].requis.dia))));
                            //Prazo de devolução tem de ser superior ao dia de requisição


                            //Nome Utente
                            printf("\nNome do utente: ");
                            lerString(req[cont->totalderequisefet].nomedoutente, MAX_NOME);

                            //Typo Utente
                            printf("\nTipo de utente: ");
                            do{
                                lerString(req[cont->totalderequisefet].typeut, 25);
                                for(h = 0; h < strlen(req[cont->totalderequisefet].typeut);h++){
                                    req[cont->totalderequisefet].typeut[h] = tolower(req[cont->totalderequisefet].typeut[h]);
                                }
                                if( strcmp(req[cont->totalderequisefet].typeut, TIPO_ESTUD)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_DOCE)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_ADM)!= 0){
                                    printf("\nErro tipo de utente invalido (estudante, docente, tecnico administrativo).Insira novamente: ");
                                }
                            }while(strcmp(req[cont->totalderequisefet].typeut, TIPO_ESTUD)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_DOCE)!= 0 && strcmp(req[cont->totalderequisefet].typeut, TIPO_ADM)!= 0);

                            // Numero de utente
                            printf("\nNumero do utente: ");
                            do{
                                numutente = lerUtente(cont, port,req);
                            }while(numutente == -1);
                            if(numutente == -2){
                                printf("\n\t\t\t\tRegisto cancelado!\n");
                            }
                            else{
                                req[cont->totalderequisefet].numutent = numutente;
                                (port[indice].quantReq)++;
                                strcpy(req[cont->totalderequisefet].statreq, STAT_ATIV);
                                req[cont->totalderequisefet].portid = port[indice].portId;
                                req[cont->totalderequisefet].indiceport = indice;
                                ((*cont).requisativas)++;
                                (cont->totalderequisefet)++;
                                (cont->portatedisp)--;
                                strcpy(port[indice].stat, STAT_REQ);

                            }
                        }
                        else{
                            printf("\nPortatil indisponivel\n");
                        }
                        l = (*cont).portatexist;
                        //fim do ciclo
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
}
//parece que sim
void listaReq(CONTADOREs *cont, PORTATIl port[MAXX],REQUi *req){
    int i=0,u=0,o=0;
    if(cont->totalderequisefet != 0){
        for(i=0; i<cont->totalderequisefet;i++){
            printf("\nComputador: %s",port[req[i].indiceport].desig);
                  // requi e um vetor, logo temos de fazer outro for
                printf("\n\tData requisicao: %d/%d/%d",req[i].requis.dia,req[i].requis.mes,req[i].requis.ano);
                printf("\n\tEstado da requisicao: %s",req[i].statreq);
                if(strcmp(req[i].statreq, STAT_ATIV)==0){
                    printf("\n\tDia maximo de Devolucao: %d/%d/%d",req[i].praz.dia,req[i].praz.mes,req[i].praz.ano);
                    printf("\n\tDuracao maxima da requisicao: %d",req[i].numpraz);
                    printf("\n\tLocal: ---\n\tMulta: ---\n");
                }
                else{
                    printf("\n\tDevolucao: %d/%d/%d",req[i].devol.dia,req[i].devol.mes,req[i].devol.ano);
                    printf("\n\tDuracao da  requisicao: %d",req[i].prazreal);
                    printf("\n\tLocal: %s\n\tMulta: %d\n",req[i].local,req[i].finee);
                }

        }
    }
}

//Tá bom! ! !
void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava){
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
            port[i].quantDev = 0;
            port[i].quantDiasReq=0;
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


            printf("\n\tQuantidade de memoria: ");

            port[i].memoria = lerInteiro(UM,MAXIMUS);

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

            //estado
            strcpy(port[i].stat,STAT_DISP);
            /*
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
                
                regAva(cont, port,i,ava);  // adicionar indice
            }
            */

            printf("\n\tValor do equipamento: ");
            port[i].valuequi = lerFloat(MAXX,MAXIMUS);

            port[i].quantReq = 0;
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
// por alterar
void dadosEstatisticos(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req){      //funcao so e acionada se houverem pcs
    int opcao, quant = 0, i,aux1,aux3;
    int numerodeMultas=0, auxdata=0,referencia = -1,*indicereqderef,*confindice,numdemin=0,u=-1;
    int quantEst = 0, quantDoce = 0, quantTec = 0;
    float atalmedia,totalMultas=0,percentagem;
    char processador[3];
    DATa base;
    base.dia = 1;
    base.mes = 1;
    base.ano = 2010;
    indicereqderef=NULL;
    confindice = indicereqderef;

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
        printf("A percentagem de processadores %s e %.1f%%.\n", processador, percentagem);
        break;
    case 2:
        for(aux1 = 0; aux1 < (*cont).totalderequisefet; aux1++){
                if(req[aux1].finee > 0){
                    totalMultas += req[aux1].finee;
                    numerodeMultas++;
                }
        }
        atalmedia = (float)totalMultas/numerodeMultas;
        printf("\n\tO custo media de cada multa e %f.",atalmedia);
        break;
    case 3:                                     // ainda nao terminado!!!! /////
        if( (cont->totalderequisefet) == 0){
            printf("\nAinda nao foram realizadas requisicoes.\n");
        }
        else{
            
            for(i=0; i < (cont->totalderequisefet); i++){

                    if(strcmp(TIPO_ESTUD, req[i].typeut) == 0){
                        quantEst ++;
                    }
                    if(strcmp(TIPO_DOCE, req[i].typeut) == 0){
                        quantDoce ++;
                    }
                    if(strcmp(TIPO_ADM, req[i].typeut) == 0){
                        quantTec ++;
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
        if(cont->totalderequisefet!=0){      //ids possui ids de pcs já  registados e devolvidos
            for(aux3 = 0;aux3<cont->totalderequisefet;aux3++){
                if(strcmp(req[aux3].statreq,STAT_CONC)){
                    auxdata = subtrairDatas(base,req[aux3].devol);
                    if(auxdata > referencia){
                        referencia = auxdata;
                    }
                }
            }
            for(aux3 = 0;aux3<cont->totalderequisefet;aux3++){
                if(strcmp(req[aux3].statreq,STAT_CONC)){
                    auxdata = subtrairDatas(base,req[aux3].devol);
                    if(auxdata == referencia){
                        numdemin ++;
                        u++;
                        indicereqderef = realloc(indicereqderef,(numdemin)*sizeof(int));
                        if(indicereqderef == NULL){
                            printf("\nErro de memoria!\n");
                        }
                        else{
                            indicereqderef[u]=aux3;
                        }
                        
                    }
                }
            }
            printf("\nA(s) ultima(s) requisicao(coes) é(sao):");
            for(aux3 = u; aux3 >=0;aux3--){
                printf("\nId:%d\n\t\tDia de devolucao: %d - %d - %d",req[indicereqderef[aux3]].portid,req[indicereqderef[aux3]].devol.dia,req[indicereqderef[aux3]].devol.mes,req[indicereqderef[aux3]].devol.ano);
            }
        }
        break;
    default:
        printf("\n\n\n\n");
    }
    
}

//________________________________________________________________________________________________________________________________________________________________
void gravarFicheiroBinario(CONTADOREs cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava){
    FILE *fc,*fp,*fa;
    //ficheiro contadores, ficheiro portateis
    int confirmacao = 1;
    char continuar;
    if(cont.portatexist == 0){
        printf("\nNão há registo(gravar nada), pretende continuar?(S/N) ");
        do{
            continuar = getchar();
            continuar = toupper(continuar);
        }while(continuar != 'S' && continuar != 'N');
        switch (continuar){

        case 'S':
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
        }
        fclose(fc);

        fp = fopen("portateis.dat", "wb");
        if(fp == NULL){
            printf("\nErro ao abrir o ficheiro!\n");
        }
        else{
            fwrite(port,sizeof(PORTATIl),cont.portatexist,fp);
            fwrite(req,sizeof(REQUi),cont.totalderequisefet,fp);
        }
        fclose(fp);

        fa = fopen("avarias.dat","wb");
        if(fa == NULL){
            printf("\n\nErro ao abrir o ficheiro!\n");
        }
        else{
            fwrite(ava,sizeof(AVARIAs),cont.totaldeavarias,fa);
        }
        fclose(fa);
    }
}

void lerFicheiroBinario(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req, AVARIAs *ava){
    FILE *fc,*fp,*fa;
    REQUi *talvezcorramal; // talvez corra mal, então guarda-se o valor para ser reposto
    talvezcorramal = req;
    AVARIAs *talvezcorramalsim; // talvez corra mal, se sim entao guardamos o valor na variavel para colocar de novo na ava
    talvezcorramalsim = ava;
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
            printf("\n\tNao e possivel retirar do ficheiro a informacao.\n");
        }
        else{
            req = realloc(req,(cont->totalderequisefet)*sizeof(REQUi));
            if(req == NULL){
                printf("\n\tErro de memoria!\n");
                req = talvezcorramal;
                problem = 'N';
            }
            ava = realloc(ava,(cont->totaldeavarias)*sizeof(AVARIAs));
            if(ava == NULL){
                printf("\n\tErro de memoria!\n");
                ava = talvezcorramalsim;
                problem = 'N';
            }
            if(problem == 'N'){
                printf("\n\tNao e possivel erro memoria.\n");
            }
            else{
                fread(port,sizeof(PORTATIl),cont->portatexist,fp);
                fread(req,sizeof(REQUi),cont->totalderequisefet,fp);

            }
        }
        
    }
    fclose(fp);
    if(problem != 'O'&& problem != 'N'){
        fa = fopen("avarias.dat","wb");
        if(fa == NULL){
            printf("\n\nErro ao abrir o ficheiro!\n");
        }
        else{
            fread(ava,sizeof(AVARIAs),cont->totaldeavarias,fa);
        }
        fclose(fa);
    }
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

int lerUtente(CONTADOREs *cont, PORTATIl port[MAXX],REQUi *req){
    int i, ut=0,u=0;
    char conf, confdoconf;
    ut = lerInteiro(UM,MAXIMUS);
    for (i=0; i<(*cont).totalderequisefet; i++){
            if( ut == req[i].numutent && strcmp(req[i].statreq,STAT_ATIV)==0){
                printf("\nO utente com o numero %d, ja tem uma requisicao ativa!",req[i].numutent);
                
                i = (*cont).totalderequisefet;
                printf("\n\tDeseja continuar com o registo com este numero?(S/N)");
                do{
                    conf = getchar();
                    conf = toupper(conf);
                }while(conf != 'S'&& conf != 'N');
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

int procurarReq(CONTADOREs *cont, PORTATIl port[MAXX],REQUi *req){
    int i, cod = -1, u;
    char code[NMAXX];
    lerString(code, NMAXX);
    for (i=0; i < (*cont).totalderequisefet; i++){
        if(strcmp(req[i].requiscode, code)==0){
            cod = i;

            i = (*cont).totalderequisefet;
        }
    }

    return cod; //devolve indice da requesicao
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

DATa sumD(DATa d1, int d){
    int aux,aux1,aux2,aux3;
    DATa data;
    switch(d1.mes){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
            aux = d1.dia+7;
            aux1 = aux -31;
            if(aux1>0){
                data.mes = d1.mes +1;
                data.dia = aux1;
                data.ano = d1.ano;
            }
            else{
                data.mes = d1.mes;
                data.dia = aux,
                data.ano = d1.ano;
            }
            break;
        case 12:
            aux = d1.dia+7;
            aux1 = aux -31;
            if(aux1 > 0){
                data.mes = 1;
                data.dia = aux1;
                data.ano = d1.ano++;
            }
            else{
                data.dia = aux;
                data.mes = d1.mes;
                data.ano = d1.ano;
            }
            break;
        case 2:
            if((d1.ano%400==0) || (d1.ano%4==0 && d1.ano%100!=0)){
                aux =d1.dia+7 ;
                aux1 = aux -29;
                if(aux1 >0){
                    data.mes = d1.mes++;
                    data.dia = aux1;
                    data.ano =d1.ano;
                }
                else{
                    data.mes = d1.mes;
                    data.dia = aux;
                    data.ano = d1.ano;
                }
            }
            else{
                aux = d1.dia + 7;
                aux1 = aux -28;
                if(aux1 > 0){
                    data.mes = d1.mes++;
                    data.dia = aux1;
                    data.ano = d1.ano;
                }
                else{
                    data.mes = d1.mes;
                    data.dia = aux;
                    data.ano = d1.ano;
                }
            }
            break;

        
        default:
            aux = d1.dia+7;
            aux1 = aux -30;
            if(aux1>0){
                data.mes = d1.mes +1;
                data.dia = aux1;
                data.ano = d1.ano;
            }
            else{
                data.mes = d1.mes;
                data.dia = aux,
                data.ano = d1.ano;
            }
    }
    return data;
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
