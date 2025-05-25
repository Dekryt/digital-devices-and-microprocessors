// ������� 15, 5 �������� ����
// ���������� 5�5
// ���������� ������ �� ��������� � ��������� ���������� ����� ������� 

#include <8051.h>
volatile bit E @ 0xA0;
volatile bit RS @ 0xA1;
volatile bit RW @ 0xA2;
volatile unsigned char data @0xB0; // ��������� �� ����� ����� P3 
void zapis(unsigned char pelmen) // ������� ��� ������
{
	RS = 1; // 1 -������  0 - ����������
	RW = 0;
	data = pelmen;
	E = 1;
	E = 0;
}

unsigned char vvod() {
	int row = 0, column = 0;
	
	unsigned char bukovka = 0; // ���������� ��� �������� �������� �������
	P0 = 0xFF; // ��� ���� 0
	P1 = 0x00; // ��� ���� 1 
	if (P00 != 0 && P01 != 0 && P02 != 0 && P03 != 0 && P04 != 0) {
		bukovka = ' ';
		return bukovka;
	}
	if (P00 == 0) {
		row = 0; // I ������
	}
	if (P01 == 00) {
		row = 1; // II ������
	}
	if (P02 == 00) {
		row = 2; // III ������
	}
	if (P03 == 00) {
		row = 3; // IV ������
	}
	if (P04 == 00) {
		row = 4; // V ������
	}
	P1 = 0xFF; // ��� ���� 1 
	P0 = 0x00; // ��� ���� 0
	if (P10 == 0) {
		column = 0; // I �������
	}
	if (P11 == 00) {
		column = 1; // II �������
	}
	if (P12 == 00) {
		column = 2; // III �������
	}
	if (P13 == 00) {
		column = 3; // IV �������
	}
	if (P14 == 00) {
		column = 4; // V �������
	}
	if (column == 0 && row == 0)
		bukovka = 'Q';
	if (column == 1 && row == 0)
		bukovka = 'W';
	if (column == 2 && row == 0)
		bukovka = 'E';
	if (column == 3 && row == 0)
		bukovka = 'R';
	if (column == 4 && row == 0)
		bukovka = 'T';

	if (column == 0 && row == 1)
		bukovka = 'A';
	if (column == 1 && row == 1)
		bukovka = 'S';
	if (column == 2 && row == 1)
		bukovka = 'D';
	if (column == 3 && row == 1)
		bukovka = 'F';
	if (column == 4 && row == 1)
		bukovka = 'G';

	if (column == 0 && row == 2)
		bukovka = 'Z';
	if (column == 1 && row == 2)
		bukovka = 'X';
	if (column == 2 && row == 2)
		bukovka = 'C';
	if (column == 3 && row == 2)
		bukovka = 'V';
	if (column == 4 && row == 2)
		bukovka = 'B';

	if (column == 0 && row == 3)
		bukovka = '1';
	if (column == 1 && row == 3)
		bukovka = '2';
	if (column == 2 && row == 3)
		bukovka = '3';
	if (column == 3 && row == 3)
		bukovka = '4';
	if (column == 4 && row == 3)
		bukovka = '5';

	if (column == 0 && row == 4)
		bukovka = '6';
	if (column == 1 && row == 4)
		bukovka = '7';
	if (column == 2 && row == 4)
		bukovka = '8';
	if (column == 3 && row == 4)
		bukovka = '9';
	if (column == 4 && row == 4)
		bukovka = '0';


	return bukovka;
}

void main()
{
	int i;
	char space, old;
	while (1) {
		old = vvod();
		if (space != ' ')
		{
			//zapis(space);
			for (i = 0; i < 1; i++);
			space = vvod();
			if (space == old && space != ' ')
				zapis(space);
		}
	}

	
}


