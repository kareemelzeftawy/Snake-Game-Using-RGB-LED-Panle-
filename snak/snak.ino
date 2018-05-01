#include <LinkedList.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <avr/pgmspace.h>

// RGB Matrix pin defines
#define CLK 8 
#define LAT A3
//#define LAT 10
#define OE  9
#define A   A0
#define B   A1
#define C   A2

//symbolic button defines
#define UP 4
#define RIGHT 7
#define DOWN 5
#define LEFT 6
#define START 3

// Push Buttons defines
#define UP_Button 13
#define LEFT_Button 12
#define RIGHT_Button 11
#define DOWN_Button 1
#define START_Button 0
#define speakerOut 10

// instantiate matrix object
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false, 1);

// Intro screen frames stored in flash memory

const char snek1[][14][3] PROGMEM = {{{0, 0, 0},{0, 0, 0},{10, 0, 0},{10, 0, 0},{8, 8, 8},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0}},
{{0, 0, 0},{10, 0, 0},{10, 0, 0},{10, 0, 0},{8, 8, 8},{10, 10, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0}},
{{0, 0, 0},{10, 0, 0},{10, 0, 0},{10, 0, 0},{8, 8, 8},{10, 10, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0}},
{{10, 0, 0},{8, 8, 8},{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 10, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 0, 0}},
{{10, 0, 0},{10, 10, 10},{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 10, 0},{0, 0, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 10}},
{{10, 0, 0},{10, 10, 10},{10, 10, 10},{10, 0, 0},{10, 10, 0},{10, 10, 0},{0, 0, 0},{10, 10, 0},{0, 10, 0},{0, 10, 10},{0, 10, 10},{0, 10, 10},{0, 10, 10},{0, 10, 10}},
{{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 10, 0},{0, 0, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 10, 10},{0, 10, 10}},
{{0, 0, 0},{10, 0, 0},{10, 0, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 10, 10},{0, 10, 10},{0, 10, 10}},
{{0, 0, 0},{0, 0, 0},{10, 0, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 10},{0, 10, 10},{0, 0, 0}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 10},{0, 0, 10},{0, 10, 10},{0, 0, 0}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 10},{0, 0, 10},{0, 0, 0},{0, 0, 0}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 10},{0, 0, 10},{0, 0, 0},{0, 0, 0}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 10},{0, 0, 0},{0, 0, 0}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{10, 0, 10},{10, 0, 10},{0, 0, 0}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{10, 0, 10},{0, 0, 0}}};

const char snek2[][14][3] PROGMEM = {{{0, 0, 0},{8, 8, 8},{10, 0, 0},{10, 0, 0},{8, 8, 8},{8, 8, 8},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0}},
{{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 0, 0},{8, 8, 8},{10, 10, 0},{8, 8, 8},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0}},
{{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 0, 0},{8, 8, 8},{10, 10, 0},{8, 8, 8},{0, 0, 0},{0, 0, 0},{8, 8, 8},{8, 8, 8},{8, 8, 8},{8, 8, 8},{0, 0, 0}},
{{10, 0, 0},{8, 8, 8},{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 10, 0},{8, 8, 8},{8, 8, 8},{8, 8, 8},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{8, 8, 8}},
{{10, 0, 0},{10, 10, 10},{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 10, 0},{8, 8, 8},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 10}},
{{10, 0, 0},{10, 10, 10},{10, 10, 10},{10, 0, 0},{10, 10, 0},{10, 10, 0},{8, 8, 8},{10, 10, 0},{0, 10, 0},{0, 10, 10},{0, 10, 10},{0, 10, 10},{0, 10, 10},{0, 10, 10}},
{{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 10, 0},{8, 8, 8},{10, 10, 0},{10, 10, 0},{10, 10, 0},{8, 8, 8},{0, 10, 10},{0, 10, 10},{0, 10, 10},{0, 10, 10}},
{{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{8, 8, 8},{8, 8, 8},{0, 0, 10},{0, 10, 10},{8, 8, 8},{8, 8, 8}},
{{0, 0, 0},{8, 8, 8},{10, 0, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{8, 8, 8},{8, 8, 8},{0, 0, 0},{8, 8, 8},{0, 0, 10},{0, 0, 10},{8, 8, 8},{0, 0, 0}},
{{0, 0, 0},{0, 0, 0},{8, 8, 8},{8, 8, 8},{8, 8, 8},{8, 8, 8},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{0, 0, 10},{0, 0, 10},{0, 0, 10},{8, 8, 8}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{0, 0, 10},{10, 0, 10},{10, 0, 10}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{8, 8, 8},{10, 0, 10}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{10, 0, 10}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{10, 0, 10},{8, 8, 8}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{8, 8, 8},{0, 0, 0}}};

const char PROGMEM snek3[][14][3] PROGMEM = {{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0}},
{{8, 8, 8},{10, 10, 10},{10, 10, 10},{10, 0, 0},{10, 10, 0},{8, 8, 8},{8, 8, 8},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{8, 8, 8}},
{{10, 0, 0},{10, 10, 10},{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 10, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0}},
{{10, 0, 0},{8, 8, 8},{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 10, 0},{8, 8, 8},{8, 8, 8},{8, 8, 8},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{8, 8, 8}},
{{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 10, 0},{10, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 10}},
{{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 0, 0},{10, 10, 0},{10, 10, 0},{0, 10, 0},{0, 10, 0},{0, 10, 10},{0, 10, 10},{0, 10, 10},{0, 10, 10},{0, 10, 10}},
{{10, 0, 0},{8, 8, 8},{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 10, 0},{10, 10, 0},{10, 10, 0},{0, 10, 0},{8, 8, 8},{0, 10, 10},{0, 10, 10},{0, 10, 10},{0, 10, 10}},
{{10, 0, 0},{10, 10, 10},{8, 8, 8},{10, 0, 0},{10, 0, 0},{10, 10, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{8, 8, 8},{0, 0, 10},{0, 10, 10},{8, 8, 8},{8, 8, 8}},
{{8, 8, 8},{10, 10, 10},{10, 10, 10},{10, 0, 0},{10, 10, 0},{8, 8, 8},{8, 8, 8},{8, 8, 8},{0, 0, 0},{8, 8, 8},{0, 0, 10},{0, 0, 10},{8, 8, 8},{0, 0, 0}},
{{0, 0, 0},{8, 8, 8},{8, 8, 8},{8, 8, 8},{8, 8, 8},{8, 8, 8},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{0, 0, 10},{0, 0, 10},{0, 0, 10},{8, 8, 8}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{0, 0, 10},{10, 0, 10},{10, 0, 10}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{8, 8, 8},{10, 0, 10}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{10, 0, 10}},
{{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{8, 8, 8},{10, 0, 10},{8, 8, 8}}};

#define mC 1911
#define mC1 1804
#define mD 1703
#define mEb 1607
#define mE 1517
#define mF 1432
#define mF1 1352
#define mG 1276
#define mAb 1204
#define mA 1136
#define mBb 1073
#define mB 1012
#define mc 955
#define mc1 902
#define md 851
#define meb 803
#define me 758
#define mf 716
#define mf1 676
#define mg 638
#define mab 602
#define ma 568
#define mbb 536
#define mb 506

#define mp 0  //pause


// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[],
//  which sets each note's relative length (higher #, longer note)
int melody[] = {mg};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int beats[]  = {8};

//int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
int MAX_COUNT = sizeof(melody) / sizeof(int); // Melody length, for looping.

// Set overall tempo
long tempo = 20000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;


// define node struct
struct node 
{
  uint8_t x;       // location of node
  uint8_t y;
  uint8_t dir;     // direction node is moving
  boolean r, g, b; // color of node
};

// single node to act as food pixel
node food;

// more global variables             
byte controller_byte = 255;  // byte to shift in NES Controller button states
uint8_t color = 1;           // variable to cycle through food pixel colors
uint8_t current_dir = RIGHT; // keeps track of current direction given by NES Controller
uint16_t d = 600;            // delay to set snake's speed
uint16_t score = 0;          // score for game
boolean ate = false;         // flag set true when snek ate a food pixel, time to respawn new food
boolean next_state = false;  // flag asserted when time to go to next game state in FSM
boolean collision = false;   // flag asserted when snake collides with itself

// make a linked list of type node, to hold nodes in the snake
LinkedList <node> snake;


void setup() 
{
  matrix.begin();

  pinMode(speakerOut, OUTPUT);
  TriggerSound();
  
  // set DDR for the buttons pins
  pinMode(UP_Button, INPUT_PULLUP);
  pinMode(LEFT_Button, INPUT_PULLUP);
  pinMode(RIGHT_Button, INPUT_PULLUP);
  pinMode(DOWN_Button, INPUT_PULLUP);
  pinMode(START_Button, INPUT_PULLUP);

  // start with 3 node snake
  snake.add({2, 0, RIGHT, false, false, true});
  snake.add({1, 0, RIGHT, true, false, true});
  snake.add({0, 0, RIGHT, true, true, true});

  // seed random number generator
  randomSeed(analogRead(3));

  // set text size to print, used for displaying score
  matrix.setTextSize(1);
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

    // when coming back from score screen, wait for player to unpress start button
    while(next_state == true)
      read_controller();

    // start screen state
    while(next_state == false)
    {
      // display start screen animation
      start_screen();
    }
    
    // start game, clear screen, reset score to 0, put out new food pixel
    matrix.fillScreen(0);
    score = 0;
    new_food();

    // wait for start button to be let go
    while(next_state == true)
            read_controller();

    // game play mode state
    // while snake hasn't killed itself
    while(collision == false)
    {
      // if snake ate food pixel, respawn new one
      if(ate == true)
      {
         // generate new food pixel
         new_food();

         // draw new food pixel on screen
         matrix.drawPixel(food.x, food.y, matrix.Color333(food.r*10, food.g*10, food.b*10));
         
         // reset ate flag
         ate = false;

         // update delay 
         d = d > 130 ? 550 - score*7: d;
      }

      // else
    
      // check is snake ate food pixel
      ate_food();

      // draw food pixel on screen, if not already
      matrix.drawPixel(food.x, food.y, matrix.Color333(food.r*10, food.g*10, food.b*10));
      
      // mode snake on screen
      move_snake();

      // draw updated snake on screen
      draw_snake();
    
      // check if snake had collision
      detect_collision();
      
      // during delay between next pass, check controller input
      // to recieve potential new direction for snake
      for(int i = 0; i < d; i++)
        read_controller();

      // pause
      if(next_state == true)
        {
          while(next_state == true)
            read_controller();

          while(next_state == false)
            read_controller();

          while(next_state == true)
            read_controller();
        }
    
    } // end gameplay mode state

  // reset next_state flag
  next_state = false;

  // reset screen
  matrix.fillScreen(0);

  // variable used to shift colors in score screen
  uint8_t c = 0;

  // score screen state
    // while user hasn't pressed start
    while(next_state == false)
    { 
     // display score on screen
     show_score(c);

     // increment color shifting variable
     c++;

     // check controller
     read_controller();

     // if start button pressed, exit score display state
     if(next_state == true)
     break;
    }

    // reset game paramters
    reset_game();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// redraw snake at new location on screen
void draw_snake()
{ 
  // for all nodes in snake, draw node's pixel color at it's location
  for(int i = 0; i < snake.size(); i++)
      matrix.drawPixel(snake.get(i).x, snake.get(i).y, matrix.Color333(snake.get(i).r*10, snake.get(i).g*10, snake.get(i).b*10));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// move snake one iteration
void move_snake()
{
  // remove tail pixel of snake on screen
  matrix.drawPixel(snake.get(snake.size()-1).x, snake.get(snake.size()-1).y, matrix.Color333(0,0,0));

  node temp;     // temp node for shifting down directions
  int del_x = 0; // change in x and y motion of a node
  int del_y = 0;

 // update directions of nodes of snake:
 // from the tail node, the direction of the tail node is the direction of the node before it.
 // continue shifting direction of nodes down and stop at head of snake. 
 for(int i = snake.size()-1; i > 0; i--)
    {
      temp = snake.get(i);
      temp.dir = snake.get(i-1).dir;
      snake.set(i, temp);
    }

  // set direction of head node of snake to current direction variable
  temp = snake.get(0);
  temp.dir = current_dir;
  snake.set(0, temp);
  

  // now update locations of snake nodes based on each node's direction. 
  for(int i = 0; i < snake.size(); i++)
     {
      // reset change in x/y too apply to node's location
      del_x = del_y = 0;

      // set change in x/y to be applied to node depending on direction of node.
      if(snake.get(i).dir == RIGHT)
        del_x = 1;

      if(snake.get(i).dir == LEFT)
        del_x = -1;
        
      if(snake.get(i).dir == UP)
        del_y = -1;

      if(snake.get(i).dir == DOWN)
        del_y = 1;

      // set current contents of node to temp node.
      temp = snake.get(i);

      // update temp nodes x location, accounting for wrap around the screen
      if(temp.x == 31 && del_x == 1)
        temp.x = 0;
      else if(temp.x == 0 && del_x == -1)
        temp.x = 31;
      else
        temp.x = temp.x + del_x;

      // update temp nodes y location, accounting for wrap around the screen
      if(temp.y == 15 && del_y == 1)
        temp.y = 0;
      else if(temp.y == 0 && del_y == -1)
        temp.y = 15;
      else
        temp.y = temp.y + del_y;

      // set the current node equal to the modified temp node
      snake.set(i, temp);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

boolean ate_food()
{
  // if snake's head is about to move into same location of food node,
  // based on head's location and direction, make food pixel head of snake,
  // and set ate flag as true, so new food is respawned
  
  if(current_dir == UP && (snake.get(0).y - 1 == food.y && snake.get(0).x == food.x) 
                       || (snake.get(0).y == 0 && food.y == 15 && snake.get(0).x == food.x))
    {
      food.dir = UP;
      snake.unshift(food);
      ate = true;
      TriggerSound();
    }
  if(current_dir == DOWN && (snake.get(0).y + 1 == food.y && snake.get(0).x == food.x)
                         || (snake.get(0).y == 15 && food.y == 0 && snake.get(0).x == food.x))
    {
      food.dir = DOWN;
      snake.unshift(food);
      ate = true;
      TriggerSound();
    }
  if(current_dir == LEFT && (snake.get(0).x - 1 == food.x && snake.get(0).y == food.y)
                         || (snake.get(0).x  == 0 && food.x == 31 && snake.get(0).y == food.y))
    {
      food.dir = LEFT;
      snake.unshift(food);
      ate = true;
      TriggerSound();
    }
  if(current_dir == RIGHT && (snake.get(0).x + 1 == food.x && snake.get(0).y == food.y)
                          || (snake.get(0).x  == 31 && food.x == 0 && snake.get(0).y == food.y))
    {
      food.dir = RIGHT;
      snake.unshift(food);
      ate = true;
      TriggerSound();
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

// Push_Buttons Controller
void read_controller()
{  
   // if UP button pressed and head can go up, change direction
   if((digitalRead(UP_Button) == LOW) && (snake.get(0).dir == LEFT || snake.get(0).dir == RIGHT))
     current_dir = UP;
   

  // if DOWN button pressed and head can go up, change direction
  if((digitalRead(DOWN_Button) == LOW) && (snake.get(0).dir == LEFT || snake.get(0).dir == RIGHT))
      current_dir = DOWN;


  // if LEFT button pressed and head can go up, change direction
  if((digitalRead(LEFT_Button) == LOW) && (snake.get(0).dir == UP || snake.get(0).dir == DOWN))
      current_dir = LEFT;


  // if RIGHT button pressed and head can go up, change direction
  if((digitalRead(RIGHT_Button) == LOW) && (snake.get(0).dir == UP || snake.get(0).dir == DOWN))
      current_dir = RIGHT;


   // if start button pressed, set next-state flag
   if(digitalRead(START_Button) == LOW)
     next_state = true;
   else 
     next_state = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// detect if the snake's head exists where any of it's other nodes are
void detect_collision()
{
 // location of head
 uint8_t head_x = snake.get(0).x;
 uint8_t head_y = snake.get(0).y;

 // for nodes greater than 4, check if collision occured
 for(int i = 3; i < snake.size(); i++)
   // if collision occured
   if(snake.get(i).x == head_x && snake.get(i).y == head_y)
      {
        // set collition flag true, delay, and return
        collision = true;
        delay(2000);
        TriggerSound();
        TriggerSound();
        return;
      }  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// generate new food pixel on screen
void new_food()
{
  // update score
  score++;

  // get random location for new food
  // this can be where a snake node is
  food.x = random(0, 32);
  food.y = random(0, 16);

  // cycle color variable to next color in rainbow
  if(color < 5)
    color++;
  else
    color = 0;

  // set color of new food pixel to next color in rainbow sequence
  if(color == 0)
    {
      food.r = true;
      food.g = false;
      food.b = true;
    }
  else if(color == 1)
    {
      food.r = false;
      food.g = false;
      food.b = true;
    }
   else if(color == 2)
     {
       food.r = false;
       food.g = true;
       food.b = true;
     }
   else if(color == 3)
     {
       food.r = false;
       food.g = true;
       food.b = false;
     }
   else if(color == 4)
     {
       food.r = true;
       food.g = true;
       food.b = false;
     }
   else if(color == 5)
     {
       food.r = true;
       food.g = false;
       food.b = false;
     }
  
   food.dir = UP;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// reset game parameters before new game
void reset_game()
{ 
  score = 0;                                    // reset score
  collision = false;                            // set collision flag off
  snake.clear();                                // clear snake linked list
  matrix.fillScreen(0);                         // clear screen
  d = 600;                                      // reset delay
  snake.add({2, 0, RIGHT, false, false, true}); // draw inition three node snake
  snake.add({1, 0, RIGHT, true, false, true});
  snake.add({0, 0, RIGHT, true, true, true});
  color = 1;                                    // reset color variable for new food pixel color
  current_dir = RIGHT;                          // starting direction is right
  new_food();                                   // generate a new food pixel
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// display score on screen
void show_score(int c)
{
  // display "SCORE"
  char S = 'S';
  char C = 'C';
  char O = 'O';
  char R = 'R';
  char E = 'E';

  // subroutine called to print character at certain location, with color dependent on c variable
  print_char(S, 0, 0, (c)%6);
  print_char(C, 6, 0, (c+1)%6);
  print_char(O, 12, 0, (c+2)%6);
  print_char(R, 18, 0, (c+3)%6);
  print_char(E, 24, 0, (c+4)%6);

  // display score value on screen
  matrix.setCursor(11, 8);
  matrix.print(score-1);
  matrix.swapBuffers(false);

  // delay between update and color shifting
  delay(100);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// print character on screen at location, with color dependent on color variable input
void print_char(char c, uint8_t x, uint8_t y, uint8_t color)
 {
   // set location of drawing cursor
   matrix.setCursor(x, y);

   // color goes from red to magenta, values 0, 5.
   // set actual color to draw character based on color input
   if(color == 0)
      matrix.setTextColor((matrix.Color333(10, 0, 0)));
   else if(color == 1)
      matrix.setTextColor((matrix.Color333(10, 10, 0)));
   else if(color == 2)
      matrix.setTextColor((matrix.Color333(0, 10, 0)));
   else if(color == 3)
      matrix.setTextColor((matrix.Color333(0, 10, 10)));
   else if(color == 4)
      matrix.setTextColor((matrix.Color333(0, 0, 10)));
   else if(color == 5)
      matrix.setTextColor((matrix.Color333(10, 0, 10)));

   // print character to screen
   matrix.print(c);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////

// start screen animation
void start_screen()
{
     
     // draw "SNAKE" on screen
     // S
     read_controller();
     matrix.drawPixel(16, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(17, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(18, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(16, 4, matrix.Color333(10, 10, 0));
     matrix.drawPixel(16, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(17, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(18, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(18, 6, matrix.Color333(0, 10, 10));
     matrix.drawPixel(18, 7, matrix.Color333(0, 0, 10));
     matrix.drawPixel(17, 7, matrix.Color333(0, 0, 10));
     matrix.drawPixel(16, 7, matrix.Color333(0, 0, 10));
    
     // N
     matrix.drawPixel(19, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(19, 4, matrix.Color333(10, 10, 0));
     matrix.drawPixel(19, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(19, 6, matrix.Color333(0, 10, 10));
     matrix.drawPixel(19, 7, matrix.Color333(0, 0, 10));
     matrix.drawPixel(20, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(21, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(21, 4, matrix.Color333(10, 10, 0));
     matrix.drawPixel(21, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(21, 6, matrix.Color333(0, 10, 10));
     matrix.drawPixel(21, 7, matrix.Color333(0, 0, 10));

     //A
     matrix.drawPixel(23, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(22, 4, matrix.Color333(10, 10, 0));
     matrix.drawPixel(24, 4, matrix.Color333(10, 10, 0));
     matrix.drawPixel(22, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(23, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(24, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(22, 6, matrix.Color333(0, 10, 10));
     matrix.drawPixel(24, 6, matrix.Color333(0, 10, 10));
     matrix.drawPixel(22, 7, matrix.Color333(0, 0, 10));
     matrix.drawPixel(24, 7, matrix.Color333(0, 0, 10));     
     
     // K
     matrix.drawPixel(25, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(25, 4, matrix.Color333(10, 10, 0));
     matrix.drawPixel(25, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(25, 6, matrix.Color333(0, 10, 10));
     matrix.drawPixel(25, 7, matrix.Color333(0, 0, 10));
     matrix.drawPixel(26, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(26, 6, matrix.Color333(0, 10, 10));
     matrix.drawPixel(27, 4, matrix.Color333(10, 10, 0));
     matrix.drawPixel(27, 7, matrix.Color333(0, 0, 10));
    
     // E
     matrix.drawPixel(28, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(29, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(30, 3, matrix.Color333(10, 0, 0));
     matrix.drawPixel(28, 4, matrix.Color333(10, 10, 0));
     matrix.drawPixel(28, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(29, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(30, 5, matrix.Color333(0, 10, 0));
     matrix.drawPixel(28, 6, matrix.Color333(0, 10, 10));
     matrix.drawPixel(28, 7, matrix.Color333(0, 0, 10));
     matrix.drawPixel(29, 7, matrix.Color333(0, 0, 10));
     matrix.drawPixel(30, 7, matrix.Color333(0, 0, 10));
    
     // Draw animation frames on screen, after each frame, check if the start button was pressed.

     for(int k = 0; k < 3; k++)
     {
       for(int i = 0; i < 15; i++)
          for(int j = 0; j < 14; j++)
            matrix.drawPixel(i+1, j+1, matrix.Color333(pgm_read_byte(&snek1[i][j][0]), pgm_read_byte(&snek1[i][j][1]), pgm_read_byte(&snek1[i][j][2])));
        delay(200);
        read_controller();
        if(next_state == true)
          return;
        
        for(int i = 0; i < 15; i++)
          for(int j = 0; j < 14; j++)
            matrix.drawPixel(i+1, j+1, matrix.Color333(pgm_read_byte(&snek2[i][j][0]), pgm_read_byte(&snek2[i][j][1]), pgm_read_byte(&snek2[i][j][2])));
        delay(200);
        read_controller();
        if(next_state == true)
          return;
     }
      
      for(int i = 0; i < 14; i++)
        for(int j = 0; j < 14; j++)
          matrix.drawPixel(i+1, j+1, matrix.Color333(pgm_read_byte(&snek3[i][j][0]), pgm_read_byte(&snek3[i][j][1]), pgm_read_byte(&snek3[i][j][2])));
      delay(1000);
      read_controller();
      if(next_state == true)
        return;
}

//**********************************************************************************************************************************************************
void TriggerSound()
{
  // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone();
    delayMicroseconds(pause);
  }
}



//**********************************************************************************************************************************************************
// Pulse the speaker to play a tone for a particular duration
void playTone() 
{
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                
}
