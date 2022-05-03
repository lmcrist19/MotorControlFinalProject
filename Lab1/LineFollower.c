/*
 * LineFollower.c
 *
 * Created: 4/6/2022 9:58:02 PM
 * Author : Lauren Crist
*/

#include "F_cpu_lib.h" //Set clock frequency
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_lib.h" //LCD library
#include "Serial_lib2.h" //Serial Communication library
#include "Motor_PWM_lib.h" //Motor Control library

uint8_t leftMotor = 0;
uint8_t rightMotor = 1;
uint8_t forwardDir = 0;
uint8_t reverseDir = 1;

int main(void)
{
	char mode; //Character sent by VS using Serial
		
	LCD_init();
	USART_vInit();
	HBridgeInit();
	
	sei(); //Enable interrupts
	
	LCDGoToPosition(1, 1);
	LCDSendString("Good morning Lauren");
	
	while(1)
	{
		
		mode = USART_vReceiveByte(); //set mode to received byte
		
		LCDGoToPosition(1, 3);
		LCDSendString(mode);

		switch(mode)
		{
			case 'C':
			{
				LCDClearScreen();
				HBridgeCommand(leftMotor, 90, forwardDir); //motor speed differed all the time
				HBridgeCommand(rightMotor, 88, forwardDir);
				LCDGoToPosition(1, 1);
				LCDSendString("Going straight");
				break;
			}
			case 'l':
			{	
				LCDClearScreen();
				HBridgeCommand(leftMotor, 75, forwardDir);
				HBridgeCommand(rightMotor, 100, forwardDir);
				LCDGoToPosition(1, 1);
				LCDSendString("Turning slightly left"); 
				break;
			}
			case 'L':
			{
				LCDClearScreen();
				HBridgeCommand(leftMotor, 10, forwardDir);
				HBridgeCommand(rightMotor, 100, forwardDir);
				LCDGoToPosition(1, 1);
				LCDSendString("Turning hard left");
				break;
			}
			case 'r':
			{
				LCDClearScreen();
				HBridgeCommand(leftMotor, 100, forwardDir); 
				HBridgeCommand(rightMotor, 75, forwardDir);
				LCDGoToPosition(1, 1);
				LCDSendString("Turning slightly right");
				break;
			}
			case 'R':
			{
				LCDClearScreen();
				HBridgeCommand(leftMotor, 100, forwardDir); //drastic differences worked best
				HBridgeCommand(rightMotor, 10, forwardDir);
				LCDGoToPosition(1, 1);
				LCDSendString("Turning hard right");
				break;
			}
			case 'X':
			{
				LCDClearScreen();
				HBridgeCommand(leftMotor, 0, forwardDir);
				HBridgeCommand(rightMotor, 0, forwardDir);
				LCDGoToPosition(1, 1);
				LCDSendString("Stopping...");
				break;
			}
		}
	}
}

