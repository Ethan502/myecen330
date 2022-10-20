#include "minimax.h"
#include "stdio.h"

#define TOP 0
#define MID 1
#define BOT 2
#define LFT 0
#define RGT 2

#define NOTHING 0
#define SQUARE_COUNT 9

static minimax_score_t score;


//call the recursive version of the minimax function here
tictactoe_location_t minimax_computeNextMove(tictactoe_board_t *board, bool is_Xs_turn)
{

}

minimax_score_t minimax_computeBoardScore(tictactoe_board_t *board, bool is_Xs_turn)
{
    if
    (   is_Xs_turn &&
        board->squares[TOP][LFT] == MINIMAX_O_SQUARE &&
        board->squares[MID][LFT] == MINIMAX_O_SQUARE &&
        board->squares[BOT][LFT] == MINIMAX_O_SQUARE
    )
    {
        return MINIMAX_O_WINNING_SCORE;
    }
    else if
    (
        is_Xs_turn &&
        board->squares[TOP][MID] == MINIMAX_O_SQUARE &&
        board->squares[MID][MID] == MINIMAX_O_SQUARE &&
        board->squares[BOT][MID] == MINIMAX_O_SQUARE
    )
    {
        return MINIMAX_O_WINNING_SCORE;
    }
    else if
    (
        is_Xs_turn &&
        board->squares[TOP][RGT] == MINIMAX_O_SQUARE &&
        board->squares[MID][RGT] == MINIMAX_O_SQUARE &&
        board->squares[BOT][RGT] == MINIMAX_O_SQUARE
    )
    {
        return MINIMAX_O_WINNING_SCORE;
    }
    else if
    (
        is_Xs_turn &&
        board->squares[TOP][LFT] == MINIMAX_O_SQUARE &&
        board->squares[TOP][MID] == MINIMAX_O_SQUARE &&
        board->squares[TOP][RGT] == MINIMAX_O_SQUARE
    )
    {
        return MINIMAX_O_WINNING_SCORE;
    }
    else if
    (
        is_Xs_turn &&
        board->squares[MID][LFT] == MINIMAX_O_SQUARE &&
        board->squares[MID][MID] == MINIMAX_O_SQUARE &&
        board->squares[MID][RGT] == MINIMAX_O_SQUARE
    )
    {
        return MINIMAX_O_WINNING_SCORE;
    }
    else if
    (
        is_Xs_turn &&
        board->squares[BOT][LFT] == MINIMAX_O_SQUARE &&
        board->squares[BOT][MID] == MINIMAX_O_SQUARE &&
        board->squares[BOT][RGT] == MINIMAX_O_SQUARE
    )
    {
        return MINIMAX_O_WINNING_SCORE;
    }
    else if
    (
        is_Xs_turn &&
        board->squares[TOP][LFT] == MINIMAX_O_SQUARE &&
        board->squares[MID][MID] == MINIMAX_O_SQUARE &&
        board->squares[BOT][RGT] == MINIMAX_O_SQUARE
    )
    {
        return MINIMAX_O_WINNING_SCORE;
    }
    else if
    (
        is_Xs_turn &&
        board->squares[TOP][RGT] == MINIMAX_O_SQUARE &&
        board->squares[MID][MID] == MINIMAX_O_SQUARE &&
        board->squares[BOT][LFT] == MINIMAX_O_SQUARE
    )
    {
        return MINIMAX_O_WINNING_SCORE;
    }
    else if
    (   !is_Xs_turn &&
        board->squares[TOP][LFT] == MINIMAX_X_SQUARE &&
        board->squares[MID][LFT] == MINIMAX_X_SQUARE &&
        board->squares[BOT][LFT] == MINIMAX_X_SQUARE
    )
    {
        return MINIMAX_X_WINNING_SCORE;
    }
    else if
    (
        !is_Xs_turn &&
        board->squares[TOP][MID] == MINIMAX_X_SQUARE &&
        board->squares[MID][MID] == MINIMAX_X_SQUARE &&
        board->squares[BOT][MID] == MINIMAX_X_SQUARE
    )
    {
        return MINIMAX_X_WINNING_SCORE;
    }
    else if
    (
        !is_Xs_turn &&
        board->squares[TOP][RGT] == MINIMAX_X_SQUARE &&
        board->squares[MID][RGT] == MINIMAX_X_SQUARE &&
        board->squares[BOT][RGT] == MINIMAX_X_SQUARE
    )
    {
        return MINIMAX_X_WINNING_SCORE;
    }
    else if
    (
        !is_Xs_turn &&
        board->squares[TOP][LFT] == MINIMAX_X_SQUARE &&
        board->squares[TOP][MID] == MINIMAX_X_SQUARE &&
        board->squares[TOP][RGT] == MINIMAX_X_SQUARE
    )
    {
        return MINIMAX_X_WINNING_SCORE;
    }
    else if
    (
        !is_Xs_turn &&
        board->squares[MID][LFT] == MINIMAX_X_SQUARE &&
        board->squares[MID][MID] == MINIMAX_X_SQUARE &&
        board->squares[MID][RGT] == MINIMAX_X_SQUARE
    )
    {
        return MINIMAX_X_WINNING_SCORE;
    }
    else if
    (
        !is_Xs_turn &&
        board->squares[BOT][LFT] == MINIMAX_X_SQUARE &&
        board->squares[BOT][MID] == MINIMAX_X_SQUARE &&
        board->squares[BOT][RGT] == MINIMAX_X_SQUARE
    )
    {
        return MINIMAX_X_WINNING_SCORE;
    }
    else if
    (
        !is_Xs_turn &&
        board->squares[TOP][LFT] == MINIMAX_X_SQUARE &&
        board->squares[MID][MID] == MINIMAX_X_SQUARE &&
        board->squares[BOT][RGT] == MINIMAX_X_SQUARE
    )
    {
        return MINIMAX_X_WINNING_SCORE;
    }
    else if
    (
        !is_Xs_turn &&
        board->squares[TOP][RGT] == MINIMAX_X_SQUARE &&
        board->squares[MID][MID] == MINIMAX_X_SQUARE &&
        board->squares[BOT][LFT] == MINIMAX_X_SQUARE
    )
    {
        return MINIMAX_X_WINNING_SCORE;
    }
    
    for(uint8_t i = NOTHING;i<TICTACTOE_BOARD_ROWS;i++)
    {
        for(uint8_t j = NOTHING;j<TICTACTOE_BOARD_COLUMNS;j++)
        {
            if(board->squares[i][j] == MINIMAX_EMPTY_SQUARE)
            {
                return MINIMAX_NOT_ENDGAME;
            }
        }
    }

    return MINIMAX_DRAW_SCORE;

}

void minimax_initBoard(tictactoe_board_t *board)
{
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

bool minimax_isGameOver(minimax_score_t score)
{
    if(score == MINIMAX_O_WINNING_SCORE || score == MINIMAX_X_WINNING_SCORE ||
       score == MINIMAX_DRAW_SCORE)
    {
        return true;
    }
    else if (score == MINIMAX_NOT_ENDGAME)
    {
        return false;
    }
}

minimax_score_t minimax(tictactoe_board_t *board,bool is_Xs_turn)
{
    tictactoe_location_t moves[SQUARE_COUNT] = {};
    minimax_score_t scores[SQUARE_COUNT] = {};
    uint8_t location = 0;


    if(minimax_isGameOver(score))
    {
        return minimax_computeBoardScore(board,!is_Xs_turn);
    }

    for(uint8_t i = NOTHING;i<TICTACTOE_BOARD_ROWS;i++)
    {
        for(uint8_t j = NOTHING;i<TICTACTOE_BOARD_COLUMNS;i++)
        {
            //if there is an empty square here
            if(board->squares[i][j] == MINIMAX_EMPTY_SQUARE)
            {
                if(is_Xs_turn)
                {
                    board->squares[i][j] = MINIMAX_X_SQUARE;
                }
                else if (!is_Xs_turn)
                {
                    board->squares[i][j] = MINIMAX_O_SQUARE;
                }

                score = minimax(&board,!is_Xs_turn);

                scores[location] = score;
                moves[location].row = i;
                moves[location].column = j;

                board->squares[i][j] = MINIMAX_EMPTY_SQUARE;
            }
            location++;
        }
    }
}

void printBoard(tictactoe_board_t *board, bool is_Xs_turn)
{
    for(uint8_t i = 0; i < TICTACTOE_BOARD_ROWS;i++)
    {
        printf("\n");
        for(uint8_t j = 0; j < TICTACTOE_BOARD_COLUMNS;j++)
        {
            tictactoe_square_state_t spot = board->squares[i][j];
            if(spot == MINIMAX_EMPTY_SQUARE)
            {
                printf("%c  ",'-');
            }
            else if(spot == MINIMAX_X_SQUARE)
            {
                printf("%c  ",'X');
            }
            else if(spot == MINIMAX_O_SQUARE)
            {
                printf("%c  ",'O');
            }

            if(j == 2)
            {
                //printf("\n");
            }
            
        }
    }
    printf("\n");
}





