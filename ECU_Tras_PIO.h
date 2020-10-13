/* ECU_Tras_PIO.h
 *  Configuração das portas I/O do microcontrolador para funcionamento dos periféricos e sensores.
 *  Autor: Everton A. Gomes
 *  Data: 03/10/2020
*/

#ifndef _ECU_TRAS_PIO_H
#define _ECU_TRAS_PIO_H


//********************************************************************************
//                             #includes
//********************************************************************************

#include "ECU_Tras_PMC.h"

//********************************************************************************
//                             #defines
//********************************************************************************

//Defines gerais:
#define PIOC_PID                          13                //PIO C peripheral identifier

//Endereços de registradores:

#define PIOA_PDR                          REG_PIOA_PDR      //PIO A Disable Register

#define PIOB_PER                          0x400E1000        //PIO B enable register
#define PIOB_PDR                          0x400E1004        //PIO B disable register

#define PIOC_PER                          0x400E1200        //PIO C enable register
#define PIOC_PDR                          0x400E1204        //PIO C disable register
#define PIOC_PSR                          0x400E1208        //PIO C status register
#define PIOC_ODR                          0x400E1214        //PIO C output disable register
#define PIOC_PUDR                         0x400E1260        //PIO C Pull up disable register
#define PIOC_PUER                         0x400E1264        //PIO C Pull up enable register
#define PIOC_PUSR                         0x400E1268        //PIO C Pull up status register
#define PIOC_PDSR                         0x400E123C        //PIO C data status register
#define PIOC_ABSR                         0x400E1270        //PIO C peripheral AB select register
#define PIOC_IER                          0x400E1240        //PIO C interrupt enable register
#define PIOC_IMR                          0x400E1248        //PIO C interrupt mask register
#define PIOC_ISR                          0x400E124C        //PIO C interrupt status register


//********************************************************************************
//                             Registradores
//********************************************************************************

uint32_t *pPIOB_PDR = (uint32_t*)(PIOB_PDR);

uint32_t *pPIOC_PER = (uint32_t*)(PIOC_PER);
uint32_t *pPIOC_PDR = (uint32_t*)(PIOC_PDR);
uint32_t *pPIOC_PSR = (uint32_t*)(PIOC_PSR);
uint32_t *pPIOC_ODR = (uint32_t*)(PIOC_ODR);
uint32_t *pPIOC_PUDR = (uint32_t*)(PIOC_PUDR);
uint32_t *pPIOC_PUER = (uint32_t*)(PIOC_PUER);
uint32_t *pPIOC_PUSR = (uint32_t*)(PIOC_PUSR);
uint32_t *pPIOC_PDSR = (uint32_t*)(PIOC_PDSR);
uint32_t *pPIOC_ABSR = (uint32_t*)(PIOC_ABSR);
uint32_t *pPIOC_IER = (uint32_t*)(PIOC_IER);
uint32_t *pPIOC_IMR = (uint32_t*)(PIOC_IMR);
uint32_t *pPIOC_ISR = (uint32_t*)(PIOC_ISR);


//********************************************************************************
//                             Funções
//********************************************************************************


void ecu_tras_pio_init(){
  ecu_tras_pmc_enable_periph_clock(PIOC_PID);
}

/* ecu_tras_pioa_disable_pin_controlling(uint8_t pin)
 *  Desabilita o controlador PIOA controlar o pino "pin", habilitando o controle de periféricos sobre esse pino.
*/
void ecu_tras_pioa_disable_pin_controlling(uint8_t pin){
  PIOA_PDR |= 1 << pin;
}


/* ecu_tras_piob_disable_pin_controlling(uint8_t pin)
 *  Desabilita o controlador PIOB controlar o pino "pin", habilitando o controle de periféricos sobre esse pino.
*/
void ecu_tras_piob_disable_pin_controlling(uint8_t pin){
  *pPIOB_PDR |= 1 << pin;
}

/* ecu_tras_pio_enable_pin_controlling(uint8_t pin)
 *  Habilita o controlador PIO controlar o pino "pin", desabilitando o controle de periféricos sobre esse pino.
*/
void ecu_tras_pioc_enable_pin_controlling(uint8_t pin){
  *pPIOC_PER |= 1 << pin;
}


void ecu_tras_pioc_disable_pio_controlling(uint8_t pin){
  *pPIOC_PDR |= 1 << pin;
}

/* ecu_tras_pio_config_input(uint8_t pin)
 *  Configura o pino <pin> com entrada.
*/
void ecu_tras_pioc_config_input(uint8_t pin){
  *pPIOC_ODR |= 1 << pin;
}


void ecu_tras_pioc_select_peripheral(char periph, uint8_t pin){
  if(periph == 'A' || periph == 'a'){
    *pPIOC_ABSR &= ~(1 << pin);   //apaga o bit, configurando o pino para a função periférica A
  }
  if(periph == 'B' || periph == 'b'){
    *pPIOC_ABSR |= 1 << pin;  //seta o bit, configurando o pino para a função periférica B
  }
}


/* pio_enable_pin_controlling(uint8_t pin)
 *  Habilita o resistor pull-up interno do pino "pin".
*/
void ecu_tras_pio_enable_pullup_resistor(uint8_t pin){
  *pPIOC_PUER |= 1 << pin;
}

/* ecu_tras_pioc_enable_interrupt_pin(uint8_t pin)
 * Habilita interrupção do pino <pin>.
 */
void ecu_tras_pioc_enable_interrupt_pin(uint8_t pin){
  *pPIOC_IER |= 1 << pin;
}

void ecu_tras_pioc_interrupt_enable(uint8_t prior){
  NVIC_EnableIRQ(PIOC_IRQn); //habilita interrupção do timer0
  NVIC_SetPriority(PIOC_IRQn, prior); //configura nível de prioridade
}

/*
 * ecu_tras_pio_read_all_pins()
 * Reads all pin status (LOW = 0, HIGH = 1).
 */
uint8_t ecu_tras_pio_read_all_pins(){
  uint32_t pin_levels = *pPIOC_PDSR;
  return pin_levels;
}


uint8_t ecu_tras_pioc_read_pin(uint8_t pin){
  return (*pPIOC_PDSR & (1 << pin)) >> pin;
}

/*
 * ecu_tras_pio_read_pin(uint8_t pin)
 * Reads pin status (LOW = 0, HIGH = 1).
 */
uint8_t ecu_tras_pio_read_pin(uint8_t pin){
  uint32_t pin_levels = *pPIOC_PDSR;
  return ( ( pin_levels & ( 1 << pin )) >> pin );
}



#endif
