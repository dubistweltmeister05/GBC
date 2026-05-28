#include <stdio.h>
#include <stdlib.h>

#define col 3
#define row 2

/*
we are trying to avoid the simple matrix[][]
pattern, so the logic being applied here is as follows - 

a matrix decays into a pointer to an array of something 
- int (*)[rows]

this means that dereferencing a matrixz variable gives the pointer to 
the base of an array of length [rows]. 

*(matrix+i) -> i=0 gives a pointer to the 0th array of length [rows]
               i=1 gives a pointer to the 1st array of length [rows] 
               i=2 gives a pointer to the 2nd array of length [rows] 

add to this pointer the index within the array that you want to be at
and you get the element that you've wanted.

*(matrix+i)+j -> i=0 gives a pointer to the 0th array of length [rows]
                    j=0 gives a pointer to 0th element in the 0th array.
                    j=1 gives a pointer to 1st element in the 0th array. 
                 i=1 gives a pointer to the 1st array of length [rows]
                    j=0 gives a pointer to 0th element in the 1st array.
                    j=1 gives a pointer to 1st element in the 1st array.
                 i=2 gives a pointer to the 2nd array of length [rows] 
                    j=0 gives a pointer to 0th element in the 2nd array.
                    j=1 gives a pointer to 1st element in the 2nd array.
*/
void traverse_matrix(int mat[][row], int column, int rows)
{
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%d ", *(*(mat+i)+j));
        }
        printf("\n");
    }
}

int main()
{

    int matrix[col][row] = {{1, 2}, {3, 4}, {5, 6}};

    traverse_matrix(matrix, col, row);

    return 0;
}