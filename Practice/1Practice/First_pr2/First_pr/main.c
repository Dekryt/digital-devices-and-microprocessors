// 15 variant
/*
N = 8 (kB)
XX = 33h => 51 (10)
ZZZ = 1000h => 4096 (10)
ot 51 do 4096, mejdu nimi 4046 (10) = FCE (16)
*/
/*
int i, j;           // Моргание лампочки на контакте P1B0
void main() {
	P1 = 0x00;
	for (i = 0; i < 1000000; i++) {
		P10 = 1;
		for (j = 0; j < 2; j++);
		P10 = 0;
		for (j = 0; j < 1; j++);
	}
}
*/
#include <8051.h>

int i, dlina;
char xdata* ptr;
char xdata start, end;

char buf, value;

void main(void) {
	start = 0x33; // начальный адрес в зависимости от вар.
	end = 0x1000;  // конечный адрес в зависимости от вар.
	value = 0x11;	// bin: 00010001, dec: 17, значение для теста
	ptr = (char xdata*) start;
	while ((int)ptr != (int)end) { // работа до достижения последнего адреса
		P1 = 0x00;
			*ptr = value;
			 buf = *ptr;
		if (buf != value) { // проверка на работу с идиотом
			P16 = 1;
			break;
		}
		P15 = 1;
		ptr++;
	}
}
