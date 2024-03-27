#include <stdio.h>
#include <conio.h>
#include <string.h>

void test01(); // �Լ��� prototype void�� ���� ���� ���°��� �����Լ� ���ν���
void test02(int a);
void test03();
void test04();
void test05();
void test06();
void test07();
void test08();
void test09();

int Length(char* str);
// -----�Լ��� ����-----
// �Լ��� prototype : int Length(char* str)
// �Լ��� : Length
// ��� : ���ڿ��� �μ��� �޾Ƽ� ���ڿ��� ���̸� ��ȯ
// �μ� : ���ڿ� - char *str
// ���ϰ� : ���ڿ��� ���� - int len
int Compare(char* a, char* b);
// -----�Լ��� ����-----
// �Լ��� prototype : int Compare(char* a, char* b)
// �Լ��� : Compare
// ��� : ���ڿ��� �μ��� �޾Ƽ� ���ڿ��� ũ�⸦ ��('������' '������' �� ������ ASCII �ڵ��� ���ڰ��� ��)
// �μ� : ���ڿ� - char* a , char* b
// ���ϰ� : ���ڿ��� �񱳰� - i

void Dump(char* p, int len); // �޸� ���� ��¿� �����Լ�
void Copy(char* p1, char* p2); // p1�� p2�� �޾Ƽ� ����
// -----�Լ��� ����-----
// �Լ��� prototype : void Copy(char* p1, char* p2);
// �Լ��� : Copy
// ��� : p2 ���ڿ��� �μ��� �޾Ƽ� p1 ���ڿ��� ����
// �μ� : Ÿ�ٹ��ڿ�,�ҽ����ڿ� - char *p1, char *p2
// ���ϰ� : void

// GitHub���� �ҽ� ����
main()
{
	int n;
	void* pF[] = { test01,test02,test03,test04,test05,test06,test07,test08,test09}; // void pF�� type �������� ���� ��. test01,test02,test03,test04 �� �Լ��� �ּ�
	void (*pFunc)();
	while (1)
	{
		printf("\n\n\n\n\n");
		printf("1. ����Ű�� ���� ���ڿ� ��� �̼�\n");
		printf("2. ���ڿ��� ���ڹ迭\n");
		printf("3. �������� ��ġ ����\n");
		printf("4. �����͸� �̿��� ���ڿ� ������Լ�\n");
		printf("5. ����ü �׽�Ʈ\n");
		printf("6. ǥ���Լ� �׽�Ʈ\n");
		printf("7. Length �Լ� �׽�Ʈ\n");
		printf("8. Compare �Լ� �׽�Ʈ\n");
		printf("9. Buf Clear �׽�Ʈ\n");
		printf("0. ����\n");
		printf("====================================\n ���� ");
		scanf("%d", &n);
		if (n == 0) return;
		pFunc = pF[n - 1];
		pFunc();
	}
	//test01();		// �ϰ� �Լ��� �ٲ�
	//test02(1);	// 1�� ���̴°� �ƹ� �ǹ� ����
	//test03();
	//test04();
	//test05();
}

void test01() // ����Ű�� ���� ���ڿ� ��� �̼�
{
	const char* str[] = { "Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine" }; // ���ڿ� ������ �迭 10���� �迭��� ��� ���ڿ���
	printf("���� Ű�� �Է��ϼ���. �ش��ϴ� ���ܾ �˷��帮�ڽ��ϴ�.\n");
	printf("���α׷��� �����÷��� 'Q' Ű�� �Է��ϼ���/\n\n");
	int n = 1; // ������ ���� ������� ��� �ʱ�ȭ
	while (n)
	{
		printf(">");
		char c = getch(); // no echo : Ű���� ������� �ʰ� ��ȯ(���� ���� Ű ���� ������ ���� �ǵ����ش�.)
		//char c1 = getchar(); // [enter] �ʿ�. 

		//if (c == '1') printf("%c :One\n", c);
		//else if (c == '2') printf("%c :Two\n", c);
		//else if (c == '3') printf("%c :Three\n", c);
		//else if (c | 0x20 == 'q') break; // �빮�� Hex 40 �迭 �ҹ��� Hex 60 �迭
		// 0x20 C���� 16���� ǥ��� 0010 0000 ������ ����� ��. 40 �迭 0100 0000 60 �迭 0110 0000
		
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
		//int m = c - 0x30; //ASCII --> num ����
		if ((c | 0x20) == 'q') break; // bit OR ������ | ���� ������ == ���� �켱������ ����.
		printf("%c : %s\n", c, str[c - 0x30]); // str[n][m]
	}
}
void test02(int a) // ���ڿ��� ���ڹ迭
{
	char ca[] = "Hello"; // ca[0] : 'H' ... ca[4] : 'o' ca[5] : \0
	for (int i = 0; i < 6; i++) // 0~5���� i �� ���� null �� ���� �Ǿ� �ֱ� ������ 6���� ��
	{
		//i?? for loop int = i �� ���� ��.
		printf("ca[%d] : %c (%02x) [%08x]\n", i, ca[i], ca[i], ca + i); //ca+i = 6
	}
	int ia[] = { 10,20,30,40,50 }; //5�� �迭�� ���� int Arr
	for (int i = 0; i < 6; i++) // 0~5���� i �� ���� null �� ���� �Ǿ� �ֱ� ������ 6���� ��
	{
		printf("ia[%d] : %d (%08x) [%08x]\n", i, ia[i], ia[i], ia + i);
	}
	int ia2[2][3] = { 10,20,30,40,50,60 }; //5�� �迭�� ���� int Arr
	for (int y = 0; y < 2; y++) // 0~2
	{
		for (int x = 0; x < 3; x++)
		{
			printf("ia2[%d][%d] : %d [%08x]\n", y, x, ia2[y][x], ia2 + y);//ia2 �� �迭�� y offset�� ������ 0 1 2 �ٲ�� y index
		}
	}
}
void test03() // �������� ��ġ ����
{
	char buf[100];	// buf�� ���� 100�� ����. �����͸� �̿��� ������ �ּ� �ùķ��̼� ���� �޸� ���� Ȯ�� ���� ���ص� �Ǵµ� �������� ���� ���� �ϱ��
	char* pBuf;		// �ּ��� �̸��� ���̷�Ʈ�� �Է��� �޵��� ���� �޸� ���� ���� ��� ��ġ
	unsigned int addr;		// ��� ��ġ ������ ���� �Էº���(�ּ�)
	char kBuf[100];	// ��� ���ڿ� �Է°��� scanf�� �������� �Է��� ������ �ʿ���
	printf("���������� �ּҴ� %d[%08x] �Դϴ�.\n", (unsigned int)buf, buf);
	printf("�Է��� ������ �ּҸ� �Է��ϼ��� :");
	scanf("%d", &addr); // �������� �ּ� ����  �� �ּҷ� �Է��� ���� ��
	pBuf = buf + addr;
	printf("���ڿ��� �Է��ϼ��� : ");
	scanf("%s", kBuf); // Ű����� ���� ���ڿ��� �Է¹޾� kBuf�� ��
	Copy(pBuf, kBuf);
	Dump(buf, 100);
}
void test04() // �����͸� �̿��� ���ڿ� ������Լ�
{
	char* arr[10] = { "aaaaa","bbbb","ccc","dd","eeeeee" };
	char buf[100];	// ���� arr ����
	printf("[6]"); scanf("%s", buf);
	arr[6] = buf;
	printf("[7]"); scanf("%s", buf + 50); // ������ ���� �ޱ� ����+50�� ���ش�
	arr[7] = buf + 50; // ���� �Է��� �޾Ƽ� 7�� arr
	for (int i = 0; i < 10; i++)
	{
		printf("arr[%d] : 0x%08x %s\n", i, arr[i], arr[i]); // arr[i] 16���� 8�ڸ� ǥ�� �ּҰ� arr[i] ���ڿ�
	}
}
void test05() // ����ü �׽�Ʈ
{
	struct stTest
	{
		int i; // 4byte
		float a; // 4byte
		char name[20]; // 20���� �ϴϱ� ������ �ȵ� �� �׷��� ���庸�� char* �� 8byte = �ּҴ� 8byte
	} s1 = { 1, 3.14 ,"��õ���ڵ����" };
	//s1.name = "��õ���� �����"; // const �������� ���� �ű⿡ �ּҰ� ���� �ּҰ� name�� �����
	struct stTest s2 = s1;

	printf("sizeof(struct stTest) : %d\n", sizeof(struct stTest)); // sizeof �� ��ũ�� ��Ȱ ��ȣ���� ���ڸ� byte ������ size�� �ǵ�����.

	printf("struct stTest s1 : %d  %f  %s\n", s1.i, s1.a, s1.name);
	printf("struct stTest s2 : %d  %f  %s\n", s2.i, s2.a, s2.name);
};
void test06()
{
	char* s1;// = "Good"; // const ����, ����(����)�Ұ� ����, �ֻ����� �ö�. char* s1; �� cccc�� ���� ������ ������ �ִ°��� �ƴ�.
	char* s2;// = "afternoon"; // ��������� �ּҴ� stack ������ �� ����. char* s2; �� cccc�� ���� ������ ������ �ִ°��� �ƴ�.
	char buf[100]; // ������ �޸� ����, local�� ������ 00�� ���� �ʰ� cc�� ��. ������ ������ ��. ���ڿ��� �ڰ���Ȯ��
	s1 = buf;
	s2 = buf + 50;
	scanf("%s", s1);
	scanf("%s", s2);
	// strcat Test ���� ���ڿ��� �ڿ� ���ڿ��� �����δ�. �����ؾ� �Ѵ�. cat�� ���� ���� ���°� ��õ���� �ʴ´�. 1.���÷� ������ͼ� ���� ���� �迭��, 2.printf�� �̿��ؼ� console �Լ�
	// fprintf �� ������ ���, sprintf buf�� ����ϴ� printf �Լ�
	printf("s1 : %s(%d)\n",s1, strlen(s1)); // strlen �����Լ�, strlen �� ���̻����� null�� �� ������. ���� ���ڸ��� ī��Ʈ
	printf("s2 : %s(%d)\n",s2, strlen(s2));
	strcpy(buf, s1); // �����Լ�
	strcat(buf, s2); // s1+s2 s1�� ��� �����̸� �����Ұ��� ������ �ްԵ�, �߰��Լ�
	printf("strcat(s1,s2) : %s", buf); //�����߻� �κ� �ǳʶ� s1 ��ü�� ��� ������ ����Ŵ strcat(s1, s2) ���� ���
	//sprintf(buf, "strcat(s1,s2) : %s%s", s1, s2); // buf��
	//printf("%s", buf);
	//fprintf(FILE* stream, "strcat(s1,s2) : %s", strcat(s1, s2)); ���߿� �غ���.
}
void test07()
{
	char buf[100];
	printf("���ڿ��� �Է��ϼ��� :"); scanf("%s", buf);
	printf("�Է��� ���ڿ��� ���̴� [ %d ] �Դϴ�. \n", Length(buf));
}
int Length(char* str) // ���ڿ� str�� �μ��� �޾Ƽ� ���̸� ��ȯ, ���ڿ��� Ư�� \0(null)�� �ִٴ°��� �˰� ����, char* str�� ������ġ�� ����Ŵ
{
	int len = 0; // ��ȯ�� ���ڿ��� ����
	while (1)
	{
		if (*(str + len) == 0) break; // ���ڿ��� ��(\0,null)�� ���������� Ż��
		len++;
	}
	return len; // return ���� ����� ��ȯ
}
void test08()
{
	char* str1 = "���Ⱑ�ٶ���";
	char* str2 = "���Ⱑ�λ���";
	printf("ũ���:%d",Compare(str1, str2));
}
int Compare(char* a, char* b)
{
	int n = 0;
	int i = 0;
	while (1) // ���� ���� �϶��� 1�̴�.
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
	int n = 0,i=0;// a=5 a�� 5�̴� ������
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
			if ((a[n] == 0) && (b[n] == 0)) // a==0 �� a�� 0�� ���� ũ��� != ���� �ʴ�.
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
	while (*p2) *p1++ = *p2++; *p1 = 0; // p2�� ���� \0(null)�� �ƴ� p1�� p2�� �ִ� ���� �����ؼ� �־��
}
void Dump(char* p, int len) // �޸� ���� ��� �޸� �ּ� 16byte 00000000 00000000 �ٹٲ� �ϰ� �ּ� 00000000 00000000 �����Լ�
{
	for (int i = 0; i < len; i++) // �������� �޸� ����
	{
		if (i % 16 == 0) printf("\n%08x ", p);// i �� 16�� ��� ù��° �� ���� �ؼ� �� �ٲ��� �Ͼ�� ���� �ּҸ� ����� p�� �ּҰ�
		if (1 % 8 == 0) printf("   "); // i �� 8�� ������� ������ ��� ����
		printf("%02x ", (unsigned char)*p++); // *p �ش� �ϴ� �ּҿ� �ִ� ��
	}
}
void test09()
{
	char buf[100];
	int n, m;
	while (1)
	{
		printf("Ȧ���� �Է��ϼ��� : ");
		m = scanf("%d", &n);
		if (m == 0) // �Է¿���
		{
			fflush(stdin); // ���� Ŭ����
			rewind(stdin); // ���� ����Ʈ �ʱ�ȭ
			continue;
		}
		printf("�Է��� ���ڴ� [%d] �Դϴ�.\n\n", n);
	}
}