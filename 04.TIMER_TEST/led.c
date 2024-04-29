﻿/*
 * led.c
 *
 * Created: 2024-04-29 오전 10:58:07
 *  Author: HARMAN-27
 */ 
#include "led.h"
#include "extern.h"

void shift_left2right_keep_ledon();
void shift_right2left_kepp_ledon();
void led_all_on_off();


void led_all_on_off(){
	 static int led_toggle = 0;
	 //함수가 종료되더라도 update된 값을 유지하게 static
	 
	if(ms_count >= 300){
		//hardware적으로 뜨기때문에 값이 툭 튈수도 있어요 그래서 >=로 하기(==대신)
		ms_count = 0; // clear
		led_toggle = !led_toggle; // 1혹은 0의 값
		if(led_toggle)
		PORTA = 0xff;
		else
		PORTA = 0x00;
	}
}


void shift_left2right_keep_ledon(void){
	#if 1
		//delay안하고 가기
		static int i = 0; // 이전에 update된 내용을 유지하기위해, 전역함수와 동일한 효과
		//timer interrupt가 300ms가 됬는지 안됬는지 check하는 로직 필요(main.c에 있다)
		// shift_timer를 이용합시다(extern.h)
		if(shift_timer >= 300){ // 00000001 -> 00000011 -> .... -> 11111111
			// shift_timer==300해버리면, 실제 상황에서 301ms가 넘어오면 실행안됨
			//300ms가 되면 bit shift를 해주는거야!
			shift_timer = 0; //shift_timer를 0으로 초기화 해주는거 필수
			
			if(i >= 8){
				i=0; //circulation
				PORTA = 0x00;
			}else{
				// shifting logic
				PORTA |= 0b00000001 << i++; // 1.shift left , 2. i++해줌
			}
		}

	#else
		for(int i=0; i < 8; i++){ // for문을 2400ms동안 실행하고 빠져나오게됨
			//문제점 : 2400ms동안 아무것도 못함
			PORTA |= 0b00000001 << i; // 기존 led를 현상유지 하기위해 |=를 해준다
			// '=' 하면은 기존 것 꺼집니다
			_delay_ms(300);
		}
		PORTA = 0x00;
		_delay_ms(300);
	#endif
}
void shift_right2left_kepp_ledon(void){
	
#if 1
	//delay안하고 가기
	static int i = 0; // 이전에 update된 내용을 유지하기위해, 전역함수와 동일한 효과
	//timer interrupt가 300ms가 됬는지 안됬는지 check하는 로직 필요(main.c에 있다)
	// shift_timer를 이용합시다(extern.h)
	if(shift_timer >= 300){ // 00000001 -> 00000011 -> .... -> 11111111
		// shift_timer==300해버리면, 실제 상황에서 301ms가 넘어오면 실행안됨
		//300ms가 되면 bit shift를 해주는거야!
		shift_timer = 0; //shift_timer를 0으로 초기화 해주는거 필수
			
		if(i >= 8){
			i=0; //circulation
			PORTA = 0x00;
		}else{
			// shifting logic
			PORTA |= 0b10000000 >> i++; // 1.shift right , 2. i++해줌
		}
	}
#else
	for(int i=0; i < 8; i++){
		PORTA |= 0b10000000 >> i; // 기존 led를 현상유지 하기위해 |=를 해준다
		// '=' 하면은 기존 것 꺼집니다
		_delay_ms(300);
	}
	PORTA = 0x00;
	_delay_ms(300);
#endif
}