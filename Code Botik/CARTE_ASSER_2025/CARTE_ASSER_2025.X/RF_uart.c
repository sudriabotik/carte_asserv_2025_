/******************************************************************************/
/************** Carte principale Robot 1 : DSPIC33FJ128MC804*******************/
/******************************************************************************/
/* Fichier 	: RF_uart.c
 * Auteur  	: Tankin
 * Revision	: 1.0
 * Date		: 02/07/2018
 *******************************************************************************
 *
 *
 ******************************************************************************/

#include "system.h"

#ifdef MODULE_RF

/******************************************************************************/
/************ Declaration de connexion du module RF ***************************/
/******************************************************************************/
/******************************************************************************/
/*** Le module RF utilisé est le eRIC4-BOB                                  ***/
/***                                                                        ***/
/*** Les connexions de la carte strat (uart1) vers le module RF à faire     ***/
/*** sont :                                                                 ***/
/*** -> le RX vers le RX (blanc)                                            ***/
/*** -> le TX vers le TX (noir)                                             ***/
/*** -> le 3,3V vers le 3,3V (marron)                                       ***/
/*** -> la masse vers la masse (bleu)                                       ***/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/*************************** Variables Globales *******************************/
/******************************************************************************/
_receptionRF receptionRF;
_emissionRF emissionRF;
_infoRF infoRF;
_trameRF trameRF;
/******************************************************************************/
/*************************** FONCTIONS INITS **********************************/
/******************************************************************************/
void initRF(){
    //InitUART(UART_RF,19200); //est fait dans init_system()
    receptionRF.libre=1;
    
    infoRF.ACK=0;
    infoRF.TOP_DEPART=0;
    infoRF.flag_X_PETIT_ROBOT=0;
    infoRF.flag_Y_PETIT_ROBOT=0;
    infoRF.flag_X_GROS_ROBOT=0;
    infoRF.flag_Y_GROS_ROBOT=0;
    infoRF.flag_MESSAGE_PERSONNEL=0;
    infoRF.flag_CHAINE_PERSONNEL=0;
    
    trameRF.trameAEnvoyer=0;
    trameRF.watchdog=0;
}

/******************************************************************************/
/***************** Fonction de communication RF UART **************************/
/******************************************************************************/
void receptionASCII(uint8_t buf){
    CAPTEUR3=1;
    delay_ms(100);
    CAPTEUR3=0;
    delay_ms(500);
    
    if (buf==0b01000001){
        //printf("A");
        //printf("A");
    }else if(buf=='D'){
        //printf("B");
        CAPTEUR3=1;
        //_ETAT_ADV_AVANT_C=0;
        delay_ms(500);
        CAPTEUR3=0;
    }else if(buf=='B'){
        //printf("B");
    }else{
        //printf("autre");
        //printf("autre");
    }
}
void testRFEnvoyeur(){
    //*** *** *** déconmmenter la fonction à tester
    
    //receptionRF.indice=0;
    //envoi d'une lettre
    //PutcUART(UART_RF, 'D'); //non interprété par la réception
    
    //envoi du signal de teop départ
    //envoie(TOP_DEPART,ID_GROS_ROBOT,0);
    
    //envoi d'une coordonée
    //envoie(X_PETIT_ROBOT,ID_GROS_ROBOT,0);
    
    //demande une coordonnée
    //demande(X_PETIT_ROBOT,ID_GROS_ROBOT);
    
    //message personnalisé
    //envoie(PERSONNEL,ID_GROS_ROBOT,125);
    
    //demande personalisé
    //demande(PERSONNEL,ID_GROS_ROBOT);
    
    while(1){
#ifdef MODE_TEST_RF_ENVOI
        CAPTEUR3=1;
        delay_ms(100);
        CAPTEUR3=0;
#endif
        //envoie(ACK,ID_GROS_ROBOT,0);
        //envoie(TOP_DEPART,ID_GROS_ROBOT,0);
        //envoie(X_PETIT_ROBOT,ID_GROS_ROBOT,0);
        //envoie(PERSONNEL,ID_GROS_ROBOT,125);
        //demande(X_PETIT_ROBOT,ID_GROS_ROBOT);
        //demande(PERSONNEL,ID_GROS_ROBOT);
        uint32_t j=0;
        uint8_t i;
        for(i=0;i<7;i++){
            j=0;
            while((j++)<0xFFFFD); // 0,5s
            j=0;
            while((j++)<0xFFFFD); // 0,5s
        }
        //attendre(1000);
        
        //while(1);
    }
}
void testRFReceveur(){
    //rien à faire car les intérruptions se chargent d'appeler la fonction récepetionASCII() ou recoitOctet()
    //receptionRF.indice=0;
    infoRF.MESSAGE_PERSONNEL=0;
    CAPTEUR3=1;
    delay_ms(1000);
    CAPTEUR3=0;
    delay_ms(300);
    CAPTEUR3=1;
    delay_ms(300);
    CAPTEUR3=0;
    //infoRF.X_PETIT_ROBOT=0;
    
    
    
    while(1){
        //delay_ms(100);
        attendre(100);
    }
}


void envoie(uint8_t objet,uint8_t IDDestinataire,uint64_t messagePerso){
    if(ID_MIN<=IDDestinataire && IDDestinataire<=ID_MAX){
        emissionRF.IDDestinataire=IDDestinataire;
        emissionRF.objet=objet;
        switch (objet) {
            case X_PETIT_ROBOT :
                emissionRF.taille=8;            //longueur de la variable à transmettre (bytes)
                completeDataEmi(X.actuelle);    //variable à transmettre
                //completeDataEmi(0x1122334455667788); //pour tester
                //completeDataEmi(284564219); //pour tester
                break;
            case Y_PETIT_ROBOT :
                emissionRF.taille=8;            //longueur de la variable à transmettre (bytes)
                completeDataEmi(Y.actuelle);    //variable à transmettre
                break;
            case X_GROS_ROBOT :
                emissionRF.taille=8;            //longueur de la variable à transmettre (bytes)
                completeDataEmi(X.actuelle);    //variable à transmettre
                break;
            case Y_GROS_ROBOT :
                emissionRF.taille=8;            //longueur de la variable à transmettre (bytes)
                completeDataEmi(Y.actuelle);    //variable à transmettre
                break;
            case TOP_DEPART :
                emissionRF.taille=1;
                completeDataEmi(0b00011100);
                break;
            case ACK :
                emissionRF.taille=1;
                completeDataEmi(0b00011100);
                break;
            case PERSONNEL :
                emissionRF.taille=1;
                completeDataEmi(messagePerso);
                break;
            case CHAINE_PERSONNEL :
                emissionRF.taille=8;
                uint8_t i;
                for(i=0;i<8;i++){
                    emissionRF.data[i]=infoRF.CHAINE_PERSONNEL[i];
                }
                break;
            //case à compléter selon les infos utiles à trasmettre

        }
        if(OBJET_MIN<=objet && objet<=OBJET_MAX) //si l'objet demandé existe
            ConstruitTrame();
    }
}

void envoieChainePerso(uint8_t IDDestinataire,char* chainePerso){
    emissionRF.IDDestinataire=IDDestinataire;
    emissionRF.objet=CHAINE_PERSONNEL;
    emissionRF.taille=8;
    uint8_t i;
    for(i=0;i<8;i++){
        emissionRF.data[i]=chainePerso[i];
    }
    ConstruitTrame();
}


void completeDataEmi(unsigned long long info){
    uint8_t i;
    uint8_t octet;
    for(i=0;i<emissionRF.taille;i++){
        octet=info>>(i*8);
        emissionRF.data[i]=octet;
    }
}

void ConstruitTrame(){
    trameRF.taille=8; //7 = taille des éléments autre que data
    //Trame de début
    trameRF.trame[0]=DEBUT_TRAME;
    trameRF.trame[1]=DEBUT_TRAME;
    trameRF.trame[2]=MON_ID;
    trameRF.trame[3]=emissionRF.IDDestinataire;
    trameRF.trame[4]=emissionRF.objet;
    trameRF.trame[5]=emissionRF.taille;
    uint8_t i;
    for(i=0;i<emissionRF.taille;i++){
        trameRF.trame[i+6]=emissionRF.data[i];
    }
    trameRF.taille+=emissionRF.taille; //ajoute la taille des datas à la taille de la trame
    trameRF.trame[trameRF.taille-2]= checksumEmi();//checksum
    trameRF.trame[trameRF.taille-1]=FIN_TRAME;
    
#ifdef AvecACK
#ifdef MODE_TEST_RF_ACK
    CAPTEUR3=1;
#endif
    //uint32_t j;
    if (emissionRF.objet==ACK || receptionRF.objet==DEMANDE){// /!\ si on envoie un ACK ou si on répond à une demande, on ne doit pas attendre un ACK
        PutsUART(UART_RF,trameRF.trame,trameRF.taille);
    }else if(emissionRF.objet==DEMANDE){  //si envoi d'une demande
        switch (emissionRF.data[0]){
            case X_PETIT_ROBOT :
                infoRF.flag_X_PETIT_ROBOT=0;
                break;
            case Y_PETIT_ROBOT :
                infoRF.flag_Y_PETIT_ROBOT=0;
                break;
            case X_GROS_ROBOT :
                infoRF.flag_X_GROS_ROBOT=0;
                break;
            case Y_GROS_ROBOT :
                infoRF.flag_X_GROS_ROBOT=0;
                break;
            case TOP_DEPART :
                //Ne rien faire
                break;
            case ACK : //pas bloquant
                //Ne rien faire
                break;
            case PERSONNEL :
                infoRF.flag_MESSAGE_PERSONNEL=0;
                break;
            case CHAINE_PERSONNEL :
                infoRF.flag_CHAINE_PERSONNEL=0;
                break;
        }
        if(OBJET_MIN<=emissionRF.data[0] && emissionRF.data[0]<=OBJET_MAX) //si l'objet est dans l'énumération _Objet
            trameRF.trameAEnvoyer=1;
    }else{
        infoRF.ACK=0;
#ifdef RF_AVEC_INTERRUPTION
        trameRF.trameAEnvoyer=1;
#else
        i=0;
        while(infoRF.ACK==0 && i<100){
            PutsUART(UART_RF,trame,emissionRF.taille+rallongeTaille);
            delay_ms(500);
#ifdef AvecWatchdog
            i++;
#endif

        }
#endif
    }
#ifdef MODE_TEST_RF_ACK
    CAPTEUR3=0;
#endif
#else //sans attente d'ACK
    PutsUART(UART_RF,trame,emissionRF.taille+rallongeTaille);
#endif
}

uint8_t checksumEmi(){
    uint8_t checksum=emissionRF.objet;
    uint8_t i;
    for(i=0;i<emissionRF.taille;i++){
        checksum = checksum | emissionRF.data[i];
    }
    return checksum;
}

uint8_t checksumRec(){
    uint8_t checksum=receptionRF.objet;
    uint8_t i;
    for(i=0;i<receptionRF.taille;i++){
        checksum = checksum | receptionRF.data[i];
    }
    return checksum;
}

void recoitOctet(uint8_t octet){
    if(octet==DEBUT_TRAME && receptionRF.libre==1){
        receptionRF.indice=-1;
        receptionRF.libre=0;        
    }
    if(receptionRF.libre==0){
        if(receptionRF.indice==0 && octet!=DEBUT_TRAME){
            receptionRF.libre=1;
        }else if(receptionRF.indice==1){
            receptionRF.IDSource=octet;
        }else if(receptionRF.indice==2 && octet!=MON_ID){ //Cette trame s'adresse-t-elle à moi
            receptionRF.libre=1;
        }else if(receptionRF.indice==3){
            receptionRF.objet=octet;
        }else if(receptionRF.indice==4){
            receptionRF.taille=octet;
        }else if(5<=receptionRF.indice && receptionRF.indice<5+receptionRF.taille){
            receptionRF.data[receptionRF.indice-5]=octet;
        }else if(receptionRF.indice==5+receptionRF.taille){
            receptionRF.checksum=octet;
        }else if(receptionRF.indice==6+receptionRF.taille){
            verifTame();
        }
    }
    receptionRF.indice++;
}

void verifTame(){
    if(receptionRF.checksum==checksumRec()){  //si le checksum est bon
        if(receptionRF.objet!=ACK && receptionRF.objet!=DEMANDE){ //si j'ai recu un ACK ou une DEMANDE, je n'envoie pas d'ACK
            envoie(ACK,receptionRF.IDSource,0);
        }
        traitementTrame();
    }else{
        //rien ou possible demande de renvoie
        receptionRF.libre=1;
    }
}
void traitementTrame(){
    uint8_t i;
#ifdef MODE_TEST_RF
    uint8_t i; //pour le clignottement de la led 3
#endif
    switch (receptionRF.objet) {
        case X_PETIT_ROBOT :
            infoRF.X_PETIT_ROBOT=convertitVarDouble();
            infoRF.flag_X_PETIT_ROBOT=1;
#ifdef MODE_TEST_RF
            //delay_ms(100);
            if(infoRF.X_PETIT_ROBOT==284564219){
                for(i=0;i<8;i++){
                    CAPTEUR3=1;
                    delay_ms(100);
                    CAPTEUR3=0;
                    delay_ms(100);
                }
            }
#endif
            break;
        case Y_PETIT_ROBOT :
            infoRF.Y_PETIT_ROBOT=convertitVarDouble();
            infoRF.flag_Y_PETIT_ROBOT=1;
            break;
        case X_GROS_ROBOT :
            infoRF.X_GROS_ROBOT=convertitVarDouble();
            infoRF.flag_X_GROS_ROBOT=1;
            break;
        case Y_GROS_ROBOT :
            infoRF.Y_GROS_ROBOT=convertitVarDouble();
            infoRF.flag_Y_GROS_ROBOT=1;
            break;
        case TOP_DEPART :
            infoRF.TOP_DEPART=1;
#ifdef MODE_TEST_RF2
            if(convertitVarDouble()==0b00011100)//pour tester si convertitVarDouble fonctionne
            CAPTEUR3=1;
            delay_ms(1000);
            CAPTEUR3=0;
#endif
            break;
        case ACK :
            infoRF.ACK=1;
#ifdef MODE_TEST_RF_ACK
            if(convertitVarDouble()==0b00011100)//pour tester si convertitVarDouble fonctionne
            CAPTEUR3=1;
            delay_ms(500);
            CAPTEUR3=0;
#endif
            break;
        case DEMANDE :
            envoie(convertitVarDouble(),receptionRF.IDSource,infoRF.MESSAGE_PERSONNEL);
            break;
        case PERSONNEL :
            infoRF.MESSAGE_PERSONNEL=convertitVarDouble();
            infoRF.flag_MESSAGE_PERSONNEL=1;
#ifdef MODE_TEST_RF2
            if(infoRF.MESSAGE_PERSONNEL==125){
                for(i=0;i<4;i++){
                    CAPTEUR3=1;
                    delay_ms(200);
                    CAPTEUR3=0;
                    delay_ms(100);
                }
            }
#endif
            break;
        case CHAINE_PERSONNEL :
            for(i=0;i<8;i++){
                infoRF.CHAINE_PERSONNEL[i]=receptionRF.data[i];
            }
            infoRF.flag_CHAINE_PERSONNEL=1;
            break;        
        //case à compléter selon les infos utiles à trasmettre
            
    }
    receptionRF.libre=1;
}

unsigned long long convertitVarDouble(){
    unsigned long long rep=0;
    uint8_t i, flagAvecPointeur=0;
    if(receptionRF.taille==9)flagAvecPointeur=1;
    for(i=0;i<receptionRF.taille-flagAvecPointeur;i++){ 
        rep+=(unsigned long long)receptionRF.data[i]<<(i*8);
    }
    return rep;
}

void demande(uint8_t objet, uint8_t IDDestinataire){
    emissionRF.IDDestinataire=IDDestinataire;
    emissionRF.objet=DEMANDE;
    emissionRF.taille=1;
    completeDataEmi(objet);
    ConstruitTrame();
}

void envoieRFSurInterruption(){
    if(trameRF.trameAEnvoyer==1){//passe à 0 dans verifTrame lorsque ACK recu
        _Bool flagBienRecu;

        if(emissionRF.objet==DEMANDE){  //si envoi d'une demande, le flag de reception est celui associé à la variable demandé

            switch (emissionRF.data[0]){
                case X_PETIT_ROBOT :
                    flagBienRecu=infoRF.flag_X_PETIT_ROBOT;
                    break;
                case Y_PETIT_ROBOT :
                    flagBienRecu=infoRF.flag_Y_PETIT_ROBOT;
                    break;
                case X_GROS_ROBOT :
                    flagBienRecu=infoRF.flag_X_GROS_ROBOT;
                    break;
                case Y_GROS_ROBOT :
                    flagBienRecu=infoRF.flag_X_GROS_ROBOT;
                    break;
                case TOP_DEPART :
                    //n'existe pas
                    break;
                case ACK :
                    //n'existe pas
                    break;
                case PERSONNEL :
                    flagBienRecu=infoRF.flag_MESSAGE_PERSONNEL;
                    break;
                case CHAINE_PERSONNEL :
                    flagBienRecu=infoRF.flag_CHAINE_PERSONNEL;
                    break;
                //case à compléter selon les infos utiles à demander

            }
        }else{//si envoi d'autre chose qu'une demande
            flagBienRecu=infoRF.ACK;
        }

        if(flagBienRecu==0){ //si l'info n'a pas été bien recu, je continue à envoyer
            PutsUART(UART_RF,trameRF.trame,trameRF.taille);
            trameRF.watchdog++;
        }else{ //l'info a bien été transmise
            trameRF.trameAEnvoyer=0;
            trameRF.watchdog=0;
        }
        if(trameRF.watchdog==100){ //on a envoyé 100 fois sans réponse
            //Qu'est ce que l'on fait? 
            //trameRF.trameAEnvoyer=0; //arrete d'envoyer
            //trameRF.watchdog=0;
            //Message de mauvaise réception???
        }
    }
}

bool read_RF_TOP_DEPART(){
    return infoRF.TOP_DEPART;
}

void debugEnvoyeur(){//fonction qui test tout les type de les messages : ACK, TOP_DEPART, X_PETIT_ROBOT, PERSONNEL, DEMANDE->PERSONNEL, CHAINE_PERSO 
    //0 flash pas de réponse
    //1 flash = envoi
    //2 flashs = bien reçu
    //3 flashs = pas reçu
    //5 longs flash = fin du test
    uint32_t j=0;
    uint8_t i;
    
    uint8_t Destinataire=ID_PC;
    
    //flash de démagage
    CAPTEUR3=1;
    delay_ms(1000);
    CAPTEUR3=0;
    delay_ms(5000);

    //envoi du signal de bonne réception
    envoie(ACK,Destinataire,0);
    
    //1 flash
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    
    for(i=0;i<10;i++){//attend 5sec
        j=0;
        while((j++)<0xFFFFD); // 0,5s
    }
    if(trameRF.trameAEnvoyer==0){//bien envoyé
        for(i=0;i<2;i++){//2 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }else{//message pas reçu (toujours en train d'envoyé)
        for(i=0;i<3;i++){//3 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }
    delay_ms(2000);
    
    //envoi du signal de top départ
    envoie(TOP_DEPART,Destinataire,0);
    
    
    PutsUART(UART_RF, (uint8_t*)"test strat numero 2\n", 20);
    
    //1 flash
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    
    for(i=0;i<10;i++){//attend 5sec
        j=0;
        while((j++)<0xFFFFD); // 0,5s
    }
    if(trameRF.trameAEnvoyer==0){//bien envoyé
        for(i=0;i<2;i++){//2 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }else{//message pas reçu (toujours en train d'envoyé)
        for(i=0;i<3;i++){//3 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }
    delay_ms(2000);
    
    //envoi d'une coordonée
    infoRF.X_PETIT_ROBOT=5;
    envoie(X_PETIT_ROBOT,Destinataire,0);
    
    //1 flash
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    
    for(i=0;i<10;i++){//attend 5sec
        j=0;
        while((j++)<0xFFFFD); // 0,5s
    }
    if(trameRF.trameAEnvoyer==0){//bien envoyé
        for(i=0;i<2;i++){//2 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }else{//message pas reçu (toujours en train d'envoyé)
        for(i=0;i<3;i++){//3 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }
    delay_ms(2000);
    
    //message personnalisé
    envoie(PERSONNEL,Destinataire,123);
    
    //1 flash
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    
    for(i=0;i<10;i++){//attend 5sec
        j=0;
        while((j++)<0xFFFFD); // 0,5s
    }
    if(trameRF.trameAEnvoyer==0){//bien envoyé
        for(i=0;i<2;i++){//2 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }else{//message pas reçu (toujours en train d'envoyé)
        for(i=0;i<3;i++){//3 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }
    delay_ms(2000);
    
    //demande une coordonnée
    demande(PERSONNEL,Destinataire);
    
    //1 flash
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    
    for(i=0;i<10;i++){//attend 5sec
        j=0;
        while((j++)<0xFFFFD); // 0,5s
    }
    if(infoRF.MESSAGE_PERSONNEL==42){//bien reçu la valeur demandé
        for(i=0;i<2;i++){//2 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }else{//message pas reçu
        for(i=0;i<3;i++){//3 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }
    delay_ms(2000);
    
    //envoi de la chaine personnel
    char chaine[8];
    chaine[0]='C';
    chaine[1]='o';
    chaine[2]='u';
    chaine[3]='c';
    chaine[4]='o';
    chaine[5]='u';
    chaine[6]='\0';
    envoieChainePerso(Destinataire,chaine);
    
    //1 flash
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    
    for(i=0;i<10;i++){//attend 5sec
        j=0;
        while((j++)<0xFFFFD); // 0,5s
    }
    if(infoRF.MESSAGE_PERSONNEL==42){//bien reçu la valeur demandé
        for(i=0;i<2;i++){//2 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }else{//message pas reçu
        for(i=0;i<3;i++){//3 flashs
            CAPTEUR3=1;
            delay_ms(200);
            CAPTEUR3=0;
            delay_ms(200);
        }
    }
    delay_ms(2000);
    
    //fin du test
    for(i=0;i<5;i++){//5 flashs
        CAPTEUR3=1;
        delay_ms(1000);
        CAPTEUR3=0;
        delay_ms(200);
    }
    
    while(1);
}
    
void debugReceveur(){//fonction qui test tout les type de les messages : ACK, TOP_DEPART, X_PETIT_ROBOT, PERSONNEL, DEMANDE->PERSONNEL, CHAINE_PERSO
    //1 flash = bien reçu avec la bonne valeur
    //2 flashs = pas la bonne valeur
    //5 longs flashs = fin du test
    
    uint8_t i;
    
    //flash de démagage
    CAPTEUR3=1;
    delay_ms(1000);
    CAPTEUR3=0;
    delay_ms(200);
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(2000);
    
    while(infoRF.ACK==0); //attend l'envoi d'un ACK
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    
    while(infoRF.TOP_DEPART==0); //attend l'envoi du top départ
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    
    infoRF.X_PETIT_ROBOT=42;
    while(infoRF.flag_X_PETIT_ROBOT==0); //attend l'envoi X_PETIT_ROBOT=position initiale du robot
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    if(infoRF.X_PETIT_ROBOT!=0){
        CAPTEUR3=1;
        delay_ms(200);
        CAPTEUR3=0;
        delay_ms(200);
    }
    
    while(infoRF.flag_MESSAGE_PERSONNEL==0); //attend l'envoi de Message perso=123
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    if(infoRF.MESSAGE_PERSONNEL!=123){
        CAPTEUR3=1;
        delay_ms(200);
        CAPTEUR3=0;
        delay_ms(200);
    }
    
    infoRF.MESSAGE_PERSONNEL=42;
    while(receptionRF.libre==1); //attend demande PERSONNEL
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    
    while(infoRF.flag_CHAINE_PERSONNEL==0); //attend l'envoi de chaine perso=Coucou
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(200);
    if(infoRF.CHAINE_PERSONNEL[0]!='C' || infoRF.CHAINE_PERSONNEL[1]!='o'){
        CAPTEUR3=1;
        delay_ms(200);
        CAPTEUR3=0;
        delay_ms(200);
    }
    
    //fin du test
    delay_ms(2000);
    for(i=0;i<5;i++){//5 flashs long
        CAPTEUR3=1;
        delay_ms(1000);
        CAPTEUR3=0;
        delay_ms(200);
    }
    
    while(1);
}

void testRapiditeEnvoyeur(){
    //flash de démagage
    CAPTEUR3=1;
    delay_ms(1000);
    CAPTEUR3=0;
    delay_ms(5000);
    
    uint32_t j;
    uint8_t i;
    for(i=0;i<100;i++){
        CAPTEUR3=1;
        envoie(PERSONNEL,ID_GROS_ROBOT,i);
        CAPTEUR3=0;
        j=0;
        while((j++)<0x7FFFD); //???s
        
    }
    CAPTEUR3=1;
    delay_ms(1000);
    CAPTEUR3=0;
    delay_ms(200);
    CAPTEUR3=1;
    delay_ms(1000);
    CAPTEUR3=0;
    while(1);
}

void testRapiditeReceveur(){
    //flash de démagage
    CAPTEUR3=1;
    delay_ms(1000);
    CAPTEUR3=0;
    delay_ms(200);
    CAPTEUR3=1;
    delay_ms(200);
    CAPTEUR3=0;
    delay_ms(2000);
    
    uint8_t i=0;
    uint64_t tableau[100];
    while(i<100){
        if(infoRF.flag_MESSAGE_PERSONNEL==1){
            tableau[i]=infoRF.MESSAGE_PERSONNEL;
            i++;
            infoRF.flag_MESSAGE_PERSONNEL=0;
        }
    }
    
    //annalyse de la réception
    bool flagToutVaBien=1;
    for(i=0;i<100;i++){
        if(tableau[i]!=i){
            flagToutVaBien=0;
            break;
        }
    }
    
    while(1){
        //bilan de la réception : 2 flashs = OK, 3 flashs = Problème
        if(flagToutVaBien==1){//suite de message recu bien dans l'ordre
            for(i=0;i<2;i++){//2 flashs
                CAPTEUR3=1;
                delay_ms(200);
                CAPTEUR3=0;
                delay_ms(200);
            }
        }else{//message pas reçu dans l'ordre
            for(i=0;i<3;i++){//3 flashs
                CAPTEUR3=1;
                delay_ms(200);
                CAPTEUR3=0;
                delay_ms(200);
            }
        }
        delay_ms(2000);
    }
    //flash de fin
    delay_ms(3000);
    CAPTEUR3=1;
    delay_ms(1000);
    CAPTEUR3=0;
    delay_ms(200);
    CAPTEUR3=1;
    delay_ms(1000);
    CAPTEUR3=0;
    while(1);
}

#endif /* MODULE_RF */
