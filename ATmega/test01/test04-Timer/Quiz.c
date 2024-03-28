/*
 * Quiz.c
 *
 * Created: 2024-03-28 오후 4:01:43
 *  Author: boysb
 */ 
#include "myHeader.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define __delay_t 500
#define OPMODEMAX	3
#define STATE_MAX	3

volatile int opmode = 0, state = 0;

unsigned long cnt = 0, tcnt = 0;

void LED_blink() {
	// LED 점멸 함수
	for (int i = 0; i < 5; i++) {
		PORTB |= (1 << PB0); // LED ON
		_delay_ms(100); // 100ms 대기
		PORTB &= ~(1 << PB0); // LED OFF
		_delay_ms(100); // 100ms 대기
	}
}
int main(void)
{
	long t = 0;
	SegPort(&PORTD, &PORTC);
	DDRD = 0xFF; // Segment 제어를 위한 포트레지스터, 세그먼트 제어 핀 8개를 출력으로 설정
	DDRC = 0x0F; // Segment 제어를 위한 포트레지스터, 자릿수 선택 핀 4개를 출력으로 설정
	//DDRB |= (1 << PB0); // LED를 출력
	DDRE = 0x8F; // PE 4,5,6 입력으로 설정
	//EIMSK = 0x70; // PE4,5,6 설정을 위해 0111 0000 설정 됨.
	//EICRB = 0x2a; // PE4,5,6 하강에지시 동작을 시키기 위해 0010 1010 이 됨
	TIMSK |= 0x01; // 2진수 0000 0001 - Timer 0 TCNT Overflow interrupt, page 297 (8bit)
	TCCR0 = 0x04;  // 분주비(Pre-Scaler) 64, page 296, |= 해줘도 됨. 주기를 결정하기 위해 사용. Timer 0
	SREG |= 0x80;
	sei();
	while (1)
	    {
		    if(cnt >= 0x10000) cnt = 0;
		    SegDisp(cnt);
	    }
	/*while (1)
	{
		switch(opmode) // 정해져 있는 opmode 대해 진행
		{
			case 0 : // start & stop & restart
			t = 0; break;
			case 1 : // setting
			t++;
			if (t >= 10) 
			{
				LED_blink(); // 설정 시간에 도달하면 LED를 점멸시킴
				opmode = 0; // opmode를 0으로 설정하여 타이머를 재설정할 수 있도록 함
			}
			break;
			case 2 : // 자리이동
			break;
			default : break;
		}
		Disp(t);
		_delay_ms(15);
		Disp(t);
		_delay_ms(15);
		Disp(t);
		_delay_ms(15);
		Disp(t);
		_delay_ms(13);
	}*/

}
ISR(INT4_vect) // INT4 4번 인터럽트 처리 루틴 : sw1
{
	opmode++;
	if(opmode >= OPMODEMAX) opmode = 0; // 직접 들어간거는 상수 처리 모드가 증가 하면 증가 해야 됨. opmode >= 3과 같이 직접 넣지 않도록 하는게 좋음.
}
ISR(INT5_vect) // INT5 5번 인터럽트 처리 루틴 : 버튼 2
{
	if (opmode == 0) // 설정 상태에서만 타이머 설정 가능
	{
		opmode = 1; // 카운터 시작
	}
	else if (opmode == 1) // 카운터 진행 중이면 카운터를 멈춤
	{
		opmode = 2; // 카운터 종료
	}
}
ISR(INT6_vect) // INT6 6번 인터럽트 처리 루틴 : 버튼 3
{
	opmode = 0; // 설정 초기화
}
ISR(TIMER0_OVF_vect)
{
	tcnt++;
	if(tcnt >= 1000)
	{
		cnt++; tcnt = 0;
	}
}