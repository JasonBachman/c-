
#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
// reads a file containing a sudoku puzzle represented as
// 9 rows, each consisting of 9 comma-separated values
Sudoku::Sudoku(const char *fname)
{
    // create a file reader stream to read data from a file
    ifstream infile;
    // will store lines and numbers
    string line, number;
    // index to write value to in puzzle
    int i = 0;
    // open a stream to the given file
    infile.open(fname);
    // get a line of input from the file
    while (getline(infile, line))
    {
        // store the line inside a stringstream
        stringstream parser(line);
        // use stringstream to split line along ','
        while (getline(parser, number, ','))
        {
            // convert string to an integer, store it, and update iterator
            puzzle[i++] = stoi(number);
        }
    }
    // close the filestream once we are done wiht it
    infile.close();
}
// destruct Sudoku object
Sudoku::~Sudoku()
{
    // since we never allocated any memory on the heap, we don't need
    // to define behavior for the deconstructor
}
// this is the funciton call which will be made by the autograder to test
// your implementation for problem 3. It takes no parameters and
// should overwrite the 0s in puzzle to so that it represents a solved puzzle
bool Sudoku::solve()
{
    int row = 0;
    int column = 0;
    
    
    if (!emptyspot(&row, &column)){return true;}
    
    for (int num = 1; num <= 9; num++)
    {
        if (safe(num, row, column))
        {
            int base = row * 9;
            //
            //
            puzzle[base + column] = num;
            //
            if (solve())
            {
				//done
                return true;
            }
            puzzle[base + column] = 0;
        }
    }
    return false;
}





bool Sudoku::safe_row(int num, int row, int column){
	
	
	for (int i = 0; i < 9; i++)
    {
        if (puzzle[(row * 9) + i] == num && column != i)
        {
            return false;
        }
    }
    
    return true;
	
	
	
	
}

bool Sudoku::safe_col(int num, int row, int column)
{
	
	for (int i = 0; i < 9; i++)
    {
        if (puzzle[(i * 9) + column] == num && row != i)
        {
            return false;
        }
    }
    return true;
	
	
}	






bool Sudoku::safe(int num, int row, int column)
{
	
	if(safe_col(num, row, column) && safe_row(num, row, column) && safe_box(num, row, column)){
			return true;
		}
	else{return false;}
	
}	
    
    
    
    
 bool Sudoku::safe_box(int num, int row, int column){
    
    
    
    
    int box_x = column / 3;
    int box_y = row / 3;
    for (int i = box_y * 3; i < box_y * 3 + 3; i++)
    {
        for (int j = box_x * 3; j < box_x * 3 + 3; j++)
        {
            if (puzzle[(i * 9) + j] == num && i != row && j != column)
            {
                return false;
            }
        }
    }
    return true;
}






int Sudoku::emptyspot(int *row, int *column)
{
    for (*row = 0; *row < 9; (*row)++)
    {
        for (*column = 0; *column < 9; (*column)++)
        {
            int base = (*row) * 9;
            if (puzzle[base + (*column)] == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}
// this function prints your puzzle in 2D format with commas
// separating your values
void Sudoku::print()
{
    for (int i = 0; i < 9; i++)
    {
        std::cout << puzzle[i * 9];
        int base = i * 9;
        for (int offset = 1; offset < 9; offset++)
        {
            std::cout << ',' << puzzle[base + offset];
        }
        std::cout << std::endl;
    }
}


