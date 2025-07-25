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
        for(int j=0; j<3; j+=1)
        {
            cout<<board[i][j];
            if(j != 2) cout<<" | ";
        }
        if(i != 2) cout<<"\n-----------\n";
    }
    cout<<"\n\n";
}