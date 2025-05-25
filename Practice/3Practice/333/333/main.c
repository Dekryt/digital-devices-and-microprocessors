// 15 ������� (16�2)
// 2 ����� (<8 �������� �����)
// I ����� - 8 ������� I ���
// II ����� - ����� "������� ������" (<----) II ���
#include <8051.h>
#include <string.h>
volatile bit E @ 0xA0;
volatile bit RS @ 0xA1;
volatile bit RW @ 0xA2;

volatile unsigned char data @ 0x80; // ��������� �� ����� ����� P0 
int i;
unsigned char right = 0x06, left = 0x04;
int counter = 0;
//const unsigned char Islovo[8]; // ����� ��� I �������

// RS 1 -> ������ ������  
//    0 -> ������ �������
// RW 1 -> ������
//	  0 -> ������
// E  1->0(�������) -> ��������� ������
//    0->1(�������) -> ������ �� ������

void zapis(unsigned char pelmen)
{
	RS = 1;
	RW = 0;
	data = pelmen;
	E = 1;
	E = 0;
}
 
void vivod(unsigned char pelmen[])
{ 
	int j;
	j = strlen(pelmen);
	for (i = 0; i < j; i++)
	{
		zapis (pelmen[i]); // �������� ������� � ������� ������
	}
}

void commandor(unsigned char pelmen)
{
	RS = 0;
	RW = 0;
	data = pelmen;
	E = 1;
	E = 0;
}

void clear()
{
	RS = 0;
	RW = 0;
	data = 0x01;
	E = 1;
	E = 0;
}

void sleep()
{
	for (i = 0; i < 50; i++);
}

void task(unsigned char* pelmen, unsigned char* pelmen2) {
	int j = strlen(pelmen2);
	clear();
	
	while (1) {
		commandor(0x06);	// ����� ����������� ������
		vivod("       ");
		
		//vivod(pelmen);	// ���� ���	


		zapis(159 + 19);	// ���� ���� ����
		zapis(159 + 20);
		zapis(159 + 7);
		zapis(159 + 17);
		zapis(159 + 1);

		commandor(0x02);	// � ������ ������ ������
		commandor(0x04);	// 0x04 - �������� ������ ������ ������ ��� �������� �� 2 ������
		zapis(' ');
		for (i = 0; i <= counter; i++) {				// j = 6, counter = 6 ->  "  slovo2"
			if (counter >= j) {							// ���� ����� ��� �������� ���������
				if (counter - j - i < 0)
					zapis(pelmen2[counter - i]);
				else
					zapis(' ');
			}
			else
				zapis(pelmen2[counter - i]);
		}
		sleep();
		counter++;
		if (counter >= 16)
			counter = 0;
		clear();
	}
}

void main() {
	task(
		"svo svo svo",	// I  �������
		"svo svo"		// II �������
	);
	vivod("wake up! ");
}
