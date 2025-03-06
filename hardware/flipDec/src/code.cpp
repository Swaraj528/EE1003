#include <Arduino.h>

//Declaring all variables as integers
int Z=0,Y=0,X=0,W=0, A, B, C, D;

//Code released under GNU GPL.  Free to use for anything.
void disp_7447(int D, int C, int B, int A)
{
	digitalWrite(2, A); //LSB
	digitalWrite(3, B); 
	digitalWrite(4, C); 
	digitalWrite(5, D); //MSB

}
// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(2, OUTPUT);  
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, INPUT);  
	pinMode(7, INPUT);
	pinMode(8, INPUT);
	pinMode(9, INPUT);

}

// the loop function runs over and over again forever
void loop() {
	disp_7447(W,X,Y,Z);  
	delay(1000);
	A=W;B=X;C=Y;D=Z;
	W = (A&(!B)&(!C)&(!D))|((!A)&B&C&D);
  X = ((!A)&(!B)&C&D)|(B&(!C))|(B&B&(!D));
  Y = ((!A)&(!C)&D)|(C&(!D));
  Z = !D;
	}
