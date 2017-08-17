# Here you get a description what you need to do to program and run the ESP-01.

## Downloads and instalation:
1.	Download the project
2.	Install the "Arduino IDE" (you can download it here: https://www.arduino.cc/en/Main/Software)
3.	Install the ESP8266 Platform to your "Arduino IDE". The P I C T U R E will show you or you can follow the link: http://esp8266.github.io/Arduino/versions/2.0.0/doc/installing.html#boards-manager
4.	Install the SPIFFS by following this manual until Step 3 http://www.instructables.com/id/Using-ESP8266-SPIFFS/
5.	Install the "ArduinoJson"-library as shown on the P I C T U R E
6.	Install the driver for the TTL-232R-Cabel https://cdn.sparkfun.com/assets/learn_tutorials/7/4/CDM_v2.12.00_WHQL_Certified.exe
	  You can find a quick install tutorial here: https://learn.sparkfun.com/tutorials/how-to-install-ftdi-drivers/all

## Program the ESP-01:
1.	Open the "src\main" folder
2.	Open the main.ino in the folder
3.	Connect the TTL-232R-Cabel to your PC
4. 	Set the right board-options as shown on the P I C T U R E and select the right "COM"-Port
5.	Connect your ESP-01 as shown on the schematic. Make sure that the ESP-01 only connect to an 3,3V DC-power-supply.
	  For the right connection have a look for the pinout at the datasheet of the TTL-232R-Cabel (http://www.ftdichip.com/Support/Documents/DataSheets/Cables/DS_TTL-232R_CABLES.pdf)
	  If you want you can also use an ESP-01 programmer board (http://www.ebay.de/itm/like/262988751030?chn=ps&dispItem=1). Here you can get a good interduction:https://www.xgadget.de/anleitung/esp-01-esp8266-mit-adapter-programmieren-so-gehts/
6.	Reset your ESP-01 by pull the "RST"-Pin to "GND" and releas him again
7.	Upload the data-folder. Click Tools->ESP8266 Sketch Data Upload.
	  Make sure that the "Serial Monitor" is closed while this process.
8.	Reset your ESP-01 again by repeating point 6.
9.	Upload the scetch by pressing "STRG+U" or click the upload-button in the left upper corner.
	  If you want to see the fist debugging-news you can open the "Serial Monitor" and set him to the baud rate 9600. Do this befor you upload the scetch.
10.	If everything worked fine you can release the connections and put him in to the circuit board.
11.	Put the circuit board with the ESP-01 in the control box and close it. Connect the power supply and the RGB-LED-Chain.
	  Connect your device to the ESP-01 and have fun.
