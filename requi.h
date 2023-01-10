
#ifndef REQUI_INCLUDED
#define REQUI_INCLUDED

#include "constantes.h"

void lePortate(CONTADOREs *cont, PORTATIl port2[MAXX], REQUi *req);
void insertPCs(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req,AVARIAs *ava);
void dadosEstatisticos(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);
int procurarReq(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);
void regRq(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);
REQUi *aumentarReq(CONTADOREs *cont, REQUi *req,int *confirm);
void listaReq(CONTADOREs *cont, PORTATIl port[MAXX], REQUi *req);

#endif // REQUI_INCLUDED
