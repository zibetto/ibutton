#include <OneWire.h>

OneWire ibutton (2); // I button connected on PIN 2.

byte ibuttonid[10] = {1,144,74,165,21,0,0,143}; // Ibutton ID must be typed in Decimal in the following order: Family code (01 for DS1990); numbers from R. to L.; CRC. 
byte buffer[10]; //array to store the readed Ibutton ID.

boolean result;  // this variable will hold the compare result

int doorpin = 13; // the output pin to activate the door.

void setup(){
    Serial.begin(9600); 
    pinMode(doorpin,OUTPUT);
   
}

void loop(){
   
 if (!ibutton.search (buffer)){//read attached ibutton and asign value to buffer
    ibutton.reset_search();
    delay(200);
    return;
 }
  
  for (int x = 0; x<8; x++){  
    Serial.print(buffer[x],HEX); //print the buffer content in LSB. For MSB: for (int x = 8; x>0; x--) 
    Serial.print(" "); // print a space
   }
   Serial.println("\n"); // print new line
   
   // compare the ibutton id
   
  result = true; // set variable equal to one.
  for (int x=0; x<10; x++){ 
  int compare1 = ibuttonid[x];// asign each index of arrays to test, one by one and compare
  int compare2 = buffer[x];
  
  
  if(compare1 != compare2){ // if any index comparison is not equal, then the arrays are not equal and result will be 0.
   result = false; 
  }
  
  }
  if(result == true){ // if the arrays are equal, do something.
   Serial.println("Door open for 5 seconds."); 
   digitalWrite(doorpin,HIGH); // Turn on LED on pin 13 (build-in on the Arduino board)
   delay(5000); // wait five seconds. (1 second = 1000 milliseconds)
   Serial.println("Door closed");
   digitalWrite(doorpin,LOW); // turn off LED.
 }
   
    //set buffer back to cero.
    
    for (int x=0; x<10; x++){
     buffer[x] = 0 ;
    }                
}

