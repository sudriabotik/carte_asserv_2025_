/* 
 * File:   autom.h
 * Author: Quentin
 *
 * Created on 1 février 2015, 17:12
 */

#ifndef AUTOM_H
#define	AUTOM_H

#ifdef	__cplusplus
extern "C" {
#endif


/******************************************************************************/
/******************************** INCLUDES ************************************/
/******************************************************************************/

#include "Config_robots.h"

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/



/******************************************************************************/
/****************************** DEFINES GLOBALES ******************************/
/******************************************************************************/


    /**************************************************************************/
    /*************************** DEFINE Général *******************************/
    /**************************************************************************/

    /**
     * Couleurs des zondes de départ
     */
    typedef enum
    {
        JAUNE = 1,
        BLEU = 0
        
    }_enum_couleurs;
    
    /**
     * Strat de départ
     */
    typedef enum
    {
        STRAT1 = 0,
        STRAT2 = 1
        
    }_enum_strategies;
     
     
    /**************************************************************************/
    /*************************** DEFINE ID AX12 *******************************/
    /**************************************************************************/

#ifdef PETIT_ROBOT
    
    // AX PINCE GAUCHE 
#define AX_GAUCHE 7
#define OUVERT_GAUCHE 85
#define FERMER_GAUCHE 193
#define RANGER_GAUCHE 324
    
    // AX PINCE DROITE
#define AX_DROIT 25
#define OUVERT_DROIT 380
#define FERMER_DROIT 206
#define RANGER_DROIT 110
    
    
    // AX CERISE
#define AX_CERISE 23
    
#define POS_REFUEL 2

#define CERISE_1 1
#define CERISE_2 2 
#define CERISE_3 3
#define CERISE_4 4
#define CERISE_5 5
#define CERISE_6 6

   
    
    
#endif

#ifdef  GROS_ROBOT
    
    
    
#define PIN_COMMAND	    PORTAbits.RA4
#define PIN_COMMAND_TRIS1    TRISAbits.TRISA4
    
#define PIN_DIRECTION	    PORTAbits.RA8   
#define PIN_DIRECTION_TRIS2    TRISAbits.TRISA8
    
    
    
    
    
    

#endif

    /**************************************************************************/
    /*************************** POSITIONS AX12 *******************************/
    /**************************************************************************/

#ifdef  PETIT_ROBOT
    
    
    
#endif

#ifdef GROS_ROBOT
    

#endif

    /**************************************************************************/
    /************************* DEFINE FLAG_ACTION *****************************/
    /**************************************************************************/

    typedef enum
    {
        NE_RIEN_FAIRE,                                       

#ifdef  PETIT_ROBOT
        // FLAG ACTION DU PETIT ROBOT
#endif

#ifdef GROS_ROBOT
       // FLAG ACTION DU GROS ROBOT       
#endif 
     
        FIN_DE_MATCH
            
    }_enum_flag_action;




/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


    
/******************************************************************************/
/****************************** Prototypes ************************************/
/******************************************************************************/

    void jack();
    void allumer_pompes ();
    void eteindre_pompe();
    void autom_20ms (void);
    void son_evitement (uint8_t melodie);

#ifdef  PETIT_ROBOT
    
    void grab_cake();
    void release_cake();
    void drop_cherry();

#endif

#ifdef  GROS_ROBOT

    void rotation_us(void);

    // Fonctions d'init
    void init_jack();
    void init_depart();

    void rotation_us_avant();
    void poulie_haut();
    void poulie_bas();
    void start_aspi();
    void stop_aspi();
    void throw_cherry();
    
    
    
    
    //Fonction AX12

    uint8_t check_capteur (uint8_t cote);

    /**
     * Fonction qui permet d'inverser le côté en fonction de la couleur
     * @param cote : le cote (DROITE ou GAUCHE)
     * @return le côté opposé GAUCHE ou DROITE
     */
    uint8_t inversion_autom (uint8_t cote);

   
    /**************************************************************************/
    /**************************************************************************/
    /**************************************************************************/
#endif


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

#ifdef	__cplusplus
}
#endif

#endif	/* AUTOM_H */

