#include <vector>
#include <unordered_map>
#include <stack>

#include <string>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <limits>

/* Ref: http://web.cs.ucla.edu/~rosen/161/notes/alphabeta.html
 *
 */

#define O_BIT 3 // 'O' = 11
#define X_BIT 0 // 'X' = 00
#define BLANK 1 // '.' = 01
#define N_ROW 5
#define N_COL 5
#define N_DIA 2 // # of diagonal

// alpha: lower bound, for X
// beta:  upper bound, for O

const int X_WIN = 1;
const int O_WIN = -1;
const int DRAW  = 0;

//#define DEBUG 1
//#define GET_NEXT_BOARD 1
//#define TEST_NEXT_BOARD 1
//#define TEST_IS_END 1
//#define TEST_OPERATOR_EQUAL 1
//#define TEST_WHO_WIN 1
//#define SHOW_SCORE 1
using namespace std;

typedef long long ll;
typedef vector< vector<char> > CharMatrix;
// global variable 
// unordered_map<Board, string> board_record
// defined at line 156 

char bit_to_move(ll bit) {
    char ret = '_';
    switch(bit) {
        case O_BIT: ret = 'O'; break;
        case X_BIT: ret = 'X'; break;
        case BLANK: ret = '.'; break;
    }
    return ret;
}

ll move_to_bit(char move) {
    ll ret = 0;
    switch(move) {
        case 'O': ret = O_BIT; break;
        case 'X': ret = X_BIT; break;
        case '.': ret = BLANK; break;
    }
    return ret;
}

char get_ith_grid(ll state, int ith_grid) {
    // return the 'move' in ith_grid
    // 'O' or 'X' or '.'
    int shift_d = 48 - 2 * ith_grid;
    ll _bit = ( (state >> shift_d) & 3 ); // 3: 11

    return bit_to_move(_bit);
}

inline ll get_grid_bit (ll state, int ith_grid) {
    // return the 'move' in ith_grid
    // 'O' or 'X' or '.'
    //  11     00     01
    int shift_d = 48 - 2 * ith_grid;
    ll _bit = ( (state >> shift_d) & 3 ); // 3: 11

    return _bit;
}

struct ScorePair {
    int O_score;
    int X_score;

    ScorePair() { O_score = 0; X_score = 0; }

    ScorePair(int o_s, int x_s) {
        O_score = o_s;
        X_score = x_s;
    }

};

struct MovePair {
    int grid1;
    int grid2;

    MovePair() { grid1 = -1; grid2 = -1; }

    MovePair(int g1, int g2) {
        grid1 = g1;
        grid2 = g2;
    }
    
    void print() {
        printf("[%d, %d]\n", grid1, grid2);
    }

};
// 
class Board {
public:
    // status of the current Board
    // O's score
    // X's score
    
    // I view the grid as follows:
    // 0  1  2  3  4
    // 5  6  7  8  9
    // 10 11 12 13 14
    // 15 16 17 18 19
    // 20 21 22 23 24
   
    ll state;
    int O_score;
    int X_score;
    int alpha;
    int beta;

    Board() {}

    Board(ll s, int O_s=0, int X_s=0) {
        state = s;
        O_score = O_s;
        X_score = X_s;
        alpha = -1;
        beta = 1;
    }
   
    char operator[](int i) {
        assert ( i >= 0 && i < 25);
        return get_ith_grid(state, i);
    }

    Board operator=(Board& rhs) {
        if (&rhs == this) {
            return (*this);
        } else {
            state = rhs.state;
            O_score = rhs.O_score;
            X_score = rhs.X_score;
            alpha = rhs.alpha;
            beta = rhs.beta;
            return (*this);
        }
    }

    bool operator==(const Board& rhs) const {
        if (rhs.state == state && rhs.O_score == O_score && rhs.X_score == X_score ) {
            //return (rhs.beta <= rhs.alpha && beta <= alpha) || (rhs.alpha == alpha && rhs.beta == beta);
            return (rhs.beta <= rhs.alpha && beta <= alpha) || (rhs.alpha < rhs.beta && alpha < beta);
        }
        return false;
    }

    bool isEnd() {
        // iterate through 0 ~ 24 grid to check '.'
        for (int i = 0; i < 25; ++i) {
           char cur_grid = get_ith_grid(state, i);
           if (cur_grid == '.') 
               return false;
        }
        return true;
    }

    void print() {
        // we have 25 grids in each Board;
        for (int i = 0; i < N_ROW; ++i) {
            for (int j = 0; j < N_COL; ++j) {
                // cerr << "i_th bit: " << (2 * (i * N_ROW + j) ) << "\n";
                // I view the grid as follows:
                // 0  1  2  3  4
                // 5  6  7  8  9
                // 10 11 12 13 14
                // 15 16 17 18 19
                // 20 21 22 23 24
                // thus 0th grid is at (48 - 2 * 0)th bit.
                cout << get_ith_grid(state, i*N_ROW + j);
            }
            cout << "\n";
        }
    
    }

    vector< vector<char> > in_matrix() {
        vector< vector<char> > ret(N_ROW, vector<char>(N_COL));

        for (int i = 0; i < N_ROW; ++i) {
            for (int j = 0; j < N_COL; ++j) {
                ret[i][j] = get_ith_grid(state, i*N_ROW + j);
            }
        }
        return ret;
    }
};

// define the hash function    
struct BoardHasher {
        size_t operator()(const Board& b) const {

      // Compute individual hash values for state,
      // O_score and X_score combine them using XOR
      // and bit shifting:

        return (((((hash<ll>()(b.state)
               ^ (hash<int>()(b.O_score) << 1)) >> 1)
               ^ (hash<int>()(b.X_score) << 1)  >> 1)
               ^ (hash<int>()(b.alpha) << 1)) >> 1)
               ^ (hash<int>()(b.beta) << 1);
        }
};

//typedef unordered_map<Board, string, BoardHasher> BoardMap;
typedef unordered_map<Board, int, BoardHasher> BoardMap;
BoardMap board_record;

void print_matrix(vector< vector<char> >& mat) {
    
    for (int i = 0; i < N_ROW; ++i) {
        for (int j = 0; j < N_COL; ++j) {
            cout << mat[i][j];
        }
        cout << "\n";
    }
}

template <typename T>
void print_vector(vector<T>& v) {
    int n = v.size();
    for (int i = 0; i < n; ++i)
        cout << v[i] << " ";
    cout << "\n"; 
}

inline ScorePair calc_row_score(Board& b, int idx_row) {
    int o_count = 0, x_count = 0;
    ll state = b.state, move;
    int idx_start_grid = N_ROW * idx_row;
    int idx_end_grid = idx_start_grid + N_COL;

    for (int i = idx_start_grid; i < idx_end_grid; ++i) {
        move = get_grid_bit(state, i);
        
        switch(move) {
            case O_BIT: ++o_count; break;
            case X_BIT: ++x_count; break;
            case BLANK: break;
        }
    }
    
    //int o_score = 0, x_score = 0;
                                // Score
    if (o_count >= 4) {         // O    X
        return ScorePair(1, 0); // 1    0
    } else if (x_count >= 4) {
        return ScorePair(0, 1); // 0    1
    } else {
        return ScorePair(0, 0); // 0    0
    }
    //return ScorePair(o_score, x_score);
}

inline ScorePair calc_col_score(Board& b, int idx_col) {
    int o_count = 0, x_count = 0;
    ll state = b.state, move;
    int idx_start_grid = idx_col;

    // iterate N_ROW times
    // each time increment idx_start_grid by 5
    for (int i = 0; i < N_ROW; ++i) {
        move = get_grid_bit(state, idx_start_grid);
        
        switch(move) {
            case O_BIT: ++o_count; break;
            case X_BIT: ++x_count; break;
            case BLANK: break;
        }
        idx_start_grid += N_COL;
    }

    //int o_score = 0, x_score = 0;
                                // Score
    if (o_count >= 4) {         // O    X
        return ScorePair(1, 0); // 1    0
    } else if (x_count >= 4) {
        return ScorePair(0, 1); // 0    1
    } else {
        return ScorePair(0, 0); // 0    0
    }
    //    ++x_score;

    //return ScorePair(o_score, x_score);
}

inline ScorePair calc_diagonal_score(Board& b, int idx_dia) {
    // 0: upper left to lower right
    // 1: upper right to lower left
 
    int o_count = 0, x_count = 0;
    ll state = b.state, move;
    
    if (idx_dia == 0) {
        // upper right to lower left
        // indices are:
        // 0           
        //   6      
        //     12
        //        18
        //           24
        for (int idx_grid = 0; idx_grid < 25; idx_grid += 6) {
            move = get_grid_bit(state, idx_grid);
        
            switch(move) {
                case O_BIT: ++o_count; break;
                case X_BIT: ++x_count; break;
                case BLANK: break;
            }
        }

    } else { 
        // upper right to lower left
        // indices are:
        //             4
        //          8
        //       12
        //    16
        // 20
        for (int idx_grid = 4; idx_grid <= 20; idx_grid += 4) {
            move = get_grid_bit(state, idx_grid);
        
            switch(move) {
                case O_BIT: ++o_count; break;
                case X_BIT: ++x_count; break;
                case BLANK: break;
            }
        }
    }

                                // Score
    if (o_count >= 4) {         // O    X
        return ScorePair(1, 0); // 1    0
    } else if (x_count >= 4) {
        return ScorePair(0, 1); // 0    1
    } else {
        return ScorePair(0, 0); // 0    0
    }

}

inline vector<int> find_blank_grid(Board& b) {

    vector<int> ret;
    ll state = b.state;

    for (int i = 0; i < 25; ++i) {
        if (get_grid_bit(state, i) == BLANK)
            ret.push_back(i);
    }

    return ret;
}

inline vector< MovePair > get_move_combination(vector<int>& idx_blank_grid) {
    // return a combination of pairs given all inx of blank_grid.
    vector< MovePair > ret;
    ret.reserve(150);
    
    int total = idx_blank_grid.size();
    for (int i = 0; i < total; ++i) {
        for (int j = i + 1; j < total; ++j) {
            MovePair tmp = MovePair(idx_blank_grid[i], idx_blank_grid[j]);
            ret.push_back(tmp);
        }
    }

    return ret;
}


inline Board get_next_board(Board& b, MovePair& mp, char r) {
    // given r = 'o', 'x'
    // return the modified Board mod_b;
    Board mod_b = b;
    ll cur_state = b.state;

    int idx_grid1 = mp.grid1, idx_grid2 = mp.grid2;
    // for grid1 = 0, we will modify bits 48, 49
    // for grid2 = 13, we will modify bits 22, 23
    // if grid1 = grid2 = -1, it means we are at last round
    
    if (idx_grid1 == -1 || idx_grid2 == -1) {
        if (r == 'X') {
            // last round for 'X'
            vector<int> blank_grid = find_blank_grid(b);
            int mod_bit1 = 48 - 2*blank_grid[0],
                mod_bit2 = 48 - 2*blank_grid[1],
                mod_bit3 = 48 - 2*blank_grid[2];
                
            cur_state &= ~( (3ll << mod_bit1) + (3ll << mod_bit2) + (3ll << mod_bit3) );
        } else { // error happens
            printf("It's last round but r = %c\n", r);
            mod_b.state = -1;
            return mod_b;
        }
    } else { // normal case
        int mod_bit1 = 48 - 2*idx_grid1, mod_bit2 = 48 - 2*idx_grid2;

        if (r == 'O') {
            // 'O': 11, set this bit to 1
            cur_state |= ( (3ll << mod_bit1) + (3ll << mod_bit2) );

        } else {
            // 'X': 00, clear this bit to 0
            cur_state &= ~( (3ll << mod_bit1) + (3ll << mod_bit2) );
        }

    }

    mod_b.state = cur_state;    
    return mod_b;
}

/*
char get_round(Board& b) {
    int O_count = 0, X_count = 0;
    char move;
    for (int i = 0; i < 25; ++i) {
        move = get_ith_grid(b.state, i);
        if (move == 'O') {
            ++O_count;
        } else if (move == 'X') {
            ++X_count;
        }
    }
    return (O_count == X_count) ? 'O' : 'X';
}*/

char get_round(Board& b) {
    int O_count = 0, X_count = 0;
    ll move;
    for (int i = 0; i < 25; ++i) {
        move = get_grid_bit(b.state, i);
        switch(move) {
            case O_BIT: ++O_count; break;
            case X_BIT: ++X_count; break;
        }
    }
    return (O_count == X_count) ? 'O' : 'X';
}
// calculate scores and update b
//string evaluate(Board& b) {
int evaluate(Board& b) {
    // return the score of b
    //string result = "O win";
    int result = O_WIN;
    
    int tmp_O_score = 0, tmp_X_score = 0;
    ScorePair tmp_pair;
    //CharMatrix b_mat = b.in_matrix();


    // convert to matrix to calculate
    // for each row in Board
    //     if num of 'O' >= 4
    //         ++tmp_O_score;
    //
    //     if num of 'X' >= 4
    //         ++tmp_X_score;
    //
    for (int i = 0; i < N_ROW; ++i) {
        //tmp_pair = calc_row_score(b_mat, i);
        tmp_pair = calc_row_score(b, i);
        tmp_O_score += tmp_pair.O_score;
        tmp_X_score += tmp_pair.X_score;
    }

    // for each col in Board
    //     if num of 'O' >= 4
    //         ++tmp_O_score;
    //
    //     if num of 'X' >= 4
    //         ++tmp_X_score;
    
    for (int i = 0; i < N_COL; ++i) {
        //tmp_pair = calc_col_score(b_mat, i);
        tmp_pair = calc_col_score(b, i); 
        tmp_O_score += tmp_pair.O_score;
        tmp_X_score += tmp_pair.X_score;
    }

    // for two diagonal in Board
    //     if num of 'O' >= 4
    //         ++tmp_O_score;
    //
    //     if num of 'X' >= 4
    //         ++tmp_X_score;
   
    for (int i = 0; i < N_DIA; ++i) {
        //tmp_pair = calc_diagonal_score(b_mat, i);
        tmp_pair = calc_diagonal_score(b, i);
        tmp_O_score += tmp_pair.O_score;
        tmp_X_score += tmp_pair.X_score;
    }

    b.O_score = tmp_O_score;
    b.X_score = tmp_X_score;

    if (tmp_O_score > tmp_X_score) {
        //result = "O win";
        result = O_WIN;
    } else if (tmp_O_score == tmp_X_score) {
        //result = "Draw";
        result = DRAW;
    } else {
        //result = "X win";
        result = X_WIN;
    }
   
     
    #ifdef SHOW_SCORE
    printf("tmp_O_score: %d, tmp_X_score: %d\n", tmp_O_score, tmp_X_score);
    #endif

    return result;
}

//int count_who_win = 0;

int whoWin(Board& b, int alpha, int beta, char r) {
//string whoWin(Board& b, int alpha=-1, int beta=1, char r) {
    // TODO
    // b: current Board
    // r: current player
    //
    // Should have a map<Board, string> to record the Board we've evaluated.
    // ex: {Board: "O win"}
    
    // Base case 1: b isEnd
    
    b.alpha = alpha;
    b.beta = beta;
    
    if (b.isEnd()) {
        // copy b to insert in board_record
        BoardMap::const_iterator got = board_record.find(b);
        if (got != board_record.end()) {
            #ifdef DEBUG
            printf("Looking up b!\n");
            #endif
            return got->second;
        }

        Board insert_b = b;
        //string result = evaluate(b);
        int result = evaluate(b);
        board_record.insert ( {insert_b, result} );
        return result;
    }
   

    // TODO
    // Base case 2: we've already evaluated b
    /*
    BoardMap::const_iterator got = board_record.find(b);
    if (got != board_record.end()) {
        #ifdef DEBUG
        printf("Looking up b!\n");
        #endif
        return got->second;
    }*/
    
    //string result, next_result;
    //int result, next_result;

    // TODO
    // cache which alpha-beta to board?
    //
    // alpha-beta pruning 
    if (r == 'X') {
        //result = "O win";
                        
        // Get all child grid
        vector<int> blank_grid = find_blank_grid(b);
        vector<MovePair> comb_moves;
        if (blank_grid.size() == 3) { // last round
            comb_moves.push_back(MovePair(-1, -1));
            //r = 'X';
        } else {
            comb_moves = get_move_combination(blank_grid);
        }

        // maxmizing player
        // int next_result = - numeric_limits<int>::infinity(); 
        // int next_result = -1;
        int result = -1;
        for (auto mp : comb_moves) {
            Board next_board = get_next_board(b, mp, r);
            
            //BoardMap::const_iterator got = board_record.find(next_board);
            BoardMap::const_iterator got = board_record.find(next_board);
            if (got != board_record.end()) {
                result = max(result, got->second);
                
                if (result == X_WIN) {
                    //b.alpha = 1;
                    //b.beta = 1;
                    board_record.insert( {b, result} );
                    return result;
                }

            } else {
                result = max(result, whoWin(next_board, alpha, beta, 'O'));
            
                if (result == X_WIN) {
                    //b.alpha = 1;
                    //b.beta = 1;
                    board_record.insert( {b, result} );
                    return result;
                }
                
            }
            
            alpha = max(alpha, result);
            if (beta <= alpha)
                break; // beta cut-off
            /*
            alpha = max(alpha, result);
            
            if (beta <= alpha)
                break; // beta cut-off
            */
            //next_result = whoWin(next_board, 'O');
            
            /* no pruning 
            if (next_result == "X win") {
                result = "X win";
                
                board_record.insert ( {b, result} );
                
                return result;
            } else if (next_result == "Draw" && result == "O win") {
                result = "Draw";
            }   */
        }
        // can record the result now
        
        //b.alpha = alpha;
        //b.beta = beta;

        board_record.insert( {b, result} );

        return result;
    } else { // r == 'O'
        // ... likewise
        //result = "X win";

        // Get all child grid
        vector<int> blank_grid = find_blank_grid(b);
        vector<MovePair> comb_moves;
        if (blank_grid.size() == 3) { // last round
            comb_moves.push_back(MovePair(-1, -1));
            //r = 'X';
        } else {
            comb_moves = get_move_combination(blank_grid);
        }

        int result = 1;
        //for (next_Board in all possible next move) {// pop Board from stack
        for ( auto mp : comb_moves) {
            Board next_board = get_next_board(b, mp, r);
            /*
            BoardMap::const_iterator got = board_record.find(next_board);
            if (got != board_record.end()) {
                next_result = got->second;
            } else {
                next_result = whoWin(next_board, 'X');
            }*/
             
            BoardMap::const_iterator got = board_record.find(next_board);
            if (got != board_record.end()) {
    
                result = min(result, got->second);
                if (result == O_WIN) {
                    //b.alpha = -1;
                    //b.beta = -1;
                    
                    board_record.insert( {b, result} );

                    return result;
                }

            } else {
                result = min(result, whoWin(next_board, alpha, beta, 'X'));
                if (result == O_WIN) {
                    //b.alpha = -1;
                    //b.beta = -1;
                    
                    board_record.insert( {b, result} );
                    return result;
                }
                
            }
            
            beta = min(beta, result);
            
            if (beta <= alpha)
                break; // alpha cut-off
            //next_result = whoWin(next_board, 'X');
            
            /* 
            if (next_result == "O win") {
                result = "O win";

                board_record.insert ( {b, result} );

                return result;
            } else if (next_result == "Draw" && result == "X win") {
                result = "Draw";
            }*/  
        }
        // can record the result now
        //b.alpha = alpha;
        //b.beta = beta;
        
        board_record.insert( {b, result} );
        return result;
    }
}

int main(int argc, char** argv) {
    int num_Board;
    char move1, move2, move3, move4, move5;
    
    // read # of Boards to solve
    #ifndef DEBUG
    fscanf(stdin, "%d\n", &num_Board);
    #endif

    #ifdef DEBUG
    FILE* fp = fopen(argv[1], "r");
    fscanf(fp, "%d\n", &num_Board);
    #endif
    vector<Board> input_board(num_Board);
    for (int i = 0; i < num_Board; ++i) {
        ll row_state = 0; // state of current row 
        for (int j = 0; j < N_ROW; ++j) { // 5 row for each grid
            //while (EOF != fscanf(stdin, "%c%c%c%c%c", &move1, &move2, &move3, &move4, &move5)) {
            #ifndef DEBUG
            fscanf(stdin, "%c%c%c%c%c\n", &move1, &move2, &move3, &move4, &move5);
            #endif 
            
            #ifdef DEBUG
            fscanf(fp, "%c%c%c%c%c\n", &move1, &move2, &move3, &move4, &move5);
            #endif

            #ifdef DEBUG
            printf("%c%c%c%c%c\n", move1, move2, move3, move4, move5);
            #endif
            
            ll tmp_move = (move_to_bit(move1) << 8) +
                          (move_to_bit(move2) << 6) +
                          (move_to_bit(move3) << 4) +
                          (move_to_bit(move4) << 2) + (move_to_bit(move5));
            
            // update row_state
            row_state += tmp_move;
            #ifdef DEBUG
            cout << "tmp_move: " << tmp_move << "\n";
            #endif
            row_state = (row_state << 10);
        }
        ll state = (row_state >> 10); // we move bits too far, have to shift it back;
        #ifdef DEBUG
        cout << "state of this Board: " << state << "\n";
        #endif
        Board cur_Board = Board(state, 0, 0);
        input_board[i] = cur_Board;    
    }
   
    #ifdef DEBUG    
    for (int i = 0; i < num_Board; ++i) {   
        //cout << input_board[i].state << "\n";
        cout << i << "th Board:\n";
        input_board[i].print();
        cout << "who wins?\n";
        cout << evaluate(input_board[i]) << "\n";
    }
    #endif
        
    #ifdef DEBUG
    cout << "Test in_matrix\n";
    vector< vector<char> > tmp = input_board[0].in_matrix();
    print_matrix(tmp);
    #endif
    
    #ifdef DEBUG
    int input_n;
    printf("Input [0, %d] to find Board's blank gird, or -1 to quit: ", num_Board - 1);
    while (cin >> input_n) {
        if (input_n == -1)
            break;

        Board in_board = input_board[input_n];

        printf("Finding %d th Board's blank grid.\n", input_n);
        CharMatrix bn_mat = in_board.in_matrix();
        printf("%d Matrix is:\n", input_n);
        print_matrix(bn_mat);

        vector<int> blank_grid = find_blank_grid(in_board);
        print_vector(blank_grid);
        printf("Input [0, %d] to find Board's blank gird, or -1 to quit: ", num_Board - 1);
    
        printf("Generating combination of moves.\n");

        vector<MovePair> comb_moves = get_move_combination(blank_grid);
        
        printf("# of blank_grid: %lu, # of comb.: %lu\n", blank_grid.size(), comb_moves.size());
        for (int i = 0; i < comb_moves.size(); ++i) {
            comb_moves[i].print();
        }    

    }
    #endif
    
    #ifdef DEBUG
    printf("Testing [] operator, -2 to quit. Board is 0th Board:\n");
    Board in_board = input_board[0];
    in_board.print();

    while (cin >> input_n) {
        if (input_n == -2)
            break;
        printf("b[%d] = %c, or -2 to quit\n", input_n, in_board[input_n]);
    }
    #endif

    #ifdef TEST_OPERATOR_EQUAL
    printf("Testing = operator, 0th Board is:\n");
    in_board.print();
    Board copy = in_board;
    printf("copy is:\n");
    copy.print();
    printf("copy 1 is:\n");
    copy = input_board[1];
    copy.print();

    #endif

    #ifdef GET_NEXT_BOARD
    printf("Test modify Board. Input n to mod Board n: ");
    cin >> input_n;
    printf("Modifying b%d.\n", input_n);
    in_board = input_board[input_n];
    in_board.print();
    printf("Available moves:\n");
    vector<int> blank_grid = find_blank_grid(in_board);
    vector<MovePair> comb_moves = get_move_combination(blank_grid);
    for (int i = 0; i < comb_moves.size(); ++i) {
        comb_moves[i].print();
    }
    int in_g1, in_g2;
    
    printf("Input grid to modify, or -3 -3 to quit: ");
    while(cin >> in_g1 >> in_g2) {
        if (in_g1 == -3 || in_g2 == -3)
            break;
        char r = 'O';
        MovePair mp(in_g1, in_g2);
        Board nb = get_next_board(in_board, mp, r);
        
        printf("Next Board:\n");
        nb.print();

        printf("Input grid to modify, or -3 to quit: ");
    }
    #endif

    #ifdef TEST_NEXT_BOARD
    whoWin(input_board[0], 'X');
    #endif
    
    #ifdef TEST_IS_END
    printf("Testing isEnd.\n");
    Board cur_b = input_board[0];
    MovePair last_move(-1, -1);
    Board next_b = get_next_board(cur_b, last_move, 'X');
    if (next_b.isEnd())
        printf("Maybe no bug.\n");
    else
        printf("Definitely has bug.\n");

    #endif

    #ifdef TEST_NEXT_BOARD
    // Get all child grid
    printf("Insert n, r to check all next_board: ");
    char r;
    cin >> input_n >> r;
    cur_b = input_board[input_n];
    blank_grid = find_blank_grid(cur_b);
    comb_moves.clear();
    if (blank_grid.size() == 3) { // last round
        comb_moves.push_back(MovePair(-1, -1));
        //r = 'X';
    } else {
        comb_moves = get_move_combination(blank_grid);
    }
    for (vector<MovePair>::iterator it = comb_moves.begin(); it != comb_moves.end(); ++it) {
        printf("Original Board:\n");
        cur_b.print();
        Board next_Board = get_next_board(cur_b, (*it), r);
        printf("Modified Board with grid: ");
        (*it).print();
        next_Board.print();
    }
    #endif

    #ifdef TEST_WHO_WIN
    printf("Insert n, r to test whoWin, or r = q to quit: ");
    while (cin >> input_n >> r) {
        if (r == 'q')
            break;
        printf("r = %c, Board %d is:\n", r, input_n);
        cur_b = input_board[input_n];
        cur_b.print();
        string result = whoWin(cur_b, r);
        printf("Who win? %s\n", result.c_str());
        printf("Insert n, r to test whoWin, or r = q to quit: ");
    }
    #endif

    // writing ouput
    for (int i = 0; i < num_Board; ++i) {
        Board cur_board = input_board[i];
        char r = get_round(cur_board);
        int result = whoWin(cur_board, -1, 1, r);
        
        switch (result) {
            case O_WIN: fprintf(stdout, "O win\n"); break;
            case X_WIN: fprintf(stdout, "X win\n"); break;
            case DRAW: fprintf(stdout, "Draw\n"); break;
        }

        //fprintf(stdout, "%s\n", result.c_str());
        //fprintf(stdout, );
    
    }

    return 0;
}

