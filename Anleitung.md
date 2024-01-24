# TechTresor: Helfer in der Not
TechTresor ist ein smarter Schrank, der Studierenden die Möglichkeit bietet technische Gebrauchsgegenstände ganz einfach mit ihrem Studi-Ausweis auszuleihen um ihnen in Notfall Situationen den Tag zu retten. Neben den technischen Gegenstände, die nur zur Ausleihe stehen, stellt der TechTresor durch die sogenannte "Free Stuff" Schublade auch eine Reihe verschiedenster Freebies wie z.B. Hygieneartikel und Süßigkeiten zur Verfügung. Das Ziel davon ist es den Aufenthalt an der Hochschule angenehmer zu gestalten.

Durch verschiedene Aufzeichnungsmethoden ist es den Betreibern des TechTresors möglich festzustellen welcher Studierender welchen Gegenstand ausgeliehen hat und wann. Dadurch kann geschaut werden, falls ein Gegenstand verschwunden ist, wer möglicherweise für das Verschwinden des Gegenstands verantwortlich ist. 

## Die Challenge
Die Challenge, welche im Rahmen des Moduls "Challenge Based Making (WS 23/24)" gestellt wurde, lautete: "Wie können wir durch smarte Devices dabei helfen, dass die Aufenthaltsqualität an der Hochschule steigt?"   

Anhand dieser Challenge führten wir einige Interviews mit Studierenden um herauszufinden, was die größten Auslöser für eine schlechte Aufenthaltsqualität sind. Aus dem Ergebnis der Interviews haben wir eine Persona erstellt: 
   
   ![persona](https://github.com/cbm-instructions/sixtysix/blob/main/images/POV.png)


# Bauanleitung
In diesem Abschnitt befindet sich die komplette Anleitung zum Bau von dem TechTresor. Der Code für den Arduino  und Raspberry befindet sich hier:  [Code](https://github.com/cbm-instructions/sixtysix/code)

## Materialien und Werkzeuge
### Materialien

 - Arduino Uno
 - Raspberry Pi 3
 - ESP32-Kamera
 - RFID Reader RC522
 - Ultraschall Entferungsmesser HC-SR04
 - Lautsprecher mit AUX Anschluss
 - TIANKONGRC TS90A Servo - 3.3V
 - **Leiterplatte ???**
 - Neopixel LED mit mind. 56 Pixeln
 - Barcode-Scanner
----
 - AUX Kabel
 - USB 2.0 Cable Type A/B (Für Verbindung zwischen Raspberry und Arduino)
 - **??? x Jumper Wire** 
 - Raspberry Pi - Netzteil, 5 V, 2,5 A, Micro-USB
 ---------
- **Schrankwände Holz ???**
- **Schrankinneres Holz ???**
 - **Farbe???**
 - **Schrauben???**
 - 4 x Möbelrollen
 - Klebeband
 - Draht für Schloss
 - 2 x Scharniere für Schranktür
 - Kabelspirale
 - **??? x Metallwinkel**
 - **??? x Muttern ???**
 - Möbelgriff
 - Lötzinn
 

### Werkzeuge

 - 3D-Drucker
 - Lasercutter
 - Lötkolben
 - Teppichmesser
 - Kreissäge
 - Akkuschrauber
 - Schraubenzieher
 - Pinsel

## Schritt für Schritt Anleitung
### 1. Schrank bauen
Als aller erstes wird der Schrank selbst gebaut. Dafür braucht man genug Holz um die Wände, Decke und den Boden zu bauen. Für unseren Schrank haben wir uns für ehemalige Tischplatten entschieden, welche wir mithilfe einer Kreissäge passend zusammen geschnitten haben. 
### 2. Schrankinneres erstellen

### 3. Technik konfigurieren
#### 3.1 Raspberry
#### 3.2 Arduino Uno

 1. Installiere die Arduino IDE
 2. Öffne `Tools/Board` in der Arduino IDE und wähle den Arduino Uno
 3. Öffne  `Tools/Port`  und wähle den COM Port, mit dem der Arduino Uno verbunden ist.
 4. Damit das Projekt funktionieren kann, müssen folgende Libraries über den Library Manager (`Tools/Manage Libraries`) installiert werden:
    -   Adafruit NeoPixel
    - MFRC522
    - Servo

#### 3.3 ESP32-Cam
1.  Öffne  `File/Preferences`
2.  Gebe folgendes in das  `Additional Board Mananger URLs`  Feld ein: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
und http://arduino.esp8266.com/stable/package_esp8266com_index.json
3.  Öffne  `Tools/Board/Boards Manager`
4.  Suche nach ESP32 und Klicke den  `install`  Knopf für  `ESP32 by Espressif Systems`

Der Code für die ESP32-Cam ist eine angepasste Version von folgendem Open Source Projekt: https://github.com/yoursunny/esp32cam/tree/main/examples/WifiCam
#### 3.4 Barcode-Scanner
#### 3.5 Datenbank erstellen
Um die Bilder, welche bei der Öffnung der Tür entstehen abzuspeichern und um immer den aktuellsten Bestand der Produktverfügbarkeit zu haben wird eine Datenbank benötigt. Wir haben uns für eine SQLite Datenbank entschieden, die lokal auf dem Raspberry Pi läuft. Dazu muss man SQLite wie folgt auf dem Raspberry per Terminal herunterladen: 
```
sudo apt install sqlite3
```
Nachdem SQLite installiert wurde, kann eine Datenbank mit folgendem Befehl erstellt werden: 
```
sqlite3 DatabaseName.db
```
Jetzt kann mit folgendem Befehl die Datenbank geöffnet werden (nachdem SQLite gestartet wurde): 
```
.open DatabaseName.db
```
Die Datenbank existiert also nun aber es werden noch zwei Tables benötigt in die die Daten geschrieben werden. Benötigt wird ein Table für die Aktivität des TechTresors. Konkret gesagt heißt das, dass für jedes Öffnen der Tür die eindeutige ID des Studi-Ausweises, das entstandene Bild und alle Items die von diesem Studierenden ausgeliehen wurde in den Table geschrieben wird. Diesen Table nennen wir mal "images". Um ein solchen Table zu erstellen muss folgender Befehlt ausgeführt werden:
```sql
CREATE TABLE images (image BLOB, uid VARCHAR(32), qrcodes TEXT); 
```
Außerdem wird noch ein Table benötigt um den aktuellen Bestand aller Items im Schrank festzuhalten. Die Idee dahinter ist, dass für jedes Item ein Eintrag in diesem Table erstellt wird mit der dazugehörigen Item ID und ein "taken" Bit, welches für den Status des Items steht. Wenn das "taken" Bit auf 1 steht, dann ist das Item ausgeliehen und wenn es 0 steht, dann ist das Item verfügbar. Der Befehl für das Erstellen eines solchen Tables sieht so aus: 
```sql
CREATE TABLE items (qrcode VARCHAR(32), taken BIT);
```
Später wenn es wirklich Produkte in dem TechTresor geben soll, müssen diese natürlich in dem "items" Table eingetragen werden.



### 4. Code schreiben
Damit der TechTresor richtig funktioniert muss für die einzelnen Technikkomponenten Code geschrieben werden. Insgesamt haben wir drei verschiedene Skripte geschrieben, die verschiedene Teile des TechTresors steuern. Das erst Skript welches sich um das starten und steuern der ESP32-Cam kümmert befindet sich [hier](https://github.com/cbm-instructions/sixtysix/tree/main/code/WIFICam). 

Es muss auch ein Skript geschrieben werden, welches auf dem Arduino Uno läuft. In diesem befindet sich die Logik für den RFID-Scanner, Servo-Motor und LED-Strips. Der Arduino Code befindet sich [hier](https://github.com/cbm-instructions/sixtysix/blob/main/code/Arduino.ino).

Das dritte Skript ist ein Python Skript, welches auf dem konfigurierten Raspberry Pi laufen muss. Mithilfe diesem Python Skript wird eine Kommunikation zwischen dem Arduino und Raspberry ermöglicht. Das geschieht durch eine Library namens "Pyserial". Des Weiteren nimmt das Python-Skript die erfassten Artikel des Barcode-Scanners auf und speichert sie zusammen mit dem von der URL abgerufenen Bild der ESP32-Cam beim Schließen der Schranktür in die lokalen SQLite-Datenbank unter dem Table "images". Außerdem wird für jedes ausgeliehene und zurückgegebenes Item der Table "items" aktualisiert um den aktuellsten Zustand eine jeden Items zu erhalten (Mit Zustand ist gemeint ob ein Item momentan ausgeliehen ist oder nicht). Das Python Skript befindet sich [hier](https://github.com/cbm-instructions/sixtysix/blob/main/code/asdf.py).
### 5. Schranktür bauen

### 6. Technik anbringen
Die Verkabelung der Technikkomponenten ist aufgebaut wie in der folgenden Grafik dargestellt:
![Schaltplan](https://github.com/cbm-instructions/sixtysix/blob/main/images/Schaltplan.png)
Wir haben uns dafür entschieden die Kabel zu löten und eine Leiterplatte zu nutzen um die Chance von Wackelkontakten usw. zu verringern. Es ist aber natürlich auch möglich mithilfe von Breadboards und Kabelstecker ohne löten auszukommen. 

Um die Technikkomponenten bestmöglich nutzen und verstauen zu können haben wir diese in zwei verschiedenen Technikspaces angebracht. 

Der erste Technikspace befinden sich im inneren des Schrankes unterhalb der "Free Stuff" Schublade. Dort befindet sich der Raspberry Pi und der Arduino Uno. Von dort aus verlaufen alle Kabel an die einzelnen Komponenten, die entweder von dem Raspberry oder Arduino gesteuert werden. Um den Raspberry mit Strom zu versorgen muss in die Rückwand des Schrank ein Loch gebohrt werden, durch welches das Stromkabel geführt wird. Der Technikspace im inneren des Schrankes sollte am Schluss so aussehen: 
![Technik Schrank](https://github.com/cbm-instructions/sixtysix/blob/main/images/TechnikSchrank.jpg)
Innerhalb der Schranktür befindet sich der zweite Technikspace. Hier müssen nicht nur einige der steuerbaren Komponenten angebracht werden, sondern auch die Leiterplatte ist hier positioniert. Der RFID-Sensor, der Barcode-Scanner, der Servo-Motor und die Kamera müssen hier sicher befestigt werden, um ein ungewolltes Verrutschen während des Öffnens und Schließens der Tür zu verhindern. Wir empfehlen das befestigen der Komponenten durch die Verwendung mehrerer Schrauben und kleiner Holzstücke, welche z.B. den RFID-Sensor an der Tür halten. Der zweite Technikspace sollte ungefähr so aussehen:
![Technik Tür](https://github.com/cbm-instructions/sixtysix/blob/main/images/TechnikTür.jpg)
Der RFID-Sensor befindet sich in der Tür, damit ein Nutzer den TechTresor ganz simpel durch das Anhalten dessen Studi-Ausweises an der Tür den TechTresor öffnen kann. Die Kamera und Barcode-Sensor befinden sich an der Tür, damit nur wenn der TechTresor offen ist, Bilder gemacht und Items eingescanned werden können. Der Servo-Motor befindet sich in einem speziell für ihn mit einem 3D-Drucker hergestellten Behälter direkt neben dem Schloss in der Tür. Dieser Motor ermöglicht das Öffnen und Schließen des Schlosses durch einen Draht, der sowohl mit dem Servo-Motor als auch mit dem Schloss verbunden ist.


Neben den zwei großen Technispaces gibt es noch zwei kleinere Stellen an dem TechTresor, bei denen Technik benötigt wird. Die erste Stelle befindet sich oben auf dem Schrank in einem Behälter, der durch einen Lasercutter erstellt wurde. In diesem Behälter befindet sich der Motion-Sensor und Lautsprecher. Um die beiden Komponenten mit dem Arduino und Raspberry zu verbinden, muss ein Loch in die Oberseite des Schranks gebohrt werden, durch welches die Kabel gelegt werden. Das sollte zu Schluss dann so aussehen: ![Motionsensor außen](https://github.com/cbm-instructions/sixtysix/blob/main/images/MotionSensorAußen.jpg)

![Motionsensor innen](https://github.com/cbm-instructions/sixtysix/blob/main/images/MotionSensorInnen.jpg)

Zu guter Letzt befindet sich außen an beiden Seiten des Schranks ein NeoPixel LED Strip mit jeweils ca. 26 Pixeln. Um diese Strips an den Schrank anzubringen muss in den Seitenwänden ein passender großer Bereich gefräst werden und es muss an jeder Seite ein Loch in die Wände gebohrt werden um die LED Strips mit Strom usw. zu versorgen. Die LEDs müssen, wenn korrekt angebracht so aussehen: 

![LEDs](https://github.com/cbm-instructions/sixtysix/blob/main/images/LEDAußen.jpg)
## Funktionsweise
Der TechTresor hatte viele Funktionalitäten weswegen wir es für sinnvoll erachten die allgemeine Funktionsweise in einem eigenen Abschnitt zu erläutern. 

Wenn ein Studierender ein oder mehrere Items aus dem TechTresor ausleihen möchte muss dieser seinen Studi-Ausweis an den RFID-Sensor halten, der sich in der Tür befindet. In dem selben Moment macht die ESP32-Cam ein Foto von dem Inneren des Schranks. Nach kurzer Zeit öffnet der Servo-Motor das 3D-Druck Schloss, wodurch sich die Tür öffnen lässt. Jetzt kann sich der Studierende ein Produkt nehmen und an dem im inneren der Tür fixierten Barcode-Scanner abscannen. Das kann der Studierende mit beliebig vielen Produkten machen. Zum Schließen der Tür muss einfach nur wieder der Studi-Ausweis an den RFID-Reader gehoben werden. 
Zusätzlich zu diesen Hauptfunktionalitäten gibt es noch zwei weiter Features, welche den TechTresor besonders machen. Das erste Feature ist der Bewegungssensor, der sich auf dem TechTresor befindet. Mithilfe von dem Bewegungssensor wird, sobald eine Person an dem TechTresor vorbeiläuft ein zufälliger Sound durch einen eingebauten Lautsprecher abgespielt, damit wird die Aufmerksamkeit der Personen auf den TechTresor gelenkt.
Das zweite Feature sind die zwei LED-Strips die sich an den Seitenwänden des TechTresors befinden. Diese geben Auskunft darüber wie viele Items sich noch im Inneren befinden. Wenn mehr als 66% der Items nicht ausgeliehen sind, leuchten die LEDs grün. Bei weniger als 66% aber mehr als 33%, dann leuchten sie orange. Wenn weniger als 33% der Items vorhanden sind, leuchten die LEDs rot. 

## Nutzungsanleitung für Studierende

 1. Halte deinen Studi-Ausweis an das RFID-Symbol vorne am Schrank, nach kurzem Warten solltest du hören, wie sich der Schrank öffnet
 2. Suche dir anschließend das aus was du brauchst und scanne jedes Item einzeln mit dem Barcode-Scanner in der Tür
 3. Schließe die Tür und halte sie geschlossen, halte dabei deinen Studi-Ausweise erneut an das RFID-Symbol, bis du hörst, wie das Schloss sich schließt
 
 Gib deine Artikel spätestens nach 2 Wochen wieder ab, damit sie auch jemand anderem helfen können.

