/*
 * RPS Demo 
 * July 4, 2016
 * Code by Dan Lungaro
 * Graphics by L. Torrecilla
 */
#include "Arduboy.h"
#include "Gfx.h"
#include "globals.h"

Arduboy arduboy;

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
    y = 40;
    arduboy.setCursor(x,y);
    endMatch();
  }
  else if(GAME_STATE == STATS)
  {
    doStats();
  }
  
  arduboy.setCursor(x,y);
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
  arduboy.print("PLAYER:");
  printMove(curChoice);
  drawHand(30,30,curChoice);
  
  if((arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) && (curChoice != 0))
  {
    arduboy.tunes.tone(175,100);
    getEnemyChoice();
    GAME_STATE = END_MATCH;
  }

}

void endMatch()
{
  //arduboy.print("PLAYER:");
  //printMove(curChoice);
  //arduboy.print("ENEMY:");
  //printMove(enemyChoice);
  
  matchResult = (curChoice - enemyChoice + 3) % 3;
  if(matchResult == 0)
    tieMatch();
  if(matchResult == 1)
    winMatch();
  if(matchResult == 2)
    lossMatch();

  drawHand(26,5,curChoice);
  drawHand(92,5,enemyChoice);
  arduboy.println("Press UP for rematch\nPress Down for Stats");

  if(arduboy.pressed(UP_BUTTON))
  {
    y = 0;
    addScore();
    GAME_STATE = MATCH;
  }
  if(arduboy.pressed(DOWN_BUTTON))
  {
    y = 0;
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
  curChoice = 0;
  enemyChoice = 0;
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

void drawHand(byte x,byte y,byte hand)
{
  switch (hand)
  {
    case (ROCK):
    {
      arduboy.drawBitmap(x,y,rockGfx,16,16,WHITE);
      break;
    }
    case (PAPER):
    {
      arduboy.drawBitmap(x,y,paperGfx,16,16,WHITE);
      break;
    }
    case (SCISSORS):
    {
      arduboy.drawBitmap(x,y,scissorsGfx,16,16,WHITE);
      break;
    }
    default:
     break;
  }
}


