/*
 * extern.h
 *
 * Created: 2024-04-29 오전 11:27:41
 *  Author: HARMAN-27
 */ 
#ifndef EXTERN_H_
#define EXTERN_H_

// led
extern void shift_left2right_keep_ledon();
extern void shift_right2left_kepp_ledon();

// button
extern void init_button(void);
extern int get_button(int button_pin, int button_number);


#endif /* LED_H_ */
