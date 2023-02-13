// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT7L 
// Names: Low Kai Yan | Nicholas Tiow Kai Bo
// IDs:    1211101699 |  1211102398
// Emails: 1211101699@student.mmu.edu.my |  1211102398@student.mmu.edu.my
// Phones: +60 11-1536 9536 | +60 12-593 5388 
// ********************************************************* 

// ------------------------------ Library Used ----------------------------------------- //

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cctype>
#include <fstream>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>

// ----------------------------------- Set Color ------------------------------------------- //

#define C_DEFAULT -1
#define C_BLACK 0
#define C_DARK_RED 1
#define C_DARK_GREEN 2
#define C_DARK_YELLOW 3
#define C_DARK_BLUE 4
#define C_DARK_PINK 5
#define C_DARK_CYAN 6
#define C_DARK_GRAY 8
#define C_GRAY 7
#define C_RED 9
#define C_GREEN 10
#define C_YELLOW 11
#define C_BLUE 12
#define C_PINK 13
#define C_CYAN 14
#define C_WHITE 15

//  ----------------------- Key Code ------------------------
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_F1	59
#define KEY_F2	60
#define KEY_F3	61
#define KEY_F4	62
#define KEY_F5	63
#define KEY_F6	64
#define KEY_F7	65
#define KEY_F9 67
#define KEY_W 17
#define KEY_A 30
#define KEY_S 31
#define KEY_D 32
#define KEY_ESC 27
#define KEY_BACKSPACE 8

using namespace std;

//---------------------------------
//All Created void Function
//----------------------------------

//--------------------- Print Display ---------------------------------
void printDefaultSetting();
void printMap();
void printHelp();
void printMapDetails();
void printAll();
void printGoodbye();
void turnGuide(); // Display character turns'
void checkPCTurn(); // Move arrow to nect character

void loseGame(); // display lost game
void winGame(); // display win game

void quit(); // quit game

// ---------------------- Starting / Checking Map --------------------------------
void initMap();
void userCommand();
string randomlyNewObject();
int getPlayerPosY(vector<vector<string>> playerPos);
int getPlayerPosX(vector<vector<string>> playerPos);
bool isZombie(vector<vector<string>> v, int mX, int mY);
bool checkAllZomDead();
bool isObj(string n);

// ----------------- System CLS / ANSI Code ---------------------------
void sPause();
void xScreen();
void xScreenAll();

bool initColorTerminal(int &x, int &y);
void setCursor(int x, int y);
void setColor(int fc , int bc);
void clearLine(int y);
void showCursor(bool visible);

string getTimeNow(); // get latest time (hour:minute:second)

void clearVector(); // Clear all the initialize vector in the code before new game start

void maximizeWindow(); // maximize windows for better game experience

// ---------------------- Alien Function ----------------------------------

void moveAlien(int mX, int mY);
void clearTrail();
void controlArrow();
void podAttack();

// ------------------------- Zombie Move ----------------------------

void zombieMove();

//---------------------- Save/Read/AutoSave/AutoSync gameMap ---------------------------

void saveMapData(vector<vector<string>> v1, vector<vector<string>> v2);
void readGameMap();
void loadMap();
void autoSave();
void autoSyncMap();
void wLastGameTime();
void rLastGameTime();

// ----------------------- Game Log Display / Save --------------------------

void logPush(string log);
void logPrint(string log);

// ------------------------ Main() -----------------------

int main();

// ----------------------------------------------------------------------


// ---------------------------- Initialize global variable data -------------------------------- //

int row = 5, column = 9, numZombie = 1, playerX = 0, playerY = 0;
int screenWidth;
int screenHeight;
int startGame, endGame;
string startTime;
vector<string> gameLog_list;
vector<vector<string>> gameMap;
// {
//     {"+","-","+","-","+","-","+","-","+","-","+","-","+","-","+","-","+"},
//     {"|"," ","|"," ","|"," ","|"," ","|"," ","|"," ","|"," ","|"," ","|"},
//     {"+","-","+","-","+","-","+","-","+","-","+","-","+","-","+","-","+"},
// };
vector<vector<string>> characterDetails;
//  = {
//     {"-> ","Alien   :", "100", "0"},
//     {"   ", "250", "5", "1"},
//     {"   ", "50","15","3" },
// };
vector<vector<int>> emptySpacePosList;
vector<string> gameTimeList;



// ------------------------------------ Push game log into a vector ----------------------------------- 
void logPush(string log)
{
    while(log.length()!= 57)
    {
        log += " ";
    }
    if(gameLog_list.size() == 8)
    {
        gameLog_list.erase(gameLog_list.begin());
    }
    gameLog_list.push_back(log);

    for(int i = 0; i < gameLog_list.size(); i++)
    {
        gameMap[i+1][gameMap[i+1].size()-1] = gameLog_list[i];
    }
}

void logPrint(string log)
{
    setColor(C_WHITE,C_DARK_RED);
    cout << "\033[1m" << log << "\033[0m" << endl;
    setColor(C_DEFAULT, C_DEFAULT);
}

// -------------------------------------- Clear All Data In The Vector -----------------------------
void clearVector()
{
    gameLog_list.clear();
    gameMap.clear();
    characterDetails.clear();
    emptySpacePosList.clear();
}


// ---------------------------------- Get Data By Code Automatically -------------------------------------//

string getTimeNow()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string hour = to_string(ltm->tm_hour);
    string min = to_string(ltm->tm_min);
    string sec = to_string(ltm->tm_sec);

    if(ltm->tm_sec < 10)
    {
        sec = "0" + to_string(ltm->tm_sec);
    }
    if(ltm->tm_min < 10)
    {
        min = "0" + to_string(ltm->tm_min);
    }
    if(ltm->tm_hour < 10)
    {
        hour = "0" + to_string(ltm->tm_hour);
    }

    return "[" + hour + ":" + min +":" + sec + "] ";
}


int getPlayerPosX(vector<vector<string>> playerPos)
{
    for(int i = 0; i < playerPos.size(); i++)
    {
        for(int j = 0; j < playerPos[i].size(); j++)
        {
            if(playerPos[i][j] == "A")
            {
                return i;
                break;
            }
        }
    }
}

int getPlayerPosY(vector<vector<string>> playerPos)
{
    for(int i = 0; i < playerPos.size(); i++)
    {
        for(int j = 0; j < playerPos[i].size(); j++)
        {
            if(playerPos[i][j] == "A")
            {
                return j;
                break;
            }
        }
    }
}

void getAlienPos()
{
    playerX = getPlayerPosX(gameMap);
    playerY = getPlayerPosY(gameMap);
}

bool isWall(int posX, int posY)
{
    int deleteNum;
    if(gameMap[0].size() >= 24)
    {
        deleteNum = 4;
    }
    else
    {
        deleteNum = 3;
    }
    return posX < 1 || posX > gameMap.size() - deleteNum || posY < 2 || posY > gameMap[0].size()-4;
}

bool isZombie(vector<vector<string>> v, int mX, int mY)
{
    vector<string> empty_zombie;
    for(int i = 1; i < characterDetails.size(); i++)
    {
        empty_zombie.push_back(to_string(i));
    }
    for(int i = 0;i < empty_zombie.size(); i++)
    {
        if(gameMap[mX][mY] == empty_zombie[i])
        {
            return true;
        }
    }
    
}

bool checkAllZomDead()
{
    int countDie = 1;

    for(int i = 1; i < characterDetails.size(); i++)
    {
        if(stoi(characterDetails[i][1]) == 0)
        {
            countDie += 1;
        }
    }

    if(countDie == characterDetails.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isObj(string n)
{
    if(n == "p" || n == "A" || n == "h" || n == "r" || n == "B" || n == "^" || n == "v" || n == "<" || n == ">" || n == " "|| n == "." || n == "1" || n == "2" || n == "3" || n == "4" || n == "5" || n == "6" || n == "7" || n == "8" || n == "9")
    {
        return true;
    }
}

void printMapDetails()
{
    int arrow = 0;
    int zombie = 0;
    int rock = 0;
    int hPack = 0;
    int pod = 0;
    int bomb = 0;
    for(int i = 0; i < gameMap.size(); i++)
    {
        for(int j = 0; j < gameMap[i].size(); j++)
        {
            if(gameMap[i][j] == "^" || gameMap[i][j] == "v" || gameMap[i][j] == "<" || gameMap[i][j] == ">")
            {
                arrow += 1;
            }
            else if(gameMap[i][j] == "r")
            {
                rock += 1;
            }
            else if(gameMap[i][j] == "h")
            {
                hPack += 1;
            }
            else if(gameMap[i][j] == "B")
            {
                bomb += 1;
            }
            else if(gameMap[i][j] == "p")
            {
                pod += 1;
            }
        }
    }
    for(int i = 1; i < characterDetails.size(); i++)
    {
        if(stoi(characterDetails[i][1]) > 0)
        {
            zombie += 1;
        }
    }

    cout << "\nQuantity [ ";
    setColor(C_WHITE, C_DARK_RED); cout << "Zombie"; setColor(C_DEFAULT,C_DEFAULT);
    cout << ": " << setw(2) << zombie;
    cout << " | ";
    setColor(C_YELLOW, C_DEFAULT); cout << "Arrow"; setColor(C_DEFAULT,C_DEFAULT);
    cout << ": " << setw(2) << arrow;
    cout << " | ";
    setColor(C_BLACK, C_GRAY); cout << "Rock"; setColor(C_DEFAULT,C_DEFAULT);
    cout << ": " << setw(2) << rock;
    cout << " | ";
    setColor(C_BLACK, C_GREEN); cout << "Health Pack"; setColor(C_DEFAULT,C_DEFAULT);
    cout << ": " << setw(2) << hPack;
    cout << " | ";
    setColor(C_WHITE, C_DARK_PINK); cout << "Pod"; setColor(C_DEFAULT,C_DEFAULT);
    cout << ": " << setw(2) << pod;
    cout << " | ";
    setColor(C_BLACK,C_RED); cout << "Bomb"; setColor(C_DEFAULT,C_DEFAULT);
    cout << ": " << setw(2) << bomb;
    cout << " ]" << endl;
    

}




// --------------------------- Check the turn of the player or zombie & print it out --------------------------------//

void checkPCTurn()
{
    int currentPos;

    for(int i = 0; i < characterDetails.size(); i++)
    {
        if(characterDetails[i][0] == "-> ")
        {
            currentPos = i;
            break;
        }
    }

    if(currentPos == characterDetails.size() - 1)
    {
        currentPos = 0;
        characterDetails[characterDetails.size()-1][0] = "   ";
        characterDetails[currentPos][0] = "-> ";
    }
    else
    {
        characterDetails[currentPos][0] = "   ";
        currentPos += 1;
        characterDetails[currentPos][0] = "-> ";
    }
    
    // sPause(); 
}

void turnGuide()
{
    cout << endl;
    if(characterDetails[0][0]=="-> ")
    {
        setColor(C_BLACK,C_DARK_YELLOW);
    }
    else
    {
        setColor(C_DEFAULT,C_DEFAULT);
    }
    cout << characterDetails[0][0] << characterDetails[0][1] 
    << " Life " << setw(3) << characterDetails[0][2] << ", "
    << "Attack " << setw(3) << characterDetails[0][3] 
    << "             Position: [ ROW: " 
    << setw(3) << (getPlayerPosX(gameMap) + 1) / 2 << "   | COLUMN: " << setw(3) << (getPlayerPosY(gameMap)+1)/ 2 << "   ]  "  << endl;
    setColor(C_DEFAULT,C_DEFAULT);

    for(int i = 1;i <= characterDetails.size() - 1; i++)
    {
        
        for(int j = 0; j < (characterDetails[i].size() / 4); j++)
        {
            if(stoi(characterDetails[i][j+1]) == 0)
            {
                cout << characterDetails[i][j] << "Zombie " << (i) << ": " << "Life " << setw(3) << characterDetails[i][j+1] 
                << ", " << "Attack " << setw(3) <<characterDetails[i][j+2] << ", " 
                << "Range " << setw(3) << characterDetails[i][j+3] 
                << " [ X DEAD X ]  " << endl;
            }
            else
            {
                if(characterDetails[i][0]=="-> ")
                {
                    setColor(C_BLACK,C_DARK_YELLOW);
                }
                cout << characterDetails[i][j] << "Zombie " << (i) << ": " << "Life " << setw(3) << characterDetails[i][j+1] 
                << ", " << "Attack " << setw(3) <<characterDetails[i][j+2] << ", " 
                << "Range " << setw(3) << characterDetails[i][j+3] 
                << ", Position: [ ROW: " << setw(3) << (stoi(characterDetails[i][j+4]) + 1) / 2 << "   | COLUMN: " << setw(3) << (stoi(characterDetails[i][j+5]) + 1) / 2 << "   ]  "  << endl;
            }
            
        }
        setColor(C_DEFAULT,C_DEFAULT);
    }
    cout << endl;
}

// ------------------------------ Print all interface of map and clear the dot on the trail ----------------------------- //

void clearTrail()
{
    printAll();
    cout << "Action Log: Alien's turn ends. The trial is reset." << endl << endl;
    for(int i = 0; i < gameMap.size()-1; i++)
    {
        for(int j = 0; j < gameMap[i].size()-1; j++)
        {
            if(gameMap[i][j] == ".")
            {
                gameMap[i][j] = randomlyNewObject();
            }
        }
    }
}

void printMap()
{
    maximizeWindow();
    initColorTerminal(screenWidth,screenHeight);
    xScreen();


    showCursor(false);

    cout << endl;

    for(int i = 0; i < gameMap.size(); i++)
    {
        for(int j = 0; j < gameMap[i].size(); j++)
        {
            if(gameMap[i][j] == "A")
            {
                setColor(C_WHITE, C_DARK_BLUE);
            }
            else if(gameMap[i][j] == "h")
            {
                setColor(C_BLACK, C_GREEN);
            }
            else if(gameMap[i][j] == "p")
            {
                setColor(C_WHITE, C_DARK_PINK);
            }
            else if(gameMap[i][j] == "^" || gameMap[i][j] == "v" || gameMap[i][j] == "<" || gameMap[i][j] == ">")
            {
                setColor(C_YELLOW, C_DEFAULT);
            }
            else if(gameMap[i][j] == "1" || gameMap[i][j] == "2" || gameMap[i][j] == "3" || gameMap[i][j] == "4" || gameMap[i][j] == "5" || gameMap[i][j] == "6" || gameMap[i][j] == "7" || gameMap[i][j] == "8" || gameMap[i][j] == "9")
            {
                if(i >= gameMap.size()-2)
                {
                    setColor(C_DEFAULT,C_DEFAULT);
                }
                else
                {   
                    setColor(C_WHITE, C_DARK_RED);
                }
                
            }
            else if(gameMap[i][j] == "r")
            {
                setColor(C_BLACK, C_GRAY);
            }
            else if(gameMap[i][j] == "B")
            {
                setColor(C_BLACK,C_RED);
            }
            else if(gameMap[i][j] == ".")
            {
                setColor(C_CYAN, C_DEFAULT);
            }
            else if(gameMap[i][j] == "+--" || gameMap[i][j] == "-" || gameMap[i][j] == "+" || gameMap[i][j] == "|" || gameMap[i][j] == "| ")
            {
                setColor(C_BLUE,C_DEFAULT);
            }

            if(i <= 8 && (j == gameMap[i].size()-2 || j == gameMap[i].size()-1))
            {
                setColor(C_GREEN,C_BLACK);
            }

            if(i <= 8 && (j == gameMap[i].size()-1 || j == gameMap[i].size()-1))
            {
                setColor(C_CYAN,C_DEFAULT);
            }


            if(isObj(gameMap[i][j]))
            {
                if(i > gameMap.size() - 2) // Maintain same color
                {
                    cout << gameMap[i][j];
                }
                else // To make sure those game object only color with one character only / print one more blank place to the map
                {
                    cout << gameMap[i][j];
                    setColor(C_DEFAULT,C_DEFAULT);
                    cout << " ";
                }
                
            }
            else
            {
                cout << gameMap[i][j]; // print out those wall 
            }
            
            setColor(C_DEFAULT,C_DEFAULT); // set default color to those index number
        }
        cout << endl;
    }

    for(int y = 0; y < screenHeight - gameMap.size(); y++)
    {
        clearLine(gameMap.size()+y+3);
    }
    
    setCursor(0, gameMap.size()+3);
    showCursor(true);



    // // check index
    // for(int i = 0; i < gameMap.size(); i++)
    // {
    //     for(int j = 0; j < gameMap[i].size(); j++)
    //     {
    //         cout << gameMap[i][j] << "(" << i << ", " << j <<")" << ", ";
    //     }
    //     cout << endl;
    // }
    // system("PAUSE");
}

void printGoodbye()
{
    cout <<"\n\n";
    cout << R"(
                          ___     ___     ___     ___     ___   __   __   ___            
                  / __|   / _ \   / _ \   |   \   | _ )  \ \ / /  | __|     o O O 
                 | (_ |  | (_) | | (_) |  | |) |  | _ \   \ V /   | _|     o      
                  \___|   \___/   \___/   |___/   |___/   _|_|_   |___|   TS__[O] 
            _|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_| """ |_|"""""| {======| 
            "`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'./o--000' 
    )" << '\n';
    PlaySound(TEXT("./music/intro.wav"), NULL, SND_LOOP | SND_ASYNC);
    auto now = chrono::system_clock::now();
    time_t time_now = chrono::system_clock::to_time_t(now);
    string str_time = ctime(&time_now);
    cout << "Last Game ended: " << str_time << endl;
    sPause();
}

void printHelp()
{
    xScreenAll();
    printMap();
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << R"(
                                                    __  _____________    __  ______   _  ____  _____   __ 
                                                   / / / / __/ __/ _ \  /  |/  / _ | / |/ / / / / _ | / / 
                                                  / /_/ /\ \/ _// , _/ / /|_/ / __ |/    / /_/ / __ |/ /__
                                                  \____/___/___/_/|_| /_/  /_/_/ |_/_/|_/\____/_/ |_/____/

    )" << endl;

    cout << "+---------------+----------------------------------------------------------------------+---------------------------------------------------------------+" << endl;
    cout << "|  Game Object  |                                  Introduce                           |                              Guidance                         |" << endl;
    cout << "+---------------+----------------------------------------------------------------------+---------------------------------------------------------------+" << endl;                                                                      //|
    cout << "|       ";setColor(C_WHITE, C_DARK_BLUE);cout << "A";setColor(C_DEFAULT,C_DEFAULT);cout << "       |  Alien With Initialization 100 Life & 0 Attack.                      | 1. Press [WASD] On Keyboard To Control The Movement Of Alien. |" << endl;
    cout << "+---------------+----------------------------------------------------------------------+---------------------------------------------------------------+" << endl;
    cout << "|       ";setColor(C_BLACK, C_GREEN);cout << "h";setColor(C_DEFAULT,C_DEFAULT);cout << "       |  Health Pack. Help Alien +20 Life.                                   | 2. Press [p] On Keyboard To Change Direction Of Arrow Power.  |" << endl;
    cout << "+---------------+----------------------------------------------------------------------+---------------------------------------------------------------+" << endl;
    cout << "|       ";setColor(C_WHITE, C_DARK_PINK);cout << "p";setColor(C_DEFAULT,C_DEFAULT);cout << "       |  Pod Attack. Attack The Nearest Zombie With 10 Damage.               | 3. Press [F1] On Keyboard To Open The User Help Manual.       |" << endl;
    cout << "+---------------+----------------------------------------------------------------------+---------------------------------------------------------------+" << endl;
    cout << "|       ";setColor(C_BLACK,C_RED);cout << "B";setColor(C_DEFAULT,C_DEFAULT);cout << "       |  Bomb Attack. Zombies / Alien Step On it -20 Life.                   | 4. Press [F2] To Save Your Current Progress Of Your Game.     |" << endl;
    cout << "+---------------+----------------------------------------------------------------------+---------------------------------------------------------------+" << endl; 
    cout << "|       ";setColor(C_BLACK, C_GRAY);cout << "r";setColor(C_DEFAULT,C_DEFAULT);cout << "       |  Rock. Any Power Object / Empty Space Will Beneath Under It.         | 5. Press [F3] To Load Your Saved Game Progress.               |" << endl;
    cout << "+---------------+----------------------------------------------------------------------+---------------------------------------------------------------+" << endl;
    cout << "|     ";setColor(C_YELLOW, C_DEFAULT);cout << "^v<>";setColor(C_DEFAULT,C_DEFAULT);cout << "      |  Arrow Power. Change Direction Of Alien Movement & Alien +20 Attack. | 6. Press [F4] To Refresh Your Screen If Any Display Problem.  |" << endl;
    cout << "+---------------+----------------------------------------------------------------------+---------------------------------------------------------------+" << endl;
    cout << "|     ";setColor(C_WHITE, C_DARK_RED);cout << "1";setColor(C_DEFAULT,C_DEFAULT);cout << " - ";setColor(C_WHITE, C_DARK_RED);cout << "9";setColor(C_DEFAULT,C_DEFAULT);cout << "     |  Zombies [1-9] With Initialization Random Life And Attack            | 7. Press [F5] To Restart With Same Setting Of Current Game.   |" << endl;
    cout << "+---------------+----------------------------------------------------------------------+---------------------------------------------------------------+" << endl;
    

    sPause();
    xScreenAll();
}

void printAll()   
{
    showCursor(false);
    xScreen();
    printMapDetails();
    printMap();
    turnGuide();
    showCursor(true);
}

void printDefaultSetting()
{
    string selection;
    xScreenAll();
    clearVector();
    PlaySound(TEXT("./music/intro.wav"), NULL, SND_LOOP | SND_ASYNC);
    cout << R"(      
                                                                             _,-""-._                         
                            o                                              ,"        ".   
                             \_/\o                                         /    ,-,  ,"\      
                            ( Oo)                    \|/                  "    /   \ | o|   
                            (_=-)  .===O-  ~~Z~A~P~~ -O-                    \    `-o-"  `-',     
                            /   \_/U'                /|\                     `,   _.--'`'--`        
                            ||  |_/                                           `--`---'                    |   _)         
                            \\  |                                              ,' '      _  /  _ \  ` \   _ \ |  -_)        
                            {K ||                                            ./ ,  `,    ___|\___/_|_|_|_.__/_|\___|   
                             | PP                                             / /     \                  
                             | ||                                           (_)))_ _,"
                             (__\\                                              _))))_,
+------------------------------------------------------------------------------(_,-._)))-----------------+
|                       (     (            )            (          )    )     *           (              |           
|             (      )\ )  )\ )      ( /(            )\ )    ( /( ( /(   (  `      (   )\ )              |   
|             )\    (()/( (()/( (    )\())   (   (  (()/(    )\()))\())  )\))(   ( )\ (()/( (            |                                                        
|          ((((_)(   /(_)) /(_)))\  ((_)\    )\  )\  /(_))  ((_)\((_)\  ((_)()\  )((_) /(_)))\           |               
|           )\ _ )\ (_))  (_)) ((_)  _((_)  ((_)((_)(_))     _((_) ((_) (_()((_)((_)_ (_)) ((_)          |                                                      
|           (_)_\(_)| |   |_ _|| __|| \| |  \ \ / / / __|   |_  / / _ \ |  \/  | | _ )|_ _|| __|         |           
|            / _ \  | |__  | | | _| | .` |   \ V /_ \__ \    / / | (_) || |\/| | | _ \ | | | _|          |                                                           
|           /_/ \_\ |____||___||___||_|\_|    \_/(_)|___/   /___| \___/ |_|  |_| |___/|___||___          |                                                           
)";           
    cout << "+========================================================================================================+" << endl << endl;
    cout << "                                      " << "+------------------------------+" << endl;
    cout << "                                      " << "|     Default Game Settings    |" << endl;
    cout << "                                      " << "+------------------------------+" << endl;
    cout << "                                      " << "|      Board Rows    : 5       |" << endl;
    cout << "                                      " << "+------------------------------+" << endl;
    cout << "                                      " << "|      Board Columns : 9       |" << endl;
    cout << "                                      " << "+------------------------------+" << endl;
    cout << "                                      " << "|      Zombie Count  : 1       |" << endl;
    cout << "                                      " << "+------------------------------+" << endl << endl;


    ifstream file("./autosave/lastgame.txt");
    file.seekg(0,ios::end);
    if(file.tellg() != 0)
    {
        rLastGameTime();
        if(gameTimeList.size() == 0) // if last game data not set probably
        {
            gameTimeList.push_back("NULL");
            gameTimeList.push_back("NULL");
        }
        else if(gameTimeList.size() == 1)
        {
            gameTimeList.push_back("NULL");
        }
        string selection;
        file.close();
        cout << "+-----------------+" << endl;
        cout << "|    AUTO SYNC    |" << endl;
        cout << "+-----------------+" << endl;
        
        cout << "Last Game Time      : "  << gameTimeList[0] << endl;
        cout << "Last Online Duration: " << gameTimeList[1] << endl << endl;
        cout << "Do you want to sync last game stopped.(y/n): ";
        getline(cin >> ws, selection);
        while(selection != "y" && selection != "n")
        {
            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
            cout << "+-----------+-----------------------------+" << endl;
            cout << "|ATTENTION: | Only Accept Charcater (y/n) |" << endl;
            cout << "+-----------+-----------------------------+" << endl << endl;
            cout << "Do you want to sync last game stopped.(y/n): ";
            getline(cin >> ws, selection);
        }
        if(selection == "y")
        {
            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
            xScreenAll();
            autoSyncMap();
            for(int i = 1;i <= 8; i++) // push in last game latest game log history
            {
                gameLog_list.push_back(gameMap[i][gameMap[i].size()-1]);
            } 
            printAll();
            userCommand();
        }
        else
        {
            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
        }
    }
    
    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n\nDo you wish to change the game settings (y/n)? => ";
    getline(cin >> ws, selection);
    while (selection != "y" && selection != "n")
    {
        PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
        cout << "+-----------+-----------------------------+" << endl;
        cout << "|ATTENTION: | Only Accept Charcater (y/n) |" << endl;
        cout << "+-----------+-----------------------------+" << endl << endl;
        cout << "Do you wish to change the game settings (y/n)? => ";
        getline(cin >> ws, selection);
    }

    PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);

    xScreenAll();

    cout << "\t\t\t+-------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t|                              GAME RULE AND GUIDANCE FOR GAME [ ALIEN VS ZOMBIE ]                            |" << endl;
    cout << "\t\t\t+-------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t|  1. ***Please MAXIMIZE Your Windows Of Your Running Console Now To Ensure The Best GAME Experience.         |" << endl;
    cout << "\t\t\t+-------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t|  2. Your Windows Of Your Running Console Will Automatically FORCE To Be Maximize.                           |" << endl;
    cout << "\t\t\t+-------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t|  3. Player Need To Input The Number Of Zombie Not Exceeding 9 Zombies.                                      |" << endl;
    cout << "\t\t\t+-------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t|  4. The Minimum Of The Column Must Be >= 5 And The Row Also Must >= 5.                                      |" << endl;
    cout << "\t\t\t+-------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t|  5. The Maximum Of The Column And The Row For The Game Map Is Due To The Limit Of Windows Display Size.     |" << endl;
    cout << "\t\t\t+-------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t|  6. Player Need To Input The Number Of Column And Row In The Following Settings. [ONLY ODD NUMBER ACCEPTED] |" << endl;
    cout << "\t\t\t+-------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "\t\t\t|  7. Player Can press [F1] Key On Keyboard During The Game Execute For More Information.                     |" << endl;
    cout << "\t\t\t+-------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "\n\n\n";

    sPause();
    maximizeWindow();
    initColorTerminal(screenWidth,screenHeight);
    cout <<"\n\n";
    
    if(selection == "y")
    {
        maximizeWindow();

        cout << "Zombie Settings" << endl;
        cout << "------------------" << endl;
        cout << "Enter number of zombies => ";
        cin >> numZombie;
        while(numZombie > 9 || cin.fail())
        {
            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
            cin.clear();
            cin.ignore(256, '\n');
            cout << "\n+-----------+----------------------------------------------+" << endl;
            cout << "|ATTENTION: | The number of zombies cannot greater than 9. |" << endl;
            cout << "+-----------+----------------------------------------------+" << endl << endl;
            cout << "Enter number of zombies => ";
            cin >> numZombie;
        }

        PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);

        cout << "\n\n\n";

        int maxRow = (screenHeight - numZombie - 10) / 2;
        if(maxRow % 2 == 0)
        {
            maxRow = maxRow - 1;
        }
        int maxCol = (screenWidth - 10) / 6;
        if(maxCol % 2 == 0)
        {
            maxCol = maxCol - 1;
        }
        cout << "+-------------------------------+" << endl;
        cout << "|        Board Settings         |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << "| MAX ROW   : " << setw(2) << maxRow -2 << "                |"<< endl;
        cout << "| MAX Column: " << setw(2) << maxCol -10 << "                |" << endl;
        cout << "+-------------------------------+" << endl;
        cout << "Enter rows => ";
        cin >> row;
        while(row % 2 == 0 || cin.fail() || row == 1 || row > maxRow -2 || row < 5)
        {
            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
            cin.clear();
            cin.ignore(256, '\n');
            cout << "\n+----------+-----------------------------------------------------------------------------------------------------------+" << endl;
            cout << "|ATTENTION:| This input of rows only accepted odd number and maximum map display due to width of your windows display  |" << endl;
            cout << "+----------+-----------------------------------------------------------------------------------------------------------+" << endl << endl;
            cout << "Enter rows => ";
            cin >> row;
        }
        cout << endl;
        PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
        cout << "Enter columns => ";
        cin >> column;

        while(column % 2 == 0 || cin.fail() || column == 1 || column > maxCol -10 || column < 5)
        {
            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
            cin.clear();
            cin.ignore(256, '\n');
            cout << "\n+-----------+--------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "|ATTENTION: | This input of columns only accepted odd number and maximum map display due to length of your windows display |" << endl;
            cout << "+-----------+--------------------------------------------------------------------------------------------------------------+" << endl << endl;
            cout << "Enter Columns => ";
            cin >> column;
        }
        
        cout << endl << endl;


        PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);

        // if((row * column) < numZombie + 1)
        // {
        //     cout << "\n+-----------+--------------------------------------------------------------------------------+" << endl;
        //     cout << "|ATTENTION: | The game map size and number of zombies does not match. Back To Main Menu..... |" << endl;
        //     cout << "+-----------+--------------------------------------------------------------------------------+" << endl << endl;
        //     sPause();
        //     printDefaultSetting();
        // }
        cout << "+-------------------+" << endl;
        cout << "| Settings updated. |" << endl;
        cout << "+-------------------+" << endl;
        sPause();
    }
    else if(selection == "n")
    {
        row = 5;
        column = 9;
        numZombie = 1;
        cout << "\n+---------------------------+" << endl;
        cout << "| Default Setting Remained. |" << endl;
        cout << "+---------------------------+" << endl;
        sPause();
    }
}

// --------------------------------- Initialize The Details Of Game Map ----------------------------------------//

string randomlyNewObject()
{
    string randomObj = " ";

    int randomNum = rand() % 100;

    if(randomNum > 50)
    {
        randomNum = rand() % 100;
        if (randomNum < 10) randomObj = "h";
        else if (randomNum < 20) randomObj = "p";
        else if (randomNum < 30) randomObj = "r";
        else if (randomNum < 35) randomObj = "B";
        else if (randomNum < 50) randomObj = "<";
        else if (randomNum < 60) randomObj = ">";
        else if (randomNum < 80) randomObj = "v";
        else randomObj = "^";
    }

    return randomObj;
}



void initMap()
{
    // cout << row << column;
    // row = 3, column = 4
    vector<string> empty_vec = {};
    xScreen();
    
    for(int i = 0; i < (row * 2) + 1; i++)
    {
        gameMap.push_back(empty_vec);
        if(i % 2 != 0)
        {
            if((i / 2) + 1 >= 10)
            {
                gameMap[i].push_back(to_string((i /2 )+1)+ " ");
            }
            else
            {   
                gameMap[i].push_back(to_string((i /2 )+1) + "  ");
            }

            for(int j = 0; j < column; j++)
            {
                gameMap[i].push_back("| ");
                gameMap[i].push_back(" ");

                if(j == (column - 1))
                {
                    gameMap[i].push_back("|");
                }
            }
            
        }
        else
        {
            gameMap[i].push_back("   ");
            for(int j = 0; j < column; j++)
            {
                gameMap[i].push_back("+--");
                gameMap[i].push_back("-");

                if(j == (column - 1))
                {
                    gameMap[i].push_back("+");
                }
            }
        }
    }
    
    if(column >= 10)
    {
        gameMap.push_back(empty_vec);
        gameMap[gameMap.size()-1].push_back("   ");
        for(int i = 0; i < (9 * 2); i++)
        {
            gameMap[gameMap.size()-1].push_back(" ");
        }

        int remain_num = column / 10; // 13 / 10 = 1
        int remainder = column % 10;  // 13 % 10 = 3
        for(int i = 0; i < remain_num; i++)
        {
            
            if(i == remain_num - 1)
            {
                for(int j = 0; j < remainder + 1; j++)
                {
                    gameMap[gameMap.size()-1].push_back(" ");
                    gameMap[gameMap.size()-1].push_back(to_string(i+1));
                }
            }
            else if(remain_num > 1 || (i != remain_num - 1))
            {
                for(int j = 0; j <= 9; j++)
                {
                    gameMap[gameMap.size()-1].push_back(" ");
                    gameMap[gameMap.size()-1].push_back(to_string(i+1));
                }
            }
            else
            {
                for(int j = 0; j < remainder + 1; j++)
                {
                    gameMap[gameMap.size()-1].push_back(" ");
                    gameMap[gameMap.size()-1].push_back(to_string(i+1));
                }
            }
            
            
        }
        gameMap.push_back(empty_vec);
        gameMap[gameMap.size()-1].push_back("  ");
        for(int i = 0; i < 9; i++)
        {
            gameMap[gameMap.size() - 1].push_back("   ");
            gameMap[gameMap.size()-1].push_back(to_string(i+1));
        }
        for(int i = 0; i < remain_num; i++)
        {
            if(i == remain_num - 1)
            {
                for(int j = 0; j < remainder + 1; j++)
                {
                    gameMap[gameMap.size()-1].push_back("   ");
                    gameMap[gameMap.size()-1].push_back(to_string(j));
                }
            }
            else if(remain_num > 1 || (i != remain_num - 1))
            {
                for(int j = 0; j <= 9; j++)
                {
                    gameMap[gameMap.size()-1].push_back("   ");
                    gameMap[gameMap.size()-1].push_back(to_string(j));
                }
            }
            else
            {
                for(int j = 0; j < remainder + 1; j++)
                {
                    gameMap[gameMap.size()-1].push_back("   ");
                    gameMap[gameMap.size()-1].push_back(to_string(j));
                }
            }
            
        }
    }
    else
    {
        gameMap.push_back(empty_vec);
        gameMap[gameMap.size()-1].push_back("  ");
        for(int i = 0;i < column; i++)
        {
            gameMap[gameMap.size()-1].push_back("   ");
            gameMap[gameMap.size()-1].push_back(to_string(i+1));
        }
    }
    // gameMap.push_back(empty_vec);
    // for(int i = 0; i < column; i++)
    // {
    //     gameMap[gameMap.size()-1].push_back(to_string(i));
    // }


    int alien_posX, alien_posY;
    alien_posX = (((row + 1) * 2) / 2) - 1;
    alien_posY = (((column + 1) * 2) / 2) - 1; 


    // cout << alien_posX << " " << alien_posY << endl;
    characterDetails.push_back(empty_vec);
    characterDetails[0].push_back("-> ");
    characterDetails[0].push_back("Alien   :");
    characterDetails[0].push_back("100");
    characterDetails[0].push_back("0");

    srand(time(0));
    
    for(int i = 1;i <= numZombie; i++)
    {
        characterDetails.push_back(empty_vec);
        int randomLife, randomAttack;
        do
        {  
            randomLife = (rand() % 200 + 1);
        } while(randomLife < 90 || randomLife % 10 != 0);

        do
        {  
            randomAttack = (rand() % 35 + 1);
        } while(randomAttack % 5 != 0);

        int randomRange = rand() % 5 + 1;
        
        characterDetails[i].push_back("   ");
        characterDetails[i].push_back(to_string(randomLife));
        characterDetails[i].push_back(to_string(randomAttack));
        characterDetails[i].push_back(to_string(randomRange));

    }
    
    gameMap[alien_posX][alien_posY + 1] = "A";


    // Place zombie in random blank place

    vector<int> emptySpaceVec = {};

    for(int i = 0; i < gameMap.size() - 2; i++)
    {
        for(int j = 0;j < gameMap[i].size(); j++)
        {
            if(gameMap[i][j] == " ")
            {
                emptySpacePosList.push_back(emptySpaceVec);
                emptySpacePosList[emptySpacePosList.size()-1].push_back(i);
                emptySpacePosList[emptySpacePosList.size()-1].push_back(j);
                // cout << "i: " << i << ", "  << "j: " << j << endl;
                // // gameMap[i][j] = randomlyNewObject();
            }
        }
    }

    int randNumZ, zombieX, zombieY;

    for(int i = 0; i < numZombie; i++)
    {
        randNumZ = rand() % (emptySpacePosList.size() - 1);
        zombieX = emptySpacePosList[randNumZ][0];
        zombieY = emptySpacePosList[randNumZ][1];
        while(gameMap[zombieX][zombieY] != " ")
        {
            randNumZ = rand() % (emptySpacePosList.size() - 1);
            zombieX = emptySpacePosList[randNumZ][0];
            zombieY = emptySpacePosList[randNumZ][1];
        }
        gameMap[zombieX][zombieY] = to_string(i+1);
        characterDetails[i+1].push_back(to_string(zombieX)); 
        characterDetails[i+1].push_back(to_string(zombieY)); 
    }

    // Place random objects

    srand(time(0));
    for(int i = 0; i < gameMap.size() - 2; i++)
    {
        for(int j = 0;j < gameMap[i].size(); j++)
        {
            if(gameMap[i][j] == " ")
            {
                gameMap[i][j] = randomlyNewObject();
            }
        }
    }
    

    //push game control guidance into gamemap vector
    gameMap[0].push_back("         ?** Game Control **?         ");
    gameMap[1].push_back("  => [WASD]  - Move Alien             ");
    gameMap[2].push_back("  => [P]     - Change Arrow Direction ");
    gameMap[3].push_back("  => [F1]    - HELP                   ");
    gameMap[4].push_back("  => [F2]    - SAVE                   ");
    gameMap[5].push_back("  => [F3]    - LOAD                   ");
    gameMap[6].push_back("  => [F4]    - REFRESH SCREEN         ");
    gameMap[7].push_back("  => [F5]    - RESTART                ");
    gameMap[8].push_back("  => [F6]    - EXIT                   ");
    
    
    //push game log into gamemap vector
    gameMap[0].push_back("         < GAME LOG HISTORY >       ");
    gameMap[1].push_back("              N/A");
    gameMap[2].push_back("              N/A");
    gameMap[3].push_back("              N/A");
    gameMap[4].push_back("              N/A");
    gameMap[5].push_back("              N/A");
    gameMap[6].push_back("              N/A");
    gameMap[7].push_back("              N/A");
    gameMap[8].push_back("              N/A");
}



//---------------------------- Movement Of The Alien ( UP / DOWN / LEFT / RIGHT ) -----------------------------------

void moveAlien(int mX, int mY)
{
    vector<string> tempZombie;
    string randomObj, gameLog;
    int currentX, currentY;
    int alienAttack = stoi(characterDetails[0][3]);
    getAlienPos();

    xScreen();
    printAll();

    currentX = playerX;
    currentY = playerY;
    
    playerX = currentX + mX;
    playerY = currentY + mY;


    if(checkAllZomDead())
    {
        winGame();
    }

    // When alien meet a wall
    if(isWall(playerX, playerY))
    {
        PlaySound(TEXT("./music/wall.wav"), NULL, SND_ASYNC);
        this_thread::sleep_for(chrono::milliseconds(800));
        gameLog = "Alien hit a border.";
        logPrint("GAME LOG: " + gameLog);
        logPush(getTimeNow() + gameLog);
        PlaySound(TEXT("./music/zomCome.wav"), NULL, SND_ASYNC);
        sPause();
        return;
    }

    // When alien meet rock
    if(gameMap[playerX][playerY] == "r")
    {
        gameLog = "Alien stumbles upon a rock.";
        logPrint("GAME LOG: " + gameLog);
        logPush(getTimeNow() + gameLog);

        
        gameMap[playerX][playerY] = randomlyNewObject();
        if(gameMap[playerX][playerY] == " ")
        {
            randomObj = "nothing";
        }
        else if(gameMap[playerX][playerY] == "^" || gameMap[playerX][playerY] == "v" || gameMap[playerX][playerY] == "<" || gameMap[playerX][playerY] == ">")
        {
            PlaySound(TEXT("./music/good.wav"), NULL, SND_ASYNC);
            randomObj = "arrow";
        }
        else if(gameMap[playerX][playerY] == "p")
        {
            PlaySound(TEXT("./music/good.wav"), NULL, SND_ASYNC);
            randomObj = "pod";
        }
        else if(gameMap[playerX][playerY] == "h")
        {
            PlaySound(TEXT("./music/good.wav"), NULL, SND_ASYNC);
            randomObj = "health pack";
        }
        else if(gameMap[playerX][playerY] == "r")
        {
            randomObj = "2nd rock";
        }
        else if(gameMap[playerX][playerY] == "B")
        {
            randomObj = "bomb";
        }

        gameLog = "Discovers [ " + randomObj + " ] beneath the rock";
        logPush(getTimeNow() + gameLog);
        logPrint("GAME LOG: " + gameLog);

        PlaySound(TEXT("./music/rockS.wav"), NULL, SND_ASYNC);
        this_thread::sleep_for(chrono::milliseconds(800));

        
        PlaySound(TEXT("./music/zomCome.wav"), NULL, SND_ASYNC);
        sPause();
        
        return;
    }

    

    // if alien hit arrow / health pack / pod
    if(gameMap[playerX][playerY] == "^")
    {
        gameLog = "Alien find a up arrow. Attack +20.";
        PlaySound(TEXT("./music/arrowP.wav"), NULL, SND_ASYNC);
        mX = -2;
        mY = 0;
        alienAttack += 20;
        characterDetails[0][3] = to_string(alienAttack);
    }
    else if(gameMap[playerX][playerY] == "v")
    {
        gameLog = "Alien find a down arrow. Attack +20.";
        PlaySound(TEXT("./music/arrowP.wav"), NULL, SND_ASYNC);
        mX = 2;
        mY = 0;
        alienAttack += 20;
        characterDetails[0][3] = to_string(alienAttack);
    }
    else if(gameMap[playerX][playerY] == "<")
    {
        gameLog = "Alien find a left arrow. Attack +20.";
        PlaySound(TEXT("./music/arrowP.wav"), NULL, SND_ASYNC);
        mX = 0;
        mY = -2;
        alienAttack += 20;
        characterDetails[0][3] = to_string(alienAttack);
    }
    else if(gameMap[playerX][playerY] == ">")
    {
        gameLog = "Alien find a right arrow. Attack +20.";
        PlaySound(TEXT("./music/arrowP.wav"), NULL, SND_ASYNC);
        mX = 0;
        mY = 2;
        alienAttack += 20;
        characterDetails[0][3] = to_string(alienAttack);
    }
    else if(gameMap[playerX][playerY] == "h")
    {
        PlaySound(TEXT("./music/healthA.wav"), NULL, SND_ASYNC);
        gameLog = "Alien find a health pack. Life +20.";

        int health = stoi(characterDetails[0][2]);
        health += 20;
        if(health > 100)
        {
            characterDetails[0][2] = "100";
        }
        else
        {
            characterDetails[0][2] = to_string(health);
        }
    }
    else if(gameMap[playerX][playerY] == "p")
    {
        podAttack();
        gameLog = "Pod attack finish.";
        sPause();
    }
    else if(gameMap[playerX][playerY] == "B")
    {
        gameLog = "Alien step on a bomb and stun. Life -20.";
        PlaySound(TEXT("./music/bomb.wav"), NULL, SND_ASYNC);   
        int health = stoi(characterDetails[0][2]);
        health -= 20;
        if(health < 0)
        {
            characterDetails[0][2] = "0";
            gameLog = "Alien dead.";
            logPrint("GAME LOG: " + gameLog);
            logPush(getTimeNow() + gameLog);
            loseGame();
        }
        else
        {
            characterDetails[0][2] = to_string(health);
        }
        logPrint("GAME LOG: " + gameLog);
        logPush(getTimeNow() + gameLog);
        gameMap[currentX][currentY] = ".";
        gameMap[playerX][playerY] = "A";
        
        sPause();
        return;
    }
    else if(gameMap[playerX][playerY] == " ")
    {
        gameLog = "Alien find an empty space.";

        PlaySound(TEXT("./music/empty.wav"), NULL, SND_ASYNC);
    }
    else if(gameMap[playerX][playerY] == ".")
    {
        PlaySound(TEXT("./music/back.wav"), NULL, SND_ASYNC);
        gameLog = "Alien return back the same route.";
    }
    else
    {
        gameLog = "Alien meets zombie.";
    }

    logPrint("GAME LOG: " + gameLog);
    logPush(getTimeNow() + gameLog);
    this_thread::sleep_for(chrono::milliseconds(600));

    // if alien meet any zombies from "1" to "9"
    for(int i = 1; i < characterDetails.size(); i++)
    {
        tempZombie.push_back(to_string(i));
    }

    int zombieLife;

    for(int i = 0; i < tempZombie.size(); i++)
    {
        if(gameMap[playerX][playerY] == tempZombie[i])
        {
            zombieLife = stoi(characterDetails[i+1][1]);
            zombieLife -= alienAttack;
            PlaySound(TEXT("./music/zombieH.wav"), NULL, SND_ASYNC);
            if(alienAttack == 0)
            {
                gameLog = "Alien has no attack power. ";
            }
            else
            {
                gameLog = "Alien attacks Zombie " + to_string(i+1) + ". Zombie's life -" + to_string(alienAttack);
            }
            
            logPush(getTimeNow() + gameLog);
            logPrint("GAME LOG: " + gameLog);

            if(zombieLife <= 0) 
            {
                zombieLife = 0;
                gameLog = "Zombie " + to_string(i+1) + " is dead.";
                logPush(getTimeNow() + gameLog);
                logPrint("GAME LOG: " + gameLog);
            }

            alienAttack = 0;

            characterDetails[0][3] = to_string(alienAttack);
            characterDetails[i+1][1] = to_string(zombieLife);


            if(zombieLife > 0)
            {   
                gameLog = "Zombie " + to_string(i+1) + " is still alive.";
                logPush(getTimeNow() + gameLog);
                logPrint("GAME LOG: " + gameLog);
                sPause();
                return;
            }  
            sPause();
        }
    }

    gameMap[currentX][currentY] = ".";
    gameMap[playerX][playerY] = "A";


    printAll();
    this_thread::sleep_for(chrono::milliseconds(500));
    moveAlien(mX, mY);
    autoSave();
} 


// ------------------------Alien pick pod for distance attack --------------------------------

void podAttack()
{
    vector<vector<int>> c1;
    vector<int> alienPos;
    vector<int> zombieNum;
    vector<int> tempList;
    vector<float> shortestDis;
    float distance, temp, xDis, yDis;
    int countDie = 1;

    if(checkAllZomDead())
    {
        winGame();
    }

    for(int i = 1; i < characterDetails.size(); i++) // push all alive zombie into temp vector
    {
        tempList.clear();
        if(stoi(characterDetails[i][1]) > 0)
        {
            tempList.push_back(stoi(characterDetails[i][4]));
            tempList.push_back(stoi(characterDetails[i][5]));
            c1.push_back(tempList);
            zombieNum.push_back(i);
        }
    }

    alienPos.push_back(playerX);
    alienPos.push_back(playerY);

    // Using distance formula to find the distance between each zombie & alien & push into vector
    for(int i = 0; i < c1.size(); i++)  
    {
        xDis = alienPos[0] - c1[i][0];
        yDis = alienPos[1] - c1[i][1];
        distance = sqrt(pow(xDis,2) + pow(yDis,2));
        shortestDis.push_back(distance);
    }


    
    // find shortest distance in the vetor -> attack shortest distance zombie

    float nearest = *min_element(shortestDis.begin(), shortestDis.end());
    int nearestZombie = 1;

    for(int i = 0; i < shortestDis.size(); i++)
    {
        if(shortestDis[i] == nearest)
        {
            nearestZombie = zombieNum[i];
            break;
        }
    }

    // cout << alienPos[0] << " " << alienPos[1] << endl;

    // for(float i : shortestDis)
    // {
    //     cout << i << endl;
    // }

    // cout << "Nearest: " << nearest << " i: " << nearestZombie << endl;
    // sPause();

    characterDetails[nearestZombie][1] = to_string(stoi(characterDetails[nearestZombie][1]) - 10);

    PlaySound(TEXT("./music/pod.wav"), NULL, SND_ASYNC);

    string gameLog;

    gameLog = "Alien finds a pod. Zombie " + to_string(nearestZombie) + " life -10. ";
    logPrint("GAME LOG: " + gameLog);
    logPush(getTimeNow() + gameLog);
    if(stoi(characterDetails[nearestZombie][1]) > 0)
    {
        gameLog = "Zombie is still alive. [HP: "+ characterDetails[nearestZombie][1] +"]";
    }
    else
    {
        gameLog = "Zombie is dead.";
        gameMap[stoi(characterDetails[nearestZombie][4])][stoi(characterDetails[nearestZombie][5])] = " ";
    }
    logPrint("GAME LOG: " + gameLog);
    logPush(getTimeNow() + gameLog);

}

// ---------------------- Control Arrow Direction ----------------------

void controlArrow()
{
    int row, column, count = 0;
    string direction;


    do
    {
        if(count > 0)
        {
            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
            cout << "\n---------------------------------------------------------------------------------------------------------------" << endl;
            cout << "ERROR: The position of arrow that user input does not exist. Please reenter again." << endl << endl;
        }
        cout << "Enter row    : ";
        cin >> row;
        while(cin.fail())
        {
            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
            cin.clear();
            cin.ignore(256, '\n');
            cout << "+----------+--------------------------------------------------------+" << endl;
            cout << "|ATTENTION:| This input of rows only accepted valid number position |" << endl;
            cout << "+----------+--------------------------------------------------------+" << endl << endl;
            cout << "Enter row    : ";
            cin >> row;
        }

        PlaySound(TEXT("./music/success.wav"), NULL, SND_ASYNC);

        cout << "Enter column : ";
        cin >> column;
        while(cin.fail())
        {
            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
            cin.clear();
            cin.ignore(256, '\n');
            cout << "+----------+--------------------------------------------------------+" << endl;
            cout << "|ATTENTION:| This input of rows only accepted valid number position |" << endl;
            cout << "+----------+--------------------------------------------------------+" << endl << endl;
            cout << "Enter column : ";
            cin >> column;
        }

        PlaySound(TEXT("./music/success.wav"), NULL, SND_ASYNC);

        cout << "+--------------------------------------------------------------------------------------+" << endl;
        cout << "| Guidance: Use keyboard arrow key [^v<>] to change game arrow direction / [F9] for ESC|" << endl;
        cout << "+--------------------------------------------------------------------------------------+" << endl << endl;
        cout << "Direction    : ";

        int c, ex, loop = 1;

        while(loop == 1)
        {
            c = getch();

            if (c && c != 224)
            {
                PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
            }
            else
            {
                switch(ex = getch())
                {
                    case KEY_UP:
                        cout << endl << "Arrow Key Up Executed" << endl;//key up
                        direction = "up";
                        loop = 0;
                        break;
                    case KEY_DOWN:
                        cout << endl << "Arrow Key Down Executed" << endl;   // key down
                        direction = "down";
                        loop = 0;
                        break;
                    case KEY_LEFT:
                        cout << endl << "Arrow Key Left Executed" << endl;  // key left
                        direction = "left";
                        loop = 0;
                        break;
                    case KEY_RIGHT:
                        cout << endl << "Arrow Key Right Executed" << endl; 
                        direction = "right";
                        loop = 0;
                        break;
                    case KEY_F9:
                        PlaySound(TEXT("./music/success.wav"), NULL, SND_ASYNC);
                        userCommand();
                    default:
                        break;
                }
            }
        }

        count += 1;
        PlaySound(TEXT("./music/success.wav"), NULL, SND_ASYNC);

    } while(column > (gameMap[0].size() / 2) - 1 || row > (gameMap.size() / 2) - 1 || gameMap[(row * 2) - 1][(column * 2)] != "^" && gameMap[(row * 2) - 1][(column * 2)] != "v" && gameMap[(row * 2) - 1][(column * 2)] != "<" && gameMap[(row * 2) - 1][(column * 2)] != ">" );
    


    

    cout << "\nArrow " << gameMap[(row * 2) - 1][(column * 2)] << " is switched to ";

    if (direction == "right") gameMap[(row * 2) - 1][(column * 2)] = ">";
    else if(direction == "left") gameMap[(row * 2) - 1][(column * 2)] = "<";
    else if(direction == "up") gameMap[(row * 2) - 1][(column * 2)] = "^";
    else if(direction == "down") gameMap[(row * 2) - 1][(column * 2)] = "v";

    cout << gameMap[(row * 2) - 1][(column * 2)] << endl;

    sPause();
    xScreenAll();
}


// -------------- Zombie Move ------------------ //

void zombieMove()
{
    int currentZombie, currentX, currentY, mX, mY, randomNum, attackRz,attackZ, alienLife;
    int countTrap = 0;
    string gameLog;
    vector<string> empty_zombie;
    vector<vector<int>> randomPack =
    {
        {2,0},
        {-2,0},
        {0,2},
        {0,-2}
    };
    vector<vector<int>> rComb;

    for(int i = 1; i < characterDetails.size(); i++)
    {
        empty_zombie.push_back(to_string(i));
    }


    for(int i = 1; i <= characterDetails.size() -1; i++)
    {
        int alienLife = stoi(characterDetails[i][1]);
        if(characterDetails[i][0] == "-> " && alienLife == 0)
        {
            checkPCTurn();
            return;
        }
        else if(characterDetails[i][0] == "-> ")
        {
            currentZombie = i;
        }
    }

    alienLife = stoi(characterDetails[0][2]);
    attackZ = stoi(characterDetails[currentZombie][2]);
    attackRz = stoi(characterDetails[currentZombie][3]);
    currentX = stoi(characterDetails[currentZombie][4]);
    currentY = stoi(characterDetails[currentZombie][5]);

    // push number that did not greater than game map size into a vector call rComb
    for(int i = 0; i < randomPack.size(); i++)
    {
        if(gameMap[0].size() >= 24)
        {
            if(currentX + randomPack[i][0] < gameMap.size()-3 && currentX + randomPack[i][0] > 0 && currentY + randomPack[i][1] < gameMap[0].size()-1 && currentY + randomPack[i][1] > 0)
            {
                rComb.push_back(randomPack[i]);
            }
        }
        else
        {
            if(currentX + randomPack[i][0] < gameMap.size()-1 && currentX + randomPack[i][0] > 0 && currentY + randomPack[i][1] < gameMap[0].size()-1 && currentY + randomPack[i][1] > 0)
            {
                rComb.push_back(randomPack[i]);
            }
        }
        
    }

    // for(int i = 0; i < rComb.size(); i++)
    // {
    //     for(int j = 0; j < rComb[i].size(); j++)
    //     {
    //         cout << rComb[i][j] << ", ";
    //     }
    //     cout << endl;
    // }
    // sPause();


    srand(time(NULL));
    randomNum = rand() % rComb.size();
    mX = currentX + rComb[randomNum][0];
    mY = currentY + rComb[randomNum][1];
    countTrap = 0;

    while(isWall(mX,mY) || gameMap[mX][mY] == "A" || isZombie(gameMap, mX, mY))
    {
        countTrap += 1;

        // if zombie trap in corner by a zombie and an alien / zombie
        if(countTrap > 100)
        {
            rComb[randomNum][0] = 0;
            rComb[randomNum][1]= 0;
            break;
        }
        
        randomNum = rand() % rComb.size(); //since vector start from zero. NO +1
        mX = currentX + rComb[randomNum][0];
        mY = currentY + rComb[randomNum][1];

        if(gameMap[mX][mY] == " " || gameMap[mX][mY] == "h" || gameMap[mX][mY] == "p" || gameMap[mX][mY] == "B" || gameMap[mX][mY] == "r" || gameMap[mX][mY] == "^"  || gameMap[mX][mY] == "v" || gameMap[mX][mY] == "<" || gameMap[mX][mY] == ">")
        {
            break;
        }
        
        
    }
    

    // for(int i = 0; i < gameMap.size(); i++)
    // {
    //     for(int j = 0; j < gameMap[i].size(); j++)
    //     {
    //         cout << gameMap[i][j] << "(" << i << ", " << j <<")" << ", ";
    //     }
    //     cout << endl;
    // }
    // sPause();


    printAll();
    // checkPCTurn();

    if(rComb[randomNum][0] == 2)
    {
        gameLog = "Zombie " + to_string(currentZombie) + " moves down.";
    }
    else if(rComb[randomNum][0] == -2)
    {
        gameLog = "Zombie " + to_string(currentZombie) + " moves updaward.";
    }
    else if(rComb[randomNum][1] == 2)
    {
        gameLog = "Zombie " + to_string(currentZombie) + " moves right.";
    }
    else if(rComb[randomNum][1] == -2)
    {
        gameLog = "Zombie " + to_string(currentZombie) + " moves left.";
    }
    else if(rComb[randomNum][0] == 0 || rComb[randomNum][1] == 0)
    {
        mX = currentX + rComb[randomNum][0];
        mY = currentY + rComb[randomNum][1];
        gameLog = "Zombie " + to_string(currentZombie) + " no spaces move. Remain Position";
    }

    PlaySound(TEXT("./music/zombie.wav"), NULL, SND_ASYNC);
    logPrint("GAME LOG: " + gameLog);
    logPush(getTimeNow() + gameLog);
    this_thread::sleep_for(chrono::milliseconds(1100));

    if(gameMap[mX][mY] == "B")
    {
        characterDetails[currentZombie][1] = to_string(stoi(characterDetails[currentZombie][1]) - 20);
        PlaySound(TEXT("./music/bomb.wav"), NULL, SND_ASYNC);
        gameLog = "Zombie " + to_string(currentZombie) + " step on a bomb. LIFE -20. ";
        logPrint("GAME LOG: " + gameLog);
        logPush(getTimeNow() + gameLog);
        
        if(stoi(characterDetails[currentZombie][1]) <=0 )
        {
            characterDetails[currentZombie][1] = "0";
            gameLog = "Zombie " + to_string(currentZombie) + " dead. ";
            logPrint("GAME LOG: " + gameLog);
            logPush(getTimeNow() + gameLog);
            gameMap[currentX][currentY] = " ";
            gameMap[mX][mY] = " ";
            sPause();
            return;
        }
        this_thread::sleep_for(chrono::milliseconds(1100));
    }
    
    // sPause();
    

    gameMap[currentX][currentY] = " ";
    gameMap[mX][mY] = to_string(currentZombie);

    characterDetails[currentZombie][4] = to_string(mX);
    characterDetails[currentZombie][5] = to_string(mY);

    
    // printMap();
    printAll();

    bool confirmAtk = false;
    getAlienPos();

    // attack mode
    confirmAtk = (abs(playerY - mY) + abs(playerX - mX)) <= (attackRz * 2);


    if(confirmAtk)
    {
        PlaySound(TEXT("./music/hitAlien.wav"), NULL, SND_ASYNC);
        gameLog = "Zombie " + to_string(currentZombie) + " attacks Alien. Alien's life -" + to_string(attackZ) +".";
        logPrint("GAME LOG: " + gameLog);
        logPush(getTimeNow() + gameLog);
        alienLife -= attackZ;
        if(alienLife <= 0)
        {
            alienLife = 0;
        }
        characterDetails[0][2] = to_string(alienLife);
        if(alienLife > 0)
        {
            gameLog = "Alien is still alive.";
            logPrint("GAME LOG: " + gameLog);
            logPush(getTimeNow() + gameLog);
        }
        else
        {
            gameLog = "Alien is dead.";
            logPrint("GAME LOG: " + gameLog);
            logPush(getTimeNow() + gameLog);
            // cout << "Alien is dead." << endl << endl;
        }
    }
    else
    {
        gameLog = "Zombie " + to_string(currentZombie) + " unable attack Alien. Too Far.";
        logPrint("GAME LOG: " + gameLog);
        logPush(getTimeNow() + gameLog);
    }

    if(characterDetails[0][2] == "0")
    {
        loseGame();
    }
    
    // cout << gameMap[mX][mY] << ": " << mX << ": " <<mY << endl;

    // sPause();

    this_thread::sleep_for(chrono::milliseconds(1100));
    checkPCTurn();
    printAll();
    autoSave();
}

// ------------------------ QUIT GAME --------------------------
void quit()
{
    char selection;
    cout << "\nAre you sure? (y/n): ";
    cin >> selection;
    selection = tolower(selection);
    while (selection != 'y' && selection != 'n')
    {
        cout << "+-----------+---------------+" << endl;
        cout << "| Attention:| Invalid Input |" << endl;
        cout << "+-----------+---------------+" << endl;
        cout << "\nAre you sure? (y/n): ";
        cin >> selection;
        selection = tolower(selection);
    
        if(selection == 'y')
        {
            printGoodbye();
            exit(0);
        }
    }
    if(selection == 'y')
    {
        printGoodbye();
        exit(0);
    }
}


// ---------------------------------------- Game Loop for read user command ----------------------------------------// 

void userCommand()
{
    string command;
    bool loop = true;
    PlaySound(TEXT("./music/start.wav"), NULL, SND_ASYNC);
    while(loop)
    {
        bool win = true;
        
        for(int i = 1; i < characterDetails.size(); i++)
        {
            if(stoi(characterDetails[i][1]) > 0)
            {
                win = false;
            }
        }

        if(win)
        {
            winGame();
        }

        while(characterDetails[0][0] != "-> ")
        {
            zombieMove();
        }
        printAll();

        if(characterDetails[0][0] == "-> ")
        {
            int c, ex;
            bool loopTrue = true;
            cout << "Alien Turns' Now. Please select Fn keys / turn arrow." << endl;

            while(loopTrue)
            {
                ex = getch();
                if(ex == 0 || ex == 0xE0)
                {
                    ex = getch(); // Since function key getch() need to called 2 times
                    switch(ex)
                    {
                        case KEY_F1:
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Help Function Executed" << endl; 
                            this_thread::sleep_for(chrono::milliseconds(500));
                            loopTrue = false;
                            printHelp();
                            break;

                        case KEY_F2:
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Save Function Executed" << endl; 
                            this_thread::sleep_for(chrono::milliseconds(500));
                            loopTrue = false;
                            saveMapData(gameMap,characterDetails);
                            break;

                        case KEY_F3:
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Load Function Executed" << endl; 
                            this_thread::sleep_for(chrono::milliseconds(500));
                            loopTrue = false;
                            loadMap();
                            break;

                        case KEY_F4:
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Refresh Function Executed" << endl; 
                            this_thread::sleep_for(chrono::milliseconds(500));
                            loopTrue = false;
                            xScreenAll();
                            break;

                        case KEY_F5:
                            row = (gameMap.size() /2 ) -1;
                            column = (gameMap[0].size() / 2) -2;
                            numZombie = characterDetails.size() - 1;
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Restart Function Executed" << endl;
                            PlaySound(TEXT("./music/restart.wav"), NULL, SND_ASYNC);
                            cout << "+------------------+" << endl;
                            cout << "|  ~ Restarting ~  |" << endl; 
                            cout << "+------------------+" << endl;
                            this_thread::sleep_for(chrono::milliseconds(5000));
                            loopTrue = false;
                            clearVector();
                            initMap();
                            xScreenAll();
                            printAll();
                            break;
                        case KEY_F6:
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Quit Function Executed" << endl; 
                            this_thread::sleep_for(chrono::milliseconds(500));
                            loopTrue = false;
                            quit();
                            break;

                        default:
                            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
                            break;
                    }
                }
                else
                {
                    switch(ex)
                    {
                        case 'p':
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Change Arrow Function Executed" << endl; 
                            this_thread::sleep_for(chrono::milliseconds(500));
                            loopTrue = false;
                            controlArrow();
                            break;
                        
                        case 'w':
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Arrow Key Up Executed" << endl;//key up
                            this_thread::sleep_for(chrono::milliseconds(500));
                            moveAlien(-2, 0);
                            clearTrail();
                            checkPCTurn();
                            loopTrue = false;
                            break;

                        case 's':
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Arrow Key Down Executed" << endl;   // key down
                            this_thread::sleep_for(chrono::milliseconds(500));
                            moveAlien(2, 0);
                            clearTrail();
                            checkPCTurn();
                            loopTrue = false;
                            break;

                        case 'a':
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Arrow Key Left Executed" << endl;  // key left
                            this_thread::sleep_for(chrono::milliseconds(500));
                            moveAlien(0, -2);
                            clearTrail();
                            checkPCTurn();
                            loopTrue = false;
                            break;

                        case 'd':
                            PlaySound(TEXT("./music/tab.wav"), NULL, SND_ASYNC);
                            cout << endl << "Arrow Key Right Executed" << endl; 
                            this_thread::sleep_for(chrono::milliseconds(500));
                            moveAlien(0, 2);
                            clearTrail();
                            checkPCTurn();
                            loopTrue = false;
                            break;
                        
                        default:
                            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
                            break;
                    }

                    
                }
            }
        }
    }
}

// ----------------------------- Display win or lose -----------------------------------------

void winGame()
{
    string r;
    remove("./autosave/lastgame.txt");
    ofstream file;
    file.open("./autosave/lastgame.txt");
    file.close();
    xScreenAll();
    printAll();
    PlaySound(TEXT("./music/gameWin.wav"), NULL, SND_ASYNC);
    cout << R"(
_______  _______  __    _  _______  ______    _______  _______  __   __  ___      _______  _______  ___   _______  __    _  _______      __   __     
|       ||       ||  |  | ||       ||    _ |  |   _   ||       ||  | |  ||   |    |   _   ||       ||   | |       ||  |  | ||       |    |  | |  |  
|       ||   _   ||   |_| ||    ___||   | ||  |  |_|  ||_     _||  | |  ||   |    |  |_|  ||_     _||   | |   _   ||   |_| ||  _____|    |  | |  |  
|       ||  | |  ||       ||   | __ |   |_||_ |       |  |   |  |  |_|  ||   |    |       |  |   |  |   | |  | |  ||       || |_____     |  | |  |  
|      _||  |_|  ||  _    ||   ||  ||    __  ||       |  |   |  |       ||   |___ |       |  |   |  |   | |  |_|  ||  _    ||_____  |    |__| |__|  
|     |_ |       || | |   ||   |_| ||   |  | ||   _   |  |   |  |       ||       ||   _   |  |   |  |   | |       || | |   | _____| |     __   __   
|_______||_______||_|  |__||_______||___|  |_||__| |__|  |___|  |_______||_______||__| |__|  |___|  |___| |_______||_|  |__||_______|    |__| |__|  
                                       __   __  _______  __   __      _     _  ___   __    _    __   __   __  
                                      |  | |  ||       ||  | |  |    | | _ | ||   | |  |  | |  |  | |  | |  | 
                                      |  |_|  ||   _   ||  | |  |    | || || ||   | |   |_| |  |  | |  | |  | 
                                      |       ||  | |  ||  |_|  |    |       ||   | |       |  |  | |  | |  | 
                                      |_     _||  |_|  ||       |    |       ||   | |  _    |  |__| |__| |__| 
                                        |   |  |       ||       |    |   _   ||   | | | |   |   __   __   __  
                                        |___|  |_______||_______|    |__| |__||___| |_|  |__|  |__| |__| |__| 
    )";
    cout << "\n\n---------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    sPause();
    PlaySound(TEXT("./music/playAgain.wav"), NULL, SND_ASYNC);
    cout << "\nPlay again? (y/n)> ";
    getline(cin >> ws, r);
    while(r != "y" && r != "n")
    {
        cout << "ERROR: INVALID INPUT. Please reenter again." << endl;
        cout << "Play again? (y/n)> ";
        getline(cin >> ws, r);
    }
    if(r == "y")
    {
        main();
    }
    else if(r == "n")
    {
        printGoodbye();
        sPause();
        exit(0);
    }
}

void loseGame()
{
    string r;
    remove("./autosave/lastgame.txt");
    ofstream file;
    file.open("./autosave/lastgame.txt");
    file.close();
    xScreenAll();
    printAll();
    PlaySound(TEXT("./music/lose.wav"), NULL, SND_ASYNC);
    cout << "\n" << endl;
    cout << R"(
.-.   .-. .---.  .-. .-.   ,-.    .---.    .---. ,---.     .-.        _____   .---.           ,---.   ,-.,---.      .-.  .-.,-..-. .-. 
 \ \_/ )// .-. ) | | | |   | |   / .-. )  ( .-._)| .-'     |  )      /___  / / .-. ) |\    /| | .-.\  |(|| .-'      | |/\| ||(||  \| | 
  \   (_)| | |(_)| | | |   | |   | | |(_)(_) \   | `-.     | /          / /) | | |(_)|(\  / | | |-' \ (_)| `-.      | /  \ |(_)|   | | 
   ) (   | | | | | | | |   | |   | | | | _  \ \  | .-'     |/          / /(_)| | | | (_)\/  | | |--. \| || .-'      |  /\  || || |\  | 
   | |   \ `-' / | `-')|   | `--.\ `-' /( `-'  ) |  `--.   (          / /___ \ `-' / | \  / | | |`-' /| ||  `--.    |(/  \ || || | |)| 
  /(_|    )---'  `---(_)   |( __.')---'  `----'  /( __.'  (_)        (_____/  )---'  | |\/| | /( `--' `-'/( __.'    (_)   \|`-'/(  (_) 
 (__)    (_)               (_)   (_)            (__)                         (_)     '-'  '-'(__)       (__)                  (__)     
    )";
    cout << "\n--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Play again? (y/n)> ";
    getline(cin >> ws, r);
    while(r != "y" && r != "n")
    {
        cout << "ERROR: INVALID INPUT. Please reenter again." << endl;
        cout << "Play again? (y/n)> ";
        getline(cin >> ws, r);
    }
    if(r == "y")
    {
        main();
    }
    else if(r == "n")
    {
        printGoodbye();
        sPause();
        exit(0);
    }
}


// --------------------------------- Save /Load Data Into .txt file -------------------------------------

void loadMap()
{
    string selection;
    xScreenAll();
    cout << R"(
                         _      ____          _____    __  __          _____  
                         | |    / __ \   /\   |  __ \  |  \/  |   /\   |  __ \ 
                         | |   | |  | | /  \  | |  | | | \  / |  /  \  | |__) |
                         | |   | |  | |/ /\ \ | |  | | | |\/| | / /\ \ |  ___/ 
                         | |___| |__| / ____ \| |__| | | |  | |/ ____ \| |     
                         |______\____/_/    \_\_____/  |_|  |_/_/    \_\_|     
    )" << '\n';
    cout << "*******************************************************************************************************************************" << endl;
    cout << "Do you want to save current game (y/n): ";
    getline(cin >> ws, selection);
    while(selection != "y" && selection != "n")
    {
        PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
        cout << "\n---------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "ERROR: Invalid Input. Only accept (y/n), please reenter." << endl;
        cout << "Do you want to save current game (y/n): ";
        getline(cin >> ws, selection);
    }
    PlaySound(TEXT("./music/success.wav"), NULL, SND_ASYNC);
    if(selection == "y")
    {
        saveMapData(gameMap,characterDetails);
        readGameMap();

        printAll();
    }
    else
    {
        readGameMap();
        printAll();
    }
}

void saveMapData(vector<vector<string>> v1, vector<vector<string>> v2)
{
    string fileName = "";
    int ex;

    ofstream file1; // write data into txt
    ifstream fileIn; // read file from txt 
    xScreenAll();

    cout << R"(
                   _____    __      ________   __  __          _____  
                  / ____|  /\ \    / /  ____| |  \/  |   /\   |  __ \ 
                 | (___   /  \ \  / /| |__    | \  / |  /  \  | |__) |
                  \___ \ / /\ \ \/ / |  __|   | |\/| | / /\ \ |  ___/ 
                  ____) / ____ \  /  | |____  | |  | |/ ____ \| |     
                 |_____/_/    \_\/   |______| |_|  |_/_/    \_\_|  
    )" << '\n';
    cout << "*********************************************************************************************************************************" << endl;
    cout << "\t+--------------------------------------------------------------------------+" << endl;
    cout << "\t|                                 GUIDANCE                                 |" << endl;
    cout << "\t+--------------------------------------------------------------------------+" << endl;
    cout << "\t|1. Enter prefer file name to save the current game.                       |" << endl;
    cout << "\t+--------------------------------------------------------------------------+" << endl;
    cout << "\t|2. Input Example-> [name].txt | Sample: { game1.txt }                     |" << endl;
    cout << "\t+--------------------------------------------------------------------------+" << endl;
    cout << "\t|3. REMARK-> File will not be proper save if file name not included [.txt] |" << endl;
    cout << "\t+--------------------------------------------------------------------------+" << endl << endl;
    cout << "\tEnter file name [ESC - BACK TO LAST PAGE]: ";

    do
    {
        while((ex = getch()) != KEY_ENTER)
        {
            if(ex == KEY_ESC)
            {
                xScreenAll();
                userCommand();
                break;
            }
            else if(ex == KEY_BACKSPACE)
            {
                if (!fileName.empty())
                {
                    fileName.resize(fileName.size() - 1);
                }
            }
            else
            {
                fileName += char(ex);
            }

            clearLine(20);
            cout << "\tEnter file name [ESC - BACK TO LAST PAGE]: " << fileName;
        }
        fileIn.open(fileName);

        if(fileIn)
        {
            PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
            cout << "\t[ ERROR MESSAGE: FILE ALREADY EXIST. Please reenter. ]" << endl;
            fileIn.close();
        }

    } while(fileIn);

    PlaySound(TEXT("./music/success.wav"), NULL, SND_ASYNC);

    file1.open("./temp.txt");

    for(int i=0; i< v1.size(); i++ )
    {
        for(int j = 0; j < v1[i].size(); j++)
        {
            file1 << v1[i][j] << endl;
        }
        file1 << "@" << endl;
    }

    file1 << "$" << endl; // divide data into game map & character details

    for(int i=0; i< v2.size(); i++ )
    {
        for(int j = 0; j < v2[i].size(); j++)
        {
            file1 << v2[i][j] << endl;
        }
        file1 << "@" << endl;
    }
    file1 << "%" << endl;
    file1.close();
    const char* charFile = fileName.c_str();
    remove(charFile);
    rename("./temp.txt", charFile);

    cout << "\n\n\n";
    cout << "\t\t\t+-----------------------+" << endl;
    cout << "\t\t\t| SUCCESS!! Game Saved. |" << endl;
    cout << "\t\t\t+-----------------------+" << endl;
    PlaySound(TEXT("./music/success.wav"), NULL, SND_ASYNC);
    sPause();
    xScreenAll();
}


void readGameMap()
{
    vector<string> tempDataList;
    vector<string> tempDataList2;
    int turn = 0;
    int number_line = 0;
    string line;
    string fileName;

    clearVector();

    cout << "\nEnter the file name to load [Without .txt]: ";
    getline(cin >> ws, fileName);

    ifstream file("./" + fileName + ".txt");

    if(file.fail())
    {
        PlaySound(TEXT("./music/error.wav"), NULL, SND_ASYNC);
        cout << "\n";
        cout << "+-------------------------------------------+" << endl;
        cout << "|ERROR: The game file record doesn't exist. |" << endl;
        cout << "+-------------------------------------------+" << endl;
        cout << "|          ~ Back To Main Page Now ~        |" << endl;
        cout << "+-------------------------------------------+" << endl;
        sPause();
        main();
    }
    PlaySound(TEXT("./music/success.wav"), NULL, SND_ASYNC);

    while (getline(file,line))
    {
        number_line++;

        if(line.size()== 1 && line == "$")
        {
            turn += 1;
        }

        if(line.size() == 1 && line == "%")
        {
            break;
        }

        if(turn == 0)
        {
            if(line.size()>=0)
            {
                tempDataList.push_back(line);
            }
            if(line.size()== 1 && line == "@")
            {
                tempDataList.pop_back();
                gameMap.push_back(tempDataList);
                tempDataList.clear();
            }
        }
        else if (turn == 1)
        {
            if(line.size()>0)
            {
                tempDataList.push_back(line);
            }
            if(line.size()== 1 && line == "@")
            {
                tempDataList.pop_back();
                characterDetails.push_back(tempDataList);
                tempDataList.clear();
            }
        }
    }
    characterDetails[0].erase(characterDetails[0].begin());
    file.close();

    cout << endl << endl;
    PlaySound(TEXT("./music/success.wav"), NULL, SND_ASYNC);
    cout << "\t\t\t+------------------------+" << endl;
    cout << "\t\t\t| SUCCESS !! Game Loaded.|" << endl;
    cout << "\t\t\t+------------------------+" << endl;
    
    
    for(int i = 1;i <= 8; i++) // push in last game latest game log history
    {
        gameLog_list.push_back(gameMap[i][gameMap[i].size()-1]);
    } 
    sPause();
    xScreenAll();
}

// --------------------------------- Auto Save ---------------------------------
void autoSave()
{
    vector<vector<string>> v1 = gameMap;
    vector<vector<string>> v2 = characterDetails;

    ofstream file1;

    file1.open("./autosave/temp.txt");
    for(int i=0; i< v1.size(); i++ )
    {
        for(int j = 0; j < v1[i].size(); j++)
        {
            file1 << v1[i][j] << endl;
        }
        file1 << "@" << endl;
    }

    file1 << "$" << endl; // divide data into game map & character details

    for(int i=0; i< v2.size(); i++ )
    {
        for(int j = 0; j < v2[i].size(); j++)
        {
            file1 << v2[i][j] << endl;
        }
        file1 << "@" << endl;
    }
    file1 << "%" << endl;
    file1.close();

    remove("./autosave/lastgame.txt");
    rename("./autosave/temp.txt", "./autosave/lastgame.txt");

    wLastGameTime();
}



void autoSyncMap()
{
    vector<string> tempDataList;
    vector<string> tempDataList2;
    int turn = 0;
    int number_line = 0;
    string line;



    ifstream file("./autosave/lastgame.txt");
    while (getline(file,line))
    {
        number_line++;

        if(line.size()== 1 && line == "$")
        {
            turn += 1;
        }

        if(line.size() == 1 && line == "%")
        {
            break;
        }

        if(turn == 0)
        {
            if(line.size()>=0)
            {
                tempDataList.push_back(line);
            }
            if(line.size()== 1 && line == "@")
            {
                tempDataList.pop_back();
                gameMap.push_back(tempDataList);
                tempDataList.clear();
            }
        }
        else if (turn == 1)
        {
            if(line.size()>0)
            {
                tempDataList.push_back(line);
            }
            if(line.size()== 1 && line == "@")
            {
                tempDataList.pop_back();
                characterDetails.push_back(tempDataList);
                tempDataList.clear();
            }
        }
    }
    characterDetails[0].erase(characterDetails[0].begin());
    file.close();

}

void wLastGameTime()
{
    int hour, min, sec;
    auto now = chrono::system_clock::now();
    time_t time_now = chrono::system_clock::to_time_t(now);
    string str_time = ctime(&time_now);

    endGame = clock();
    int totalGameTime = (endGame - startGame) / int(CLOCKS_PER_SEC);
    min = totalGameTime / 60;
    sec = totalGameTime % 60;
    hour = min / 60;
    min = min % 60;

    string str_totalTime = to_string(hour) + " hour(s) " + to_string(min) + " minute(s) " + to_string(sec) + " second(s) ";

    ofstream file1;
    file1.open("./autosave/temp2.txt");

    file1 << str_time;
    file1 << str_totalTime;
    file1.close();
    remove("./autosave/lastGameTime.txt");
    rename("./autosave/temp2.txt", "./autosave/lastGameTime.txt");
}

void rLastGameTime()
{
    string line;
    string lastGameTime;
    ifstream file("./autosave/lastGameTime.txt");
    
    if(file.is_open())
    {
        while(getline(file, line))
        {
            // lastGameTime = line;
            gameTimeList.push_back(line);
        }
    }
    file.close();


}



// -------------------------------- Check System Operating ------------------------------ //

void xScreenAll()
{
    #if defined(__linux__) // Or #if __linux__
        system("CLEAR");
    #elif _WIN32
        system("CLS");
    #endif
}

void xScreen() {
    setCursor(1, 1);
}

void sPause()
{
    #if defined(__linux__) // Or #if __linux__
        std::system(R"(read -p "Press any key to continue . . . " dummy)");
    #elif _WIN32
        system("PAUSE");
    #endif
}

// --------------------------- Set color for game character and object -------------------------------
// Link reference: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 || https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
//                 https://www.ing.iac.es/~docs/external/bash/abs-guide/colorizing.html#:~:text=The%20simplest%2C%20and%20perhaps%20most,%5B0%22%20switches%20it%20off.

void setColor(int fc , int bc)
{
    if(fc == C_DEFAULT)
    {
        cout << "\033[39m";
    }
    else
    {
        cout << "\033[38;5;" << fc << "m";
    }

    if(bc == C_DEFAULT)
    {
        cout << "\033[49m";
    }
    else
    {
        cout << "\033[48;5;" << bc << "m";
    }

    fflush(stdout);
}

//  ----------------------------- Set cursor to x, y position -----------------------

// Refer link: https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html
// Refer Link: https://stackoverflow.com/questions/1670891/how-can-i-print-a-string-to-the-console-at-specific-coordinates-in-c

void setCursor(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
    fflush(stdout);
}

// -----------------------------
// clear line at y position
// -----------------------------
void clearLine(int y)
{
    setCursor(0, y);
    printf("\033[K");
    fflush(stdout); //push what print on console out immediate
}

// -------------------------------- show cursor ---------------------------------------------------
void showCursor(bool visible)
{
    if(visible)
    {
        cout << "\033[?25h" << flush;
    }
    else
    {
        cout << "\033[?25l" << flush;
    }
}

// -----------------------------
// init ANSI ESC sequence and get terminal size
// -----------------------------
// Refer link: https://stackoverflow.com/questions/44482505/setconsolemode-returning-false-when-enabling-ansi-color-under-windows-10
bool initColorTerminal(int &x, int &y)
{
    #ifdef _WIN32

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int cols, rows;

        // Measure Windows Display Size
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // Use For Set Color. Enable ANSI Color
        DWORD consoleMode;
        GetConsoleMode(hConsole, &consoleMode);
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        return SetConsoleMode(hConsole, consoleMode);

    #else
        return true;
    #endif
}

// ------------------------------- Force To Maximize The Windows For Best Game Experience -------------------------------

void maximizeWindow()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}


// ---------------------------------- Main function Run ---------------------------------- //


int main()
{
    //Test for ANSI ESCAPE CODE
    // cout << "\033[31;1;4mHello\033[0m";
    // cout<< "\033[4mThis is underline text.\033[0m" << endl;
    // cout<< "\033[3mThis is italic text.\033[0m" << endl;
    // cout<< "\033[1;4mThis is bold text.\033[0m" << endl;
    // cout << "Normal";
    // sPause();

    startGame = clock();

    static CONSOLE_FONT_INFOEX  fontex;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.FontWeight = 1000;
    fontex.FontFamily = ANSI_CHARSET;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
    
    clearVector();

    maximizeWindow();

    if(!initColorTerminal(screenWidth, screenHeight)) {
        cout << "Failed to init color terminal. EXIT!" << endl;
        exit(0);
    }


    getAlienPos();
    printDefaultSetting();
    initMap();
    xScreenAll();
    printMap();
    turnGuide();
    userCommand();

    sPause();
}
