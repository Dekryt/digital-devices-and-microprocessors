// 15 вариант (16х2)
// 2 слова (<8 символов слово)
// I слово - 8 позиция I стр
// II слово - режим "бегущей строки" (<----) II стр
// 
// Слова нужны на кириллице, перемещение каретки должно быть с минимальным количеством пробелов, 
//реализовать перемещение каретки на определенное место сразу без пробелом, не затирать 1 строку при перемещении 2 строки

// 0xC0 - передвижение курсора в начало II строки
// 0x80 - передвижение курсора в начало I строки

#include <8051.h>
#include <string.h>
volatile bit E @ 0xA0;
volatile bit RS @ 0xA1;
volatile bit RW @ 0xA2;

volatile unsigned char data @ 0x80; // обращение ко всему байту P0 
int i, n = 0;
unsigned char right = 0x06, left = 0x04;
int counter;
int position;

const unsigned char famaly[] = {
    159 + 15,	// Н
    159 + 10,
    159 + 23,
    159 + 1,
    159 + 14,
    159 + 10,
    159 + 19 	// С
};

//const unsigned char Islovo[8]; // слово для I задания

// RS 1 -> запись данных  
//    0 -> запись команды
// RW 1 -> чтение
//    0 -> запись
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


// void vivod(unsigned char pelmen[])
// {
    // int j;
    // j = strlen(pelmen);
    // for (i = 0; i < j; i++)
    // {
        // zapis(pelmen[i]); // передача символа в функцию записи
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
    // zapis(159 + 19);  // Степан
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


// counter - счетчик позиции каретки
// n - переменная для хранения в себе n-ого элемента из массива family и его вывода в цикле, тип каждый раз n++
// position - переменная для замены/стирания прошлого элемента при передвижении слова

void peremechenie(int pelmen)
{
    commandor(0xC0 + pelmen);	// переход в позицию pelmen от начала второй строки
}


void main() {
    int j = 7;			// ОБЯЗАТЕЛЬНО указаывать длину строки для бегущей строки
    position = 15;
    counter = 15;
    commandor(0x80 + 7);

    zapis(159 + 19);  // Степан , I строка
    zapis(159 + 20);
    zapis(159 + 6);
    zapis(159 + 17);
    zapis(159 + 1);
    zapis(159 + 15);

    peremechenie(position); // перемещение на конец II строки 
    commandor(0x04);      // пишем справа налево

    for (;;) {        // II строка, цикл для бегущей строки
        if (counter + j + 2 < 0)
            counter = 15;
        if (counter + 1 < 0)	// третий этап		counter = -2, -3, -4, ... -2-j
        {
            peremechenie(counter + j + 1);
            zapis(' ');
            for (n = 0; n < j; n++)
                if (counter + 2 + n > 0)
                    zapis(famaly[counter + 1 + n]);
        }
        else
        {
            for (n = 0; n < j; n++)	// первый этап
            {
                if ((15 - counter) - n > 0 && (15 - counter) <= j)	// 	(15 - counter) 		 = 0, 1, ... j; (15 - counter) <= j	 = до тех пор, пока не будет написано слово полностью
                    zapis(famaly[j - (15 - counter) + n]);
                else
                    break;
            }

            if ((15 - counter) - n > 0 && (15 - counter) > j)	// второй этап
            {
                peremechenie(counter + j + 1);
                zapis(' ');
                for (n = 0; n < j; n++)
                    zapis(famaly[n]);
            }
            else	// возврат в начало строки для первого этапа
                peremechenie(15);
        }
        counter--;

    }
}
