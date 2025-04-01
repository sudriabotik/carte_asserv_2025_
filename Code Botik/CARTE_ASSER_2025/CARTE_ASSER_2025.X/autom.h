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


    /************************************************************************/
    /*************************** CONFIGS AX12 *******************************/
    /************************************************************************/

//----------------------2024----------------------------------------------- 
   // BRAS AVANT
// AX BRAS AVANT AXE Z
#define AX_BRAS_Z 16     // ID
#define AX_BRAS_Z_POS_INIT 728     // POS INIT  718 
#define AX_BRAS_Z_POS_STOCKAGE 460     // POS stockage
#define AX_BRAS_Z_POS_STOCKAGE_2 504     // POS dépose jardiniere
#define AX_BRAS_Z_POS_DEPOSE 510     // POS dépose sol
#define AX_BRAS_Z_POS_DEPOSE_JARDI 510     // POS dépose jardiniere
#define AX_BRAS_Z_POS_DEPOSE_FIN 639     // POS dépose sol
#define AX_BRAS_Z_POS_INT_DEPOSE_PLATEAU 555     // POS intermediaire de dépose
#define AX_BRAS_Z_POS_INT_DEPOSE_JARDI 639     // POS intermediaire de dépose
    
// AX BRAS AVANT AXE 1ERE ROTATION
#define AX_BRAS_1ER_ROT 25     // ID
#define AX_BRAS_1ER_ROT_POS_INIT 186     // POS INIT
#define AX_BRAS_1ER_ROT_POS_STOCKAGE 680     // POS stockage    641
#define AX_BRAS_1ER_ROT_POS_STOCKAGE_2 606     // POS dépose jardiniere
#define AX_BRAS_1ER_ROT_POS_DEPOSE 509     // POS dépose sol
#define AX_BRAS_1ER_ROT_POS_DEPOSE_JARDI 509     // POS dépose jardiniere
#define AX_BRAS_1ER_ROT_POS_DEPOSE_FIN 543     // POS dépose jardiniere
#define AX_BRAS_1ER_ROT_POS_INT_DEPOSE_PLATEAU 549      // POS intermediaire de dépose
#define AX_BRAS_1ER_ROT_POS_INT_DEPOSE_JARDI 543      // POS intermediaire de dépose
    
// AX BRAS AVANT AXE 2EME ROTATION
#define AX_BRAS_2EME_ROT 5     // ID
#define AX_BRAS_2EME_ROT_POS_INIT 200     // POS INIT
#define AX_BRAS_2EME_ROT_POS_STOCKAGE 162     // POS stockage
#define AX_BRAS_2EME_ROT_POS_STOCKAGE_2 172     // POS dépose jardiniere
#define AX_BRAS_2EME_ROT_POS_DEPOSE 520     // POS dépose sol
#define AX_BRAS_2EME_ROT_POS_DEPOSE_JARDI 402     // POS dépose jardiniere
#define AX_BRAS_2EME_ROT_POS_DEPOSE_FIN 550     // POS fin dépose sol
#define AX_BRAS_2EME_ROT_POS_INT_DEPOSE_PLATEAU 512     // POS intermediaire de dépose
#define AX_BRAS_2EME_ROT_POS_INT_DEPOSE_JARDI 513     // POS intermediaire de dépose
    
// GRIFFE ARRIERE 
// AX GRIFFE GAUCHE 1 
#define AX_GRIFFE_GAUCHE_1 10     // ID
#define AX_GRIFFE_GAUCHE_1_POS_INIT 160     // POS INIT
#define AX_GRIFFE_GAUCHE_1_OUVERT 560     // POS stockage
#define AX_GRIFFE_GAUCHE_1_POS_STOCKAGE_2 465     // POS dépose jardiniere

// AX GRIFFE GAUCHE 2 
#define AX_GRIFFE_GAUCHE_2 4     // ID
#define AX_GRIFFE_GAUCHE_2_POS_INIT 240     // POS INIT
#define AX_GRIFFE_GAUCHE_2_OUVERT 710     // POS stockage
#define AX_GRIFFE_GAUCHE_2_POS_STOCKAGE_2 550     // POS dépose jardiniere

// GRIFFE ARRIERE 
// AX GRIFFE DROITE 1 
#define AX_GRIFFE_DROIT_1 20      // ID
#define AX_GRIFFE_DROIT_1_POS_INIT 160     // POS INIT
#define AX_GRIFFE_DROIT_1_OUVERT 560     // POS stockage
#define AX_GRIFFE_DROIT_1_POS_STOCKAGE_2 465     // POS dépose jardiniere

// AX GRIFFE DROITE 2 
#define AX_GRIFFE_DROIT_2 24     // ID
#define AX_GRIFFE_DROIT_2_POS_INIT 240     // POS INIT
#define AX_GRIFFE_DROIT_2_OUVERT 710     // POS stockage 302
#define AX_GRIFFE_DROIT_2_POS_STOCKAGE_2 550     // POS dépose jardiniere   526 

// AX PV DROIT 
#define AX_PV_DROIT_1 7     // ID
#define AX_PV_DROIT_1_POS_INIT 357     // POS INIT
#define AX_PV_DROIT_1_OUVERT 582     // POS sortie

// AX PV GAUCHE
#define AX_PV_GAUCHE_1 32     // ID
#define AX_PV_GAUCHE_1_POS_INIT 664     // POS INIT
#define AX_PV_GAUCHE_1_OUVERT 440     // POS sortie

// VITESSE AX 
#define VIT_AX_TRES_LENT 50
#define VIT_AX_LENT 200
#define VIT_AX_RAPIDE 500
    
// SORTIE ON/OFF TURBINE
#define PIN_COMMAND	    PORTAbits.RA4
#define PIN_COMMAND_TRIS1    TRISAbits.TRISA4

// Commande Pompinettes
#define PIN_COMMANDE_POMPINETTES	    PORTAbits.RA8   
#define PIN_COMMANDE_POMPINETTES_TRIS2    TRISAbits.TRISA8    
    
// SORTIE ON/OFF TURBINE
#define PIN_COMMAND	    PORTAbits.RA4
#define PIN_COMMAND_TRIS1    TRISAbits.TRISA4


    /**************************************************************************/
    /************************* DEFINE FLAG_ACTION *****************************/
    /**************************************************************************/

    typedef enum
    {
        NE_RIEN_FAIRE,                                       
        // FLAG ACTION DU ROBOT
        FIN_DE_MATCH
            
    }_enum_flag_action;



/******************************************************************************/
/****************************** Prototypes ************************************/
/******************************************************************************/

    void jack();
    void allumer_pompes ();
    void eteindre_pompes();
    void allumer_pompinettes (); // 2024
    void eteindre_pompinettes();	//2024
    void autom_20ms (void);
    void son_evitement (uint8_t melodie);

    void init_ax();
    void init_plantes();
  	void aspi_plantes(void);
	void stock_plant(void);
	void destock_plant(void);
	void depose_plant(void);
    void fin_depose_plant();
	void depose_jardiniere_plant(void);
    void position_intermediaire_depose_plateau(void);
    void position_intermediaire_depose_jardi(void);
	void init_griffes(void);
	void griffes_ouvertes(void);
	void griffes_stockage(void);
	void start_turbine(void);
	void stop_turbine(void);
	void bras_pv_gauche_fermer(void);
	void bras_pv_gauche_ouvert(void);	
	void bras_pv_droit_fermer(void);
	void bras_pv_droit_ouvert(void);

#ifdef	__cplusplus
}
#endif

#endif	/* AUTOM_H */
