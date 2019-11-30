//Name: Aastha Lamichhane
//File: project.cpp

#include <iostream>
#include <cstring>

const int SIZE = 8;
bool BLACK_PASS = false;
bool WHITE_PASS = false;
bool turn1 = true;
bool turn2 = true;
void help();
void play(int board[SIZE][SIZE]);
void load(int board[SIZE][SIZE]);
void setUp();
void toUpperCase(char &option);
void checkFor0and1(int row, int column, int value, int board[SIZE][SIZE], char player[SIZE]);
void printArray(int board[SIZE][SIZE]);
void printMessage(char &option);
void changeToInt(char input[SIZE], int &row, int &column, bool &check);
void flip(int board[SIZE][SIZE], int row, int column, bool &canFlip);
void won(int board[SIZE][SIZE]);
void init(int board[SIZE][SIZE]);


void init(int board[SIZE][SIZE])
{
    turn1 = true;
    turn2 = true;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = 3;
        }
    }
    int middle = SIZE / 2;
    board[middle - 1][middle - 1] = 0;
    board[middle][middle] = 0;
    board[middle - 1][middle] = 1;
    board[middle][middle - 1] = 1;
}


int main()
{
    char option;
    int board[SIZE][SIZE];
    
    printMessage(option);
    init(board);
    
    
    while (option != 'Q')
    {
        switch (option)
        {
            case 'P':
                init(board);
                printArray(board);
                play(board);
                break;
            case 'L':
                load(board);
                break;
            case 'S':
                std::cout << "To be implemented\n";
                break;
            case '?':
                help();
                break;
        }
        
        printMessage(option);
    }
    
    std::cout << "Thanks for playing Super Othello Version 0.1\n";
    return 0;
}




void play(int board[SIZE][SIZE])
{
    bool finish = false, check = true;
    char player1[] = "BLACK\0", player2[] = "WHITE\0";
    char input[SIZE];
    int row, column;
    
    while (finish != true)
    {
        BLACK_PASS = false;
        WHITE_PASS = false;
        if (turn1)
        {
            std::cout << player1 << "'s turn: (@)\n";
            std::cin >> input;
            toUpperCase(input[0]);
            if (input[0] == 'Q')
            {
                won(board);
                finish = true;
                break;
            }
            changeToInt(input, row, column, check);
            if (check)
            {
                checkFor0and1(row, column, 0, board, player1);
            }
        
            printArray(board);
            turn1 = false;
            turn2 = true;
        }
        
        if (turn2)
        {
            std::cout << player2 << "'s turn: (O)\n";
            std::cin >> input;
            toUpperCase(input[0]);
            if (input[0] == 'Q')
            {
                won(board);
                finish = true;
                break;
            }
            changeToInt(input, row, column, check);
            if (check)
            {
                checkFor0and1(row, column, 1, board, player2);
            }
        
            printArray(board);
            turn2 = false;
            turn1 = true;
        }
        
        if (BLACK_PASS && WHITE_PASS)
        {
            std::cout << "Turn passed twice. Game over!\n";
            won(board);
            finish = true;
        }
        else
        {
            int count = 0;
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    if (board[i][j] == 3)
                    {
                        break;
                    }
                    else
                    {
                        count++;
                    }
                }
            }
            if (count == 64)
            {
                std::cout << "All box are full\n";
                won(board);
                finish = true;
            }
        }
    }
}


void help()
{
    std::cout << "The official rules can be found at\n"
        << "http://en.wikipedia.org/wiki/Reversi\n\n"
        << "The Othello board is set up in the following manner\n\n"
        << "  ABCDEFGH\n"
        << " +--------+\n"
        << "1|        |1\n"
        << "2|        |2\n"
        << "3|        |3\n"
        << "4|   O@   |4\n"
        << "5|   @O   |5\n"
        << "6|        |6\n"
        << "7|        |7\n"
        << "8|        |8\n"
        << " +--------+\n"
        << "  ABCDEFGH\n\n"
        << "BLACK plays @ and WHITE plays O. Players take turn in entering\n"
        << "moves. The first player to enter a move is BLACK. To place a @\n"
        << "at row 6 and column E, BLACK enters 6E. The result of the move\n"
        << "is\n\n"
        << "  ABCDEFGH\n"
        << " +--------+\n"
        << "1|        |1\n"
        << "2|        |2\n"
        << "3|        |3\n"
        << "4|   O@   |4\n"
        << "5|   @@   |5\n"
        << "6|   @    |6\n"
        << "7|        |7\n"
        << "8|        |8\n"
        << " +--------+\n"
        << "  ABCDEFGH\n\n"
        << "Note that the WHITE piece at E5 is now a BLACK piece.\n\n";
}


void load(int board[SIZE][SIZE])
{
    printArray(board);
    play(board);
}


void setUp()
{
    
}


void toUpperCase(char &option)
{
    if (option >= 97 && option <=122)
    {
        option -= 32;
    }
}


void checkFor0and1(int row, int column, int value, int board[SIZE][SIZE], char player[SIZE])
{
    bool check = true;
    if (row > 0 && row < SIZE && column == 0)
    {
        if (board[row + 1][column] != value && board[row][column + 1] != value
            && board[row + 1][column + 1] != value && board[row - 1][column] != value
             && board[row - 1][column + 1] != value)
        {
            check = false;
        }
    }
    else if (row == 0 && column > 0 && column < SIZE)
    {
        if (board[row + 1][column] != value && board[row][column + 1] != value
            && board[row + 1][column + 1] != value && board[row][column - 1] != value
            && board[row + 1][column - 1] != value)
        {
            check = false;
        }
    }
    else if (row == 7 && column > 0 && column < SIZE)
    {
        if (board[row][column + 1] != value && board[row - 1][column] != value
            && board[row][column - 1] != value && board[row - 1][column - 1] != value
            && board[row - 1][column + 1] != value)
        {
            check = false;
        }
    }
    else if (row > 0 && row < SIZE && column == 7)
    {
        if (board[row + 1][column] != value && board[row - 1][column] != value
        && board[row][column - 1] != value && board[row - 1][column - 1] != value
        && board[row + 1][column - 1] != value)
        {
            check = false;
        }
    }
    else if (row == 0 && column == 0)
    {
        if (board[row + 1][column] != value && board[row][column + 1] != value && board[row + 1][column + 1] != value)
        {
            check = false;
        }
    }
    else if (row == 0 && column == 7)
    {
        if (board[row + 1][column] != value && board[row][column - 1] != value && board[row - 1][column - 1] != value)
        {
            check = false;
        }
    }
    else if (row == 7 && column == 0)
    {
        if (board[row - 1][column] != value && board[row][column + 1] != value && board[row - 1][column - 1] != value)
        {
            check = false;
        }
    }
    else if (row == 7 && column == 7)
    {
        if (board[row - 1][column] != value && board[row][column - 1] != value && board[row - 1][column - 1] != value)
        {
            check = false;
        }
    }
    else
    {
        if (board[row + 1][column] != value && board[row][column + 1] != value
            && board[row + 1][column + 1] != value && board[row - 1][column] != value
            && board[row][column - 1] != value && board[row - 1][column - 1] != value
            && board[row + 1][column - 1] != value && board[row - 1][column + 1] != value)
        {
            check = false;
        }
    }
    
    if (check)
    {
        bool canFlip = false;
        board[row][column] = (value == 1 ? 0 : 1);
        flip(board, row, column, canFlip);
        if (!canFlip)
        {
            board[row][column] = 3;
            std::cout << "Cannot make this move\n";
            if (player[0] == 'B')
            {
                BLACK_PASS = true;
            }
            else
            {
                WHITE_PASS = true;
            }
        }
    }
    else
    {
        std::cout << "Cannot make this move\n";
        if (player[0] == 'B')
        {
            BLACK_PASS = true;
        }
        else
        {
            WHITE_PASS = true;
        }
    }
}


void printArray(int board[SIZE][SIZE])
{
    std::cout << "  A B C D E F G H \n"
        << " +----------------+\n";
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << (i + 1);
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << "|";
            if (board[i][j] != 0 && board[i][j] != 1)
            {
                std::cout << " ";
            }
            else
            {
                std::cout << (board[i][j] == 0 ? 'O' : '@');
            }
        }
        std::cout << "|" << (i + 1) << "\n";
    }
    std::cout << " +----------------+\n"
    << "  A B C D E F G H \n\n";
}


void printMessage(char &option)
{
    std::cout << "Welcome to Super Othello Version 0.1\n"
    << "by Aastha Lamichhane \n\n"
    << "[?] Help\n"
    << "[P/p] Play a new game\n"
    << "[L/l] Load a previous game\n"
    << "[S/s] Setup the board\n"
    << "[Q/q] Quit\n";
    
    std::cout << "Enter option: ";
    std::cin >> option;
    std::cout << "\n";
    toUpperCase(option);
}


void changeToInt(char input[SIZE], int &row, int &column, bool &check)
{
    int count = 0;
    char test = input[0];
    for (int i = 0; i < SIZE; i++)
    {
        if (input[i] == '\0')
        {
            break;
        }
        else
        {
            count++;
        }
    }
    if (count > 2)
    {
        std::cout << "Wrong Input\n";
        check = false;
    }
    else
    {
        row = input[1] - '0';
        row -= 1;
        std::cout << "Row: " << row << "\n";
        
        toUpperCase(test);
        column = test - 'A';
        check = true;
        std::cout << "Column: " << column << "\n";
    }
}


void flip(int board[SIZE][SIZE], int row, int column, bool &canFlip)
{
    int tempRow = row;
    int tempColumn = column;
    bool found;
    bool flippedAlready = false;
    
    for (int i = column; i >= 0; i--)
    {
        if (board[row][i] == board[row][column] && i != column && !flippedAlready)
        {
            for (int j = i + 1; j < column; j++)
            {
                if (board[row][j] == 0)
                {
                    board[row][j] = 1;
                    canFlip = true;
                    flippedAlready = true;
                }
                else if (board[row][j] == 1)
                {
                    board[row][j] = 0;
                    canFlip = true;
                    flippedAlready = true;
                }
                else
                {
                    break;
                }
            }
        }
    }
    
    flippedAlready = false;
    for (int i = column; i <= SIZE; i++)
    {
        if (board[row][i] == board[row][column] && i != column && !flippedAlready)
        {
            for (int j = column + 1; j < i; j++)
            {
                if (board[row][j] == 0)
                {
                    board[row][j] = 1;
                    canFlip = true;
                    flippedAlready = true;
                }
                else if (board[row][j] == 1)
                {
                    board[row][j] = 0;
                    canFlip = true;
                    flippedAlready = true;
                }
                else
                {
                    break;
                }
            }
        }
    }
    
    flippedAlready = false;
    for (int i = row; i >= 0; i--)
    {
        if (board[i][column] == board[row][column] && i != row && !flippedAlready)
        {
            for (int j = i + 1; j < row; j++)
            {
                if (board[j][column] == 0)
                {
                    board[j][column] = 1;
                    canFlip = true;
                    flippedAlready = true;
                }
                else if (board[j][column] == 1)
                {
                    board[j][column] = 0;
                    canFlip = true;
                    flippedAlready = true;
                }
                else
                {
                    break;
                }
            }
        }
    }
    
    flippedAlready = false;
    for (int i = row; i <= SIZE; i++)
    {
        if (board[i][column] == board[row][column] && i != row && !flippedAlready)
        {
            for (int j = row + 1; j < i; j++)
            {
                if (board[j][column] == 0)
                {
                    board[j][column] = 1;
                    canFlip = true;
                    flippedAlready = true;
                }
                else if (board[j][column] == 1)
                {
                    board[j][column] = 0;
                    canFlip = true;
                    flippedAlready = true;
                }
                else
                {
                    break;
                }
            }
        }
    }
    
    flippedAlready = false;
    for (int i = 1; i < SIZE; i++)
    {
        if (board[row - i][column - i] == board[row][column] && row - i >= 0 && column - i >=0 && !flippedAlready)
        {
            for (int j = 1; j < i; j++)
            {
                if (board[row - j][column - j] == 1)
                {
                    board[row - j][column - j] = 0;
                    canFlip = true;
                    flippedAlready = true;
                }
                else if (board[row - j][column - j] == 0)
                {
                    board[row - j][column - j] = 1;
                    canFlip = true;
                    flippedAlready = true;
                }
                else
                {
                    break;
                }
            }
        }
    }
    
    flippedAlready = false;
    for (int i = 1; i < SIZE; i++)
    {
        if (board[row + i][column + i] == board[row][column] && row + i < SIZE && column + i < SIZE && !flippedAlready)
        {
            for (int j = 1; j < i; j++)
            {
                if (board[row + j][column + j] == 1)
                {
                    board[row + j][column + j] = 0;
                    canFlip = true;
                    flippedAlready = true;
                }
                else if (board[row + j][column + j] == 0)
                {
                    board[row + j][column + j] = 1;
                    canFlip = true;
                    flippedAlready = true;
                }
                else
                {
                    break;
                }
            }
        }
    }
     
    flippedAlready = false;
    for (int i = 1; i < SIZE; i++)
    {
        if (board[row - i][column + i] == board[row][column] && row - i >= 0 && column + i < SIZE && !flippedAlready)
        {
            for (int j = 1; j < i; j++)
            {
                if (board[row - j][column + j] == 1)
                {
                    board[row - j][column + j] = 0;
                    canFlip = true;
                    flippedAlready = true;
                }
                else if (board[row - j][column + j] == 0)
                {
                    board[row - j][column + j] = 1;
                    canFlip = true;
                    flippedAlready = true;
                }
                else
                {
                    break;
                }
            }
        }
    }
    
    flippedAlready = false;
    for (int i = 1; i < SIZE; i++)
    {
        if (board[row + i][column - i] == board[row][column] && row + i < SIZE && column - i >=0 && !flippedAlready)
        {
            for (int j = 1; j < i; j++)
            {
                if (board[row + j][column - j] == 1)
                {
                    board[row + j][column - j] = 0;
                    canFlip = true;
                    flippedAlready = true;
                }
                else if (board[row + j][column - j] == 0)
                {
                    board[row + j][column - j] = 1;
                    canFlip = true;
                    flippedAlready = true;
                }
                else
                {
                    break;
                }
            }
        }
    }
}


void won(int board[SIZE][SIZE])
{
    int blackCount = 0;
    int whiteCount = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 1) blackCount += 1;
            if (board[i][j] == 0) whiteCount += 1;
        }
    }

    std::cout << "Black count: " << blackCount << "\n";
    std::cout << "White count: " << whiteCount << "\n";
    if (blackCount > whiteCount)
    {
        std::cout << "Black won by: " << blackCount - whiteCount << "\n";
    }
    else if (blackCount < whiteCount)
    {
        std::cout << "White won by: " << whiteCount - blackCount << "\n";
    }
    else
    {
        std::cout << "Game Tie.\n";
    }
}

