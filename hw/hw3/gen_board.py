import numpy as np
import sys

DEBUG = False

# 'O' = 3, 'X' = 0, '.' = 1
O = 3
X = 0
dot = 1

NUM_ROW = 5
NUM_COL = 5

bit_one_round =   [3, 3, 0, 0, 1]
bit_empty_round = [1, 1, 1, 1, 1]

O_one_round = [3, 3]
X_one_round = [0, 0]

char_one_round =   ['O', 'O', 'X', 'X', '.']
char_empty_round = ['.', '.', '.', '.', '.']



def print_board(char_b):
    for i in range(NUM_ROW):
        print("{}{}{}{}{}".format(char_b[i][0], char_b[i][1], char_b[i][2], char_b[i][3], char_b[i][4]))

def main():
    if len(sys.argv) != 3:
        print("usage: python gen_board.py [num_board] [num_round]")
    else:
        num_board = int(sys.argv[1])
        num_round = int(sys.argv[2])

        if DEBUG:
            print("num_board = {}, current_round = {}.".format(n, num_round))

        #ret_b = np.random.randint(3, size=(NUM_ROW, 5))
        list_char_b = []

        for i in range(num_board):
            count_O_round = int(np.ceil(num_round / 2))
            count_X_round = num_round // 2

            ret_b =  count_O_round * O_one_round + count_X_round * X_one_round + [dot] * (25 - 2 * num_round)
            
            ret_b = np.random.permutation(ret_b).tolist()
            #print(ret_b)

            char_b = [ [0 for i in range(NUM_ROW)] for i in range(5)]


            
            for i in range(NUM_ROW):
                for j in range(NUM_ROW):
                    if ret_b[i + j * NUM_ROW] == O:
                        char_b[i][j] = 'O'
                    if ret_b[i + j * NUM_ROW] == X:
                        char_b[i][j] = 'X'
                    if ret_b[i + j * NUM_ROW] == dot:
                        char_b[i][j] = '.'

            #print_board(char_b)
            
            list_char_b.append(char_b)

        """END OF GENERATING RANDOM BOARD"""
        print(num_board)
        for b in list_char_b:
            print_board(b)

if __name__ == '__main__':
    main()
