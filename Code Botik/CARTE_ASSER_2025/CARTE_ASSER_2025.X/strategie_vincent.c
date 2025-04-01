/******************************************************************************/
/************** Carte principale Robot 1 : DSPIC33FJ128MC804*******************/
/******************************************************************************/
/* Fichier 	: srategie.c
 * Auteur  	: Quentin
 * Revision	: 1.0
 * Date		: 07 février 2015, 22:47
 *******************************************************************************
 *
 *
 ******************************************************************************/

/******************************************************************************/
/******************************** INCLUDES ************************************/
/******************************************************************************/

#include "system.h"
#include "autom.h"

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

void tour_de_table(){
    rejoindre(750, 750, MARCHE_AVANT, 100);
    cibler(2250,750,30);
    //avancer_reculer(1000, 70);
    //init_X(2000);
    rejoindre(2250, 750, MARCHE_AVANT, 100);
    cibler(2250,1250,30);
            
    rejoindre(2250, 1250, MARCHE_AVANT, 100);
    cibler(750,1250,30);
            
    rejoindre(750, 1250, MARCHE_AVANT, 100);
    cibler(750,750,30);
            
    rejoindre(750, 750, MARCHE_AVANT, 100);
    cibler(2250,750,30);
    brake();
}

// La stratégie de match
void strategie(){
// Code du gros robot
#ifdef GROS_ROBOT
    init_AX12();
    // initialisation en général
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    
    CPT_TEMPS_MATCH.actif = OFF;
    
    COULEUR = couleur_depart();
    STRATEGIE = strategie_depart(); 
   
    
    /*
    //TEST AX
    
    delay_ms(500); //On attend 0,1 seconde
    angle_AX12(5, 121, 800, SANS_ATTENTE);//poulie Droite level 1
    angle_AX12(13, 1012, 800, SANS_ATTENTE);//poulie gauche level 1
    delay_ms(500); //On attend
    angle_AX12(5, 600, 800, SANS_ATTENTE);//poulie droite level 0
    angle_AX12(13, 531, 800, SANS_ATTENTE);//poulie gauche level 0
    
    delay_ms(500); //On attend 0,1 seconde
    angle_AX12(5, 121, 800, SANS_ATTENTE);//poulie Droite level 1
    angle_AX12(13, 1012, 800, SANS_ATTENTE);//poulie gauche level 1
    delay_ms(500); //On attend
    angle_AX12(5, 600, 800, SANS_ATTENTE);//poulie droite level 0
    angle_AX12(13, 531, 800, SANS_ATTENTE);//poulie gauche level 0
    
    delay_ms(500); //On attend 0,1 seconde
    angle_AX12(5, 121, 800, SANS_ATTENTE);//poulie Droite level 1
    angle_AX12(13, 1012, 800, SANS_ATTENTE);//poulie gauche level 1
    delay_ms(500); //On attend
    angle_AX12(5, 600, 800, SANS_ATTENTE);//poulie droite level 0
    angle_AX12(13, 531, 800, SANS_ATTENTE);//poulie gauche level 0
    */
    
    
    //delay_ms(10); //On attend
    
    init_AX12();
    
    
     //calage_depart(STRATEGIE);
   // init_evitement();
    /*
    
    while(1){
        CPT_TEMPS_MATCH.actif=OFF;
        EVITEMENT_ADV.actif = OFF;
        EVITEMENT_ADV.mode = STOP;  
        avancer_reculer(100,10);
        delay_ms(10000);
        avancer_reculer(-100,10);
        delay_ms(10000);
    }
      */
        
    
    
    
    
    
    
    //*****************************STRAT*****************************
     /*
    while(1){
        
    
    if(SYS_JACK){
    
    CPT_TEMPS_MATCH.actif=ON;
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    
    
    
    
    //descendre l'ascenseur
    delay_ms(200); //On attend 0,1 seconde
    
    
    pince_ouverte();
    delay_ms(400); //On attend
    poulie_bas();
    delay_ms(200); //On attend
    rejoindre(1300,1775,MARCHE_AVANT,10);
    avancer_reculer(-100,10);
    brake();
    while(1);
    
     //HOMOLOGATION 
    //go 1er gateau
    rejoindre(2600,1775,MARCHE_AVANT,10);
    delay_ms(200);
    pince_fermee();
    delay_ms(500);
    pince_ouverte();
    delay_ms(200);
    //on tasse 
    rejoindre(2550,1775,MARCHE_AVANT,10);
    delay_ms(500); //On attend 
    pince_fermee();//on serre
    delay_ms(500); //On attend 
    poulie_haut();//on monte en l'air le gateau
    delay_ms(1000); //On attend 
    
    //2e gateau
    rejoindre(2375,1775,MARCHE_AVANT,10);
    pince_ouverte();
    delay_ms(500); 
    pince_fermee();
    delay_ms(500);
    pince_ouverte();// on tasse
    delay_ms(500);
    rejoindre(2350,1775,MARCHE_AVANT,10);
    delay_ms(500);
    pince_fermee();//on serre
    delay_ms(500);
    pince_ouverte();
    delay_ms(500);
    poulie_bas();//on stack
    delay_ms(500);
    pince_fermee();
    delay_ms(500);
 
    passe_part(2350,1775,MARCHE_AVANT, 30, DEBUT_TRAJECTOIRE);
    passe_part(2300, 800, MARCHE_AVANT, 30, MILIEU_TRAJECTOIRE);
    passe_part(2700, 800, MARCHE_AVANT, 30, FIN_TRAJECTOIRE);
    
    pince_ouverte();
    delay_ms(500); 
    pince_fermee();
     
    delay_ms(500);
    poulie_haut();
    
    
    delay_ms(500);
    calage_X(2860, 0, MARCHE_AVANT, 10);
    avancer_reculer(-45,10);
    orienter(-90,10);
    calage_Y(870, -90, MARCHE_ARRIERE, 10);
    //aspiiiiii
    
    
    //depose gateau
    delay_ms(1000);
    //rejoindre(290 5,825,MARCHE_AVANT,50);
    
    avancer_reculer(155,10);
    orienter(90,10);
    poulie_bas();
    delay_ms(500);
    pince_ouverte();//depose gateau 1
    delay_ms(100);
    angle_AX12(5, 220, 800, SANS_ATTENTE);//poulie Droite rangement 1 //220
    angle_AX12(13, 874 , 800, SANS_ATTENTE);//poulie gauche rangement 1 //874// higher a bit
    delay_ms(500);
    pince_fermee();//attraper 2emegateau
    delay_ms(500);
    avancer_reculer(-190,10);
    poulie_bas();
    delay_ms(500);
    pince_ouverte();//depose gateau 2
    delay_ms(100);
    brake();
    while(1);
    
    //bouger vers cerise 
        
    
    //rejoindre(2905,870,MARCHE_AVANT,100);
    //orienter(180,50);
    //rejoindre(1500,490,MARCHE_AVANT,100);
    //orienter(90,50);
    //calage_Y(140, 90, MARCHE_ARRIERE, 10);
    //passe_part(2350,1775,MARCHE_AVANT, 50, DEBUT_TRAJECTOIRE);
    //passe_part(2300, 800, MARCHE_AVANT, 50, MILIEU_TRAJECTOIRE);
    //passe_part(2700, 800, MARCHE_AVANT, 50, FIN_TRAJECTOIRE);
    
    
            
    
    
          
    
    
    
    
    
    
    
         // On attend la tirette
    
    
    // Code stratégie
     
    }
    
    brake(); 
    }
      */
#endif

// Code du petit robot
#ifdef PETIT_ROBOT
    COULEUR = couleur_depart();
    STRATEGIE = strategie_depart();
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    
    
    
    init_ax();
    /*
    allumer_pompinettes ();
    delay_ms(4000);
    allumer_pompes ();
    delay_ms(4000);
    init_ax();
    delay_ms(4000);
    stock_plant();
    delay_ms(2000);
    position_intermediaire_depose_jardi();
    delay_ms(2000);
    depose_plant();
    delay_ms(1000);
    
    position_intermediaire_depose_jardi();
    delay_ms(2000);
    init_ax();
    */
    
    //init_position_robot(200,200, 0.);
    
    
    
    //faire_des_tours(10);
     //calage_depart(STRATEGIE);
     //rejoindre(1600,500, MARCHE_AVANT, 100);
    
    
    
   // rejoindre(1500,0, MARCHE_AVANT, 149);
    //cibler(0,0,149);
    //avancer_reculer(1000, 70);
    //init_X(2000);
   // rejoindre(0, 0, MARCHE_AVANT, 149);
  //  cibler(1500,0,149);
   // rejoindre(1500,0, MARCHE_AVANT, 149);
    //cibler(0,0,149);
    //avancer_reculer(1000, 70);
    //init_X(2000);
   // rejoindre(0, 0, MARCHE_AVANT, 149);
 //   cibler(1500,0,149);
    //rejoindre(1500,0, MARCHE_AVANT, 149);
    
    //cibler(0,0,149);
    //avancer_reculer(1000, 70);
    //init_X(2000);
    //rejoindre(0, 0, MARCHE_AVANT, 149);
    //cibler(1500,0,149);
    //rejoindre(1500,0, MARCHE_AVANT, 149);
    //cibler(0,0,149);
    //avancer_reculer(1000, 70);
    //init_X(2000);
    //rejoindre(0, 0, MARCHE_AVANT, 149);
    //cibler(1500,0,149);
            
   
    //calage_Y(76, 90, MARCHE_ARRIERE, 10);
    //avancer_reculer(100,10) ;
    //avancer_reculer(1500,100) ; 
    /*delay_ms(3000);
    grab_cake();
    avancer_reculer(500,50);
    release_cake();
    avancer_reculer(-200,50);
    */
   
    
    brake();
    while(1);
    // initialisation en général
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    
    CPT_TEMPS_MATCH.actif = OFF;
    
    COULEUR = couleur_depart();
    STRATEGIE = strategie_depart();
    init_AX12();

        // Code stratégie

    
    
    //jack();     // On attend la tirette
    CPT_TEMPS_MATCH.actif=ON;
    

    
#endif
}


void homologation()
{   
#ifdef GROS_ROBOT
    
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    
    COULEUR = couleur_depart();
    STRATEGIE = strategie_depart();
    
    //Initialisation AX12
    init_AX12();
    //init_position_robot(140,450, 0.); //Pas utile
    
    calage_depart(STRATEGIE); //Calage
    
    while(1){
        if(SYS_JACK){
        }}
#endif

#ifdef PETIT_ROBOT
    
    
    
    COULEUR = couleur_depart();
    STRATEGIE = strategie_depart();
    
    //calage_depart(STRATEGIE);
    //while(!CAPTEUR5);
    ///while(CAPTEUR5);
    
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    
    CPT_TEMPS_MATCH.actif = OFF;
    //avancer_reculer(1000,20) ;
    //avancer_reculer(-1000,20) ;
    
    while(1);{
    //avancer_reculer(200,10) ;
    //while(1)
        //if(SYS_JACK){
            //brake();
        //}
    }
    brake();

#endif
}

//Initialise les positions des AX-12
void init_AX12(){
    #ifdef GROS_ROBOT
        //monte l'ascenseur
        //angle_AX12(AX_POULIE_DROITE, 300, 500, SANS_ATTENTE);//poulie rangement 1
        
        //poulie_haut();
        //delay_ms(1000); //On attend 1 seconde
        //angle_AX12(24, 259, 500, SANS_ATTENTE);//pince gauche rangement
        //angle_AX12(12, 755, 500, SANS_ATTENTE);//pince droite rangement
       
        //angle_AX12(22, 853, 500, SANS_ATTENTE);//aspi ferme
        
        //lancer_autom_AX12();
    #endif
    #ifdef PETIT_ROBOT
        init_ax();

    #endif
}
/*void AX12_depart(){
    #ifdef GROS_ROBOT
        //monte l'ascenseur
        angle_AX12(5, 487, 800, SANS_ATTENTE);//poulie rangement 1
        delay_ms(100); //On attend 1 seconde
        angle_AX12(24, 577, 100, SANS_ATTENTE);//pince gauche ouvert
        angle_AX12(12, 577, 100, SANS_ATTENTE);//pince droite ouvert    
    #endif
    #ifdef PETIT_ROBOT
        
        angle_AX12(11, 500, 500, SANS_ATTENTE);
        delay_ms(100);
        angle_AX12(12, 180, 500, SANS_ATTENTE);
        delay_ms(100);
        angle_AX12(13, 500, 500, SANS_ATTENTE);
        delay_ms(100);
        angle_AX12(21, 500, 500, SANS_ATTENTE);
        delay_ms(100);
        angle_AX12(22, 180, 500, SANS_ATTENTE);
        delay_ms(100);
        angle_AX12(23, 500, 500, SANS_ATTENTE);
        delay_ms(100);
        clean_des_erreurs_ax12();
        
    #endif
}*/
void pince_ouverte(){
    angle_AX12(24, 415, 200, SANS_ATTENTE);//pince gauche ouvert
    angle_AX12(12, 594, 200, SANS_ATTENTE);//pince droite ouvert
}
void pince_fermee(){
    angle_AX12(24, 500 , 200, SANS_ATTENTE);//pince gauche ferme
    angle_AX12(12, 492, 200, SANS_ATTENTE);//pince droite ferme
}
void poulie_bas(){
    angle_AX12(5, 607, 800, SANS_ATTENTE);//poulie droite level 0
    angle_AX12(13, 485, 800, SANS_ATTENTE);//poulie gauche level 0
}
void poulie_haut(){
    angle_AX12(5, 224, 800, SANS_ATTENTE);//poulie Droite rangement 1 //220
    angle_AX12(13, 870 , 800, SANS_ATTENTE);//poulie gauche rangement 1 //874
}

// Permet de caler le robot sur les bords pour connaitre sa position
void calage_depart(_enum_strategies STRATEGIE){
    //init_position_robot(1860., 2860., 180.); //utile
    
    init_position_robot(0., 0., 0.);
    #ifdef GROS_ROBOT
    calage_X(2860, 0, MARCHE_AVANT, 10);
    avancer_reculer(-200,50);
    orienter(90,50);
    calage_Y(1860, 90, MARCHE_AVANT, 10);
    avancer_reculer(-200,50); 
    rejoindre(2695,1775,MARCHE_AVANT,50);
    orienter(180,50);
    #endif

    #ifdef PETIT_ROBOT
    
    calage_X(76, 0, MARCHE_ARRIERE, 10);
    avancer_reculer(200,50);
    orienter(90,50);
    calage_Y(76, 90, MARCHE_ARRIERE, 10);
    avancer_reculer(200,50);
    //rejoindre(750,750,MARCHE_AVANT,50);
    orienter(0,50);
    
    #endif
}

/******************************************************************************/
/***************************** FONCTION STRATEGIE *****************************/
/******************************************************************************/

#ifdef GROS_ROBOT
#endif

#ifdef PETIT_ROBOT



#endif


/******************************************************************************/
/**************************** FONCTION ACTIONNEUR *****************************/
/******************************************************************************/

#ifdef GROS_ROBOT

#endif

#ifdef PETIT_ROBOT
void bras_recup_rack_int(){

    angle_AX12(11, 620, 300, SANS_ATTENTE);
    angle_AX12(12, 800, 300, SANS_ATTENTE);
    angle_AX12(13, 200, 300, SANS_ATTENTE);
    //lancer_autom_AX12();
    delay_ms(500);
    
    angle_AX12(21, 395, 300, SANS_ATTENTE);
    angle_AX12(22, 800, 300, SANS_ATTENTE);
    angle_AX12(23, 200, 300, SANS_ATTENTE);
    //lancer_autom_AX12(); 
}
void bras_recup_rack_ext(){
    angle_AX12(11, 600, 300, SANS_ATTENTE);
    angle_AX12(12, 600, 300, SANS_ATTENTE);
    angle_AX12(13, 500, 300, SANS_ATTENTE);
    //lancer_autom_AX12();
    delay_ms(500);
    
    angle_AX12(21, 400, 300, SANS_ATTENTE);
    angle_AX12(22, 600, 300, SANS_ATTENTE);
    angle_AX12(23, 500, 300, SANS_ATTENTE);
    //lancer_autom_AX12();
}

void bras_depose_ext(){
    angle_AX12(11, 800, 300, SANS_ATTENTE);
    angle_AX12(12, 700, 300, SANS_ATTENTE);
    angle_AX12(13, 400, 300, SANS_ATTENTE);
    //lancer_autom_AX12();
    delay_ms(500);
    
    angle_AX12(21, 200, 300, SANS_ATTENTE);
    angle_AX12(22, 700, 300, SANS_ATTENTE);
    angle_AX12(23, 400, 300, SANS_ATTENTE);
    
}
void bras_depose(){
    angle_AX12(6,875,200,SANS_ATTENTE);
}

#endif


//Autre
void attendre(uint32_t ms)
{
    uint32_t temp = CPT_TEMPS_MATCH.t_ms;
    while(CPT_TEMPS_MATCH.t_ms - temp < ms); 
}


