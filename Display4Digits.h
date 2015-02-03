/********************************************************************************************
*   Display4Digits - klasa do obsługi wyświetlacza 7 - segmentowego 4 cyfrowego             *
*   Autor: Piotr Kowalczyk                                                                  *
*   Wersja: 1.1                                                                             *
*                                                                                           *
*   Zezwalam na rozpowszechnianie i edycję z zachowaniem informacji o pierwszym autorze     *																*
*********************************************************************************************
*   Changelog:                                                                              *
*   [23-01-2015] v1.0 - Pierwsze wydanie                                                    *
*   [03-02-2015] v1.1:                                                                      *
*       - możliwość wyłączenia poszczególnych cyfr -disable() & enable()                    *
*       - możliwość włączenia migania cyfr -setFlash()                                      *
*       - poprawki błędów                                                                   *
********************************************************************************************/


#ifndef Display4Digits_h
#define Display4Digits_h

#include "Arduino.h"
#include <SPI.h>
#include <Timer.h>


class Display4Digits
{
private:
	// Wyświetlana liczba (cała)
	int number;

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
	
	// Wyłączone cyfry
	bool disabled[4];
	
	// Miganie cyfr
	bool flashing[4];
	
	// Timery dla cyfr
	Timer timer[4];

public:
	
	/****************************************************************************************************************
	*                                              Konstruktor                                                      *
	*   parametry:                                                                                                  *
	*       pin1-pin4 	- kolejne piny cyfr wyświetlacza od lewej                                                   *
	*       type		- typ wyświetlacza. wspólna anoda - HIGH, wspólna katoda - LOW                              *
	*       CS			- port Chip Select (Slave Select). http://arduino.cc/en/Reference/SPI (tabela Connections)  *
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
	
	// Wyłącza wyświetlanie wybranej cyfry
	void disable(int digit);
	
	// Włącza wyświetlanie wybranej cyfry
	void enable(int digit);
	
	// Zwraca wyświetlaną wartość
	int get();
	
	// Ustawia miganie cyfry
	void setFlash(int digit, bool enable);
};

#endif