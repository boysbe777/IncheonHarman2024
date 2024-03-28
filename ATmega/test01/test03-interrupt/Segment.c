/*
 * CFile1.c
 *
 * Created: 2024-03-28 오전 10:45:36
 *  Author: boysb
 */ 
//#include "myHeader.h" // test04-Timer libraries내 myHeader.h에 있음.
#define F_CPU 16000000L // 빼먹으면 곤란하다. 없으면 1M로 설정함. myHeader.h에 있음.

#include <avr/io.h>
#include <avr/delay.h>

uint8_t digit[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
char arr[5];

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