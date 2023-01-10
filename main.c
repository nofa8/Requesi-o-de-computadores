#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "menus.h"
#include "constantes.h"
#include "leituraemais.h"
#include "avarias.h"
#include "requi.h"




int main()
{
    REQUi *req;
    AVARIAs *ava;
    req = malloc(sizeof(REQUi)*1);
    ava = malloc(sizeof(AVARIAs)*1);
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
                        for(aux1 = (oscontadores.totalderequisefet-1);aux1>=0; aux1--){
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
                                    for(aux = 0; aux < (strlen(req[pc].local)); aux++){
                                        req[pc].local[aux] = tolower(req[pc].local[aux]);
                                    }
                                    if(strcmp(CAMPUS1 , req[pc].local)!=0 && strcmp(CAMPUS2, req[pc].local)!=0 && strcmp(CAMPUS5, req[pc].local)!=0 && strcmp(RESID, req[pc].local)!=0 ){
                                        printf("\nLocalizacao invalida (Campus1, Campus2, Campus5 ou Residencias). Insira novamente: ");
                                    }
                                }while(strcmp(CAMPUS1 , req[pc].local)!=0 && strcmp(CAMPUS2, req[pc].local)!=0 && strcmp(CAMPUS5, req[pc].local)!=0 && strcmp(RESID, req[pc].local)!=0 );
                                oscontadores.requisativas--;
                                if(req[pc].prazreal > req[pc].numpraz){
                                    //10€ por dia
                                    req[pc].finee = 10*(req[pc].prazreal - req[pc].numpraz);
                                    printf("\n\tO valor a pagar e %f€.\n",req[pc].finee);
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


