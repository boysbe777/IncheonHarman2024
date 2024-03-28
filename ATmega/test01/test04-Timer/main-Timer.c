/*
 * test04-Timer.c
 *
 * Created: 2024-03-28 오전 10:57:13
 * Author : boysb
 */ 
#include "myHeader.h" // test04-Timer libraries내 myHeader.h에 있음. "" 현재 경로에 있을때 C:\Users\boysb\source\repos\Work\ATmega\test01\test04-Timer
#include <avr/io.h> // <> system Header 시스템 경로 C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\avr\include\avr
#include <avr/delay.h>
#include <avr/interrupt.h>

#define __delay_t 500

unsigned long cnt = 0, tcnt = 0; // While Loop 전에 선언이 되어 있어야 하기 때문에 이동 시킴. microchip studio는 int가 2byte여서 unsigned long으로 써야 됨.
/* extern char* Disp(unsigned long num);  외부에 있는 함수의 프로토타입을 컴파일러에게 인지 시켜 주는 것이 좋음. 없어도 돌아는 가지만 있는게 정석이다.
myHeader.h에 옮겨 둿음.*/

int main(void)
{
    /* Replace with your application code */
	SegPort(&PORTD, &PORTC);
	DDRD = 0xFF; // Segment 제어를 위한 포트레지스터, 세그먼트 제어 핀 8개를 출력으로 설정
	DDRC = 0x0F; // Segment 제어를 위한 포트레지스터, 자릿수 선택 핀 4개를 출력으로 설정
	/* Timer interrupt에 대한 setting 시작 */

	// TIMSK |= 0x01; // 2진수 0000 0001 - Timer 0 TCNT Overflow interrupt, page 297 (8bit)
	TIMSK |= 0x04; // 2진수 0000 0100 - Timer 1 TCNT Overflow interrupt, page 297 (16bit)
	// TIMSK |= 0x40; // 2진수 0100 0000 - Timer 2 TCNT Overflow interrupt, page 297 (8bit)
	// TCCR0 = 0x04;  // 분주비(Pre-Scaler) 64, page 296, |= 해줘도 됨. 주기를 결정하기 위해 사용. Timer 0
	TCCR1B = 0x04;  // 분주비(Pre-Scaler) 64, page 317, |= 해줘도 됨. 주기를 결정하기 위해 사용. Timer 1
	// TCCR2 = 0x04;  // 분주비(Pre-Scaler) 64, page 296, |= 해줘도 됨. 주기를 결정하기 위해 사용. Timer 2
	SREG |= 0x80;  // 최상의 bit를 1로 설정하여 사용하게 함.
	sei();
	/* Timer interrupt에 대한 setting 완료 */
    while (1) 
    {
		if(cnt >= 0x10000) cnt = 0;
		SegDisp(cnt); // unsigned long 이 아니고 integer가 들어가는 경우 오동작 할 수 있음.
    }
}
ISR(TIMER1_OVF_vect) // 1㎳ 마다 발생함. TCNTx(8bit) 256 * 분주비 64 = 16,384의 값을 갖고 ATmega의 clk 주파수 1초에 16,000,000 보다 1/1000 작기 때문에 대략 1㎳가 나온다.
{
	tcnt++; // 인터럽트가 발생 할때 마다 1000개에 도달 하게 되면, 원래의 동작 cnt++ 이 되고 tcnt는 0으로 초기화 된다.
	//if(tcnt >= 1000) // 빠르게 하기 위해서는 1000의 숫자를 줄이면 된다. ISR(TIMER0_OVF_vect)에서 사용, 8bit Timer 일때 사용
	{
		cnt++; tcnt = 0; // 1초마다 cnt가 하나씩 증가 됨. While loop는 계속 진행 됨.
	}
	// ISR(TIMER1_OVF_vect)를 작업 하기 위해서는 외부클록(크리스탈)이 있어야 가능하다. page 293
	// ISR(TIMER2_OVF_vect)를 작업 하기 위해서는 외부클록(크리스탈)이 있어야 가능하다. page 293
	/*if(cnt >= 0x10000) cnt = 0;
	Disp(cnt); Disp 작업은 While Loop에 넣는게 좋다.*/
}

