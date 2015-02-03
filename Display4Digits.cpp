#include "Display4Digits.h"

#define MINUS 17
#define NOTHING 18


// Konfiguracja cyfr
byte digitsPattern[18] =  {		B00111111,   // 0
								B00000110,   // 1
								B01011011,   // 2
								B01001111,   // 3
								B01100110,   // 4
								B01101101,   // 5
								B01111101,   // 6
								B00000111,   // 7
								B01111111,   // 8
								B01101111,   // 9
								B01110111,	 // A 10
								B01111100,	 // b 11
								B00111001,	 // C 12
								B01011110,	 // d 13
								B01111001,   // E 14
								B01110001,	 // F 15
								B01000000,	 // - 16
								B00000000 }; // NOTHING 17


Display4Digits::Display4Digits(short pin1, short pin2, short pin3, short pin4, int type, int CS)
{
	SPI.begin();

	// Ustawia piny wyświetlacza
	pins[0] = pin1;
	pins[1] = pin2;
	pins[2] = pin3;
	pins[3] = pin4;
	
	this->type = type;
	
	pinMode(CS, OUTPUT);	// Konfiguracja pinu CS

	
	for(int i = 0; i < 4; ++i)
	{
		// Czyści wyświetlacz
		digits[i] = NOTHING;
		
		// Konfiguruje piny
		pinMode(pins[i], OUTPUT);
		
		// Wszystkie cyfry włączone
		disabled[i] = false;
	}
	
	// Włącza wyświetlanie wszystkich cyfr
	displayAll0 = true;		

}


void Display4Digits::update(int number)
{
	if(number < 10000 && number > -1000)	// Jeżeli liczba ma maksymalnie 4 cyfry
	{
		this->number = number;
		
		// Obliczanie poszczególnych cyfr 
	
		int numberCopy = number;
	
		if(number < 0)
			number = -number;

	
		int temp[4];
		
		temp[3] = number % 10;
		temp[2] = number % 100;
		temp[1] = number % 1000;
		temp[0] = number % 10000;
		
		digits[3] = temp[3];
		digits[2] = (temp[2] - digits[3]) / 10;
		digits[1] = (temp[1] - digits[2]) / 100;
		digits[0] = (temp[0] - digits[1]) / 1000;
		
		///////////////////////////////////
		
		if(numberCopy < 0)
		{
			digits[0] = MINUS;
		}
		// Wyświetlanie cyfr po kropce i 1 przed, gdy wyłączone jest wyświetlanie wszystkich cyfr
		if(numberCopy >= 0 && !displayAll0)
		{
			if(numberCopy < 1000 && !dots[0])
			{
				digits[0] = NOTHING;
				
				if(numberCopy < 100 && !dots[1])
				{
					digits[1] = NOTHING;
					if(numberCopy < 10 && !dots[2])
					{
						digits[2] = NOTHING;
					}
				}		
			}

		}
	}
}

void Display4Digits::display()
{
	
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
        {
			if(type == HIGH)
				digitalWrite(pins[j], LOW);    	// Wyłączenie wyświetlaczy
			else
				digitalWrite(pins[j], HIGH);    // Wyłączenie wyświetlaczy
        }
			static byte dis;
			dis = digitsPattern[digits[i]];
			if(dots[i])
				dis ^= byte(10000000);			// Dodawanie kropki, jeśli włączona
		
			
			// Jesli nie jest wyłączone lub właśnie miga
			if(!disabled[i] && (!flashing[i] || timer[i].get() < 500))
			{
				if(type == HIGH)					// Wspólna anoda
				{
					digitalWrite(pins[i], HIGH);    // uruchomienie wybranego wyświetlacza
					SPI.transfer (~dis);          // Wysyłanie liczby
				}
				else								// Wspólna katoda
				{
					digitalWrite(pins[i], LOW);    	// uruchomienie wybranego wyświetlacza
					SPI.transfer (dis);     		// Wysyłanie liczby
				}
			}
			else if(dots[i])
			{
				// Wysyłanie samej kropki jeśli włączona
				if(type == HIGH)					// Wspólna anoda
				{
					digitalWrite(pins[i], HIGH); 
					SPI.transfer (~byte(10000000)); 
				}
				else								// Wspólna katoda
				{
					digitalWrite(pins[i], LOW);
					SPI.transfer (byte(10000000));
				}
			}
			if(timer[i].get() >= 1000)
			{
				timer[i].reset();
			}
			delayMicroseconds(1000);			// Czekanie przez 1000 mikrosekund = 1 milisekunde
	}

	
}

void Display4Digits::setDot(int digit, bool enable)
{
	if(digit >= 0 && digit < 4)
		dots[digit] = enable;

}

void Display4Digits::displayAll0Digits(bool enable)
{
	displayAll0 = enable;
}

void Display4Digits::disable(int digit)
{
	disabled[digit] = true;
}

void Display4Digits::enable(int digit)
{
	disabled[digit] = false;
}

int Display4Digits::get()
{
	return number;
}

void Display4Digits::setFlash(int digit, bool enable)
{
	flashing[digit] = enable;
}