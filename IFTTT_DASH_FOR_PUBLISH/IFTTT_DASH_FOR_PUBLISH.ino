/*
 * Felix Bonus, 03-2018
 * 
 * ##########    IFTTT-Dash Button   ##########
 * 
 * Dieser Sketch ermöglicht das Aufrufen einer IFTTT Aktion durch das Drücken eines Buttons.
 * Die URL für diese Aktion ergibt sich aus der Website www.maker.ifttt.com
 * Um ein versehentliches Auslösen zu verhindern, wird der Controller mit einem ersten Button (Reset)
 * aus seinem Deep-Sleep geweckt. Eine Wifi-Verbindung wird aufgebaut, danach hat man 4 Sekunden (Zeit wählbar)
 * Zeit, den zweiten Button zu drücken, der die Aktion (das Aufrufen der URL) auslöst.
 * 
 * Verwendet wurde primär ein Wemos D1 Mini, jeder andere ESP 8266 sollte aber auch funktionieren.
 * 
 * Zum Aufwecken wird ein NO-Pushutton direkt zwischen RST und GND angebracht, kein Widerstand nötig
 * 
 * Der Pin des zweiten Button wird mit einem ca. 10-15 kOhm Widerstand mit 3,3V verbunden um ihn 
 * "high" zu ziehen. Ein NO-Pushbutton wird dann direkt zwischen dem Pin und GND verbaut, der bei 
 * Betätigung den Pin auf "low" zieht. (Alternativ: Verwenden von GPIO0 [D3], da dieser scheinbar
 * einen eingebauten Pullup hat.)
 * 
 * Eine LED wird mit entsprechendem Vorwiderstand (lieber etwas größer, da sonst zu hell) an den ent-
 * sprechenden Pin angeschlossen.
 * 
 * !!Wichtig!! Bei allen Pinbezeichnung am Wemos immer die GPIO-Nummer verwenden! Nicht die aufgedruckte 
 * Bezeichnung
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define mySSID "yourSSID"
#define myPASSWORD "yourPASSWORD"

#define LED 5     //Pin an den die LED angeschlossen ist.(GPIO-Nummer verwenden!!!)
#define BUTTON 14 //Pin an den der Button angeschlossen ist.(GPIO-Nummer verwenden!!!)
#define TIME 4000 //Zeit zum Auslösen der Aktion


void buttonPressed() {
  //Starte Den HTTP Client:
  //Serial.println("Gedrückt!");
  HTTPClient http;

  //URL zu der IFTTT Applet:
  http.begin("http://maker.ifttt.com/trigger/DEINE-AKTION/with/key/DEIN-KEY");

  //Ruft URL auf:
  http.GET();

  delay(50);

  //Beendet Verbindung zur Website:
  http.end();

}

void blinkAcc() {
  int i = 1;
  for (i = 1; i <= 40; i++) {
    digitalWrite(LED, 0);
    delay(150 / i);
    digitalWrite(LED, 1);
    delay(150 / i);
  }
  digitalWrite(LED, 0);
}

void blinkError() {
  //Serial.println("FEHLER!");
  digitalWrite(LED, 0);
  delay(400);
  digitalWrite(LED, 1);
  delay(400);
  digitalWrite(LED, 0);
  delay(400);
  digitalWrite(LED, 1);
  delay(400);
  digitalWrite(LED, 0);
  delay(400);
  digitalWrite(LED, 1);
  delay(400);
  digitalWrite(LED, 0);
}

void connectWifi() {
  int tries = 0; //Zähler für Verbindungsversuche

  //Serial.println("Verbindungsversuch:");

  //Wifi verbinden:
  WiFi.begin(mySSID, myPASSWORD);
  do {
    tries++;
    //Serial.println(tries);
    delay(300);
    if (WiFi.status() == WL_CONNECTED) {
      //Serial.println("Verbunden!");
    }
    if (tries >= 20) {
      blinkError();
      goSleep();
    }
    yield(); //verhindert WatchDogTimer Reset
  }
  while (WiFi.status() != WL_CONNECTED && tries <= 20);
}

void goSleep() {
  //Serial.println("Schlafen");
  ESP.deepSleep(0);
}

//###########
//###SETUP###
//###########

void setup() {
  //Serial.begin(9600);
  
  int counter = 0;  //Vergangene Zeit 
  bool state = 1;

  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);


  connectWifi();

  digitalWrite(LED, 1);
  int finished = millis() + TIME; //4 Sekunden Zeit, in der Aktion ausgelöst werden kann.
  //Serial.print("Ende: "); Serial.println(finished);

  //Eigentliche Buttonabfrage und Auslösen der Aktion
  do {
    counter = millis();
    state = digitalRead(BUTTON);  //Ließt Button aus
    if (state == 0) {             //Wenn Button gedrückt--> Aktion
      buttonPressed();
      blinkAcc();   //Bestätigt Aktion
      goSleep();    
      break;
    }
    //Serial.println(counter);
    yield(); //verhindert WatchDogTimer Reset
  }
  while (counter <= finished);

  digitalWrite(LED, 0);

  //Geht in Tiefschlaf, nur durch Reset erweckbar
  goSleep();
}


void loop() {
  // put your main code here, to run repeatedly:

}
