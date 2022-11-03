#include "minimax.h"
#include "stdio.h"

#define TOP 0
#define MID 1
#define BOT 2
#define LFT 0
#define RGT 2

#define NOTHING 0
#define SQUARE_COUNT 9

// global variables for the moves
static tictactoe_location_t choice;
static tictactoe_location_t daMove;

// function to test the passed board pointer against all possible board winning
// cases
minimax_score_t minimax_computeBoardScore(tictactoe_board_t *board,
                                          bool is_Xs_turn) {
  if (is_Xs_turn && board->squares[TOP][LFT] == MINIMAX_O_SQUARE &&
      board->squares[MID][LFT] == MINIMAX_O_SQUARE &&
      board->squares[BOT][LFT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  } else if (is_Xs_turn && board->squares[TOP][MID] == MINIMAX_O_SQUARE &&
             board->squares[MID][MID] == MINIMAX_O_SQUARE &&
             board->squares[BOT][MID] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  } else if (is_Xs_turn && board->squares[TOP][RGT] == MINIMAX_O_SQUARE &&
             board->squares[MID][RGT] == MINIMAX_O_SQUARE &&
             board->squares[BOT][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  } else if (is_Xs_turn && board->squares[TOP][LFT] == MINIMAX_O_SQUARE &&
             board->squares[TOP][MID] == MINIMAX_O_SQUARE &&
             board->squares[TOP][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  } else if (is_Xs_turn && board->squares[MID][LFT] == MINIMAX_O_SQUARE &&
             board->squares[MID][MID] == MINIMAX_O_SQUARE &&
             board->squares[MID][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  } else if (is_Xs_turn && board->squares[BOT][LFT] == MINIMAX_O_SQUARE &&
             board->squares[BOT][MID] == MINIMAX_O_SQUARE &&
             board->squares[BOT][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  } else if (is_Xs_turn && board->squares[TOP][LFT] == MINIMAX_O_SQUARE &&
             board->squares[MID][MID] == MINIMAX_O_SQUARE &&
             board->squares[BOT][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  } else if (is_Xs_turn && board->squares[TOP][RGT] == MINIMAX_O_SQUARE &&
             board->squares[MID][MID] == MINIMAX_O_SQUARE &&
             board->squares[BOT][LFT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  } else if (!is_Xs_turn && board->squares[TOP][LFT] == MINIMAX_X_SQUARE &&
             board->squares[MID][LFT] == MINIMAX_X_SQUARE &&
             board->squares[BOT][LFT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  } else if (!is_Xs_turn && board->squares[TOP][MID] == MINIMAX_X_SQUARE &&
             board->squares[MID][MID] == MINIMAX_X_SQUARE &&
             board->squares[BOT][MID] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  } else if (!is_Xs_turn && board->squares[TOP][RGT] == MINIMAX_X_SQUARE &&
             board->squares[MID][RGT] == MINIMAX_X_SQUARE &&
             board->squares[BOT][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  } else if (!is_Xs_turn && board->squares[TOP][LFT] == MINIMAX_X_SQUARE &&
             board->squares[TOP][MID] == MINIMAX_X_SQUARE &&
             board->squares[TOP][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  } else if (!is_Xs_turn && board->squares[MID][LFT] == MINIMAX_X_SQUARE &&
             board->squares[MID][MID] == MINIMAX_X_SQUARE &&
             board->squares[MID][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  } else if (!is_Xs_turn && board->squares[BOT][LFT] == MINIMAX_X_SQUARE &&
             board->squares[BOT][MID] == MINIMAX_X_SQUARE &&
             board->squares[BOT][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  } else if (!is_Xs_turn && board->squares[TOP][LFT] == MINIMAX_X_SQUARE &&
             board->squares[MID][MID] == MINIMAX_X_SQUARE &&
             board->squares[BOT][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  } else if (!is_Xs_turn && board->squares[TOP][RGT] == MINIMAX_X_SQUARE &&
             board->squares[MID][MID] == MINIMAX_X_SQUARE &&
             board->squares[BOT][LFT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  }

  // if the board wasnt a winning case, check to see if there are open spaces to
  // play
  for (uint8_t i = NOTHING; i < TICTACTOE_BOARD_ROWS; i++) // loop the rows
  {
    for (uint8_t j = NOTHING; j < TICTACTOE_BOARD_COLUMNS;
         j++) // loop the columns
    {
      if (board->squares[i][j] == MINIMAX_EMPTY_SQUARE) {
        return MINIMAX_NOT_ENDGAME;
      }
    }
  }

  return MINIMAX_DRAW_SCORE;
}

// initialize the board to all zeroes
void minimax_initBoard(tictactoe_board_t *board) {
  board->squares[TOP][LFT] = 0;
  board->squares[TOP][MID] = 0;
  board->squares[TOP][RGT] = 0;
  board->squares[MID][LFT] = 0;
  board->squares[MID][MID] = 0;
  board->squares[MID][RGT] = 0;
  board->squares[BOT][LFT] = 0;
  board->squares[BOT][MID] = 0;
  board->squares[BOT][RGT] = 0;
}

// test and see if the score is in a value that denotes the end of a game
bool minimax_isGameOver(minimax_score_t score) {
  if (score == MINIMAX_O_WINNING_SCORE || score == MINIMAX_X_WINNING_SCORE ||
      score == MINIMAX_DRAW_SCORE) {
    return true;
  } else if (score == MINIMAX_NOT_ENDGAME) {
    return false;
  }
}

// the minimax recursive function
minimax_score_t minimax(tictactoe_board_t *board, bool is_Xs_turn) {
  tictactoe_location_t moves[SQUARE_COUNT];
  minimax_score_t scores[SQUARE_COUNT];
  uint8_t location = 0;

  minimax_score_t score = minimax_computeBoardScore(board, !is_Xs_turn);

  if (minimax_isGameOver(score)) // check and see if the game is over
  {
    // return minimax_computeBoardScore(board,!is_Xs_turn);
    return score;
  }

  for (uint8_t i = NOTHING; i < TICTACTOE_BOARD_ROWS; i++) // loop the rows
  {
    for (uint8_t j = NOTHING; j < TICTACTOE_BOARD_COLUMNS;
         j++) // loop the columns
    {
      // if there is an empty square here
      if (board->squares[i][j] == MINIMAX_EMPTY_SQUARE) {
        if (is_Xs_turn) {
          board->squares[i][j] = MINIMAX_X_SQUARE;
        } else if (!is_Xs_turn) {
          board->squares[i][j] = MINIMAX_O_SQUARE;
        }

        score = minimax(board, !is_Xs_turn); // recurse the minimax function

        daMove.row = i;
        daMove.column = j;

        // add to the arrays of moves and scores
        moves[location] = daMove;
        scores[location] = score;

        board->squares[i][j] = MINIMAX_EMPTY_SQUARE;
        location++;
      }
    }
  }

  if (is_Xs_turn) // search if its Xs turn
  {
    minimax_score_t temp = scores[NOTHING];
    uint8_t tempHolder = NOTHING;
    for (uint8_t i = NOTHING; i < location; i++) {
      if (scores[i] >
          temp) // see if the placeholder is bigger than the next value
      {
        temp = scores[i];
        tempHolder = i;
      }
    }
    choice = moves[tempHolder]; // update the best choice and the score
    score = scores[tempHolder];
  } else // search if its 0s turn
  {
    minimax_score_t temp = scores[NOTHING];
    uint8_t tempHolder = NOTHING;
    for (uint8_t i = NOTHING; i < location; i++) {
      if (scores[i] <= temp) // see if the placeholder is less than or equal to
                             // the next value
      {
        temp = scores[i];
        tempHolder = i;
      }
    }
    choice = moves[tempHolder]; // updatea the best choice and the score
    score = scores[tempHolder];
  }
  return score;
}

// call the recursive version of the minimax function here, then return the best
// location to make a move
tictactoe_location_t minimax_computeNextMove(tictactoe_board_t *board,
                                             bool is_Xs_turn) {
  minimax(board, is_Xs_turn);
  return choice;
}

// a function to print the passed board
void printBoard(tictactoe_board_t *board) {
  // loop through the rows
  for (uint8_t i = 0; i < TICTACTOE_BOARD_ROWS; i++) {
    printf("\n");
    // loop through the columns
    for (uint8_t j = 0; j < TICTACTOE_BOARD_COLUMNS; j++) {
      tictactoe_square_state_t spot = board->squares[i][j];
      if (spot == MINIMAX_EMPTY_SQUARE) // print the empty
      {
        printf("%c  ", '-');
      } else if (spot == MINIMAX_X_SQUARE) // print the X
      {
        printf("%c  ", 'X');
      } else if (spot == MINIMAX_O_SQUARE) // print the 0
      {
        printf("%c  ", 'O');
      }
    }
  }
  printf("\n");
}
