#include <iostream>
#include<limits>;
using namespace std;

char board[3][3];

// Initialize board
void resetBoard()
{
    char count = '1';
    for(int i=0; i<3; i+=1)
    {
        for(int j=0; j<3; j+=1)
        {
            board[i][j] = count+=1;
        }
    }
}

// Display board
void displayBoard()
{
    cout<<endl;
    
    for(int i=0; i<3; i+=1)
    {
        cout<<" ";
        for(int j=0; j<3; j++) 
        {
            cout<<board[i][j];
            if(j != 2) cout<<" | ";
        }
        if(i != 2) cout<<"\n-----------\n";
    }
    cout<<"\n\n";
}

// Check if a player has won
char checkWin() {
    for (int i = 0; i < 3; i++) {
        // Rows and columns
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];
    return ' '; // No winner yet
}
 
// Check for draw
bool isDraw() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}
 
// Human vs Human game
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
 
        // Switch player
        player = (player == 'X') ? 'O' : 'X';
    }
}
 

int main() {
    int mode;
    char playAgain;
 
    do {
        resetBoard();
 
        cout << "==== Tic Tac Toe ====\n";
        cout << "1. Human vs Human\n";
        cout << "2. Exit\n";
        cout << "Choose mode: ";
        cin >> mode;
 
        if (mode == 1) {
            playHumanVsHuman();
        } else {
            cout << "Goodbye!\n";
            break;
        }
 
        cout << "Play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
 
    return 0;
}
 