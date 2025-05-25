// 15 вариант (16х2)
// 2 слова (<8 символов слово)
// I слово - 8 позиция I стр
// II слово - режим "бегущей строки" (<----) II стр
#include <8051.h>
#include <string.h>
volatile bit E @ 0xA0;
volatile bit RS @ 0xA1;
volatile bit RW @ 0xA2;

volatile unsigned char data @ 0x80; // обращение ко всему байту P0 
int i;
unsigned char right = 0x06, left = 0x04;
int counter = 0;
//const unsigned char Islovo[8]; // слово для I задания

// RS 1 -> запись данных  
//    0 -> запись команды
// RW 1 -> чтение
//	  0 -> запись
// E  1->0(импульс) -> обработка данных
//    0->1(импульс) -> ничего не делает

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
		zapis (pelmen[i]); // передача символа в функцию записи
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
		commandor(0x06);	// задаём направление вправо
		vivod("       ");
		
		//vivod(pelmen);	// либо это	


		zapis(159 + 19);	// либо этот блок
		zapis(159 + 20);
		zapis(159 + 7);
		zapis(159 + 17);
		zapis(159 + 1);

		commandor(0x02);	// в начало первой строки
		commandor(0x04);	// 0x04 - начинает писать справа налево для перехода на 2 строку
		zapis(' ');
		for (i = 0; i <= counter; i++) {				// j = 6, counter = 6 ->  "  slovo2"
			if (counter >= j) {							// если слово уже написано полностью
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
		"svo svo svo",	// I  задание
		"svo svo"		// II задание
	);
	vivod("wake up! ");
}
