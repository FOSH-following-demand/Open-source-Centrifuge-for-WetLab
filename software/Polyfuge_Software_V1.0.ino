/*
 *  Polyfuge_Software_V1.0.ino - Polyfuge control software.
 *  Copyright (C) 2018 Jason Wu. All Rights Reserved.
 *
 *  Polyfuge control software is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Polyfuge control software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  the Polyfuge control software.  If not, see <http://www.gnu.org/licenses/>.
 */
 
/*
 * Pins on Board
 * LCD: 7,8,9,10,11,12
 * ESC: 13
 * Optical: A0
 * Rotary Encoder: 4,5
 * Button: 6
*/

//add libraries
#include <PinChangeInt.h>
#include <Servo.h>
#include <LiquidCrystal.h>

//define pins
int opticalPin = A0;
#define encoderPinA 5
#define encoderPinB 4
int buttonPin = 6;
int escPin = 13;

//constants
LiquidCrystal lcd(7,8,9,10,11,12);
Servo esc;

//input variables
int encoderVal = 0;
int buttonState;
int previousButtonState = HIGH;
int opticalState;

//modes
boolean modeSelect = true;
boolean rpmSelect = false;
boolean minuteSelect = false;
boolean secondSelect = false;
boolean confirmSelect = false;
boolean runModeSetup = false;
boolean runMode = false;

//calculation variables
int option;
int rpm;
long minutes;
long seconds;
long runTime;
unsigned long startTime;
unsigned long endTime;

//display variables
int displayMinutes;
int displaySeconds;

//confirm variables
boolean confirmStatus = false;

//previous calculation variables
int previousOption = -1;
long previousrpm = 1;
long previousMinutes = 1;
long previousSeconds = 1;
boolean previousConfirmStatus = true;
int previousDisplayMinutes = -1;
int previousDisplaySeconds = -1;

//motor variables
int escValNeutral = 1000;


void setup() {

  //pinModes
  pinMode(opticalPin,INPUT);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(encoderPinA,INPUT_PULLUP);
  pinMode(encoderPinB,INPUT_PULLUP);
  pinMode(escPin,OUTPUT);

  //attach interrupts
  attachPinChangeInterrupt(encoderPinA, readEncoder, CHANGE);

  //arm motor
  esc.attach(escPin);
  esc.writeMicroseconds(escValNeutral);

  //start lcd
  lcd.begin(16,2);
  lcd.clear();

  //welcome text
  lcd.setCursor(0,0);
  lcd.print("Welcome to");
  lcd.setCursor(0,1);
  lcd.print("Polyfuge");
  delay(3000);

  //loading countdown
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading in");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("3 second(s)");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("2");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("1");
  delay(1000);

  //set up modeSelect screen
  if(modeSelect == true){
    lcd.setCursor(0,0);
    lcd.print("                ");  
    lcd.setCursor(0,0);         
    lcd.print("  Timed Run");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("  Quick Spin");
    }
}

void loop() {

  //modeSelect and read encoder + mark selection
  if(modeSelect == true){

    if(encoderVal > 1){
      encoderVal = 1;
      }
      if(encoderVal < 0){
        encoderVal = 0;
        }

    //show selected option on LCD
    option = encoderVal;
    if(option != previousOption){
      if(option == 0){
        lcd.setCursor(0,0);
        lcd.print(">");
        lcd.setCursor(0,1);
        lcd.print(" ");
        }
        else{
          lcd.setCursor(0,1);
          lcd.print(">");
          lcd.setCursor(0,0);
          lcd.print(" ");
          }
      }
      previousOption = option;       
    }

  //buttonPressed Mode switch to rpmSelect or quickSpin
  if(modeSelect == true){
    buttonState = digitalRead(buttonPin);

    //user selects timed run
    if(buttonState == LOW && previousButtonState == HIGH && option == 0){

      //set up rpmSelect screen
      previousOption = -1;
      encoderVal = 0;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Microseconds");

      //turn off modeSelect and turn on rpmSelect
      modeSelect = false;
      rpmSelect = true;
      }

    //user selects quick spin
    if(buttonState == LOW && previousButtonState == HIGH && option == 1){

      //set up screen for quickSpin
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Quick spin in");
      lcd.setCursor(0,1);
      lcd.print("progress.");

      //turn on motor
      esc.writeMicroseconds(1300);
      delay(800);

      //turn off motor
      esc.writeMicroseconds(escValNeutral);

      //set up screen for modeSelect
      lcd.setCursor(0,0);
      lcd.print("                ");  
      lcd.setCursor(0,0);         
      lcd.print("  Timed Run");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("  Quick Spin");

      //reset variables
      previousOption = -1;
      encoderVal = 0;
      }
      previousButtonState = buttonState; 
      delay(50);    
    }

  //read rotary encoder and display rpm + read button
  if(rpmSelect == true){
    //check encoderVal for max + min out
    if(encoderVal > 90){
      encoderVal = 90;
      }
      if(encoderVal < 0){
        encoderVal = 0;
        }
        
    //rewrite screen if rpm changed
    rpm = encoderVal + 1235;
    if(rpm != previousrpm){
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,0);
      lcd.print(rpm);
      }
      previousrpm = rpm;
  }

  //button pressed mode switch from rpm to minuteSelect
  if(rpmSelect == true){
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW && previousButtonState == HIGH){
      //motor to neutral
      esc.writeMicroseconds(0);
      rpmSelect = false;
      minuteSelect = true;
      encoderVal = 0;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Minute(s)");
      }
      previousButtonState = buttonState;
      delay(50);
    }

    //read rotary encoder and display minutes + read button
    if(minuteSelect == true){
      //check encoderVal for max + min out
      if(encoderVal > 15){
        encoderVal = 15;
        }
        if(encoderVal < 0){
          encoderVal = 0;
          }
          
      //rewrite screen if minute changed
      minutes = encoderVal;
      if(minutes != previousMinutes){
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print(minutes);
        }
      previousMinutes = minutes;
      }

  //button pressed mode switch from minuteSelect to secondSelect
  if(minuteSelect == true){
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW && previousButtonState == HIGH){
      minuteSelect = false;
      secondSelect = true;
      encoderVal = 0;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Second(s)");
      }
      previousButtonState = buttonState;
      delay(50);
    }

    //read rotary encoder and display seconds + read button
    if(secondSelect == true){
      //check encoderVal for max + min out
      if(encoderVal > 59){
        encoderVal = 59;
        }
        if(encoderVal < 0){
          encoderVal = 0;
          }
          
      //rewrite screen if seconds changed
      seconds = encoderVal;
      if(seconds != previousSeconds){
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print(seconds);
        }
      previousSeconds = seconds;
      }

  //button pressed mode switch from secondSelect to confirmSelect
  if(secondSelect == true){
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW && previousButtonState == HIGH){
      secondSelect = false;
      confirmSelect = true;
      encoderVal = 0;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Ready to Spin?");
      }
      previousButtonState = buttonState;
      delay(50);
    }
    
    //read rotary encoder and display confirm + read button
    if(confirmSelect == true){
      //check encoderVal for max + min out
      if(encoderVal > 1){
        encoderVal = 0;
        }
        if(encoderVal < 0){
          encoderVal = 1;
          }
          
      //map confirmStatus
      if(encoderVal == 1){
        confirmStatus = true;
        }
        else{
          confirmStatus = false;
          }
          
      //rewrite screen if seconds changed
      if(confirmStatus != previousConfirmStatus){
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        if(confirmStatus == true){
          lcd.print("Yes");
          }
          else{
            lcd.print("No");
            }
        }
      previousConfirmStatus = confirmStatus;
      }

  //button pressed mode switch from confirmSelect to runModeSetup
  if(confirmSelect == true){
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW && previousButtonState == HIGH && confirmStatus == true){
      confirmSelect = false;
      runModeSetup = true;
      encoderVal = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Preparing for");
      lcd.setCursor(0,1);
      lcd.print("run...");
      }
      
      //reset to modeSelect
      else if(buttonState == LOW && previousButtonState == HIGH && confirmStatus == false){
        //reset variables
        encoderVal = 0;
        rpm = 0;
        minutes = 0;
        seconds = 0;
        confirmStatus = false;
        previousrpm = 1;
        previousMinutes = 1;
        previousSeconds = 1;
        previousConfirmStatus = true;
        
        //mode switch
        confirmSelect = false;
        modeSelect = true;
        
        //set modeSelect screen
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("                ");  
        lcd.setCursor(0,0);         
        lcd.print("  Timed Run");
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("  Quick Spin");
        }
      previousButtonState = buttonState;
      delay(50);
    }

  //reset variables + setup for run
  if(runModeSetup == true){
    
    //calculate run time (in milliseconds)
    runTime = (((minutes*60)+seconds)*1000); 
    
    //reset variables
    encoderVal = 0;
    minutes = 0;
    seconds = 0;
    confirmStatus = false;
    previousrpm = 1;
    previousMinutes = 1;
    previousSeconds = 1;
    previousConfirmStatus = true;
    
    //give countdown for run
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Run Starting in:");
    lcd.setCursor(0,1);
    lcd.print("3 Second(s)");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("2");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("1");
    delay(1000);
    
    //switch to runMode
    runModeSetup = false;
    runMode = true;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    Minute(s)");
    lcd.setCursor(0,1);
    lcd.print("    Second(s)");
  }

  //runMode
  if(runMode == true){
    
    //set time reference with millis
    startTime = millis();
    endTime = startTime;
    
    //turn motor on
    esc.writeMicroseconds(rpm);
    
    //run motor until time is up
    while(((endTime-startTime) <= runTime) && runMode == true){
      
      //calculate display minutes + display seconds
      displayMinutes = (((runTime-(endTime-startTime))/1000)/60);
      displaySeconds = (((runTime-(endTime-startTime))/1000)%60);
      
      //display minutes + seconds
      if(displayMinutes != previousDisplayMinutes){
        lcd.setCursor(0,0);
        lcd.print("    ");
        lcd.setCursor(0,0);
        lcd.print(displayMinutes);
        }
      if(displaySeconds != previousDisplaySeconds){
        lcd.setCursor(0,1);
        lcd.print("    ");
        lcd.setCursor(0,1);
        lcd.print(displaySeconds);
        }
        
      //check for opticalPin state, if optical state is low (lid is open so terminate run)
      opticalState = digitalRead(opticalPin);
      if(opticalState == HIGH){
        
        //turn off run mode
        runMode = false;
        
        //turn motor off
        esc.writeMicroseconds(escValNeutral);
        
        //give error text
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Lid Opened");
        lcd.setCursor(0,1);
        lcd.print("Run Terminated");
        delay(5000);
        
        //set up mode select screen + mode
        modeSelect = true;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("                ");  
        lcd.setCursor(0,0);         
        lcd.print("  Timed Run");
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("  Quick Spin");
        }  
        
      //check for buttonPin state, if buttonPin state is high, then user cancelled run
      buttonState = digitalRead(buttonPin);
      if(buttonState == LOW){
        
        //turn off run mode
        runMode = false;
        
        //turn motor off
        esc.writeMicroseconds(escValNeutral);
        
        //give error text
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Button Pressed");
        lcd.setCursor(0,1);
        lcd.print("Run Terminated");
        delay(5000);
        
        //set up modeSelect screen + mode
        modeSelect = true;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("                ");  
        lcd.setCursor(0,0);         
        lcd.print("  Timed Run");
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("  Quick Spin");
        }
      
      //reset endTime + display time values
      previousDisplayMinutes = displayMinutes;
      previousDisplaySeconds = displaySeconds;
      endTime = millis();
      }
      if(runMode == true){
        
      //turn off run mode
      runMode = false;
      
      //turn off motor
      esc.writeMicroseconds(escValNeutral);
      
      //write completed screen
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Run Status:");
      lcd.setCursor(0,1);
      lcd.print("Completed");
      delay(3000);
      
      //reset values
      previousDisplayMinutes = -1;
      previousDisplaySeconds = -1;
      
      //set up modeSelect screen
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("                ");  
      lcd.setCursor(0,0);         
      lcd.print("  Timed Run");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("  Quick Spin");
      
      //switch to rpm select
      modeSelect = true;      
      }
    }
}

//Read Encoder Interrupt
void readEncoder(){
  if(digitalRead(encoderPinA) == HIGH){
    if(digitalRead(encoderPinB) == HIGH){
      encoderVal--;
      }
      else{
        encoderVal++;
      }
    }
  }     
  

