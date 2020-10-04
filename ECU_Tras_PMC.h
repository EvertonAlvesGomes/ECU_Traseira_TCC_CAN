/* ECU_Tras_PMC.h
 *  Configuração do Power Management Controller (PMC).
 *  Autor: Everton A. Gomes
 *  Data: 03/10/2020
*/

#ifndef _ECU_TRAS_PMC_H
#define _ECU_TRAS_PMC_H


//********************************************************************************
//                             #defines
//********************************************************************************

//Endereços de registradores:
#define PMC_PCER0                         0x400E0610        //PMC peripheral clock enable register 0
#define PMC_PCSR0                         0x400E0618        //PMC peripheral clock status register 0
#define PMC_PCER1                         0x400E0700        //PMC Peripheral Clock Enable Register 1
#define PMC_SR                            0x400E0688        //PMC Status Register

//********************************************************************************
//                             Registradores
//********************************************************************************

uint32_t *pPMC_PCER0 = (uint32_t*)(PMC_PCER0);
uint32_t *pPMC_PCSR0 = (uint32_t*)(PMC_PCSR0);
uint32_t *pPMC_PCER1 = (uint32_t*)(PMC_PCER1);
uint32_t *pPMC_SR    = (uint32_t*)(PMC_SR);


//********************************************************************************
//                             Registradores
//********************************************************************************

/*
 * ecu_tras_pmc_enable_periph_clock(uint8_t id)
 * Habilita o clock do periférico de PID (Peripheral ID) <pid>.
 */
void ecu_tras_pmc_enable_periph_clock(uint8_t id){
  *pPMC_PCER0 |= 1 << id;
}


#endif
