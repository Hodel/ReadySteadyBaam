
/*
Ready Steady Baam
Wer drückt schneller, wenn die grüne LED leuchtet?

Speaker GND und 12
greenLed 7
yellowLed 6
redLed 5
Taster1 (player1) 2
Taster2 (player2) 3
*/

#include <Tone.h>


int greenLed = 5;
int yellowLed = 6;
int redLed = 7;
int player1 = 2;
int player2 = 3;

long bamTime;
long p1Time;
long p2Time;

Tone speaker;


void setup() {
  
 Serial.begin(9600); 
 Serial.println("setup");
 
 
 speaker.begin( 12 );
  
 pinMode( greenLed, OUTPUT );
 pinMode( yellowLed, OUTPUT );
 pinMode( redLed, OUTPUT );
 
 setupPlayers();
 
    //Startmelodie
 
 digitalWrite (greenLed, HIGH);
 delay (500);
 digitalWrite (greenLed, HIGH);
 digitalWrite (yellowLed, HIGH);
 delay (500);
 digitalWrite (yellowLed, HIGH);
 digitalWrite (redLed, HIGH);
 delay (500);
 digitalWrite (redLed, HIGH);
 speaker.play( NOTE_G5, 100 );  
 delay (250); 
 speaker.play( NOTE_C6, 100 );  
 delay (250);
 speaker.play( NOTE_E6, 100 );  
 delay (300); 
 speaker.play( NOTE_DS6, 100 );  
 delay (150); 
 speaker.play( NOTE_DS6, 100 );  
 delay (220); 
 speaker.play( NOTE_DS6, 100 );  
 delay (250);
 speaker.play( NOTE_G5, 100 );  
 delay (100); 
 speaker.play( NOTE_GS5, 100 );  
 delay (450);
 speaker.play( NOTE_GS6, 100 );  
 delay (1000);
 
}


void setupPlayers() {
  
  pinMode( player1, INPUT );
  digitalWrite( player1, HIGH );
  attachInterrupt( 0, onPlayer1, FALLING );
  
  pinMode( player2, INPUT );
  digitalWrite( player2, HIGH );
  attachInterrupt( 1, onPlayer2, FALLING ); 
}


void loop() {
  runGame();
}

void runGame() {
  
  int bam = random( 500, 3000 );
  int d = 1000;
  p1Time = 0;
  p2Time = 0;
  bamTime = 0;
  
  // turn off all leds
  digitalWrite( greenLed, LOW );
  digitalWrite( yellowLed, LOW );
  digitalWrite( redLed, LOW );
  
  delay( d );
  speaker.play( NOTE_A3, 300 );
  digitalWrite( redLed, HIGH );
  
  delay( d );
  speaker.play( NOTE_A3, 300 );
  digitalWrite( yellowLed, HIGH );
  
  delay( bam );
  speaker.play( NOTE_A4, 600 );
  digitalWrite( greenLed, HIGH );
  bamTime = millis();
  
  delay( d );
  
  long delta1 = p1Time - bamTime;
  long delta2 = p2Time - bamTime;
  
  digitalWrite( greenLed, LOW );
  digitalWrite( yellowLed, LOW );
  digitalWrite( redLed, LOW );
  
  boolean loose = true;
  
  if( delta1 > 0 && ( delta1 < delta2 || delta2 < 0 ) ) {
    digitalWrite( yellowLed, HIGH );
    speaker.play( NOTE_G5, 100 );
    loose = false;
  }
  
  if( delta2 > 0 && ( delta2 < delta1 || delta1 < 0 )  ) {
    digitalWrite( redLed, HIGH );
    speaker.play( NOTE_C5, 100 );
    loose = false;
  }
  
  if( loose ) {
    speaker.play( NOTE_A2, 600 );
  }
  
  delay( d );
}



void onPlayer1() {
  if( p1Time == 0 ) p1Time = millis();
}

void onPlayer2() {
  if( p2Time == 0 ) p2Time = millis();
}
