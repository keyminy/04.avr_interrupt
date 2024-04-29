/*
 * led.c
 *
 * Created: 2024-04-29 오전 10:58:07
 *  Author: HARMAN-27
 */ 
#include "led.h"

void shift_left2right_keep_ledon();
void shift_right2left_kepp_ledon();

void shift_left2right_keep_ledon(void){
	for(int i=0; i < 8; i++){ // for문을 2400ms동안 실행하고 빠져나오게됨
		//문제점 : 2400ms동안 아무것도 못함
		PORTA |= 0b00000001 << i; // 기존 led를 현상유지 하기위해 |=를 해준다
		// '=' 하면은 기존 것 꺼집니다
		_delay_ms(300);
	}
	PORTA = 0x00;
	_delay_ms(300);
}
void shift_right2left_kepp_ledon(void){
	for(int i=0; i < 8; i++){
		PORTA |= 0b10000000 >> i; // 기존 led를 현상유지 하기위해 |=를 해준다
		// '=' 하면은 기존 것 꺼집니다
		_delay_ms(300);
	}
	PORTA = 0x00;
	_delay_ms(300);
}