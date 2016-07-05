#define ROCK 1
#define PAPER 2
#define SCISSORS 3

#define MAIN_MENU 0
#define STATS 1
#define MATCH 2
#define END_MATCH 3


#define MAIN_MENU_PLAY 0
#define MAIN_MENU_STATS 1

byte x,y;
byte curChoice = 0;
byte enemyChoice = 0;
byte win = 0,loss = 0,tie = 0;
byte matchResult;
bool winBool = false,lossBool = false, tieBool = false;
byte menuChoice = MAIN_MENU_PLAY;
byte GAME_STATE = 0;
