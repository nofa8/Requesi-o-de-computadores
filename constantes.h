#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED


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
#endif