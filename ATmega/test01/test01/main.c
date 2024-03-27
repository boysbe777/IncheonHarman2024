/*
 * test01.c
 *
 * Created: 2024-03-20 오전 11:42:05
 * Author : boysb
 */ 
#define F_CPU 16000000L // 16M로 CPU define 정의, Board에 대한 Clock 정보
#include <avr/io.h>
#include <avr/delay.h>
#include <util/delay.h>
#define __delay_t 500

void TogglePinA(int n, double dl) // n : n번째 bit, dl : delay in ㎧ mili-second
{
	char b = 1 << n; // n 번만큼 bit Shite left
	PORTA |= b; // PORTA의 n번째 bit를 High 로 출력, PORTA는 Type이 없음. 상수처럼 취급해야 함.
	_delay_ms(__delay_t);
	PORTA &= ~b; // PORTA의 n번째 bit를 Low 로 출력
	_delay_ms(__delay_t);
}

int main(void) // main 하나만 탑재됨. main 이 시작지점
{/*
    /* Replace with your application code */
	// DDRA |= 0X01; // A port의 0번째 bit를 출력용으로 사용, 나머지는 입력, DDRA는 입출력 Resister (PORTA는 port) 0은 입력, 1은 출력 1111 1110, (|= bit or 연산), 기존에 무엇이 나가건 간에
	// DDRA |= 0X02; // A port의 1번째 bit를 출력용으로 사용, 나머지는 입력
	// DDRA |= 0X03; // A port의 0,1번째 bit를 출력용으로 사용, 나머지는 입력, 동시에 깜빡임. 0000 0011로 되어서
	//DDRA |= 0x01;
	/*DDRA |= 0x02;
	DDRA |= 0x04; 순차적 진행*/
	DDRA |= 0x07; // A port 의 0,1,2번째 bit를 출력으로 사용 (07H = 0000 0111)
	DDRB &= ~0x01; // DDR 설정 레지스터, PORTB의 0번째 bit를 입력용으로 사용, 나머지는 그대로 유지 나머지를 반전 1111 1110 마지막 bit를 입력으로 사용
    int mode = 0; // mode1 : Red mode2 : Yellow mode3 : Grean flash

    while (1) // 무한 Loop가 기본, embedded programing의 기본임.
    {
	    // if(PINB & 0x01 == 1) // Switch를 눌러야 1, 아니면 0. 1이라는 의미는 Switch pull(not push) 스위치가 안눌려 졌을때 1, 눌려졌을때 0(0이면 동작이 안된다. 일반적인 'C' 프로그램이 아니다.) Swith가 안눌렸을때 true
	    if(!(PINB & 0x01 == 1)) // Swith가 눌렸을때 true
		{
		    mode++;
			if(mode >= 3) mode = 0; // 3에 도달 됬을때는 그때 0으로, int mode가 stack에 쌓이는데 다른 메모리 영역, 요인에 의해서 변경될 가능성이 있다.
			 // 3을 넘어서면 0이 되지 않는다. 여유를 준다 == >  >=로 변경, 한문장에 ++과 연산식을 동시에 넣지 않도록.
		}
		switch(mode)
		{		
			case 0 : 
			TogglePinA(0,__delay_t); // PORTA의 0번째 bit 점멸
			break;
			case 1 : 
			TogglePinA(1,__delay_t); // PORTA의 1번째 bit 점멸
			break;
			case 2 :
			TogglePinA(2,__delay_t); // PORTA의 2번째 bit 점멸
			break;
			default : mode = 0; // 변경될수 있으니 마지막에 0으로 돌아가게 끔. 안전한 프로그래밍 방식이다.
		}
		/*PORTA |= 0x01;
		_delay_ms(500);
		PORTA &= ~0x01;
		_delay_ms(500);
		PORTA |= 0x02;
		_delay_ms(500);
		PORTA &= ~0x02;
		_delay_ms(500);
		PORTA |= 0x04;
		_delay_ms(500);
		PORTA &= ~0x04;
		_delay_ms(500);*/
		// PORTA |= 0x01; // PORTA 8bit 출력 Resister, PORTA의 0번째 bit를 High로 출력
		// PORTA |= 0x02; // PORTA의 1번째 bit를 High로 출력
		// PORTA |= 0x03; // PORTA의 0,1번째 bit를 High로 출력
		//_delay_ms(500);
		// PORTA &= ~0x01; // PORTA의 0번째 bit를 Low로 출력
		// PORTA &= ~0x02; // PORTA의 1번째 bit를 Low로 출력
		// PORTA &= ~0x03; // PORTA의 0,1번째 bit를 Low로 출력
		//_delay_ms(500);
		/*PORTA |= 0x01; 
		_delay_ms(500);
		PORTA &= 0x01;
		_delay_ms(500);
		PORTA |= 0x02;
		_delay_ms(500);
		PORTA &= 0x02;
		_delay_ms(500);
		PORTA |= 0x04;
		_delay_ms(500);
		PORTA &= 0x04;
		_delay_ms(500); 순차적 진행*/
	}
} 
/*XXXX XXXX bit or(|=) 수행시 출력은 3번째 bit 
  0000 0100 PORTA |= 0x04
  1111 1011 PORTA &=~ 0x04 */

