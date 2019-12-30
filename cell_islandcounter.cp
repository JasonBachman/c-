#include "cellgrid.h"
#include <iostream>
#include <fstream>
using namespace std;

// reads a file containing 1's and 0's and the dimesnsions to expect and
// creates a Cellgrid object
Cellgrid::Cellgrid(const char *fname, int m, int n) {
    // assign row and col counters
    rows = m;
    cols = n;
    // create the grid on the heap, this will have to be deallocated later in
    // the destructor
    grid = new bool[rows*cols];

    // create a file reader stream to read data from a file
    ifstream infile;

    // open a stream to the given file
    infile.open(fname);

    // we are using row-major order in order to store this grid in 1D
    // instead of accessing grid like grid[a][b], we instead do:
    // grid[(a * number of columns) + b]
    for(int i = 0; i < rows; i++) {
        // calculate "(a * number of columns)" from above
        // in order to save some unnecessary computation
        int base = i * cols;
        for(int offset = 0; offset < cols; offset++) {
            // read data from filestream and store it in grid
            infile >> grid[base + offset];
        }
    }

    // close the filestream once we are done with it
    infile.close();
}

// destruct object where not implicit to the program
Cellgrid::~Cellgrid() {
    // since we allocated memory on the heap, we must deallocate that memory
    delete[] grid;
}

// this is the function call which will be made by the autograder to test
// your implementation for problem 1. (row, col) is the "start point" for
// counting the cells, conn is the type of connection to consider (4 or 8).
int Cellgrid::countCells(int row, int col, int conn) {
	int count = 0;
	if(grid[((row-1)*cols)+col-1] != 1){
		return 0;
	}
	else if(grid[((row-1)*cols)+col-1] == 1){
		grid[((row-1)*cols)+col-1] = 0;
		
		count++;
		if(conn == 4){
			return count + countCells(row+1,col,conn) + countCells(row-1,col,conn) + countCells(row,col+1,conn) + 
			countCells(row,col-1,conn);
		} 
		else if(conn == 8){
			return count + countCells(row+1,col,conn) + countCells(row+1,col+1,conn) + countCells(row+1,col-1,conn) + countCells(row-1,col,conn) + countCells(row-1,col+1,conn) + countCells(row-1,col-1,conn) + countCells(row,col+1,conn) + countCells(row,col-1,conn);
		}
	}
	
	
	
	
	return 69;
	
	
    // TODO:
    // implement solution for problem 1.

    // this is where your private helper method which does the
    // backtracking should be called
    
    // this will prevent a compiler error but should be changed
    // to return the cell count you have found
}

// this is the funciton call which will be made by the autograder to test
// your implementation for problem 2. conn is the type of connection
// to consider (4 or 8).





void Cellgrid::sink(int row, int col, int conn){
	
	if(grid[(row*cols) + col] == 1){
		grid[(row*cols) + col] = 0;
		if(conn == 4){
			
			if(row!=0){sink(row-1,col,conn);}
			if(row!=rows-1){sink(row+1,col,conn);}
			if(col!=0){sink(row,col-1,conn);}
			if(col!=cols-1){sink(row,col+1,conn);}
			

		}
		else if(conn == 8){
			//if(row != 0 && row != rows-1 && col != 0 && col != cols){
				if(row!=0){
					if(col!=0){sink(row-1,col-1,conn);}
					sink(row-1,col,conn);
					if(col != cols-1){sink(row-1,col+1,conn);}
				}
				
				if(col!=0){sink(row,col-1,conn);}
				if(col != cols-1){sink(row,col+1,conn);}
				if(row != rows-1){
					sink(row+1,col,conn);
					if(col!=0){sink(row+1,col-1,conn);}
					if(col!= cols-1){sink(row+1,col+1,conn);}
			}
		}
	}
}





int Cellgrid::countBlobs(int conn) {
    //TODO:
    // implement solution for problem 2

    // this is where your private helper method which does the
    // backtracking should be called

    // this will prevent compiler error but should be changed
    // to return the blob count which you have found using
    // your helper function
    int count = 0;
    
    
    for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(grid[(i*cols)+j] == 1){
				sink(i,j, conn);
				//cout << "count: " << count << endl;
				//print();
				count++;
			}
			
		}
		
	}
    
    
    
    
    
    
    return count;
    
    
    
    
    
}    
    
    
    
    


void Cellgrid::print() {
    for(int i = 0; i < rows; i++) {
        int base = i * cols;
        std::cout << grid[base];
        for(int offset = 1; offset < cols; offset++) {
            std::cout << ' ' << grid[base + offset];
        }
        std::cout << std::endl;
    }
}
