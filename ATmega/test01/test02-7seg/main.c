/*
 * test02-7seg.c
 *
 * Created: 2024-03-21 오후 3:34:27
 * Author : boysb
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/delay.h>
#include <util/delay.h>
#define __delay_t 500

uint8_t digit[] ={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7c, 0x58, 0x5E, 0x79, 0x71}; // 전역 변수
char arr[5]; // 세그먼트 이미지 정보를 담을 안전 영역

void TogglePinA(int n, double dl) // n : n번째 bit, dl : delay in ㎧ mili-second
{
	char b = 1 << n; // n 번만큼 bit Shite left
	PORTA |= b; // PORTA의 n번째 bit를 High 로 출력, PORTA는 Type이 없음. 상수처럼 취급해야 함.
	_delay_ms(__delay_t);
	PORTA &= ~b; // PORTA의 n번째 bit를 Low 로 출력
	_delay_ms(__delay_t);
}
void LED(char *p, int n) // p: PORTx 의 포인터, n : n번째 bit
{
	char b = 1 << n; // n 번만큼 bit Shite left
	*p |= b; // PORTx의 n번째 bit를 High 로 출력
	_delay_ms(__delay_t);
	*p &= ~b; // PORTx의 n번째 bit를 Low 로 출력
	_delay_ms(__delay_t);
}
void seg(int sel, uint8_t c) // c : segment image, sel : chip select
{
	PORTC |= 0x0F; // 하위 4 bit 1111 미 출력 sel 신호는 0
	PORTC &= ~(1 << (3-sel));
// 왼쪽부터가 아니라 오른쪽 부터 하기 위해서 3-sel로 변경, 1000 의 bit not 0111로 변경, 1111과 0111을 bit and 0111 로 되어 마지막 자리에 세그먼트 이미지가 1110으로 됨.
	PORTD = c; // 숫자 데이터 출력
	_delay_us(1); // 0.01초 간격으로 전환
}
void FND_4(char *inf) // segment image 배열
{
	for(int i = 0 ; i < 4; i++)
		{
			seg(i, *(inf+i)); //seg(i, inf[i]); 동일
		}
}
char* Trans(unsigned long num) // 10진 정수 ==> 16진수 문자열 : 56506 ==> 0xDCBA, N4,N3,N2,N1 4096,256,16,1 문자열 다룰땐 안전영역 고려 정적변수영역에 넣어주는게 좋음.
					 //			 ==> 16진수 segment image 배열
{
	int n1 = num % 16;			// A : 문자가 아닌 숫자(10) // 10진수라면은 & 10으로 하면 됨
	int n2 = (num / 16) % 16;	// B : 문자가 아닌 숫자(11)
	int n3 = (num / 256) % 16;	// C : 문자가 아닌 숫자(12)
	int n4 = (num / 4096);		// D : 문자가 아닌 숫자(13)
	arr[0] = digit[n1];
	arr[1] = digit[n2];
	arr[2] = digit[n3];
	arr[3] = digit[n4];
	// FND_4(arr); // main 함수 내에서 해도 됨.
	return arr;
}
int main(void)
{
    // Replace with your application code
		unsigned long j = 0;
		// int i,j = 0;
		// DDRB = 0x07; // 하위 3 bit 0000 0111
		DDRD = 0xFF;
		DDRC = 0x0F;	
    while (1) 
    {
		//TogglePinA(2,__delay_t); // PORTA의 0번째 bit를 점멸
		//LED(&PORTD,1); // PORTD의 0번째 bit를 점멸
		FND_4(Trans(j++));
		_delay_us(11);
		
		/*for(i = 0; i < 4; i++)
			{
			PORTC |= 0x0F;
			PORTC &= ~(1 << (3-i)); // 왼쪽부터가 아니라 오른쪽 부터 하기 위해서 3-i로 변경
				for(j = 0; j < 16; j++) // 16진수를 표현하기 위해 j <10 → j <16으로 변경함.
					{
						PORTD = digit[j];
						_delay_ms(1000);
					}
			}*/
	}
	return 0;
}