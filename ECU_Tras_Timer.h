/* ECU_Tras_Timer.h
 *  Implementação dos timers em modo de captura, destinados à medição de velocidade.
 *  Autor: Everton A. Gomes
 *  Data: 19/09/2020
*/

#ifndef _ECU_TRAS_TIMER_H
#define _ECU_TRAS_TIMER_H


//********************************************************************************
//                             #includes
//********************************************************************************


#include "ECU_Tras_PMC.h"
#include "ECU_Tras_PIO.h"


//********************************************************************************
//                             #defines
//********************************************************************************

#define TC0_ID        27  //ID do periférico
#define TC1_ID        28  //ID do periférico
#define TC2_ID        29  //ID do periférico
#define CLKEN         0x01 << 0   //bit CLEN no registrador TC_CCRx
#define CAPT          0x00 << 15  //bit ~WAVE (Capture Mode) no TC_CMRx
#define TIMER_CLOCK1  0           //Clock interno MCK/2
#define TIMER_CLOCK2  1           //Clock interno MCK/8
#define TIMER_CLOCK3  2           //Clock interno MCK/32
#define TIMER_CLOCK4  3           //Clock interno MCK/128
#define TCCLKS        0           //Posição do bit TCCLKS no registrador TC_CMRx
#define WPKEY         0x54494D    //PASSWD for Write Protection
#define TC2_BASE_ADDRESS 0x40088000
#define TC2_CHANNEL   1           //Canal do timer utilizado
#define LDRA_RISING   1 << 16


//********************************************************************************
//                             Registradores
//********************************************************************************

//Registradores - Timer_0:
#define TC_CCR0   0x40080000  //TC Channel Control Register
#define TC_CMR0   0x40080004  //TC Channel Mode Register
#define TC_CV0    0x40080010  //TC Counter Value Register
#define TC_RA0    0x40080014  //TC Register A
#define TC_RB0    0x40080018  //TC Register B
#define TC_RC0    0x4008001C  //TC Register C
#define TC_SR0    0x40080020  //TC Status Register
#define TC_IER0   0x40080024  //TC Interrupt Enable Register
#define TC_IDR0   0x40080028  //TC Interrupt Disable Register
#define TC_IMR0   0x4008002C  //TC Interrupt Mask Register
#define TC_WPMR0  0x400800E4  //TC Write Protection Mode Register

//Registradores - Timer 2, canal 1 (TIOA7)
#define TC2_CCR1  (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x00)   //TC2 Channel Control Register
#define TC2_CMR1  (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x04)   //TC2 Channel Mode Register
#define TC2_CV1   (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x10)   //TC2 Counter Value
#define TC2_RA1   (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x14)   //TC2 Register A
#define TC2_RB1   (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x18)   //TC2 Register B
#define TC2_RC1   (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x1C)   //TC2 Register C
#define TC2_SR1   (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x20)   //TC2 Status Register
#define TC2_IER1  (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x24)   //TC2 Interrupt Enable Register
#define TC2_IDR1  (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x28)   //TC2 Interrupt Disable Regiser
#define TC2_IMR1  (TC2_BASE_ADDRESS + TC2_CHANNEL*0x40 + 0x2C)   //TC2 Interrupt Mask Register
#define TC2_WPMR  0x400880E4                          //TC Write Protection Mode Register


//Registradores - Power Management Controller (PMC)
#define PMC_PCER0 0x400E0610  //PMC Peripheral Clock Enable Register 0
#define PMC_PCER1 0x400E0700  //PMC Peripheral Clock Enable Register 1
#define PMC_SR    0x400E0688  //PMC Status Register
#define PMC_PCSR0 0x400E0618  //PMC Peripheral Clock Status Register 0

//Registradores - PIO Controller
#define PIOA_PDR  0x400E0E04  //PIO Controller PIOA Disable Register
#define PIOA_ABSR 0x400E0E70  //PIO Peripheral PIOB AB Select Register
#define PIOA_ODR  0x400E0E14  //PIO Controller Output Disable Register
#define PIOB_PDR  0x400E1004  //PIO Controller PIOB Disable Register
#define PIOB_ABSR 0x400E1070  //PIO Peripheral PIOB AB Select Register
#define PIOB_ODR  0x400E1014  //PIO Controller Output Disable Register

//***********************************************************************//

//Ponteiros de registradores - Timer_0
uint32_t *pTC_CCR0 = (uint32_t*)(TC_CCR0);
uint32_t *pTC_CMR0 = (uint32_t*)(TC_CMR0);
uint32_t *pTC_CV0 = (uint32_t*)(TC_CV0);
uint32_t *pTC_RA0 = (uint32_t*)(TC_RA0);
uint32_t *pTC_RB0 = (uint32_t*)(TC_RB0);
uint32_t *pTC_RC0 = (uint32_t*)(TC_RC0);
uint32_t *pTC_SR0 = (uint32_t*)(TC_SR0);
uint32_t *pTC_IMR0 = (uint32_t*)(TC_IMR0);
uint32_t *pTC_IER0 = (uint32_t*)(TC_IER0);
uint32_t *pTC_IDR0 = (uint32_t*)(TC_IDR0);
uint32_t *pTC_BCR = (uint32_t*)(0x400800C0);
uint32_t *pTC_WPMR0 = (uint32_t*)(TC_WPMR0);

uint32_t *pTC_CCR1 = (uint32_t*)(0x40080040);
uint32_t *pTC_CMR1 = (uint32_t*)(0x40080044);
uint32_t *pTC_CV1 = (uint32_t*)(0x40080050);
uint32_t *pTC_SR1 = (uint32_t*)(0x40080060);

//Ponteiros de registradores - Timer 1
uint32_t *pTC1_CCR0 = (uint32_t*)(0x40084000);
uint32_t *pTC1_BCR = (uint32_t*)(0x400840C0);
uint32_t *pTC1_SR0 = (uint32_t*)(0x40084020);

//Ponteiros de registradores - Timer_2
uint32_t *pTC2_CCR0 = (uint32_t*)(0x40088000);
uint32_t *pTC2_SR0 = (uint32_t*)(0x40084020);
uint32_t *pTC2_CCR1 = (uint32_t*)(TC2_CCR1);
uint32_t *pTC2_CMR1 = (uint32_t*)(TC2_CMR1);
uint32_t *pTC2_CV1 = (uint32_t*)(TC2_CV1);
uint32_t *pTC2_RA1 = (uint32_t*)(TC2_RA1);
uint32_t *pTC2_RB1 = (uint32_t*)(TC2_RB1);
uint32_t *pTC2_RC1 = (uint32_t*)(TC2_RC1);
uint32_t *pTC2_SR1 = (uint32_t*)(TC2_SR1);
uint32_t *pTC2_IMR1 = (uint32_t*)(TC2_IMR1);
uint32_t *pTC2_IER1 = (uint32_t*)(TC2_IER1);
uint32_t *pTC2_IDR1 = (uint32_t*)(TC2_IDR1);
uint32_t *pTC2_BCR = (uint32_t*)(0x400880C0);
uint32_t *pTC2_WPMR = (uint32_t*)(TC2_WPMR);

uint32_t *pPIOB_ABSR = (uint32_t*)(PIOB_ABSR);
uint32_t *pPIOB_ODR = (uint32_t*)(PIOB_ODR);



//********************************************************************************
//                             Variáveis
//********************************************************************************

uint32_t raValue = 0, rbValue = 0; //variáveis de leitura dos registradores RA e RB


//********************************************************************************
//                             Funções
//********************************************************************************

void unableWriteProtection_timer0(){
  //Timer 0:
  *pTC_WPMR0 |= (WPKEY << 8); //insere a chave de proteção de escrita
  *pTC_WPMR0 &= ~(0x01 << 0); //desabilita a proteção de escrita
}

void unableWriteProtection_timer2(){
  //Timer 2:
  
  *pTC2_WPMR |= (WPKEY << 8); //insere a chave de proteção de escrita
  *pTC2_WPMR &= ~(0x01 << 0); //desabilita a proteção de escrita
}

/* void pioConfig()
 *  Configuração do pino de entrada do sinal (PB25)
*/
void pioConfig(){
  
  //Configuração de portas I/O para o timer 0
  
  *pPIOB_PDR |= 0x01 << 25; //Habilita o pino PB25 (pino digital 2) para ser controlado pelo periférico (Timer0)
  *pPIOB_ABSR |= 0x01 << 25; //Configura o pino PB25 para a função periférica B
  *pPIOB_ODR |= 0x01 << 25; //Configura o pino como entrada
}


/* void enablePMCclock(uint8_t id)
 *  Habililta o clock do periférico pelo PMC (Power Management Controller), sendo "id" o ID
 *  do periférico.
*/
void enablePMCclock(uint8_t id){
  if(id <= 31)
    *pPMC_PCER0 |= 0x01 << id;  //habilita o clock pelo registrador PMC_PCER0 se o ID for até 31
  else
    if(id >= 32 && id <= 44)
      *pPMC_PCER1 |= 0x01 << id; //habilita o clock pelo registrador PMC_PCER0 se o ID for de 32 até 44
}


/* void tc0config()
 *  Configuração do Timer_0
*/
void tc0config(){
  //*pPMC_PCER0 |= TC0_ID; //habilita o clock do Timer Counter 0 no controlador PMC
  enablePMCclock(TC0_ID);
  pioConfig(); //configura pino de entrada do sinal
  
  //Configurando canal 0:
  *pTC_CCR0 |= CLKEN; //seta o bit CLKEN para habilitar o clock
  *pTC_CCR0 |= 0x01 << 2; //software trigger
  unableWriteProtection_timer0();
  *pTC_CMR0 |= CAPT; //configura o TC para modo waveform
  *pTC_CMR0 |= TIMER_CLOCK1 << TCCLKS; //seleciona prescaler

  //Configurando interrupção para leitura do sinal:
  NVIC_EnableIRQ(TC0_IRQn); //habilita interrupção do timer0
  NVIC_SetPriority(TC0_IRQn, 14); //configura nível de prioridade
  *pTC_IER0 |= 1 << 5; //Habilitando interrupção por RA loading
  *pTC_IDR0 &= ~(1 << 5); //apaga o bit que desabilita a interrupção por RA loading - canal 0
}

/* void captureConfig()
 *  Configuração do modo de captura. O registrador RA é carregado em nível alto,
 *  enquanto RB é carregado em nível baixo.
*/
void captureConfig(){
  //Timer_0
  *pTC_CMR0 |= 0x01 << 16; //RA é carregado quando é detectada uma borda de subida no sinal em TIOA
  *pTC_CMR0 |= 0x02 << 18; //RB é carregado quando é detectada uma borda de descida no sinal em TIOA
  *pTC_CMR1 |= 0x01 << 16; //RA é carregado quando é detectada uma borda de subida no sinal em TIOA
  *pTC_CMR1 |= 0x02 << 18; //RB é carregado quando é detectada uma borda de descida no sinal em TIOA  
}


void ecu_tras_timer_timer2_config(){
  ecu_tras_pmc_enable_periph_clock(TC2_ID);   //habilita o clock do timer 2
  
  ecu_tras_pioc_disable_pio_controlling(28);
  ecu_tras_pioc_select_peripheral('B', 28);
  ecu_tras_pioc_config_input(28);
  
  *pTC2_CCR0 = 5;
  unableWriteProtection_timer2();
  *pTC2_CCR1 = 5;
  *pTC2_BCR = 1;
  
  *pTC2_CMR1 |= CAPT; //configura o TC para modo captura
  *pTC2_CMR1 |= TIMER_CLOCK3 << TCCLKS; //seleciona prescaler
  *pTC2_CMR1 |= LDRA_RISING;

  //Configurando interrupção para leitura do sinal:
//  NVIC_EnableIRQ(TC2_IRQn); //habilita interrupção do timer 2
//  NVIC_SetPriority(TC2_IRQn, 15); //configura nível de prioridade
//  *pTC2_IER1 |= 1 << 5; //Habilitando interrupção por RA loading
//  *pTC2_IDR1 &= ~(1 << 5); //apaga o bit que desabilita a interrupção por RA loading - canal 0
}

void ecu_tras_timer_enable_all_timers(){
  //Enable PMC clock
  ecu_tras_pmc_enable_periph_clock(TC0_ID);
  ecu_tras_pmc_enable_periph_clock(TC1_ID);
  ecu_tras_pmc_enable_periph_clock(TC2_ID);

  //Activate clock:
  *pTC_CCR0 |= 1;
  *pTC1_CCR0 |= 1;
  *pTC2_CCR0 |= 1;

  //Restart clock by software trigger:
  *pTC_BCR = 1;
  *pTC1_BCR = 1;
  *pTC2_BCR = 1;
}

/* void captureRA()
 *  Retorna o valor de RA.
*/
uint32_t captureRA(){
  return *pTC_RA0;
}


uint32_t ecu_tras_timer_capture_ra_value(uint8_t timer_index){
  switch(timer_index){
    case 0 : return *pTC_RA0;
    case 2 : return *pTC2_RA1;
  }
}

uint32_t ecu_tras_timer_get_status(uint8_t timer_index){
    switch(timer_index){
      case 0 : return *pTC_SR0;
      case 2 : return *pTC2_SR1;
    }
}


#endif
