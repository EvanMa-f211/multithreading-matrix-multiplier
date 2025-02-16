# Multithreading Matrix Multiplier
This repository provides C functions that perform matrix multiplication in parallel using threads.
## Details

### ```Matrix``` Structure
```C=
struct Matrix{
    int** mat;
    int r;
    int c;
}
```
```mat``` is a pointer to a 2D array representing the matrix, where ```r``` and ```c``` represent the number of rows and columns.
### Functions
#### ```Matrix* New_Matrix(int r, int c)```
This function creates a new matrix with ```r``` rows and ```c``` columns, initialized to 0.
* return ```NULL``` if an error occurs during ```malloc``` or ```calloc```.
* return ```1``` if ```r``` or ```c``` less than 1.
#### ```Matrix* array_to_matrix(int* p, int r, int c)```
This function converts the array ```p``` to a matrix with ```r``` rows and ```c``` columns.
* return ```NULL``` if an error occurs during ```malloc``` or ```calloc```.
* return ```1``` if ```r``` or ```c``` is less than 1.
#### ```Matrix* matrix_multiplier(Matrix* m1, Matrix* m2, int nthreads)```
This function multiplies matrix ```m1``` and ```m2``` using up to ```nthreads``` threads and returns with a pointer to the resulting product.
* return ```NULL``` if an error occurs during ```malloc``` or ```calloc```.
* return ```1``` if
    * ```m1``` or ```m2``` is ```NULL```
    * ```m1->c``` $\ne$ ```m2->r```
    * ```m1->r``` or ```m1->c``` or ```m2->c``` less than 1
    * ```nthreads``` less than 0
* If ```nthreads``` is 0, it will be set to ```DEFAULT_NTHREADS```, which is defined in ```matrix_multiplier.h```.
## Usage
Download ```matrix_multiplier.c``` and  ```matrix_multiplier.h```, then include the header file.
## Example
I wrote ```main.c``` and some example input files to demonstrate how to use them.
### Description
Input two matrices $A$ and $B$, then return $AB$.  
For each matrix:
* The first line contains two integers representing the number of rows and columns. 
* The following lines contain the elements of the matrix.
### Compile and Run
```
$ gcc -c matrix_multiplier.c -o matrix_multiplier.o
$ gcc -c main.c -o main.o
$ gcc -o main main.o matrix_multiplier.o
$ ./main
```
