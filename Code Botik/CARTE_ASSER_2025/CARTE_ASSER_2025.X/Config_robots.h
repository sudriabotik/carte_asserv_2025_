/******************************************************************************/
/************** Carte principale Robot 1 : DSPIC33FJ128MC804*******************/
/******************************************************************************/
/* Fichier 	: Config_robots.h
 * Auteur  	: Quentin
 * Revision	: 1.0
 * Date		: 4 décembre 2014, 12:52
 *******************************************************************************
 *  Fichier qui permet très facilemet d'adapter les paramètres pour changer
 *  de robots.
 *
 ******************************************************************************/

#ifndef CONFIG_ROBOTS_H
#define	CONFIG_ROBOTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system.h"

#define TEMPS_MATCH_MS 90000UL

/******************************************************************************/
/***************************** Defines ****************************************/
/******************************************************************************/
#define PETIT_ROBOT

#define NO_SERIALUS     // Commanter la ligne pour avoir le serialus, décommanter pour supprimer le serialus
#define SerialusM2MTrue   // test serialus machine to machine prototype
#define DEBUG_ACTIF
    
//#define MODULE_RF 
//#define ARDUINO

#define _Pi                             3.14159265359

//#define CARTE_V1
#define CARTE_V2
 /**************************************************************************/
    /****************************** ODOMETRIE *********************************/
    /**************************************************************************/
    #define _ENTRAXE_MM                302.46 //JAMES //174.7// 173.25// 173.75 vincent //170.75 //Pas assez tourné -> augmenter entraxe
    #define _DIAMETRE_ROUE_CODEUSE       63.0//JAMES//51.9715   //51.9715     //Toujours dans le sens de l'erreur : aller plus loin = diminuer D
    #define _PERIMETRE_ROUE_MM         (_DIAMETRE_ROUE_CODEUSE*_Pi)  //JAMES//196.0 //195.4 //194.91//195.1 Si distance parcourue trop grande -> Augmenter la taille des roues
  

    #define  _COEF_D                    (double) 1.000//1.0017 VIN //  //1.00372     1.004 gauche x=1.003  1.0025droite //augmente = + devie a gauche
    //+COEF_D -> + a droite
    #define  _COEF_G                    (double) 1.000   //augmente = + devie a droite
    //+COEF_G -> + a gauche
    /**************************************************************************/
    /******************************** ASSERV **********************************/
    /**************************************************************************/
        //Association distance - Vitesse - Accélérations max
    #define _VITESSE_CONSIGNE_MAX_MM     2.5//011.// VINCENT//2. //1. //2. //2.8 

    #define _VITESSE_DISTANCE_MIN        0.75
    #define _VITESSE_MAX_MM_TENSION      6.//4.//2.2 //4.
    #define _DISTANCE_CONSIGNE_MM        500.//400

    #define _ACC_POSITION_CONSIGNE      3.///1.35//2.5 //VIN //0.5  
    #define _DCC_POSITION_CONSIGNE      6.//1.05//2.5 //VIN//0.5 //2.8//0.5  LA
    #define _ACC_POSITION_MIN           1.5//1.105 //1. VIN //1. // 
    #define _DCC_POSITION_MIN           1.5//0.655// 1. VIN//0.25 //0.25 //1. //0.25 LAn

    #define _COEF_FREINAGE                1.25//1.//1.

        //Association Angle - Vitesse - Accélérations max
    #define _VITESSE_ANGLE_MAX           0.02//0.1// VIN//0.015 
    #define _VITESSE_ANGLE_MIN           0.005
    #define _ORIENTATION_CONSIGNE_DEG    90.

    #define _ACC_ORIENTATION_CONSIGNE    4.//2. 
    #define _DCC_ORIENTATION_CONSIGNE    6.//2.
    #define _ACC_ORIENTATION_MIN         2.//0.5
    #define _DCC_ORIENTATION_MIN         3.//0.5

        //Autres réglages asserv
    #define _SEUIL_IMMOBILITE               100ULL//75ULL //200
    #define _MAX_ERREUR_INTEGRALLE_V    4500.//10000.//100000.//10000. //3500.
    #define _MAX_E_INTEGRALLE_BRAKE     500.//1000. //12000

    /**************************************************************************/
    /********************************* PID ************************************/ // PID === Present Passé Futur
    /**************************************************************************/

    //PID
    #define _VITESSE_DIS_KP            0.45//0.98//0.5//0.25  VINCENT     //0.8 //1. //0.8 //1.5 //0.8 
    #define _VITESSE_DIS_KI           0.05//0.0855// 0.005//0.0005 vin //0.08//0.082 //0.13 //0.3 //0.1 //0.05 //0.02 //0.045
    #define _VITESSE_DIS_KD            0.35 //0.55//0.2// vin //0.8//0.9 //1.0 //0.8 //0.5 //0.2
    
    #define _POSITION_KP                 1.
    #define _POSITION_KI                 0.//0
    #define _POSITION_KD                 0.

    #define _ORIENTATION_KP              1.// 1.
    #define _ORIENTATION_KI              0.//0.
    #define _ORIENTATION_KD              0.

    #define KP_BRAKE                    0.04//0.008//JAMES//0.04 VIN//0.03//0.09//0.058//0.04 // fait avec vincent le 16 AVRIL 2023
    #define KI_BRAKE                    0.0015//0.0006//JAMES//0.0005 VIN//0.0015
    #define KD_BRAKE                    0.08//0.0//JAMES//0.6 VIN//0.2 //0.00333 //1.2 //0.8


    /**************************************************************************/
    /******************************* TENSIONS *********************************/
    /**************************************************************************/

    //Tensions d'alimentations
    #define _TENSION_MOTEUR_DROIT        24L
    #define _TENSION_MOTEUR_GAUCHE       24L

    #define _TENSION_MOTEUR_X            12L

    #define _TENSION_SORTIE_PTN          32L

    #define _CKECK_LIMITATION_COURANT    true 


    /**************************************************************************/
    /*************************** CONFIGS MOTEURS ******************************/
    /**************************************************************************/


    //Paramètres codeurs, et moteurs
    //Sens rotation codeur
    #define _SENS_ROT_D                  1L
    #define _SENS_ROT_G                  1L

    #define _RAPPORT_REDUCTION           1U

    #define _CODEUR_D_NB_IMP             3600U
    #define _CODEUR_G_NB_IMP             3600U

    #define _RESOLUTION_LOGICIELLE       1LL

    //PWM : sens de rotation du moteur
    #define _AVANCER_MOTEUR_D            0
    #define _RECULER_MOTEUR_D            1

    #define _AVANCER_MOTEUR_G            0
    #define _RECULER_MOTEUR_G            1

    #define _AVANCER_MOTEUR_X            0
    #define _RECULER_MOTEUR_X            1

    #define _AVANCER_MOTEUR_Y            0
    #define _RECULER_MOTEUR_Y            1
    


/**************************************************************************/
/***************************** PORTS CARTE ********************************/
/**************************************************************************/


//La définition des ports relatif à chaque carte se trouve
//Dans le fichier system.h

#define CAPT_IR_ARRIERE_DROIT      AUCUN //CAPTEUR4
#define CAPT_IR_ARRIERE_GAUCHE     AUCUN //CAPTEUR7
#define CAPT_IR_AVANT_DROIT        AUCUN //CAPTEUR1
#define CAPT_IR_AVANT_GAUCHE       AUCUN //CAPTEUR5


// Définition des standart pour la fonction évitement
// ETAT : etat de detection du capteur (si il détecte à un : ETAT_HAUT)
// NB : Si un capteur n'existe pas, le mettre à AUCUN et à ETAT_HAUT
#define _CAPT_ADV_AVANT_G            AUCUN
#define _CAPT_ADV_AVANT_D            AUCUN
#define _CAPT_ADV_AVANT_C            AUCUN

#define _ETAT_ADV_AVANT_G            ETAT_HAUT
#define _ETAT_ADV_AVANT_D            ETAT_HAUT
#define _ETAT_ADV_AVANT_C            ETAT_HAUT

#define _CAPT_ADV_ARRIERE_G          AUCUN
#define _CAPT_ADV_ARRIERE_C          AUCUN
#define _CAPT_ADV_ARRIERE_D          AUCUN

#define _ETAT_ADV_ARRIERE_G          ETAT_HAUT
#define _ETAT_ADV_ARRIERE_C          ETAT_HAUT
#define _ETAT_ADV_ARRIERE_D          ETAT_HAUT

#define _CAPTEUR1_ANALOGIQUE        DIGITAL
#define _CAPTEUR2_ANALOGIQUE        DIGITAL
#define _CAPTEUR3_ANALOGIQUE        DIGITAL


/**************************************************************************/
/**************************************************************************/
/**************************************************************************/


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_ROBOTS_H */

