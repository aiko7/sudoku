#include <iostream>
#include <map>
#include <vector>
#include <set>
//530070000600195000098000060800060003400803001700020006060000280000419005000080079
//003590040020000080005103000700010000400080100000020006000309050050000000000040000
using namespace std;
const int BOARD_SIZE = 9;

class Board
{
private:
    int board_state[BOARD_SIZE][BOARD_SIZE]{};
    map<int, vector<int>> cell_info;
    vector<int> squares[9];
    vector<int> rows[9];
    vector<int> columns[9];

public:
    explicit Board(int board[BOARD_SIZE][BOARD_SIZE])
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                board_state[i][j] = board[i][j];
            }
        }
    }

    void print_board() const
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            if (i % 3 == 0)
            {
                cout << " -------------------------" << endl;
            }
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (j % 3 == 0)
                {
                    cout << " |";
                }
                cout << " " << board_state[i][j];
            }
            cout << " |" << endl;
        }
        cout << " -------------------------" << endl;
    }

    int get_square_number(int i, int j)
    {
        if (i / 3 == 0)
        {
            if (j / 3 == 0)
            {
                return 0;
            }
            else if (j / 3 == 1)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
        else if (i / 3 == 1)
        {
            if (j / 3 == 0)
            {
                return 3;
            }
            else if (j / 3 == 1)
            {
                return 4;
            }
            else
            {
                return 5;
            }
        }
        else if (i / 3 == 2)
        {
            if (j / 3 == 0)
            {
                return 6;
            }
            else if (j / 3 == 1)
            {
                return 7;
            }
            else
            {
                return 8;
            }
        }
    }

    void generate_available_numbers(set<int> unavailable_nums, vector<int>& vec)
    {
        bool n1 = true, n2 = true, n3 = true, n4 = true, n5 = true, n6 = true, n7 = true, n8 = true, n9 = true;
        for (const auto& num : unavailable_nums)
        {
            if (num == 1) n1 = false;
            if (num == 2) n2 = false;
            if (num == 3) n3 = false;
            if (num == 4) n4 = false;
            if (num == 5) n5 = false;
            if (num == 6) n6 = false;
            if (num == 7) n7 = false;
            if (num == 8) n8 = false;
            if (num == 9) n9 = false;
        }

        if (n1)vec.push_back(1);
        if (n2)vec.push_back(2);
        if (n3)vec.push_back(3);
        if (n4)vec.push_back(4);
        if (n5)vec.push_back(5);
        if (n6)vec.push_back(6);
        if (n7)vec.push_back(7);
        if (n8)vec.push_back(8);
        if (n9)vec.push_back(9);
    }

    void square_info()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board_state[i][j] == 0) continue;
                squares[get_square_number(i, j)].push_back(board_state[i][j]);
            }
        }
    }

    void row_info()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board_state[i][j] == 0) continue;
                rows[i].push_back(board_state[i][j]);
            }
        }
    }

    void column_info()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board_state[j][i] == 0) continue;
                columns[i].push_back(board_state[j][i]);
            }
        }
    }

    void fill_cell_map()
    {
        square_info();
        row_info();
        column_info();
        int CURRENT_CELL = 0;

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                set<int> unavailable_nums;
                vector<int> available_nums;

                for (const auto& num : squares[get_square_number(i, j)])
                {
                    unavailable_nums.insert(num);
                }
                for (const auto& num : rows[i])
                {
                    unavailable_nums.insert(num);
                }
                for (const auto& num : columns[j])
                {
                    unavailable_nums.insert(num);
                }

                generate_available_numbers(unavailable_nums, available_nums);

                if (board_state[i][j] == 0)
                {
                    cell_info[CURRENT_CELL]=available_nums;
                }
                else
                {
                    cell_info[CURRENT_CELL]=vector<int>();
                }
                CURRENT_CELL++;
            }
        }
    }

    void fill_trivial_solutions()
    {
        int c = 0;
        for (const auto& num : cell_info)
        {
            if (num.second.size() == 1 && num.second.at(0) != -1)
            {
                board_state[c / 9][c % 9] = num.second.at(0);
            }
            c++;
        }
    }

    bool check_invalid_state(int i ,int j)
    {

    }
};


int main()
{
    char board_string[82];
    cin >> board_string;
    int board[BOARD_SIZE][BOARD_SIZE];
    int c = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = (board_string[c] - 48);
            c++;
        }
    }
    Board testBoard(board);
    testBoard.print_board();
    testBoard.fill_cell_map();
    testBoard.fill_trivial_solutions();
    for (int i = 0; i < 6; i++)
    {
        testBoard.fill_cell_map();
        testBoard.fill_trivial_solutions();
    }
    testBoard.fill_cell_map();
    testBoard.fill_trivial_solutions();
    testBoard.print_board();
}
