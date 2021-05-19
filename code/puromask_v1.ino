#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

int bP1 = 2; //where is a button connected
int f = 0; //which face to display atm - 0 = idle
int s = 0; //just a useless variable for a switch blow

void setup() {
  
  Serial.begin(9600);
  Serial.println("Puro will be happy with you UwU"); 
  matrix.begin(0x70);
  pinMode(bP1, INPUT_PULLUP);
  
}

static const uint8_t PROGMEM
  base1_bmp[] =     //creating expressions as bitmaps
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011100,
    B00111110,
    B00111110,
    B00001100
  },

  base2_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00111000,
    B01111100,
    B01111100,
    B00110000
  },

  big1_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011100,
    B00111110,
    B01111110
  },

  big2_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00111000,
    B01111100,
    B01111110
  };

void loop() {
  
  switch(digitalRead(bP1)) { //checking if a button is pressed    
    case HIGH:
      s = 0;
      break;
    
    case LOW:
      if(s == 0) {
        f = f + 1;
        s = 0;
      }
      break;
  }

  delay(500);

  if(f == 3) { //setting up a limit to displayed faces    
    f = 0;    
  }

  switch(f) {    //checking which face should be displayed
    case 0:
      matrix.clear(); //idle atate - nothing is displayed, matrix is cleared
      matrix.writeDisplay();
      break;

    case 1:
      matrix.clear(); //clear matrix
      matrix.drawBitmap(0, 0, base1_bmp, 8, 8, LED_ON); //drawing first eye
      matrix.drawBitmap(0, 8, base2_bmp, 8, 8, LED_ON); //drawing second eye
      matrix.writeDisplay(); //saving them to matrix
      break;
    
    case 2:
      matrix.clear();
      matrix.drawBitmap(0, 0, big1_bmp, 8, 8, LED_ON);
      matrix.drawBitmap(0, 8, big2_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      break;
  }
  matrix.setRotation(0);
}
