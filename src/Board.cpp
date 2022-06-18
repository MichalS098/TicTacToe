#include "../inc/Board.hh"
#include <stdio.h>

using namespace TicTacToe;

Board::Board() {   
    _size = 3;    
    _winning_size = 3;
    _board = new int[9];
    for (int i = 0; i < 9; ++i) {   
        _board[i] = EMPTY;
    }    
}

Board::Board(int board_size, int winning_size) {    
    if(board_size < 3 || board_size > 10) {
        std::cout << "Invalid board size ("<<board_size<<")"<<std::endl;
    }
    if(winning_size < 3 || winning_size > board_size) {
        std::cout << "Invalid winning size ("<<winning_size<<")"<<std::endl;
    }
    _size = board_size;    
    _winning_size = winning_size;
    _board = new int[board_size * board_size];
    for (int i = 0; i < board_size * board_size; ++i) {   
        _board[i] = EMPTY;
    }    
}

Board::~Board() {
    delete[] _board;
}

int Board::getSize() {
    return _size;
}

int Board::getWinningSize() {
    return _winning_size;
}

int* Board::getBoard() {
    return _board;
}

bool Board::checkHorizontal(int symbol) {    
    int count = 0;
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if(_board[j + _size * i] == symbol) {
                ++count;                
            }
            else if (count == _winning_size) {
                return true;
            }
            else {
                count = 0;
            }
        }
        if(count == _winning_size) {
            return true;
        }
        else {
            count = 0;
        }
    }     
    return false;    
}

bool Board::checkVertical(int symbol) {
    int count = 0;
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            if(_board[i + _size * j] == symbol) {
                ++count;
            }
            else if(count == _winning_size) {
                return true;
            }
            else {
                count = 0;
            }            
        }
        if(count == _winning_size) {
            return true;
        }
        else {
            count = 0;
        }
    }
    return false;    
}

bool Board::checkDiagonal(int symbol) {
    int count = 0;
    for (int i = 0; i < _size; ++i) {
        if(_board[i + _size * i] == symbol) {
            ++count;
        }
        else if(count == _winning_size) {
            return true;
        }
        else {
            count = 0;
        }        
    }
    if(count == _winning_size) {
        return true;
    }
    else {
        count = 0;
    }
    for (int i = 0; i < _size; ++i) {
        if(_board[_size*(i+1) - 1 - i] == symbol) {
            ++count;
        }
        else if(count == _winning_size) {
            return true;
        }
        else {
            count = 0;
        }        
    }
    if(count == _winning_size) {
        return true;
    }
    else {
        count = 0;
    }
    return false;  
}

/**
 * @brief Check if game is end
 * 
 * @return unsigned int 0 - isnt end, 1 - cross win, 2 - circle win
 */
int Board::isEnd() {    
    if (checkHorizontal(CROSS) || checkVertical(CROSS) || checkDiagonal(CROSS)) {
        return CROSS;
    }
    else if (checkHorizontal(CIRCLE) || checkVertical(CIRCLE) || checkDiagonal(CIRCLE)) {
        return CIRCLE;
    }
    else {
        return EMPTY;
    }
}

/**
 * @brief return true i
 * 
 * @return int 
 */
bool Board::isLeftAvailableSpace() {
    for (int i = 0; i < _size * _size; ++i) {
        if(_board[i] == EMPTY) {
            return true;
        }
    }
    return false;
}


void Board::print() {
    int val;
    std::cout << "|";
    for (int i = 0; i < _size; ++i) {
        std::cout << "----";        
    }    
    std::cout << "|" << std::endl;
    std::cout << "|";
    for (int i = 0; i < _size; ++i) {
        std::cout << " "<<i<<"  ";        
    }    
    std::cout << "|" << std::endl;
    std::cout << "|";
    for (int i = 0; i < _size; ++i) {
        std::cout << "----";        
    }    
    std::cout << "|" << std::endl;
    for(int i = 0; i < _size; ++i) {
        for(int j = 0; j < _size; ++j) {
            std::cout << "|";
            val = _board[j + _size * i];            
            if(val == EMPTY) {
                std::cout << "   ";
            }
            else if(val == CROSS) {
                std::cout << " x ";
            }
            else if(val == CIRCLE) {
                std::cout << " o ";
            }            
        }
        std::cout << "|";
        std::cout<<std::endl;                
        std::cout << "|";
        for (int i = 0; i < _size; ++i) {
            std::cout << "---";        
        }
        for (int i = 0; i < _size-1; ++i) {
            std::cout << "-";        
        }
        std::cout << "|" << std::endl;    
    }    
}

bool Board::isEmpty() {
    for (int i = 0; i < _size * _size; ++i) {
        if(_board[i] != EMPTY) {
            return false;
        }
    }
    return true;
}