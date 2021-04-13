/*
 * Author: Logan Hartford
 * Description: A physical tic tac toe game created using and arduino nano, RGB led's and shift registers.
 * Note: - All functions can be found below the void loop(){}.
 *       - Player 1's selections are made with blue, Player 2's with red. 
 *       - Both red and blue are turned ON to create megenta which is the cursor color.
 *       - Due to the physical orientation of the components my data structures may seem a bit confusing. 
 *         While the game only makes use of 18 pins, I was not able to wire to 18 consecutive pins so the 
 *         moves array is 24 long rather than 18. The LED's are also not wired in such a way that pin numbers 
 *         intuitively correspond to their positon on the board so various "perpective based" data structure
 *         had to be made.
 */

#include <HC595.h>

// Player 1 controls
int left1 = 10;
int right1 = 11;
int select1 = 12;

int left1Read;
int right1Read;
int select1Read;

// Player 2 Controls
int left2 = 3;
int right2 = 8;
int select2 = 2;

int left2Read;
int right2Read;
int select2Read;

// Player 1 Pin Arrays (Based player perspective.)
int red1[9] = {19, 21, 23, 18, 22, 13, 4, 2, 11};
int blue1[9] = {20, 15, 14, 6, 10, 12, 5, 3, 1};

// Player 2 Pin Arrays (Based on player perspecitve.)
int red2[9] = {11, 2, 4, 13, 22, 18, 23, 21, 19};
int blue2[9] = {1, 3, 5, 12, 10, 6, 14, 15, 20};

// Array to track all moves made so far. 24 = 3 x 8 pin shift registers
int moves[24] = {0}; 
                                                  
// Turn Tracker
int turn = 1; // 1 for player 1, 2 for player 2.

// Shift Register Stuff
int latchPin = 5;
int clockPin = 4;
int dataPin = 6;
HC595 msr (3, latchPin, clockPin, dataPin);

// Cursor
int pos = 0;

// Delays
int dt = 200;
int dt2 = 350;
int bdt = 300; // Button delay fo bouncing


void setup() {
  Serial.begin(9600);
  
  // Shift Register 
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  msr.reset();

  // P1
  pinMode(left1, INPUT);
  pinMode(right1, INPUT);
  pinMode(select1, INPUT);

  digitalWrite(left1, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(select1, HIGH);
  
  // P2
  pinMode(left2, INPUT);
  pinMode(right2, INPUT);
  pinMode(select2, INPUT);

  digitalWrite(left2, HIGH);
  digitalWrite(right2, HIGH);
  digitalWrite(select2, HIGH);
}

void loop() {
  // Player 1 is blue
  if (turn == 1) {
    start(turn);
    while (turn == 1) {
      // Reads all of the buttons to detect player input
      left1Read = digitalRead(left1);
      right1Read = digitalRead(right1);
      select1Read = digitalRead(select1);
      // Move left
      if (left1Read == 0) {
        delay(bdt);
        moveLeft(turn);
      }
      // Move right
      if (right1Read == 0) {
        delay(bdt);
        moveRight(turn);
      }
      // Make a selection
      if (select1Read == 0) {
        delay(bdt);
        select(turn);
        // Checks to see if selection resulted in a win condition
        if (winCheck(1)) {
          break;
        }
        // Checks to see if the game is a tie
        if (catsGameCheck()) {
         break; 
        }
      }
    }
  }
  
  // Player 2 is red
  if (turn == 2) {
    start(turn);
    while (turn == 2) {
      left2Read = digitalRead(left2);
      right2Read = digitalRead(right2);
      select2Read = digitalRead(select2);
      if (left2Read == 0) {
        delay(bdt);
        moveLeft(turn);
      }
      if (right2Read == 0) {
        delay(bdt);
        moveRight(turn);
      }
      if (select2Read == 0) {
        delay(bdt);
        select(turn);
        if (winCheck(2)) {
          break;
        }
        if (catsGameCheck()) {
         break; 
        }
      }
    }
  }       
}

//######################### FUNCTIONS #########################

// start(): sets the cursor back to the proper position at  the 
// begining of each turn.
void start(int turn) { 
  // Player 1
  if (turn == 1) {
    // Turns on upper left block from P1 perspective.
    // Flashes LED's to let user know turn has begun.
    msr.setPin(red1[pos], ON);
    msr.setPin(blue1[pos], ON);
    delay(dt2);
    // Leaves on LED ON if a move has been made on this tile 
    // to remind the user.
    if (moves[red1[pos]] == 0) {
       msr.setPin(red1[pos], OFF);
    }
    if (moves[blue1[pos]] == 0) {
      msr.setPin(blue1[pos], OFF);
    }
    delay(dt2);
    msr.setPin(red1[pos], ON);
    msr.setPin(blue1[pos], ON);
  }
  // Player 2
  else if (turn == 2) {
    msr.setPin(red2[pos], ON);
    msr.setPin(blue2[pos], ON);
    delay(dt2);
    if (moves[red2[pos]] == 0) {
       msr.setPin(red2[pos], OFF);
    }
    if (moves[blue2[pos]] == 0) {
      msr.setPin(blue2[pos], OFF);
    }
    delay(dt2);
    msr.setPin(red2[pos], ON);
    msr.setPin(blue2[pos], ON);
  }
}

// moveLeft(): Moves the "cursor" one to the left
void moveLeft(int turn) {
  // Player 1
  if (turn == 1) {
    // Checks to see if moves have been made on pin, if so, leave them on.
    if (moves[red1[pos]] == 0) {
      msr.setPin(red1[pos], OFF);
    }
    if (moves[blue1[pos]] == 0) {
      msr.setPin(blue1[pos], OFF);
    }
    // Moves cursor to the left
    pos--;
    // Wraps around
    if (pos < 0) {
      pos = 8;
    }
    // Turns next pins on
    msr.setPin(red1[pos], ON);
    msr.setPin(blue1[pos], ON);
  }

  // Player 2
  if (turn == 2) {
    if (moves[red2[pos]] == 0) {
      msr.setPin(red2[pos], OFF);
    }
    if (moves[blue2[pos]] == 0) {
      msr.setPin(blue2[pos], OFF);
    }
    pos--;
    if (pos < 0) {
      pos = 8;
    }
    msr.setPin(red2[pos], ON);
    msr.setPin(blue2[pos], ON);
  }
}

// moveRight moves the "cursor" one positon to the right.
void moveRight(int turn) {
  // Player 1
  if (turn == 1) {
    // Checks to see if moves have been made on pin, if so, leave them on.
    if (moves[red1[pos]] == 0) {
      msr.setPin(red1[pos], OFF);
    }
    if (moves[blue1[pos]] == 0) {
      msr.setPin(blue1[pos], OFF);
    }
    // Moves cursor to the right
    pos++;
    // Wraps around
    if (pos > 8) {
      pos = 0;
    }
    // Turns next pins on
    msr.setPin(red1[pos], ON);
    msr.setPin(blue1[pos], ON);
  }

  // Player 2
  if (turn == 2) {
    if (moves[red2[pos]] == 0) {
      msr.setPin(red2[pos], OFF);
    }
    if (moves[blue2[pos]] == 0) {
      msr.setPin(blue2[pos], OFF);
    }
    pos++;
    if (pos > 8) {
      pos = 0;
    }
    msr.setPin(red2[pos], ON);
    msr.setPin(blue2[pos], ON);
  }
}

// select(): allows player to select block to place colour on.
void select(int turn) {
  // Player 1 is blue
  if (turn == 1) {
    // checks moves array to see if P1 or P2 has already made this move.
    if (moves[blue1[pos]] == 1) {
      flashOne(red1[pos]);
    }
    else if (moves[red1[pos]] == 1) {
      flashOne(blue1[pos]);
    }
    // If the move is not taken, make selection.
    else {
      // Blinks led and leave players colour on
      msr.setPin(red1[pos], OFF);
      msr.setPin(blue1[pos], OFF);
      delay(dt);
      msr.setPin(blue1[pos], ON);
      // Updates moves array
      moves[blue1[pos]] = 1;
      // Set cursor back to start
      pos = 0;
      // Change global variable turn
      ::turn = 2;
    }
  }

  // Player 2 is red
  else if (turn == 2) {
    if (moves[blue2[pos]] == 1) {
      flashOne(red2[pos]);
    }
    else if (moves[red2[pos]] == 1) {
      flashOne(blue2[pos]);
    }
    else {
      msr.setPin(red2[pos], OFF);
      msr.setPin(blue2[pos], OFF);
      delay(dt);
      msr.setPin(red2[pos], ON);
      moves[red2[pos]] = 1;
      pos = 0;
      ::turn = 1;
    }
  }
}

// flashOne(): rapidly flashes a single LED ON and OFF 3 times.
void flashOne(int i) {
  msr.setPin(i, OFF);
  delay(dt);
  msr.setPin(i, ON);
  delay(dt);
  msr.setPin(i, OFF);
  delay(dt);
  msr.setPin(i, ON);
  delay(dt);
  msr.setPin(i, OFF);
  delay(dt);
  msr.setPin(i, ON);
  delay(dt);
}

// flash() repidly flashes 3 led's ON and OFF 3 times.
void flash(int i, int j, int k) {
  // Flashes 3 LED's 3 times
  msr.setPin(i, OFF);
  msr.setPin(j, OFF);
  msr.setPin(k, OFF);
  delay(dt);
  msr.setPin(i, ON);
  msr.setPin(j, ON);
  msr.setPin(k, ON);
  delay(dt);
  msr.setPin(i, OFF);
  msr.setPin(j, OFF);
  msr.setPin(k, OFF);
  delay(dt);
  msr.setPin(i, ON);
  msr.setPin(j, ON);
  msr.setPin(k, ON);
  delay(dt);
  msr.setPin(i, OFF);
  msr.setPin(j, OFF);
  msr.setPin(k, OFF);
  delay(dt);
  msr.setPin(i, ON);
  msr.setPin(j, ON);
  msr.setPin(k, ON);
  delay(dt);
}

// flashAll(): creates an array which contains the pins of all of the
// currently ON led's and then flashes them OFF and ON 3 times.
void flashAll() {
  // Array to store ON pins
  int onPin[9] = {0};
  int count = 0;
  // Checks moves array for ON pins then adds them to onPin[].
  for (int i = 0; i < 24; i++) {
    if (moves[i] == 1) {
      onPin[count] = i;
      count++;
    }
  }
  // Flashes all of the pins collected in onPin
  for (int i : onPin) {
    msr.setPin(i, OFF);
  }
  delay(dt);
  for (int i : onPin) {
    msr.setPin(i, ON);
  }
  delay(dt);
  for (int i : onPin) {
    msr.setPin(i, OFF);
  }
  delay(dt);
  for (int i : onPin) {
    msr.setPin(i, ON);
  }
  delay(dt);
  for (int i : onPin) {
    msr.setPin(i, OFF);
  }
  delay(dt);
  for (int i : onPin) {
    msr.setPin(i, ON);
  }
}

// reset() does everything necessary to reset the game.
void reset() {
  // Games always begin with player 1.
  turn = 1;
  // Resets cursor position
  pos = 0;
  // Sets moves array to all 0's
  for (int i = 0; i < 24; i++) {
    moves[i] = 0; 
  }
  // Clears all of the shift register's pins.
  msr.reset();
}

// catsGameCheck(): checks to see if all possible moves have been made,
// and if so resets the game.
// We return a bool here so we can break out of the while(turn == _) loop.
bool catsGameCheck() {
  // Array which stores the status of each board position.
  // as a 0 or 1.
  int cats[9] {0};
  // Checks for moves made by P1.
  for (int i = 0; i < 9; i++) {
    if (moves[blue1[i]] == 1) {
      cats[i] = 1;
    }
  }
  // Checks for moves made by P2.
  for (int i = 0; i < 9; i++) {
    if (moves[red1[i]] == 1) {
      cats[i] = 1;
    }
  }
  // result stays true if all possible moves have been made,
  // result becomes false if even a single move is available.
  bool result = true;
  for (int i = 0; i < 9; i++) {
    if (cats[i] == 0) {
      result = false;
    }
  }
  // If all moves have been made, end game and reset.
  if (result) {
    // flashes game board
    flashAll();
    delay(500);
    // resets game
    reset();
    return result;
  }
  else {
    return result;
  }
}

// winCheck(): checks to see if a win condition has been met.
// i.e.if a 3 square line in any direction has been made.
// We return a bool here so we can break out of the while(turn == _) loop.
bool winCheck(int turn) {
  // Player 1
  if (turn == 1) {
    // Array which stores the status of all the blue pins
    int p1Win[9] = {0};
    for (int i = 0; i < 9; i++) {
      if (moves[blue1[i]] == 1){
        p1Win[i] = 1;
      }
    }
    // checks for all win conditions the move through the center.
    // 0 1 2
    // 3 4 5
    // 6 7 8
    // For any win invloving the middle pin, the index of the other 2 pins
    // involved in the p1Win array will always add to 8.
    if (p1Win[4] == 1) {
      for (int i = 0; i < 4; i++) {
        if (p1Win[i] == 1 && p1Win[8 - i] == 1){
          // Game is won!
          // flashe winning line
          flash(blue1[i], blue1[8 - i], blue1[4]);
          // reset game.
          reset();
          return true;
          break;
        }
      }
    }
    // Brute for checks for any wins invloving top left corner.
    else if (p1Win[0] == 1) {
      if (p1Win[1] == 1 && p1Win[2] == 1){
        flash(blue1[0], blue1[1], blue1[2]);
        delay(500);
        reset();
        return true;
      }
      else if (p1Win[3] == 1 && p1Win[6] == 1){
        flash(blue1[6], blue1[3], blue1[0]);
        delay(500);
        reset();
        return true;
      }
    }
    // Brute force checks for any wins involving bottom left corner.
    else if (p1Win[8] == 1) {
      if (p1Win[5] == 1 && p1Win[2] == 1){
        flash(blue1[8], blue1[5], blue1[2]);
        delay(500);
        reset();
        return true;
      }
      else if (p1Win[6] == 1 && p1Win[7] == 1){
        flash(blue1[8], blue1[6], blue1[7]);
        delay(500);
        reset();
        return true;
      }
    }
    // No win conditions met.
    else {
      return false;
    }
  }
  // Player 2
  else if (turn == 2) {
    int p2Win[9] = {0};
    for (int i = 0; i < 9; i++) {
      if (moves[red2[i]] == 1){
        p2Win[i] = 1;
      }
    }
    if (p2Win[4] == 1) {
      for (int i = 0; i < 4; i++) {
        if (p2Win[i] == 1 && p2Win[8 - i] == 1){
          flash(red2[i], red2[8 - i], red2[4]);
          delay(500);
          reset();
          return true;
          break;
        }
      }
    }
    else if (p2Win[0] == 1) {
      if (p2Win[1] == 1 && p2Win[2] == 1){
        flash(red2[0], red2[1], red2[2]);
        delay(500);
        reset();
        return true;
      }
      else if (p2Win[3] == 1 && p2Win[6] == 1){
        flash(red2[6], red2[3], red2[0]);
        delay(500);
        reset();
        return true;
      }
    }
    else if (p2Win[8] == 1) {
      if (p2Win[5] == 1 && p2Win[2] == 1){
        flash(red2[8], red2[5], red2[2]);
        delay(500);
        reset();
        return true;
      }
      else if (p2Win[6] == 1 && p2Win[7] == 1){
        flash(red2[8], red2[6], red2[7]);
        delay(500);
        reset();
        return true;
      }
    }
    else {
      return false;
    }
  }
}
