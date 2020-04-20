/*
----------------------------------------------------------------

* Multiprocesadores: Actividad 04, TBB

* Archivo: Solución TBB

* Fecha: 17-Octubre-2019

* Autores: A01209499, Gerardo Naranjo
           A01209351, Iván Ochoa

--------------------------------------------------------------
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "cppheader.h"

//STL libraries shortcut
using namespace std;
using namespace tbb;

//Board Dimensions
#define ROWS 10000
#define COLUMNS 10000

//tbb variables
const int SIZE = COLUMNS;
const int GRAIN = max(COLUMNS/100,1);

//Number of generations to simulate
#define GENERATIONS 1

//TBB classes and operands definitions

class ClearRow {
private:
	int *row;

public:
	ClearRow(int *row) 
		: row(row) {}

	void operator() (const blocked_range<int> &r) const {
		for (int i = r.begin(); i != r.end(); i++) {
			row[i] = 0;
		}
	}
};

class CopyRows {
private:
	int *destinationRow, *sourceRow;

public:
	CopyRows(int *destinationRow, int *sourceRow) 
		: destinationRow(destinationRow), sourceRow(sourceRow) {}

	void operator() (const blocked_range<int> &r) const {
		for (int i = r.begin(); i != r.end(); i++) {
			destinationRow[i] = sourceRow[i];
		}
	}
};


int* createRow(){

    //Allocate memory as an array
    int* row = (int*) malloc(COLUMNS*sizeof(int));

    //Checks if row has allocated memory, throws error otherwise
    if(row == NULL){
        cout<<"Row not created."<<endl;
        exit(1);
    }

    return row;
}

int** createBoard(){

    //Allocate memory as a matrix
    int** board = (int**) malloc(ROWS*sizeof(int*));

    //Checks if board has allocated memory, throws error otherwise
    if(board == NULL){
        cout<<"Board not created."<<endl;
        exit(1);
    }

    for(int i = 0; i < ROWS; ++i){
        board[i] = createRow(); 
    }

    return board;
}

void initializeBoard(int** board){

    //Checks if board has allocated memory, throws error otherwise
    if(board == NULL){
        cout<<"Board is not created."<<endl;
        exit(1);
    }
    
    // Initialize random seed
    srand (time(NULL));

    //Randomized initialization of alive and dead cells in the board
    //Uses individual bits of the randomized value to reduce by a factor of 31 the number of calls to rand()

    int randBitIdx = 0;
    int randomBitMask = rand();

    for(int i = 0; i < ROWS; ++i){
        for(int j = 0; j < COLUMNS; ++j){
            if(randBitIdx == 31){
                randBitIdx = 0;
                randomBitMask = rand();
            }
            board[i][j] = ( randomBitMask & (1<<randBitIdx) )? 1:0;
            ++randBitIdx; 
        }
    }

}

void showBoard(int** board){
    //Checks if board has allocated memory, throws error otherwise
    if(board == NULL){
        cout<<"Board is not created."<<endl;
        exit(1);
    }

    //Prints board representing alive cells with a '*' and dead cells with a '.'
    for(int i = 0; i < ROWS; ++i){
        for(int j = 0; j < COLUMNS; ++j){
            if(board[i][j]){
                cout<<"*";
            } else{
                cout<<".";
            }
        }
        cout<<endl;
    }
}

int checkRules(int neighbors, int state){
    //state = 0 -> cell is dead
    //state = 1 -> cell is alive

    //Cell is dead
    if(state == 0){
        //Is born
        if(neighbors == 3){
            return 1;
        } else{
            //Remains dead
            return 0;
        }
    } else{ //Cell is alive
        //Remains alive
        if(neighbors == 2 || neighbors == 3){
            return 1;
        } else{ //Dies
            return 0;
        }
    }

    return 0;
}

//Checks whether such position exists in the board or not
bool validPosition(const int &row, const int &col){
    return (row >= 0 && col >= 0 && row < ROWS && col < COLUMNS);
}

int getNeighbors(const int &row, const int &col, int** board, int* prevRow){

    int numberOfNeighbors = 0;

    int dr[8] = {0,0,1,-1,1,-1,1,-1};
    int dc[8] = {1,-1,0,0,-1,1,1,-1};

    //Iterates over each possible neighbor (8)

    for(int neighbor = 0; neighbor < 8; ++neighbor){
        int nr = row+dr[neighbor];
        int nc = col+dc[neighbor];

        //Checks if current neighbor exists or if its out of board's boundaries
        if(validPosition(nr,nc)){

            //if it's a neighbor from above, check the stored Row (which keeps the previous value) instead of the current board
            if(dr[neighbor] == -1){
                if(prevRow[nc])    ++numberOfNeighbors;
            } else{
                if(board[nr][nc])  ++numberOfNeighbors;
            }
        }
    }

    return numberOfNeighbors;
}

class IterateRowToNxtGen {
private:
    int rowIdx;
	int **board;
    int *prevRow, *currRow;

public:
	IterateRowToNxtGen(int rowIdx, int **board, int *prevRow, int *currRow) 
		: rowIdx(rowIdx), board(board), prevRow(prevRow), currRow(currRow) {}

	void operator() (const blocked_range<int> &r) const {
		for (int i = r.begin(); i != r.end(); i++) {
            //Get how many neighbors are alive around this cell
            int neighbors = getNeighbors(rowIdx,i,board,prevRow);

            //Apply rules to determinte the current cell's state
			currRow[i] =  checkRules(neighbors, currRow[i]);
		}
	}
};


void nextGeneration(int** board, int* prevRow, int* currRow){

    //Initializes prevRow with zeroes
    parallel_for(blocked_range<int>(0, SIZE, GRAIN),  ClearRow(prevRow));

    for(int i = 0; i < ROWS; ++i){
        
        //Makes a copy of the current row
        parallel_for(blocked_range<int>(0, SIZE, GRAIN),  CopyRows(currRow,board[i]));

        //Iterates row through next generetion
        parallel_for(blocked_range<int>(0, SIZE, GRAIN),  IterateRowToNxtGen(i,board,prevRow,board[i]));

        //Swaps currRow and prevRow pointers
        int* auxPtr = prevRow;
        prevRow = currRow;
        currRow = auxPtr;
    }
}

void runGame(int generations, int** board){

    //Checks if board has allocated memory, throws error otherwise
    if(board == NULL){
        cout<<"Board is not created."<<endl;
        exit(1);
    }

    //Allocates blocks of memory for auxiliar variables
    int* auxRow  = createRow();
    int* auxRow2 = createRow();

    //Iterates through generations one by one

    for(int generation = 0; generation <= generations; ++generation){
        
        //Show board in current generation if board size is less than 1000
        if(ROWS*COLUMNS <= 1000){
            cout<<"Generation "<<generation<<":"<<endl;
            showBoard(board);
        } else{
            cout<<"Generation "<<generation<<"..."<<endl;
        }

        //Simulates next generation in the board
        nextGeneration(board, auxRow, auxRow2);
    }
}


int main(){

    double ms;
    Timer t;

    int **board = createBoard();
    
    t.start();
    initializeBoard(board);
    runGame(GENERATIONS, board);
    ms = t.stop();
    
    std::cout << '\n' << "avg time = " << ms << " ms" << '\n';

    return 0;
}
