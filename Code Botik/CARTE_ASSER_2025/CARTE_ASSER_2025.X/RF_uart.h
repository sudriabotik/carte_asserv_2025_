/* 
 * File:   RF_uart.h
 * Author: Tankin
 *
 * Created on 2 juillet 2018, 15:05
 */
/******************************************************************************/
/************ Declaration de la trame RF ***************************/
/******************************************************************************/
/******************************************************************************/
/*** La trame RF se décompose en 8 paties dans l'ordre suivant :            ***/
/***                                                                        ***/
/*** 1) Trame de début              2 octet                                 ***/
/*** 2) ID Source                   1 octet                                 ***/
/*** 3) ID Destinataire             1 octet                                 ***/
/*** 4) Objet                       1 octet                                 ***/
/*** 5) Taille                      1 octet                                 ***/
/*** 6) Données                     1 à 8 octet(s)                          ***/
/*** 7) Checksum                    1 octet                                 ***/
/*** 8) Trame de fin                1 octet                                 ***/
/******************************************************************************/
/******************************************************************************/

#ifndef RF_UART_H
#define	RF_UART_H

#ifdef MODULE_RF

/** D E F I N E S ****************************************/
//type de communication RF
#define AvecACK
#define AvecWatchdog
#define RF_AVEC_INTERRUPTION

//Mode de test avec clignotement de LED
//#define MODE_TEST_RF //ne fonctionne pas sans ?
//#define MODE_TEST_RF_ENVOI
//#define MODE_TEST_RF2
//#define MODE_TEST_RF_ACK

//adresse des machine sur le réseau RF
#define ID_GROS_ROBOT       1
#define ID_PETIT_ROBOT      2
#define ID_BALISE           3
#define ID_PC               4

#define ID_MIN              ID_GROS_ROBOT
#define ID_MAX              ID_PC

//adresse du porteur du code
#ifdef PETIT_ROBOT
#define MON_ID          ID_PETIT_ROBOT       //ATTENTION ERR BATEAU
#endif
#ifdef GROS_ROBOT
#define MON_ID          ID_GROS_ROBOT
#endif

//octet envoyé à chaque débbut ou fin de message envoyé pour faciliter le décodage
#define DEBUT_TRAME     0b00100100      //$
#define FIN_TRAME       0b00100011      //#

#define OBJET_MIN       ERR
#define OBJET_MAX       CHAINE_PERSONNEL

/** S T R U C T U R E S ****************************************/

//Structure qui rassemble les informations à transmettre par RF
typedef struct
{
    uint8_t IDDestinataire; //adresse de la machine destinataire
    uint8_t objet;          //nom de l'élément à envoyer (cf enum _Objet)
    uint8_t taille;         //nombre d'octet de la variable à envoyer
    uint8_t data[8];        //décomposition en octets de la variable à envoyer
}_emissionRF;

//Structure qui rassemble les informations brutes d'une communication RF brute reçues
typedef struct
{
    volatile _Bool libre             : 1; //La structure est en cours de modification
    uint8_t indice;              //pointe vers l'étape actuel de la trame, à quoi correspond l'octet reçu
    uint8_t IDSource;           //adresse de la machine qui viens d'envoyer le message
    uint8_t objet;              //nom de l'élément reçu (cf enum _Objet)
    uint8_t taille;             //nombre d'octet de la variable reçu
    uint8_t data[8];            //suite d'octet(s) reçu correspondant à une valeur de variable
    uint8_t checksum;           //checksum du message reçu (cf fonction checksumEmi() et checksumRec())
}_receptionRF;

//Structure qui stocke les variables reçues avec un flag 'la variable est reçu' pour chaque var
typedef struct
{
    volatile _Bool ACK :1;              //message de bien recu (ACKnoledge)
    
    _Bool flag_X_PETIT_ROBOT :1;        //=1 quand la coordonné X du petit robot peut etre lue
    double X_PETIT_ROBOT;               //coordonné X du petit robot
    
    _Bool flag_Y_PETIT_ROBOT :1;        //=1 quand la coordonné Y du petit robot peut etre lue
    double Y_PETIT_ROBOT;               //coordonné Y du petit robot
    
    _Bool flag_X_GROS_ROBOT :1;        //=1 quand la coordonné X du gros robot peut etre lue
    double X_GROS_ROBOT;               //coordonné X du gros robot
    
    _Bool flag_Y_GROS_ROBOT :1;        //=1 quand la coordonné Y du gros robot peut etre lue
    double Y_GROS_ROBOT;               //coordonné Y du gros robot
    
    _Bool TOP_DEPART :1;                //Signal pour confirmer les JACKs
    
    _Bool flag_MESSAGE_PERSONNEL :1;    //=1 quand le message personnel peut être lue
    uint64_t MESSAGE_PERSONNEL;           //Message personnalisé par le 3e argument de la fonction envoie()
    
    _Bool flag_CHAINE_PERSONNEL :1;     //=1 quand la chine personnel peut être lue
    char CHAINE_PERSONNEL[8];               //Chaine de caractère qui s'envoi avec la fonction envoieChainePerso
}_infoRF;

//Structure qui rassemble les octets à transmettre par RF par la fonction envoiSurInterruption()
typedef struct
{
    uint8_t trame[16];                  //trame d'octets à envoyer
    uint8_t taille;                     //taille de la trame d'octets (nombre d'octet utile dans trame[16])
    volatile _Bool trameAEnvoyer : 1;   //=1 quand une trame doit être envoyé
    uint8_t watchdog;                   //compteur d'envoi, au dela de 100 envoi, on s'arret d'envoyé
}_trameRF;


/**E N U M S **********************************/
//Objet déterminant ce qui est envoyé/reçu par RF (cf fonction envoie(...))
typedef enum
{
    ERR=0,          //Le message précedent est éroné (non implémenté)
    ACK,            //Bien reçu le message précedent
    PING_RF,        //Demande d'ACK
    DEMANDE,        //Demande d'une variable (est utilisé automatiquement lors de l'appel de la fonction demande)
    TOP_DEPART,     //Baisse le flag TOP_DEPART du destinataire
    X_PETIT_ROBOT,  //Envoie la coordoné X du petit robot
    Y_PETIT_ROBOT,  //Envoie la coordoné Y du petit robot
    X_GROS_ROBOT,   //Envoie la coordoné X du gros robot
    Y_GROS_ROBOT,   //Envoie la coordoné Y du gros robot     
    PERSONNEL,      //objet pour envoyer un message personalisé avec le 3e argument de la fonction envoie()
    CHAINE_PERSONNEL,
    SERIALUS
}_Objet;

//déjà défini plus haut
//#define OBJET_MIN    ERR
//#define OBJET_MAX   CHAINE_PERSO

/** P R O T O T Y P E S **********************************/


/**
 * @brief	: Fonction permettant d'envoyer le caractere A sur la liaison serie
 */
//void envoieASCII();

/**
 * @brief	: Fonction permettant de recevoir le caractere A sur la liaison serie
 * @param	: octet		: octet recu par l'interruption UART1
 */
void receptionASCII(uint8_t buf);

/** Fonction initialisation **********************************/
/**
 * @brief	: initialise les flags de réception (infoRF, receptionRF et trameRF)
 */
void initRF();

/** Fonction checksum**********************************/

/**
 * @brief	: Fonction qui calcul un checksum par adition de objet et data[] de 
 *              la structure _emissionRF
 * @return  : renvoie la somme
 */
uint8_t checksumEmi();

/**
 * @brief	: Fonction qui calcul un checksum par adition de objet et data[] de 
 *              la structure _receptionRF
 * @return  : renvoie la somme
 */
uint8_t checksumRec();

/** fonction d'emission **********************************/

/**
 * @brief	: Fonction qui envoie une variable qui sera stocker dans la structure infoRF
 * @param	: objet		:  nom de l'élement à envoyer (liste d'objet : enum _Objet) 
 * @param   : IDDestinataire : nom du destinataire (liste de destinataire : #define dans ce fichier)
 * @param   : messagePerso : Valeur à transmettre avec l'objet PERSONNEL, avec les autres objet la valeur n'est pas prise en compte
 */
void envoie(uint8_t objet,uint8_t IDDestinataire,uint64_t messagePerso);

/**
 * @brief	: Fonction qui replie le champ data de la struture emissionRF
 *              Décompose les variables de plus de 1 octet en plusieurs octet
 * @param	: info		:  variable à convertir et stocker
 */
void completeDataEmi(unsigned long long info);

/**
 * @brief	: Fonction qui crée la trame d'octets à transmettre à partir de la structure emissionRF
 */
void ConstruitTrame();

/** fonction de  réception **********************************/

/**
 * @brief	: Fonction appelé lors de l'interruption de réception UART1 (réception d'un octet).
 *              Stocke les données recues dans la structure receptioinRF
 * @param   : octet : 8 bits recus sur la liaison UART1
 */
void recoitOctet(uint8_t octet);

/**
 * @brief	: Fonction qui vérifie le checksum
 *              envoie un ACK (acknoledge=bien recu) si le checksum est bon et que le message recu n'est pas un checksum
 *              met le flag libre (prêt à recevoir) à 1 sinon
 */
void verifTame();

/**
 * @brief	: Fonction qui stocke dans la structure infoRF la variable recu selon l'objet puis met le flag libre à 1
 */
void traitementTrame();

/**
 * @brief	: assemble les octets recus dans la structure receptionRF.data pour reformer la valeur
 * @return   : renvoie la valeur des octets recomposés
 */
unsigned long long convertitVarDouble();

/**
 * @brief	: demande au destinataire d'utiliser la fonction envoie() avec l'objet passé en premier argument et le demandeur comme destinataire
 * @param   : objet : élément demandé parmis l'énumération _Objet
 * @param   : IDDestinataire : nom du destinataire (liste de destinataire : #define dans ce fichier)
 */
void demande(uint8_t objet, uint8_t IDDestinataire);

/**
 * @brief	: Fonction qui envoie une chaine de 8 caractère qui sera stocker dans la structure infoRF.CHAINE_PERSONNEL
 * @param   : IDDestinataire : nom du destinataire (liste de destinataire : #define dans ce fichier)
 * @param	: chainePerso :  chaine de char à transmettre
 */
void envoieChainePerso(uint8_t IDDestinataire,char* chainePerso);

/**
 * @brief	: envoi la trame stocker dans la structure trameRF
 *              l'envoi se fait tout les 100 ms avec le timer _T4Interrupt
 *              la fonction est appelé par le timer et si trameRF.trameAEnvoyer==1 alors la trame est envoyée
 */
void envoieRFSurInterruption();

/*
 * @brief 
 */

bool read_RF_TOP_DEPART();


/** Fonction de test**********************************/

void testRFEnvoyeur();
void testRFReceveur();

void debugEnvoyeur();
void debugReceveur();

void testRapiditeEnvoyeur();
void testRapiditeReceveur();

#endif /* MODULE_RF */

#endif	/* RF_UART_H */

