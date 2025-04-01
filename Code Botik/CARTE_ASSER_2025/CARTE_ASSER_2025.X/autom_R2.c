 /******************************************************************************/
/************** Carte principale Robot 1 : DSPIC33FJ128MC804*******************/
/******************************************************************************/
/* Fichier 	: autom.c
 * Auteur  	: Quentin
 * Revision	: 1.0
 * Date		: 01 février 2015, 17:11
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
/***************************** FONCTIONS DIVERSES *****************************/
/******************************************************************************/

void jack()
{
    while(!SYS_JACK);
    allumer_LED_AX12(TOUS_LES_AX12);
    while(SYS_JACK);
}

void allumer_pompes ()
{
    envoit_pwm(MOTEUR_X, 35);
}

void eteindre_pompes ()
{
    envoit_pwm(MOTEUR_X, 0);
}

void allumer_pompinettes(){      
    PIN_COMMANDE_POMPINETTES_TRIS2 = 0; //Make the LED pin an output
    PIN_COMMANDE_POMPINETTES = 1;  
}

void eteindre_pompinettes(){
    PIN_COMMANDE_POMPINETTES_TRIS2 = 0; //Make the LED pin an output
    PIN_COMMANDE_POMPINETTES = 0;
}
void start_turbine(){      
    PIN_COMMAND_TRIS1 = 0; //Make the LED pin an output
    PIN_COMMAND = 1;  
}

void stop_turbine(){
    PIN_COMMAND_TRIS1 = 0; //Make the LED pin an output
    PIN_COMMAND = 0;
}
//Carte non patcher LMD18200 inutilisable
//void allumer_pompinettes ()
//{
//    ALIM_MOTEUR_Y = ACTIVE;
//    envoit_pwm (SENS_MOTEUR_Y, 0);
//}

//void eteindre_pompinettes ()
//{
//    envoit_pwm(SENS_MOTEUR_Y, 0);
//}

void son_evitement (uint8_t melodie)
{/*
    commande_AX12(100, _4PARAM, WRITE_DATA, 0x29, 10);
    commande_AX12(100, _4PARAM, WRITE_DATA, 0x28, melodie);

  */}

/******************************************************************************/
/********************************  FONCTION AX12  *****************************/
/******************************************************************************/


//-------------------------------------2024-------------------------------------
//inti des AX12
void init_ax() {
    angle_AX12(AX_BRAS_Z,AX_BRAS_Z_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);   
    delay_ms(200);
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_INIT,VIT_AX_LENT,SANS_ATTENTE);
    delay_ms(200);
    angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_1ER_ROT_POS_INIT,VIT_AX_LENT,SANS_ATTENTE); 
    delay_ms(200);
    angle_AX12(AX_GRIFFE_GAUCHE_2,AX_GRIFFE_GAUCHE_2_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_DROIT_2,AX_GRIFFE_DROIT_2_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);	
    delay_ms(300);
    angle_AX12(AX_GRIFFE_GAUCHE_1,AX_GRIFFE_GAUCHE_1_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_DROIT_1,AX_GRIFFE_DROIT_1_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(200);
    angle_AX12(AX_GRIFFE_DROIT_2,AX_GRIFFE_DROIT_2_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(200);
	angle_AX12(AX_PV_GAUCHE_1,AX_PV_GAUCHE_1_POS_INIT,VIT_AX_LENT,SANS_ATTENTE);
    delay_ms(200);
	angle_AX12(AX_PV_DROIT_1,AX_PV_DROIT_1_POS_INIT,VIT_AX_LENT,SANS_ATTENTE);
    delay_ms(500);
}

void init_plantes() {
    angle_AX12(AX_BRAS_Z,AX_BRAS_Z_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);   
    delay_ms(100);
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_INIT,VIT_AX_LENT,SANS_ATTENTE);
    delay_ms(100);
    angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_1ER_ROT_POS_INIT,VIT_AX_LENT,SANS_ATTENTE); 
    delay_ms(100);
}

//fonction pour le systeme plantes:
void aspi_plantes() {
       //Activation des Pompinette
    // allumage des pompes
	allumer_pompes ();    
    start_turbine();
    // changement de position des ax12 pour preparer la dépose
    angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_1ER_ROT_POS_INIT,VIT_AX_LENT,SANS_ATTENTE);
	angle_AX12(AX_BRAS_Z,AX_BRAS_Z_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
	delay_ms(200);
}

void stock_plant(){
       
   //Activation des Pompinette
	allumer_pompinettes ();
   delay_ms(500);
   // changement de position des ax12 pour le stockage
        angle_AX12(AX_BRAS_1ER_ROT,400,1024,SANS_ATTENTE);

    delay_ms(500);
    angle_AX12(AX_BRAS_Z,AX_BRAS_Z_POS_STOCKAGE,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_STOCKAGE,VIT_AX_RAPIDE,SANS_ATTENTE);    
     angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_1ER_ROT_POS_STOCKAGE,800,SANS_ATTENTE);
	angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_STOCKAGE,VIT_AX_RAPIDE,SANS_ATTENTE);    
  
    delay_ms(800);
	
    //Désactivation des Pompes
	eteindre_pompes ();
    delay_ms(200);  
}  

void destock_plant(){
       
   //Activation des Pompes
	allumer_pompes ();
    
   // changement de position des ax12 pour aller au stockage
    angle_AX12(AX_BRAS_Z,AX_BRAS_Z_POS_STOCKAGE,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_STOCKAGE,VIT_AX_RAPIDE,SANS_ATTENTE);    
    angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_1ER_ROT_POS_STOCKAGE,800,SANS_ATTENTE);
	angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_STOCKAGE,VIT_AX_RAPIDE,SANS_ATTENTE);    
  
   //Désactivation des Pompinettes
	delay_ms(200);
	eteindre_pompinettes ();
	delay_ms(400);
}  

void depose_plant(){
   
   // changement de position des ax12 pour la dépose sur le plateau
    angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_Z_POS_DEPOSE,VIT_AX_LENT,SANS_ATTENTE);
	delay_ms(200);
	angle_AX12(AX_BRAS_Z,AX_BRAS_1ER_ROT_POS_DEPOSE,VIT_AX_RAPIDE,SANS_ATTENTE);
	delay_ms(200);
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_DEPOSE,VIT_AX_RAPIDE,SANS_ATTENTE);
	
	
   //Désactivation des Pompes
	eteindre_pompes ();
    delay_ms(200);
}

// changement de position des ax12 après la dépose dans la jardinaire
void fin_depose_plant() {
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_DEPOSE_FIN,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(200);
	angle_AX12(AX_BRAS_Z,AX_BRAS_Z_POS_DEPOSE_FIN,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(200);
    angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_Z_POS_INT_DEPOSE_JARDI,VIT_AX_LENT,SANS_ATTENTE);
    delay_ms(500);
}

void depose_jardiniere_plant(){
   
   // changement de position des ax12 pour la dépose dans la jardinaire
    angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_Z_POS_DEPOSE_JARDI,VIT_AX_LENT,SANS_ATTENTE);
	delay_ms(200);
	angle_AX12(AX_BRAS_Z,AX_BRAS_1ER_ROT_POS_DEPOSE_JARDI,VIT_AX_RAPIDE,SANS_ATTENTE);
	delay_ms(200);
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_DEPOSE_JARDI,VIT_AX_RAPIDE,SANS_ATTENTE);
	
	
   //Désactivation des Pompes
	eteindre_pompes ();
    delay_ms(200);
}


void position_intermediaire_depose_plateau(){
    // changement de position des ax12 pour preparer la dépose
    angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_Z_POS_INT_DEPOSE_PLATEAU,VIT_AX_LENT,SANS_ATTENTE);
	delay_ms(200);
	angle_AX12(AX_BRAS_Z,AX_BRAS_1ER_ROT_POS_INT_DEPOSE_PLATEAU,VIT_AX_RAPIDE,SANS_ATTENTE);
	delay_ms(200);
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_INT_DEPOSE_PLATEAU,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(500);
}

void position_intermediaire_depose_jardi(){
    // changement de position des ax12 pour preparer la dépose
    angle_AX12(AX_BRAS_1ER_ROT,AX_BRAS_Z_POS_INT_DEPOSE_JARDI,VIT_AX_LENT,SANS_ATTENTE);
	delay_ms(200);
	angle_AX12(AX_BRAS_Z,AX_BRAS_1ER_ROT_POS_INT_DEPOSE_JARDI,VIT_AX_RAPIDE,SANS_ATTENTE);
	delay_ms(200);
    angle_AX12(AX_BRAS_2EME_ROT,AX_BRAS_2EME_ROT_POS_INT_DEPOSE_JARDI,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(500);  
}

//fonction pour les griffes
void init_griffes() {
   // changement de position des ax12 pour le stockage
	angle_AX12(AX_GRIFFE_GAUCHE_2,AX_GRIFFE_GAUCHE_2_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
	angle_AX12(AX_GRIFFE_GAUCHE_2,AX_GRIFFE_GAUCHE_2_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(10);
    angle_AX12(AX_GRIFFE_DROIT_2,AX_GRIFFE_DROIT_2_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_DROIT_2,AX_GRIFFE_DROIT_2_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(300);
    angle_AX12(AX_GRIFFE_GAUCHE_1,AX_GRIFFE_GAUCHE_1_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_GAUCHE_1,AX_GRIFFE_GAUCHE_1_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(10);
    angle_AX12(AX_GRIFFE_DROIT_1,AX_GRIFFE_DROIT_1_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_DROIT_1,AX_GRIFFE_DROIT_1_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(50);
}

void griffes_ouvertes() {
   // changement de position des ax12 pour le stockage
    angle_AX12(AX_GRIFFE_GAUCHE_1,AX_GRIFFE_GAUCHE_1_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_GAUCHE_1,AX_GRIFFE_GAUCHE_1_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(10);
    angle_AX12(AX_GRIFFE_DROIT_1,AX_GRIFFE_DROIT_1_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_DROIT_1,AX_GRIFFE_DROIT_1_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(100);
    angle_AX12(AX_GRIFFE_GAUCHE_2,AX_GRIFFE_GAUCHE_2_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_GAUCHE_2,AX_GRIFFE_GAUCHE_2_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(10);
    angle_AX12(AX_GRIFFE_DROIT_2,AX_GRIFFE_DROIT_2_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_DROIT_2,AX_GRIFFE_DROIT_2_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(50);
}


void griffes_stockage() {
   // changement de position des ax12 pour le stockage
    angle_AX12(AX_GRIFFE_GAUCHE_1,AX_GRIFFE_GAUCHE_1_POS_STOCKAGE_2,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_GAUCHE_1,AX_GRIFFE_GAUCHE_1_POS_STOCKAGE_2,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(10);
    angle_AX12(AX_GRIFFE_DROIT_1,AX_GRIFFE_DROIT_1_POS_STOCKAGE_2,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_DROIT_1,AX_GRIFFE_DROIT_1_POS_STOCKAGE_2,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(50);
	angle_AX12(AX_GRIFFE_GAUCHE_2,AX_GRIFFE_GAUCHE_2_POS_STOCKAGE_2,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_GAUCHE_2,AX_GRIFFE_GAUCHE_2_POS_STOCKAGE_2,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(10);
    angle_AX12(AX_GRIFFE_DROIT_2,AX_GRIFFE_DROIT_2_POS_STOCKAGE_2,VIT_AX_RAPIDE,SANS_ATTENTE);
    angle_AX12(AX_GRIFFE_DROIT_2,AX_GRIFFE_DROIT_2_POS_STOCKAGE_2,VIT_AX_RAPIDE,SANS_ATTENTE);
    delay_ms(50);
}

//fonction pour l'ouverture et la fermeture des bras pour les PV
void bras_pv_gauche_fermer(){
    angle_AX12(AX_PV_GAUCHE_1,AX_PV_GAUCHE_1_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE); 
}

void bras_pv_gauche_ouvert(){
	angle_AX12(AX_PV_GAUCHE_1,AX_PV_GAUCHE_1_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
}

void bras_pv_droit_fermer(){
    angle_AX12(AX_PV_DROIT_1,AX_PV_DROIT_1_POS_INIT,VIT_AX_RAPIDE,SANS_ATTENTE); 
}

void bras_pv_droit_ouvert(){
	angle_AX12(AX_PV_DROIT_1,AX_PV_DROIT_1_OUVERT,VIT_AX_RAPIDE,SANS_ATTENTE);
}


/******************************************************************************/
/******************************** FONCTION BOUCLE *****************************/
/******************************************************************************/
void autom_20ms (void)
{
    //fonction qui definit les actions
    switch (FLAG_ACTION)
    {
        case NE_RIEN_FAIRE:
            break;
        default :
            break;
    }
    
    if (CPT_TEMPS_MATCH.t_ms > 97000UL)
    {
        // Funny action
    }
}    
