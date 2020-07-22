/*

Project ended on 22/7/2020 1200HR HKT
Copyright by Morgan Cheng

This is just a simple console Tic Tae Teo project
Easy to build and fun to play. Encourage any coding beginner to try it.


*/


#include <iostream>
#include <string>
#include <conio.h>



class DISPLAY {


    char board[3][3];
    bool P1_win = false;
    bool P2_win = false;
    bool P1_turn = true;
    int counter = 0;


    public:
    DISPLAY() {
        /*create the number code for the display*/

        for (int j = 1; j < 10 ; j++){

            if (j % 3 != 0){
                board[j/3][j % 3 - 1 ] = '0' + j;
            }
            else {
                board[j/3 - 1][ 2 ] = '0' + j;
            }



        }



    };

    void DRAW(){
        /*Draw the 3x3 board and number code each square */
        std::cout << " Player 1 \"O\"  vs   Player 2 \"X\" \n\n";



        std::cout << "           |       |       \n";
        std::cout << "       " << board[0][0] << "   |   " << board[0][1] << "   |   " << board[0][2] << "   \n";
        std::cout << "           |       |       \n";
        std::cout << "    ———————+———————+———————\n";
        std::cout << "           |       |       \n";
        std::cout << "       " << board[1][0] << "   |   " << board[1][1] << "   |   " << board[1][2] << "   \n";
        std::cout << "           |       |       \n";
        std::cout << "    ———————+———————+———————\n";
        std::cout << "           |       |       \n";
        std::cout << "       " << board[2][0] << "   |   " << board[2][1] << "   |   " << board[2][2] << "   \n";
        std::cout << "           |       |       \n";


    };

    bool update(int i, char input){
        /*Insert the O/X into the board*/
        /* return T if the board was updated*/


        if (input != 'O' and input != 'X'){
            return false;
        }
        else if (i % 3 != 0 and (board[i/3][i % 3 - 1 ] != 'O' and board[i/3][i % 3 - 1 ] != 'X')){
            board[i/3][i % 3 - 1 ] = input;
            return true;
        }
        else if (i % 3 == 0 and ( board[i/3 - 1][ 2 ] != 'O' and board[i/3 - 1][ 2 ] != 'X') ) {
            board[i/3 - 1][ 2 ] = input;
            return true;
        }

        return false;
    };

    char WIN_CHECK(){
        /*check whether P1 or P2 has won */
        /* return N: no players win, O: P1 win, X: P2 win*/

        for (int i = 0; i < 3; i++){

            if (board[i][0] == board[i][1] and board[i][2] == board[i][1]){
                return board[i][0];
            }
            else if (board[0][i] == board[1][i] and board[2][i] == board[1][i]){
                return board[0][i];
            }
            else if (board[0][0] == board[1][1] and board[2][2] == board[1][1]){
                return board[1][1];
            }
            else if (board[0][2] == board[1][1] and board[2][0] == board[1][1]){
                return board[1][1];
            }

        }
        return 'N';
    };

    void TIC_GAME(){

        std::cout << " _____ _        _____            _____          \n";
        std::cout << "|_   _(_)      |_   _|          |_   _|         \n";
        std::cout << "  | |  _  ___    | | __ _  ___    | | ___   ___ \n";
        std::cout << "  | | | |/ __|   | |/ _` |/ __|   | |/ _ \\ / _ \\\n";
        std::cout << "  | | | | (__    | | (_| | (__    | | (_) |  __/\n";
        std::cout << "  \\_/ |_|\\___|   \\_/\\__,_|\\___|   \\_/\\___/ \\___|\n";
        std::cout << "                                                \n";
        std::cout << "\n";
        std::cout << "Press any key to start\n";
        getch();



        bool round_not_updated = true;

        while ((!P1_win and !P2_win) and counter != 9)
        {
            //Set Player number, char and null loaction N
            int user_in = 0;
            std::string error_message = "";
            std::string Player_no = P1_turn? "1" : "2";
            char Player_char = P1_turn? 'O' : 'X';

            while(round_not_updated){


                std::cout << "\n\n🝪———————————————————————————————🝪\n";
                this->DRAW();
                std::cout << error_message;
                std::cout << "\nIt is Player " << Player_no << " turn! Enter a block you want to take: " ;
                std::cin >> user_in;

                round_not_updated = !this->update(user_in, Player_char);

                if (round_not_updated){
                    error_message =  "🜍Error🜍 Player " + Player_no + " Please enter a valid location!";
                }

            }

            P1_turn = !P1_turn;
            round_not_updated = !round_not_updated;
            counter++;

            if (this->WIN_CHECK() == 'O'){
                P1_win = true;
            }
            else if (this->WIN_CHECK() == 'X'){
                P2_win = true;
            }
        }
        std::cout << "\n\n🝪——————————————————————————————🝪\n";
        std::cout << "        This round ends\n\n";
        this->DRAW();



        if (P1_win){
            std::cout << "🜍 Player 1 win!! Congrets!! 🜍\n";
        }
        else if (P2_win){
            std::cout << "🜍 Player 2 win!! Congrets!! 🜍\n";
        }
        else
        {
            std::cout << "🜍 It is a draw! 🜍 \n";
        }

        std::cout << "🜍———————————————————————————————🜍\n";

        std::cout << "Press any key to exit\n";
        getch();
    };






};



int main(){

    DISPLAY A;
    A.TIC_GAME();
    return 0;
}


