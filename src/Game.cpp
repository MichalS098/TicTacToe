#include "../inc/Game.hh"
#include <stdlib.h>     /* srand, rand */
#include <time.h>  



/**
 * @brief Funkcja heurystyczna obliczajaca
 * wynik gry w kolko i krzyzyk.
 * 
 * @param board plansza gry 
 * @return int zwraca wynik gry
 */
int TicTacToe::staticScoreEvaluation(TicTacToe::Board& board) {    
    int evaluation = 0;
    int count_x = 0;
    int count_o = 0;
    int* lines_with_n_x = new int[board.getWinningSize() - 1];
    int* lines_with_n_o = new int[board.getWinningSize() - 1];

    for (int i = 0; i < board.getWinningSize() - 1; ++i) {
        lines_with_n_x[i] = 0;
        lines_with_n_o[i] = 0;
    }
    
    for (int row=0; row<board.getSize(); ++row) {
        for (int col=0; col<board.getSize(); ++col) {
            if (board(col, row) == TicTacToe::CROSS) {
                count_x++;
            } 
            else if (board(col, row) == TicTacToe::CIRCLE) {
                count_o++;
            }                        
        }
        if (count_x != 0) {
            lines_with_n_x[count_x-1]++;
            count_x = 0;    
        }
        if (count_o != 0) {
            lines_with_n_o[count_o-1]++;
            count_o = 0;    
        }
    }

    for (int col=0; col<board.getSize(); ++col) {
        for (int row=0; row<board.getSize(); ++row) {
            if (board(col, row) == TicTacToe::CROSS) {
                count_x++;
            } 
            else if (board(col, row) == TicTacToe::CIRCLE) {
                count_o++;
            }                        
        }
        if (count_x != 0) {
            lines_with_n_x[count_x-1]++;
            count_x = 0;    
        }
        if (count_o != 0) {
            lines_with_n_o[count_o-1]++;
            count_o = 0;    
        }
    }

    for (int i=0; i<board.getSize(); ++i) {
        if (board(i, i) == TicTacToe::CROSS) {
            count_x++;
        } 
        else if (board(i, i) == TicTacToe::CIRCLE) {
            count_o++;
        }                        
    }
    if (count_x != 0) {
        lines_with_n_x[count_x-1]++;
        count_x = 0;    
    }
    if (count_o != 0) {
        lines_with_n_o[count_o-1]++;
        count_o = 0;    
    }

    for (int i=0; i<board.getSize(); ++i) {
        if (board(board.getSize()-1-i, i) == TicTacToe::CROSS) {
            count_x++;
        } 
        else if (board(board.getSize()-1-i, i) == TicTacToe::CIRCLE) {
            count_o++;
        }                        
    }
    if (count_x != 0) {
        lines_with_n_x[count_x-1]++;
        count_x = 0;    
    }
    if (count_o != 0) {
        lines_with_n_o[count_o-1]++;
        count_o = 0;    
    }

    for (int i = 0; i < board.getWinningSize()-1; ++i) {
        evaluation += (i+1) * (lines_with_n_x[i] - lines_with_n_o[i]);
    }
    return evaluation;
}



/**
 * @brief Algorytm minimax zwracajaca wartosc gry dla danego stanu gry.
 * 
 * @param board plansza gry
 * @param player gracz
 * @param alpha 
 * @param beta 
 * @param depth glebokosc szukania algorytmu
 * @return int Wartosc wyniku gry
 */
int TicTacToe::minimax(TicTacToe::Board& board, int player, int alpha, int beta, int depth) {     
    // sprawdz czy koniec gry i kto wygral
    int winner = board.isEnd();
    if(winner == TicTacToe::MAXIMIZING_PLAYER) {
        return TicTacToe::INF;
    }
    else if(winner == TicTacToe::MINIMIZING_PLAYER) {
        return -TicTacToe::INF;
    }

    // sprawdz czy sa jeszcze mozliwe ruchy lub koniec glebokosci szukania
    if(board.isLeftAvailableSpace() == false || depth == 0) {
        return staticScoreEvaluation(board);        
    }        

    // change player
    player = (player == TicTacToe::MAXIMIZING_PLAYER) ? TicTacToe::MINIMIZING_PLAYER : TicTacToe::MAXIMIZING_PLAYER;
    int best_score = (player == TicTacToe::MAXIMIZING_PLAYER) ? -TicTacToe::INF : TicTacToe::INF;

    for (int row=0; row<board.getSize(); ++row) {
        for (int col=0; col<board.getSize(); ++col) {
            if (board(col, row) == TicTacToe::EMPTY) {
                if (player == TicTacToe::MAXIMIZING_PLAYER) {
                    board(col, row) = player;
                    int score = minimax(board, player, alpha, beta, depth-1);
                    best_score = std::max(best_score, score);
                    alpha = std::max(alpha, best_score);
                    board(col, row) = TicTacToe::EMPTY;
                    if (alpha >= beta) {
                        return best_score;
                    }                    
                }
                else {
                    board(col, row) = player;
                    int score = minimax(board, player, alpha, beta, depth-1);
                    best_score = std::min(best_score, score);
                    beta = std::min(beta, best_score);
                    board(col, row) = TicTacToe::EMPTY;
                    if (alpha >= beta) {
                        return best_score;
                    }                                     
                }
            }
        }
    }    
    return best_score;
}



/**
 * @brief funkcja szuka najlepszego ruchu dla podanego gracza player
 * na planszy board, uzywa do tego algorytmu minmax wiec podajemy rowniez glebokosc    
 * 
 * @param board plansza gry
 * @param player Gracz dla ktorego ruch ma byc najlepszy
 * @param depth glebokosc szukania algorytmu minmax
 * @return int zwraca ruch w postaci indeksu wiersza i kolumny
 */
int TicTacToe::bestMove(TicTacToe::Board& board, int player, int depth) {    
    // best score ma wartosc przeciwna do maksymalnej wartosci gry dla danego gracza
    int best_score = (player == TicTacToe::MAXIMIZING_PLAYER) ? -TicTacToe::INF : TicTacToe::INF;         
    int temp_score = 0;
    // najlepszy ruch ustawiamy wstepnie na niemozliwy
    int best_move = -1;

    for (int row=0; row<board.getSize(); ++row) {
        for (int col=0; col<board.getSize(); ++col) {
            if (board(col, row) == TicTacToe::EMPTY) {
                board(col, row) = player;                
                if(player == TicTacToe::MAXIMIZING_PLAYER) {
                    temp_score = minimax(board, player, -TicTacToe::INF, TicTacToe::INF, depth);                    
                    if(temp_score > best_score) {
                        best_score = temp_score;
                        best_move = row * board.getSize() + col;
                    }
                }
                else {
                    temp_score = minimax(board, player, TicTacToe::INF, -TicTacToe::INF, depth);
                    if(temp_score < best_score) {
                        best_score = temp_score;
                        best_move = row * board.getSize() + col;
                    }
                }                
                board(col, row) = TicTacToe::EMPTY;
            }
        }
    }    
    return best_move;
}


/**
 * @brief Glowna petla gry.
 * 
 * @param board plansza gry
 * @param human_player symbol gracza ktory bedzie gral z komputerem
 * @param min_max_depth glebokosc szukania algorytmu minmax
 */
void TicTacToe::game(TicTacToe::Board& board, int human_player, int min_max_depth) {                
    // pierwszy ruch ma krzyzyk
    int player = TicTacToe::CROSS;
    int x, y;    
    char enter_text[] = "Wprowadz wspolrzedne: ";

    while (board.isEnd() == TicTacToe::EMPTY) {
        if (board.isLeftAvailableSpace() == false) {         
            break;
        }
        board.print();
        std::cout << std::endl << "Runda " << (player==TicTacToe::CROSS ? "krzyzyk" : "kolko") << std::endl;
        if(player == human_player) {
            std::cout << enter_text;
            while(true) {
                std::cin >> x >> y;            
                if(x >= board.getSize() || y >= board.getSize()) {
                    std::cout << "Niepoprawna pozycja" << std::endl;
                    std::cout << enter_text;
                }
                else if(board(x, y) != TicTacToe::EMPTY) {
                    std::cout << "Pozycja zajęta" << std::endl;
                    std::cout << enter_text;
                }                
                else {
                    break;
                }            
            }
            board(x, y) = player;
        }
        else {            
            if (board.isEmpty()) {                
                srand(time(NULL));
                x = rand() % board.getSize();
                y = rand() % board.getSize();
                board(x, y) = player;
            } 
            else {
                board(bestMove(board, player, min_max_depth)) = player;
            }
        }            
        player = (player == TicTacToe::CROSS) ? TicTacToe::CIRCLE : TicTacToe::CROSS;
    }     
    board.print();
    TicTacToe::printWinner(board, human_player);
}


/**
 * @brief Funkcja wyswietla wynik gry w terminalu.
 * 
 * @param board plansza gry
 */
void TicTacToe::printWinner(TicTacToe::Board& board, int human_player) {
    int symbol = board.isEnd();
    if(symbol == TicTacToe::CROSS) {
        std::cout << "Krzyzyk wygral!" << std::endl;
        if(human_player == TicTacToe::CROSS) {
            std::cout << "Wygrales!" << std::endl;
        }
        else {
            std::cout << "Przegrales!" << std::endl;
        }
    }
    else if(symbol == TicTacToe::CIRCLE) {
        std::cout << "Kolko wygralo!" << std::endl;
        if(human_player == TicTacToe::CIRCLE) {
            std::cout << "Wygrales!" << std::endl;
        }
        else {
            std::cout << "Przegrales!" << std::endl;
        }
    }
    else {
        std::cout << "Remis" << std::endl;
    }
}