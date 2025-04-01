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

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

void attendre(uint32_t ms)
{
    uint32_t temp = CPT_TEMPS_MATCH.t_ms;
    while(CPT_TEMPS_MATCH.t_ms - temp < ms); 
}


//#define STRAT
void strategie()
{
    
#ifdef GROS_ROBOT
    
    //EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    //EVITEMENT_ADV.mode = ACTION_EVITEMENT;
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    
    COULEUR = couleur_depart();
    
    
    //INITIALISATION DES ROBOTS + POSITIONNEMENT
    init_AX12();
        
#define ROBOT_GOLDENIUM
    
    
    
#ifdef SERVO_2_AXES
    //void angle_AX12 (uint8_t ID,  uint16_t position, uint16_t vitesse, uint8_t ATTENTE )
    angle_AX12(1, 382, 100, SANS_ATTENTE);
    angle_AX12(2, 512, 100, SANS_ATTENTE);
    //angle_AX12(3,695, 100, SANS_ATTENTE);
   
    CPT_TEMPS_MATCH.actif = true;
    attendre(3000);
    
    angle_AX12(1,560, 200, SANS_ATTENTE);
    angle_AX12(1, 88, 100, AVEC_ATTENTE);
    angle_AX12(2,815, 200, AVEC_ATTENTE);
    attendre(500);
    lancer_autom_AX12();
    
            
#endif
    
   
    
#ifdef ROBOT_GOLDENIUM
    // position au centre de la plaque des roues (INUTILE CALAGE AUTOMATIQUE APRES)
    init_position_robot(140,450, 0.); 
    
    //angle_AX12(4,300,100,SANS_ATTENTE);//init ax_pompe
    
    //Procédure de calage automatique DEBUT
  
    calage_Y(450, 0, MARCHE_ARRIERE, 10);
    calage_X(140, 0, MARCHE_ARRIERE, 10);
    
    rejoindre(140+100, 450, MARCHE_AVANT, 10);
    orienter(90,50);
    
    calage_Y(140, 90, MARCHE_ARRIERE, 10);
    rejoindre(240, 450, MARCHE_AVANT, 10);
                                                                                //print_position();
    orienter(-55., 50);
    //Procedure de calage automatique FIN
    
    /*QUELQUES LIGNES DE DEBUG POUR Y VOIR PLUS CLAIR*/
    if (COULEUR == VIOLET){printf("VIOLET");}
    if (COULEUR == ORANGE){printf("ORANGE");}
    /*FIN DEBUG*/
    
#endif
    
    EVITEMENT_ADV.actif = ON;
    EVITEMENT_ADV.actif = OFF;
    
    while(1){
        if(SYS_JACK){
            CPT_TEMPS_MATCH.actif = true;
           
            if (COULEUR == VIOLET){ printf("Strat violet");
                //Chemin vert le goldenium
            
                passe_part(415, 235, MARCHE_AVANT, 50, DEBUT_TRAJECTOIRE);
                
                EVITEMENT_ADV.actif = ON;
                
                passe_part(1500, 240,MARCHE_AVANT, 50, MILIEU_TRAJECTOIRE);
                passe_part(1600, 240,MARCHE_AVANT, 25, MILIEU_TRAJECTOIRE);
                //on sort le bras un peu avant
                angle_AX12(BRAS_DROIT, BRAS_DROIT_OUVERT, 255, SANS_ATTENTE);
                //on avance en poussant le palet
                passe_part(1860, 240, MARCHE_AVANT, 25, FIN_TRAJECTOIRE);
                //on ferme le bras 
                angle_AX12(BRAS_DROIT, BRAS_DROIT_DERRIERE, 255, SANS_ATTENTE);

                //on se positionne face au goldenium
                rejoindre(2180,290,MARCHE_AVANT, 40);
                angle_AX12(BRAS_POMPE,260,100,SANS_ATTENTE);
                
                EVITEMENT_ADV.actif = OFF;
                
                orienter(-90.,50);
                //On range le bras//on ferme le bras 
                angle_AX12(BRAS_DROIT, BRAS_DROIT_FERME, 100, SANS_ATTENTE);
                //allumer pompe
                envoit_pwm(MOTEUR_X,40);
                //on avance a toute vitesse vers le gold
                rejoindre(2180,245, MARCHE_AVANT, 40); 
                //on avance doucement vers le gold
                rejoindre(2180,225, MARCHE_AVANT, 10);
                
                //ON A LE GOLDENIUM

                delay_ms(500);
               
                //on recule
                passe_part(2180,235,MARCHE_ARRIERE,50,DEBUT_TRAJECTOIRE); //risque de collision
               //on monte le bras
                angle_AX12(BRAS_POMPE,500,100,SANS_ATTENTE);
                passe_part(2180,350,MARCHE_ARRIERE,50,FIN_TRAJECTOIRE);
                
                EVITEMENT_ADV.actif = ON; 
                EVITEMENT_ADV.sens = MARCHE_ARRIERE; //LIGNE QUE J AVAIS OUBLIE ! PERMET DE REGARDER DERRIERE POUR L EVITEMENT !! risque de soucis
                
                //on recule
                angle_AX12(BRAS_POMPE,500,100,SANS_ATTENTE); //le bras descend de maniere anormale, d'où la répétition de l'ordre
                rejoindre(1670, 850, MARCHE_ARRIERE, 50);
                
                
                //va vers la balance
                rejoindre(1280,1190, MARCHE_AVANT, 50);
                angle_AX12(BRAS_POMPE,500,100,SANS_ATTENTE); //re_ordre au cas où
                orienter(90.,50);
                //face a la balance
                angle_AX12(BRAS_POMPE,500,100,SANS_ATTENTE); //re_ordre au cas où
                EVITEMENT_ADV.actif = OFF;
                //rejoindre(1280, 1220, MARCHE_AVANT, 35); //LIGNE PAS TESTEE risque d'être trop proche de la balance et la detecte comme un obstacle (23cm))
               
                rejoindre(1280, 1450, MARCHE_AVANT, 35);
                
                //on eteind la pompe (lache gold)
                envoit_pwm(MOTEUR_X,0);
                delay_ms(500);
                
                //RECUPERATION BLEU BALANCE
                //quitte la balance en marche arriere 
                EVITEMENT_ADV.actif = ON;  
                EVITEMENT_ADV.sens = MARCHE_ARRIERE; //LIGNE pas testée
                rejoindre(1280, 1200, MARCHE_ARRIERE, 35);
                //Va vers sa gauche, vers le bleu
                EVITEMENT_ADV.actif = OFF; 
                orienter(180.,50);
               
                //avance jusqu'au bleu (selon les x) 
                passe_part(1280, 1200,MARCHE_AVANT,50,DEBUT_TRAJECTOIRE);
                EVITEMENT_ADV.actif = ON;
                //on oriente la pompe
                angle_AX12(BRAS_POMPE,0,100,SANS_ATTENTE);
                //on va vers le bleu (selonles x)
                passe_part(780,1200,MARCHE_AVANT,50,FIN_TRAJECTOIRE);
                EVITEMENT_ADV.actif = OFF;
                //s'oriente vers le bleu
                orienter(90.,50);
                rejoindre(780,1385,MARCHE_AVANT,10);
                //pompe allumé recup bleu
                envoit_pwm(MOTEUR_X,40);
                //va droit dans le mur doucement
                rejoindre(780,1410,MARCHE_AVANT,10);
                delay_ms(500);
                //recule avec le bleu
                EVITEMENT_ADV.actif = ON; 
                EVITEMENT_ADV.sens = MARCHE_ARRIERE;
                //recule avec le bleu
                rejoindre(780,1200,MARCHE_ARRIERE,25);
                //monte le bras avec le bleu
                angle_AX12(BRAS_POMPE,500,100,SANS_ATTENTE);
                //s'oriente vers la balance
                EVITEMENT_ADV.actif = OFF;
                orienter(0.,50);
                EVITEMENT_ADV.actif = ON; 
                EVITEMENT_ADV.sens = MARCHE_AVANT; 
                //va vers la balance
                rejoindre(1040,1200,MARCHE_AVANT,50);
                EVITEMENT_ADV.actif = OFF;
                rejoindre(1262,1200,MARCHE_AVANT,50);
                //s'oriente face à la balance
                orienter(90.,50);
                //avance droit sur la balance
                rejoindre(1262,1420,MARCHE_AVANT,25);
                rejoindre(1262,1435,MARCHE_AVANT,10);
                envoit_pwm(MOTEUR_X,0); //lache le bleu
                delay_ms(500);
                
               
                //RECUPERATION VERT BALANCE (cote violet))
                
                //quitte la balance en marche arriere
                EVITEMENT_ADV.actif = ON; 
                EVITEMENT_ADV.sens = MARCHE_ARRIERE; 
                rejoindre(1280, 1200, MARCHE_ARRIERE, 35);
                //se tourne vers le vert
                orienter(180.,50);
                //avance jusqu'au vert (selon les x) 
                passe_part(1280, 1200,MARCHE_AVANT,50,DEBUT_TRAJECTOIRE);
                EVITEMENT_ADV.actif = ON; 
                EVITEMENT_ADV.sens = MARCHE_AVANT; 
                //on oriente la pompe
                angle_AX12(BRAS_POMPE,0,100,SANS_ATTENTE);
                //on va vers le vert (selonles x)
                passe_part(560,1200,MARCHE_AVANT,50,FIN_TRAJECTOIRE);
                EVITEMENT_ADV.actif = OFF;
                //s'oriente vers le vert
                orienter(90.,50);
                rejoindre(560,1385,MARCHE_AVANT,10);
                //pompe allumé recup vert
                envoit_pwm(MOTEUR_X,40);
                //va droit dans le mur
                rejoindre(560,1410,MARCHE_AVANT,10);
                delay_ms(500);
                
                //recule avec le vert
                EVITEMENT_ADV.actif = ON;
                EVITEMENT_ADV.sens = MARCHE_ARRIERE;
                rejoindre(560,1200,MARCHE_ARRIERE,25);
                //monte le bras avec le vert
                angle_AX12(BRAS_POMPE,500,100,SANS_ATTENTE);
                //s'oriente vers la balance
                EVITEMENT_ADV.actif = OFF;
                orienter(0.,50);
                 EVITEMENT_ADV.actif = ON;
                
                //va vers la balance
                rejoindre(1270,1200,MARCHE_AVANT,50);
                //s'oriente face à la balance
                orienter(90.,50);
                //avance droit sur labalance
                EVITEMENT_ADV.actif = OFF;
                rejoindre(1270,1415,MARCHE_AVANT,25);
                rejoindre(1270,1435,MARCHE_AVANT,10);
                envoit_pwm(MOTEUR_X,0); //lache le vert
                delay_ms(500);
                
                
                
                
            }//COULEUR VIOLET
            
            if (COULEUR == ORANGE){printf("Strat orange");
            //Chemin vert le goldenium
                
                passe_part(415, 200, MARCHE_AVANT, 50, DEBUT_TRAJECTOIRE);
                
                EVITEMENT_ADV.actif = ON;
                
                passe_part(1500, 180,MARCHE_AVANT, 50, MILIEU_TRAJECTOIRE);
                passe_part(1600, 180,MARCHE_AVANT, 25, MILIEU_TRAJECTOIRE);
                //on sort le bras un peu avant
                angle_AX12(BRAS_GAUCHE, BRAS_GAUCHE_OUVERT, 255, SANS_ATTENTE);
                //on avance en poussant le palet
                passe_part(1865, 180, MARCHE_AVANT, 25, FIN_TRAJECTOIRE);
                //on ferme le bras 
                angle_AX12(BRAS_GAUCHE, BRAS_GAUCHE_DERRIERE, 255, SANS_ATTENTE);

                //on se positionne face au goldenium
                rejoindre(2260,260,MARCHE_AVANT, 40);
                angle_AX12(BRAS_POMPE,260,100,SANS_ATTENTE);
                EVITEMENT_ADV.actif = OFF;
                
                orienter(-90.,50);
                //On range le bras//on ferme le bras 
                angle_AX12(BRAS_GAUCHE, BRAS_GAUCHE_FERME, 100, SANS_ATTENTE);
                
                //allumer pompe
                envoit_pwm(MOTEUR_X,40);
                rejoindre(2260,155, MARCHE_AVANT, 40); 
                rejoindre(2260,135, MARCHE_AVANT, 10); 
                
                
                //ON A LE GOLDENIUM

                delay_ms(500);
                angle_AX12(BRAS_POMPE,280,100,SANS_ATTENTE);
                
                //on recule avec le gold
                rejoindre(2210, 350, MARCHE_ARRIERE, 50);
                 angle_AX12(BRAS_POMPE,280,100,SANS_ATTENTE); //prob avec moteur, on le force en haut
                 
                EVITEMENT_ADV.actif = ON;
                EVITEMENT_ADV.sens = MARCHE_ARRIERE; //LIGNE QUE J AVAIS OUBLIE ! PERMET DE REGARDER DERRIERE POUR L EVITEMENT !!
                 angle_AX12(BRAS_POMPE,280,100,SANS_ATTENTE);//on reforce
                
                
                rejoindre(1670, 850, MARCHE_ARRIERE, 50);
                
                 angle_AX12(BRAS_POMPE,280,100,SANS_ATTENTE);
                EVITEMENT_ADV.actif = OFF;
                //pour se mettre face à la balance (mauvaise orientation))
                rejoindre(1350,1190, MARCHE_AVANT, 50);
                orienter(90.,50);
                rejoindre(1350, 1415, MARCHE_AVANT, 125);
                
                //on eteind la pompe 
                envoit_pwm(MOTEUR_X,0);
                delay_ms(500);
                
                  //METTRE BLEU DANS BALANCE
                EVITEMENT_ADV.actif = ON; 
                EVITEMENT_ADV.sens = MARCHE_ARRIERE; 
                //recule au niveau dela balance
                rejoindre(1350, 1200, MARCHE_ARRIERE, 35);

                //s'oriente vers le bleu
                orienter(180.,50);
                //avance vers le bleu
                passe_part(1350, 1200,MARCHE_AVANT,50,DEBUT_TRAJECTOIRE);
                EVITEMENT_ADV.actif = ON;
                //descend le bras au niveau du palet
                angle_AX12(BRAS_POMPE,0,100,SANS_ATTENTE);
                //avance vers le bleu
                passe_part(830,1200,MARCHE_AVANT,50,FIN_TRAJECTOIRE);
                EVITEMENT_ADV.actif = OFF;
                //s'oriente vers le bleu
                orienter(90.,50);
                //avance droit dans le mur
                rejoindre(830,1385,MARCHE_AVANT,10);
                //on enclenche la pompe
                envoit_pwm(MOTEUR_X,40);
                rejoindre(830,1410,MARCHE_AVANT,10);
                delay_ms(500);
                //recule avec le bleu
                EVITEMENT_ADV.actif = ON; 
                EVITEMENT_ADV.sens = MARCHE_ARRIERE; 
                rejoindre(830,1200,MARCHE_ARRIERE,25);
                //monte le bleu
                angle_AX12(BRAS_POMPE,300,100,SANS_ATTENTE);
                //s'oriente vers la balance
                EVITEMENT_ADV.actif = OFF; 
                
                orienter(0.,50);
                //avance vers la balance
                //EVITEMENT_ADV.actif = ON; 
                //EVITEMENT_ADV.sens = MARCHE_AVANT; //LIGNE QUE J AVAIS OUBLIE ! PERMET DE REGARDER DERRIERE POUR L EVITEMENT !! risque de soucis
                
                
                rejoindre(1350,1200,MARCHE_AVANT,50);
                //se tourne vers la balance
                orienter(90.,50);
                //avance droit sur la balance
                rejoindre(1350,1420,MARCHE_AVANT,25);
                //lache le palet
                envoit_pwm(MOTEUR_X,0);
                delay_ms(500);
                                
                //METTRE VERT DANS BALANCE
                EVITEMENT_ADV.actif = ON; 
                EVITEMENT_ADV.sens = MARCHE_ARRIERE; //LIGNE QUE J AVAIS OUBLIE ! PERMET DE REGARDER DERRIERE POUR L EVITEMENT !! risque de soucis
                //recule au niveau dela balance
                rejoindre(1350, 1200, MARCHE_ARRIERE, 35);
                //s'oriente vers le vert
                orienter(180.,50);
                //avance vers le vert
                passe_part(1350, 1200,MARCHE_AVANT,50,DEBUT_TRAJECTOIRE);
                EVITEMENT_ADV.actif = ON;
                //descend le bras au niveau du palet
                angle_AX12(BRAS_POMPE,0,100,SANS_ATTENTE);
                //avance vers le vert
                passe_part(640,1200,MARCHE_AVANT,50,FIN_TRAJECTOIRE);
                EVITEMENT_ADV.actif = OFF;
                //s'oriente vers le vert
                orienter(90.,50);
                //avance droit dans le mur
                rejoindre(630,1385,MARCHE_AVANT,10);
                //on enclenche la pompe
                envoit_pwm(MOTEUR_X,40);
                rejoindre(640,1415,MARCHE_AVANT,10);
                delay_ms(500);
                //recule avec le vert
                EVITEMENT_ADV.actif = ON;
                EVITEMENT_ADV.sens = MARCHE_ARRIERE;
                rejoindre(640,1200,MARCHE_ARRIERE,25);
                //monte le bleu
                angle_AX12(BRAS_POMPE,300,100,SANS_ATTENTE);
                //s'oriente vers la balance
                
                orienter(0.,50);
                EVITEMENT_ADV.actif = OFF;
                //avance vers la balance
                rejoindre(1350,1200,MARCHE_AVANT,50);
                //se tourne vers la balance
                orienter(90.,50);
                //avance droit sur la balance
                rejoindre(1350,1405,MARCHE_AVANT,25);
                rejoindre(1350,1435,MARCHE_AVANT,10); //ralentit pour ne pas dévier
                //lache le palet
                envoit_pwm(MOTEUR_X,0);
                delay_ms(500);
                //le vert a été laché
                
                //recuper bleu 2
                /*rejoindre(1350, 1200, MARCHE_ARRIERE, 35);
                orienter(180.,50);
                rejoindre(250, 1200, MARCHE_AVANT, 35);
                orienter(90.,50);
                angle_AX12(BRAS_POMPE,330,100,SANS_ATTENTE);
                rejoindre(250, 1900, MARCHE_AVANT, 35);
                */
                //ARRET FIN DE STRAT  /  EVITEMENT OFF
              
            }//COULEUR ORANGE
            

            while(1);//stop
            
        }
    }

#endif

#ifdef PETIT_ROBOT
    
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    
    COULEUR = couleur_depart();
    init_AX12();
    init_position_robot(0,0,0.); 
    
    calage_X(0,0., MARCHE_AVANT, 10);
    calage_Y(0,0., MARCHE_AVANT, 10);
    
    while(1){
        if(!CAPTEUR8){ //orange est le bouton vert
            CPT_TEMPS_MATCH.actif = true;

            while(1);
            
            
            if(COULEUR == ORANGE){//côté vert        
                
            }
            if(COULEUR == VERT){ //côté orange
              
            }
        }
    }
  
#endif
}


void homologation()
{   
#ifdef GROS_ROBOT

    
    //EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    //EVITEMENT_ADV.mode = ACTION_EVITEMENT;
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    
    COULEUR = couleur_depart();
    //arrière du robot au milieu init : 170-26 = 144
    init_AX12();
    init_position_robot(170, 485, 0.); // position du centre de la plaque des roues
    
    
    EVITEMENT_ADV.actif = ON;
     
    while(1){
        if(SYS_JACK){
        
            while(1);
        }
    }
#endif

#ifdef PETIT_ROBOT
    
    EVITEMENT_ADV.actif = ON;
    EVITEMENT_ADV.mode = STOP;
    
    COULEUR = couleur_depart();
    init_AX12();
    init_position_robot(127., 125., 180.); 
    

    calage_Y(122, 180, MARCHE_AVANT, 25);
    rejoindre(196,122,MARCHE_ARRIERE,25);
    orienter(185, 25);
    orienter(190,25);
    
    while(1){
//        if(SYS_JACK){
        
            
            while(1){
                brake();
            }
//        }
    }
    
    brake();
        
#endif
}

void init_AX12(){
    #ifdef GROS_ROBOT
        //Init ax pompe
        angle_AX12(4,512,200,SANS_ATTENTE);
    
        //Ouvre le bras droit
        angle_AX12(BRAS_DROIT, BRAS_DROIT_OUVERT, 100, AVEC_ATTENTE);
        //Ouvre le bras gauche
        angle_AX12(BRAS_GAUCHE, BRAS_GAUCHE_OUVERT, 100, AVEC_ATTENTE);

        //Les deux bras s'ouvrent pour voir si ils fonv=ctionnent
        lancer_autom_AX12(); 
        delay_ms(2000); //On attend 2 seconde
        
        //Ferme le bras droit
        angle_AX12(BRAS_DROIT, BRAS_DROIT_FERME, 100, AVEC_ATTENTE);
        //ferme le bras gauche
        angle_AX12(BRAS_GAUCHE, BRAS_GAUCHE_FERME, 100, AVEC_ATTENTE);
        
        //Les deux bras se ferment
        lancer_autom_AX12();
    #endif
    
    
#ifdef PETIT_ROBOT
    //aaa
#endif
}



