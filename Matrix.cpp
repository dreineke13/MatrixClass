#include "Matrix.hpp"
#include <limits>

void Matrix::output( std::ostream &out ) const
{  
  for(int i = 0; i < A.size(); i++)
    out << A[i] << " ";
  
  return;
}
//implementation of the defualt constructor
Matrix::Matrix()
{
    //sets the size of the matrix
    this->m = 2;
    this->n = 2;
    //pushes the value 0 to the matrix 4 times
    this->A.push_back(0);
    this->A.push_back(0);
    this->A.push_back(0);
    this->A.push_back(0);
}

//put the other constructors here
//this is the matrix constructor implementation with the vector and number of columns provided
Matrix::Matrix(const std::vector<int>& A, unsigned int n) {
    unsigned int size = A.size();
    if (size == 0 || n < 1) { //makes sure both n and the size of A are not 0/ less than 0
        std::vector<int> C;
        this->A = C;
        this->n = 0;
        this->m = 0;
    }
    else {
        unsigned int k = size % n; //makes sure n divides A with no remaineders
        if (k != 0) {
            std::vector<int> C;
            this->A = C;
            this->n = 0;
            this->m = 0;
        }
        else {
            unsigned int l = size / n;
            this->A = A;
            this->n = n;
            this->m = l;
        }
    }
}

//this is the matrix constructor implementation with the vector, number of columns and rows provided
Matrix::Matrix(const std::vector<int>& A, unsigned int m, unsigned int n) {
    unsigned int i = m * n;
    if (A.size() == 0 || A.size() != i || m < 1 || n < 1) {
        std::vector<int> C;
        this->A = C;
        this->n = 0;
        this->m = 0;
    }
    else {
        this->A = A;
        this->n = n;
        this->m = m;
    }
}


//this is the implementation of the get function
//with only one 'search' term
int Matrix::get(unsigned int i) const{
    //this checks to make sure the term is within the bounds of the matrix
    unsigned int k = this->m * this->n;
    if (i >= k) {
        return std::numeric_limits<int>::min();
    }
    else if (i < 0) {
        return std::numeric_limits<int>::min();
    }
    //if it is, it returns the value at that position
    else {
        return this->A.at(i);
    }
}

//the implementation of the get function with 2 inputs
int Matrix::get(unsigned int i, unsigned int j) const{
    //this checks to make sure the 'i' term is within the bounds of the matrix
    if (i >= this->m) {
        return std::numeric_limits<int>::min();
    }
    else if (i < 0) {
        return std::numeric_limits<int>::min();
    }
    else {
        if (j >= this->n) {
            //this checks and makes sure the 'j' term is within the matrix
            return std::numeric_limits<int>::min();
        }
        else if (j < 0) {
            return std::numeric_limits<int>::min();
        }
        else{
            //if it is within the bounds, it returns the value at that position
            //i * n gives the column, adding j gives the position within that column
            unsigned int k = j * this->m;
            k += i;
            return A.at(k);
        }
    }
}

//the implementaion of the size function
unsigned int Matrix::size(unsigned int dim) const {
    //if the input is one, it returns the rows
    if (dim == 1) {
        return m;
    }
    //if the input is two, it returns the columns
    else if (dim == 2) {
        return n;
    }
    //if the input is neither, it returns 0
    else {
        return 0;
    }
}

//the implementation of the add function
const Matrix Matrix::add(const Matrix& rhs) const {
    std::vector<int> a; //a vector to hold the sums
    //this checks to make sure the matricies are the same size
    if (rhs.size(1) != this->m || rhs.size(2) != this->n) {
        return Matrix(a, 0, 0);
    }

    unsigned int k = this->n * this->m; //gets the total number of elements in the matrix
    for (int i = 0; i < k; i++) {
        int val = A.at(i) + rhs.get(i);
        a.push_back(val); //the addition is perfomed element-wise here
    }
    return Matrix(a, m, n); //returns the new matrix
}

//this is the implementation of the subtraction function
const Matrix Matrix::sub(const Matrix& rhs) const {
    //this makes the matrix negative because adding a negative
    //is the same as subtracting a positive
    Matrix A = rhs.mult(-1);
    //add the newly negative matrix to the second matrix
    Matrix B = this->add(A);
    //return the difference
    return B;
}


//this is the implementation of the multiplication by a constant function
const Matrix Matrix::mult(int c) const {
    std::vector<int> a;//the vector to hold the new matrix
    unsigned int size = this->n * this->m; //the size of the matrix
    //this for loop iterates through each element of the matrix and multiplies it by the constant
    for (int i = 0; i < size; i++) {
        int val = this->A.at(i) * c;
        a.push_back(val);
    }
    return Matrix(a, m, n);
}

//this is the one-dimensional set function
bool Matrix::set(unsigned int i, int ai) {
    unsigned int k = this->n * this->m;
    if (i >= k) { //makes sure i is within the bounds
        return false;
    }
    if (i < 0) {
        return false;
    }
    std::vector<int> C;
    for (int j = 0; j < k; j++) { //this iterates through the vector A
        if (i != j) { //checks to see if the vector is at the chosen spot
            int ele = this->get(j); //gets the element at location j
            C.push_back(ele);

        }
        else { //if it's at the chosen spot, it replaces the value
            C.push_back(ai);
        }
    }
    this->A = C; //replaces A with the new vector
    return true;
}

//the two-dimensional set function implementation
bool Matrix::set(unsigned int i, unsigned int j, int aij) {
    if (i >= this->m || i < 0) {//makes sure the i is in range
        return false;
    }
    else if (j >= this->n || j < 0) { //makes sure the j is in range
        return false;
    }
    std::vector<int> C; //the new vector for the matrix
    for (int x = 0; x < this->size(2); x++) { //this iterates through the columns
        for (int y = 0; y < this->size(1); y++) { //this iterates through the rows
            if (x != j || y != i) { //if the current spot is not the selected spot,
                int z = (x * this->size(1)) + y; //the curruent spot is identified
                C.push_back(this->get(z)); //and the element in the current spot is added to C
            }
            else {// if the current spot is the selected spot
                C.push_back(aij); //it gets added to C instead of the old element
            }
        }

    }
    this->A = C; //swaps A with the new vector
    return true;
}


//the implementation of the equal function
bool Matrix::equal(const Matrix& rhs) const {
    //this returns false if the matricies are not the same size
    if (rhs.size(1) != this->m || rhs.size(2) != this->n) {
        return false;
    }
    unsigned int k = this->n * this->m;
    //this makes sure the matricies have the same elements
    for (int i = 0; i < k; i++) { //this for loop adds each element, one-by-one
        if (this->A.at(i) != rhs.get(i)) {
            return false;
        }
    }
    return true;
}

//the implementation of the transpose function
const Matrix Matrix::trans() const {
    unsigned int rows = this->size(1); //number of rows of original matrix
    unsigned int columns = this->size(2); //number of columns of original matrix

    //the variables for declaring the new matrix
    unsigned int tn = rows; //transpose columns
    unsigned int tm = columns; //transpose rows
    std::vector<int> C;

    for (int x = 0; x < rows; x++) { //this iterates by rows
        for (int y = 0; y < columns; y++) { //this iterates by columns
            unsigned int pos = (y * rows) + x; // this gets the location of the next needed element
                                           //it iterates through each row, by getting the next elemnt in the column
            unsigned int ele = this->get(pos);
            C.push_back(ele); //this gets the element and adds it to the C vector
        }
    }
    return Matrix(C, tm, tn); //return the new matrix
}

const Matrix Matrix::mult(const Matrix& rhs) const {
    unsigned int rows = this->size(1);
    unsigned int columns = this->size(2);

    unsigned int rhsRows = rhs.size(1);
    unsigned int rhsColumns = rhs.size(2);

    std::vector<int> C; // the new vector
    //makes sure a 0x0 matrix is not being delt with
    if (columns == 0 || rows == 0 || rhsRows == 0 || rhsColumns == 0) {
        return Matrix(C, 0, 0);
    }
    if (columns != rhsRows) { //makes sure the multiplication is possible
        return Matrix(C, 0, 0);
    }
    //defines the size of the new matrix
    int tn = rhsColumns;
    int tm = rows;
    for (int c = 0; c < rhsColumns; c++) { //iterates by column
        for (int r = 0; r < rows; r++) { //iterates by row
            int s = 0; //stores the dot product
            for (int i = 0; i < rhsRows; i++) {
                int ele = this->get(r, i);
                int rhsEle = rhs.get(i, c);
                int product = ele * rhsEle;
                s += product; // the dot product is found by summing the products
            }
            C.push_back(s); //adds the dot product to the vector
        }
    }
    return Matrix(C, tm, tn);
}

//this is the implementation of the power function
const Matrix Matrix::pow(unsigned int n) const {
    std::vector<int> C;
    if (n < 0 || this->n != this->m) {
        return Matrix(C, 0, 0);
    }
    else if (this->n == 0 || this->m == 0) {
        return *this;
    }
    else if(n == 0) {
        Matrix B = this->mult(0);
        unsigned int rows = this->size(1);
        unsigned int columns = this->size(2);
        unsigned int r = 0;
        unsigned int c = 0;
        unsigned int pro = rows * columns;
        unsigned int p = 0;
        while (p < pro) {
            B.set(r, c, 1);
            r++;
            c++;
            p = (r * c) - 1;
        }
        return B;
    }
    else if (n == 1) {
        return *this;
    }
    else {
        Matrix x; //stores the current iteration of the multiplied function
        //the matrix is mulitplied by itself n times
        for (int i = 0; i < (n - 1); i++) {
            if (i == 0) { //performs the multiplication the first time
                x = this->mult(*this);
            }
            else { //performs the multiplicaton for the other times
                x = this->mult(x);  //multiplies the matrix by itself
            }
            if (x.size(1) == 0 || x.size(2) == 0) { //if the multiplicaton became invalid
                                                    //it ends the loop early to not waste time
                return x;
            }
        }
        return x;
    }
}

