#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define BOARD_HEIGHT		12
#define BOARD_WIDTH		12
#define WALL_SIZE		1
#define DEFULT_VALUE '.'
#define WALL_VALUE '*'
#define MINES_FILE "mines.txt"
#define MAX_CHAR_READ 1024
#define MAX_BOMB 144

// This general procedure initializes a matrix with a given value
//-----------------------------------------------------------------------------
// MineSweeper
// ---------
//
// General : This general procedure initializes a matrix and the boarders with a given value
//
// Input :  mat - the matrix, matrix_hight - matrix hight, matrix_width - matrix width,
//			value - the defult value in the game, border - the char that the borders will be
//
// Process : using 2 for loops to work on all the places in the matrix.
//
// Output : None.
//-----------------------------------------------------------------------------
// Programmer : Yotam Levit
// Student No : 200041119
// Date : 15.10.2019
//-----------------------------------------------------------------------------
void init_matrix(char* mat,
	int matrix_height,
	int matrix_width,
	char value, char border)
{
	int i, j;
	for (i = 0; i < matrix_height; i++)
	{
		for (j = 0; j < matrix_width; j++)
		{
			if (j == 0 || i == 0 || j == 13 || i == 13)
				mat[i * matrix_width + j] = border;
			else
				mat[i * matrix_width + j] = value;;
		}
	}
}

// This function loads the locations of the mines from the input file, setting
// loaded mines on the board and returns how many mines were set. If the input
// file didn’t open the function returns -1.
//-----------------------------------------------------------------------------
// MineSweeper
// ---------
//
// General :  This function loads the locations of the mines from the input file, setting
//		      loaded mines on the board and returns how many mines were set. If the input
//			  file didn’t open the function returns -1.
//
// Input :  game_board - the matrix with the answers of where are the bombs
//
// Process : reading a string from mine.txt file then using a protocol to understend where
//			 each bomb should be placed. the protocol - in the string the row and the col
//			 of each bomb are in the next order: row space col (then next bomb) space row space col
//
// Output : the number of mines in the game.
//-----------------------------------------------------------------------------
// Programmer : Yotam Levit
// Student No : 200041119
// Date : 15.10.2019
//-----------------------------------------------------------------------------
int  set_mines(char	game_board[BOARD_HEIGHT + 2 * WALL_SIZE]
	[BOARD_WIDTH + 2 * WALL_SIZE])
{
	FILE* fptr;
	int search_col = 0;
	int have_col = 0;
	int have_row = 0;
	int double_digit = 0;
	int row = 0, col = 0;
	int value = 0;
	int count_mines = 0;
	char str[MAX_CHAR_READ];
	char* pstr;
	fptr = fopen(MINES_FILE, "r");
	if (fptr == NULL)
	{
		printf("Could not open file %s", MINES_FILE);
		return -1;
	}
	while (fgets(str, MAX_CHAR_READ, fptr) != NULL);
	pstr = str;
	while (*pstr)
	{
		while (*pstr != ' ' && *pstr)
		{
			if (double_digit)
				value *= 10;
			value += *pstr - '0';
			double_digit = 1;
			pstr++;
		}
		pstr++;
		double_digit = 0;
		if (have_row)
		{
			col = value;
			have_col = 1;
		}
		else
		{
			row = value;
			have_row = 1;
		}
		if (have_col && have_row)
		{
			//printf("Set Boamb in - row: %d col: %d\n", row, col);
			game_board[row][col] = 'B';
			count_mines++;
			have_col = 0;
			have_row = 0;
		}
		value = 0;
	}
	fclose(fptr);
	return count_mines;

}

// This procedure prints the game board on the screen 
//-----------------------------------------------------------------------------
// MineSweeper
// ---------
//
// General :  This procedure prints the game board on the screen.
//
// Input :  game_board - the matrix with that is shown to the user with hide bombs
//
// Process : using 2 for loops to print each char in the matrix
//
// Output : None.
//-----------------------------------------------------------------------------
// Programmer : Yotam Levit
// Student No : 200041119
// Date : 15.10.2019
//-----------------------------------------------------------------------------
void print_board(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE]
	[BOARD_WIDTH + 2 * WALL_SIZE])
{
	int i, j;
	for (i = 0; i < BOARD_HEIGHT + 2 * WALL_SIZE; i++)
	{
		for (j = 0; j < BOARD_WIDTH + 2 * WALL_SIZE; j++)
		{
			printf(" %c ", game_board[i][j]);
		}
		printf("\n");
	}
}

// This function returns how many mines there are around a given location
//-----------------------------------------------------------------------------
// MineSweeper
// ---------
//
// General :  This function returns how many mines there are around a given location.
//
// Input :  game_board - the matrix with that has all the locations of the bombs and all the blanks,
//			curr_row - the current row position that the program will check arround,
//			curr_col - the current col position that the program will checl arround.
//
// Process : using if statments to check the 8 possible options for a bomb to be 
//			 next a specific row and col.
//
// Output : the number of bombs next to a specific location in the matirx.
//-----------------------------------------------------------------------------
// Programmer : Yotam Levit
// Student No : 200041119
// Date : 15.10.2019
//-----------------------------------------------------------------------------
int  count_mines_around(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE]
	[BOARD_WIDTH + 2 * WALL_SIZE],
	int	curr_row,
	int	curr_col)
{
	int count_bomb = 0;
	count_bomb += game_board[curr_row - 1][curr_col - 1] == 'B' ? 1 : 0;
	count_bomb += game_board[curr_row - 1][curr_col + 1] == 'B' ? 1 : 0;
	count_bomb += game_board[curr_row - 1][curr_col] == 'B' ? 1 : 0;
	count_bomb += game_board[curr_row + 1][curr_col + 1] == 'B' ? 1 : 0;
	count_bomb += game_board[curr_row + 1][curr_col - 1] == 'B' ? 1 : 0;
	count_bomb += game_board[curr_row + 1][curr_col] == 'B' ? 1 : 0;
	count_bomb += game_board[curr_row][curr_col - 1] == 'B' ? 1 : 0;
	count_bomb += game_board[curr_row][curr_col + 1] == 'B' ? 1 : 0;
	return count_bomb;
}

//init game
//-----------------------------------------------------------------------------
// MineSweeper
// ---------
//
// General :  This function initializes the board game and the bombs location board.
//			  if succses returns the number of bombs that were placed, if there are no bombs
//			  return 0 and if the board if full with bombs the program will retirn -1.
//
// Input :  game_board - the matrix with that has all the locations of the bombs and all the blanks,
//			game_board - the matrix with the answers of where are the bombs
//
// Process : using init_matrix function too initializes the boards and set_mines to set the mines
//			 in the answers then checking the nummber of bombs in the game and return the answer
//
// Output : if succses returns the number of bombs that were placed, if there are no bombs
//			  return 0 and if the board if full with bombs the program will retirn -1.
//-----------------------------------------------------------------------------
// Programmer : Yotam Levit
// Student No : 200041119
// Date : 15.10.2019
//-----------------------------------------------------------------------------
int init_game(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE]
	[BOARD_WIDTH + 2 * WALL_SIZE],
	char bomb_answer[BOARD_HEIGHT + 2 * WALL_SIZE]
	[BOARD_WIDTH + 2 * WALL_SIZE])
{
	int return_code = 1;
	init_matrix(game_board, BOARD_HEIGHT + 2 * WALL_SIZE, BOARD_WIDTH + 2 * WALL_SIZE, DEFULT_VALUE, WALL_VALUE);
	init_matrix(bomb_answer, BOARD_HEIGHT + 2 * WALL_SIZE, BOARD_WIDTH + 2 * WALL_SIZE, DEFULT_VALUE, WALL_VALUE);
	return_code = set_mines(bomb_answer);
	if (return_code == 0)
	{
		printf("There are no bombs on the board\n");
		return_code = 0;
	}
	else if (return_code == MAX_BOMB)
	{
		printf("The board is full with bombs(no free space)\n");
		return_code = -1;
	}
	return return_code;
}

//get input from ussere
//-----------------------------------------------------------------------------
// MineSweeper
// ---------
//
// General :  This function gets the input from the user (row and col).
//
// Input :  row_input - a pointer for an int that represent the row index in the place
//			that the user want to choose.
//			col_input - a pointer for an int that represent the col index in the place
//			that the user want to choose.
//
// Process : do while to check that the input in valid.
//
// Output : None.
//-----------------------------------------------------------------------------
// Programmer : Yotam Levit
// Student No : 200041119
// Date : 15.10.2019
//-----------------------------------------------------------------------------
void get_input(int* row_input, int* col_input)
{
	do {
		printf("Enter the row of the place that you choose (1-12): ");
		scanf("%d", row_input);
		if (*row_input == 999)
		{
			return;
		}
	} while (*row_input < 1 || *row_input > 12);
	if (row_input == 999)
	{
		return;
	}
	do {
		printf("Enter the col of the place that you choose (1-12): ");
		scanf("%d", col_input);
	} while (*col_input < 1 || *col_input > 12);
}

//-----------------------------------------------------------------------------
// MineSweeper
// ---------
//
// General :  This function is operating according to the input from the user.
//			  if there is a bomb the program will operate as needed,
//			  if not the program will check the number of bombs arround the index
//			  that the user choose.
//
// Input :  game_board - the matrix with that has all the locations of the bombs and all the blanks,
//			game_board - the matrix with the answers of where are the bombs,
//			curr_row - the current row position that the program will check arround,
//			curr_col - the current col position that the program will checl arround.
//
// Process : checks if there is a bomb in the index that the user choose if yes the
//			 function will stop and show a massege, if there is no bomb hte function
//			 will check how many mines there are arround the cuurent index (row and col)
//			 and insert the number in the cuurent place.
//
// Output : if there is a bomb the program will return 'B' if not the program will return
//			the number of bombs arround the current index.
//-----------------------------------------------------------------------------
// Programmer : Yotam Levit
// Student No : 200041119
// Date : 15.10.2019
//-----------------------------------------------------------------------------
char input_operation(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE]
	[BOARD_WIDTH + 2 * WALL_SIZE],
	char bomb_answer[BOARD_HEIGHT + 2 * WALL_SIZE]
	[BOARD_WIDTH + 2 * WALL_SIZE],
	int curr_row, int curr_col)
{
	int bomb_arround;
	if (bomb_answer[curr_row][curr_col] == 'B')
	{
		printf("/////////////////////////////////////\n");
		printf("/////////////////////////////////////\n\n");
		printf("You stepped on a bomb - game over\n");
		game_board[curr_row][curr_col] = 'B';
		return 'B';
	}
	game_board[curr_row][curr_col] = (char)(count_mines_around(bomb_answer, curr_row, curr_col) + '0');
	printf("There are %c mines arround the choosen spot\n", game_board[curr_row][curr_col]);
	return game_board[curr_row][curr_col];
}

//main game function and operating
//-----------------------------------------------------------------------------
// MineSweeper
// ---------
//
// General :  This function is operating the main game - starts the game and operating the main loop.
//
// Input :  game_board - the matrix with that has all the locations of the bombs and all the blanks,
//			game_board - the matrix with the answers of where are the bombs,
//			number_of_bombs - the number of bombs in the game.
//
// Process : entering the main loop - prints the board,
//			 getting input  and calling the operate functiopn
//
// Output : if the user won the game the profram will show a massege.
//-----------------------------------------------------------------------------
// Programmer : Yotam Levit
// Student No : 200041119
// Date : 15.10.2019
//-----------------------------------------------------------------------------
void start_game(char game_board[BOARD_HEIGHT + 2 * WALL_SIZE]
	[BOARD_WIDTH + 2 * WALL_SIZE],
	char bomb_answer[BOARD_HEIGHT + 2 * WALL_SIZE]
	[BOARD_WIDTH + 2 * WALL_SIZE],
	int num_of_bomb)
{
	int row_input = 0, col_input = 0, count_space_found = 0;
	char input_efect = NULL;
	while (row_input != 999 && col_input != 999
		&& BOARD_HEIGHT * BOARD_WIDTH - num_of_bomb != count_space_found && input_efect != 'B')
	{
		print_board(game_board);
		get_input(&row_input, &col_input);
		if (row_input == 999 || col_input == 999)
		{
			input_efect = 'E';
			break;
		}
		input_efect = input_operation(game_board, bomb_answer, row_input, col_input);
		count_space_found++;
	}
	if (input_efect == 'E')
		printf("Thank you for playing ... BYE");
	if (input_efect == 'B')
		print_board(game_board);
	if (BOARD_HEIGHT * BOARD_WIDTH - num_of_bomb == count_space_found)
	{
		printf("\n\nYou won the game!!!!!! :) ");
	}
}

//-----------------------------------------------------------------------------
// MineSweeper
// ---------
//
// General :  the first function that is called - creates the matrixes, init them
//			  and calling the main game funtion.
//
// Input :  None.
//
// Process : creates the matrixes, init them if the board if full of mines or empty of them
//			 the function wont start the game if everything is valid - calling the main game funtion.
//
// Output : the number of bombs next to a specific location in the matirx.
//-----------------------------------------------------------------------------
// Programmer : Yotam Levit
// Student No : 200041119
// Date : 15.10.2019
//-----------------------------------------------------------------------------
void main()
{
	int number_of_bomb;
	char end;
	char game_board[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_WIDTH + 2 * WALL_SIZE];
	char bomb_answer[BOARD_HEIGHT + 2 * WALL_SIZE][BOARD_WIDTH + 2 * WALL_SIZE];
	number_of_bomb = init_game(game_board, bomb_answer);
	if (number_of_bomb != -1 || number_of_bomb != 0)
	{
		start_game(game_board, bomb_answer, number_of_bomb);
	}
	rintf(" Press ENTER key to Continue\n");
	getchar();	
}
