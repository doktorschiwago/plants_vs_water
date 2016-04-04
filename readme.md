plants_vs_water
===============

Dieses Repository enthaelt die Quellen zum plants vs. water Projekt. Folgende Programme sind vorhanden:

plants_vs_water
---------------

Dieses Arduino Programm kann Feuchtigkeits- und Temperatursensoren auslesen. Die gemessenen Werte werden ueber die serielle Schnittstelle ausgegeben.

client.py
---------

Dies ist der Serverprogramm zu plants_vs_water. Das Programm oeffnet die serielle Schnittstelle und speichert die vom Arduino gelieferten Werte in eine Datenbank.

pvw_wifi
--------

Dieses Arduino Programm ist eine Weiterentwicklung von plants_vs_water. Die Ausgabe der gemessenen erfolgt hier durch Ansteuerung eines ESP8266 ueber WLAN.

client.py
---------

Dies ist der Serverprogramm zu pvw_wifi. Das Programm liest die gemessenen Werte von stdin. Es ist fuer den Aufruf durch inetd gedacht.

plot.gnu und plotSeries.sh
--------------------------

Dies sind Programme zum Auslesen der gemessenen Werte aus der Datenbank. Mittels gnuplot erstellen Sie einen Chart ueber die Entwicklung der letzten 48 Stunden.

sendMail.py
-----------

sendMail.py verschickt die von den Plotprogrammen generierten Charts per E-Mail.
