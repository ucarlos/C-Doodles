/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 06/22/2020 at 09:47 PM
 * 
 * Tic_Tak_Toe.cc
 * Awful Implementation of Tic Tac Toe.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
using namespace std;

const char default_tile_char = '!';
int total_marks = 0;
// 80 char terminal
const int max_term_length = 80;

class Mark {
public:
    void set_mark(char ch) { value = ch; }
    char get_mark() const{ return value; }
    bool is_mark(char ch) const { return value == ch; }
    void clear_mark() { value = default_tile_char; }

    Mark()=default;
    explicit Mark(char val) : value{val} { }
    
    void toggle_on() { chosen = true; }
    void toggle_off() { chosen = false; }
    bool is_empty() const { return !chosen; }
private:
    char value{default_tile_char};
    bool chosen{false};
};

void draw_board(const vector<Mark> &vm);

class Player {
public:
    Player()=default;
    vector<int>& get_mark_list() { return mark_indices; }

    explicit Player(char ch) : mark_char{ch} { }
    // Copy constructor
    Player(const Player &p);
    
    void add_mark_to_list(int i) { mark_indices.push_back(i); }
    [[nodiscard]] char get_mark_character() const { return mark_char; }
private:
    char mark_char{'@'};
    vector<int> mark_indices;
};


Player::Player(const Player &p) {
    this->mark_char = p.mark_char;
    this->mark_indices = p.mark_indices;
}

//------------------------------------------------------------------------------
// Class helper functions
//------------------------------------------------------------------------------

void claim_mark(Player &p, Mark &m, int index) {
    m.set_mark(p.get_mark_character());
    m.toggle_on();
    // Add to list:
    p.add_mark_to_list(index);
    total_marks++;

}

void print_dash_line(const int &term_len) {
    for (int i = 0; i < term_len; i++)
        cout << "-";
    cout << "\n";
}
//------------------------------------------------------------------------------
// Check Win Conditions
//------------------------------------------------------------------------------
inline bool check_down(const vector<Mark> &board, const int &index,
                       const char &ch) {
    return board[index].get_mark() == ch
        && board[index + 3].get_mark() == ch
        && board[index + 6].get_mark() == ch;
}

inline bool check_across(const vector<Mark> &board, const int &index,
                         const char &ch) {
    return board[index].get_mark() == ch
        && board[index + 1].get_mark() == ch
        && board[index + 2].get_mark() == ch;

}

inline bool check_right_diagonal(const vector<Mark> &board,
                                 const int &index, const char &ch) {
    return board[index].get_mark() == ch
        && board[index + 4].get_mark() == ch
        && board[index + 8].get_mark() == ch;
}

inline bool check_left_diagonal(const vector<Mark> &board,
                                const int &index, const char &ch) {
    return board[index].get_mark() == ch
        && board[index + 2].get_mark() == ch
        && board[index + 4].get_mark() == ch;

}

//------------------------------------------------------------------------------
// Awful way of checking winning conditions, but it works.
//------------------------------------------------------------------------------
bool check_winning_conditions(vector<Mark> &board, Player &p) {
    bool check{true};
    char player_character = p.get_mark_character();
    int temp_index;
    
    // Now check the player's vector list. If less than 3, return false.
    const vector<int> &vec = p.get_mark_list();
    
    if (vec.size() < 3) return false;
    
    for (const int &i : vec) {
        temp_index = i;
    
        switch(temp_index) {
        case 0:
            check = check_across(board, temp_index, player_character);
            check |= check_down(board, temp_index, player_character);
            check |= check_right_diagonal(board, temp_index, player_character);
            break;
        case 1:
            check = check_down(board, temp_index, player_character);
            break;
        case 2:
            check = check_down(board, temp_index, player_character);
            check |= check_left_diagonal(board, temp_index, player_character);
            break;
        case 3: case 6:
            check = check_across(board, temp_index, player_character);
            // break can be omitted if you want
            //break;
        default:
            break;
        
        }
    
        if (check) {
            draw_board(board);
            cout << "Player '" << player_character
                 << "' wins!" << endl;
            return true;
        }

    }
    
    // if check is still false, then the game has ended in a draw.
    if (!check && total_marks >= 9) {
        draw_board(board);
        cout << "This game ends in a draw." << endl;
        return true;
    }
    
    // If none were found, then continue.
    return false;
}


void draw_board(const vector<Mark> &vm) {
    for (unsigned long i = 0; i < vm.size(); i++)
        cout << vm[i].get_mark()
             << (((i + 1) % 3 == 0) ? "\n" : " ");

}

void player_turn(vector<Mark> &board, Player &p) {
    // Clear screen and print the current board:
    // Windows Version
#if defined(WIN32) || defined(_WIN32)
    system("cls");
#else // Linux/POSIX
    system("clear");
#endif
    
    char pc = p.get_mark_character();
    print_dash_line(max_term_length);
    cout << "It is now Player " << pc << "'s turn.\n";
    print_dash_line(max_term_length);
    
    draw_board(board);
    print_dash_line(max_term_length);
    cout << "Please enter a row and column where you want to put down"
         << " a character.\nMake sure that the row and columns are"
         << " between 1 and 3.\n";
    int row, column;
    cin >> row >> column;
    int index = 3 * (row - 1) + (column - 1);
    
    bool check_range = (1 <= row && row <= 3) && (1 <= column && column <= 3);
    while (!check_range || !board[index].is_empty()) {
        cerr << "The row and column combination is invalid or "
             << "is already marked by another player. Try again.\n";
        cin >> row >> column;
        index = 3 * (row - 1) + (column - 1);
        check_range = (1 <= row && row <= 3) && (1 <= column && column <= 3);       
    }
    // Now translate to 1d array:
    
    claim_mark(p, board[index], index);
    
    bool check_win = check_winning_conditions(board, p);
    
    if (check_win)
        exit(EXIT_SUCCESS);
    
}

int main(void) {
    // Create the board.
    vector<Mark> board(9);
    Player p1('x');
    Player p2('o');
    print_dash_line(max_term_length);
    cout << "Tic Tac Toe (Version 0.5)" << endl;
    print_dash_line(max_term_length);
    
    char ch;
    cout << "Press any letter to begin!" << endl;
    cin >> ch;
    
    while (true) {
        player_turn(board, p1);
        player_turn(board, p2);
    }

}
