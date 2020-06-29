By using STM32_Programmer_V2.py python script here, you can run it on your host (Computer) so that you can burn new binary file on your board.
First, you need to erase the sector specified to flash you code on it.
Second, you will write your binary file on the flash
Finally you will jump to the first address of your speicifed sector.
This Bootloade is the second version.
Some Features:
- New Interface
- Added new commands (like Chip ID, RDP Status, Enable/Disable FLash Read/Write protection
- Read Sector Read/Write Status
Here i attached user_app.bin as my binary code example.
Iam using TrueStudio IDE.
Make sure that in your user application that you Enable the interrupt by assembly and set the VTOR Register to the start address where your code will be flashed on the flash. 
Ex:
	/* Enable IRQ because it was disabled in the bootloader before Jump here */
	asm("MOV R0,#0");
	asm("MSR PRIMASK,R0");

	/* Set Vector table to the first adddress of the sector 2 (SP) */
	SCB_VTOR = (SECTOR2_BASE_ADDRESS);
Also you need to modify the linker script on your user app (FLASH Origin address) to make it start at the address you want to flash you code.
Thanks for FastBit Embedded for explanation and Python code
