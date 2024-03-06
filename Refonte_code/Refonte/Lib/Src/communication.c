/*
 * communication.c
 *
 *  Created on: Feb 14, 2024
 *      Author: smore
 */


#include "main.h"
#include "../Inc/communication.h"

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart2;

extern int effect_led;
extern bool uart2_irq_is_captured;
extern bool uart5_irq_is_captured;

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

uint8_t rx_buffer_uart2[MSG_SIZE_UART2];
uint8_t tx_buffer_uart2[MSG_SIZE_UART2];
uint8_t rx_buffer_uart5[MSG_SIZE_UART5];
uint8_t tx_buffer_uart5[MSG_SIZE_UART5];
uint8_t checksum = 0;
uint8_t msg_size = 0;
uint8_t msg_size_reception = 0;

void uart_init(UART_HandleTypeDef * uart){
	memset(rx_buffer_uart2, 0, MSG_SIZE_UART2);
	memset(tx_buffer_uart2, 0, MSG_SIZE_UART2);
	memset(rx_buffer_uart5, 0, MSG_SIZE_UART5);
	memset(tx_buffer_uart5, 0, MSG_SIZE_UART5);

	__HAL_UART_DISABLE(uart);
	__HAL_UART_ENABLE(uart);
	HAL_UART_Receive_IT(uart, rx_buffer_uart2, MSG_SIZE_UART2);//START_IT UART2
}

void reception(UART_HandleTypeDef * uart){
	__HAL_UART_DISABLE_IT(uart,  UART_IT_RXNE);  // Disable UART2 RX interrupt
	parser();
	memset(rx_buffer_uart2, 0, MSG_SIZE_UART2);
	__HAL_UART_ENABLE_IT(uart, UART_IT_RXNE);  // Enable UAR2T RX interrupt
	HAL_UART_Receive_IT(uart, rx_buffer_uart2, MSG_SIZE_UART2);
}

void parser()
{
	if(check_msg_identifier())
	{
		if (robot_uid()){
			if(check_checksum_rx()){
				uint8_t actionneur = rx_buffer_uart2[POS_ACT];
				uint8_t msg_type = rx_buffer_uart2[POS_MSG_TYPE];
				switch (actionneur){
					case ARM :
						switch (msg_type){
							case ACK :
								break;
							case READ_ENCODER_POSITION :
								msg_size = 3;
								msg_size_reception = 8 ;
								break;
							case NB_OF_PULSE :
								msg_size = 3;
								break;
							case READ_ERROR_MOTOR_ANGLE :
								msg_size = 3;
								break;
							case EN_Pin_STATUS :
								msg_size = 3;
								break;
							case MOTOR_SHAFT_LOCKED_ROTOR :
								msg_size = 3;
								break;
							case MOTOR_SHAFT_PROTECTION_STATE :
								msg_size = 3;
								break;
							case CALIBRATE_THE_ENCODER :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = 0x00;
								break;
							case MOT_TYPE :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case MODE :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
							case MA :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case MSTEP :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case EN_PIN__COMMAND :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case DIRECTION :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case AUTO_SSD :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case LOCKED__MOTOR :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case SUBDIVISION_INTERPOLATION_APP :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case BAUDRATE_APP :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case UARTADDR:
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case RESTORE_DEFAULT_PARAMETRE :
								msg_size = 3;
								break;
							case ZERO_MOD :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case SET_ZERO :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = 0x00;
								break;
							case SPEED_ZERO :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case DIR_ZERO :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case GO_TO_0 :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = 0x00;
								break;
							case PID_KP :
								msg_size = 5;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								tx_buffer_uart5[POS_ACT] = rx_buffer_uart2[POS_DATA_SECOND_BYTE];
								break;
							case PID_KI :
								msg_size = 5;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								tx_buffer_uart5[POS_ACT] = rx_buffer_uart2[POS_DATA_SECOND_BYTE];
								break;
							case PID_KD :
								msg_size = 5;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								tx_buffer_uart5[POS_ACT] = rx_buffer_uart2[POS_DATA_SECOND_BYTE];
								break;
							case ACC :
								msg_size = 5;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								tx_buffer_uart5[POS_ACT] = rx_buffer_uart2[POS_DATA_SECOND_BYTE];
								break;
							case TORQUE_MAX :
								msg_size = 5;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								tx_buffer_uart5[POS_ACT] = rx_buffer_uart2[POS_DATA_SECOND_BYTE];
								break;
							case EN_PIN :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case ROTOR_FORWARD:
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								tx_buffer_uart5[POS_ACT] = rx_buffer_uart2[POS_DATA_SECOND_BYTE];
								break;
							case STOP_MOTOR_APP:
								msg_size = 3;
								break;
							case SAVE_AND_CLEAR :
								msg_size = 4;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								break;
							case RUN_MOTOR_APP :
								msg_size = 8;
								tx_buffer_uart5[POS_UID] = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
								tx_buffer_uart5[POS_ACT] = rx_buffer_uart2[POS_DATA_SECOND_BYTE];
								tx_buffer_uart5[POS_MSG_TYPE] = rx_buffer_uart2[POS_DATA_THIRD_BYTE];
								tx_buffer_uart5[POS_AXE] = rx_buffer_uart2[POS_DATA_FOURTH_BYTE];
								tx_buffer_uart5[POS_DATA_FIRST_BYTE] = rx_buffer_uart2[POS_DATA_LAST_BYTE];
								break;
							default :
								break;
						}
							tx_buffer_uart5[POS_ID_FIRST_BYTE] = rx_buffer_uart2[POS_AXE];
							tx_buffer_uart5[POS_ID_LAST_BYTE] = rx_buffer_uart2[POS_MSG_TYPE];
							tx_buffer_uart5[msg_size-1] = calc_checksum_uart5(msg_size);
							HAL_UART_Transmit(&huart5 ,tx_buffer_uart5, msg_size ,200);
							memset(tx_buffer_uart5, 0, MSG_SIZE_UART5);

					break;
					case LED_RING :
						switch (msg_type){
						case NORMAL :
							effect_led = false;
							break;
						case FADE :
							effect_led = true;
							break;
						case LOADING :
							break;
						default:
							break;
						}
					choice_color();
					break;

					case SCREEN :
						break;
					default:
						break;
				}
			}
		}
	}
}

void msg_manager(UART_HandleTypeDef * uart){
	if (uart2_irq_is_captured)
	{
		reception(&huart2);
		uart2_irq_is_captured = false;
	}
	if (uart5_irq_is_captured){
		HAL_UART_Transmit(&huart2,rx_buffer_uart5, msg_size_reception ,500);
		uart5_irq_is_captured = false;
		__HAL_UART_DISABLE_IT(&huart5,  UART_IT_RXNE);  // Disable UART2 RX interrupt
		memset(rx_buffer_uart5, 0, MSG_SIZE_UART2);
	}
//	if (sending_msg)
//	{
//		transmission_uart2(uart);
//		sending_msg = 0;
//	}
}

bool check_msg_identifier(){
	return rx_buffer_uart2[POS_ID_FIRST_BYTE] == MSG_ID_FIRST_BYTE
			&& rx_buffer_uart2[POS_ID_LAST_BYTE] == MSG_ID_LAST_BYTE;
}

bool robot_uid(){
	return UID == rx_buffer_uart2[POS_UID];
}

uint8_t calc_checksum_rx(int trame){
//	for (int i = 0; i < trame; i++){
//		checksum = rx_buffer_uart2[i];
//	}
//	return checksum;
	return rx_buffer_uart2[POS_ID_FIRST_BYTE] + rx_buffer_uart2[POS_ID_LAST_BYTE] +
			rx_buffer_uart2[POS_UID] + rx_buffer_uart2[POS_ACT] + rx_buffer_uart2[POS_MSG_TYPE] +
			rx_buffer_uart2[POS_AXE] + rx_buffer_uart2[POS_DATA_FIRST_BYTE] + rx_buffer_uart2[POS_DATA_SECOND_BYTE] +
			rx_buffer_uart2[POS_DATA_THIRD_BYTE] + rx_buffer_uart2[POS_DATA_FOURTH_BYTE] + rx_buffer_uart2[POS_DATA_LAST_BYTE];
}
uint8_t calc_checksum_uart5(int trame){
	checksum = 0;
		for (int i = 0; i < trame; i++){
			checksum += tx_buffer_uart5[i];
		}
		return checksum;
}

uint8_t check_checksum_rx(){
	return rx_buffer_uart2[POS_CHECKSUM] == calc_checksum_rx(MSG_SIZE_UART2);
}

void choice_color(){
	red = rx_buffer_uart2[POS_AXE];
	green = rx_buffer_uart2[POS_DATA_FIRST_BYTE];
	blue = rx_buffer_uart2[POS_DATA_SECOND_BYTE];
}


//uint8_t transmission(UART_HandleTypeDef * uart){
//
//	tx_buffer_uart2[POS_ID_FIRST_BYTE] = MSG_ID_FIRST_BYTE;
//	tx_buffer_uart2[POS_ID_LAST_BYTE] = MSG_ID_LAST_BYTE;
//	tx_buffer_uart2[POS_UID] = MY_ID;
//	tx_buffer_uart2[POS_MSG_TYPE] = tx_msg_type_byte;
//	tx_buffer_uart2[POS_DATA_FIRST_BYTE] = tx_data_first_byte;
//	tx_buffer_uart2[POS_DATA_LAST_BYTE] = tx_data_last_byte;
//	tx_buffer_uart2[POS_CHECKSUM] = calc_checksum_tx(tx_buffer_uart2);
//
//	return HAL_UART_Transmit(uart,tx_buffer_uart2,MSG_SIZE_UART2,DEFAULT_TIMEOUT);
//}