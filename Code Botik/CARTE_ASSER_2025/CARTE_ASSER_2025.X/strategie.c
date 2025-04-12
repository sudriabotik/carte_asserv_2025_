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

#include "strategie.h"

// Configuration robot
#define ROBOT_DIAG 365
#define ROBOT_LONGUEUR 250
#define ROBOT_LARGEUR (91+174)
static const double robot_diag_2 = ROBOT_DIAG/2;
static const double robot_longueur_2 = ROBOT_LONGUEUR/2;
static const double robot_largeur_2 = ROBOT_LARGEUR/2;
static const double calage_deplacement_min = ROBOT_DIAG/2 - ROBOT_LONGUEUR/2 + 25;

#define TEST_EVITEMENT(x, y, d) (((EVITEMENT_ADV.detection == ON) && (abs((int) (get_X() - (x)))) > (d)) && (abs((int) (get_Y() - (y))) > (d)))
#define EVITEMENT_AVANCER { EVITEMENT_ADV.sens = MARCHE_AVANT; avancer_reculer(250, 10); EVITEMENT_ADV.sens = MARCHE_ARRIERE; }
#define EVITEMENT_RECULER { EVITEMENT_ADV.sens = MARCHE_ARRIERE; avancer_reculer(-250, 10); EVITEMENT_ADV.sens = MARCHE_AVANT; }

static bool stock_full = false;
static bool bras_full = false;
static bool griffes_full = false;

const double vitesse_recup_plantes = 25;
static double y_extra = 50.;
static double x_extra = 100.;
const double calage_extra_plante = 25.;
const double decalage_min_position_depose_jardiniere = ROBOT_DIAG/2 + 25;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

void tour_de_table() {
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

// Récupération plante 4 (STRAT1) ou plante 1 (STRAT2)
uint8_t recup_plante4_ou_1(bool test, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0; 
    const int evitement_mode = EVITEMENT_ADV.mode;

    //const int evitement_actif = EVITEMENT_ADV.actif;
    const double x_base = (STRATEGIE == STRAT1) ? 1000 : 1775;
    const double y_base = (STRATEGIE == STRAT1) ? 3000 - 225 : 225 + y_extra;
    const double x_target = (STRATEGIE == STRAT1) ? 700 : 1300 + x_extra;
    const double y_target1 = (STRATEGIE == STRAT1) ? 2000 + 125 + robot_diag_2 : 1000 - 125 - robot_diag_2;
    const double y_target2 = (STRATEGIE == STRAT1) ? 2000 + robot_largeur_2 + 25 : 1000 - robot_largeur_2 - 25;
    const double y_target3 = (STRATEGIE == STRAT1) ? 2000 - 250 : 1000 + 250;
    const double y_orient = (STRATEGIE == STRAT1) ? 0 : 3000;
    
    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 25000UL))
        return 255;
    
    EVITEMENT_ADV.sens = MARCHE_AVANT;
    if (test) {
        rejoindre(x_base, y_base, MARCHE_AVANT, 50);
        cibler(x_base, y_orient, 50);
    }

    init_plantes();

    if ((erreur = rejoindre(x_target, y_target1, MARCHE_AVANT, 100))) return erreur;

    start_turbine();    
    aspi_plantes();
    if ((erreur = rejoindre(x_target, y_target2, MARCHE_AVANT, vitesse_recup_plantes)))  return erreur;
    bras_full = true;

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = avancer_reculer(-250, 25);  // Stratégie OK si trajectoire non terminée
    EVITEMENT_ADV.mode = evitement_mode;

    stock_plant();
    stock_full = true;
    bras_full = false;
    init_plantes();
    aspi_plantes();

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    erreur = rejoindre(x_target, y_target3, MARCHE_AVANT, vitesse_recup_plantes);
    stop_turbine();
    if (erreur) {
        const double y_min = (STRATEGIE == STRAT1) ? (2000 - 125 + robot_largeur_2) : (1000 + 125 - robot_largeur_2);
        if ((STRATEGIE == STRAT1) && (get_Y() > y_min))      return erreur;
        else if ((STRATEGIE == STRAT2) && (get_Y() < y_min)) return erreur;
    }

    bras_full = true;

    return DEPLACEMENT_NORMAL;
}

// Récupération plante 5 (STRAT1) ou 2 (STRAT2)
uint8_t recup_plante5_ou_2(bool test, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0;

    //const int evitement_actif = EVITEMENT_ADV.actif;
    //const int evitement_mode = EVITEMENT_ADV.mode;
    const double x_base = (STRATEGIE == STRAT1) ? 700 : 1300;
    const double y_base = (STRATEGIE == STRAT1) ? 2000 - 125 : 1000 + y_extra;
    const double x_target = (STRATEGIE == STRAT1) ? 1300 - 100 : 700 + 100; // 100 pour prendre en comptes les pinces
    const double x_orient = (STRATEGIE == STRAT1) ? 0 : 2000;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 20000UL))
        return 255;

    if (test) {
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        if (STRATEGIE == STRAT1) rejoindre(2000 - 125, y_base, MARCHE_AVANT, 25);
        else rejoindre(1000 + 125, y_base, MARCHE_AVANT, 25);
        cibler(x_orient, y_base, 50);
    }

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    if ((erreur = rejoindre(x_base, y_base, MARCHE_ARRIERE, 50))) {
        EVITEMENT_AVANCER
        erreur = rejoindre(x_base, 1000, MARCHE_ARRIERE, 50); // Stratégie OK si trajectoire non terminée
    }

    if ((erreur = cibler(x_orient, y_base, 50))) {
        EVITEMENT_RECULER
        if ((erreur = cibler(x_orient, y_base, 50))) return erreur;
    }
    
    griffes_ouvertes();
    if ((erreur = rejoindre(x_target, y_base, MARCHE_ARRIERE, vitesse_recup_plantes))) {
        const double x_min = (STRATEGIE == STRAT1) ? (1300 - robot_largeur_2) : (700 + robot_largeur_2);
        if ((STRATEGIE == STRAT1) && (get_X() < x_min))      return erreur;
        else if ((STRATEGIE == STRAT2) && (get_X() > x_min)) return erreur;
    }

    griffes_stockage();
    griffes_full = true;

    return DEPLACEMENT_NORMAL;
}

// Récupération plante 5 (STRAT1) ou 2 (STRAT2) / stratégie alternative
uint8_t recup_plante5_ou_2_alt(bool test, _enum_strategies STRATEGIE, double x_target, double y_target, double y_evitement) {
    uint8_t erreur = 0;
    const int evitement_mode = EVITEMENT_ADV.mode;

    //const int evitement_actif = EVITEMENT_ADV.actif;
    const double y_base = (STRATEGIE == STRAT1) ? y_target + 125 + robot_diag_2 : y_target - 125 - robot_diag_2;
    const double y_target1 = (STRATEGIE == STRAT1) ? y_target + robot_largeur_2 + 25 : y_target - robot_largeur_2 - 25;
    const double y_target2 = (STRATEGIE == STRAT1) ? y_target - 125 : y_target + 125;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 25000UL))
        return 255;

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    if (test) {
        if (STRATEGIE == STRAT1) rejoindre(2500, 850, MARCHE_AVANT, 50);
        else if (x_target == 2000) rejoindre(750, 1700, MARCHE_AVANT, 50);
        else rejoindre(500, 375, MARCHE_AVANT, 50);
        cibler(x_target, y_base, 50);
    }

    if (!bras_full) init_plantes();

    if ((erreur = rejoindre(x_target, y_base, MARCHE_AVANT, 100))) {
        EVITEMENT_ADV.sens = MARCHE_ARRIERE;
        erreur = rejoindre(1000, y_evitement, MARCHE_ARRIERE, 25);
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        if ((erreur = rejoindre(x_target, y_base, MARCHE_AVANT, 100))) return erreur;
    }

    if (bras_full && !stock_full) {
        stock_plant();
        stock_full = true;
        bras_full = false;
    }

    if (!bras_full) {       
        start_turbine();
        aspi_plantes();
        if ((erreur = rejoindre(x_target, y_target1, MARCHE_AVANT, 25))) {
            EVITEMENT_RECULER
            if ((erreur = rejoindre(x_target, y_target1, MARCHE_AVANT, 25))) {
                stop_turbine();
                return erreur;
            }
        }
        stop_turbine();

        EVITEMENT_ADV.sens = MARCHE_ARRIERE;
        EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
        erreur = avancer_reculer(-250, 50);  // Stratégie OK si trajectoire non terminée
        EVITEMENT_ADV.mode = evitement_mode;

        EVITEMENT_ADV.sens = MARCHE_AVANT;
        if (!stock_full) {
            start_turbine();

            stock_plant();
            stock_full = true;
            bras_full = false;

            aspi_plantes();
            erreur = rejoindre(x_target, y_target2, MARCHE_AVANT, 25);
            stop_turbine();
            if (erreur) {
                const double y_min = (STRATEGIE == STRAT1) ? (y_target - 125 + robot_largeur_2) : (y_target + 125 - robot_largeur_2);
                if ((STRATEGIE == STRAT1) && (get_Y() > y_min))      return erreur;
                else if ((STRATEGIE == STRAT2) && (get_Y() < y_min)) return erreur;
            }
            bras_full = true;
        }
    } else {
        // Stratégie alternative si le robot est arrivé avec le bras ou le stock déjà en partie rempli
        const double y_orient = (STRATEGIE == STRAT1) ? 3000 : 0;
        EVITEMENT_ADV.sens = MARCHE_ARRIERE;
        if ((erreur = cibler(x_target, y_orient, 50))) {
            erreur = rejoindre(x_target, y_evitement, MARCHE_ARRIERE, 25);
            if ((erreur = cibler(x_target, y_orient, 50))) return erreur;
        }

        griffes_ouvertes();
        if ((erreur = rejoindre(x_target, y_target1, MARCHE_ARRIERE, 50))) {
            const double y_min = (STRATEGIE == STRAT1) ? (y_target + 125 + robot_largeur_2) : (y_target - 125 - robot_largeur_2);
            if ((STRATEGIE == STRAT1) && (get_Y() > y_min))      return erreur;
            else if ((STRATEGIE == STRAT2) && (get_Y() < y_min)) return erreur;
        }

        griffes_stockage();
        griffes_full = true;
    }

    return DEPLACEMENT_NORMAL;
}

// Dépose dans la zone de départ de la stratégie 1
uint8_t depose_zone_depart_strat1(bool test) {
    uint8_t erreur = 0;
    const int evitement_mode = EVITEMENT_ADV.mode;

    const int evitement_actif = EVITEMENT_ADV.actif;
    const bool calageY = true;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 25000UL))
        return 255;

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    if (test) {
        rejoindre(1425, 2000, MARCHE_AVANT, 25);
        cibler(2000, 2000, 50);
    }

    if ((erreur = rejoindre(1000, 2250, MARCHE_AVANT, 50))) {
        EVITEMENT_RECULER
        if ((erreur = rejoindre(1000, 1500, MARCHE_AVANT, 50))) return erreur;
        rejoindre(1000, 2250, MARCHE_AVANT, 50);
    }

    position_intermediaire_depose_jardi();

    if (calageY) {
        if (rejoindre(1775, 2250, MARCHE_AVANT, 50) == DEPLACEMENT_NORMAL) {
            EVITEMENT_ADV.actif = OFF;
            erreur = calage_X(2000 - robot_largeur_2, 180, MARCHE_AVANT, 10);
            EVITEMENT_ADV.actif = evitement_actif;
        }
        erreur = rejoindre(1000, 2250, MARCHE_ARRIERE, 50);
    }
    
    if ((erreur = rejoindre(1000, 2750, MARCHE_AVANT, 75))) return erreur;
    if ((erreur = cibler(1000, 3000, 50)))                  return erreur;

    EVITEMENT_ADV.actif = OFF;
    erreur = calage_Y(3000 - robot_largeur_2, 90, MARCHE_AVANT, 10);
    erreur = avancer_reculer(-calage_deplacement_min, 10);
    EVITEMENT_ADV.actif = evitement_actif;
    
    if ((erreur = cibler(2000, get_Y(), 25))) return erreur;
    // Tentative de dépose même en cas d'évitement
    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = avancer_reculer(200, 25);
    EVITEMENT_ADV.mode = evitement_mode;

    griffes_ouvertes();
    griffes_full = false;

    return DEPLACEMENT_NORMAL;
}

// Dépose dans la zone de départ de la stratégie 2
uint8_t depose_zone_depart_strat2(bool test) {
    uint8_t erreur = 0;
    //const int evitement_actif = EVITEMENT_ADV.actif;
    const int evitement_mode = EVITEMENT_ADV.mode;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 15000UL))
        return 255;

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    if (test) {
        rejoindre(500, 1500, MARCHE_ARRIERE, 25);
        cibler(500, 0, 50);
    }

    griffes_stockage();

    // Déplacement bonus donc non critique pour la suite
    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = cibler(0, 1500, 50);
    griffes_ouvertes();
    erreur = rejoindre(1500 + 125, 1500, MARCHE_ARRIERE, 50); // Pas de gestion d'évitement. Si évitement, on continue les actions
    EVITEMENT_ADV.mode = evitement_mode;

    if ((erreur = rejoindre(1775, 450, MARCHE_ARRIERE, 25))) {
        griffes_stockage();
        EVITEMENT_AVANCER
        if ((erreur = rejoindre(1000, 1000, MARCHE_ARRIERE, 25))) return erreur;
        if ((erreur = rejoindre(1775, 450, MARCHE_ARRIERE, 25)))  return erreur;
        griffes_ouvertes();
    }

    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = avancer_reculer(250, 50); // Stratégie OK si trajectoire non terminée 
    EVITEMENT_ADV.mode = evitement_mode;

    if (erreur == DEPLACEMENT_NORMAL) init_griffes();

    return DEPLACEMENT_NORMAL;
}

// Dépose jardinière 1
uint8_t depose_jardiniere1(bool test, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0;

    const int evitement_actif = EVITEMENT_ADV.actif;
    const int evitement_mode = EVITEMENT_ADV.mode;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 25000UL))
        return 255;

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    if (test) {
        rejoindre(1000, 3000-225, MARCHE_AVANT, 25);
        cibler(2000, 3000-robot_longueur_2, 25);
    }

    if ((erreur = avancer_reculer(350, 25)))
        if (get_X() < (2000 - 450 - robot_largeur_2)) return erreur;

    init_griffes();
    position_intermediaire_depose_jardi();

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    erreur = rejoindre(1615, 2650, MARCHE_ARRIERE, 50);
    //if (erreur) return erreur; // Si évitement, tentative de dépose

    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = cibler(1385, 3000, 50); // Si évitement, le calage devrait corriger la trajectoire
    EVITEMENT_ADV.mode = evitement_mode;

    EVITEMENT_ADV.actif = OFF;
    calage_Y(3000 - robot_largeur_2, 90, MARCHE_AVANT, 10);
    depose_plant();
    fin_depose_plant();
    bras_full = false;
    EVITEMENT_ADV.actif = evitement_actif;

    return avancer_reculer(-calage_deplacement_min, 25);
}

// Récupération Plante 3
// use_bras = 1 -> récupération de 3 plantes par le bras + 3 plantes par les pinces
// use_bras = 0 -> récupération des 6 plantes par les pinces
uint8_t recup_plante3(bool test, bool use_bras, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0;

    //const int evitement_actif = EVITEMENT_ADV.actif;
    const int evitement_mode = EVITEMENT_ADV.mode;
    
    use_bras = (STRATEGIE == STRAT1) ? use_bras : false; // Pas d'utilisation du bras si Strat2
    const double x_target = 500;
    const double y_base = (STRATEGIE == STRAT1) ? 2000 : 1000;
    const double y_orient = (STRATEGIE == STRAT1) ? 3000 : 0;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 25000UL))
        return 255;

    if (test) { // Non corrigé
        if (use_bras) {
            position_intermediaire_depose_jardi();
            EVITEMENT_ADV.sens = MARCHE_ARRIERE;
            rejoindre(2650, 1615, MARCHE_ARRIERE, 25);
            cibler(3000, 1385, 50);
            EVITEMENT_ADV.sens = MARCHE_AVANT;
            calage_X(3000 - robot_largeur_2, 0, MARCHE_AVANT, 10);
        } else {
            if (STRATEGIE == STRAT1) {
                EVITEMENT_ADV.sens = MARCHE_AVANT;
                rejoindre(3000 - 225, 1000, MARCHE_AVANT, 25);
                cibler(3000 - robot_longueur_2, 2000, 25);
                avancer_reculer(150, 25);
            } else {
                EVITEMENT_ADV.sens = MARCHE_ARRIERE;
                rejoindre(450, 615, MARCHE_ARRIERE, 25);
                cibler(0, 615, 50);
                calage_X(robot_largeur_2, 180, MARCHE_AVANT, 20);
                avancer_reculer(450, 25);
            }
        }
    }

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    init_griffes();
    if (!use_bras && (STRATEGIE == STRAT1)) // Trajectoire intermédiaire -> si évitement, on passe à l'étape d'après
        erreur = rejoindre(1250, 2250, MARCHE_ARRIERE, 50);

    if (use_bras && (STRATEGIE == STRAT1)) {
        if ((erreur = rejoindre(x_target, y_base, MARCHE_ARRIERE, 100))) {
            EVITEMENT_AVANCER
            if ((erreur = rejoindre(get_X(), y_base, MARCHE_ARRIERE, 25))) return erreur;
            if ((erreur = rejoindre(x_target, y_base, MARCHE_ARRIERE, 25))) return erreur;
        }

        start_turbine();
        init_plantes();

        if ((erreur = cibler(x_target, 0, 50))) {
            const double y_evitement = get_Y() + 250;
            EVITEMENT_AVANCER
            erreur = rejoindre(x_target, y_evitement, MARCHE_ARRIERE, 50); // Pas de gestion d'évitement sur une trajectoire de contournement
            if ((erreur = cibler(x_target, 0, 50))) return erreur;
        }

        aspi_plantes();
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        erreur = rejoindre(x_target, 1500 + robot_largeur_2, MARCHE_AVANT, 10);
        if (get_Y() > (1500 + 125 + robot_largeur_2)) {
            EVITEMENT_RECULER
            erreur = rejoindre(x_target, 1500 + robot_largeur_2, MARCHE_AVANT, 10);
        }
        stop_turbine();
        if (get_Y() > (1500 + 125 + robot_largeur_2)) return erreur;

        bras_full = true;

        EVITEMENT_ADV.sens = MARCHE_ARRIERE;
        EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
        erreur = avancer_reculer(-250, 50);  // Stratégie OK si trajectoire non terminée
        EVITEMENT_ADV.mode = evitement_mode;
    }

    if ((erreur = cibler(x_target, y_orient, 50))) {
        const double y_evitement = (STRATEGIE == STRAT1) ? 1500 + 50 + robot_diag_2 : 1500 - 50 - robot_diag_2;
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        erreur = rejoindre(x_target, y_evitement, MARCHE_AVANT, 10); // Pas de gestion d'évitement sur une trajectoire de contournement
        
        EVITEMENT_ADV.sens = MARCHE_ARRIERE;
        if ((erreur = cibler(x_target, y_orient, 50)))                     return erreur;
    }

    griffes_ouvertes();

    if ((erreur = rejoindre(x_target, 1500, MARCHE_ARRIERE, 50))) {
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        rejoindre(get_X()-100, 1000, MARCHE_AVANT, 50);
    }
    // En cas d'évitement, pas important de s'assurer que les griffes soient pleines ou non
    griffes_full = true;

    return erreur;
}

// Dépose jardinière 2
uint8_t depose_jardiniere2(bool test, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0;

    const int evitement_actif = EVITEMENT_ADV.actif;
    const double y_target = 765.;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 25000UL))
        return 255;

    if (test) {
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        if (STRATEGIE == STRAT1) rejoindre(1500, 500, MARCHE_AVANT, 50);
        else rejoindre(700, 1000, MARCHE_AVANT, 50);
        cibler(0, 1000, 50);
    }

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    if (STRATEGIE == STRAT1) griffes_ouvertes();
    if ((erreur = rejoindre(615, y_target, MARCHE_ARRIERE, 50))) {
        EVITEMENT_AVANCER      
        if ((erreur = rejoindre(1000, 1500, MARCHE_ARRIERE, 20))) EVITEMENT_AVANCER
        if ((erreur = rejoindre(615, y_target, MARCHE_ARRIERE, 50)))   return erreur;
    }
    griffes_full = true;

    if ((erreur = cibler(0, y_target, 50))) {
        EVITEMENT_AVANCER
        if ((erreur = rejoindre(1000, y_target, MARCHE_ARRIERE, 50))) rejoindre(1500, 1000, MARCHE_ARRIERE, 50);
        if ((erreur = rejoindre(1000, y_target, MARCHE_ARRIERE, 50))) return erreur;
        if ((erreur = cibler(0, y_target, 50)))                       return erreur;
    }

    griffes_stockage();

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    if ((erreur = rejoindre(400, y_target, MARCHE_AVANT, 30))) {
        EVITEMENT_RECULER
        if ((erreur = rejoindre(400, y_target, MARCHE_AVANT, 30))) return erreur;
    }

    EVITEMENT_ADV.actif = OFF;
    calage_X(robot_largeur_2 + calage_extra_plante, NAN, MARCHE_AVANT, 10); // Teta = NAN pour ne pas faire de calage d'angle

    avancer_reculer(-200, 25);
    position_intermediaire_depose_jardi();
    avancer_reculer(200, 25);
    depose_plant();
    fin_depose_plant();
    avancer_reculer(-decalage_min_position_depose_jardiniere, 15);
    position_intermediaire_depose_jardi();
    bras_full = false;

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    EVITEMENT_ADV.actif = evitement_actif;

    return erreur;
}

// Dépose dans la zone réservée
uint8_t depose_zone_reservee(bool test, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0;
    //const int evitement_actif = EVITEMENT_ADV.actif;
    const int evitement_mode = EVITEMENT_ADV.mode;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 15000UL))
        return 255;

    if (test) {
        position_intermediaire_depose_jardi();
        EVITEMENT_ADV.sens = MARCHE_ARRIERE;
        rejoindre(765,615, MARCHE_ARRIERE, 25);
        cibler(765, 0, 50);
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        calage_Y(robot_largeur_2, 90, MARCHE_AVANT, 20);
    }

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    //erreur = rejoindre(225 + x_extra, 765, MARCHE_ARRIERE, 25); // Si évitement, passage à l'étape suivante

    if ((erreur = rejoindre(225 + x_extra, 350, MARCHE_ARRIERE, 50))) return erreur;

    griffes_ouvertes();

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = avancer_reculer(450, 25); // Stratégie OK si trajectoire non terminée
    if (get_Y() < 500) return erreur;
    EVITEMENT_ADV.mode = evitement_mode;

    griffes_full = false;
    init_griffes();

    return erreur;
}

// Dépose dans la zone réservée / alternative
uint8_t depose_zone_reservee_alt(bool test, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0;

    const int evitement_actif = EVITEMENT_ADV.actif;
    const int evitement_mode = EVITEMENT_ADV.mode;
    const double angle_calage = (STRATEGIE == STRAT1) ? 0 : -90;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 25000UL))
        return 255;

    if (test) {
        position_intermediaire_depose_jardi();
        EVITEMENT_ADV.sens = MARCHE_ARRIERE;
        rejoindre(615, 765, MARCHE_ARRIERE, 25);
        cibler(0, 765, 50);
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        calage_X(robot_largeur_2, 90, MARCHE_AVANT, 20);
    }

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = rejoindre(300, 765, MARCHE_ARRIERE, 50);  // Si évitement, passage à l'étape suivante
    EVITEMENT_ADV.mode = evitement_mode;

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    if ((erreur = rejoindre(300, 300, MARCHE_AVANT, 50))) return erreur;

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = cibler(300, 0, 50); // Pas de stratégie d'évitement
    EVITEMENT_ADV.mode = evitement_mode;

    EVITEMENT_ADV.actif = OFF;
    calage_Y(robot_largeur_2, angle_calage, MARCHE_AVANT, 20);
    avancer_reculer(-calage_deplacement_min, 10);
    cibler(1385, 0, 25);
    avancer_reculer(200, 10);
    cibler(2000, get_Y(), 25);
    EVITEMENT_ADV.actif = evitement_actif;

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = avancer_reculer(150, 25); // Stratégie OK si trajectoire non terminée
    EVITEMENT_ADV.mode = evitement_mode;

    griffes_ouvertes();
    griffes_full = false;

    return DEPLACEMENT_NORMAL;
}

// Dépose jardinière 3
uint8_t depose_jardiniere3(bool test, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0;

    const int evitement_actif = EVITEMENT_ADV.actif;
    const int evitement_mode = EVITEMENT_ADV.mode;
    const double angle_calage = (STRATEGIE == STRAT1) ? 0 : -90;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 25000UL))
        return 255;

    if (test) {
        EVITEMENT_ADV.sens = MARCHE_ARRIERE;
        rejoindre(765, 300, MARCHE_ARRIERE, 50);
        cibler(0, 300, 50);
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        calage_X(robot_largeur_2, 0, MARCHE_AVANT, 20);
        EVITEMENT_ADV.sens = MARCHE_ARRIERE;
        avancer_reculer(-robot_diag_2, 10);
        cibler(robot_longueur_2, 2000, 25);
        EVITEMENT_ADV.sens = MARCHE_AVANT;
        avancer_reculer(150, 25);
    }

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    if ((erreur = avancer_reculer(350, 25)))
        if (get_X() < (450 + robot_largeur_2)) return erreur;
    init_griffes();

    EVITEMENT_ADV.sens = MARCHE_ARRIERE;
    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    erreur = rejoindre(615, 350, MARCHE_ARRIERE, 50);
    erreur = cibler(615, 0, 50);

    if (!bras_full) {
        destock_plant();
        stock_full = false;
    }

    EVITEMENT_ADV.actif = OFF;
    position_intermediaire_depose_jardi();
    calage_Y(robot_largeur_2, angle_calage, MARCHE_AVANT, 20);
    depose_plant();
    fin_depose_plant();
    EVITEMENT_ADV.actif = evitement_actif;
    EVITEMENT_ADV.mode = evitement_mode;
    
    bras_full = false;
    EVITEMENT_ADV.sens = MARCHE_AVANT;
    erreur = avancer_reculer(450, 50); // Pas de gestion d'évitement -> fin de déplacement OK pour la suite

    return DEPLACEMENT_NORMAL;
}

// Préparation de l'activation des panneaux solaires
uint8_t activation_panneaux_solaires(bool test, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0;
    
    const int evitement_actif = EVITEMENT_ADV.actif;
    const int evitement_mode = EVITEMENT_ADV.mode;

    if ((CPT_TEMPS_MATCH.actif == ON) && ((TEMPS_MATCH_MS - CPT_TEMPS_MATCH.t_ms) < 20000UL))
        return 255;

    if (test) {
        if (STRATEGIE == STRAT1) {
            EVITEMENT_ADV.sens = MARCHE_AVANT;
            rejoindre(750, 225, MARCHE_AVANT, 25);
            cibler(0, 225, 50);
        } else {
            EVITEMENT_ADV.sens = MARCHE_ARRIERE;
            rejoindre(225, 2000 - robot_diag_2, MARCHE_ARRIERE, 25);
            cibler(3000, 2000 - robot_diag_2, 50);
        }
    }

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    if (STRATEGIE == STRAT1) {
        if ((erreur = rejoindre(600, 1550, MARCHE_ARRIERE, 100))) {
            EVITEMENT_AVANCER
            if ((erreur = rejoindre(225, 1000, MARCHE_ARRIERE, 50))) {
                EVITEMENT_AVANCER
                if ((erreur = rejoindre(1000, 1500, MARCHE_ARRIERE, 50))) EVITEMENT_AVANCER
            }
            if ((erreur = rejoindre(600, 1550, MARCHE_ARRIERE, 50))) {
                EVITEMENT_AVANCER
                if ((erreur = rejoindre(225, 1550, MARCHE_ARRIERE, 50))) return erreur;
            }
        }

        EVITEMENT_ADV.actif = OFF;
        init_griffes();
        cibler(get_X(), 2000, 50);
        calage_Y(2000 - robot_largeur_2, -90, MARCHE_AVANT, 10);
        avancer_reculer(-calage_deplacement_min, 10);
        cibler(0, get_Y(), 10);
        if (STRATEGIE == STRAT1) calage_X(robot_largeur_2, 0, MARCHE_AVANT, 10);
        EVITEMENT_ADV.actif = evitement_actif;
    }

    if (COULEUR == BLEU) bras_pv_droit_ouvert();
    else bras_pv_gauche_ouvert();

    EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
    const double max_y = 1500 + 225; // 1000
    if ((erreur = rejoindre(get_X(), max_y, MARCHE_AVANT, 50))) {
        EVITEMENT_RECULER
        erreur = rejoindre(get_X(), max_y, MARCHE_AVANT, 50);
    }
    EVITEMENT_ADV.mode = evitement_mode;

    bras_pv_droit_fermer();
    bras_pv_gauche_fermer();

    if (STRATEGIE == STRAT2) {
        if ((erreur = rejoindre(1775, 400, MARCHE_ARRIERE, 50))) {
            EVITEMENT_AVANCER
            if ((erreur = rejoindre(1000, 1500, MARCHE_ARRIERE, 50))) EVITEMENT_AVANCER
            erreur = rejoindre(1500, 1000, MARCHE_ARRIERE, 50);
            erreur = rejoindre(1000, 500, MARCHE_ARRIERE, 50);
        }
    }

    return erreur;
}

// Retour vers la zone de recharge
uint8_t retour_zone_recharge(bool test, _enum_strategies STRATEGIE) {
    uint8_t erreur = 0;

    //const int evitement_actif = EVITEMENT_ADV.actif;
  
    const int x_base = (STRATEGIE == STRAT1) ? 2000 - robot_diag_2 : 1385;
    const int y_base = (STRATEGIE == STRAT1) ? 1500 + 225 : 3000 - robot_diag_2;
    const int x_target = (STRATEGIE == STRAT1) ? 450 : 450;
    const int y_target = (STRATEGIE == STRAT1) ? 450 : 450;
    const int y_orient = (STRATEGIE == STRAT1) ? 0 : 3000;

    EVITEMENT_ADV.sens = MARCHE_AVANT;
    if (test) {
         rejoindre(x_base, y_base, MARCHE_AVANT, 25);
         if (STRATEGIE == STRAT1) cibler(x_base, 0, 50);
         else cibler(2000, 3000 - robot_longueur_2, 25);
    }
    
    init_griffes(); // Rentrer les griffes pour ne pas risquer de les prendre dans l'adversaire

    if (STRATEGIE == STRAT2) {
        erreur = cibler(1000, 600, 50);
        erreur = passe_part(1000, 600, MARCHE_AVANT, 75, DEBUT_TRAJECTOIRE);
    }

    erreur = passe_part(x_target, y_target, MARCHE_AVANT, 75, FIN_TRAJECTOIRE);
    if (erreur && TEST_EVITEMENT(x_target, y_target, 200)) {
        EVITEMENT_RECULER
        erreur = rejoindre(x_target, y_target, MARCHE_AVANT, 100);
        if (erreur && TEST_EVITEMENT(x_target, y_target, 200)) {
            EVITEMENT_RECULER
            erreur = passe_part(1500, 1000, MARCHE_AVANT, 50, DEBUT_TRAJECTOIRE);
            erreur = passe_part(x_target, y_target, MARCHE_AVANT, 100, FIN_TRAJECTOIRE);
            if (erreur && TEST_EVITEMENT(x_target, y_target, 200)) {
                erreur = rejoindre(225, 225, MARCHE_AVANT, 100);
                if (erreur && TEST_EVITEMENT(225, 225, 250)) return erreur;
                
                const double angle_calage = (STRATEGIE == STRAT1) ? 90 : -90;

                EVITEMENT_ADV.actif = OFF;
                cibler(0, 225, 50);
                calage_Y(robot_largeur_2, angle_calage, MARCHE_AVANT, 20);
                EVITEMENT_ADV.actif = ON;
            } else {
                const double y_calage = (STRATEGIE == STRAT1) ? robot_largeur_2 : 3000 - robot_largeur_2;
               
                EVITEMENT_ADV.actif = OFF;
                cibler(x_target, y_orient, 50);
                calage_Y(y_calage, 90, MARCHE_AVANT, 20);
                EVITEMENT_ADV.actif = ON;
            }
        }
    }

    if (stock_full && !bras_full) {
        destock_plant();
        //position_intermediaire_depose_plateau();
        init_plantes();
    }

    return erreur;
}

// Stratégie de match
void strategie(){
    
    COULEUR = couleur_depart();
    STRATEGIE = STRAT2; //strategie_depart();

    // Initialisation
    EVITEMENT_ADV.actif = ON;
  
   

    init_ax();
    //calage_depart(STRATEGIE);
    /*
    EVITEMENT_ADV.actif = ON;
    EVITEMENT_ADV.mode = ACTION_EVITEMENT;
    CPT_TEMPS_MATCH.actif = OFF;
     */
    
    
    brake();
    while(1);
   

# if 0
    if (STRATEGIE == STRAT2) activation_panneaux_solaires(false, STRATEGIE);

    if (recup_plante4_ou_1(false, STRATEGIE) == EVITEMENT) {
        const double x_target = (STRATEGIE == STRAT1) ? 1300 : 700;
        const double y_target = (STRATEGIE == STRAT1) ? 2000 : 1000;
        const double y_evitement = (STRATEGIE == STRAT1) ? 3000 - 225 : 225;
        recup_plante5_ou_2_alt(false, STRATEGIE, x_target, y_target, y_evitement); // Pas de stratégie alternative en cas d'évitement lors de la récupération de plante 5
    } else
        recup_plante5_ou_2(false, STRATEGIE); // Pas de stratégie alternative en cas d'évitement lors de la récupération de plante 5

    if (STRATEGIE == STRAT1) {
        if (depose_zone_depart_strat1(false)) {
            depose_jardiniere2(false, STRATEGIE);
            depose_zone_reservee_alt(false, STRATEGIE);
            depose_jardiniere3(false, STRATEGIE);
        } else {
            if (depose_jardiniere1(false, STRATEGIE))
                recup_plante3(false, false, STRATEGIE); // pince uniquement
            else
                recup_plante3(false, true, STRATEGIE); // bras + pince
            depose_jardiniere2(false, STRATEGIE);
            depose_zone_reservee(false, STRATEGIE);
        }
        activation_panneaux_solaires(false, STRATEGIE);
    } else { // STRAT2
        depose_jardiniere2(false, STRATEGIE);
        depose_zone_reservee_alt(false, STRATEGIE);
        depose_jardiniere3(false, STRATEGIE);
        recup_plante3(false, false, STRATEGIE);
        depose_zone_depart_strat2(false);
        recup_plante5_ou_2_alt(false, STRATEGIE, (double) 1300, (double) 2000, (double) 1500);
        depose_zone_depart_strat1(false);
        depose_jardiniere1(false, STRATEGIE);
    }

    retour_zone_recharge(false, STRATEGIE);
#else
    if (STRATEGIE == STRAT2) activation_panneaux_solaires(false, STRATEGIE);

    if (recup_plante4_ou_1(false, STRATEGIE) == EVITEMENT) {
        const double x_target = (STRATEGIE == STRAT1) ? 1300 : 700;
        const double y_target = (STRATEGIE == STRAT1) ? 2000 : 1000;
        const double y_evitement = (STRATEGIE == STRAT1) ? 3000 - 225 : 225;
        recup_plante5_ou_2_alt(false, STRATEGIE, x_target, y_target, y_evitement); // Pas de stratégie alternative en cas d'évitement lors de la récupération de plante 5
    } else
        recup_plante5_ou_2(false, STRATEGIE); // Pas de stratégie alternative en cas d'évitement lors de la récupération de plante 54
        depose_jardiniere2(false, STRATEGIE);
    depose_zone_reservee(false, STRATEGIE);
    //depose_jardiniere3(false, STRATEGIE);
    recup_plante3(false, false, STRATEGIE);
    depose_zone_depart_strat2(false);
    //recup_plante5_ou_2_alt(false, STRATEGIE, (double) 1300, (double) 2000, (double) 1500);
    //depose_zone_depart_strat1(false);
    //depose_jardiniere1(false, STRATEGIE);
    retour_zone_recharge(false, STRATEGIE);
#endif
    
    brake();
    
    while(1);
}

void homologation() {
    COULEUR = couleur_depart();
    STRATEGIE = STRAT2; //strategie_depart();

    // Initialisation
    EVITEMENT_ADV.actif = OFF;
    EVITEMENT_ADV.mode = STOP;
    EVITEMENT_ADV.sens = MARCHE_AVANT;
    CPT_TEMPS_MATCH.actif = OFF;

    init_ax();
    calage_depart(STRATEGIE);

    EVITEMENT_ADV.actif = ON;
    EVITEMENT_ADV.mode = STOP;
    EVITEMENT_ADV.sens = MARCHE_AVANT;

    while(!SYS_JACK);
    CPT_TEMPS_MATCH.actif = ON;

    //avancer_reculer(1500,20);
    activation_panneaux_solaires(false, STRATEGIE);
    
    brake();

    while(1);
    /*while (1)
    {
        if ( (CAPT_ADV_AVANT_C1 == ETAT_ADV_AVANT_C1) || (CAPT_ADV_AVANT_C2 == ETAT_ADV_AVANT_C2))
            stock_plant();
        else
            destock_plant();
        if ((CAPT_ADV_AVANT_G == ETAT_ADV_AVANT_G))
            bras_pv_gauche_fermer();
        else
            bras_pv_gauche_ouvert();
        if ((CAPT_ADV_AVANT_D == ETAT_ADV_AVANT_D))
            bras_pv_droit_fermer();
        else
            bras_pv_droit_ouvert();

        delay_ms(2000);
    }*/

    brake();
}

// Permet de caler le robot sur les bords pour connaitre sa position
void calage_depart(_enum_strategies STRATEGIE){
    init_position_robot(0., 0., 0.); //utile
    
    if (STRATEGIE == STRAT1) { // Départ du milieu
        calage_Y(3000 - robot_largeur_2, -90, MARCHE_ARRIERE, 10);
        avancer_reculer(500, 25);
        orienter(180, 25);
        calage_X(robot_largeur_2, 180, MARCHE_AVANT, 10);
        avancer_reculer(-200, 25);
        rejoindre(1500, get_Y(), MARCHE_ARRIERE, 25);
        orienter(-90, 25);
        calage_Y(3000 - robot_largeur_2, -90, MARCHE_ARRIERE, 10);
        avancer_reculer(150, 25);
    } else { // Départ du coin
        orienter(90, 25);
        calage_X(2000 - robot_largeur_2, 0, MARCHE_ARRIERE, 10);
        avancer_reculer(calage_deplacement_min, 25);
        orienter(-90, 25);
        calage_Y(robot_largeur_2, 90, MARCHE_ARRIERE, 10);
    }
}

//Autre
void attendre(uint32_t ms)
{
    uint32_t temp = CPT_TEMPS_MATCH.t_ms;
    while(CPT_TEMPS_MATCH.t_ms - temp < ms); 
}
