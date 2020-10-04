/* ECU_Trasei.ino
 *  Firmware da ECU Traseira do projeto CAN desenvolvido para a equipe CEFAST Baja.
 *  Autor: Everton A. Gomes
 *  Data: 19/09/2020
*/



//********************************************************************************
//                             #includes
//********************************************************************************

#include "ECU_Tras_Defines.h"
#include "ECU_Tras_CAN.h"
#include "ECU_Tras_SensPressao.h"
#include "ECU_Tras_SensVelocidade.h"
#include "ECU_Tras_CAN_Deploying.h"
#include "ECU_Tras_Peripheral_Deploying.h"
#include "ECU_Tras_Comb.h"


//********************************************************************************
//                             Variáveis
//********************************************************************************

uint16_t velT = 0;      //velocidade Traseira
uint16_t tempT = 0 ;    //temperatura disco Traseiro
float pressT = 0;       //pressão freio Traseiro
uint16_t rpm = 0;       //rpm
uint16_t comb = 0;      //combustível

uint8_t tick = 0;       //temporizador de inicialização do CAN



void setup(){
  #ifdef ENABLE_SERIAL_COMMUNICATION
    Serial.begin(9600);
  #endif

  //Configura medição das grandezas se PERIPHERAL_COMMUNICATION estiver habilitado
  #ifdef ENABLE_PERIPHERAL_COMMUNICATION 
    velocidade_meas_config();     //configura medição de velocidade
    sens_pressao_meas_config();   //configura medição de pressão
    ecu_tras_comb_config_input_pins();
  #endif

  #ifdef ENABLE_CAN_COMMUNICATION
    startCan();   //inicializa interface CAN
    
    canConfigMailboxTx(&can_mailbox_tx_a, MB_TX_A_INDEX);       //configura mailbox tx
    canConfigMailboxTx(&can_mailbox_tx_b, MB_TX_B_INDEX);       //configura mailbox rx
    canConfigMailboxRx(&can_mailbox_rx, MB_RX_INDEX, ID_MB_RX); //configura mailbox rx 

    //Aguarda inicialização do CAN
    while(!(*pCAN_SR & (1 << 21))){
      tick++;
      if(tick >= TIMEOUT_CAN){
        #ifdef ENABLE_SERIAL_COMMUNICATION
          Serial.println("Falha na inicialização do CAN.\n");
        #endif
        return;
      }
    }
    #ifdef ENABLE_SERIAL_COMMUNICATION
      Serial.println("CAN Inicializado.\n\n");
    #endif

    can_enable_interrupts(ENABLE_MB2_INTERRUPT); //habilita apenas interrupção da mailbox 2, usada para recepção
  #endif
  
}

void loop(){
  #ifdef ENABLE_CAN_COMMUNICATION
    tick = 0; //reinicia temporizador

    //Se o CAN_DEPLOYING estiver habilitado, usam-se valores aleatórios para as grandezas medidas
    #ifdef ENABLE_CAN_DEPLOYING
      velT = velocidade_tras[random(0,100)];
      rpm = Rpm[random(0,20)];
      tempT = temp_tras[random(0,100)];
      pressT = pressao_tras[random(0,10)];
      comb = combustivel[random(0,6)];
    #endif

    //Se CAN_DEPLOYING não estiver habilitado, usam-se valores calculados pelos periféricos para as grandezas medidas
    #ifndef ENABLE_CAN_DEPLOYING
      velT = calcula_velocidade();
      rpm = Rpm[random(0,20)];
      tempT = temp_tras[random(0,100)];
      pressT = calcula_pressao();

    #endif

    //Envio das mensagens CAN
    send_status_a = canSend(&can_mailbox_tx_a, ID_MB_TX_A, joinToSend(pressT,tempT), joinToSend(rpm,velT));
    can_global_send_transfer_cmd(CAN0, (0x1u << MB_TX_A_INDEX));
    send_status_b = canSend(&can_mailbox_tx_b, ID_MB_TX_B, joinToSend(0,0), joinToSend(0,comb));
    can_global_send_transfer_cmd(CAN0, (0x1u << MB_TX_B_INDEX));

    //Se a comunicação serial estiver habilitada, os dados são escritos na serial
    #ifdef ENABLE_SERIAL_COMMUNICATION
      can_monitoring();
      //data_monitoring();
    #endif
    
  #endif

  #ifdef ENABLE_PERIPHERAL_DEPLOYING
    //Leitura dos periféricos
    #ifdef ENABLE_SERIAL_COMMUNICATION
      /*Serial.println(ler_adc(), HEX);
      Serial.println(ler_timer_0_counter(), HEX);
      Serial.println(ler_timer_0_status(), HEX);*/
      //Serial.println(*pPIOC_PDSR, HEX);
      Serial.println(ecu_tras_comb_calcula_nivel());
    #endif

  #endif
  
}



//********************************************************************************
//                             ISRs
//********************************************************************************

//Timer0_ISR:
void TC0_Handler(void){
  ra_atual = captureRA(); //leitura do registrador RA
  tc_sr = *pTC_SR0; //leitura do registrador de status para permitir o processador retornara pra thread mode
}


//CAN_ISR: utilizada apenas para mailboxes de recepção
void CAN0_Handler(void){

  //RX mailbox
  if((*pCAN_MSR_2 & 0xFFFFFF) >> 23){
    rec_status = can_mailbox_read(CAN0, &can_mailbox_rx); //pressD | tempD | velD
  }
  
  can_sr = *pCAN_SR; //leitura do registrador de status (libera thread mode)
}
