#include <bits/stdc++.h>

using namespace std;

#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526 // (25 * 25 - 99)

int SIZE, MINES;

bool isValid(int row, int col)
{
    return (row >= 0) && (row < SIZE) && (col >= 0) && (col < SIZE);
}

class Board
{
public:
    char **board;
    Board()
    {
        board = new char *[MAXSIDE + 1];
        for (int i = 0; i <= MAXSIDE; ++i)
        {
            board[i] = new char[MAXSIDE + 1];
            for (int j = 0; j <= MAXSIDE; ++j)
                board[i][j] = '-';
        }
    }

    bool isMine(int row, int col)
    {
        if (board[row][col] == '*')
            return true;
        else
            return false;
    }

    void makeMove(int *x, int *y)
    {
        cout << "Enter move (row, column):    ";
        int X, Y;
        cin >> X >> Y;
        *x = X;
        *y = Y;
        return;
    }

    void printBoard()
    {
        int i, j;
        cout << "    ";
        for (i = 0; i < SIZE; i++)
            cout << i << " ";
        cout << '\n';
        for (i = 0; i < SIZE; i++)
        {
            cout << i << " ";
            for (j = 0; j < SIZE; j++)
                cout << board[i][j] << " ";
            cout << '\n';
        }
        return;
    }

    int countAdjacentMines(int row, int col, int mines[][2])
    {
        int i;
        int count = 0;

        int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int d = 0; d < 8; d++)
        {
            int newRow = row + dx[d];
            int newCol = col + dy[d];

            if (isValid(newRow, newCol) == true)
            {
                if (isMine(newRow, newCol) == true)
                    count++;
            }
        }
        return (count);
    }

    void placeMines(int mines[][2])
    {
        bool mark[MAXSIDE * MAXSIDE];

        memset(mark, false, sizeof(mark));

        for (int i = 0; i < MINES;)
        {
            int random = rand() % (SIZE * SIZE);
            int x = random / SIZE;
            int y = random % SIZE;

            if (mark[random] == false)
            {
                mines[i][0] = x;
                mines[i][1] = y;

                board[mines[i][0]][mines[i][1]] = '*';
                mark[random] = true;
                i++;
            }
        }
        return;
    }

    void replaceMine(int row, int col)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] != '*')
                {
                    board[i][j] = '*';
                    board[row][col] = '-';
                    return;
                }
            }
        }
        return;
    }
};

class Game
{
public:
    bool playMinesweeperUtil(Board &myBoard,
                             Board &realBoard,
                             int mines[][2], int row,
                             int col, int *movesLeft)
    {
        if (myBoard.board[row][col] != '-')
            return (false);

        int i, j;

        if (realBoard.board[row][col] == '*')
        {
            myBoard.board[row][col] = '*';
            for (i = 0; i < MINES; i++)
                myBoard.board[mines[i][0]][mines[i][1]] = '*';

            myBoard.printBoard();
            cout << "You lost!" << '\n';
            return (true);
        }
        else
        {
            int count = realBoard.countAdjacentMines(
                row, col, mines);
            (*movesLeft)--;

            myBoard.board[row][col] = count + '0';

            if (!count)
            {
                int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
                int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

                for (int d = 0; d < 8; d++)
                {
                    int newRow = row + dx[d];
                    int newCol = col + dy[d];

                    if (isValid(newRow, newCol) == true)
                    {
                        if (realBoard.isMine(newRow, newCol) == false)
                            playMinesweeperUtil(
                                myBoard, realBoard, mines,
                                newRow, newCol, movesLeft);
                    }
                }
            }
            return (false);
        }
    }

    void playMinesweeper(Board &realBoard, Board &myBoard)
    {
        bool gameOver = false;

        int movesLeft = SIZE * SIZE - MINES, x, y;
        int mines[MAXMINES][2];
        realBoard.placeMines(mines);
        int currentMoveIndex = 0;
        while (gameOver == false)
        {
            cout << "Current status of board: " << '\n';
            myBoard.printBoard();
            myBoard.makeMove(&x, &y);

            if (currentMoveIndex == 0)
            {
                if (realBoard.isMine(x, y) == true)
                    realBoard.replaceMine(x, y);
            }

            currentMoveIndex++;

            gameOver = playMinesweeperUtil(
                myBoard, realBoard, mines, x, y,
                &movesLeft);

            if ((gameOver == false) && (movesLeft == 0))
            {
                cout << "You won!" << '\n';
                gameOver = true;
            }
        }
        return;
    }
};

void chooseDifficulty()
{
    int level;

    cout << "Chose the difficulty:" << '\n';
    cout << "Press 0 for EASY 9x9" << '\n';
    cout << "Press 1 for MEDIUM 16x16" << '\n';
    cout << "Press 2 for HARD 24x24" << '\n';

    cin >> level;
    if (level == 0)
    {
        SIZE = 9;
        MINES = 10;
    }
    if (level == 1)
    {
        SIZE = 16;
        MINES = 40;
    }
    if (level == 2)
    {
        SIZE = 24;
        MINES = 99;
    }
}

int main()
{
    Board myBoard, realBoard;

    Game *game = new Game();
    chooseDifficulty();

    game->playMinesweeper(myBoard, realBoard);
    return 0;
}