#include <iostream>
#include "../inc/Board.hh"
#include "../inc/Game.hh"


int main() {    
    // inputs
    int board_size = 3;
    int winning_size = 3;
    int human_player = TicTacToe::CIRCLE;
    int min_max_depth = 12;

    // game start
    TicTacToe::Board board(board_size, winning_size);    
    TicTacToe::game(board, human_player, min_max_depth);
    
    return 0;    
}