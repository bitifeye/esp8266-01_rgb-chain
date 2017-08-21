# An RGB-Chain controlled by the ESP-01
This is an project to control a RGB-chain with the ESP-01 by WiFi.
The Esp-01 will programmed by the Arduini IDE and fit in a selfmade circuit board which will replace the old one of the RGB-chain.

## Components
To run the project you need some components. 
You find a list of them [here](https://github.com/bitifeye/esp8266-01_rgb-chain/blob/master/component_list.txt).

## Folder structure
Exery folder has its own readme for more details.
- [components](https://github.com/bitifeye/esp8266-01_rgb-chain/blob/master/component_list.txt)
  Here will you find a list of all components you need.

- [pcb](https://github.com/bitifeye/esp8266-01_rgb-chain/tree/master/pcb)
  Here will you find informations about the circuit board.

- [src](https://github.com/bitifeye/esp8266-01_rgb-chain/tree/master/src)
  In this folder is the sourcecode.
  You will also find some information how to use it.
  
## Using
Create the cuircit board by following the [instructions](https://github.com/bitifeye/esp8266-01_rgb-chain/blob/master/pcb/README.md). Programm the ESP-01 with the main.ino and stick him in the cuircit board.<br>
After that the ESP-01 will create an AP by default with name: "ESP-01". There is no password. If you are connected to the ESP-01 you can call him by "esp8266.local" form your PC. For this you have to install the [Bonjour](https://support.apple.com/bonjour), if you use an Linux-System use the [Avahi](http://avahi.org/). Calling the hostname don't work with an Android-System yet.
After calling the ESP-01 you can get the IP-Address by clicking the appropriate button. With this IP-Address you can use the system with any devices.<br>
If you set a new WiFi-connection, e.g. your own WiFi-network, the ESP-01 try to connect as a station, if that fail it create an AP agin. For that use the SSID of your network (the WiFi-name) and the matching password.<br>
For using the system by a smartphone, you have to look for the IP-Address. Either look in your router or call by your PC "esp8266.local" in your browser and click the "Get the IP-Address"-button. Now you can see the IP-Address which you can use to connect your smartphone or tablet.<br>
Make sure that the ESP-01 and the using device are both in the same network. Otherwise it will not work yet.
  
## Possible extensions of the project
- The circuit board has the opportunity to receive th IR-signal from the old remote controler.
  But the code for that aren't implemented yet.

## License
The whole project is under the GPLv3.<br>
For more ditails have a look in the [License](https://github.com/bitifeye/esp8266-01_rgb-chain/blob/master/LICENSE) 
