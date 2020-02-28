//**************************************************
//  Simple Rocket Launch V1.0 by Norf
//  27.02.2020
//**************************************************

#define IgnitionTIME    1500    // Ignition current duration in milliseconds.

#define ArmButt       4         // Pin connected to the Arm button.
#define LaunchButt    5         // Pin connected to the Launch button.
#define ArmLED        6         // Pin connected to the Arm LED.
#define LaunchLED     7         // Pin connected to the Launch LED.
#define Ignition     13         // Pin connected to the Fuse N_Fet. SET TO PIN 13 ( INTERNAL LED ) FOR TESTING!!
//#define Ignition   10         // Pin connected to the Fuse N_Fet. SET TO YOUR IGNITION PIN AFTER ALL IS FINE!!
#define Buzzer       11         // Connected to a Buzzer.


//**************************************************
// Setup
//**************************************************
void setup() 
{
  pinMode(ArmButt, INPUT);          // set "ARM" button pin to input
  pinMode(LaunchButt, INPUT);       // set "GO" button pin to input
  pinMode(ArmLED, OUTPUT);          // set "ARM" LED pin to output
  pinMode(LaunchLED, OUTPUT);       // set "GO" LED pin to output
  pinMode(Ignition,OUTPUT);         // set "Fuss" pin to output
  pinMode(Buzzer,OUTPUT);           // set "Buzzer" pin to output

  digitalWrite(ArmButt, HIGH);      // turn on pullup resistor 
  digitalWrite(LaunchButt, HIGH);   // turn on pullup resistor 
  digitalWrite(Ignition,LOW);       // OPEN the ignition circuit
  

// Startup Sound
//**************************************************
 tone(Buzzer, 1000, 100);
 delay(200);
 tone(Buzzer, 1500, 100);
 delay(200);
 tone(Buzzer, 2000, 100);
 delay(500);
 tone(Buzzer, 2000, 100);
 delay(200);
 tone(Buzzer, 1500, 100);
 delay(200);
 tone(Buzzer, 1000, 500);
 delay(200);
}

int  DownCntr;           // down counter 
int  Cntdown  = 0;       // Countdown inactiv = 0 

//**************************************************
// Main Loop
//**************************************************
void loop() 
{
// Cancle Countdown
//**************************************************
 if(!digitalRead(LaunchButt)||!digitalRead(ArmButt)){
    Cntdown=0;                                          // Cancel Countdown
    DownCntr=0;
    digitalWrite(Buzzer,HIGH);
    delay(2000);
    digitalWrite(Buzzer,LOW);
  }

  if(Cntdown==0){
    WaitARM();  
    WaitLaunch();
  }
// Countdown Beep
//**************************************************
  if (DownCntr > 30){
      if (DownCntr % 10 ==0)tone(Buzzer, 1000, 50);  //Tone every second.
     }
  else if (DownCntr % 5 ==0)tone(Buzzer, 2000, 50);  //Tone every 1/5 second.

// ROCKET LAUNCH!!!
//**************************************************
  if (DownCntr ==0){
    //**************************************************
    tone(Buzzer, 440, IgnitionTIME);   
    digitalWrite(Ignition,HIGH);          
    delay(IgnitionTIME);
    digitalWrite(Ignition,LOW);           
    //**************************************************
    Cntdown=0;
    }
  while (millis()% 100);        //Wait until the next 1/10 of second.
  delay(50);
  DownCntr=0;
}

// Wait Launch Button
//**************************************************
void WaitLaunch(){
  while(digitalRead(LaunchButt));   // Launch Button pushed
  Cntdown=1;
  delay(20);
  while(!digitalRead(LaunchButt));  //Debounce Launch Button.
}

// Wait Arm Button
//**************************************************
void WaitARM(){
  while(digitalRead(ArmButt)==1)  // Arm Button pushed
  DownCntr=100;
  Cntdown=0;
  tone(Buzzer, 2000, 100);
  delay(100);
  tone(Buzzer, 2000, 100);
  delay(100);
  tone(Buzzer, 2000, 100);
  delay(20);
  while(!digitalRead(ArmButt));  //Debounce ARM Button.
  
  
}//End Loop
