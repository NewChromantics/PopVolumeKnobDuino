//#include <Keyboard.h>
#include "DigiKeyboard.h"

#define Keyboard DigiKeyboard

#define LED_PIN 1

int encoder0PinA = 2;
int encoder0PinB = 4;
int encoder0PinALast = LOW;

#define VK_OEM_PLUS     0xBB
#define VK_OEM_MINUS     0xBD
//  gr: not VK codes!
//  https://digistump.com/board/index.php?topic=166.0
//#define VK_VOLUME_UP    0xAF  
//#define VK_VOLUME_DOWN  0xAE
//  https://github.com/Bluebie/volume_knob/blob/master/volume_knob.ino
//  this works!
#define VK_VOLUME_UP    128  
#define VK_VOLUME_DOWN  129
//#define VK_VOLUME_UP    0xEA  
//#define VK_VOLUME_DOWN  0xE9
//  https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db20
//#define VK_VOLUME_UP    0xED  //  media
//#define VK_VOLUME_DOWN  0xEE
//#define VK_VOLUME_UP    KEY_A
//#define VK_VOLUME_DOWN  KEY_B

#define VOLUME_MULT       1
#define INTRO_BLINK_COUNT 5
#define ENABLE_BLINK      true

void Blink()
{
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
}

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  digitalWrite(encoder0PinA, HIGH);
  digitalWrite(encoder0PinB, HIGH);

  //Keyboard.begin();
  Keyboard.delay(100);

  for ( auto i=0; i<INTRO_BLINK_COUNT;  i++ )
  {
    Keyboard.update();
    Blink();
    delay(200);
  }
  
}


void OnIncrement()
{
  if ( ENABLE_BLINK )
    Blink();
  for ( auto i=0; i<VOLUME_MULT;  i++ )
  {
    Keyboard.sendKeyStroke(VK_VOLUME_UP);
    Keyboard.update();
  }
}

void OnDecrement()
{
  if ( ENABLE_BLINK )
    Blink();
  for ( auto i=0; i<VOLUME_MULT;  i++ )
  {
    Keyboard.sendKeyStroke(VK_VOLUME_DOWN);
    Keyboard.update();
  }
}


void loop() 
{
  Keyboard.update();
  auto Latch = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (Latch == HIGH)) 
  {
    if (digitalRead(encoder0PinB) == LOW) 
    {
     OnIncrement();
    } else {
      OnDecrement();
    }
  }
  encoder0PinALast = Latch; 
}
