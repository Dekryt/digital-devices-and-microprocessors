#include <8051.h>

int period;
interrupt void interr() {
	P05 = !P05;
	if (P00 == 1 && period <= 230)
		period += 25;
	if (P01 == 1 && period > 25)
		period -= 25;
	if (P02 == 1)
		period = 100;
}


int step;
int i;

void sleep(int x);

void draw() {
	for(i = 0; i < 64; i++)
	{
		P1 += step;
		sleep(period);
	}
}

void sleep(int x) {
	TH1 = 0xFF;
    TL1 = 0xFF - x ;
    TF1 = 0;
    TR1 = 1;
    while(TF1 == 0);
    TR1 = 0;
    TL1 = 0;
}




int main() {
	int step1;
	int step2;
	int step3;
	int x1;
	int x2;
	int x3;
	
	//int y_max = 255;
	P0 = P1 = P2 = P3 = 0;
	period = 100;
	
	IE = 0;
	IE_BITS.B7 = 1;
	IE_BITS.B0 = 1;
	TCON = 0;
	TCON_BITS.B0 = 1;
	TCON_BITS.B1 = 1;
	
    TMOD = 0b00010000;
	
	//y_max = 255;
	

	step1 = (255 + 1) / 2 / 64;
	step2 = 0;
	step3 = (255 +1) / 4 / 64;
	x1 = 256 / 4;
	x2 = 255;
	x3 = 256 / 2;
	
	while (1) {
		P1 = 0;
		step = step2;
		draw();
		P1 = x1;
		step = step1;
		draw();
		P1 = x2;
		step = step2;
		draw();
		P1 = x3;
		step = step3;
		draw();
		P1 = 0;
		step = step2;
		draw();
	}
	
	
}