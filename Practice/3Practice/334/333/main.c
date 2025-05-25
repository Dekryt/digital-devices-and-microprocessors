// 15 ������� (16�2)
// 2 ����� (<8 �������� �����)
// I ����� - 8 ������� I ���
// II ����� - ����� "������� ������" (<----) II ���
// 
// ����� ����� �� ���������, ����������� ������� ������ ���� � ����������� ����������� ��������, 
//����������� ����������� ������� �� ������������ ����� ����� ��� ��������, �� �������� 1 ������ ��� ����������� 2 ������

// 0xC0 - ������������ ������� � ������ II ������
// 0x80 - ������������ ������� � ������ I ������

#include <8051.h>
#include <string.h>
volatile bit E @ 0xA0;
volatile bit RS @ 0xA1;
volatile bit RW @ 0xA2;

volatile unsigned char data @ 0x80; // ��������� �� ����� ����� P0 
int i, n = 0;
unsigned char right = 0x06, left = 0x04;
int counter;
int position;

const unsigned char famaly[] = {
    159 + 15,	// �
    159 + 10,
    159 + 23,
    159 + 1,
    159 + 14,
    159 + 10,
    159 + 19 	// �
};

//const unsigned char Islovo[8]; // ����� ��� I �������

// RS 1 -> ������ ������  
//    0 -> ������ �������
// RW 1 -> ������
//    0 -> ������
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


// void vivod(unsigned char pelmen[])
// {
    // int j;
    // j = strlen(pelmen);
    // for (i = 0; i < j; i++)
    // {
        // zapis(pelmen[i]); // �������� ������� � ������� ������
    // }
// }

void commandor(unsigned char pelmen)
{
    RS = 0;
    RW = 0;
    data = pelmen;
    E = 1;
    E = 0;
}

// void clear()
// {
    // RS = 0;
    // RW = 0;
    // data = 0x01;
    // E = 1;
    // E = 0;
// }

// void sleep()
// {
    // for (i = 0; i < 50; i++);
// }


// void task(/*unsigned char* pelmen, unsigned char* pelmen2*/)
// {
    // zapis(159 + 19);  // ������
    // zapis(159 + 20);
    // zapis(159 + 6);
    // zapis(159 + 17);
    // zapis(159 + 1);
    // zapis(159 + 15);

    // commandor(0xC0 + 15);
    // commandor(0x04);

    //// sleep();
    // counter++;
    // if (counter >= 16)
        // counter = 0;
// }


// counter - ������� ������� �������
// n - ���������� ��� �������� � ���� n-��� �������� �� ������� family � ��� ������ � �����, ��� ������ ��� n++
// position - ���������� ��� ������/�������� �������� �������� ��� ������������ �����

void peremechenie(int pelmen)
{
    commandor(0xC0 + pelmen);	// ������� � ������� pelmen �� ������ ������ ������
}


void main() {
    int j = 7;			// ����������� ���������� ����� ������ ��� ������� ������
    position = 15;
    counter = 15;
    commandor(0x80 + 7);

    zapis(159 + 19);  // ������ , I ������
    zapis(159 + 20);
    zapis(159 + 6);
    zapis(159 + 17);
    zapis(159 + 1);
    zapis(159 + 15);

    peremechenie(position); // ����������� �� ����� II ������ 
    commandor(0x04);      // ����� ������ ������

    for (;;) {        // II ������, ���� ��� ������� ������
        if (counter + j + 2 < 0)
            counter = 15;
        if (counter + 1 < 0)	// ������ ����		counter = -2, -3, -4, ... -2-j
        {
            peremechenie(counter + j + 1);
            zapis(' ');
            for (n = 0; n < j; n++)
                if (counter + 2 + n > 0)
                    zapis(famaly[counter + 1 + n]);
        }
        else
        {
            for (n = 0; n < j; n++)	// ������ ����
            {
                if ((15 - counter) - n > 0 && (15 - counter) <= j)	// 	(15 - counter) 		 = 0, 1, ... j; (15 - counter) <= j	 = �� ��� ���, ���� �� ����� �������� ����� ���������
                    zapis(famaly[j - (15 - counter) + n]);
                else
                    break;
            }

            if ((15 - counter) - n > 0 && (15 - counter) > j)	// ������ ����
            {
                peremechenie(counter + j + 1);
                zapis(' ');
                for (n = 0; n < j; n++)
                    zapis(famaly[n]);
            }
            else	// ������� � ������ ������ ��� ������� �����
                peremechenie(15);
        }
        counter--;

    }
}
