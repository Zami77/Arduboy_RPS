/*
 * Test Demo 
 * July 4, 2016
 * Dan Lungaro
 */
#include "Arduboy.h"

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

#define MAIN_MENU 0
#define STATS 1
#define MATCH 2
#define END_MATCH 3


#define MAIN_MENU_PLAY 0
#define MAIN_MENU_STATS 1

Arduboy arduboy;

//Variables here
byte x,y;
byte curChoice = 0;
byte enemyChoice = 0;
byte win = 0,loss = 0,tie = 0;
bool winBool = false,lossBool = false, tieBool = false;
byte menuChoice = MAIN_MENU_PLAY;
byte GAME_STATE = 0;

void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
  
  x = 0;
  y = 0;

}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(arduboy.nextFrame())) return;

  arduboy.clear();
  arduboy.setCursor(x,y);
  if(GAME_STATE == MAIN_MENU)
  {
    doMenu();
  }
  
  else if(GAME_STATE == MATCH)
  {
    
    doMatch();
  }

  else if(GAME_STATE == END_MATCH)
  {
    endMatch();
  }
  else if(GAME_STATE == STATS)
  {
    doStats();
  }
  
  arduboy.display();
}

void doMatch()
{
  if (arduboy.pressed(LEFT_BUTTON))
  {
    curChoice = ROCK;
  }
  if (arduboy.pressed(UP_BUTTON))
  {
    curChoice = PAPER;
  }
  if (arduboy.pressed(RIGHT_BUTTON))
  {
    curChoice = SCISSORS;
  }
  /*if (arduboy.pressed(DOWN_BUTTON))
  {
    GAME_STATE = MAIN_MENU;
  }
  */
  arduboy.print("PLAYER: ");
  switch(curChoice)
  {
    case(ROCK):
    {
      arduboy.print("Rock");
      break;
    }
    case(PAPER):
    {
      arduboy.print("Paper");
      break;
    }
    case(SCISSORS):
    {
      arduboy.print("Scissors");
      break;
    }
  }
  if((arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) && (curChoice != 0))
  {
    getEnemyChoice();
    GAME_STATE = END_MATCH;
  }

}

void endMatch()
{
  arduboy.print("PLAYER:");
  printMove(curChoice);
  arduboy.print("ENEMY:");
  printMove(enemyChoice);
  switch(curChoice)
  {
    case (ROCK):
    {
      if(enemyChoice == ROCK)
        tieMatch();
      
      else if(enemyChoice == PAPER)
        lossMatch();
      
      else if(enemyChoice == SCISSORS)
        winMatch();

      break;
    }
    case (PAPER):
    {
      if(enemyChoice == ROCK)
        winMatch();
      
      else if(enemyChoice == PAPER)
        tieMatch();
      
      else if(enemyChoice == SCISSORS)
        lossMatch();
      break;
    }
    case (SCISSORS):
    {
      if(enemyChoice == ROCK)
        lossMatch();
      
      else if(enemyChoice == PAPER)
        winMatch();
      
      else if(enemyChoice == SCISSORS)
        tieMatch();
      break;
    }
    default:
      //do nothing
      break;
  }
  arduboy.println("Press UP for rematch\nPress Down to Stats");

  if(arduboy.pressed(UP_BUTTON))
  {
    curChoice = 0;
    enemyChoice = 0;
    addScore();
    GAME_STATE = MATCH;
  }
  if(arduboy.pressed(DOWN_BUTTON))
  {
    addScore();
    GAME_STATE = STATS;
  }
}
void addScore()
{
  if (winBool)
    win++;
  else if(lossBool)
    loss++;
  else if(tieBool)
    tie++;
  winBool = false;
  lossBool = false;
  tieBool = false;
}
void tieMatch()
{
  tieBool = true;
  arduboy.println("It's a tie!");
}
void winMatch()
{
  winBool = true;
  arduboy.println("It's a win!");
}
void lossMatch()
{
  lossBool = true;
  arduboy.println("It's a loss...");
}
void printMove(byte moveChoice)
{
  switch(moveChoice)
  {
    case ROCK:
      arduboy.println("Rock");
      break;
    case PAPER:
      arduboy.println("Paper");
      break;
    case SCISSORS:
      arduboy.println("Scissors");
      break;
  }
}
void getEnemyChoice()
{
  enemyChoice = random(1,4);
}
void doMenu()
{
  if(menuChoice == MAIN_MENU_PLAY)
  {
    arduboy.println("->Play Game");
    arduboy.println("Stats");
  }
  if(menuChoice == MAIN_MENU_STATS)
  {
    arduboy.println("Play Game");
    arduboy.println("->Stats");
  }

  if(arduboy.pressed(DOWN_BUTTON))
  {
    if(menuChoice >= 1){
      //do nothing
      }
    else{
      menuChoice++;}
  }
  if(arduboy.pressed(UP_BUTTON))
  {
    if(menuChoice <= 0){
      //do nothing
      }
    else{
      menuChoice--;
    }

  }
  
  
  curChoice = 0;
  enemyChoice = 0;
  if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON))
  {
    
    switch (menuChoice)
    {
      case (MAIN_MENU_PLAY):
      {
        GAME_STATE = MATCH;
        break;
      }
      case (MAIN_MENU_STATS):
      {
        GAME_STATE = STATS;
        break;
      }
    }
    menuChoice = MAIN_MENU_PLAY;
  }
}

void doStats()
{
  arduboy.println("\tSTATS\n----------");
  arduboy.print("Win(s):");
  arduboy.println(win);
  arduboy.print("Loss(es):");
  arduboy.println(loss);
  arduboy.print("Tie(s):");
  arduboy.println(tie);
  arduboy.println("Press UP for Menu...");
  if (arduboy.pressed(UP_BUTTON))
    GAME_STATE = MAIN_MENU;
  
}

