/******************************************************************************/
/************** Carte principale Robot 1 : DSPIC33FJ128MC804*******************/
/******************************************************************************/
/* Fichier 	: asserv.c
 * Auteur  	: Quentin
 * Revision	: 1.2
 * Date		: 08/11/2014
 *******************************************************************************
 *
 *
 ******************************************************************************/

#include "system.h"


/******************************************************************************/
/*************************** Variables Globales *******************************/
/******************************************************************************/

volatile __attribute__((near)) _robot ROBOT;

volatile __attribute__((near)) _PID PID;
volatile __attribute__((near)) double KP_hybride;
volatile __attribute__((near)) _vitesse VITESSE_MAX;

volatile __attribute__((near)) _systeme_asserv X, Y;
volatile __attribute__((near)) _systeme_asserv BRAKE[2];
volatile __attribute__((near)) _systeme_asserv DISTANCE;
volatile __attribute__((near)) _systeme_asserv ORIENTATION;
volatile __attribute__((near)) _systeme_asserv VITESSE_ORIENTATION[3];
volatile __attribute__((near)) _systeme_asserv VITESSE[3];

volatile __attribute__((near)) _acc acc;

volatile __attribute__((near)) _erreur ERREUR_DISTANCE;
volatile __attribute__((near)) _erreur ERREUR_VITESSE[2];
volatile __attribute__((near)) _erreur ERREUR_ORIENTATION;
volatile __attribute__((near)) _erreur ERREUR_BRAKE[2];

volatile __attribute__((near)) _commande_moteur COMMANDE;

volatile __attribute__((near)) _flag_asserv FLAG_ASSERV;

__attribute__((near)) static double distance_restante;
__attribute__((near)) static double distance_freinage;
__attribute__((near)) static double distance_anticipation;

////////////////////////////////////////////////////////////////////////////////////
///////////////init variable asserve/////////////////////


double ENTRAXE_MM = _ENTRAXE_MM;
double DIAMETRE_ROUE_CODEUSE = _DIAMETRE_ROUE_CODEUSE;
double PERIMETRE_ROUE_MM = _PERIMETRE_ROUE_MM ;

double COEF_D = _COEF_D;
double COEF_G = _COEF_G;

double MM_PAR_TICKS = _PERIMETRE_ROUE_MM/CODEUR_D_NB_IMP_LOG;
double TICKS_PAR_MM = CODEUR_D_NB_IMP_LOG / _PERIMETRE_ROUE_MM;
#define _ticks_par_mm (CODEUR_D_NB_IMP_LOG / _PERIMETRE_ROUE_MM) 
double ENTRAXE_TICKS = CODEUR_D_NB_IMP_LOG * _ENTRAXE_MM / _PERIMETRE_ROUE_MM ;
#define _entraxe_ticks  (CODEUR_D_NB_IMP_LOG * _ENTRAXE_MM / _PERIMETRE_ROUE_MM )
double SEUIL_IMMOBILITE = _SEUIL_IMMOBILITE;

double VITESSE_CONSIGNE_MAX_MM = _VITESSE_CONSIGNE_MAX_MM;
double VITESSE_DISTANCE_MIN = _VITESSE_DISTANCE_MIN;
double VITESSE_MAX_MM_TENSION = _VITESSE_MAX_MM_TENSION;

double VITESSE_CONSIGNE_MAX_PAS  = _VITESSE_CONSIGNE_MAX_MM * _ticks_par_mm;
double VITESSE_DISTANCE_MIN_PAS =   ( _VITESSE_DISTANCE_MIN * _ticks_par_mm );
double VITESSE_MAX_TENSION  =       ( _VITESSE_MAX_MM_TENSION * _ticks_par_mm );

double DISTANCE_CONSIGNE_MM = _DISTANCE_CONSIGNE_MM;
double DISTANCE_CONSIGNE_PAS  =     ( _DISTANCE_CONSIGNE_MM * _ticks_par_mm );

double ACC_POSITION_CONSIGNE = _ACC_POSITION_CONSIGNE;
double DCC_POSITION_CONSIGNE = _DCC_POSITION_CONSIGNE;
double ACC_POSITION_MIN = _ACC_POSITION_MIN;
double DCC_POSITION_MIN = _DCC_POSITION_MIN;

double COEF_FREINAGE = _COEF_FREINAGE;

double VITESSE_ANGLE_MAX = _VITESSE_ANGLE_MAX;
double VITESSE_ANGLE_MIN = _VITESSE_ANGLE_MIN;
double VITESSE_ANGLE_PAS         =  ( _VITESSE_ANGLE_MAX * (_entraxe_ticks / 2.) );
double VITESSE_ANGLE_MIN_PAS     = ( _VITESSE_ANGLE_MIN * (_entraxe_ticks / 2.) );

double ORIENTATION_CONSIGNE_DEG = _ORIENTATION_CONSIGNE_DEG;
double ORIENTATION_CONSIGNE_PAS  =  ( _ORIENTATION_CONSIGNE_DEG * Pi /180. * (_entraxe_ticks /2.) );
 
double ACC_ORIENTATION_CONSIGNE = _ACC_ORIENTATION_CONSIGNE;
double DCC_ORIENTATION_CONSIGNE = _DCC_ORIENTATION_CONSIGNE;
double ACC_ORIENTATION_MIN = _ACC_ORIENTATION_MIN;
double DCC_ORIENTATION_MIN = _DCC_ORIENTATION_MIN;

double MAX_ERREUR_INTEGRALLE_V = _MAX_ERREUR_INTEGRALLE_V;
double MAX_E_INTEGRALLE_BRAKE = _MAX_E_INTEGRALLE_BRAKE;


/******************************************************************************/
/***************************** Fonctions Inits ********************************/
/******************************************************************************/

/**
 * Fonction qui initialise les flag de l'asserv pour d�marer l'asserv
 */
void init_flag_asserv()
{
    FLAG_ASSERV.position = OFF;
    FLAG_ASSERV.vitesse = OFF;
    FLAG_ASSERV.orientation = OFF;
    FLAG_ASSERV.fin_deplacement = FIN_DEPLACEMENT;
    FLAG_ASSERV.brake = OFF;
    FLAG_ASSERV.erreur = DEPLACEMENT_NORMAL;
    
    FLAG_ASSERV.vitesse_fin_nulle = ON;
    FLAG_ASSERV.sens_deplacement = MARCHE_AVANT;

    reinit_asserv();
    reglage_PID();

    PORTCbits.RC5 = 1;              // LED plaquette
    FLAG_ASSERV.totale = ON;
}

static inline void init_X (double x)
{
    ROBOT.X_mm = x;
    X.actuelle = ROBOT.X_mm * TICKS_PAR_MM;
}

static inline void init_Y (double y)
{
    ROBOT.Y_mm = inversion_couleur(y);
    Y.actuelle = ROBOT.Y_mm * TICKS_PAR_MM;
}

static inline void init_orientation (double teta)
{
    teta = inversion_couleur(teta);
    ROBOT.orientation_degre = teta;  // FROM 2017
    ORIENTATION.actuelle =  teta * Pi / 180. * ENTRAXE_TICKS/2;
}

void init_position_robot (double x0, double y0, uint32_t teta0)
{
    DISABLE_INTERRUPTS; // Bug fix / Jamais test�
    if (!isnan(x0))    init_X (x0);
    if (!isnan(y0))    init_Y (y0);
    if (!isnan(teta0)) init_orientation (teta0);
    ENABLE_INTERRUPTS; // Bug fix / Jamais test�
}

void init_commande_moteur(void)
{
    COMMANDE.droit = 0;
    COMMANDE.gauche = 0;
}

void reinit_asserv(void)
{
    FLAG_ASSERV.brake = OFF;
    FLAG_ASSERV.erreur = DEPLACEMENT_NORMAL;
    FLAG_ASSERV.vitesse_fin_nulle = ON;
    FLAG_ASSERV.phase_decelaration_orientation = PHASE_NORMAL;
    FLAG_ASSERV.phase_deceleration_distance = PHASE_NORMAL;

    FLAG_ASSERV.immobilite = 0ULL;

    DISTANCE.actuelle = 0.;
    DISTANCE.theorique = 0.;
    DISTANCE.consigne = 0.;

    ORIENTATION.theorique = 0.;
    ORIENTATION.consigne = 0.;

    ERREUR_DISTANCE.actuelle = 0.;
    ERREUR_DISTANCE.integralle = 0.;
    ERREUR_DISTANCE.precedente = 0.;

    ERREUR_ORIENTATION.actuelle = 0.;
    ERREUR_ORIENTATION.precedente = 0.;
    ERREUR_ORIENTATION.integralle = 0.;

    ERREUR_VITESSE[ROUE_DROITE].actuelle = 0.;
    ERREUR_VITESSE[ROUE_DROITE].integralle = 0.;
    ERREUR_VITESSE[ROUE_DROITE].precedente = 0.;

    ERREUR_VITESSE[ROUE_GAUCHE].actuelle = 0.;
    ERREUR_VITESSE[ROUE_GAUCHE].integralle = 0.;
    ERREUR_VITESSE[ROUE_GAUCHE].precedente = 0.;

    VITESSE[ROUE_DROITE].actuelle = 0.;
    VITESSE[ROUE_DROITE].consigne = 0.;
    VITESSE[ROUE_DROITE].theorique = 0.;

    VITESSE[ROUE_GAUCHE].actuelle = 0.;
    VITESSE[ROUE_GAUCHE].consigne = 0.;
    VITESSE[ROUE_GAUCHE].theorique = 0.;

    VITESSE[SYS_ROBOT].theorique = 0.;
    VITESSE[SYS_ROBOT].consigne = 0.;
    VITESSE[SYS_ROBOT].actuelle = 0.;

    VITESSE_ORIENTATION[ROUE_DROITE].actuelle = 0.;
    VITESSE_ORIENTATION[ROUE_DROITE].consigne = 0.;
    VITESSE_ORIENTATION[ROUE_DROITE].theorique = 0.;

    VITESSE_ORIENTATION[ROUE_GAUCHE].actuelle = 0.;
    VITESSE_ORIENTATION[ROUE_GAUCHE].consigne = 0.;
    VITESSE_ORIENTATION[ROUE_GAUCHE].theorique = 0.;

    VITESSE_ORIENTATION[SYS_ROBOT].actuelle = 0.;
    VITESSE_ORIENTATION[SYS_ROBOT].consigne = 0.;
    VITESSE_ORIENTATION[SYS_ROBOT].theorique = 0.;

    PID.VITESSE_DIS.seuil_immobilite = SEUIL_IMMOBILITE;
    PID.VITESSE_DIS.max_I = MAX_ERREUR_INTEGRALLE_V;
    PID.BRAKE.max_I = MAX_E_INTEGRALLE_BRAKE;
    
    acc.acceleration.orientation.max = ACC_ORIENTATION_CONSIGNE;
    acc.acceleration.orientation.min = ACC_ORIENTATION_MIN;
    acc.acceleration.position.max = ACC_POSITION_CONSIGNE;
    acc.acceleration.position.min = ACC_POSITION_MIN;
    acc.deceleration.orientation.max = DCC_ORIENTATION_CONSIGNE;
    acc.deceleration.orientation.min = DCC_ORIENTATION_MIN;
    acc.deceleration.position.max = DCC_POSITION_CONSIGNE;
    acc.deceleration.position.min = DCC_POSITION_MIN;
    
    COMMANDE.max = CONSIGNE_MAX;

    PORTCbits.RC5 = 1;
}

/******************************************************************************/
/***************************  Fonctions Getters  ******************************/
/******************************************************************************/

double get_X (void)
{
    return ROBOT.X_mm;
}

double get_Y (void)
{
    return inversion_couleur (ROBOT.Y_mm);
}

double get_orientation (void)
{
    return inversion_couleur(ROBOT.orientation_degre);
}

/******************************************************************************/
/*************************  Fonctions Conversions *****************************/
/******************************************************************************/

double MM_TO_TICK (double distance_mm)
{
    return (distance_mm * MM_PAR_TICKS);
}

double TICK_TO_MM (int32_t nb_ticks)
{
    return ((double) (nb_ticks) * (TICKS_PAR_MM));
}


/******************************************************************************/
/************************** Fonctions Saturations *****************************/
/******************************************************************************/

/**
 * ecretage_consignes()
 * Ecretage des consignes maximum pour respecter la tention max des moteurs 
 */
void ecretage_consignes(void)
{
    if (COMMANDE.droit > COMMANDE.max)
        COMMANDE.droit = COMMANDE.max;
    else if (COMMANDE.droit < - COMMANDE.max)
        COMMANDE.droit = -COMMANDE.max;

    if (COMMANDE.gauche > COMMANDE.max) 
        COMMANDE.gauche = COMMANDE.max;
    else if (COMMANDE.gauche < -COMMANDE.max)
        COMMANDE.gauche = -COMMANDE.max;
}

/**
 * saturation_vitesse_max()
 * @brief Fonction appel� lors de la g�n�ration des rampes de vitesse
 * Permet de saturer la vitesse � sa valeur maximale
 * Permet �galement d'emp�cher l'oscillation entre deux valeurs, si la vmax n'est pas un multiple de l'acel
 * @param type : asserv concern� (position, orientation)
 */
void saturation_vitesse_max (_enum_type_PID type)
{
    if (type == ASSERV_POSITION)
    {
        //Pour �viter d'osciller autour d'une valeur consigne en haut du trap�ze
        //on �cr�te � la valeur max
        if (VITESSE[SYS_ROBOT].theorique > VITESSE_MAX.position)
            VITESSE[SYS_ROBOT].theorique = VITESSE_MAX.position;
        else if (VITESSE[SYS_ROBOT].theorique < - VITESSE_MAX.position)
            VITESSE[SYS_ROBOT].theorique = - VITESSE_MAX.position;

        //Pour ne pas osciller autour d'une consigne � 0,
       // Lors de la g�n�ration de la courbe de freinage, on emp�che la g�n�ration de 
       // vitesse n�gative
        else if (VITESSE[SYS_ROBOT].consigne == 0.)
            if (abs(VITESSE[SYS_ROBOT].theorique) < acc.deceleration.position.consigne )
                VITESSE[SYS_ROBOT].theorique = 0.;
    }
    else if (type == ASSERV_ORIENTATION)
    {
        //Pour �viter d'osciller autour d'une valeur consigne en haut du trap�ze
        //on �cr�te � la valeur max
        if (VITESSE_ORIENTATION[SYS_ROBOT].theorique > VITESSE_MAX.orientation)
            VITESSE_ORIENTATION[SYS_ROBOT].theorique = VITESSE_MAX.orientation;
        else if (VITESSE_ORIENTATION[SYS_ROBOT].theorique < - VITESSE_MAX.orientation)
            VITESSE_ORIENTATION[SYS_ROBOT].theorique = - VITESSE_MAX.orientation;

        //Pour ne pas osciller autour d'une consigne � 0,
        //On check, lors de la g�n�ration de la courbe de freinage,
        //Que si on va passer n�gatif alors on �crette � 0.
        else if (VITESSE_ORIENTATION[SYS_ROBOT].consigne == 0.)
            if (abs(VITESSE_ORIENTATION[SYS_ROBOT].theorique) < acc.deceleration.orientation.consigne )
                VITESSE_ORIENTATION[SYS_ROBOT].theorique = 0.;

    }
}

/**
 * saturation_erreur_integralle_vitesse()
 * @brief : Saturation du terme int�grale 
 */
void saturation_erreur_integralle_vitesse (void)
{
    if (ERREUR_VITESSE[ROUE_DROITE].integralle > PID.VITESSE_DIS.max_I)
        ERREUR_VITESSE[ROUE_DROITE].integralle = PID.VITESSE_DIS.max_I;
    else if (ERREUR_VITESSE[ROUE_DROITE].integralle < - PID.VITESSE_DIS.max_I)
        ERREUR_VITESSE[ROUE_DROITE].integralle = - PID.VITESSE_DIS.max_I;

    if (ERREUR_VITESSE[ROUE_GAUCHE].integralle > PID.VITESSE_DIS.max_I)
        ERREUR_VITESSE[ROUE_GAUCHE].integralle = PID.VITESSE_DIS.max_I;
    else if (ERREUR_VITESSE[ROUE_GAUCHE].integralle < - PID.VITESSE_DIS.max_I)
        ERREUR_VITESSE[ROUE_GAUCHE].integralle = - PID.VITESSE_DIS.max_I;
}

/**
 * detection_blocage()
 */
void detection_blocage (void)
{
    
    // TODO : Define pourcentage mini ailleurs
    double pourcentage_vitesse_mini = 0.2;      //0.2
    
    // Si la vitesse est trop faible (20% de la consigne) et que le terme int�gralle est satur�,
    // Alors on notifie d'un blocage
    if (VITESSE[ROUE_DROITE].actuelle < pourcentage_vitesse_mini * (VITESSE[ROUE_DROITE].consigne * FLAG_ASSERV.sens_deplacement))
    {
       if (ERREUR_VITESSE[ROUE_DROITE].integralle == PID.VITESSE_DIS.max_I || ERREUR_VITESSE[ROUE_DROITE].integralle == - PID.VITESSE_DIS.max_I )
        {
            FLAG_ASSERV.immobilite++;
            FLAG_ASSERV.erreur = BLOCAGE;
        }
    }
    else if (VITESSE[ROUE_GAUCHE].actuelle < pourcentage_vitesse_mini * (VITESSE[ROUE_GAUCHE].consigne * FLAG_ASSERV.sens_deplacement))
    {
        if (ERREUR_VITESSE[ROUE_GAUCHE].integralle == PID.VITESSE_DIS.max_I || ERREUR_VITESSE[ROUE_GAUCHE].integralle == - PID.VITESSE_DIS.max_I)
        {
            FLAG_ASSERV.immobilite++;
            FLAG_ASSERV.erreur = BLOCAGE;
        }
    }
    else
    {
        FLAG_ASSERV.immobilite = 0ULL;
        FLAG_ASSERV.erreur = DEPLACEMENT_NORMAL;
    }
}

/**
 * calcul_vitesse_position()
 * @brief : d�termine la vitesse max � atteindre pour le d�placement bas� sur : 
 *      - La longueur du d�placement
 *      - La vitesse maximale auoris�e
 *      - La vitesse minimale autoris�e
 *      - le ratio envoy� par l'utilisateur
 * @param pourcentage_vitesse : % appliqu� � la valeur max calcul�e 
 */
void calcul_vitesse_position (double pourcentage_vitesse)
{
    calcul_distance_consigne_XY();
    double temp;

    // diminue la v max calcul�
    // on ne consid�re pas la courbe comme �tant lin�aire
    // mais je ne me souviens plus exactment
    if (DISTANCE.consigne > DISTANCE_CONSIGNE_PAS)
    {
        temp =  DISTANCE.consigne - DISTANCE_CONSIGNE_PAS;
        temp /= 2.;
        temp += DISTANCE_CONSIGNE_PAS;
    }
    else
        temp = DISTANCE.consigne;

    VITESSE_MAX.position = VITESSE_CONSIGNE_MAX_PAS * temp;
    VITESSE_MAX.position /= DISTANCE_CONSIGNE_PAS;

    // On garde la valeur absolue
    if (VITESSE_MAX.position < 0.)
        VITESSE_MAX.position *= -1.;

    // On �cr�te par le haut avant la mise � l'�chelle pour que cette derni�re 
    // ait une r�elle signifiacation (la fonction de calcul de vitesse, dans le cas de grande
    // vitesse, obtiens des vitesse bien superieur au max)
    if (VITESSE_MAX.position > VITESSE_MAX_TENSION)
        VITESSE_MAX.position = VITESSE_MAX_TENSION;
    
    // Mise � l'�chelle de la vitesse par rapport � la requ�te utilisateur 
    // (pourcentage de la vitesse max calcul�e)
    VITESSE_MAX.position *= pourcentage_vitesse;
    VITESSE_MAX.position /= 100.;
    
    // on �cr�te une seconde fois (l'utilisateur pouvant demander une vitesse > 100 %)
    // On peut avoir d�pass� la valeur max
    if (VITESSE_MAX.position > VITESSE_MAX_TENSION)
        VITESSE_MAX.position = VITESSE_MAX_TENSION;
    
    // On �cr�te la valeur min apr�s la mise � l'�chelle pour emp�cher que la mise � l'�chelle
    // induise des vitesse inf�rieur au minimum
    if (VITESSE_MAX.position < VITESSE_DISTANCE_MIN_PAS)
        VITESSE_MAX.position = VITESSE_DISTANCE_MIN_PAS;
}

/**
 * calcul_acceleration_position()
 * @brief FOnction qui calcul les acc�l�rations et d�c�l�rations pour construire la rampe de vitesse
 * En fonction de la distance � parcourir
 */
void calcul_acceleration_position (void)
{
    double accelMax = 0.;
    double accelMin = 0.;
    double decelMax = 0.;
    double decelMin = 0.;
    
    // si la consigne de distance est n�gative :
    //  -> La dimunition de la vitesse = acc�l�ration
    //  -> L'augmentation de la vitesse = d�c�l�ration
    // (on passe d'une vitesse nulle � une vitesse n�gative pour reculer)
    // Il faut donc inverser l'acc�l�ration et la d�c�l�ration
    if (DISTANCE.consigne > 0.)
    {
        accelMin = acc.acceleration.position.min;
        accelMax = acc.acceleration.position.max;
        decelMin = acc.deceleration.position.min;
        decelMax = acc.deceleration.position.max;
    }
    else
    {
        accelMin = acc.deceleration.position.min;
        accelMax = acc.deceleration.position.max;
        decelMin = acc.acceleration.position.min;
        decelMax = acc.acceleration.position.max;
    }
    
    //TODO : VITESSE_CONSIGNE_MAX_PAS ?
    // on fait un produit en croix par rapport � la calib, (petite vitesse, plus faible acc�l�ration)
    acc.acceleration.position.consigne = VITESSE_MAX.position;
    acc.acceleration.position.consigne *= accelMax; 
    acc.acceleration.position.consigne /= VITESSE_CONSIGNE_MAX_PAS;

    acc.deceleration.position.consigne = VITESSE_MAX.position;
    acc.deceleration.position.consigne *= decelMax; 
    acc.deceleration.position.consigne /= VITESSE_CONSIGNE_MAX_PAS;

    
    // Puis on sature l'ac�l�ration/d�c�laration aux valuers min/max
    if (acc.acceleration.position.consigne < accelMin)
    {
        acc.acceleration.position.consigne = accelMin;
    }    
    else if (acc.acceleration.position.consigne > accelMax)
    {
        acc.acceleration.position.consigne = accelMax;
    }
    
    if (acc.deceleration.position.consigne < decelMin) // /!\ REMPLACEMENT DU SIGNE > PAR <
    {
        acc.deceleration.position.consigne = decelMin;
    }
    else if (acc.deceleration.position.consigne > decelMax)
    {
        acc.deceleration.position.consigne = decelMax;
    }
}

void calcul_vitesse_orientation (double pourcentage_vitesse)
{
    calcul_distance_consigne_XY();

    fonction_PID(ASSERV_ORIENTATION);

    // Calcul de la vitesse � appliquer pour l'orientation
    VITESSE_MAX.orientation = VITESSE_ANGLE_PAS;
    VITESSE_MAX.orientation *= ERREUR_ORIENTATION.actuelle; // orientation restante � parcourir
    VITESSE_MAX.orientation /= ORIENTATION_CONSIGNE_PAS;
    
    // Valeur absolue
    if (VITESSE_MAX.orientation < 0.)
        VITESSE_MAX.orientation *= - 1.;
    
    // Saturation de la valeur max pour que la mise � l'�chelle est un sens r�el
    if (VITESSE_MAX.orientation > VITESSE_MAX_TENSION)
        VITESSE_MAX.orientation = VITESSE_MAX_TENSION;
    
    // mise � l'�chelle
    VITESSE_MAX.orientation *= pourcentage_vitesse;
    VITESSE_MAX.orientation /= 100.;


    // Re saturation apr�s la mise � l'�chelle (pouvant �tre > 100 %)
    if (VITESSE_MAX.orientation > VITESSE_MAX_TENSION)
        VITESSE_MAX.orientation = VITESSE_MAX_TENSION;
    else if (VITESSE_MAX.orientation < VITESSE_ANGLE_MIN_PAS)
        VITESSE_MAX.orientation = VITESSE_ANGLE_MIN_PAS;
}

void calcul_acceleration_orientation (void)
{
    double accelMax = 0.;
    double accelMin = 0.;
    double decelMax = 0.;
    double decelMin = 0.;
    
    // si la consigne d'orientation est n�gative :
    //  -> La dimunition de la vitesse = acc�l�ration
    //  -> L'augmentation de la vitesse = d�c�l�ration
    // (on passe d'une vitesse nulle � une vitesse n�gative pour reculer)
    // Il faut donc inverser l'acc�l�ration et la d�c�l�ration
    if (ERREUR_ORIENTATION.actuelle > 0.)
    {
        accelMin = acc.acceleration.orientation.min;
        accelMax = acc.acceleration.orientation.max;
        decelMin = acc.deceleration.orientation.min;
        decelMax = acc.deceleration.orientation.max;
    }
    else
    {
        accelMin = acc.deceleration.orientation.min;
        accelMax = acc.deceleration.orientation.max;
        decelMin = acc.acceleration.orientation.min;
        decelMax = acc.acceleration.orientation.max;
    }
   
    // on fait un produit en croix par rapport � la calib, (petite vitesse, plus faible acc�l�ration)
    acc.acceleration.orientation.consigne = VITESSE_MAX.orientation;
    acc.acceleration.orientation.consigne *= accelMax; 
    acc.acceleration.orientation.consigne /= VITESSE_ANGLE_PAS;

    acc.deceleration.orientation.consigne = VITESSE_MAX.orientation;
    acc.deceleration.orientation.consigne *= decelMax; 
    acc.deceleration.orientation.consigne /= VITESSE_ANGLE_PAS;


    // Puis on sature l'ac�l�ration/d�c�laration aux valuers min/max
    if (acc.acceleration.orientation.consigne < accelMin)
    {
        acc.acceleration.orientation.consigne = accelMin; 
    }
    else if (acc.acceleration.orientation.consigne > accelMax)
    {
        acc.acceleration.orientation.consigne = accelMax; 
    }
        
    if (acc.deceleration.orientation.consigne < decelMin)
    {
        acc.deceleration.orientation.consigne = decelMin;
    }
    else if (acc.deceleration.orientation.consigne > decelMax)
    {
        acc.deceleration.orientation.consigne = decelMax;
    }
        
}

void calcul_distance_consigne_XY (void)
{
    if (FLAG_ASSERV.type_consigne == XY)
    {
        __attribute__((near)) static double delta_x, delta_y;
        delta_x = (double) (X.consigne - X.actuelle);
        delta_y = (double) (Y.consigne - Y.actuelle);

        ORIENTATION.consigne = atan2(delta_y, delta_x ) * (ENTRAXE_TICKS /2.);

        // Si on va en marche arri�re, alors la consigne d'angle est invers�e
        // (une inversion de l'angle revient � lui enlever ou lui ajouter Pi)
        if (FLAG_ASSERV.sens_deplacement == MARCHE_ARRIERE)
        {
            if (ORIENTATION.consigne < 0.)
                ORIENTATION.consigne += Pi * ENTRAXE_TICKS/2.;
            else
                ORIENTATION.consigne -= Pi * ENTRAXE_TICKS/2.;
        }


        DISTANCE.consigne = sqrt(delta_x * delta_x + delta_y * delta_y);
        DISTANCE.consigne *= FLAG_ASSERV.sens_deplacement;
        DISTANCE.actuelle = 0.;


        // Orientation conprise entre Pi et - Pi
        if ((ORIENTATION.consigne - ORIENTATION.actuelle) > Pi * ENTRAXE_TICKS/2.)
            ORIENTATION.consigne -= Pi * ENTRAXE_TICKS;
        else if (ORIENTATION.consigne - ORIENTATION.actuelle < - Pi * ENTRAXE_TICKS/2.)
            ORIENTATION.consigne += Pi * ENTRAXE_TICKS;
    }
}


/******************************************************************************/
/**************************** Fonctions Asserv ********************************/
/******************************************************************************/


void brake(void)
{
    ERREUR_BRAKE[ROUE_DROITE].actuelle = 0.;
    ERREUR_BRAKE[ROUE_DROITE].integralle = 0.;
    ERREUR_BRAKE[ROUE_DROITE].precedente = 0.;

    ERREUR_BRAKE[ROUE_GAUCHE].actuelle = 0.;
    ERREUR_BRAKE[ROUE_GAUCHE].integralle = 0.;
    ERREUR_BRAKE[ROUE_GAUCHE].precedente = 0.;

    BRAKE[ROUE_DROITE].actuelle = 0.;
    BRAKE[ROUE_GAUCHE].actuelle = 0.;

    FLAG_ASSERV.brake = ON;
}

void unbrake (void)
{
    ERREUR_VITESSE[ROUE_DROITE].actuelle = 0.;
    ERREUR_VITESSE[ROUE_DROITE].integralle = 0.;
    ERREUR_VITESSE[ROUE_DROITE].precedente = 0.;

    ERREUR_VITESSE[ROUE_GAUCHE].actuelle = 0.;
    ERREUR_VITESSE[ROUE_GAUCHE].integralle = 0.;
    ERREUR_VITESSE[ROUE_GAUCHE].precedente = 0.;

    VITESSE[ROUE_DROITE].actuelle = 0.;
    VITESSE[ROUE_DROITE].consigne = 0.;
    VITESSE[ROUE_DROITE].theorique = 0.;

    VITESSE[ROUE_GAUCHE].actuelle = 0.;
    VITESSE[ROUE_GAUCHE].consigne = 0.;
    VITESSE[ROUE_GAUCHE].theorique = 0.;

    VITESSE_ORIENTATION[ROUE_DROITE].actuelle = 0.;
    VITESSE_ORIENTATION[ROUE_DROITE].consigne = 0.;
    VITESSE_ORIENTATION[ROUE_DROITE].theorique = 0.;

    VITESSE_ORIENTATION[ROUE_GAUCHE].actuelle = 0.;
    VITESSE_ORIENTATION[ROUE_GAUCHE].consigne = 0.;
    VITESSE_ORIENTATION[ROUE_GAUCHE].theorique = 0.;

    FLAG_ASSERV.erreur = DEPLACEMENT_NORMAL;
    FLAG_ASSERV.brake = OFF;
}

void fin_deplacement (void)
{
    FLAG_ASSERV.etat_angle = ANGLE_ATTEINT;
    FLAG_ASSERV.etat_distance = DISTANCE_ATTEINTE;
    FLAG_ASSERV.fin_deplacement = FIN_DEPLACEMENT;
}

//Fonction principale de l'asserv, qui permet d'activer les diff�rents asserv
//D'envoyer la commande aux moteurs, et de sortir des fonctions de d�placements
void asserv()
{
    VITESSE[ROUE_DROITE].consigne = 0.;
    VITESSE[ROUE_GAUCHE].consigne = 0.;

 
    //Fonction de sortie de l'asserv, v�rifie que le robot est bien a sa position.
    if (FLAG_ASSERV.etat_angle == ANGLE_ATTEINT && FLAG_ASSERV.etat_distance == DISTANCE_ATTEINTE && FLAG_ASSERV.fin_deplacement != FIN_DEPLACEMENT)
    {
        PORTCbits.RC5 = 0;
        FLAG_ASSERV.immobilite ++;

        if (FLAG_ASSERV.vitesse_fin_nulle == ON && FLAG_ASSERV.brake == OFF)
            brake();
     
        if (FLAG_ASSERV.immobilite >= PID.VITESSE_DIS.seuil_immobilite)
            FLAG_ASSERV.fin_deplacement = FIN_DEPLACEMENT;
        else if (FLAG_ASSERV.vitesse_fin_nulle == OFF)
            FLAG_ASSERV.fin_deplacement = FIN_DEPLACEMENT;
    }
    else
    {
        if (FLAG_ASSERV.immobilite >= PID.VITESSE_DIS.seuil_immobilite )
        {
            FLAG_ASSERV.etat_angle = ANGLE_ATTEINT;
            FLAG_ASSERV.etat_distance = DISTANCE_ATTEINTE;
        }
    }

    //Fonction d'appel de l'asserv
    if ( (FLAG_ASSERV.fin_deplacement != FIN_DEPLACEMENT && (FLAG_ASSERV.etat_angle == EN_COURS || FLAG_ASSERV.etat_distance == EN_COURS)) || FLAG_ASSERV.brake == ON )
    {
        if (FLAG_ASSERV.brake == OFF)
        {
            if (FLAG_ASSERV.position == ON)
            {
                asserv_distance();
            }
            if (FLAG_ASSERV.orientation == ON)
            {
                asserv_orientation();
            }
            if(FLAG_ASSERV.vitesse == ON)
            {
                if (FLAG_ASSERV.position == ON)
                    asserv_vitesse_distance();
                if (FLAG_ASSERV.orientation == ON)
                    asserv_vitesse_orientation();
            }
        }
       
        //R�initialisation des commandes moteurs � 0
        
        init_commande_moteur();

        if (FLAG_ASSERV.brake == OFF)
        {
            //Calcul des consignes moteurs gauche et droit, asserv indispendable
            fonction_PID(ASSERV_VITESSE_DISTANCE);
        }
        else
        {
            asserv_brake();
        }
        
        ecretage_consignes();

        //envoit sur les moteurs
        envoit_pwm(MOTEUR_GAUCHE,  COMMANDE.gauche);
        envoit_pwm(MOTEUR_DROIT, COMMANDE.droit);
    }
    else
    {
        if (FLAG_ASSERV.vitesse_fin_nulle == ON)
        {
            //Si aucun asserv, on bloque les moteurs � 0;
            envoit_pwm(MOTEUR_GAUCHE, 0.);
            envoit_pwm(MOTEUR_DROIT, 0.);
        }
    }     
}

void asserv_brake(void)
{
    ERREUR_BRAKE[ROUE_DROITE].actuelle = BRAKE[ROUE_DROITE].actuelle;
    ERREUR_BRAKE[ROUE_GAUCHE].actuelle = BRAKE[ROUE_GAUCHE].actuelle;

    ERREUR_BRAKE[ROUE_DROITE].integralle += ERREUR_BRAKE[ROUE_DROITE].actuelle;
    ERREUR_BRAKE[ROUE_GAUCHE].integralle += ERREUR_BRAKE[ROUE_GAUCHE].actuelle;

    if (ERREUR_BRAKE[ROUE_DROITE].integralle > PID.BRAKE.max_I)
        ERREUR_BRAKE[ROUE_DROITE].integralle = PID.BRAKE.max_I;
    if (ERREUR_BRAKE[ROUE_GAUCHE].integralle > PID.BRAKE.max_I)
        ERREUR_BRAKE[ROUE_GAUCHE].integralle = PID.BRAKE.max_I;

    if (ERREUR_BRAKE[ROUE_DROITE].integralle < -PID.BRAKE.max_I)
        ERREUR_BRAKE[ROUE_DROITE].integralle = -PID.BRAKE.max_I;
    if (ERREUR_BRAKE[ROUE_GAUCHE].integralle < -PID.BRAKE.max_I)
        ERREUR_BRAKE[ROUE_GAUCHE].integralle = -PID.BRAKE.max_I;

    COMMANDE.droit  =  ERREUR_BRAKE[ROUE_DROITE].actuelle * PID.BRAKE.KP + ERREUR_BRAKE[ROUE_DROITE].integralle * PID.BRAKE.KI + (ERREUR_BRAKE[ROUE_DROITE].actuelle - ERREUR_BRAKE[ROUE_DROITE].precedente ) * PID.BRAKE.KD;
    COMMANDE.gauche =  ERREUR_BRAKE[ROUE_GAUCHE].actuelle * PID.BRAKE.KP + ERREUR_BRAKE[ROUE_GAUCHE].integralle * PID.BRAKE.KI + (ERREUR_BRAKE[ROUE_GAUCHE].actuelle - ERREUR_BRAKE[ROUE_GAUCHE].precedente ) * PID.BRAKE.KD;

    ERREUR_BRAKE[ROUE_DROITE].precedente = ERREUR_BRAKE[ROUE_DROITE].actuelle;
    ERREUR_BRAKE[ROUE_GAUCHE].precedente = ERREUR_BRAKE[ROUE_GAUCHE].actuelle;
}

// Fonction qui g�re l'asserv de Distance, donne les consignes pour g�n�rer les rampes
void asserv_distance(void)
{
    distance_restante = 0.;
    distance_freinage = 0.;
    distance_anticipation = 0. * TICKS_PAR_MM;
    
    calcul_distance_consigne_XY();
    distance_restante = fonction_PID(ASSERV_POSITION);

    if (FLAG_ASSERV.type_consigne == MM)
    {
        if (distance_restante < 0.)
            FLAG_ASSERV.sens_deplacement = MARCHE_ARRIERE;
        else
            FLAG_ASSERV.sens_deplacement = MARCHE_AVANT;
    }

    if ((FLAG_ASSERV.sens_deplacement * distance_restante > 2 * TICKS_PAR_MM)) // 2
    {
        //si on se trouve dans un cercle de 3 cm autour du point d'arriv�
        if (FLAG_ASSERV.sens_deplacement * distance_restante < 30. * TICKS_PAR_MM) //30
        {
            FLAG_ASSERV.orientation = OFF;
            //SI on s'�loigne de notre consigne on s'arr�te
            if (ERREUR_DISTANCE.actuelle > ERREUR_DISTANCE.precedente)
            {
                FLAG_ASSERV.position = OFF;
                FLAG_ASSERV.orientation = OFF;
                FLAG_ASSERV.etat_distance = DISTANCE_ATTEINTE;
                FLAG_ASSERV.etat_angle = ANGLE_ATTEINT;
                return;
            }
        }

        if (FLAG_ASSERV.vitesse_fin_nulle == OFF)
        {
            if (FLAG_ASSERV.sens_deplacement * distance_restante < 150. * TICKS_PAR_MM) //150
            {
                FLAG_ASSERV.etat_angle = ANGLE_ATTEINT;
                FLAG_ASSERV.etat_distance = DISTANCE_ATTEINTE;
                return;
            }
        }

//        FLAG_ASSERV.etat_distance = EN_COURS;
        if (distance_restante > 0.)
        {
            VITESSE[SYS_ROBOT].consigne =  VITESSE_MAX.position; //vmax
        }
        else if (distance_restante < 0.)
        {
            VITESSE[SYS_ROBOT].consigne = - VITESSE_MAX.position; //Vmin //-120
        }

        //G�n�ration de la courbe de freinage
       if (FLAG_ASSERV.vitesse_fin_nulle == ON)
       {
           // calcul de la distance th�orique de freinage (trap�ze)
           distance_freinage = (VITESSE[SYS_ROBOT].actuelle * VITESSE[SYS_ROBOT].theorique) / (2. * acc.deceleration.position.consigne); // vitesse actu ou th�orique ?
           
            if (distance_restante < 0.)
                distance_restante *= -1.;

            // Si le robot doit freiner
            if (distance_freinage >= (distance_restante + distance_anticipation))
            {
                    FLAG_ASSERV.phase_deceleration_distance = EN_COURS;
                    VITESSE[SYS_ROBOT].consigne = 0.;
            }
        }
    }
    // Si on arrive � 2mm du point et que l'on veut une vitesse d'arr�t nulle
    else 
    {
        FLAG_ASSERV.etat_distance = DISTANCE_ATTEINTE;
        FLAG_ASSERV.position = OFF;
        FLAG_ASSERV.orientation = OFF;
        FLAG_ASSERV.etat_angle = ANGLE_ATTEINT;
        VITESSE[SYS_ROBOT].consigne = 0.;
    }
   /* else //Sinon on passe au d�placement suivant sans arr�t
    {
        FLAG_ASSERV.etat_distance = FIN_DEPLACEMENT;
    }*/
       
}

//Fonction qui g�n�re les rampes de vitesse pour l'asserv en Distance
void asserv_vitesse_distance (void)
{
    if (FLAG_ASSERV.phase_deceleration_distance == PHASE_NORMAL || VITESSE_ORIENTATION[SYS_ROBOT].consigne == 0. )
    {
        if (VITESSE[SYS_ROBOT].theorique < VITESSE[SYS_ROBOT].consigne)
            VITESSE[SYS_ROBOT].theorique += acc.acceleration.position.consigne;
        else if (VITESSE[SYS_ROBOT].theorique > VITESSE[SYS_ROBOT].consigne)
            VITESSE[SYS_ROBOT].theorique -= acc.deceleration.position.consigne;

        saturation_vitesse_max(ASSERV_POSITION);
    }
    
    if (FLAG_ASSERV.orientation == ON)
    {
        fonction_PID(KP_HYBRIDE);
        //VITESSE[ROUE_DROITE].consigne += VITESSE[SYS_ROBOT].theorique * KP_hybride;
        //VITESSE[ROUE_GAUCHE].consigne += VITESSE[SYS_ROBOT].theorique * KP_hybride;
    }
    //else
    //{
        VITESSE[ROUE_DROITE].consigne += VITESSE[SYS_ROBOT].theorique;
        VITESSE[ROUE_GAUCHE].consigne += VITESSE[SYS_ROBOT].theorique;
    //}
}


//Fonction qui permet de cr�er les consignes pour g�n�rer les rampes de Vitesse
void asserv_orientation (void)
{
    __attribute__((near)) static double angle_restant = 0.;
    __attribute__((near)) static double temps_freinage, temps_restant;

    //static int32_t compteur  = 0;

    angle_restant = fonction_PID(ASSERV_ORIENTATION); 

    if ( (angle_restant >  0.1 * Pi / 180. * ENTRAXE_TICKS) || (angle_restant < - 0.1 * Pi / 180. * ENTRAXE_TICKS ))//|| FLAG_ASSERV.position == ON)) //2�
    {
        FLAG_ASSERV.etat_angle = EN_COURS;

        if (angle_restant > 0.) 
        {
            VITESSE_ORIENTATION[SYS_ROBOT].consigne =  VITESSE_MAX.orientation;
            temps_freinage = VITESSE_ORIENTATION[SYS_ROBOT].theorique / (acc.deceleration.orientation.consigne);
        }
        else if (angle_restant < 0.)
        {
            VITESSE_ORIENTATION[SYS_ROBOT].consigne = - VITESSE_MAX.orientation;
            temps_freinage = VITESSE_ORIENTATION[SYS_ROBOT].theorique / (acc.acceleration.orientation.consigne);
        }

        //G�n�ration de la courbe de freinage
        temps_restant = angle_restant / VITESSE_ORIENTATION[SYS_ROBOT].theorique;

        if (temps_freinage <0.)
            temps_freinage *= -1.;
        if (temps_restant <0.)
            temps_restant *= -1.;


        if (temps_freinage > temps_restant)
        {
            if (FLAG_ASSERV.type_deplacement == ORIENTER)
                FLAG_ASSERV.phase_decelaration_orientation = EN_COURS;

            if (FLAG_ASSERV.type_deplacement == FAIRE_DES_TOURS && FLAG_ASSERV.vitesse_fin_nulle == OFF)
                FLAG_ASSERV.etat_angle = ANGLE_ATTEINT;
            else
                VITESSE_ORIENTATION[SYS_ROBOT].consigne = 0.;
        }
    }
    else //(FLAG_ASSERV.vitesse_fin_nulle == ON)
    {
        VITESSE_ORIENTATION[SYS_ROBOT].theorique = 0.;
        FLAG_ASSERV.etat_angle = ANGLE_ATTEINT;
        FLAG_ASSERV.phase_decelaration_orientation = PHASE_NORMAL;
    }
}


//Fonction qui g�n�re les rampes de Vitesse pour la rotation du robot
void asserv_vitesse_orientation (void)
{
    //Si on a attaqu� la phase de d�c�l�ration, on ne permet plus de r�acc�l�rer
    if (FLAG_ASSERV.phase_decelaration_orientation == PHASE_NORMAL || VITESSE_ORIENTATION[SYS_ROBOT].consigne == 0. )
    {
         if (VITESSE_ORIENTATION[SYS_ROBOT].theorique < VITESSE_ORIENTATION[SYS_ROBOT].consigne)
            VITESSE_ORIENTATION[SYS_ROBOT].theorique += acc.acceleration.orientation.consigne;


        else if (VITESSE_ORIENTATION[SYS_ROBOT].theorique > VITESSE_ORIENTATION[SYS_ROBOT].consigne)
            VITESSE_ORIENTATION[SYS_ROBOT].theorique -= acc.deceleration.orientation.consigne;

         saturation_vitesse_max(ASSERV_ORIENTATION);

         //d�bloquage de la l'interdiction d'acceleration si on arrive � une consigne nulle pour enlever l'erreur statiqye
        // if (VITESSE_ORIENTATION[SYS_ROBOT].theorique == 0)
        //     FLAG_ASSERV.phase_decelaration_orientation = PHASE_NORMAL;
    }

     VITESSE[ROUE_DROITE].consigne += VITESSE_ORIENTATION[SYS_ROBOT].theorique;
     VITESSE[ROUE_GAUCHE].consigne -= VITESSE_ORIENTATION[SYS_ROBOT].theorique;
}

/******************************************************************************/
/************************************ PID *************************************/
/******************************************************************************/

void reglage_PID (void)
{
    // PID VITESSE DISTANCE
    PID.VITESSE_DIS.KP = VITESSE_DIS_KP;
    PID.VITESSE_DIS.KI = VITESSE_DIS_KI;
    PID.VITESSE_DIS.KD = VITESSE_DIS_KD;

    // PID DISTANCE
    PID.DISTANCE.KP = POSITION_KP;
    PID.DISTANCE.KI = POSITION_KI;
    PID.DISTANCE.KD = POSITION_KD;

    // PID ORIENTATION
    PID.ORIENTATION.KP = ORIENTATION_KP;
    PID.ORIENTATION.KI = ORIENTATION_KI;
    PID.ORIENTATION.KD = ORIENTATION_KD;
    
    // PID BRAKE
    PID.BRAKE.KP = KP_BRAKE;
    PID.BRAKE.KI = KI_BRAKE;
    PID.BRAKE.KD = KD_BRAKE;
}

double fonction_PID (_enum_type_PID type)
{
    if (type == ASSERV_VITESSE_DISTANCE)
    {
        ERREUR_VITESSE[ROUE_DROITE].actuelle = VITESSE[ROUE_DROITE].consigne - VITESSE[ROUE_DROITE].actuelle;
        ERREUR_VITESSE[ROUE_DROITE].integralle += ERREUR_VITESSE[ROUE_DROITE].actuelle;      

        ERREUR_VITESSE[ROUE_GAUCHE].actuelle = VITESSE[ROUE_GAUCHE].consigne - VITESSE[ROUE_GAUCHE].actuelle;
        ERREUR_VITESSE[ROUE_GAUCHE].integralle += ERREUR_VITESSE[ROUE_GAUCHE].actuelle;

        saturation_erreur_integralle_vitesse();
        detection_blocage();

        COMMANDE.droit  = ERREUR_VITESSE[ROUE_DROITE].actuelle * PID.VITESSE_DIS.KP + ERREUR_VITESSE[ROUE_DROITE].integralle * PID.VITESSE_DIS.KI + (ERREUR_VITESSE[ROUE_DROITE].actuelle - ERREUR_VITESSE[ROUE_DROITE].precedente ) * PID.VITESSE_DIS.KD;
        COMMANDE.gauche = ERREUR_VITESSE[ROUE_GAUCHE].actuelle * PID.VITESSE_DIS.KP + ERREUR_VITESSE[ROUE_GAUCHE].integralle * PID.VITESSE_DIS.KI + (ERREUR_VITESSE[ROUE_GAUCHE].actuelle - ERREUR_VITESSE[ROUE_GAUCHE].precedente ) * PID.VITESSE_DIS.KD;

        ERREUR_VITESSE[ROUE_DROITE].precedente = ERREUR_VITESSE[ROUE_DROITE].actuelle;
        ERREUR_VITESSE[ROUE_GAUCHE].precedente = ERREUR_VITESSE[ROUE_GAUCHE].actuelle;
    }
    else if (type == ASSERV_POSITION)
    {
        __attribute__((near)) static double duty;

        ERREUR_DISTANCE.actuelle = DISTANCE.consigne - DISTANCE.actuelle;
        ERREUR_DISTANCE.integralle += ERREUR_DISTANCE.actuelle;

         duty =  ERREUR_DISTANCE.actuelle;// * PID.DISTANCE.KP  + ERREUR_DISTANCE.integralle * PID.DISTANCE.KI - (ERREUR_DISTANCE.actuelle - ERREUR_DISTANCE.precedente) * PID.DISTANCE.KD;
 
        ERREUR_DISTANCE.precedente = ERREUR_DISTANCE.actuelle;

        return duty;
    }
    else if ( type == ASSERV_ORIENTATION)
    {
        __attribute__((near)) static double duty;

        /*if ((ORIENTATION.consigne - ORIENTATION.actuelle) > Pi * ENTRAXE_TICKS/2)
            ORIENTATION.consigne -= Pi * ENTRAXE_TICKS;
        else if (ORIENTATION.consigne - ORIENTATION.actuelle < - Pi * ENTRAXE_TICKS/2)
            ORIENTATION.consigne += Pi * ENTRAXE_TICKS;*/
       /* while (ORIENTATION.consigne > Pi * ENTRAXE_TICKS/2)
            ORIENTATION.consigne -= Pi * ENTRAXE_TICKS;
        while (ORIENTATION.consigne < - Pi * ENTRAXE_TICKS/2)
            ORIENTATION.consigne += Pi * ENTRAXE_TICKS/2;*/


        ERREUR_ORIENTATION.actuelle = ORIENTATION.consigne - ORIENTATION.actuelle;

        while (ERREUR_ORIENTATION.actuelle > (Pi * ENTRAXE_TICKS/2.))
            ERREUR_ORIENTATION.actuelle -=  Pi * ENTRAXE_TICKS;
        while (ERREUR_ORIENTATION.actuelle < - Pi * ENTRAXE_TICKS/2.)
            ERREUR_ORIENTATION.actuelle +=  Pi * ENTRAXE_TICKS;

        ERREUR_ORIENTATION.integralle += ERREUR_ORIENTATION.actuelle;
        if (ERREUR_ORIENTATION.integralle > Pi * ENTRAXE_TICKS/2.)
            ERREUR_ORIENTATION.integralle = Pi * ENTRAXE_TICKS/2.;
        else if (ERREUR_ORIENTATION.integralle < -Pi * ENTRAXE_TICKS/2.)
            ERREUR_ORIENTATION.integralle  = -Pi * ENTRAXE_TICKS/2.;

         duty =  ERREUR_ORIENTATION.actuelle; // * PID.ORIENTATION.KP + ERREUR_ORIENTATION.integralle * PID.ORIENTATION.KI - (ERREUR_ORIENTATION.actuelle - ERREUR_ORIENTATION.precedente) * PID.ORIENTATION.KD;
        ERREUR_ORIENTATION.precedente = ERREUR_ORIENTATION.actuelle;

        return duty;

    }
    else if (type == KP_HYBRIDE)
    {
        if (ERREUR_ORIENTATION.actuelle > 0.)
            KP_hybride = ERREUR_ORIENTATION.actuelle / (Pi * (ENTRAXE_TICKS/2.));
        else
            KP_hybride = - ERREUR_ORIENTATION.actuelle / (Pi * (ENTRAXE_TICKS/2.));



        if (FLAG_ASSERV.type_deplacement == PASSE_PART)
        {
            if (FLAG_ASSERV.phase_deceleration_distance == PHASE_NORMAL)
            {
                #ifdef PETIT_ROBOT
                    KP_hybride *= 0.1; //0.2
                #else
                    KP_hybride *= 0.05;
                #endif
            }
                
        }

        KP_hybride = 1. - KP_hybride;
        
        VITESSE[SYS_ROBOT].theorique *= KP_hybride;
        //return KP_hybride;
    }

    return (double) 0;

}

/******************************************************************************/
/****************************** ODOMETRIE *************************************/
/******************************************************************************/

void calcul_position_robot (void)
{
    __attribute__((near)) static int32_t delta_o, delta_d;
    __attribute__((near)) static double d_X = 0., d_Y = 0.;

    get_valeur_codeur (CODEUR_D);
    get_valeur_codeur (CODEUR_G);

    POSITION[CODEUR_D].ecart *= COEF_D;
    POSITION[CODEUR_G].ecart *= COEF_G;

    //calcul des modifs
    delta_o = (POSITION[CODEUR_D].ecart - POSITION[CODEUR_G].ecart) /2.;
    delta_d = (POSITION[CODEUR_D].ecart + POSITION[CODEUR_G].ecart) /2.;

    if (FLAG_ASSERV.brake == ON)
    {
        BRAKE[ROUE_DROITE].actuelle -= POSITION[CODEUR_D].ecart;
        BRAKE[ROUE_GAUCHE].actuelle -= POSITION[CODEUR_G].ecart;
    }

    //cumul des valeurs pour l'asserv
    DISTANCE.actuelle += delta_d;

    VITESSE[SYS_ROBOT].actuelle = delta_d;
    VITESSE[ROUE_DROITE].actuelle = POSITION[CODEUR_D].ecart;
    VITESSE[ROUE_GAUCHE].actuelle = POSITION[CODEUR_G].ecart;

    VITESSE_ORIENTATION[SYS_ROBOT].actuelle = delta_o;

    ORIENTATION.actuelle += delta_o;

    //Angle compris entre - 180 et + 180
    if (ORIENTATION.actuelle > Pi * ENTRAXE_TICKS/2.)
        ORIENTATION.actuelle -= Pi * ENTRAXE_TICKS ;
    else if(ORIENTATION.actuelle < - Pi * (ENTRAXE_TICKS/2.))
        ORIENTATION.actuelle += Pi * ENTRAXE_TICKS;

    //Orientation en radian
    ROBOT.orientation = (double) ORIENTATION.actuelle / (ENTRAXE_TICKS / 2.);

    //Calcul des positions
    d_X = (double) cos (ROBOT.orientation) * delta_d;
    d_Y = (double) sin (ROBOT.orientation) * delta_d;

    X.actuelle += d_X;
    Y.actuelle += d_Y;

    //pas besoin de le calculer toutes les 5 ms --> perte de temps inutile
    ROBOT.X_mm += d_X * MM_PAR_TICKS;
    ROBOT.Y_mm += d_Y * MM_PAR_TICKS;
    ROBOT.orientation_degre = ROBOT.orientation * 180. / Pi;
}


