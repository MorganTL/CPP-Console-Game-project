/* 

Project ended on 22/7/2020 1200HR HKT
Copyrighted by Morgan Cheng

This is a buggy and laggy snake game. 
And intended to use a learning tool.

*/


#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <thread>
#include <ctime>

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80


// Class Display > snake move moment > score


//This create the display(map)
//Contain the function to draw the map
class DISPLAY {

    protected:

    //!!!DONT make the map less than 10x10!!!
    //set the map size and the square display size!!!
    // Need to change both!!!
    int map_height = 20;
    int map_width = 38;

    // [height][width]
    char map[20][38];

    public:

    DISPLAY(){
        //Create a boarder around the map

        for (int s = 0; s < map_height; s++){
            for (int k = 0; k < map_width; k++){

                if ( (s == 0 and k == 0) or (s == 0 and k == map_width - 1) or (s == map_height -1 and k == 0) or (s == map_height -1 and k == map_width -1) ){
                    //The coner will display +
                    map[s][k] = '+';
                }
                else if ( s == 0 or s == map_height - 1){
                    //The top and bottom border
                    map[s][k] = '-';
                }
                else if ( k == 0 or k == map_width - 1){
                    //The 2 sides border
                    map[s][k] = '|';
                }
                else {
                    //Empty spaces
                    map[s][k] = ' ';
                }
            }
        }
    };

    //PRINT the whole map on the console
    void PRINT(){
        for (int i = 0; i < map_height; i++){

            for (int j = 0; j < map_width; j++){
                std::cout << map[i][j];
            }
            std::cout << "\n";
        }

    };


};




//Create one fruit randomly on screen
class FRUIT_CONTROL : public DISPLAY{

    //Fruit_x & y is the locaiton of the fruit
    protected:

    int fruit_x;
    int fruit_y;


    public:
    //Generate a random fruit
    FRUIT_CONTROL(): DISPLAY(), fruit_x( 1 + rand() % (map_width - 5 ) ), fruit_y( 1 + rand() % (map_height - 5 ) ){
        map[fruit_y][fruit_x] = '*';
    };

    //Generate a random fruit
    void ADD_NEW_FRUIT(){
        //Create new seed for rand()
        srand ( time(NULL) );

        //Using new seed to generate a new fruit
        fruit_x = 1 + rand() % (map_width - 5 );
        fruit_y = 1 + rand() % (map_height - 5 );
        map[fruit_y][fruit_x] = '*';
    }

};

//  *DLC*
//Create many fruits on screen
//Depends on size
class MULTI_FRUIT_CONTROL : DISPLAY{};


class SNAKE : public FRUIT_CONTROL{

    protected:
    //head is for easy access of the head of body
    //Orgin is at the left top hand coner
    // N: up | S: down | W: left | E:right
    int head_x;
    int head_y;
    std::vector< std::vector<int> > snake_body;

    //GAMEOVER is for collision degtection
    bool GAMEOVER = false;

    //Heading is the direction that the snake will travel next frame
    char heading = 'E';

    //The score of the snake
    int score = 0;

    public:

    //This create the SNAKE and draw the snake on the display
    // (x,y) is the location of the head
    SNAKE(int x, int y): FRUIT_CONTROL(), head_x(x), head_y(y){
        snake_body.push_back({x, y});
        map[y][x] = '@';
    };


    //1. Update the head location
    //2. See whether the snake is hitting something
    //3. Generate the frame
    void NEXT_FRAME(){




        //!!!DONT change the order!!!


        this->UPDATE_head(); //Change the location of the head_x & y in the next frame
        //test case::
        // map[10][5] = '*';
        // map[10][6] = '*';
        this->COLLISION_DETECTION();
        this->UPDATE_MAP();



    };

    //Change the location of the head_x & y in the next frame
    void UPDATE_head(){
        if (heading == 'S'){
            head_y++;
        }
        else if (heading == 'N'){
            head_y--;
        }
        else if (heading == 'W'){
            head_x--;
        }
        else if (heading == 'E'){
            head_x++;
        }
    };


    //Give gameover = T when the head is hitting the border or body
    //Extent the snake if it hit a fruit !!!
    void COLLISION_DETECTION(){

        char new_head_location = map[head_y][head_x];
        //If the head hit the border!!!!
        //including score board
        if (head_x == 0 or head_y == 0 or head_x == map_width - 1 or head_y == map_height - 1 ){
            GAMEOVER = true;
        }
        else if (new_head_location == '*'){
            snake_body.push_back(snake_body[0]); //Let the update map kill off only one tail and regan it as old head
            //ADD new fruit
            this->ADD_NEW_FRUIT();
            //add +1 to score
            score++;
        }
    };


    //1.Delete tail
    //2.Generate new head according to snake travel direction (heading)
    //3.Update score board
    void UPDATE_MAP(){
        //Get tail locaiton and delete it from the map and body
        int tail_x = snake_body[0][0];
        int tail_y = snake_body[0][1];

        map[tail_y][tail_x] = ' ';
        snake_body.erase( snake_body.begin() );

        //1. Get the old head location and turn it into O
        //2. Update the new head location and add it to the body


        int len = snake_body.size();
        if (len > 0){
            int old_H_x = snake_body[len-1][0];
            int old_H_y = snake_body[len-1][1];

            map[old_H_y][old_H_x] = 'O';
        }

        snake_body.push_back({head_x, head_y});
        map[head_y][head_x] = '@';


        //Score board

        map[map_height-1][1] = ' ';
        map[map_height-1][2] = 'S';
        map[map_height-1][3] = 'C';
        map[map_height-1][4] = 'O';
        map[map_height-1][5] = 'R';
        map[map_height-1][6] = 'E';
        map[map_height-1][7] = ' ';
        map[map_height-1][8] = '0' + (char)score;
        map[map_height-1][9] = ' ';





    };


    // **TO-DO**

    //ACCEPT PLAYER INPUT and change the direction of travel (heading)
    //use getch()
    void PLAYER_INPUT(){

        int c = 0;

        if (kbhit()){              //If there is a key press
            switch(c = getch()){   // get the key press

                case KEY_UP:
                    heading = 'N';
                    break;
                case KEY_DOWN:
                    heading = 'S';
                    break;
                case KEY_LEFT:
                    heading = 'W';
                    break;
                case KEY_RIGHT:
                    heading = 'E';
                    break;
                default:
                    break;
            }
        }
    };









};


class SNAKE_GAME : public SNAKE{


    protected:
    //Starting location
    int i = 3;
    int j = 10;

    //Time between frames = (1/FPS)
    int Frame_time = 500;

    public:

    SNAKE_GAME(): SNAKE(3, 10){};

    //Frame time is 1000
    //For threading only
    void Frame_update(){

        this->NEXT_FRAME();
        this->PRINT();
        Sleep(Frame_time);
    };

    //This provide the function for thread to take 100 input per fram
    void INPUT_UPDATE(){

        for(int j = 0; j < 100; j++){
            this->PLAYER_INPUT();
        }


    };

    void START_GAME(){

        //*Begin*
        std::cout << "Press any key to start the snake game \n";
        getch();


        //This start the game loop
        while( !GAMEOVER ){


            std::thread T1(&SNAKE_GAME::Frame_update, this);
            std::thread T2(&SNAKE_GAME::INPUT_UPDATE, this);
            T1.join();
            T2.join();
        }

        //Ending screen
        std::cout << "\n\n\n\n\n";
        std::cout << "------------------------------------------------------\n";
        std::cout << "   _____                         ____                 \n";
        std::cout << "  / ____|                       / __ \\                \n";
        std::cout << " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ \n";
        std::cout << " | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|\n";
        std::cout << " | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   \n";
        std::cout << "  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   \n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << "Your total score: " << score << "\n";
        std::cout << "Press any key to exit: ";
        getch();



    };

};












int main() {




SNAKE_GAME GT;
GT.START_GAME();




}