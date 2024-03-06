/*
 * communication.h
 *
 *  Created on: Feb 14, 2024
 *      Author: smore
 */

#ifndef INC_COMMUNICATION_H_
#define INC_COMMUNICATION_H_

#define MSG_SIZE_UART2				12
#define MSG_SIZE_UART5				12
#define MSG_ID_FIRST_BYTE			0xA8
#define MSG_ID_LAST_BYTE			0x89
#define MSG_BROADCAST 				0xFF
#define MAX_OCTET_TO_SEND_SERVO		8

#define UID 						0x01

enum MESSAGE_TYPE {
	ACK,
	READ_ENCODER_POSITION = 0x30,
	NB_OF_PULSE = 0x33,
	READ_ERROR_MOTOR_ANGLE = 0x39,
	EN_Pin_STATUS,
	MOTOR_SHAFT_LOCKED_ROTOR = 0x3D,
	MOTOR_SHAFT_PROTECTION_STATE,
	CALIBRATE_THE_ENCODER= 0x80,
	MOT_TYPE,
	MODE,
	MA,
	MSTEP,
	EN_PIN__COMMAND,
	DIRECTION,
	AUTO_SSD,
	LOCKED__MOTOR,
	SUBDIVISION_INTERPOLATION_APP,
	BAUDRATE_APP,
	UARTADDR,
	RESTORE_DEFAULT_PARAMETRE = 0x3F,
	ZERO_MOD= 0x90,
	SET_ZERO,
	SPEED_ZERO,
	DIR_ZERO,
	GO_TO_0,
	PID_KP = 0xA1,
	PID_KI,
	PID_KD,
	ACC,
	TORQUE_MAX,
	EN_PIN= 0xF3,
	ROTOR_FORWARD= 0xF6,
	STOP_MOTOR_APP,
	SAVE_AND_CLEAR= 0xFF,
	RUN_MOTOR_APP= 0xFD
};

enum BYTE_POSITION_UART2 {
	 POS_ID_FIRST_BYTE,
	 POS_ID_LAST_BYTE,
	 POS_UID,
	 POS_ACT,
	 POS_MSG_TYPE,
	 POS_AXE,
	 POS_DATA_FIRST_BYTE,
	 POS_DATA_SECOND_BYTE,
	 POS_DATA_THIRD_BYTE,
	 POS_DATA_FOURTH_BYTE,
	 POS_DATA_LAST_BYTE,
	 POS_CHECKSUM
};

enum CMD_LED_RING{
	NORMAL,
	FADE,
	LOADING
};
enum actionneur {
	ARM,
	LED_RING,
	SCREEN
};

enum address {
	E0 = 0xE0,
	E1 = 0xE1,
	E2 = 0xE2,
	E3 = 0xE3,
	E4 = 0xE4,
	E5 = 0xE5,
	E6 = 0xE6,
	E7 = 0xE7,
	E8 = 0xE8,
	E9 = 0xE9
};

void uart_init(UART_HandleTypeDef * uart);

void reception(UART_HandleTypeDef * uart);

void msg_manager(UART_HandleTypeDef * uart);

void parser();

bool check_msg_identifier();

bool robot_uid();

void choice_actionneur();

uint8_t calc_checksum_rx(int trame);

uint8_t calc_checksum_uart5(int trame);

uint8_t check_checksum_rx();

void choice_color();

#endif /* INC_COMMUNICATION_H_ */
