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

#ifdef GROS_ROBOT

void son_evitement (uint8_t melodie)
{
    //Nop();
    //commande_AX12(100, _4PARAM, WRITE_DATA, 0x29, 10);
    //commande_AX12(100, _4PARAM, WRITE_DATA, 0x28, melodie);
}


void rotation_us(void)
{
    static char sens = 0;
    static float angle = 0.;
   // if (read_data(AX_US, LIRE_MOUV_FLAG) == 0)
   // {
        if (sens == 0)
        {
           
            angle -= 6;
            if (angle < -60)
                sens = 1;
        }
        else
        {
            
            angle += 6;
            if (angle > 60)
            sens = 0;
        }
   // }
}

void rotation_us_avant ()
{
    static char sens_D = 0, sens_G = 0;
    static uint16_t position_D = 0, position_G = 0;

    if (sens_D == 0)
    {
        position_D += 10;
        if (position_D > 876)
            sens_D = 1;
    }
    else
    {
        position_D -= 10;
        if (position_D < 703)
            sens_D = 0;
    }

    if (sens_G == 0)
    {
        position_G += 10;
        if (position_G > 666)
            sens_G = 1;
    }
    else
    {
        position_G -= 10;
        if (position_G < 512)
            sens_G = 0;
    }
}



/******************************************************************************/
/********************************  FONCTION AX12  *****************************/
/******************************************************************************/



/******************************************************************************/
/**************************** FONCTIONS D'INITS *******************************/
/******************************************************************************/


void init_jack()
{
    allumer_LED_AX12(TOUS_LES_AX12);
}

void jack()
{
    while(!SYS_JACK);
    while(SYS_JACK);
}

void init_depart()
{
    //Nop();
}

/******************************************************************************/
/******************************** FONCTIONS AUTOM *****************************/
/******************************************************************************/



void start_aspi(){
        
    PIN_COMMAND_TRIS1 = 0; //Make the LED pin an output
    PIN_DIRECTION_TRIS2 = 0; //Make the LED2 pin an output
    PIN_COMMAND = 1;
    PIN_DIRECTION = 0; 
    
}



void stop_aspi(){
        
    PIN_COMMAND_TRIS1 = 0; //Make the LED pin an output
    PIN_DIRECTION_TRIS2 = 0; //Make the LED2 pin an output
    PIN_COMMAND = 0;
    PIN_DIRECTION = 0;     
    
}
void throw_cherry(){
        
    PIN_COMMAND_TRIS1 = 0; //Make the LED pin an output
    PIN_DIRECTION_TRIS2 = 0; //Make the LED2 pin an output
    PIN_COMMAND = 1;
    PIN_DIRECTION = 1;     
    
}



/******************************************************************************/
/******************************** FONCTION BOUCLE *****************************/
/******************************************************************************/


void autom_20ms (void)
{
    //static uint8_t compteur_checkup_ax12 = 0;     // usless/ pas utilisé
    
    //fonction qui definit les actions
    switch (FLAG_ACTION)
    {
        case NE_RIEN_FAIRE:
            break;
        default :
            break;
    }
    
    // Rotation des us pour la détection adversaire
    if (EVITEMENT_ADV.actif == true && EVITEMENT_ADV.detection == OFF)
    {
        if (EVITEMENT_ADV.sens == MARCHE_AVANT)
            rotation_us_avant();
        else
            rotation_us();
    }
    //else
        //position standart
    
    /*
    //(PE) Je n'aime pas cette fonction, les commandes AX12 sont bolquantes
    //      Quand on check tous les ax on bloque le robot pendent un certain temp
    // Checkup que les ax12 vont bien toutes les 500 ms
    compteur_checkup_ax12++;
    if (compteur_checkup_ax12 == 25) // 500 ms
    {
        checkup_com_ax12();
    }
    */
    
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

#endif