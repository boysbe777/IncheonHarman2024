#include <stdio.h>
#include <conio.h>
#include <string.h>

void test01(); // 함수의 prototype void로 리턴 값이 없는것은 수행함수 프로시저
void test02(int a);
void test03();
void test04();
void test05();
void test06();
void test07();
void test08();
void test09();

int Length(char* str);
// -----함수의 설계-----
// 함수의 prototype : int Length(char* str)
// 함수명 : Length
// 기능 : 문자열을 인수로 받아서 문자열의 길이를 반환
// 인수 : 문자열 - char *str
// 리턴값 : 문자열의 길이 - int len
int Compare(char* a, char* b);
// -----함수의 설계-----
// 함수의 prototype : int Compare(char* a, char* b)
// 함수명 : Compare
// 기능 : 문자열을 인수로 받아서 문자열의 크기를 비교('가나다' '가나라' 의 글자의 ASCII 코드의 숫자값을 비교)
// 인수 : 문자열 - char* a , char* b
// 리턴값 : 문자열의 비교값 - i

void Dump(char* p, int len); // 메모리 공간 출력용 범용함수
void Copy(char* p1, char* p2); // p1과 p2를 받아서 복사
// -----함수의 설계-----
// 함수의 prototype : void Copy(char* p1, char* p2);
// 함수명 : Copy
// 기능 : p2 문자열을 인수로 받아서 p1 문자열로 복사
// 인수 : 타겟문자열,소스문자열 - char *p1, char *p2
// 리턴값 : void

// GitHub에서 소스 수정
main()
{
	int n;
	void* pF[] = { test01,test02,test03,test04,test05,test06,test07,test08,test09}; // void pF는 type 정해지지 않은 것. test01,test02,test03,test04 는 함수의 주소
	void (*pFunc)();
	while (1)
	{
		printf("\n\n\n\n\n");
		printf("1. 숫자키에 대한 문자열 출력 미션\n");
		printf("2. 문자열과 문자배열\n");
		printf("3. 포인터의 위치 지정\n");
		printf("4. 포인터를 이용한 문자열 입출력함수\n");
		printf("5. 구조체 테스트\n");
		printf("6. 표준함수 테스트\n");
		printf("7. Length 함수 테스트\n");
		printf("8. Compare 함수 테스트\n");
		printf("9. Buf Clear 테스트\n");
		printf("0. 종료\n");
		printf("====================================\n 선택 ");
		scanf("%d", &n);
		if (n == 0) return;
		pFunc = pF[n - 1];
		pFunc();
	}
	//test01();		// 일개 함수로 바뀜
	//test02(1);	// 1을 붙이는건 아무 의미 없음
	//test03();
	//test04();
	//test05();
}

void test01() // 숫자키에 대한 문자열 출력 미션
{
	const char* str[] = { "Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine" }; // 문자열 포인터 배열 10개의 배열요소 어떠한 문자열을
	printf("숫자 키를 입력하세요. 해당하는 영단어를 알려드리겠습니다.\n");
	printf("프로그램을 끝내시려면 'Q' 키를 입력하세요/\n\n");
	int n = 1; // 변수일 값을 집어넣을 경우 초기화
	while (n)
	{
		printf(">");
		char c = getch(); // no echo : 키값을 출력하지 않고 반환(내가 누른 키 값이 찍히기 전에 되돌려준다.)
		//char c1 = getchar(); // [enter] 필요. 

		//if (c == '1') printf("%c :One\n", c);
		//else if (c == '2') printf("%c :Two\n", c);
		//else if (c == '3') printf("%c :Three\n", c);
		//else if (c | 0x20 == 'q') break; // 대문자 Hex 40 계열 소문자 Hex 60 계열
		// 0x20 C언어에서 16진수 표기법 0010 0000 값으로 상수가 됨. 40 계열 0100 0000 60 계열 0110 0000
		
		//switch (c) 
		//{
		//case '1' : printf("%c :One\n", c); break;
		//case '2': printf("%c :Two\n", c); break;
		//case '3': printf("%c :Three\n", c); break;
		//case '4': printf("%c :Four", c); break;
		//case '5': printf("%c :Five\n", c); break;
		//case '6': printf("%c :Six\n", c); break;
		//case '7': printf("%c :Seven\n", c); break;
		//case '8': printf("%c :Eight\n", c); break;
		//case '9': printf("%c :Nine\n", c); break;
		//case '0': printf("%c :Zero\n", c); break;
		//case 'q': 
		//case 'Q': n = 0; break;
		//}
		//int m = c - 0x30; //ASCII --> num 숫자
		if ((c | 0x20) == 'q') break; // bit OR 연산자 | 관계 연산자 == 보다 우선순위가 높다.
		printf("%c : %s\n", c, str[c - 0x30]); // str[n][m]
	}
}
void test02(int a) // 문자열과 문자배열
{
	char ca[] = "Hello"; // ca[0] : 'H' ... ca[4] : 'o' ca[5] : \0
	for (int i = 0; i < 6; i++) // 0~5까지 i 값 변동 null 이 포함 되어 있기 때문에 6개가 됨
	{
		//i?? for loop int = i 가 적용 됨.
		printf("ca[%d] : %c (%02x) [%08x]\n", i, ca[i], ca[i], ca + i); //ca+i = 6
	}
	int ia[] = { 10,20,30,40,50 }; //5의 배열을 갖는 int Arr
	for (int i = 0; i < 6; i++) // 0~5까지 i 값 변동 null 이 포함 되어 있기 때문에 6개가 됨
	{
		printf("ia[%d] : %d (%08x) [%08x]\n", i, ia[i], ia[i], ia + i);
	}
	int ia2[2][3] = { 10,20,30,40,50,60 }; //5의 배열을 갖는 int Arr
	for (int y = 0; y < 2; y++) // 0~2
	{
		for (int x = 0; x < 3; x++)
		{
			printf("ia2[%d][%d] : %d [%08x]\n", y, x, ia2[y][x], ia2 + y);//ia2 는 배열명 y offset만 가지고 0 1 2 바뀌는 y index
		}
	}
}
void test03() // 포인터의 위치 지정
{
	char buf[100];	// buf의 방을 100개 잡음. 포인터를 이용한 임의의 주소 시뮬레이션 안전 메모리 공간 확보 궂이 안해도 되는데 안전하지 않은 공간 일까봐
	char* pBuf;		// 주소의 이름을 다이렉트로 입력을 받도록 안전 메모리 공간 중의 출력 위치
	unsigned int addr;		// 출력 위치 지정을 위한 입력변수(주소)
	char kBuf[100];	// 출력 문자열 입력공간 scanf를 받을때는 입력할 공간이 필요함
	printf("안전공간의 주소는 %d[%08x] 입니다.\n", (unsigned int)buf, buf);
	printf("입력을 시작할 주소를 입력하세요 :");
	scanf("%d", &addr); // 안전공간 주소 참고  그 주소로 입력한 값이 들어감
	pBuf = buf + addr;
	printf("문자열을 입력하세요 : ");
	scanf("%s", kBuf); // 키보드로 부터 문자열을 입력받아 kBuf로 들어감
	Copy(pBuf, kBuf);
	Dump(buf, 100);
}
void test04() // 포인터를 이용한 문자열 입출력함수
{
	char* arr[10] = { "aaaaa","bbbb","ccc","dd","eeeeee" };
	char buf[100];	// 로컬 arr 영역
	printf("[6]"); scanf("%s", buf);
	arr[6] = buf;
	printf("[7]"); scanf("%s", buf + 50); // 영역을 나눠 받기 위해+50을 해준다
	arr[7] = buf + 50; // 같은 입력을 받아서 7번 arr
	for (int i = 0; i < 10; i++)
	{
		printf("arr[%d] : 0x%08x %s\n", i, arr[i], arr[i]); // arr[i] 16진수 8자리 표시 주소값 arr[i] 문자열
	}
}
void test05() // 구조체 테스트
{
	struct stTest
	{
		int i; // 4byte
		float a; // 4byte
		char name[20]; // 20으로 하니까 진행이 안됨 왜 그런지 여쭤보기 char* 는 8byte = 주소는 8byte
	} s1 = { 1, 3.14 ,"삼천갑자동방삭" };
	//s1.name = "삼천갑자 동방삭"; // const 영역으로 들어가고 거기에 주소가 있음 주소가 name에 담겨짐
	struct stTest s2 = s1;

	printf("sizeof(struct stTest) : %d\n", sizeof(struct stTest)); // sizeof 는 매크로 역활 괄호안의 인자를 byte 기준의 size를 되돌려줌.

	printf("struct stTest s1 : %d  %f  %s\n", s1.i, s1.a, s1.name);
	printf("struct stTest s2 : %d  %f  %s\n", s2.i, s2.a, s2.name);
};
void test06()
{
	char* s1;// = "Good"; // const 영역, 변형(수정)불가 영역, 최상위로 올라감. char* s1; 은 cccc로 나와 안전한 공간에 있는것이 아님.
	char* s2;// = "afternoon"; // 상수영역의 주소는 stack 영역에 들어가 있음. char* s2; 은 cccc로 나와 안전한 공간에 있는것이 아님.
	char buf[100]; // 안전한 메모리 공간, local에 잡히는 00이 되지 않고 cc가 됨. 오류의 요인이 됨. 문자열은 ★공간확보
	s1 = buf;
	s2 = buf + 50;
	scanf("%s", s1);
	scanf("%s", s2);
	// strcat Test 기존 문자열에 뒤에 문자열을 덧붙인다. 조심해야 한다. cat를 위와 같이 쓰는건 추천하지 않는다. 1.로컬로 가지고와서 로컬 문자 배열로, 2.printf를 이용해서 console 함수
	// fprintf 는 파일을 출력, sprintf buf에 출력하는 printf 함수
	printf("s1 : %s(%d)\n",s1, strlen(s1)); // strlen 길이함수, strlen 은 길이산정시 null을 미 포함함. 실제 문자만을 카운트
	printf("s2 : %s(%d)\n",s2, strlen(s2));
	strcpy(buf, s1); // 복사함수
	strcat(buf, s2); // s1+s2 s1이 상수 영역이면 수정불가한 제약을 받게됨, 추가함수
	printf("strcat(s1,s2) : %s", buf); //오류발생 부분 건너뜀 s1 자체는 상수 영역을 가리킴 strcat(s1, s2) 들어가면 곤란
	//sprintf(buf, "strcat(s1,s2) : %s%s", s1, s2); // buf로
	//printf("%s", buf);
	//fprintf(FILE* stream, "strcat(s1,s2) : %s", strcat(s1, s2)); 나중에 해보기.
}
void test07()
{
	char buf[100];
	printf("문자열을 입력하세요 :"); scanf("%s", buf);
	printf("입력한 문자열의 길이는 [ %d ] 입니다. \n", Length(buf));
}
int Length(char* str) // 문자열 str을 인수로 받아서 길이를 반환, 문자열의 특성 \0(null)이 있다는것을 알고 진행, char* str은 시작위치를 가르킴
{
	int len = 0; // 반환할 문자열의 길이
	while (1)
	{
		if (*(str + len) == 0) break; // 문자열의 끝(\0,null)에 도달했으면 탈출
		len++;
	}
	return len; // return 문을 사용해 반환
}
void test08()
{
	char* str1 = "가기가다란인";
	char* str2 = "가기가인생생";
	printf("크기비교:%d",Compare(str1, str2));
}
int Compare(char* a, char* b)
{
	int n = 0;
	int i = 0;
	while (1) // 무한 루프 일때는 1이다.
	{
		if (*(a + n) > *(b + n)) // a[n] > b[n] == *(a + n) > *(b + n)
		{
			i = 1;
			break;
		}
		else if (*(a + n) < *(b + n))
		{
			i = -1;
			break;
		}
		else if (*(a + n) == *(b + n))
		{
			if ((*(a + n) == '\0') && (*(b + n) == '\0'))
			{
				i = 0;
				break;
			}
		}
		n++;
	}
	return i;
	/*
	int n = 0,i=0;// a=5 a는 5이다 은유법
	while (1)
	{
		if (a[n] > b[n]) 
		{
			i = 1;
			break;
		}
		else if (a[n] < b[n])
		{
			i = -1;
			break;
		}
		else
		{
			if ((a[n] == 0) && (b[n] == 0)) // a==0 은 a는 0과 같다 크기비교 != 같지 않다.
			{
				i = 0;
				break;
			}
		};
		n++;
	}
	return i;*/
}
void Copy(char* p1, char* p2) // p2 source p1 target
{
	while (*p2) *p1++ = *p2++; *p1 = 0; // p2가 현재 \0(null)이 아님 p1에 p2에 있는 값을 복사해서 넣어라
}
void Dump(char* p, int len) // 메모리 공간 출력 메모리 주소 16byte 00000000 00000000 줄바꿈 하고 주소 00000000 00000000 범용함수
{
	for (int i = 0; i < len; i++) // 안전공간 메모리 덤프
	{
		if (i % 16 == 0) printf("\n%08x ", p);// i 가 16의 배수 첫번째 줄 포함 해서 줄 바꿈이 일어날때 마다 주소를 찍어줌 p는 주소값
		if (1 % 8 == 0) printf("   "); // i 가 8의 배수마다 공간을 띄워 주자
		printf("%02x ", (unsigned char)*p++); // *p 해당 하는 주소에 있는 값
	}
}
void test09()
{
	char buf[100];
	int n, m;
	while (1)
	{
		printf("홀수를 입력하세요 : ");
		m = scanf("%d", &n);
		if (m == 0) // 입력오류
		{
			fflush(stdin); // 버퍼 클리어
			rewind(stdin); // 버퍼 포인트 초기화
			continue;
		}
		printf("입력한 숫자는 [%d] 입니다.\n\n", n);
	}
}