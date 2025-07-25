// main_gui.cpp 
#include <SFML/Graphics.hpp> 
#include <iostream> 
#include <vector> 
#include <limits>
 
const int SIZE = 3; 
const int WINDOW_SIZE = 600; 
const int CELL_SIZE = WINDOW_SIZE / SIZE;
 
int humanPlayer = 1; // 1 for X, 2 for O 
int aiPlayer = 2; bool vsAI = true; 
int currentPlayer = 1; // 1: X, 2: O 
std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE, 0)); 
bool gameOver = false;
 
// Drawing X or O 
void drawMark(sf::RenderWindow &window, int row, int col, int player) 
{ 
  sf::Font font; 
  font.loadFromFile("arial.ttf"); 
  sf::Text text; 
  text.setFont(font); 
  text.setString(player == 1 ? "X" : "O"); 
  text.setCharacterSize(120); 
  text.setFillColor(player == 1 ? sf::Color::Red : sf::Color::Blue); 
  text.setPosition(col * CELL_SIZE + 60, row * CELL_SIZE + 30); 
  window.draw(text); 
}
 
// Check for win 
int checkWin() 
{ 
  for (int i = 0; i < SIZE; ++i) 
  { 
    if (board[i][0] && board[i][0] == board[i][1] && board[i][1] == board[i][2])
      return board[i][0]; 
    if (board[0][i] && board[0][i] == board[1][i] && board[1][i] == board[2][i]) 
      return board[0][i]; 
  } 
  if (board[0][0] && board[0][0] == board[1][1] && board[1][1] == board[2][2]) 
    return board[0][0]; 
  if (board[0][2] && board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
    return board[0][2]; 
  return 0; 
}
 
bool isFull() 
{ 
  for (auto &row : board) 
    for (int cell : row) 
      if (cell == 0) 
        return false; 
  return true; 
}
 
int minimax(std::vector<std::vector<int>> &b, int depth, bool isMaximizing) 
{ 
  int winner = checkWin(); 
  if (winner == aiPlayer) return 10 - depth; 
  if (winner == humanPlayer) return depth - 10; 
  if (isFull()) return 0;
 
int best = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
 
for (int i = 0; i < SIZE; ++i) 
{
    for (int j = 0; j < SIZE; ++j) 
    {
        if (b[i][j] == 0) 
        {
            b[i][j] = isMaximizing ? aiPlayer : humanPlayer;
            int score = minimax(b, depth + 1, !isMaximizing);
            b[i][j] = 0;
            best = isMaximizing ? std::max(best, score) : std::min(best, score);
        }
    }
}
return best;
 
}
 
std::pair<int, int> findBestMove() 
{ 
  int bestScore = std::numeric_limits<int>::min(); 
  std::pair<int, int> move = {-1, -1}; 
  for (int i = 0; i < SIZE; ++i) 
  { 
    for (int j = 0; j < SIZE; ++j) 
    { 
      if (board[i][j] == 0) 
      { 
        board[i][j] = aiPlayer; 
        int score = minimax(board, 0, false); 
        board[i][j] = 0; 
        if (score > bestScore) 
        { 
          bestScore = score; 
          move = {i, j}; 
        } 
      } 
    } 
  } 
  return move; 
}
 
int main() 
{ 
  std::cout << "Choose your symbol (X or O): "; 
  char choice; 
  std::cin >> choice; 
  if (choice == 'O' || choice == 'o') 
  { 
    humanPlayer = 2; 
    aiPlayer = 1; 
  }
 
sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Tic Tac Toe - SFML AI");
 
sf::Font font;
font.loadFromFile("arial.ttf");
 
while (window.isOpen()) 
{
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed)
            window.close();
 
        if (!gameOver && event.type == sf::Event::MouseButtonPressed && currentPlayer == humanPlayer) 
        {
            int x = event.mouseButton.x / CELL_SIZE;
            int y = event.mouseButton.y / CELL_SIZE;
 
            if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[y][x] == 0) 
            {
                board[y][x] = humanPlayer;
                if (checkWin() || isFull()) gameOver = true;
                currentPlayer = aiPlayer;
            }
        }
    }
 
    // AI Turn
    if (!gameOver && vsAI && currentPlayer == aiPlayer) 
    {
        auto [row, col] = findBestMove();
        if (row != -1 && col != -1) 
        {
            board[row][col] = aiPlayer;
            if (checkWin() || isFull()) gameOver = true;
            currentPlayer = humanPlayer;
        }
    }
 
    window.clear(sf::Color::White);
 
    // Draw grid
    sf::RectangleShape line;
    for (int i = 1; i < SIZE; ++i) 
    {
        line.setSize(sf::Vector2f(WINDOW_SIZE, 5));
        line.setPosition(0, i * CELL_SIZE);
        line.setFillColor(sf::Color::Black);
        window.draw(line);
 
        line.setSize(sf::Vector2f(5, WINDOW_SIZE));
        line.setPosition(i * CELL_SIZE, 0);
        line.setFillColor(sf::Color::Black);
        window.draw(line);
    }
 
    // Draw X/O
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j])
                drawMark(window, i, j, board[i][j]);
 
    window.display();
}
return 0;
 
}
 
