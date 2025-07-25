---
 
# ✅ Complete `main.cpp` File (with Human vs Human and AI modes)
 
```cpp
#include <iostream>
#include <limits>
using namespace std;
 
char board[3][3];
 
// -------------------- Board Setup --------------------
void resetBoard() {
    char count = '0';
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = count++;
}
 
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j != 2) cout << " | ";
        }
        if (i != 2) cout << "\n-----------\n";
    }
    cout << "\n\n";
}
 
// -------------------- Game Status Checkers --------------------
char checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];
    return ' ';
}
 
bool isDraw() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}
 
// -------------------- Human vs Human Mode --------------------
void playHumanVsHuman() {
    char player = 'X';
    int move;
 
    while (true) {
        displayBoard();
        cout << "Player " << player << ", enter your move (1-9): ";
        cin >> move;
 
        if (move < 1 || move > 9) {
            cout << "Invalid move. Try again.\n";
            continue;
        }
 
        int row = (move - 1) / 3;
        int col = (move - 1) % 3;
 
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Cell already taken. Try again.\n";
            continue;
        }
 
        board[row][col] = player;
 
        char winner = checkWin();
        if (winner == 'X' || winner == 'O') {
            displayBoard();
            cout << "Player " << winner << " wins!\n";
            break;
        } else if (isDraw()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }
 
        player = (player == 'X') ? 'O' : 'X';
    }
}
 
// -------------------- Minimax AI --------------------
int evaluateBoard() {
    char winner = checkWin();
    if (winner == 'O') return +10;
    if (winner == 'X') return -10;
    return 0;
}
 
int minimax(bool isAITurn) {
    int score = evaluateBoard();
    if (score == 10 || score == -10) return score;
    if (isDraw()) return 0;
 
    if (isAITurn) {
        int best = -1000;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = 'O';
                    best = max(best, minimax(false));
                    board[i][j] = backup;
                }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = 'X';
                    best = min(best, minimax(true));
                    board[i][j] = backup;
                }
        return best;
    }
}
 
pair<int, int> findBestMove() {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};
 
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char backup = board[i][j];
                board[i][j] = 'O';
                int moveVal = minimax(false);
                board[i][j] = backup;
 
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
 
    return bestMove;
}
 
// -------------------- Human vs AI Mode --------------------
void playHumanVsAI() {
    char playerMark;
    cout << "Choose your symbol (X or O): ";
    cin >> playerMark;
 
    char aiMark = (playerMark == 'X') ? 'O' : 'X';
    bool isHumanTurn = (playerMark == 'X');
 
    while (true) {
        displayBoard();
 
        if (isHumanTurn) {
            int move;
            cout << "Your move (1-9): ";
            cin >> move;
 
            if (move < 1 || move > 9) {
                cout << "Invalid move. Try again.\n";
                continue;
            }
 
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;
 
            if (board[row][col] == 'X' || board[row][col] == 'O') {
                cout << "Cell already taken. Try again.\n";
                continue;
            }
 
            board[row][col] = playerMark;
        } else {
            cout << "AI is thinking...\n";
            pair<int, int> aiMove = findBestMove();
            board[aiMove.first][aiMove.second] = aiMark;
        }
 
        char winner = checkWin();
        if (winner == playerMark) {
            displayBoard();
            cout << "You win!\n";
            break;
        } else if (winner == aiMark) {
            displayBoard();
            cout << "AI wins!\n";
            break;
        } else if (isDraw()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }
 
        isHumanTurn = !isHumanTurn;
    }
}
 
// -------------------- Main Menu --------------------
int main() {
    int mode;
    char playAgain;
 
    do {
        resetBoard();
 
        cout << "==== Tic Tac Toe ====\n";
        cout << "1. Human vs Human\n";
        cout << "2. Human vs AI\n";
        cout << "3. Exit\n";
        cout << "Choose mode: ";
        cin >> mode;
 
        if (mode == 1) {
            playHumanVsHuman();
        } else if (mode == 2) {
            playHumanVsAI();
        } else {
            cout << "Goodbye!\n";
            break;
        }
 
        cout << "Play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
 
    return 0;
}
 