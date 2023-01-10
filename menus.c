#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "constantes.h"
#include "leituraemais.h"
#include "avarias.h"
#include "menus.h"
#include "requi.h"



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
