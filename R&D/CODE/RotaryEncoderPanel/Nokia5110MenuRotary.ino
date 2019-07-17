   //////////////////////////////////////////////
  //       Arduino Rotary Encoder Menu        //
 //                 v1.0                     //
//           http://www.educ8s.tv           //
/////////////////////////////////////////////

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ClickEncoder.h>
#include <TimerOne.h>

int menuitem = 1;
int frame = 1;
int page = 1;
int lastMenuItem = 1;

String menuItem1 = "Contrast";
String menuItem2 = "Volume";
String menuItem3 = "Language";
String menuItem4 = "Difficulty";
String menuItem5 = "Light: ON";
String menuItem6 = "Reset";

boolean backlight = true;
int contrast=60;
int volume = 50;

String language[3] = { "EN", "ES", "EL" };
int selectedLanguage = 0;

String difficulty[2] = { "EASY", "HARD" };
int selectedDifficulty = 0;

boolean up = false;
boolean down = false;
boolean middle = false;

ClickEncoder *encoder;
int16_t last, value;

Adafruit_PCD8544 display = Adafruit_PCD8544( 5, 4, 3); //Download the latest Adafruit Library in order to use this constructor

void setup() {

  pinMode(7,OUTPUT);
  turnBacklightOn();
  
  encoder = new ClickEncoder(A1, A0, A2);
  encoder->setAccelerationEnabled(false);
   
  display.begin();      
  display.clearDisplay(); 
  setContrast();  

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  
  last = encoder->getValue();
}

void loop() {

  drawMenu();

  readRotaryEncoder();

   ClickEncoder::Button b = encoder->getButton();
   if (b != ClickEncoder::Open) {
   switch (b) {
      case ClickEncoder::Clicked:
         middle=true;
        break;
    }
  }    
  
  if (up && page == 1 ) {
     
    up = false;
    if(menuitem==2 && frame ==2)
    {
      frame--;
    }

     if(menuitem==4 && frame ==4)
    {
      frame--;
    }
      if(menuitem==3 && frame ==3)
    {
      frame--;
    }
    lastMenuItem = menuitem;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=1;
    } 
  }else if (up && page == 2 && menuitem==1 ) {
    up = false;
    contrast--;
    setContrast();
  }
  else if (up && page == 2 && menuitem==2 ) {
    up = false;
    volume--;
  }
  else if (up && page == 2 && menuitem==3 ) {
    up = false;
    selectedLanguage--;
    if(selectedLanguage == -1)
    {
      selectedLanguage = 2;
    }
  }
    else if (up && page == 2 && menuitem==4 ) {
    up = false;
    selectedDifficulty--;
    if(selectedDifficulty == -1)
    {
      selectedDifficulty = 1;
    }
  }

  if (down && page == 1) //We have turned the Rotary Encoder Clockwise
  {

    down = false;
    if(menuitem==3 && lastMenuItem == 2)
    {
      frame ++;
    }else  if(menuitem==4 && lastMenuItem == 3)
    {
      frame ++;
    }
     else  if(menuitem==5 && lastMenuItem == 4 && frame!=4)
    {
      frame ++;
    }
    lastMenuItem = menuitem;
    menuitem++;  
    if (menuitem==7) 
    {
      menuitem--;
    }
  
  }else if (down && page == 2 && menuitem==1) {
    down = false;
    contrast++;
    setContrast();
  }
  else if (down && page == 2 && menuitem==2) {
    down = false;
    volume++;
  }
   else if (down && page == 2 && menuitem==3 ) {
    down = false;
    selectedLanguage++;
    if(selectedLanguage == 3)
    {
      selectedLanguage = 0;
    }
  }
  else if (down && page == 2 && menuitem==4 ) {
    down = false;
    selectedDifficulty++;
    if(selectedDifficulty == 2)
    {
      selectedDifficulty = 0;
    }
  }
  
  if (middle) //Middle Button is Pressed
  {
    middle = false;
   
    if (page == 1 && menuitem==5) // Backlight Control 
    {
      if (backlight) 
      {
        backlight = false;
        menuItem5 = "Light: OFF";
        turnBacklightOff();
        }
      else 
      {
        backlight = true; 
        menuItem5 = "Light: ON";
        turnBacklightOn();
       }
    }

    if(page == 1 && menuitem ==6)// Reset
    {
      resetDefaults();
    }


    else if (page == 1 && menuitem<=4) {
      page=2;
     }
      else if (page == 2) 
     {
      page=1; 
     }
   }   
  }
  
  void drawMenu()
  {
    
  if (page==1) 
  {    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU");
    display.drawFastHLine(0,10,83,BLACK);

    if(menuitem==1 && frame ==1)
    {   
      displayMenuItem(menuItem1, 15,true);
      displayMenuItem(menuItem2, 25,false);
      displayMenuItem(menuItem3, 35,false);
    }
    else if(menuitem == 2 && frame == 1)
    {
      displayMenuItem(menuItem1, 15,false);
      displayMenuItem(menuItem2, 25,true);
      displayMenuItem(menuItem3, 35,false);
    }
    else if(menuitem == 3 && frame == 1)
    {
      displayMenuItem(menuItem1, 15,false);
      displayMenuItem(menuItem2, 25,false);
      displayMenuItem(menuItem3, 35,true);
    }
     else if(menuitem == 4 && frame == 2)
    {
      displayMenuItem(menuItem2, 15,false);
      displayMenuItem(menuItem3, 25,false);
      displayMenuItem(menuItem4, 35,true);
    }

      else if(menuitem == 3 && frame == 2)
    {
      displayMenuItem(menuItem2, 15,false);
      displayMenuItem(menuItem3, 25,true);
      displayMenuItem(menuItem4, 35,false);
    }
    else if(menuitem == 2 && frame == 2)
    {
      displayMenuItem(menuItem2, 15,true);
      displayMenuItem(menuItem3, 25,false);
      displayMenuItem(menuItem4, 35,false);
    }
    
    else if(menuitem == 5 && frame == 3)
    {
      displayMenuItem(menuItem3, 15,false);
      displayMenuItem(menuItem4, 25,false);
      displayMenuItem(menuItem5, 35,true);
    }

    else if(menuitem == 6 && frame == 4)
    {
      displayMenuItem(menuItem4, 15,false);
      displayMenuItem(menuItem5, 25,false);
      displayMenuItem(menuItem6, 35,true);
    }
    
      else if(menuitem == 5 && frame == 4)
    {
      displayMenuItem(menuItem4, 15,false);
      displayMenuItem(menuItem5, 25,true);
      displayMenuItem(menuItem6, 35,false);
    }
      else if(menuitem == 4 && frame == 4)
    {
      displayMenuItem(menuItem4, 15,true);
      displayMenuItem(menuItem5, 25,false);
      displayMenuItem(menuItem6, 35,false);
    }
    else if(menuitem == 3 && frame == 3)
    {
      displayMenuItem(menuItem3, 15,true);
      displayMenuItem(menuItem4, 25,false);
      displayMenuItem(menuItem5, 35,false);
    }
        else if(menuitem == 2 && frame == 2)
    {
      displayMenuItem(menuItem2, 15,true);
      displayMenuItem(menuItem3, 25,false);
      displayMenuItem(menuItem4, 35,false);
    }
    else if(menuitem == 4 && frame == 3)
    {
      displayMenuItem(menuItem3, 15,false);
      displayMenuItem(menuItem4, 25,true);
      displayMenuItem(menuItem5, 35,false);
    }   
    display.display();
  }
  else if (page==2 && menuitem == 1) 
  {    
   displayIntMenuPage(menuItem1, contrast);
  }

  else if (page==2 && menuitem == 2) 
  {
   displayIntMenuPage(menuItem2, volume);
  }
   else if (page==2 && menuitem == 3) 
  {
   displayStringMenuPage(menuItem3, language[selectedLanguage]);
  }
  else if (page==2 && menuitem == 4) 
  {
   displayStringMenuPage(menuItem4, difficulty[selectedDifficulty]);
  }
  else if (page==2 && menuitem == 4) 
  {
   displayStringMenuPage(menuItem4, difficulty[selectedDifficulty]);
  }
  
  }

  void resetDefaults()
  {
    contrast = 60;
    volume = 50;
    selectedLanguage = 0;
    selectedDifficulty = 0;
    setContrast();
    backlight = true;
    menuItem5 = "Light: ON";
    turnBacklightOn();
  }

  void setContrast()
  {
    display.setContrast(contrast);
    display.display();
  }

  void turnBacklightOn()
  {
    digitalWrite(7,LOW);
  }

    void turnBacklightOff()
  {
    digitalWrite(7,HIGH);
  }

  void timerIsr() {
  encoder->service();
}

void displayIntMenuPage(String menuItem, int value)
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print(menuItem);
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.print("Value");
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(value);
    display.setTextSize(2);
    display.display();
}

void displayStringMenuPage(String menuItem, String value)
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print(menuItem);
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.print("Value");
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(value);
    display.setTextSize(2);
    display.display();
}

void displayMenuItem(String item, int position, boolean selected)
{
    if(selected)
    {
      display.setTextColor(WHITE, BLACK);
    }else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0, position);
    display.print(">"+item);
}

void readRotaryEncoder()
{
  value += encoder->getValue();
  
  if (value/2 > last) {
    last = value/2;
    down = true;
    delay(150);
  }else   if (value/2 < last) {
    last = value/2;
    up = true;
    delay(150);
  }
}



