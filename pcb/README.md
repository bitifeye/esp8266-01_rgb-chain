## Here you get a description what you need to do to get the circuit board.

### Steps:
1.	Install "KiCad". It can be downladed here: http://kicad-pcb.org/
2.	Open KiCad and open the kicad-project. You find it in the folder "PCB" and it ends on ".pro".
3.	If you want you can change now somthing in the schematic or in the laylout.
4.	If you done, search for an provider of PCB-production. A good one is PCB-Pool (https://www.pcb-pool.com/)

	But you can choose your own. You can find a list here: https://www.mikrocontroller.net/articles/Platinenhersteller
	
	Check what kind of files (gerber-files or the pcb-files) your provider need. KiCad can also generate the gerber-files.
	If you make your order make sure that the circuit  board only has a depth of 1,0mm. Otherwise it will not fit in the control box.
5.	While your PCB is in processing you can order the components for the board. For that have a look in the [component_list.txt](https://github.com/bitifeye/esp8266-01_rgb-chain/blob/master/component_list.txt).
6.	If you have your board and the components you can solder everything on its position.
	For the connection to the RGB-LED-Chain you can use the old cabels. Unsolder the cabels from the old circuit 
7.	If you connect the cabels to the RGB-LED-Chain make sure you connect the right one to the appropriate hole.
	Do not trust the color of the cabel-isolation.
