/*
 * test03-interrupt.c
 *
 * Created: 2024-03-27 오후 12:20:24
 * Author : boysb
 */
#define F_CPU 16000000L // 빼먹으면 곤란하다. 없으면 1M로 설정함.
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#define __delay_t 500
#define OPMODEMAX	3
#define STATE_MAX	3

uint8_t digit[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
char arr[5];
volatile int opmode = 0, state = 0; // 볼레타일, 컴파일러에 의한 최적화 금지

void seg(int sel, uint8_t c) // c : segment image, sel : chip select
{
	PORTC |= 0x0F;
	PORTC &= ~(1 << (3-sel));
	PORTD = c; // 숫자 데이터 출력
	//_delay_us(11); // 0.01초 간격으로 전환
}
int sm = 4;
void FND_4(char *inf) // segment image 배열
{
	int i;
	for(i = 0; i < sm; i++)
	{
		seg(i, *(inf+i));
		_delay_ms(5);
	}
}
/*void LED_blink() {
	// LED 점멸 함수
	for (int i = 0; i < 5; i++) {
		PORTB |= (1 << PB0); // LED ON
		_delay_ms(100); // 100ms 대기
		PORTB &= ~(1 << PB0); // LED OFF
		_delay_ms(100); // 100ms 대기
	}
}*/
char* Disp(unsigned long num) // 10진 정수 ==> 16진수 문자열 : 56506 ==> 0xDCBA, 4 digit 16진수 segment 출력
{
	num %= 65536;
	int n1 = num % 16;			// A : 문자가 아닌 숫자(10) // 10진수라면은 & 10으로 하면 됨
	int n2 = (num / 16) % 16;	// B : 문자가 아닌 숫자(11)
	int n3 = (num / 256) % 16;	// C : 문자가 아닌 숫자(12)
	int n4 = (num / 4096);		// D : 문자가 아닌 숫자(13)
	arr[0] = digit[n1];
	arr[1] = digit[n2];
	arr[2] = digit[n3];
	arr[3] = digit[n4];
	sm = (num > 4095) ? 4 : (num > 256) ? 3 : (num > 16) ? 2 : 1;
	FND_4(arr);
	return arr;
}
int main(void)
{
    /* Replace with your application code */
	// 7-Segment 사용 : 4 Module - C type
	// Pin assign : PDx - Segment Image, PCx - Module Select
	// Interrupt 사용 : INT4 ~ INT6 (External Interrupt) 상위 Digit 7654 3210
	// Pin assign : PE4 ~ PE6
	DDRD = 0xFF;
	DDRC = 0x0F;
	/*DDRB |= (1 << PB0); // LED 핀을 출력으로 설정*/
	
	// 인터럽트 설정
	EIMSK = 0x70; // 2진수 표현 0111 0000
	EICRB = 0x2a; // 2진수 표현 0010 1010
	SREG |= 0x80; // status Register - 인터럽트 허용, 상태 레지스터 값 셋팅, SREG에 빨간줄이 가도 돌아가는데 상관없음 열이 없어도 가능함.
	sei(); // set interrupt - 인터럽트 시작
	
	long t = 0;
    while (1) 
    {
		switch(opmode) // 정해져 있는 opmode 대해 진행
		{
			case 0 : // reset & wait
			t = 0; break;
			/*case 1 : // counter start
			t++;
			if (t >= 10) {
				LED_blink(); // 설정 시간에 도달하면 LED를 점멸시킴
				opmode = 0; // opmode를 0으로 설정하여 타이머를 재설정할 수 있도록 함
			}
			break;*/
			case 2 : // counter stop
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
    }
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
/*ISR(INT5_vect) // INT5 5번 인터럽트 처리 루틴 : sw2
{
	state++;
	if(state >= STATE_MAX) state = 0;
}
ISR(INT6_vect) // INT5 6번 인터럽트 처리 루틴 : sw3
{
	
}*/