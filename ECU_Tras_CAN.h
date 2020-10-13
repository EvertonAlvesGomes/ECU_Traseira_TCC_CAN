/* ECU_Tras_CAN.h
 *  Implementação do CAN para ECU Traseira.
 *  Autor: Everton A. Gomes
 *  Data: 19/09/2020
*/

#ifndef _ECU_TRAS_CAN_H
#define _ECU_TRAS_CAN_H

//********************************************************************************
//                             #includes
//********************************************************************************

#include "D:\Documentos\CEFET-MG\Disciplinas\9 Periodo\TCC2\Projeto\Firmware\Final\CanCefast\CanCefast.h"

//********************************************************************************
//                             #defines
//********************************************************************************

//IDs das mensagens:
/*#define ID_MSG_1            0x2702      //pressD | tempD | velD
#define ID_MSG_2            0x3066        //pressT | tempT | rpm | velT
#define ID_MSG_3            0xEA27        //com*/

//IDs das mailboxes:
#define ID_MB_TX_A            ID_MSG_2      //ID mailbox tx A -> pressT | tempT | rpm | velT
#define ID_MB_TX_B            ID_MSG_3      //ID mailbox tx B -> comb
#define ID_MB_RX              ID_MSG_1      //ID mailbox rx   -> pressD | tempD | velD

//Índices das mailboxes: 0x00 a 0x07 para microcontroladores SAM3X8E
#define MB_TX_A_INDEX         0x00        //Índice Mailbox tx
#define MB_TX_B_INDEX         0x01        //Indice mailbox rx A
#define MB_RX_INDEX           0x02        //Indice mailbox rx B

//Masks para habilitar interrupção das mailboxes
#define ENABLE_MB0_INTERRUPT  (1 << 0)      //Habilita interrupção da mailbox 0
#define ENABLE_MB1_INTERRUPT  (1 << 1)      //Habilita interrupção da mailbox 1
#define ENABLE_MB2_INTERRUPT  (1 << 2)      //Habilita interrupção da mailbox 2
#define ENABLE_MB3_INTERRUPT  (1 << 3)      //Habilita interrupção da mailbox 3
#define ENABLE_MB4_INTERRUPT  (1 << 4)      //Habilita interrupção da mailbox 4
#define ENABLE_MB5_INTERRUPT  (1 << 5)      //Habilita interrupção da mailbox 5
#define ENABLE_MB7_INTERRUPT  (1 << 6)      //Habilita interrupção da mailbox 6
#define ENABLE_MB8_INTERRUPT  (1 << 7)      //Habilita interrupção da mailbox 7


//********************************************************************************
//                             Variáveis
//********************************************************************************

//Variáveis de monitoramento
uint8_t send_status_a, send_status_b, rec_status;
uint32_t can_sr=0;    //variável para leitura do registrador de status do CAN

//Mailboxes:
can_mb_conf_t can_mailbox_tx_a;                //mailbox tx_a
can_mb_conf_t can_mailbox_tx_b;                //mailbox tx_b
can_mb_conf_t can_mailbox_rx;                  //mailbox rx


//********************************************************************************
//                             Funções
//********************************************************************************

/* uint32_t joinToSend
 *  Agrupa duas variaveis de 16 bits em uma de 32 bits e retorna o valor desta variavel
*/
uint32_t joinToSend(uint16_t var_2, uint16_t var_1){
  uint32_t retval;
  retval = (uint32_t)(var_2);
  retval = (retval << 16) | (var_1);
  return retval;
}

/* uint16_t splitToRead
 *  Seleciona o dado nos registradores de dados das mailboxes de recepcao.
 *  uint8_t pos = varia de 0 a 2 e indica qual dado deve ser selecionado
*/
uint16_t splitToRead(uint8_t pos){
  uint16_t retval;

  switch(pos) {
    //case 0 -> velocidade dianteira
    case 0 : {
      retval = ((can_mailbox_rx.ul_datal) & (0x0000FFFF));
      break;
    }
    //case 1 -> temperatura dianteira
    case 1 : {
      retval = (uint16_t)((can_mailbox_rx.ul_datal & 0xFFFF0000) >> 16);
      break;
    }
    //case 2 ->pressão dianteira
    case 2 : {
      retval = ((can_mailbox_rx.ul_datah) & (0x0000FFFF));
      break;
    }
  }
  return retval;
  
}


void data_monitoring(){
  //Dados enviados:
  Serial.print("MB_TX_A: ");
  Serial.println(send_status_a);
  Serial.print("MB_TX_B: ");
  Serial.println(send_status_b);

  //Dados recebidos:
  Serial.print("VD: ");
  Serial.println(splitToRead(0));
  Serial.print("TEMPD: ");
  Serial.println(splitToRead(1));
  Serial.print("PRESSD: ");
  Serial.println(splitToRead(2));
  Serial.println("");

}

void can_monitoring(){
  //Mailbox de transmissão:
  Serial.print("MB_TX_A: ");
  Serial.print(can_mailbox_tx_a.ul_datah, HEX);
  Serial.print(" ");
  Serial.println(can_mailbox_tx_a.ul_datal, HEX);
  Serial.print("MB_TX_B: ");
  Serial.print(can_mailbox_tx_b.ul_datah, HEX);
  Serial.print(" ");
  Serial.println(can_mailbox_tx_a.ul_datal, HEX);

  //Mailboxes de recepção:
  Serial.print("MB_RX: ");
  Serial.print(can_mailbox_rx.ul_datah, HEX);
  Serial.print(" ");
  Serial.println(can_mailbox_rx.ul_datal, HEX);
  Serial.println("");
}

void canStatus(){
  Serial.println(*pCAN_SR, HEX);
}


#endif
