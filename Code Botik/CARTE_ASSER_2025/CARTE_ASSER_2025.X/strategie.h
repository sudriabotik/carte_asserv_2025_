// strategie.h

#ifndef STRATEGIE_H
#define STRATEGIE_H

#include "system.h"

void tour_de_table();
uint8_t recup_plante4_ou_1(bool test, _enum_strategies STRATEGIE);
uint8_t recup_plante5_ou_2(bool test, _enum_strategies STRATEGIE);
uint8_t recup_plante5_ou_2_alt(bool test, _enum_strategies STRATEGIE, double x_target, double y_target, double x_evitement);
uint8_t depose_zone_depart_strat1(bool test);
uint8_t depose_zone_depart_strat2(bool test);
uint8_t depose_jardiniere1(bool test, _enum_strategies STRATEGIE);
uint8_t recup_plante3(bool test, bool use_bras, _enum_strategies STRATEGIE);
uint8_t depose_jardiniere2(bool test, _enum_strategies STRATEGIE);
uint8_t depose_zone_reservee(bool test, _enum_strategies STRATEGIE);
uint8_t depose_zone_reservee_alt(bool test, _enum_strategies STRATEGIE);
uint8_t depose_jardiniere3(bool test, _enum_strategies STRATEGIE);
uint8_t activation_panneaux_solaires(bool test, _enum_strategies STRATEGIE);
uint8_t retour_zone_recharge(bool test, _enum_strategies STRATEGIE);

#endif
