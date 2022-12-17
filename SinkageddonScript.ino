#include <IRremote.h>

  bool lightsActive = false;
  bool isAlive[4] = {true, true, true, true};
  int playerTurn = 1;


 int quadOnePins[3] = {22, 23, 24};
 bool quadOneColors[3] = {false, false, false};
 int quadTwoPins[3] = {25, 26, 27};
 bool quadTwoColors[3] = {false, false, false};
 int quadThreePins[3] = {28, 29,30};
 bool quadThreeColors[3] = {false, false, false};
 int quadFourPins[3] = {31, 32, 33};
 bool quadFourColors[3] = {false, false, false};

 //RESET PIN
 int resetPin = 52;

 //For colorstate of each,
 //0 = off
 //1 = white
 //2 = red
 //3 = green (tossing)
 int colorStates[4] = {0, 0, 0, 0};

IRrecv irrecv(A0);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup()
{
  pinMode(quadOnePins[0], OUTPUT);
pinMode(quadOnePins[1], OUTPUT);
pinMode(quadOnePins[2], OUTPUT);
pinMode(quadTwoPins[0], OUTPUT);
pinMode(quadTwoPins[1], OUTPUT);
pinMode(quadTwoPins[2], OUTPUT);
pinMode(quadThreePins[0], OUTPUT);
pinMode(quadThreePins[1], OUTPUT);
pinMode(quadThreePins[2], OUTPUT);
pinMode(quadFourPins[0], OUTPUT);
pinMode(quadFourPins[1], OUTPUT);
pinMode(quadFourPins[2], OUTPUT);
 
  digitalWrite(resetPin, HIGH);
  delay(200);
  pinMode(resetPin, OUTPUT);
 
  Serial.begin(9600);
  irrecv.enableIRIn();           // Start the receiver

  lightsActive = true;
  for (int i = 0; i <= 3; i++){isAlive[i] = true;}
  playerTurn = 1;
       
  for (int i = 1; i <= 4; i++){recolorStrip(i, false, true, true);}
  delay(500);
  for (int i = 1; i <= 4; i++){recolorStrip(i, false, false, true);}
  delay(500);
  for (int i = 1; i <= 4; i++){recolorStrip(i, true, false, true);}
  delay(500);
  for (int i = 1; i <= 4; i++){recolorStrip(i, true, false, false);}
  delay(500);
  for (int i = 1; i <= 4; i++){recolorStrip(i, true, true, false);}
  delay(500);
  for (int i = 1; i <= 4; i++){recolorStrip(i, false, true, false);}
  delay(500);
  for (int i = 1; i <= 4; i++){recolorStrip(i, false, false, false);}
  delay(500);
  for (int i = 0; i <= 3; i++) {colorStates[i] = 1;}
  delay(1000);

  recolorStrip(1, true, false, true);
  colorStates[0] = 3;
}
 
void loop() {
  if (irrecv.decode(&results))   // have we received an IR signal?
  {
    Serial.println(results.value);
    translateIR();
   
    delay(500);                 // Do not get immediate repeat
    irrecv.resume();            // receive the next value
  }
 }
 
  void recolorStrip(int playerNum, bool red, bool green, bool blue)
  {
    if (playerNum == 1) {
      if (!red && !green && !blue) {colorStates[0] = 1;}
      else if (!red && green && blue) {colorStates[0] = 2;}
      else if (red && !green && blue) {colorStates[0] = 3;}
      else if (red && green && blue) {colorStates[0] = 0;}
     
      if (red) digitalWrite(quadOnePins[0], HIGH);
      else {digitalWrite(quadOnePins[0], LOW);}
      if (green) digitalWrite(quadOnePins[1], HIGH);
      else {digitalWrite(quadOnePins[1], LOW);}
      if (blue) digitalWrite(quadOnePins[2], HIGH);
      else {digitalWrite(quadOnePins[2], LOW);}
      }
    else if (playerNum == 2) {
      if (!red && !green && !blue) {colorStates[1] = 1;}
      else if (!red && green && blue) {colorStates[1] = 2;}
      else if (red && !green && blue) {colorStates[1] = 3;}
      else if (red && green && blue) {colorStates[1] = 0;}
     
      if (red) digitalWrite(quadTwoPins[0], HIGH);
      else {digitalWrite(quadTwoPins[0], LOW);}
      if (green) digitalWrite(quadTwoPins[1], HIGH);
      else {digitalWrite(quadTwoPins[1], LOW);}
      if (blue) digitalWrite(quadTwoPins[2], HIGH);
      else {digitalWrite(quadTwoPins[2], LOW);}
      }
    else if (playerNum == 3) {
      if (!red && !green && !blue) {colorStates[2] = 1;}
      else if (!red && green && blue) {colorStates[2] = 2;}
      else if (red && !green && blue) {colorStates[2] = 3;}
      else if (red && green && blue) {colorStates[2] = 0;}
     
      if (red) digitalWrite(quadThreePins[0], HIGH);
      else {digitalWrite(quadThreePins[0], LOW);}
      if (green) digitalWrite(quadThreePins[1], HIGH);
      else {digitalWrite(quadThreePins[1], LOW);}
      if (blue) digitalWrite(quadThreePins[2], HIGH);
      else {digitalWrite(quadThreePins[2], LOW);}
      }
    else if (playerNum == 4) {
      if (!red && !green && !blue) {colorStates[3] = 1;}
      else if (!red && green && blue) {colorStates[3] = 2;}
      else if (red && !green && blue) {colorStates[3] = 3;}
      else if (red && green && blue) {colorStates[3] = 0;}
     
      if (red) digitalWrite(quadFourPins[0], HIGH);
      else {digitalWrite(quadFourPins[0], LOW);}
      if (green) digitalWrite(quadFourPins[1], HIGH);
      else {digitalWrite(quadFourPins[1], LOW);}
      if (blue) digitalWrite(quadFourPins[2], HIGH);
      else {digitalWrite(quadFourPins[2], LOW);}
      }
  }
 
 void translateIR() {

  switch(results.value){
    case 0xFFA25D:{//Power Button Case - Reset  
      digitalWrite(resetPin, LOW);
      break;
    }

   
    case 0xFFE21D: //FUNC/STOP Case: off
    {
     
      break;}
    case 0xFF629D: Serial.println("VOL+"); break;
    case 0xFF22DD: Serial.println("FAST BACK");    break;
    case 0xFF02FD: Serial.println("PAUSE");    break;
    case 0xFFC23D: Serial.println("FAST FORWARD");   break;
    case 0xFFE01F: Serial.println("DOWN");    break;
    case 0xFFA857: Serial.println("VOL-");    break;
    case 0xFF906F: Serial.println("UP");    break;
    case 0xFF9867: Serial.println("EQ");    break;
    case 0xFFB04F: Serial.println("ST/REPT");    break;
   
    case 0xFF6897://0 case - Next Turn
    {
      //We know that the current player is rainbow. We need to set them to white, switch to the next player, set them to rainbow (start them off at red, then set their status to be cycling)
      int currentPlayer = playerTurn;
      recolorStrip(currentPlayer, false, false, false);
     
      //Old player has been set to white. Time to find next player.
      bool isValid = false;
      while (!isValid){
        currentPlayer = (currentPlayer%4) + 1;
        if (isAlive[currentPlayer - 1]) isValid = true;
      }
      playerTurn = currentPlayer;
     
      //New player has been found. Time to set them to red, then make sure they're marked as rainbow.
     for (int i = 0; i <= 3; i++){
      recolorStrip(currentPlayer, true, true, true);
      delay(167);
      recolorStrip(currentPlayer, true, false, true);
      delay(167);
     }
     
     
     
    break;
    }
   
    case 0xFF30CF: //1 Case - Quadrant 1 Dead
    {
      isAlive[0] = false;
      recolorStrip(1, false, true, true);
      break;
    }
   
    case 0xFF18E7: //2 Case - Quadrant 2 Dead
    {
      isAlive[1] = false;
      recolorStrip(2, false, true, true);
      break;
    }

   
    case 0xFF7A85: //3 Case - Quadrant 3 Dead
    {
      isAlive[2] = false;
      recolorStrip(3, false, true, true);
      break;
    }

   
    case 0xFF10EF: //4 Case - Quadrant 4 Dead
    {
      isAlive[3] = false;
      recolorStrip(4, false, true, true);
      break;
    }

   //TODO - Implement future use cases
    case 0xFF38C7: Serial.println("5");    break;
    case 0xFF5AA5: Serial.println("6");    break;
    case 0xFF42BD: Serial.println("7");    break;
    case 0xFF4AB5: Serial.println("8");    break;

   
    case 0xFF52AD: Serial.println("9");    break;

   
  default: Serial.print("Default case with command "); Serial.print(results.value);
  }
}
