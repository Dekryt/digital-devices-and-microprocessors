// 15 variant
/*
N = 8 (kB)
XX = 33h => 51 (10)
ZZZ = 1000h => 4096 (10)
ot 51 do 4096, mejdu nimi 4046 (10) = FCE (16)
*/
/*
int i, j;           // ћоргание лампочки на контакте P1B0
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
#include <htc.h>

int i, dlina;
unsigned char xdata* ptr;
unsigned char xdata start, end, counter;

char buf, value;

int j;

void Clear() {
	P1 = 0x00;
}

void ShowError() {
	P1 = 0xAA;		// bin: 10101010, зажигает лампы по P1 в шахматном пор€дке
}

void main(void) {
	start = 0x33; // начальный адрес в зависимости от вар.
	end = 0x1000;  // конечный адрес в зависимости от вар.
	value = 0x11;	// bin: 00010001, dec: 17, значение дл€ теста
	ptr = (unsigned char xdata*) start;
	counter = 0x0;
	while ((int)ptr != (int)end) {
		Clear(); // P1 = 0x00
		*ptr = value;
		buf = *ptr;
		if (buf != value) { // проверка на работу с идиотом
			P11 = 1;
			break;
		}
		//for (i = 0; i < 5; i++) {
			P10 = 0;
			P10 = 1;
		//}
		ptr++;
	}
	/*for (j = 0; j < 10; j++) {
		P1 = counter;
		for (i = 0; i < 1; i++);
		counter = counter + 1;
		for (i = 0; i < 1; i++);
	}
	Clear();*/
}
