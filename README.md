# TechTresor: Helfer in der Not
TechTresor ist ein smarter Schrank, der Studierenden die Möglichkeit bietet, technische Gebrauchsgegenstände ganz einfach mit ihrem Studi-Ausweis auszuleihen, um ihnen in Notfall-Situationen den Tag zu retten. Neben den technischen Gegenständen, die nur zur Ausleihe stehen, stellt der TechTresor durch die sogenannte "Free Stuff"-Schublade auch eine Reihe verschiedenster Freebies, wie z.B. Hygieneartikel und Süßigkeiten, zur Verfügung. Das Ziel davon ist es, den Aufenthalt an der Hochschule angenehmer zu gestalten.

Durch verschiedene Aufzeichnungsmethoden ist es den Betreibern des TechTresors möglich, festzustellen, welcher Studierender welchen Gegenstand ausgeliehen hat und wann. Dadurch kann geprüft werden, falls ein Gegenstand verschwunden ist, wer möglicherweise für das Verschwinden des Gegenstands verantwortlich ist.

## Die Challenge
Die Challenge, welche im Rahmen des Moduls "Challenge Based Making (WS 23/24)" gestellt wurde, lautete: "Wie können wir durch smarte Devices dabei helfen, dass die Aufenthaltsqualität an der Hochschule steigt?"   

Anhand dieser Challenge führten wir einige Interviews mit Studierenden, um herauszufinden, was die größten Auslöser für eine schlechte Aufenthaltsqualität sind. Aus dem Ergebnis der Interviews haben wir eine Persona erstellt: 
   
   ![persona](https://github.com/cbm-instructions/sixtysix/blob/main/images/POV.png)

Aufgrund dieser Persona haben wir uns dazu entschieden, den Zugang zu praktischen Technikgegenständen mithilfe des TechTresors zu ermöglichen.

# Bauanleitung
In diesem Abschnitt befindet sich die komplette Anleitung zum Bau des TechTresor. Der Code für den Arduino und Raspberry befindet sich hier:  [Code](https://github.com/cbm-instructions/sixtysix/tree/main/code)

## Materialien und Werkzeuge
### Materialien

 - Arduino Uno
 - Raspberry Pi 3
 - ESP32-Kamera
 - RFID Reader RC522
 - Ultraschall Entfernungsmesser HC-SR04
 - Lautsprecher mit AUX Anschluss
 - TIANKONGRC TS90A Servo - 3.3V
 - Leiterplatte
 - Neopixel LED mit mind. 56 Pixeln
 - Barcode-Scanner
----
 - AUX Kabel
 - USB 2.0 Cable Type A/B (Für Verbindung zwischen Raspberry und Arduino)
 - 2m 8-adriges Flachbandkabel
 - Raspberry Pi - Netzteil, 5 V, 2,5 A, Micro-USB
 ---------
- 2 x Holzplatten 120cm * 60cm * 3cm
-  Sperrholz 4mm
 - Farbe (zum Bemalen des Schranks)
 - ca. 48 Schrauben
 - 4 x Möbelrollen
 - Klebeband
 - Draht für Schloss
 - 2 x Scharniere für Schranktür
 - Kabelspirale
 - 4 x Metallwinkel
 - Muttern
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
 - Roland Schneideplotter

## Schritt für Schritt Anleitung
### 1. Schrank bauen
Zu Beginn wird der Schrankkorpus zurch Zuschneiden und Zusammenbauen der großen Holzplatten erstellt. Es ist wichtig, ausreichend Holz für die Wände, Decke und den Boden zur Verfügung zu haben. In unserem Fall haben wir ehemalige Tischplatten gewählt und diese passend mit einer Kreissäge zugeschnitten. Die genauen Schnittmaße können aus den beigefügten SVG-Dateien entnommen werden: [Schrank SVG](https://github.com/cbm-instructions/sixtysix/blob/main/images/Au%C3%9Fengestell_Ma%C3%9Fe.svg)
Dabei ist zu beachten, dass in die Decke (Nr. 5 in der SVG) ein kleines Loch gebohrt werden muss, um später die Kabel für den Entfernungsmesser und den Lautsprecher hindurchführen zu können. In die hintere Wand (Nr. 3 in der SVG) muss ein etwas größeres Loch gebohrt werden, um später das Stromkabel und gegebenenfalls ein HDMI-Kabel für den Raspberry Pi zu verlegen. Außerdem ist es erforderlich, in die Seitenwände (Nr. 1 & 2 in der SVG) einen passenden Bereich zu fräsen, um dort später die Neopixel LED Strips zu montieren. Zusätzlich muss an jeder Seite ein Loch in den gefrästen Bereich der Wände gebohrt werden, um die LED Strips mit Strom zu versorgen.

Sobald die Wände zugeschnitten und die zuvor beschriebenen Vorkehrungen getroffen wurden, ist es Zeit, die Wände miteinander zu befestigen. Dies erfolgt mit einem Akkuschrauber, mit dem die Wände miteinander verschraubt werden.

Zuerst werden die beiden Seitenwände (Nr. 1 & 2) mit der Rückwand (Nr. 3) verschraubt. Hierfür werden insgesamt 8 Schrauben benötigt: 
![Rückwand Schrauben](https://github.com/cbm-instructions/sixtysix/blob/main/images/R%C3%BCckSchrauben.png)

Als nächstes wird die Decke (Nr. 5) mit den Seitenwänden und der Rückwand verschraubt. Dazu werden 8 Schrauben benötigt: 
![Decke Schrauben](https://github.com/cbm-instructions/sixtysix/blob/main/images/DeckeSchrauben.png)

Der letzte Schritt ist das Verschrauben des Bodens mit den Wänden. Auch dazu werden 8 Schrauben benötigt:
![Boden Schrauben](https://github.com/cbm-instructions/sixtysix/blob/main/images/BodenSchrauben.png)

Am Ende soll der Schrank so aussehen: 
![Fertig Wände](https://github.com/cbm-instructions/sixtysix/blob/main/images/SchrankW%C3%A4ndeFertig.jpg)

### 2. Schrankinneres erstellen
#### 2.1 Innenleben
Das TechTresor-Innenleben kann natürlich den eigenen Bedürfnissen (größe der Fächer etc.) individuell angepasst werden. Wir haben uns für folgende Aufteilung entschieden, welche in dieser Anleitung näher beschrieben wird:
![Nahaufnahme innen](https://github.com/cbm-instructions/sixtysix/blob/main/images/InnenFertig.jpg)

Als erstes werden 3 Sperrholzplatten (Maße: [Platte SVG](https://github.com/cbm-instructions/sixtysix/blob/main/images/Regalex2_Maße.svg)) auf Innenhöhe 15cm, 45cm und 50cm angebracht.
Auf die unterste Platte wird das Regal mit den 8 Fächern gelegt und befestigt (Maße: [Fächer SVG](https://github.com/cbm-instructions/sixtysix/blob/main/images/Unterteilungsfachx8_Maße.svg)).
Es empfiehlt sich, das Regal aus Sperrholz zu fertigen und dabei den Lasercutter zu nutzen. Dies gilt auch für das Pegboard und die USB-Sticks-Schublade. Pegboard und USB-Sticks-Schublade werden wiederum auf des Regal geschoben und befestigt.
- Maße Pegboard mit passenden Pins: [Pegboard und Pins SVG](https://github.com/cbm-instructions/sixtysix/blob/main/images/PegboardPlusPin_Maße.svg)
- Maße USB-Sticks-Schublade: [USB-Sticks-Schublade SVG](https://github.com/cbm-instructions/sixtysix/blob/main/images/UsedSticks_Schublade_Maße.svg)

#### 2.2 Entfernungsmesser Box
Auf dem Schrank wird folgende Box aus Sperrholz entstehen (Maße für den Lasercutter: [Entfernungsmesser Box SVG](https://github.com/cbm-instructions/sixtysix/blob/main/images/LautsprecherBox_Oben_Maße.svg)):
![Entfernungsmesser Box](https://github.com/cbm-instructions/sixtysix/blob/main/images/MotionSensorAußen.jpg)
Die Box wird zunächst nur zusammengebaut und dann im weiteren Verlauf der Anleitung weiter bearbeitet und schließlich mittig auf den Schrank geklebt.

### 3. Technik konfigurieren
#### 3.1 Raspberry
Es empfiehlt sich, den Raspberry neu aufzusetzten und `sudo apt update` & `sudo apt upgrade` im Terminal auszuführen. Eine IDE (Geany), um einfache Scripte zu schreiben, sollte bereits installiert sein. Auch python3 sollte vorinstalliert sein. Selbst nach Fertigstellung der Box, kann der Raspberry per HDMI mit einem Monitor und per USB/Bluetooth mit einer Maus & Tastatur verbunden sein, um stets den Überlick über ablaufende Prozesse im TechTresor zu behalten.

#### 3.2 Arduino Uno

 1. Installiere die Arduino IDE
 2. Öffne `Tools/Board` in der Arduino IDE und wähle den Arduino Uno
 3. Öffne  `Tools/Port`  und wähle den COM Port, mit dem der Arduino Uno verbunden ist
 4. Damit das Projekt funktionieren kann, müssen folgende Libraries über den Library Manager (`Tools/Manage Libraries`) installiert werden:
    - Adafruit NeoPixel
    - MFRC522
    - Servo

#### 3.3 ESP32-Cam
1.  Öffne  `File/Preferences`
2.  Gebe folgendes in das  `Additional Board Mananger URLs`  Feld ein: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
und http://arduino.esp8266.com/stable/package_esp8266com_index.json
3.  Öffne  `Tools/Board/Boards Manager`
4.  Suche nach ESP32 und klicke den  `install`  Knopf für  `ESP32 by Espressif Systems`

Der Code für die ESP32-Cam ist eine angepasste Version von folgendem Open Source Projekt: https://github.com/yoursunny/esp32cam/tree/main/examples/WifiCam
#### 3.4 Barcode-Scanner
Der Barcode-Scanner wird mit dem Raspberry verbunden. Dazu kann folgendes Tutorial verwendet werden: TODO.

#### 3.5 RFID Reader
Der "RFID Reader RC522" wird mit dem Arduino verbunden. Wie das funktioniert, wird sehr gut in diesem Tutorial beschrieben: https://arduinogetstarted.com/tutorials/arduino-rfid-nfc.

#### 3.6 Datenbank erstellen
Um die beim Öffnen der Tür entstehenden Bilder zu speichern und stets den aktuellen Bestand der Produktverfügbarkeit zu erfassen, ist eine Datenbank erforderlich. Wir haben uns für eine SQLite-Datenbank entschieden, die lokal auf dem Raspberry Pi läuft. Dafür muss SQLite wie folgt über das Terminal auf dem Raspberry Pi heruntergeladen werden: 
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
Die Datenbank ist nun vorhanden, aber es fehlen noch zwei Tabellen, in die die Daten geschrieben werden sollen. Eine Tabelle wird für die Aktivität des TechTresors benötigt. Das bedeutet konkret, dass für jede Türschließung die eindeutige ID des Studienausweises, das entstandene Bild und alle ausgeliehenen Gegenstände dieses Studierenden in die Tabelle geschrieben werden. Diese Tabelle nennen wir vorläufig "images". Um eine solche Tabelle zu erstellen, muss der folgende Befehl ausgeführt werden:
```sql
CREATE TABLE images (image BLOB, uid VARCHAR(32), qrcodes TEXT); 
```
Zusätzlich wird eine weitere Tabelle benötigt, um den aktuellen Bestand aller Gegenstände im Schrank festzuhalten. Die Idee dabei ist, dass für jedes Objekt ein Eintrag in dieser Tabelle erstellt wird, der die entsprechende Objekt-ID und ein "taken"-Bit enthält, das den Status des Objekts angibt. Wenn das "taken"-Bit den Wert 1 hat, ist das Objekt ausgeliehen, andernfalls, wenn es den Wert 0 hat, ist das Objekt verfügbar. Der Befehl zum Erstellen einer solchen Tabelle sieht wie folgt aus: 
```sql
CREATE TABLE items (qrcode VARCHAR(32), taken BIT);
```
Später wenn es wirklich Produkte in dem TechTresor geben soll, müssen diese natürlich in dem "items" Tabelle eingetragen werden.



### 4. Code schreiben
Damit der TechTresor richtig funktioniert muss für die einzelnen Technikkomponenten Code geschrieben werden. Insgesamt haben wir drei verschiedene Skripte geschrieben, die verschiedene Teile des TechTresors steuern. Das erst Skript welches sich um das starten und steuern der ESP32-Cam kümmert befindet sich [hier](https://github.com/cbm-instructions/sixtysix/tree/main/code/WIFICam). 

Es muss auch ein Skript geschrieben werden, welches auf dem Arduino Uno läuft. In diesem befindet sich die Logik für den RFID-Scanner, Servo-Motor und LED-Strips. Der Arduino Code befindet sich [hier](https://github.com/cbm-instructions/sixtysix/blob/main/code/Arduino.ino).

Das dritte Skript ist ein Python-Skript, das auf dem konfigurierten Raspberry Pi ausgeführt werden muss. Dieses Python-Skript ermöglicht die Kommunikation zwischen dem Arduino und dem Raspberry Pi mithilfe einer Bibliothek namens "Pyserial". Darüber hinaus erfasst das Python-Skript die Artikel des Barcode-Scanners und speichert sie zusammen mit dem von der URL abgerufenen Bild der ESP32-Cam beim Schließen der Schranktür in die lokale SQLite-Datenbank unter dem Tabellennamen "images". Zusätzlich wird für jedes ausgeliehene und zurückgegebene Objekt die Tabelle "items" aktualisiert, um den aktuellen Status jedes Objekts zu verfolgen (mit Status ist gemeint, ob ein Objekt derzeit ausgeliehen ist oder nicht). Das Python-Skript befindet sich [hier](https://github.com/cbm-instructions/sixtysix/blob/main/code/asdf.py).
### 5. Schranktür bauen
So wird die fertige TechTresor-Tür aus Sperrholz aussehen:
![Fertige Tür](https://github.com/cbm-instructions/sixtysix/blob/main/images/TürFertig.jpg)
- Maße der Tür: [Tür SVG](https://github.com/cbm-instructions/sixtysix/blob/main/images/Tür_Maße.svg)
- Maße Tür-Cover, hinter welches später Technik befestigt wird: [Tür-Cover SVG](https://github.com/cbm-instructions/sixtysix/blob/main/images/TürCover_Maße.svg)
- Die Tür wird mit den Scharnieren am Schrank befestigt, wie es auf dem Bild zu erkennen ist. Der Tür-Cover wird erst im weiteren Verlauf angebracht.

### 6. Technik anbringen
Die Verkabelung der Technikkomponenten ist aufgebaut wie in der folgenden Grafik dargestellt:
![Schaltplan](https://github.com/cbm-instructions/sixtysix/blob/main/images/Schaltplan.png)
Wir haben uns dafür entschieden die Kabel zu löten und eine Leiterplatte zu nutzen um die Chance von Wackelkontakten usw. zu verringern. Es ist aber natürlich auch möglich mithilfe von Breadboards und Kabelstecker ohne löten auszukommen. 

Um die Technikkomponenten bestmöglich nutzen und verstauen zu können haben wir diese in zwei verschiedenen Technikspaces angebracht. 

Der erste Technikspace befinden sich im inneren des Schrankes unterhalb der "Free Stuff" Schublade. Dort befindet sich der Raspberry Pi und der Arduino Uno. Von dort aus verlaufen alle Kabel an die einzelnen Komponenten, die entweder von dem Raspberry oder Arduino gesteuert werden. Um den Raspberry mit Strom zu versorgen muss in die Rückwand des Schrank ein Loch gebohrt werden, durch welches das Stromkabel geführt wird. Der Technikspace im inneren des Schrankes sollte am Schluss so aussehen: 
![Technik Schrank](https://github.com/cbm-instructions/sixtysix/blob/main/images/TechnikSchrank.jpg)
Innerhalb der Schranktür befindet sich der zweite Technikspace. Hier müssen nicht nur einige der steuerbaren Komponenten angebracht werden, sondern auch die Leiterplatte ist hier positioniert. Der RFID-Sensor, der Barcode-Scanner, der Servo-Motor und die Kamera müssen hier sicher befestigt werden, um ein ungewolltes Verrutschen während des Öffnens und Schließens der Tür zu verhindern. Wir empfehlen das befestigen der Komponenten durch die Verwendung mehrerer Schrauben und kleiner Holzstücke, welche z.B. den RFID-Sensor an der Tür halten. Der zweite Technikspace sollte ungefähr so aussehen:
![Technik Tür](https://github.com/cbm-instructions/sixtysix/blob/main/images/TechnikTür.jpg)
Der RFID-Sensor befindet sich in der Tür, damit ein Nutzer den TechTresor ganz simpel durch das Anhalten dessen Studi-Ausweises an der Tür den TechTresor öffnen kann. Die Kamera und Barcode-Sensor befinden sich an der Tür, damit nur wenn der TechTresor offen ist, Bilder gemacht und Items eingescanned werden können. Der Servo-Motor befindet sich in einem speziell für ihn mit einem 3D-Drucker hergestellten Behälter direkt neben dem Schloss in der Tür. Dieser Motor ermöglicht das Öffnen und Schließen des Schlosses durch einen Draht, der sowohl mit dem Servo-Motor als auch mit dem Schloss verbunden ist. Um die Kabel zu schützen lohnt es sich alle Kabel, die vom Technikspace im TechTresor zum Technikspace in der Tür führt durch eine Kabelspirale zu führen.


Neben den zwei großen Technikspaces gibt es noch zwei kleinere Stellen an dem TechTresor, bei denen Technik benötigt wird. Die erste Stelle befindet sich oben auf dem Schrank in einem Behälter, der durch einen Lasercutter erstellt wurde. In diesem Behälter befindet sich der Motion-Sensor und Lautsprecher. Um die beiden Komponenten mit dem Arduino und Raspberry zu verbinden, muss ein Loch in die Oberseite des Schranks gebohrt werden, durch welches die Kabel gelegt werden. Das sollte zu Schluss dann so aussehen: ![Motionsensor außen](https://github.com/cbm-instructions/sixtysix/blob/main/images/MotionSensorAußen.jpg)

![Motionsensor innen](https://github.com/cbm-instructions/sixtysix/blob/main/images/MotionSensorInnen.jpg)

Zu guter Letzt befindet sich außen an beiden Seiten des Schranks ein NeoPixel LED Strip mit jeweils ca. 26 Pixeln. Die Strips müssen nun in den in Schritt 1 erläuterten gefrästen Bereichen eingelegt werden und die Kabel durch ein kleines Loch geführt werden.  Die LEDs müssen, wenn korrekt angebracht so aussehen: 

![LEDs](https://github.com/cbm-instructions/sixtysix/blob/main/images/LEDAußen.jpg)
### 7. Free Stuff Schublade
Die Idee hinter der Free Stuff Schublade ist, dass Studierende sich nicht nur Technikgegenstände ausleihen können sondern auch kleiner Artikel kostenlos erhalten können. Solche Artikel sind beispielsweise Süßgikeiten oder Hygieneartikel.

Die Free Stuff Schublade besteht aus Sperrholz, dass nach folgenden Maßen zugeschnitten werden muss: [Free Stuff SVG](https://github.com/cbm-instructions/sixtysix/blob/main/images/FreeStuffSchublade_Ma%C3%9Fe.svg). Die Schublade muss zusammengesteckt werden und anschließend oberhalb des Technikspaces im inneren des TechTresors angebracht werden. 

Am Schluss muss die montierte Schublade so angebracht werden wie oben im Bild: ![Free Stuff Schublade](https://github.com/cbm-instructions/sixtysix/blob/main/images/FreeStuff.jpg)
### 8. Letzte Kleinigkeiten
Zum Schluss müssen noch ein paar letzte Kleinigkeiten gemacht werden um den TechTresor zu vervollständigen. Als erstes müssen die Neopixel Strips, die sich an der Seite befinden mit einer Plexiglas Abdeckung geschützt werden. Diese muss mit einem Lasercutter zugeschnitten werden. Auch dazu gibt es eine SVG-Datei: [Plexiglas](https://github.com/cbm-instructions/sixtysix/blob/main/images/LED_Plexiglascover_Ma%C3%9Fe.svg)

Um den TechTresor zu verschönern und den Nutzern wichtige Hinweise zu geben sind Sticker für den RFID-Reader, die Free Stuff Schublade, den Barcode Scanner und die benutzte USB-Sticks Schublade ein guter Weg. Die Sticker müssen natürlich an den korrekten Stellen angebracht werden um den Nutzer mitzuteilen, wo sich welches Komponent am TechTresor befindet. Die Sticker befinden sich in folgender SVG-Datei: [Sticker](https://github.com/cbm-instructions/sixtysix/blob/main/images/Vinyl_Sticker_Ma%C3%9Fe.svg)

Um die gesamte Technik im TechTresor zu verbergen, müssen die beiden Technikräume, wie sie im Schritt 7 erklärt wurden, abgedeckt werden. Dazu müssen zwei weitere Stücke Sperrholz mit dem Lasercutter zugeschnitten werden: ein Stück für den Technikraum im [Schrankinneren](https://github.com/cbm-instructions/sixtysix/blob/main/images/TechnikspaceCover_Ma%C3%9Fe.svg) und einen für den Technikraum in der [Tür](https://github.com/cbm-instructions/sixtysix/blob/main/images/TürCover_Maße.svg) (hier nochmal die Maße). Bei der Abdeckung für die Tür ist darauf zu achten, dass der Barcode-Scanner und die Kamera korrekt durch die Löcher in der Abdeckung geführt werden, damit weder die Linse noch der Scanner verdeckt werden.

Jetzt da der TechTresor fertig gebaut wurde, müsst er ungefähr so aussehen: 

Entfernungsmesser und Free Stuff Schublade: ![oben](https://github.com/cbm-instructions/sixtysix/blob/main/images/ObenFertig.jpg)

Das Innere des TechTresors: 
![oben](https://github.com/cbm-instructions/sixtysix/blob/main/images/InnenFertig.jpg)

Das Äußere des TechTresors: 
![oben](https://github.com/cbm-instructions/sixtysix/blob/main/images/AußenFertig.jpg)

Von hinten:
![oben](https://github.com/cbm-instructions/sixtysix/blob/main/images/HintenFertig.jpg)

Fertige Tür:
![oben](https://github.com/cbm-instructions/sixtysix/blob/main/images/TürFertig.jpg)

## Funktionsweise
Angesichts der Vielzahl an Funktionen des TechTresors halten wir es für sinnvoll, die allgemeine Funktionsweise in einem separaten Abschnitt zu erläutern.

Wenn ein Studierender ein oder mehrere Gegenstände aus dem TechTresor ausleihen möchte, muss er seinen Studienausweis an den RFID-Sensor halten, der sich in der Tür befindet. In diesem Moment macht die ESP32-Cam ein Foto vom Inneren des Schranks. Nach kurzer Zeit öffnet der Servo-Motor das 3D-gedruckte Schloss, wodurch sich die Tür öffnen lässt. Jetzt kann der Studierende ein Produkt entnehmen und es am im Inneren der Tür angebrachten Barcode-Scanner scannen. Diesen Vorgang kann der Studierende mit beliebig vielen Produkten wiederholen. Zum Schließen der Tür muss lediglich erneut der Studienausweis an den RFID-Reader gehalten werden.

Zusätzlich zu diesen Hauptfunktionalitäten verfügt der TechTresor über zwei weitere Features, die ihn besonders machen. Das erste Feature ist der Bewegungssensor, der am TechTresor angebracht ist. Wenn eine Person an dem TechTresor vorbeigeht, wird durch den Bewegungssensor ein zufälliger Sound über einen eingebauten Lautsprecher abgespielt, um die Aufmerksamkeit auf den TechTresor zu lenken.

Das zweite Feature sind die zwei LED-Strips, die sich an den Seitenwänden des TechTresors befinden. Sie zeigen an, wie viele Gegenstände sich noch im Inneren befinden. Wenn mehr als 66% der Gegenstände nicht ausgeliehen sind, leuchten die LEDs grün. Bei weniger als 66%, aber mehr als 33%, leuchten sie orange. Wenn weniger als 33% der Gegenstände vorhanden sind, leuchten die LEDs rot.

## Nutzungsanleitung für Studierende

 1. Halte deinen Studi-Ausweis an das RFID-Symbol vorne am Schrank, nach kurzem Warten solltest du hören, wie sich der Schrank öffnet
 2. Suche dir anschließend das aus was du brauchst und scanne jedes Item einzeln mit dem Barcode-Scanner in der Tür
 3. Schließe die Tür und halte sie geschlossen, halte dabei deinen Studi-Ausweise erneut an das RFID-Symbol, bis du hörst, wie das Schloss sich schließt
 
 Gib deine Artikel spätestens nach 2 Wochen wieder ab, damit sie auch jemand anderem helfen können.

