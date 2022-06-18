#include <iostream>
#include "../inc/Board.hh"
#include "../inc/Game.hh"

// kolejnosc wykonywania funkcji w programie:
// funkcja game() to glowna petla gry ona wywoluje funkcje bestMove()
// a funkcja bestMove() odpala minimaxa

int main() {    
    // inputs
    int board_size = 3;
    int winning_size = 3;
    int human_player = TicTacToe::CIRCLE;
    int min_max_depth = 8;

    // std::cout << "Wybierz rozmiar planszy:" << std::endl;
    // std::cout << "1. 3x3" << std::endl;
    // std::cout << "2. 4x4" << std::endl;
    // std::cout << "3. ..." << std::endl;
    // std::cout << "..." << std::endl;
    // std::cin >> board_size;
    // board_size+=2;
    // std::cout << "Wybierz ilosc znakow wygrywajacych:" << std::endl;
    // int n =0;
    // for (int i = 3; i <= board_size; ++i)
    // {
    //     n++;
    //     std::cout <<n<< ". " <<board_size<< std::endl;
    // }
    // std::cin >> winning_size;
    // winning_size+=2;    
    // std::cout << "Wybierz gracza:" << std::endl;
    // std::cout << "1. Krzyzyk" << std::endl;
    // std::cout << "2. Kolko" << std::endl;
    // std::cin >> human_player;

    // game start
    TicTacToe::Board board(board_size, winning_size);    
    TicTacToe::game(board, human_player, min_max_depth);
    
    return 0;    
}