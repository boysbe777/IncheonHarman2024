/*
 * IncFile1.h
 *
 * Created: 2024-03-28 오전 10:59:03
 *  Author: boysb
 */ 

#define F_CPU 16000000L // 빼먹으면 곤란하다. 없으면 1M로 설정함.
extern char* SegDisp(unsigned long num); // 외부에 있는 함수의 프로토타입을 컴파일러에게 인지 시켜 주는 것이 좋음. 없어도 돌아는 가지만 있는게 정석이다.
/* int a=0,b=1,c=2; 의미를 갖는 변수들이 Header file에 들어가 있으면 Header file이 #include 된 파일에 같이 들어가게 됨.
중복된 이름이 안들어가게 아래 주석처리된 내용 안 #define INCFILE1_H_ 과 #endif 사이에 넣어줘야 한다.

/* #ifndef INCFILE1_H_ 중복방지 때문에 사용 됨. preprocessor, ifn = if not의 의미다. INCFILE1_H_는 tag명
#define INCFILE1_H_ 중복방지 때문에 사용 됨. preprocessor, 매크로 명령에 의해서. INCFILE1_H_는 #define tag명으로 작성되야 적용 된다.
#endif*/ /* INCFILE1_H_ */