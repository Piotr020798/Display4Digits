/********************************************************************************************
*	Display4Digits - klasa do obsługi wyświetlacza 7 - segmentowego 4 cyfrowego				*
*	Autor: Piotr Kowalczyk																	*
*	Wersja: 1.0																				*
*																							*
* 	Zezwalam na rozpowszechnianie i edycję z zachowaniem informacji o pierwszym autorze 	*																*
*********************************************************************************************
*	Changelog:																				*
*	[23-01-2015] v1.0 - Pierwsze wydanie													*
*********************************************************************************************
*	Znane błędy:																			*
*	- Nie działa naraz z innymi urządzeniami podłączonymi pod SPI							*
********************************************************************************************/


#ifndef Display4Digits_h
#define Display4Digits_H

#include "Arduino.h"
#include <SPI.h>


class Display4Digits
{
private:
	// Cyfry do wyświetlenia
	int digits[4];
	
	// Piny cyfr
	int pins[4];
	
	// Typ wyświetlacza
	int type;
	
	// Chip select
	int CS;
	
	// Stany kropek - włączone/wyłączone
	bool dots[4];
	
	// Czy wyświetlać wszystkie zera
	bool displayAll0;
public:
	
	/****************************************************************************************************************
	*												Konstruktor														*
	*	parametry:																									*
	*		pin1-pin4 	- kolejne piny cyfr wyświetlacza od lewej													*
	*		type		- typ wyświetlacza. wspólna anoda - HIGH, wspólna katoda - LOW								*
	*		CS			- port Chip Select (Slave Select). http://arduino.cc/en/Reference/SPI (tabela Connections)	*
	****************************************************************************************************************/
	Display4Digits(short pin1, short pin2, short pin3, short pin4, int type, int CS);
	/***************************************************************************************************************/
	
	// Funkcja aktualizująca liczbę na wyświetlaczu. Obsługuje zakres od -999 do 9999
	void update(int number);
	
	// Funkcja wyświetlająca na wyświetlaczu. Najlepiej wywoływać ją w każdym obiegu funckji loop()
	void display();
	
	// Funkcja właczająca kropkę. Parametry: digit(0-3) - kropka od lewej, enable(true/false) - włączona/wyłączona
	void setDot(int digit, bool enable);
	
	// Funkcja ustawiająca wyświetlanie wszystkich zer np. gdy mamy liczbę 10, przy włączeniu(domyślnie) będzie wyświetlać się 0010. Przyjmuje parametry true/false (włączone/wyłączone)
	// UWAGA! Jeśli opcja ta jest wyłączona, a kropka jest włączona, to automatycznie będą wyświetlane zera po kropce i jedno przed.
	void displayAll0Digits(bool enable);
};

#endif