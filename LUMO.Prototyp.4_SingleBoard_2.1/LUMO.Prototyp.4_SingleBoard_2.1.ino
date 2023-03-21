/* Saker att fixa :)

- lägga till leds när man byter läge
- Loppa lägen när man har nått max 

- Inge lagg på knappar - grej ist för Delay

- Gränssnitt

1. Fina lägen
  1.         Random utefter tid
  2. rainbow  
  3. Rainbow with glitter
  4. SpinningCykle
  5. confetti
  6. bpm80
  7. ColourCykle
  8. BigCykle
  9. FastCykle
  
2. Worms
  1. Random utefter tid
  2.
  3.
  4.
  5.
  6.
  7.
  8.
3. Party
  1. Random utefter tid
  2. Blink
  3. One side at a time
  4. Random sektions
  5. Pulse
  6.
  7.
  8.
4. Nyans
  Ena siden- andra sidan
5. Ljusstyrka
6. Speed
*/

#include "FastLED.h"
//#include <EEPROM.h>
#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif
#define DATA_PIN    9
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define SWITCHMODE  LOW
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          Brightcness
#define FRAMES_PER_SECOND  120

const int SkipBut1 = 5;
const int RighBut2 = 6;
const int LeftBut3 = 7;      
const int SaveBut4 = 8;

int StateSkipBut1 = 0;
int StateRighBut2 = 0;
int StateLeftBut3 = 0;
int StateSaveBut4 = 0;

uint8_t gHue = 0;             //Changing
uint8_t randomHue = 0;             //Changing
int randomDelay;

uint8_t gCurrentPatternNumber = 0;
uint8_t PartyPatternsListNumber = 0;
uint8_t CurrentWormPatternsList = 0;

//Saved
int Speed = 30;
int Mode = 1;
int Fina = 1;
int Worm = 1;
int Party = 1;
int Nyans1 = 100;
int Nyans2 = 100;
int Brightness = 135;


float rad;
float sinus;


CRGBPalette16 targetPalette;
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

CRGB clr1;
CRGB clr2;
uint8_t speed;
uint8_t loc1;
uint8_t loc2;
uint8_t ran1;
uint8_t ran2;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Setup Begin"); 
  Serial.println("Safety Delay 3000ms begin"); 
  delay(3000); // 3 second delay for recovery 3000ms;
  Serial.println("Safety Delay done");

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // set master brightness control
  FastLED.setBrightness(Brightness);
  pinMode(SkipBut1, INPUT_PULLUP);
  pinMode(RighBut2, INPUT_PULLUP);
  pinMode(LeftBut3, INPUT_PULLUP);
  pinMode(SaveBut4, INPUT_PULLUP);  
  LEDS.addLeds<LED_TYPE, 12, COLOR_ORDER>(leds, NUM_LEDS);
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    
  Serial.println("Setup effect"); 
  /*
    for(int i = 0; i < NUM_LEDS; i = i+3) {
    leds[i+9] = CRGB(100, 100, 100);
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
     }*/
    Serial.println(Mode); 
}
/*
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = 
{rainbow, rainbowWithGlitter, bpm80, confetti, dot_beat, Beatwave, sinelon, juggle, Colourcykle, Bigcykle};


typedef void (*WormPatternsList[])();
WormPatternsList WormPatterns = 
{Worm1,Worm2, Worm3, Worm4, Whitestripesblended, Clouds, Partyworm,ItalyBlend,Worm15,Worm16,Christmas,Worm17}; //15st
//uint8_t CurrentWormPatternsList = 0;

typedef void (*PartyPatternsList[])();
PartyPatternsList PartyPatterns = 
{BlinkMadness, madnessBlink, bpmValue, OriginalReve};
//uint8_t PartyPatternsListNumber = 0;
*/
void loop() {
  FastLED.setBrightness(Brightness);
  FastLED.show();  
  StateSkipBut1 = digitalRead(SkipBut1);
  StateRighBut2 = digitalRead(RighBut2);
  StateLeftBut3 = digitalRead(LeftBut3);
  StateSaveBut4 = digitalRead(SaveBut4);
  
  
  EVERY_N_MILLIS_I(thistimer, Speed) { gHue = gHue + 5; if (gHue > 255){gHue = 0;}} // snabb 10 > Speed < 50 Långsam 
     thistimer.setPeriod(Speed);
  
  //EVERY_N_MILLISECONDS( 10 ) { gHue = gHue + 5;  }

    
  if (StateSkipBut1 == SWITCHMODE) { Serial.println("Next mode pressed"); Mode++; if(Mode == 7){Mode = 1;} FadeBlackMode(); Serial.println(Mode); delay(250);  }
  
  if (StateLeftBut3 == SWITCHMODE && Mode == 1 && Fina > 1)    { Serial.println("LeftBut3 Fina-");  FadeBlack();  Fina--;  Serial.println(Fina); delay(100);}
  if (StateRighBut2 == SWITCHMODE && Mode == 1 && Fina < 15)   { Serial.println("RighBut2 Fina+");  FadeBlack();  Fina++;  Serial.println(Fina); delay(100);}
  
  if (StateLeftBut3 == SWITCHMODE && Mode == 2 && Worm > 1)    { Serial.println("LeftBut3 Worm-");  FadeBlack();  Worm--;  Serial.println(Worm); delay(100);}
  if (StateRighBut2 == SWITCHMODE && Mode == 2 && Worm < 14)   { Serial.println("RighBut2 Worm+");  FadeBlack();  Worm++;  Serial.println(Worm); delay(100);}
    
  if (StateLeftBut3 == SWITCHMODE && Mode == 3 && Party > 0) { Serial.println("LeftBut3 Party-"); FadeBlack();  Party--; Serial.println(Party); delay(100);}
  if (StateRighBut2 == SWITCHMODE && Mode == 3 && Party < 7) { Serial.println("RighBut2 Party+"); FadeBlack();  Party++; Serial.println(Party); delay(100);}

  if (StateLeftBut3 == SWITCHMODE && Mode == 4) { Serial.println("Nyans 1+: ");  Nyans1 = Nyans1 + 5; if (Nyans1 > 255){ Nyans1 = 0;} Serial.println(Nyans1);}
  if (StateRighBut2 == SWITCHMODE && Mode == 4) { Serial.println("Nyans 2+: ");  Nyans2 = Nyans2 + 5; if (Nyans2 > 255){ Nyans2 = 0;} Serial.println(Nyans2);}

  if (StateLeftBut3 == SWITCHMODE && Mode == 5 && Brightness > 0){ Serial.println("Brightness -: "); Brightness = Brightness - 5; Serial.println(Brightness);}
  if (StateRighBut2 == SWITCHMODE && Mode == 5 && Brightness < 130)  { Serial.println("Brightness +: "); Brightness = Brightness + 5; Serial.println(Brightness);}

  if (StateLeftBut3 == SWITCHMODE && Mode == 6 && Speed < 50) { Serial.println("Långsammare: ");   Speed = Speed - 10; Serial.println(Speed); delay(100);}
  if (StateRighBut2 == SWITCHMODE && Mode == 6 && Speed > 10) { Serial.println("Snabbare: ");      Speed = Speed + 10; Serial.println(Speed); delay(100);}
  
  if (StateSaveBut4 == SWITCHMODE) { Serial.println("SaveBut4 pressed"); FadeBlack(); Mode--; Serial.println(Mode);  delay(500);}
  
  

  switch (Mode) {
    //Fina lägen
  case 1:  { 
                          switch (Fina) {
                                             case 1:  { rainbow();                     break; } //15 sek tid typ
                                             case 2:  { rainbow();                     break; }
                                             case 3:  { rainGlitter();                 break; }
                                             case 4:  { SpinningCykle();               break; }
                                             case 5:  { confetti();                    break; }
                                             case 6:  { bpm80();                       break; }
                                             case 7:  { ColourCykle();                 break; }
                                             case 8:  { BigCykle();                    break; }
                                             case 9:  { FastCykle();                   break; }
                                             default: Fina = 1; Serial.println(Fina);  break; }     break; }
                                             
    //Worms
  case 2:  {
                          switch (Worm) {
                                             case 1:  { Worm1();         WormSetup();  break; } //15 sek tid typ
                                             case 2:  { Worm2();         WormSetup();  break; }
                                             case 3:  { Worm3();         WormSetup();  break; }
                                             case 4:  { Worm4();         WormSetup();  break; }
                                             case 5:  { Whitesblend();   WormSetup();  break; }
                                             case 6:  { Clouds();        WormSetup();  break; }
                                             case 7:  { Partyworm();     WormSetup();  break; }
                                             case 8:  { ItalyBlend();    WormSetup();  break; }
                                             case 9:  { Worm15();        WormSetup();  break; }
                                             case 10: { Worm16();        WormSetup();  break; }
                                             case 11: { Christmas();     WormSetup();  break; }
                                             case 12: { Worm17();        WormSetup();  break; }
                                             case 13: { BlackAndWhite(); WormSetup();  break; }
                                             default: Worm = 1; Serial.println(Worm);  break; }     break; } 
  
    //Party lägen
  case 3:  {  
                            switch (Party) {
                                             case 1:  { PartyCykle();                  break; } //15 sek tid typ
                                             case 2:  { BlinkMadness();                break; } 
                                             case 3:  { RandomBlinking();              break; }
                                             case 4:  { PulseRandom();                 break; }
                                             case 5:  { PulseRandomtest();             break; } 
                                             case 6:  { PulseRandom();                 break; } 
                                             default: Party = 1; Serial.println(Party);break; }     break; }
  
    //Välj nyans
  case 4:  { Selectcolour(); break; }
  
    //Välj ljusstyrka
  case 5:  { White();        break; }
  
    //Välj Speed
  case 6:  { BlackAndWhite(); WormSetup();  break; }


  default:
    // if nothing else matches, do the default
    // default is optional
    break;
}


}




#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void FadeBlack()    {for (int i = 0; i < 10; i++){ fadeToBlackBy( leds, NUM_LEDS, 88); FastLED.show();  }}
void FadeBlackMode(){for (int i = 0; i < 10; i++){ fadeToBlackBy( leds, NUM_LEDS, 88); leds[Mode-1] = CRGB::White; FastLED.show();  }}
void White(){fill_gradient(leds,0,CHSV(255,0,170),NUM_LEDS-1,CHSV(255,50,170),SHORTEST_HUES);}
void Black(){fill_gradient(leds,0,CHSV(0,0,0),300,CHSV(0,0,0),SHORTEST_HUES); FastLED.show();}


//Fina Lägen
void rainbow() {fill_rainbow( leds, NUM_LEDS, gHue, 7);}
void rainGlitter() {  rainbow();  addGlitter(80); }
void addGlitter( fract8 chanceOfGlitter) { if( random8() < chanceOfGlitter) {  leds[ random16(NUM_LEDS) ] += CRGB::White; }}
void confetti() {// random colored speckles that blink in and fade smoothly
                    fadeToBlackBy( leds, NUM_LEDS, (60-Speed)/4);
                    int pos = random16(NUM_LEDS);
                    leds[pos] += CHSV( gHue + random8(64), 200, 255);}  
void SpinningCykle()  {
rad = rad + 0.001*(65-Speed);
sinus = 255*sin(rad);
Serial.println(sinus);
fill_gradient(leds, 0, CHSV(sinus, 255,255) , NUM_LEDS-1, CHSV(sinus+80,255,255), SHORTEST_HUES);}

void bpm80()      {  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
                    uint8_t BeatsPerMinute = (70-Speed)*2.4; // 10 > 50 >> 60 > 120 
                    CRGBPalette16 palette = PartyColors_p;
                    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10)); }}

void ColourCykle(){ fill_gradient(leds, 0, CHSV(gHue, 255,255) , NUM_LEDS-1, CHSV(gHue,255,255),    SHORTEST_HUES); }
void BigCykle()  {  fill_gradient(leds, 0, CHSV(gHue, 255,255) , NUM_LEDS-1, CHSV(gHue+80,255,255), SHORTEST_HUES); }
void FastCykle(){   fill_gradient(leds, 0, CHSV(gHue, 255,255) , NUM_LEDS-1, CHSV(gHue+1,255,255),  LONGEST_HUES);  }



// party patterns
void PartyCykle()  {
rad = rad + 0.002*(65-Speed);
sinus = 255*sin(rad);
Serial.println(sinus);
fill_gradient(leds, 0, CHSV(sinus, 255,255) , NUM_LEDS-1, CHSV(sinus+20,255,255), SHORTEST_HUES);}

void BlinkMadness(){
  randomHue = random(0, 255);
  randomDelay = random(0, Speed)*80;
  EVERY_N_MILLIS_I(thattimer, randomDelay) { fill_gradient(leds,0,CHSV(randomHue,255,255),NUM_LEDS-1,CHSV(randomHue+20,255,255),SHORTEST_HUES);}
  thattimer.setPeriod(randomDelay);
  }
void RandomBlinking(){
  randomHue = random(0, 255);
  randomDelay = random(0, Speed)*80;
  EVERY_N_MILLIS_I(thattimer2, randomDelay) { fill_gradient(leds,0,CHSV(randomHue,255,255),NUM_LEDS-1,CHSV(randomHue+20,255,255),SHORTEST_HUES);}
  thattimer2.setPeriod(randomDelay);
  
  randomDelay = random(0, Speed)*80;
  EVERY_N_MILLIS_I(thattimer3, randomDelay) { fill_gradient(leds,0,CHSV(0,0,0),NUM_LEDS-1,CHSV(0,0,0),SHORTEST_HUES);}
  thattimer3.setPeriod(randomDelay);
  }
  
void PulseRandom(){
  randomHue = random(0, 255);
  randomDelay = random(0, Speed)*80;
  EVERY_N_MILLIS_I(thattimer2, randomDelay) { fill_gradient(leds,0,CHSV(randomHue,255,255),NUM_LEDS/2,CHSV(randomHue,255,255),SHORTEST_HUES);}
  thattimer2.setPeriod(randomDelay);
  
  randomDelay = random(0, Speed)*80;
  EVERY_N_MILLIS_I(thattimer3, randomDelay) { fill_gradient(leds,NUM_LEDS/2,CHSV(randomHue,255,255),NUM_LEDS-1,CHSV(randomHue,255,255),SHORTEST_HUES);}
  thattimer3.setPeriod(randomDelay);
  }
void PulseRandomtest(){
  randomHue = random(0, 255);
  randomDelay = random(0, Speed)*80;
  EVERY_N_MILLIS_I(thattimer2, randomDelay) { fill_gradient(leds,0,CHSV(randomHue,255,255),NUM_LEDS/2,CHSV(randomHue,255,255),SHORTEST_HUES);
                                              fill_gradient(leds,NUM_LEDS/2,CHSV(0,0,0),NUM_LEDS-1,CHSV(randomHue,0,0),SHORTEST_HUES);}
  thattimer2.setPeriod(randomDelay);
  
  randomDelay = random(0, Speed)*80;
  EVERY_N_MILLIS_I(thattimer3, randomDelay) { fill_gradient(leds,0,CHSV(0,0,0),NUM_LEDS/2,CHSV(0,0,0),SHORTEST_HUES);
                                              fill_gradient(leds,NUM_LEDS/2,CHSV(randomHue,255,255),NUM_LEDS-1,CHSV(randomHue,255,255),SHORTEST_HUES);}
  thattimer3.setPeriod(randomDelay);
  }
  
/*  

void FadeDown(){
  for (int i = Brightness; i > 0; i = i - 15){ delay(5); FastLED.setBrightness(i); FastLED.show();}
  FastLED.setBrightness(0); FastLED.show();
  delay(100);
}
void FadeUpp(){
  for (int i = 0; i < Brightness; i = i + 15){ delay(5); FastLED.setBrightness(i); FastLED.show();}
  FastLED.setBrightness(Brightness); FastLED.show();
} 
  // snabb 10 > Speed < 50 Långsam 
  
     
  
  fill_gradient(leds,0,CHSV(randomHue,255,255),NUM_LEDS-1,CHSV(randomHue+20,255,255),SHORTEST_HUES);
  FastLED.show(); 
  delay(Speed/2);
  fill_gradient(leds,0,CHSV(0,0,0),300,CHSV(0,0,0),SHORTEST_HUES);
  FastLED.show(); 
  randomDelay = random(Speed/10, Speed);
  delay(Speed/2);}    

void madnessBlink(){
  Nyans = random(0, 255);
  randomDelay = random( 8 ,randomDelay);
  for(int i = 0; i < 5; i++) {
  fill_gradient(leds,0,CHSV(Nyans,255,255),NUM_LEDS-1,CHSV(Nyans+20,255,255),SHORTEST_HUES);
  FastLED.show(); 
  delay(randomDelay);
  Delay = random( 8, Delay);
  fill_gradient(leds,0,CHSV(0,0,0),300,CHSV(0,0,0),SHORTEST_HUES);
  FastLED.show(); 
  delay(randomDelay);}}

void bpmValue()
{  uint8_t BeatsPerMinute = BPMnr;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));}}
*/



// Select Colour
void Selectcolour()
{ fill_gradient(leds,0,CHSV(Nyans1,255,255),NUM_LEDS-1,CHSV(Nyans2,255,255),SHORTEST_HUES);}



void WormSetup(){ static uint8_t startIndex = 0; startIndex = startIndex + ((60-Speed)/10); FillLEDsFromPaletteColors(startIndex); }

void FillLEDsFromPaletteColors( uint8_t colorIndex){  uint8_t brightness = 255; for( int i = 0; i < NUM_LEDS; i++) { leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending); colorIndex += 4; }}
        
void Worm1()  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
void Worm2()  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
void Worm3()  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
void Worm4()  { CRGB purple = CHSV( HUE_PURPLE, 255, 255);  CRGB green  = CHSV( HUE_GREEN, 255, 255);  CRGB black  = CRGB::Black;
                   currentPalette = CRGBPalette16(  green,  green,  black,  black, purple, purple, black, black, green,  green,  black,  black, purple, purple, black,  black );   currentBlending = LINEARBLEND; }
void Origignalrave() { for( int i = 0; i < 16; i++) { currentPalette[i] = CHSV( random8(), 255, random8()); }   currentBlending = LINEARBLEND; }
   
   //void Whitestripes() { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }

void Whitesblend() { BlackAndWhite();       currentBlending = LINEARBLEND; }
void Clouds() { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
void Partyworm() { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
void ItalyBlend() { fill_solid( currentPalette, 16, CRGB::Red);
    fill_solid( currentPalette, 11, CRGB::Gray);
    fill_solid( currentPalette, 6, CRGB::Green);
    fill_solid( currentPalette, 1, CRGB::Black);             currentBlending = LINEARBLEND; }    
void Worm15() { fill_solid( currentPalette, 16, CRGB::Yellow);
    fill_solid( currentPalette, 8, CRGB::Blue);           currentBlending = LINEARBLEND; }
void Worm16() { fill_solid( currentPalette, 16, CRGB::Red);
    fill_solid( currentPalette, 11, CRGB::Gray);
    fill_solid( currentPalette, 6, CRGB::Blue);
    fill_solid( currentPalette, 1, CRGB::Black);           currentBlending = LINEARBLEND; }
void Christmas() { fill_solid( currentPalette, 16, CRGB::Red);
    fill_solid( currentPalette, 12, CRGB::Green);
    fill_solid( currentPalette, 8, CRGB::Red);
    fill_solid( currentPalette, 4, CRGB::Green);           currentBlending = LINEARBLEND; }                 
void Worm17() { currentPalette = LavaColors_p; currentBlending = LINEARBLEND; }

void BlackAndWhite()
{   // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;  }











// Useless for now

/*


void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;}
    }
    
void sinelon()    { // a colored dot sweeping back and forth, with fading trails
                    fadeToBlackBy( leds, NUM_LEDS, 20);
                    int pos = beatsin16(5,0,NUM_LEDS);
                    leds[pos] += CHSV( gHue, 255, 192);}
void Beatwave(){
  currentPalette = RainbowColors_p;
  uint8_t wave1 = beatsin8(9, 0, 255);                        // That's the same as beatsin8(9);
  uint8_t wave2 = beatsin8(8, 0, 255);
  uint8_t wave3 = beatsin8(7, 0, 255);
  uint8_t wave4 = beatsin8(6, 0, 255);

  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, i+wave1+wave2+wave3+wave4, 255, currentBlending); }

EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 10; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }

  FastLED.show();
    
}
  
void dot_beat() {
  
int   thisdelay =   2;                                       // A delay value for the sequence(s)
uint8_t   count =   0;                                        // Count up to 255 and then reverts to 0
uint8_t fadeval = 224;                                        // Trail behind the LED's. Lower => faster fade.

uint8_t bpm = 30;

  uint8_t inner = beatsin8(bpm, 200, 299);    // Move 1/4 to 3/4
  uint8_t outer = beatsin8(bpm, 0, 100);      // Move entire length
  uint8_t middle = beatsin8(bpm, 100, 200);   // Move 1/3 to 2/3

  leds[middle] = CRGB::Purple;
  leds[inner] = CRGB::Blue;
  leds[outer] = CRGB::Aqua;

nscale8(&leds[2], 5, fadeval);
//  nscale8(leds,NUM_LEDS,fadeval);                             // Fade the entire array. Or for just a few LED's, use  nscale8(&leds[2], 5, fadeval);
FastLED.show();
} // dot_beat()
/*

  
void OriginalReve(){
  Worm();
  Origignalrave();}
  */ 
