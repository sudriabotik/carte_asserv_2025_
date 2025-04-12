/* 
 * File:   serialusM2M.h
 * Author: AJREI
 *
 * Created on September 4, 2023, 4:54 PM
 */

// serialusM2M.h

#ifndef SERIALUS_M2M_H
#define SERIALUS_M2M_H

#include <stdint.h>
#include <stdbool.h>
#include "system.h"

#define BUFFER_SIZE 512 //

typedef struct {
    bool clignotement_en_cours;
    char buffer[BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    bool carriageReturnReceived;
    
} SerialusM2M;

extern SerialusM2M serialusM2M;

void serialusM2M_init();
void serialusM2M_receive();
void serialusM2M_process();
void reset_rx_Buffer();
void reset_overflow_error();


void print_pos();

void calageX();
void calageY();
void calageALL();

void set_Break();

bool sontdesdigits(const char* str);
void InitPosM2M();
void ori();
void cib();
void av();
void rec();
void rej();
void passe_par();
void print_erreur_deplacementM2M(_enum_erreur_asserv erreur);
void erreur_deplacementM2M(_enum_erreur_asserv erreur);

void init_clignotement();

void calcul_var_odom_asserv();
void DEBUG_ON();
void DEBUG_OFF();
void reset_asserve();
void reset_VITESSE_CONSIGNE_MAX_MM();
void reset_VITESSE_DISTANCE_MIN();
void reset_VITESSE_MAX_MM_TENSION();
void reset_DISTANCE_CONSIGNE_MM();
void reset_VITESSE_ANGLE_MAX();
void reset_VITESSE_ANGLE_MIN();
void reset_ORIENTATION_CONSIGNE_DEG();
void reset_PID_Vitesse();
void reset_PID_Break();
void reset_ENTRAXE_MM();
void reset_DIAMETRE_ROUE_CODEUSE();
void reset_PERIMETRE_ROUE_MM();
void reset_coef_D();
void reset_coef_G();
void set_ENTRAXE_MM();
void set_DIAMETRE_ROUE_CODEUSE();
void set_PERIMETRE_ROUE_MM();
void set_coef_D();
void set_coef_G();
void set_PID_Vitesse();
void set_PID_Break();
void set_MAX_ERREUR_INTEGRALLE_V();
void set_MAX_E_INTEGRALLE_BRAKE();
void set_SEUIL_IMMOBILITE();
void set_VITESSE_CONSIGNE_MAX_MM();
void set_VITESSE_DISTANCE_MIN();
void set_VITESSE_MAX_MM_TENSION();
void set_DISTANCE_CONSIGNE_MM();
void set_VITESSE_ANGLE_MAX();
void set_VITESSE_ANGLE_MIN();
void set_ORIENTATION_CONSIGNE_DEG();
void set_ACC_ORIENTATION_CONSIGNE();
void set_DCC_ORIENTATION_CONSIGNE();
void set_ACC_ORIENTATION_MIN();
void set_DCC_ORIENTATION_MIN();
void set_ACC_POSITION_CONSIGNE();
void set_DCC_POSITION_CONSIGNE();
void set_ACC_POSITION_MIN();
void set_DCC_POSITION_MIN();



void AX_set_ang();
void AX_set_pos();
void AX_set_led();
void AX_set_torque();
void AX_set_alim();

void AX_get_pos();
void AX_get_ping();

int16_t check_id_ax12_m2m(int16_t id);
void print_ping(uint8_t id);
void print_position_ax12(uint8_t id, int16_t position);
void print_erreur_ax12();
        
void get_couleur();
void set_couleur();

void Check_evitment();
void Evitement_on_off();
void set_evitment();
void start_match();
// Add other function declarations...


#endif
