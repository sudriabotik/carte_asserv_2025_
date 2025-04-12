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

#ifdef PETIT_ROBOT

void jack()
{
    while(!SYS_JACK);
    allumer_LED_AX12(TOUS_LES_AX12);
    while(SYS_JACK);
}

void allumer_pompes ()
{
    envoit_pwm(MOTEUR_X, 100);
}

void eteindre_pompe ()
{
    envoit_pwm(MOTEUR_X, 0);
}

void son_evitement (uint8_t melodie)
{/*
    commande_AX12(100, _4PARAM, WRITE_DATA, 0x29, 10);
    commande_AX12(100, _4PARAM, WRITE_DATA, 0x28, melodie);

  */}

/******************************************************************************/
/********************************  FONCTION AX12  *****************************/
/******************************************************************************/

int pos_cherry[6] = {
    CERISE_1,
    CERISE_2,
    CERISE_3,
    CERISE_4,
    CERISE_5,
    CERISE_6
};





void grab_cake(){
    
    angle_AX12(AX_DROIT, OUVERT_DROIT, 800, SANS_ATTENTE);
    delay_ms(50);// we put this delay so the 2 pince doesn't over lap and break
    angle_AX12(AX_GAUCHE, OUVERT_GAUCHE, 800, SANS_ATTENTE);
    avancer_reculer(150,20);
    angle_AX12(AX_DROIT, FERMER_DROIT, 800, SANS_ATTENTE);
    angle_AX12(AX_GAUCHE, FERMER_GAUCHE, 800, SANS_ATTENTE);
    delay_ms(500);
    
}
void release_cake(){
    
    drop_cherry();
    angle_AX12(AX_DROIT, OUVERT_DROIT, 800, SANS_ATTENTE);
    angle_AX12(AX_GAUCHE, OUVERT_GAUCHE, 800, SANS_ATTENTE);
    avancer_reculer(-150,20);
    angle_AX12(AX_GAUCHE, FERMER_GAUCHE, 800, SANS_ATTENTE);
    delay_ms(50);
    angle_AX12(AX_DROIT, FERMER_DROIT, 800, SANS_ATTENTE);
    delay_ms(500);
    
}


int counter=0;
bool refuel= false; 

void drop_cherry(){
    
    if( counter>2 && !refuel){
        angle_AX12(AX_CERISE, POS_REFUEL, 500, SANS_ATTENTE);
        refuel=true;
    }
    else{
        angle_AX12(AX_CERISE, pos_cherry[counter], 100, SANS_ATTENTE);
        counter++;
    }
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

#endif