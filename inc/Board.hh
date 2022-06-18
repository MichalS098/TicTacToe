#pragma once
#include <iostream>

namespace TicTacToe {
    // game symbols macros
    constexpr int EMPTY = 0; 
    constexpr int CROSS = 1;
    constexpr int CIRCLE = 2;

    class Board {    
    private:
        int* _board;
        int _size;  
        int _winning_size;
        bool checkHorizontal(int symbol);  
        bool checkVertical(int symbol);
        bool checkDiagonal(int symbol);
    public: 
        Board();
        Board(int board_size, int winning_size);
        ~Board();
        int getSize();
        int getWinningSize();
        int* getBoard();        
        int operator()(int x, int y) const { return _board[x + _size * y];}
  	    int& operator()(int x, int y) { return _board[x + _size * y];}
        int operator()(int pos) const { return _board[pos];}
  	    int& operator()(int pos) { return _board[pos];}
        int isEnd(); 
        bool isLeftAvailableSpace();
        bool isEmpty();
        void print();    
    };    
}
