# IFTTT-DashButton
[right now only in German, sorry]


Felix Bonus, 03-2018
 
##########    IFTTT-Dash Button   ##########

Dieser Sketch ermöglicht das Aufrufen einer IFTTT Aktion durch das Drücken eines Buttons.
Die URL für diese Aktion ergibt sich aus der Website www.maker.ifttt.com
Um ein versehentliches Auslösen zu verhindern, wird der Controller mit einem ersten Button (Reset)
aus seinem Deep-Sleep geweckt. Eine Wifi-Verbindung wird aufgebaut, danach hat man 4 Sekunden (Zeit wählbar)
Zeit, den zweiten Button zu drücken, der die Aktion (das Aufrufen der URL) auslöst.

Verwendet wurde primär ein Wemos D1 Mini, jeder andere ESP 8266 sollte aber auch funktionieren.

Zum Aufwecken wird ein NO-Pushutton direkt zwischen RST und GND angebracht, kein Widerstand nötig

Der Pin des zweiten Button wird mit einem ca. 10-15 kOhm Widerstand mit 3,3V verbunden um ihn 
"high" zu ziehen. Ein NO-Pushbutton wird dann direkt zwischen dem Pin und GND verbaut, der bei 
Betätigung den Pin auf "low" zieht. (Alternativ: Verwenden von GPIO0 [D3], da dieser scheinbar
einen eingebauten Pullup hat.)

Eine LED wird mit entsprechendem Vorwiderstand (lieber etwas größer, da sonst zu hell) an den ent-
sprechenden Pin angeschlossen.
 
!!Wichtig!! Bei allen Pinbezeichnung am Wemos immer die GPIO-Nummer verwenden! Nicht die aufgedruckte 
 Bezeichnung
