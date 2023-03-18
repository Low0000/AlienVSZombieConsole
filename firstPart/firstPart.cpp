// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT7L 
// Names: Low Kai Yan | Nicholas Tiow Kai Bo
// IDs:    1211101699 |  1211102398
// Emails: 1211101699@student.mmu.edu.my |  1211102398@student.mmu.edu.my

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

using namespace std;

// ------------------------------------- All Created void Function ------------------------------------------- //

void printDefaultSetting();
void initMap();
void printMap();
void printAll();
void turnGuide();
void userCommand();
void clearTrail();
string randomlyNewObject();
int getPlayerPosY(vector<vector<string>> playerPos);
int getPlayerPosX(vector<vector<string>> playerPos);
int getTotalSpace(vector<vector<string>> mapSize);
void moveAlien(int mX, int mY);
void sPause();
void xScreen();
void zombieMove();


// ---------------------------- Initialize global variable data -------------------------------- //

int row = 5, column = 9, numZombie = 1, playerX = 0, playerY = 0;
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
vector<vector<int>> finalZombiePos;



// ---------------------------------- Get Data By Code Automatically -------------------------------------//
int getTotalSpace(vector<vector<string>> mapSize)
{
    int columnSize, rowSize, totalBlank;

    columnSize = (gameMap.size() / 2) - 1;
    rowSize = (gameMap[0].size() / 2) - 1;

    totalBlank = columnSize * rowSize;

    return totalBlank;
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
    return posX < 1 || posX > gameMap.size() - deleteNum || posY < 2 || posY > gameMap[0].size()-2;
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

    // cout << "Current Pos: " << currentPos << endl;
    // cout << characterDetails.size()-1 << endl
    // for(int i = 0; i < characterDetails.size(); i++)
    // {
    //     for(int j = 0; j < characterDetails[i].size(); j++)
    //     {
    //         cout << characterDetails[i][j] << ", ";
    //     }
    // }
    // sPause();
    // cout << currentPos << endl;

    if(currentPos == characterDetails.size() - 1)
    {
        currentPos = 0;
        characterDetails[characterDetails.size()-1][0] = "   ";
        characterDetails[currentPos][0] = "-> ";
    }
    else
    {
        // cout << currentPos << endl;
        characterDetails[currentPos][0] = "   ";
        currentPos += 1;
        characterDetails[currentPos][0] = "-> ";
    }
    
    // sPause(); 
}

void turnGuide()
{
    cout << endl;
    // cout << "MAP SIZE: "<< gameMap.size() << "   " << gameMap[0].size() << endl;
    cout << characterDetails[0][0] << characterDetails[0][1] << " Life " << setw(3) << characterDetails[0][2] << ", " << "Attack " << setw(3) << characterDetails[0][3] << ", Position: [ ROW: " << (getPlayerPosX(gameMap) + 1) / 2 << " | COLUMN: " << (getPlayerPosY(gameMap)+1)/ 2 << " ]" << endl << endl;
    for(int i = 1;i <= characterDetails.size() - 1; i++)
    {
        for(int j = 0; j < (characterDetails[i].size() / 4); j++)
        {
            // cout.width(3);
            cout << characterDetails[i][j] << "Zombie " << (i) << ": " << "Life " << setw(3) << characterDetails[i][j+1] 
            << ", " << "Attack " << setw(3) <<characterDetails[i][j+2] << ", " 
            << "Range " << setw(3) << characterDetails[i][j+3] 
            << ", Position: [ ROW: " << (stoi(characterDetails[i][j+4]) + 1) / 2 << " | COLUMN:" << (stoi(characterDetails[i][j+5]) + 1) / 2 << " ]"  << endl << endl;
        }
    }
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
    xScreen();
    cout << "          .: Alien vs Zombie :." << endl << endl; 
    for(int i = 0; i < gameMap.size(); i++)
    {
        for(int j = 0; j < gameMap[i].size(); j++)
        {
            cout << gameMap[i][j];
        }
        cout << endl;
    }

    // check index of alien, zombie, new object, wall
    // for(int i = 0; i < gameMap.size(); i++)
    // {
    //     for(int j = 0; j < gameMap[i].size(); j++)
    //     {
    //         cout << gameMap[i][j] << "(" << i << ", " << j <<")" << ", ";
    //     }
    //     cout << endl;
    // }
}


void printAll()
{
    xScreen();
    printMap();
    turnGuide();
}

void printDefaultSetting()
{
    string selection;
    xScreen();
    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : 5" << endl;
    cout << "Board Columns : 9" << endl;
    cout << "Zombie Count  : 1" << endl << endl;

    cout << "Do you wish to change the game settings (y/n)? => ";
    getline(cin >> ws, selection);
    while (selection != "y" && selection != "n")
    {
        cout << "+-----------+-----------------------------+" << endl;
        cout << "|ATTENTION: | Only Accept Charcater (y/n) |" << endl;
        cout << "+-----------+-----------------------------+" << endl << endl;
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> selection;
    }

    if(selection == "y")
    {
        xScreen();
        cout << "Board Settings" << endl;
        cout << "-----------------" << endl;
        cout << "Enter rows => ";
        cin >> row;
        while(row % 2 == 0 || cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "+----------+---------------------------------------------+" << endl;
            cout << "|ATTENTION:| This input of rows only accepted odd number |" << endl;
            cout << "+----------+---------------------------------------------+" << endl << endl;
            cout << "Enter rows => ";
            cin >> row;
        }
        cout << "Enter columns => ";
        cin >> column;

        while(column % 2 == 0 || cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "+-----------+------------------------------------------------+" << endl;
            cout << "|ATTENTION: | This input of columns only accepted odd number |" << endl;
            cout << "+-----------+------------------------------------------------+" << endl << endl;
            cout << "Enter Columns => ";
            cin >> column;
        }

        cout << endl;

        cout << "Zombie Settings" << endl;
        cout << "------------------" << endl;
        cout << "Enter number of zombies => ";
        cin >> numZombie;
        while(numZombie > 9 || cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "+-----------+----------------------------------------------+" << endl;
            cout << "|ATTENTION: | The number of zombies cannot greater than 9. |" << endl;
            cout << "+-----------+----------------------------------------------+" << endl << endl;
            cout << "Enter number of zombies => ";
            cin >> numZombie;
        }
        cout << endl;

        cout << "Settings updated." << endl;
        sPause();
    }
    else if(selection == "n")
    {
        row = 5;
        column = 9;
        numZombie = 1;
    }
}

// --------------------------------- Initialize The Details Of Game Map ----------------------------------------//

string randomlyNewObject()
{
    string randomObj = " ";

    int randomNum = rand() % 100; // 0 -99 //44

    if(randomNum > 70)
    {
        randomNum = rand() % 100; // 0 - 99
        if (randomNum < 5) randomObj = "h"; //+20
        else if (randomNum < 10) randomObj = "p"; // attack the nearest zombie wif 10 attack value
        else if (randomNum < 20) randomObj = "r";
        else if (randomNum < 40) randomObj = "<";
        else if (randomNum < 60) randomObj = ">";
        else if (randomNum < 80) randomObj = "v";
        else randomObj = "^";
    }

    return randomObj;
}



void initMap()
{
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
                gameMap[i].push_back("|");
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
                gameMap[i].push_back("+");
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
        gameMap[gameMap.size()-1].push_back("   ");
        for(int i = 0; i < 9; i++)
        {
            gameMap[gameMap.size() - 1].push_back(" ");
            gameMap[gameMap.size()-1].push_back(to_string(i+1));
        }
        for(int i = 0; i < remain_num; i++)
        {
            if(i == remain_num - 1)
            {
                for(int j = 0; j < remainder + 1; j++)
                {
                    gameMap[gameMap.size()-1].push_back(" ");
                    gameMap[gameMap.size()-1].push_back(to_string(j));
                }
            }
            else if(remain_num > 1 || (i != remain_num - 1))
            {
                for(int j = 0; j <= 9; j++)
                {
                    gameMap[gameMap.size()-1].push_back(" ");
                    gameMap[gameMap.size()-1].push_back(to_string(j));
                }
            }
            else
            {
                for(int j = 0; j < remainder + 1; j++)
                {
                    gameMap[gameMap.size()-1].push_back(" ");
                    gameMap[gameMap.size()-1].push_back(to_string(j));
                }
            }
            
        }
    }
    else
    {
        gameMap.push_back(empty_vec);
        gameMap[gameMap.size()-1].push_back("   ");
        for(int i = 0;i < column; i++)
        {
            gameMap[gameMap.size()-1].push_back(" ");
            gameMap[gameMap.size()-1].push_back(to_string(i+1));
        }
    }



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
            randomLife = (rand() % 350 + 1);
        } while(randomLife < 120 || randomLife % 10 != 0);

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
        randNumZ = rand() % (emptySpacePosList.size() - 1); // 0
        zombieX = emptySpacePosList[randNumZ][0]; //emptySpacePosList[0][0]
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
    
}



//---------------------------- Movement Of The Alien ( UP / DOWN / LEFT / RIGHT ) -----------------------------------
//The alien still can't able to scan the zombie
void moveAlien(int mX, int mY)
{
    string randomObj;
    int currentX, currentY;
    int alienAttack = stoi(characterDetails[0][3]);
    getAlienPos();

    xScreen();
    printMap();

    currentX = playerX;
    currentY = playerY;
    
    playerX = currentX + mX;
    playerY = currentY + mY;


    // When alien meet a wall
    if(isWall(playerX, playerY))
    {
        cout << "\nAction Log: Aliens hit a border." << endl << endl;
        sPause();
        return;
    }

    // When alien meet rock
    if(gameMap[playerX][playerY] == "r")
    {
        cout << "\nAction Log: Alien stumbles upon a rock." << endl;
        
        gameMap[playerX][playerY] = randomlyNewObject();
        if(gameMap[playerX][playerY] == " ")
        {
            randomObj = " nothing ";
        }
        else if(gameMap[playerX][playerY] == "^" || gameMap[playerX][playerY] == "v" || gameMap[playerX][playerY] == "<" || gameMap[playerX][playerY] == ">")
        {
            randomObj = " an arrow ";
        }
        else if(gameMap[playerX][playerY] == "p")
        {
            randomObj = " a pod ";
        }
        else if(gameMap[playerX][playerY] == "h")
        {
            randomObj = " a health pack ";
        }
        cout << "Action discovers [" << randomObj << "] beneath the rock" << endl;

        sPause();
        return;
    }

    

    // if alien hit arrow / health pack / pod
    if(gameMap[playerX][playerY] == "^")
    {
        cout << "\nAction Log: Alien find an arrow." << endl;
        cout << "Attack increase 20" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        mX = -2;
        mY = 0;
        alienAttack += 20;
        characterDetails[0][3] = to_string(alienAttack);
    }
    else if(gameMap[playerX][playerY] == "v")
    {
        cout << "\nAction Log: Alien find an arrow." << endl;
        cout << "Attack increase 20" << endl;
        this_thread::sleep_for(chrono::milliseconds(1500));
        mX = 2;
        mY = 0;
        alienAttack += 20;
        characterDetails[0][3] = to_string(alienAttack);
    }
    else if(gameMap[playerX][playerY] == "<")
    {
        cout << "\nAction Log: Alien find an arrow." << endl;
        cout << "Attack increase 20" << endl;
        this_thread::sleep_for(chrono::milliseconds(1500));
        mX = 0;
        mY = -2;
        alienAttack += 20;
        characterDetails[0][3] = to_string(alienAttack);
    }
    else if(gameMap[playerX][playerY] == ">")
    {
        cout << "\nAction Log: Alien find an arrow." << endl;
        cout << "Attack increase 20" << endl;
        this_thread::sleep_for(chrono::milliseconds(1500));
        mX = 0;
        mY = 2;
        alienAttack += 20;
        characterDetails[0][3] = to_string(alienAttack);
    }
    else if(gameMap[playerX][playerY] == "h")
    {
        cout << "\nAction Log: Alien finds a health pack." << endl;
        cout << "Alien's life increased by 20." << endl;

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
        this_thread::sleep_for(chrono::milliseconds(1500));
    }
    else if(gameMap[playerX][playerY] == " ")
    {
        cout << "\nAction Log: Alien find an empty space." << endl;
        this_thread::sleep_for(chrono::milliseconds(1100));
    }
    else if(gameMap[playerX][playerY] == ".")
    {
        cout << "\nAction Log: Alien return back the same route." << endl;
        this_thread::sleep_for(chrono::milliseconds(1100));
    }

    

    gameMap[currentX][currentY] = ".";
    gameMap[playerX][playerY] = "A";

    

    printMap();
    this_thread::sleep_for(chrono::milliseconds(1000));

    moveAlien(mX, mY);
} 


// -------------- Zombie Move ------------------ //
// The zombie will eat alien immediatly cause of ignore alien.

void zombieMove()
{
    int currentZombie, currentX, currentY, mX, mY, randomNum;
    vector<vector<int>> randomPack =
    {
        {2,0},
        {-2,0},
        {0,2},
        {0,-2}
    };
    for(int i = 1; i <= characterDetails.size() -1; i++)
    {
        if(characterDetails[i][0] == "-> ")
        {
            currentZombie = i;
        }
    }
    currentX = stoi(characterDetails[currentZombie][4]);
    currentY = stoi(characterDetails[currentZombie][5]);

    srand(time(NULL));
    randomNum = rand() % 4;
    mX = currentX + randomPack[randomNum][0];
    mY = currentY + randomPack[randomNum][1];


    while(isWall(mX,mY))
    {
        randomNum = rand() % 4;
        mX = currentX + randomPack[randomNum][0];
        mY = currentY + randomPack[randomNum][1];
    }

    printAll();
    checkPCTurn();

    if(randomPack[randomNum][0] == 2)
    {
        cout << "\nZombie " << currentZombie <<  " moves down." << endl;
    }
    else if(randomPack[randomNum][0] == -2)
    {
        cout << "\nZombie " << currentZombie <<  " moves updaward." << endl;
    }
    else if(randomPack[randomNum][1] == 2)
    {
        cout << "\nZombie " << currentZombie <<  " moves right." << endl;
    }
    else if(randomPack[randomNum][1] == -2)
    {
        cout << "\nZombie " << currentZombie <<  " moves left." << endl;
    }
    
    sPause();

    gameMap[currentX][currentY] = " ";
    gameMap[mX][mY] = to_string(currentZombie);

    characterDetails[currentZombie][4] = to_string(mX);
    characterDetails[currentZombie][5] = to_string(mY);

    printAll();
}


// ---------------------------------------- Game Loop for read user command ----------------------------------------// 

void userCommand()
{
    string command;
    bool loop = true;
    while(loop)
    {
        // cout << "C: " << characterDetails[0][0] << endl;
        // system("PAUSE");
        while(characterDetails[0][0] != "-> ")
        {
            zombieMove();
        }
        printMap();
        turnGuide();
        cout << "Command> ";
        getline(cin >> ws, command);

        if(command == "help")
        {
            cout << endl << "Commands" << endl;
            cout << "1. up - Move up." << endl;
            cout << "2. down - Move Down." << endl;
            cout << "3. left - Move Left." << endl;
            cout << "4. right - Move Right." << endl;
            cout << "5. arrow - Change the direction of an arrow." << endl;
            cout << "6. help - Display these users commands." << endl;
            cout << "7. save - Save the game." << endl;
            cout << "8. load - Load a game." << endl;
            cout << "9. quit = Quit the game." << endl << endl;

            sPause();
        }
        else if(command == "up")
        {
            moveAlien(-2, 0);
            clearTrail();
            checkPCTurn();
        }
        else if(command == "down")
        {
            moveAlien(2, 0);
            clearTrail();
            checkPCTurn();
        }
        else if(command == "right")
        {
            moveAlien(0, 2);
            clearTrail();
            checkPCTurn();
        }
        else if(command == "left")
        {
            moveAlien(0, -2);
            clearTrail();
            checkPCTurn();
        }
        else if(command == "quit")
        {
            loop = false;
        }
    }
}

// -------------------------------- Check System Operating ------------------------------ //

void xScreen()
{
    #if defined(__linux__) // Or #if __linux__
        system("CLEAR");
    #elif _WIN32
        system("CLS");
    #endif
}

void sPause()
{
    #if defined(__linux__) // Or #if __linux__
        std::system(R"(read -p "Press any key to continue . . . " dummy)");
    #elif _WIN32
        system("PAUSE");
    #endif
}


int main()
{
    getAlienPos();
    printDefaultSetting();
    initMap();
    printMap();
    turnGuide();
    userCommand();

    sPause();
}



// Task To Be Done: Function: Zombie attack / alien attack / pod attack / arrow control / save game / load game 
// Additional Feature: 1. Use keyboard arrow key to control the alien and change the direction of the arrow power
//                     2. Do some game sound effect
//                     3. Improve user interface
// Details: Need to limit user map size according to the windows screen size for better game experience. 
//          Make sure the input of column and row of the game map is make sense. Example if player input column 3, row 3 but the zombie place 9, it is not make sense
