#pragma once
#include "../inc/Board.hh"
#include <iostream>

namespace TicTacToe {    
    // zmienne globalne gry
    // gracz maksymalizujacy i minimalizujacy
    constexpr int MAXIMIZING_PLAYER = CROSS;
    constexpr int MINIMIZING_PLAYER = CIRCLE;
    constexpr int INF = std::numeric_limits<int>::max();

    int staticScoreEvaluation(Board& board);    
    int minimax(Board& board, int alpha, int beta, int depth, bool is_maximizing_player);    
    int bestMove(Board& board, int player, int depth);
    void game(Board& board, int human_player, int min_max_depth);
    void printWinner(Board& board, int human_player);
}
