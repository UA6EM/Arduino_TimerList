/*
 Name:		RelayTest.ino
 Created:	03.03.2020 8:35:57
 Author:	DtS
*/
#include <Arduino.h>
#include <TimerList.h>

extern TTimerList TimerList;

const uint8_t MIN_RELAY_PIN = 14; // А0
const uint8_t MAX_RELAY_PIN = 17; // А3

const uint32_t t1_ms = 2000; // время включения реле 2 сек (2000 мс)

uint8_t CurrentRelay = MIN_RELAY_PIN;


THandle hT1Timer = INVALID_HANDLE;

void tmrT1Ends(void) {
	digitalWrite(CurrentRelay, LOW); // Выключается текущее реле
	CurrentRelay++;					 // Текущим становится следующее реле
	if (CurrentRelay > MAX_RELAY_PIN) CurrentRelay = MIN_RELAY_PIN; // или первое
	digitalWrite(CurrentRelay, HIGH); // включается текущее реле
	Serial.println(CurrentRelay);
}

// А если нада, чтоб реле сработали паочереди и остановились, тогда по другому

void tmrT1Ends_v2(void) {
	digitalWrite(CurrentRelay, LOW); // Выключается текущее реле
	CurrentRelay++;					 // Текущим становится следующее реле
	if (CurrentRelay <= MAX_RELAY_PIN)
		digitalWrite(CurrentRelay, HIGH); // включается текущее реле
	else
		TimerList.Stop(hT1Timer);  // или останавливается таймер
}


void setup() {
	Serial.begin(115200);
	delay(250);
	Serial.println("Application started.");

	digitalWrite(CurrentRelay, HIGH);          // включаем первое реле 
	hT1Timer = TimerList.Add(t1_ms, tmrT1Ends);// и взводим таймер на t1_ms миллисекунд
}

void loop() {
  
}
