#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

int LED = 8;
int BUTTON = 7;
int timelapse = 0;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean message;
boolean started = false;
boolean timer = false;
long startTime;
long endTime;
long randomTime;
float elapsedTime;

void setup() {
  // put your setup code here, to run once:
pinMode(LED,OUTPUT);
digitalWrite(LED, LOW);

pinMode(BUTTON,INPUT);

lcd.begin(16,2);
Serial.begin(9600);


lcd.print("Start?");
lcd.setCursor(0,1);
lcd.print("Press button");

int go = 0;
while (go == 0) {
  go =digitalRead(BUTTON);
}
lcd.setCursor(0,0);
lcd.print("REACTION GAME GO!");
lcd.setCursor(0,1);
lcd.print("                 ");
delay(1000);
lcd.setCursor(0,0);
lcd.print("Press the button ");
delay(1000);
lcd.setCursor(0,0);
lcd.print("when the light   ");
delay(1000);
lcd.setCursor(0,0);
lcd.print("turns ON........");
delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  lcd.noDisplay(); // wipe out instructions
  
  
  //wait for a button press
  
  while (digitalRead(BUTTON)== LOW) {
    
  }
  
  lcd.display();

  started = !started; // we've started the game!! or ended the game!!
  
  
  if (started == true && timer == false) {
          //start the random timer
          randomTime = random(4,10)*1000; //get a random number btw 4 and 10, *1000 to seconds
      
          
          //switch the light on once to say the game is starting
          message = false;
          if (!message) {
            lcd.setCursor(0,0);
            lcd.print("game has started   ");
            lcd.setCursor(0,1);
            lcd.print("                   ");
            delay(500);
            message = true;
          }
          
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED,LOW);
      
          //wait for a random amount of time
          delay(randomTime);
      
          //now start timing the player
          startTime=millis();
          //switch the light on
         
          digitalWrite(LED,HIGH);
          //start timing
           timer = true;
    
    }//game started

   if (started == true && timer == true) {
    //the game has started and we are timing, so we must be waiting for the button press!
      
    while (digitalRead(BUTTON)== LOW) {
    
    }
    // button was pressed... let's stop and work out elaspsed time
    started=false;
    
   }
   
   if (started == false && timer == true) {
        digitalWrite(LED,LOW);
        // this means they are being timed, and the button press has arrived since !
        endTime=millis();
        elapsedTime= endTime-startTime;
        elapsedTime= elapsedTime/1000;
        lcd.setCursor(0,0);
        lcd.print("you took         ");
        lcd.setCursor(0,1);
        lcd.print(elapsedTime);
        delay(2000); // wait a bit before the game starts again...
        
        timer=false; // go back to initial state
    }//timing 


 
}//  main loop
