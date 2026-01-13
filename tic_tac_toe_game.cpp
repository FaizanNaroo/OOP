#include <iostream>
#include <limits>
#include <string>
using namespace std;

class TicTacToe {
    char **board;
    int size;      // Board size (NxN)
    int winLength; // Number of consecutive symbols needed to win
    int moves;     // Track number of moves made

public:
    TicTacToe(int s = 3) {
        if (s < 3) s = 3;
        size = s;
        moves = 0;
        if (size <= 3) winLength = 3;
        else if (size <= 5) winLength = 4;
        else winLength = 5;

        board = new char *[size];
        for (int i = 0; i < size; i++) {
            board[i] = new char[size];
            for (int j = 0; j < size; j++) board[i][j] = ' ';
        }
    }

    ~TicTacToe() {
        for (int i = 0; i < size; i++) delete[] board[i];
        delete[] board;
    }

    void display() {
        cout << "\n    ";
        for (int j = 0; j < size; j++) cout << j << "   ";
        cout << "\n";

        for (int i = 0; i < size; i++) {
            cout << i << "  ";
            for (int j = 0; j < size; j++) {
                cout << " " << board[i][j] << " ";
                if (j < size - 1) cout << "|";
            }
            cout << "\n";
            if (i < size - 1) {
                cout << "   ";
                for (int k = 0; k < size; k++) {
                    cout << "---";
                    if (k < size - 1) cout << "+";
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }

    bool checkDirection(int r, int c, int dr, int dc, char ch) {
        int count = 0, i = r, j = c;
        while (i >= 0 && i < size && j >= 0 && j < size && board[i][j] == ch) {
            count++; i -= dr; j -= dc;
        }
        i = r + dr; j = c + dc;
        while (i >= 0 && i < size && j >= 0 && j < size && board[i][j] == ch) {
            count++; i += dr; j += dc;
        }
        return count >= winLength;
    }

    bool checkWin(int r, int c, char ch) {
        if (moves < winLength * 2 - 1) return false;
        return checkDirection(r, c, 0, 1, ch) ||   // Horizontal
               checkDirection(r, c, 1, 0, ch) ||   // Vertical
               checkDirection(r, c, 1, 1, ch) ||   // Diagonal
               checkDirection(r, c, 1, -1, ch);    // Diagonal /
    }

    bool isBoardFull() { return moves >= size * size; }

    bool input(char ch, const string &playerName) {
        int x, y;
        while (true) {
            cout << playerName << " (" << ch << ") - Enter row (0-" << size - 1 << "): ";
            
            // Validate row input
            if (!(cin >> x)) {
                cout << "Invalid input! Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            
            cout << playerName << " (" << ch << ") - Enter column (0-" << size - 1 << "): ";
            
            // Validate column input
            if (!(cin >> y)) {
                cout << "Invalid input! Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            
            // Validate if position is within bounds
            if (x < 0 || x >= size || y < 0 || y >= size) {
                cout << "Invalid position! Row and column must be between 0 and " << size - 1 << ".\n";
                continue;
            }
            
            // Check if cell is already filled
            if (board[x][y] != ' ') {
                cout << "Cell already filled! Try again.\n";
                continue;
            }
            
            board[x][y] = ch;
            moves++;
            break;
        }
        return checkWin(x, y, ch);
    }

    bool playTurn(int player, const string &playerName) {
        char ch = (player == 1 ? 'X' : 'O');
        display();
        return input(ch, playerName);
    }
};

int main() {
    cout << "\n\t\t\t\t\tWelcome to Tic-Tac-Toe! \n";

    int size;
    cout << "\nEnter board size (N x N, minimum 3): ";
    while (!(cin >> size) || size < 3) {
        cout << "Invalid input! Please enter a number 3 or greater: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string player1, player2;
    cout << "==>Enter Player 1 name: "; cin >> player1;
    cout << "==>Enter Player 2 name: "; cin >> player2;

    TicTacToe game(size);
    cout << "\n\t\t\t\t\tGame started on a " << size << "x" << size << " board.\n";
    cout << "\t\t\t\t    ---(You need " << (size <= 3 ? 3 : (size <= 5 ? 4 : 5)) << " in a row to win!)---\n";

    for (int i = 0; i < size * size; i++) {
        int currentPlayer = (i % 2 == 0 ? 1 : 2);
        string currentName = (currentPlayer == 1 ? player1 : player2);

        if (game.playTurn(currentPlayer, currentName)) {
            game.display();
            cout << " " << currentName << " wins! Congratulations! \n";
            return 0;
        }

        if (game.isBoardFull()) break;
    }

    game.display();
    cout << "\nIt's a Draw! \n";
    return 0;
}
