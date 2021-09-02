#include "catch.hpp"
#include "Matrix.hpp"

TEST_CASE( "default constructor", "[Matrix]" )
{
  INFO("Hint: default constructor (linear get() must work)");
  Matrix A;

  REQUIRE(A.get(0) == 0);
  REQUIRE(A.get(1) == 0);
  REQUIRE(A.get(2) == 0);
  REQUIRE(A.get(3) == 0);

  REQUIRE(A.size(1) == 2);
  REQUIRE(A.size(2) == 2);
}

//test case for the get with one input
TEST_CASE("get one input", "[Matrix]") {
	INFO("Hint: get, one input (Requires: default constructor and set)");
	Matrix A;
	//this tests what should be the default functional case
	REQUIRE(A.get(0) == 0);
	REQUIRE(A.get(1) == 0);
	REQUIRE(A.get(2) == 0);
	REQUIRE(A.get(3) == 0);
	//this tests to make sure it throws the minimum int val if the desired location doesn't exist
	REQUIRE(A.get(4) == std::numeric_limits<int>::min());
	//this makes sure it deals with values less than zero correctly
	REQUIRE(A.get(-1) == std::numeric_limits<int>::min());

	A.set(1, 1);
	//makes sure its reading the changed value
	REQUIRE(A.get(1) == 1);
}

//test case for the get with two inputs
TEST_CASE("get two inputs", "[Matrix]") {
	INFO("Hint: get, two inputs (Requires: default constructor and set)");
	Matrix A;
	//this tests the default matrix with the get function
	REQUIRE(A.get(0) == 0);
	REQUIRE(A.get(1) == 0);
	REQUIRE(A.get(2) == 0);
	REQUIRE(A.get(3) == 0);
	//this tests to make sure the i out of bounds returns the minimum value
	REQUIRE(A.get(2, 0) == std::numeric_limits<int>::min());
	//this tests to make sure the j out of bounds returns the minimum value
	REQUIRE(A.get(0, 2) == std::numeric_limits<int>::min());

	A.set(2, 5); //changes the value of A's 3rd element to 5

	//this tests to make sure the value actually is what is getting returned
	//and not a value at another location
	REQUIRE(A.get(0, 1) == 5);

	//this checks to make sure the method deals with negatives correctly
	REQUIRE(A.get(0, -1) == std::numeric_limits<int>::min());
	REQUIRE(A.get(-1, 0) == std::numeric_limits<int>::min());
}

//this is the test case for the size function
TEST_CASE("size", "[Matrix]") {
	INFO("Hint: size (Requires: default constructor and constructor with rows and columns)");
	Matrix A;

	//this tests to make sure it deals with the invalid case correctly
	REQUIRE(A.size(4) == 0);

	//makes sure that A's size returns properly
	REQUIRE(A.size(1) == 2);
	REQUIRE(A.size(2) == 2);

	std::vector<int> C;

	C.push_back(0);
	C.push_back(0);
	C.push_back(0);

	Matrix B(C, 3, 1);

	//this tests the row size
	REQUIRE(B.size(1) == 3);
	//this tests the column size
	REQUIRE(B.size(2) == 1);

	//this makes sure negative works correctly
	REQUIRE(B.size(-10) == 0);

	//makes sure zero doesn't return anything
	REQUIRE(B.size(0) == 0);

	//makes sure changing a value in A does not change its size
	A.set(1, 2);

	REQUIRE(A.size(1) == 2);
	REQUIRE(A.size(2) == 2);


}

//this is the test case for the constructor with two overloads
TEST_CASE("constructor with two overloads", "[Matrix]") {
	INFO("Hint: constructor with two overloads (Requires: get and size)");

	std::vector<int> C; //vector to test the constructor with

	C.push_back(0);
	C.push_back(1);
	C.push_back(2);

	Matrix B(C, 3); //this generates a 1x3 matrix

	REQUIRE(B.size(2) == 3); //checks the number of columns
	REQUIRE(B.size(1) == 1); //checks the number of rows

	//makes sure the values of the matrix are correct
	REQUIRE(B.get(0, 0) == 0);
	REQUIRE(B.get(0, 1) == 1);
	REQUIRE(B.get(0, 2) == 2);

	//this checks to make sure when the matrix cannnot be made, a 0x0 is made instead
	Matrix D(C, 10);

	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	//makes sure negatives are handled
	Matrix E(C, -1);

	REQUIRE(E.size(1) == 0);
	REQUIRE(E.size(2) == 0);

	//makes sure 0 is handled correctly
	Matrix F(C, 0);
	REQUIRE(F.size(1) == 0);
	REQUIRE(F.size(2) == 0);
}

//the test case for a constructor with three overloads
TEST_CASE("constructor with three overloads", "[Matrix]") {
	INFO("Hint: constructor with three overloads (Requires get and size)");

	std::vector<int> C; //vector to test the constructor with

	C.push_back(0);
	C.push_back(1);
	C.push_back(2);

	Matrix B(C, 3, 1); //this generates a 3x1 matrix

	REQUIRE(B.size(1) == 3); //checks the number of rows
	REQUIRE(B.size(2) == 1); //checks the number of columns

	//makes sure the values of the matrix are correct
	REQUIRE(B.get(0) == 0);
	REQUIRE(B.get(1) == 1);
	REQUIRE(B.get(2) == 2);

	Matrix A(C, 1, 3); //makes a 1x3 matrix

	REQUIRE(A.size(1) == 1); //checks the number of rows
	REQUIRE(A.size(2) == 3); //checks the number of columns

	//makes sure the values of the matrix are correct
	REQUIRE(A.get(0) == 0);
	REQUIRE(A.get(1) == 1);
	REQUIRE(A.get(2) == 2);

	//this checks to make sure when the matrix cannnot be made, a 0x0 is made instead
	Matrix D(C, 10, 1);

	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	//this checks to make sure when the matrix cannnot be made, a 0x0 is made instead
	Matrix E(C, 1, 10);

	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	//these check to make sure negatives don't break anything
	Matrix F(C, -1, 3);

	REQUIRE(F.size(1) == 0);
	REQUIRE(F.size(2) == 0);

	Matrix G(C, 3, -1);

	REQUIRE(G.size(1) == 0);
	REQUIRE(G.size(2) == 0);
}

//the test case for the additon function
TEST_CASE("add", "[Matrix]") {
	INFO("Hint: add function (Requires: constructor with 2 overloads, get, and size)");

	std::vector<int> C; //vector to set the matricies with

	C.push_back(1);
	C.push_back(1);
	C.push_back(1);

	Matrix B(C, 3); //makes a 1x3 matrix


	std::vector<int> X; //vector to set the matricies with

	X.push_back(1);
	X.push_back(2);
	X.push_back(3);

	Matrix A(X, 3);

	Matrix D = B.add(A);

	//makes sure the addition properly happened
	REQUIRE(D.get(0) == 2);
	REQUIRE(D.get(1) == 3);
	REQUIRE(D.get(2) == 4);
	
	//checks to make sure the summed matrix is the right size
	REQUIRE(D.size(1) == 1);
	REQUIRE(D.size(2) == 3);

	Matrix F; //makes an empty 2x2 matrix

	D = B.add(F); //attempts to add a 1x3 and a 2x2

	//makes sure the error matrix is 0x0
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	//making the C vector's size 9 for a 3x3 matrix
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);

	Matrix E(C, 3, 3); //making a 3x3 matrix of 1s

	 D = E.add(B); //this attempts to add a 3x3 and a 1x3

	//checking to make sure the invalid addition produced a 0x0
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	A = B.trans(); //takes the transpose of B, making A a 3x1 matrix

	D = E.add(A); //this attempts to add a 3x3 and a 3x1 matrix

	//checking to make sure the invalid addition produced a 0x0
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	A = E.mult(-1); //makes A a 3x3 matrix of -1s

	D = E.add(A); //this makes sure negatives are handled properly

	//makes sure the output size is correct
	REQUIRE(D.size(1) == 3);
	REQUIRE(D.size(2) == 3);

	//makes sure the addition by a negative happened correctly
	REQUIRE(D.get(0) == 0);
	REQUIRE(D.get(1) == 0);
	REQUIRE(D.get(2) == 0);
	REQUIRE(D.get(3) == 0);
	REQUIRE(D.get(4) == 0);
	REQUIRE(D.get(5) == 0);
	REQUIRE(D.get(6) == 0);
	REQUIRE(D.get(7) == 0);
	REQUIRE(D.get(8) == 0);

	Matrix G(C, 0, 0); //this makes a 0x0 matrix
	//makes sure a matrix cannot have a 0x0 added to it
	D = E.add(G);
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	//makes sure a 0x0 matrix cannot have another matrix added to it
	D = G.add(E);
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

}

//the test case for the subtraction function
TEST_CASE("sub", "[Matrix]") {
	INFO("Hint: sub function (Requires: constructor with 2 overloads, get, and size)");

	std::vector<int> C; //vector to set the matricies with

	C.push_back(1);
	C.push_back(2);
	C.push_back(3);

	Matrix B(C, 3);


	std::vector<int> X; //vector to set the matricies with

	X.push_back(3);
	X.push_back(2);
	X.push_back(1);

	Matrix A(X, 3);

	Matrix D = B.sub(A);

	//makes sure the subtraction properly happened
	REQUIRE(D.get(0) == -2);
	REQUIRE(D.get(1) == 0);
	REQUIRE(D.get(2) == 2);

	//checks to make sure the summed matrix is the right size
	REQUIRE(D.size(2) == 3);
	REQUIRE(D.size(1) == 1);

	Matrix F; //makes an empty 2x2 matrix

	D = B.sub(F); //attempts to subtract a 1x3 and a 2x2

	//makes sure the error matrix is 0x0
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);


	//making the C vector's size 9 for a 3x3 matrix
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);

	Matrix E(C, 3, 3); //making a 3x3 matrix of 1s

	D = E.sub(B); //this attempts to subtract a 3x3 and a 1x3

   //checking to make sure the invalid addition produced a 0x0
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	A = B.trans(); //takes the transpose of B, making A a 3x1 matrix

	D = E.add(A); //this attempts to subtract a 3x3 and a 3x1 matrix

	//checking to make sure the invalid addition produced a 0x0
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	A = E.mult(-1); //makes A a 3x3 matrix of -1s

	A.set(1, -1);
	A.set(2, -1);

	D = E.add(A); //this makes sure negatives are handled properly

	//makes sure the output size is correct
	REQUIRE(D.size(1) == 3);
	REQUIRE(D.size(2) == 3);

	//makes sure the subtraction by a negative happened correctly
	REQUIRE(D.get(0) == 0);
	REQUIRE(D.get(1) == 1);
	REQUIRE(D.get(2) == 2);
	REQUIRE(D.get(3) == 0);
	REQUIRE(D.get(4) == 0);
	REQUIRE(D.get(5) == 0);
	REQUIRE(D.get(6) == 0);
	REQUIRE(D.get(7) == 0);
	REQUIRE(D.get(8) == 0);

	Matrix G(C, 0, 0); //this makes a 0x0 matrix
	//makes sure a matrix cannot have a 0x0 subtracted from it
	D = E.sub(G);
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

	//makes sure a 0x0 matrix cannot have another matrix subtrated from it
	D = G.sub(E);
	REQUIRE(D.size(1) == 0);
	REQUIRE(D.size(2) == 0);

}

//the test case for multipling by a constant
TEST_CASE("mult by constant", "[Matrix]") {
	INFO("Hint: mult by a constant (Requires: constructor with 2 overloads, default constructor, get, and size)");
	std::vector<int> C; //vector to set the first matrix with

	C.push_back(3);
	C.push_back(2);
	C.push_back(4);

	Matrix B(C, 3); //this makes a 1x3 matrix

	Matrix D = B.mult(4); //multiplies the matrix B by 2

	//makes sure the multiplication was performed correctly
	REQUIRE(D.get(0) == 12);
	REQUIRE(D.get(1) == 8);
	REQUIRE(D.get(2) == 16);

	REQUIRE(D.size(1) == 1); //verifies the number of rows
	REQUIRE(D.size(2) == 3); //verifies the number of columns

	Matrix A;

	D = A.mult(12);

	//makes sure the multiplication was performed correctly
	REQUIRE(D.get(0) == 0);
	REQUIRE(D.get(1) == 0);
	REQUIRE(D.get(2) == 0);
	REQUIRE(D.get(3) == 0);

	REQUIRE(D.size(1) == 2); //verifies the number of rows
	REQUIRE(D.size(2) == 2); //verifies the number of columns

	//makes sure negatives are correctly handled
	D = B.mult(-1);

	REQUIRE(D.get(0) == -3);
	REQUIRE(D.get(1) == -2);
	REQUIRE(D.get(2) == -4);

	//makes sure multiplying by zero works as expected
	D = B.mult(0);

	REQUIRE(D.get(0) == 0);
	REQUIRE(D.get(1) == 0);
	REQUIRE(D.get(2) == 0);

	Matrix E(C, 0, 0);
	D = E.mult(1);
	REQUIRE(D.size(1) == 0); //verifies the number of rows
	REQUIRE(D.size(2) == 0); //verifies the number of columns



}

//test case for the set function with two overloads
TEST_CASE("set with two overloads","[Matrix]") {

	INFO("Hint: set with two overloads (Requires: default constructor and get function)");

	//creates a 2x2 matrix
	Matrix A;
	//checks to make sure it returns true
	REQUIRE(A.set(2, 1));
	//checks to make sure it fails when out of bounds
	REQUIRE(!A.set(10, 9));
	//makes sure the value gets properly changed
	REQUIRE(A.get(2) == 1);

	//checks to make sure negatives are correctly returning false
	REQUIRE(!A.set(-1, 3));

	//makes sure numbers right on the boundry are correctly handled
	REQUIRE(!A.set(4, 1));
	
	//makes sure zero and negatives can be input as values to the matrix
	REQUIRE(A.set(1, -1));
	REQUIRE(A.get(1) == -1);

	REQUIRE(A.set(0, 0));
	REQUIRE(A.get(0) == 0);

	//checking to make sure the value of a 0x0 matrix cannot be set
	std::vector<int> C;
	Matrix B(C, 0, 0);

	REQUIRE(!B.set(1, -12));

}

//test case for the set function with three overloads
TEST_CASE("set with three overloads", "[Matrix]") {
	INFO("Hint: set with three overloads (Requires: default constructor and get function with two overloads)");

	Matrix A; //creates a 2x2 matrix filled with zeros

	//this makes sure the out of bounds properly works
	REQUIRE(!A.set(1, 2, 2));
	REQUIRE(!A.set(2, 1, 2));
	REQUIRE(!A.set(2, 2, 2));

	//this makes sure the set workes correctly
	REQUIRE(A.set(1, 1, 2));

	//checks to make sure the value actually got changed
	REQUIRE(A.get(1, 1) == 2);

	//checks to make sure negatives are correctly returning false
	REQUIRE(!A.set(1, -1, 2)); 
	REQUIRE(!A.set(-1, 1, 2));

	//checking to make sure a zero and negative numbers can be input into the matrix
	REQUIRE(A.set(0, 0, 0));
	REQUIRE(A.set(1, 1, -1));

	REQUIRE(A.get(0, 0) == 0);
	REQUIRE(A.get(1, 1) == -1);

	//this makes sure a 0x0 matrix cannot have its value set
	std::vector<int> C;
	Matrix B(C, 0, 0);

	REQUIRE(!B.set(1, 1, 0));
}

//this is the test case for the equals function
TEST_CASE("equal", "[Matrix]") {
	INFO("Hint: equal function (Requires: default constructor, constructor with three overloads, and set with two overloads)");

	Matrix A;

	//makes sure the matrix is equal to itself
	REQUIRE(A.equal(A));

	Matrix B;

	//makes sure it is actually equal to an identical matrix
	REQUIRE(A.equal(B));

	B.set(1, 1);
	REQUIRE(!A.equal(B));

	std::vector<int> c; //vector to set the first matrix with

	c.push_back(0);
	c.push_back(0);
	c.push_back(0);
	c.push_back(0);

	Matrix D(c, 4, 1);

	//makes sure the matrix with the same values but different sizes is not equal
	REQUIRE(!A.equal(D));

	Matrix E(c, 0, 0); //this makes a 0x0 matrix

	//makes sure the case of a 0x0 matrix is correctly handled
	REQUIRE(!A.equal(E));

	REQUIRE(!E.equal(A));

	REQUIRE(E.equal(E));

	std::vector<int> g; //vector to set the matrix with
	g.push_back(0);
	g.push_back(0);


	Matrix F(g, 2); //makes a 1x2 matrix of 0s

	REQUIRE(!F.equal(A)); //makes sure it is correctly false

	D = F.trans(); //takes the transpose of the 1x2, making a 2x1 matrix
	
	REQUIRE(!A.equal(D));//makes sure it is correctly false

	//makes matrix D a 2x2 of -1s
	//and makes B a 2x2 of +1s
	B.set(0, 1);
	B.set(2, 1);
	B.set(3, 1);
	D = B.mult(-1);

	REQUIRE(!D.equal(B)); //makes sure negatives are not treated as equals

	Matrix G(c, 0, 0);
	REQUIRE(G.equal(E));
}

//the test case for the transpose function
TEST_CASE("trans function","[Mattix]") {
	INFO("Hint: the transpose function (Requires: get, size, default constructor, and set)");

	Matrix A; //creates a 2x2 matrix of zeros

	A.set(0, 0);
	A.set(1, 1);
	A.set(2, 2);
	A.set(3, 3);
	//fills the matrix as follows:
	// |0 2|
	// |1 3|

	Matrix B = A.trans();

	//makes sure the correct values got flipped
	// |0 1|
	// |2 3|
	REQUIRE(B.get(0) == 0);
	REQUIRE(B.get(1) == 2);
	REQUIRE(B.get(2) == 1);
	REQUIRE(B.get(3) == 3);

	REQUIRE(B.size(1) == 2);
	REQUIRE(B.size(2) == 2);

	std::vector<int> C; //vector to set the first matrix with

	C.push_back(1);
	C.push_back(2);
	C.push_back(3);

	Matrix D(C, 1); //creates a 1x3 vector

	//checks to see if the matrix is created with the correct dimensions
	REQUIRE(D.size(1) == 3);
	REQUIRE(D.size(2) == 1);

	B = D.trans();

	//checks to see if the values get changed
	REQUIRE(B.get(0) == 1);
	REQUIRE(B.get(1) == 2);
	REQUIRE(B.get(2) == 3);

	//checks to see if the dimensions got flipped
	REQUIRE(B.size(1) == 1);
	REQUIRE(B.size(2) == 3);

	Matrix E(C, 0, 0);//generates a 0x0 matrix
	//attempts to take the transpose of a 0x0
	B = E.trans();
	//makes sure the size of the 0x0 remains 0 for both dimensions
	REQUIRE(B.size(1) == 0);
	REQUIRE(B.size(2) == 0);

}


//this is the test case for the multiplication by a matrix
TEST_CASE("mult", "[Matrix]") {
	INFO("Hint: the mult function");

	std::vector<int> C; //vector to set the first matrix with

	C.push_back(2);
	C.push_back(1);
	//sets up a 1x2 and a 2x1 maxrix
	//|2  1|   B: |2|
	//  A^        |1|
	Matrix A(C, 2);
	Matrix B(C, 1);

	Matrix E = A.mult(B); //this should produce the matrix: |5|
	//makes sure the dot product is correctly calculated
	REQUIRE(E.get(0) == 5);
	//makes sure the new matrix is properly sized
	REQUIRE(E.size(1) == 1); //rows
	REQUIRE(E.size(2) == 1); //columns

	C.push_back(1);
	C.push_back(2);
	//this makes a new 2x2 matrix
	// |2  1|  <-D
	// |1  2|
	Matrix D(C, 2, 2);

	E = D.mult(B); //this should produce: |5|
					//					  |4|
	//makes sure the second multiplicaton produces a properly sized matrix
	REQUIRE(E.size(1) == 2); //rows
	REQUIRE(E.size(2) == 1); //columns
	//makes sure the outputted values are correct
	REQUIRE(E.get(0) == 5);
	REQUIRE(E.get(1) == 4);

	E = A.mult(D);//this should produce: |5  4|
	//makes sure the third multiplicaton produces a properly sized matrix
	REQUIRE(E.size(1) == 1); //rows
	REQUIRE(E.size(2) == 2); //columns
	//makes sure the outputted values for the third multiplication are correct
	REQUIRE(E.get(0) == 5);
	REQUIRE(E.get(1) == 4);

	E = D.mult(A);
	//makes sure impossible multiplicatons are properly delt with
	REQUIRE(E.size(1) == 0);
	REQUIRE(E.size(2) == 0);

	Matrix F;//creates a 2x2 matrix of 0s
	
	E = D.mult(F);
	//makes sure the output matrix is correctly sized
	REQUIRE(E.size(1) == 2); //rows
	REQUIRE(E.size(2) == 2); //columns
	//makes sure the multiplication by zero works
	REQUIRE(E.get(0) == 0);
	REQUIRE(E.get(1) == 0);
	REQUIRE(E.get(2) == 0);
	REQUIRE(E.get(3) == 0);

	Matrix G(C, 0, 0); //G is a 0x0 matrix
	//tests for the invalid case of a another matrix times a 0x0
	E = D.mult(G);
	REQUIRE(E.size(1) == 0);
	REQUIRE(E.size(2) == 0);
	//tests for the case of a 0x0 times a 0x0
	E = G.mult(G);
	REQUIRE(E.size(1) == 0);
	REQUIRE(E.size(2) == 0);
	//tests for a 0x0 times another matrix
	E = G.mult(D);
	REQUIRE(E.size(1) == 0);
	REQUIRE(E.size(2) == 0);

	G = D.mult(-1);

	//testing for negative multiplication
	E = D.mult(G);
	//makes sure the matrix is the correct size
	REQUIRE(E.size(1) == 2); //rows
	REQUIRE(E.size(2) == 2); //columns
	//makes sure the correct values got output
	REQUIRE(E.get(0) == -5);
	REQUIRE(E.get(1) == -4);
	REQUIRE(E.get(2) == -4);
	REQUIRE(E.get(3) == -5);

}

//this is the test case for the power function
TEST_CASE("pow", "[Matrix]") {
	Matrix A;

	// |2 1|
	// |1 2|
	A.set(0, 0, 2);
	A.set(1, 0, 1);
	A.set(0, 1, 1);
	A.set(1, 1, 2);

	Matrix B = A.pow(2);
	//makes sure the output is
	// |5 4|
	// |4 5|
	REQUIRE(B.get(0, 0) == 5);
	REQUIRE(B.get(1, 0) == 4);
	REQUIRE(B.get(0, 1) == 4);
	REQUIRE(B.get(1, 1) == 5);
	//makes sure the out put is a 2x2
	REQUIRE(B.size(1) == 2);
	REQUIRE(B.size(2) == 2);

	std::vector<int> C;
	C.push_back(1);
	C.push_back(2);

	Matrix D(C, 2);

	B = D.pow(2); //this makes sure the function can fail correctly

	//checks to make sure this is a 0x0 matrix
	REQUIRE(B.size(1) == 0);
	REQUIRE(B.size(2) == 0);

	B = D.pow(0);
	//checks to make sure this is a 0x0 matrix
	REQUIRE(B.size(1) == 0);
	REQUIRE(B.size(2) == 0);


	B = A.pow(5); //verifies it does repeated exponents correctly

	//makes sure the output is
	// |122 121|
	// |121 122|
	REQUIRE(B.get(0, 0) == 122);
	REQUIRE(B.get(1, 0) == 121);
	REQUIRE(B.get(0, 1) == 121);
	REQUIRE(B.get(1, 1) == 122);
	//makes sure the out put is a 2x2
	REQUIRE(B.size(1) == 2);
	REQUIRE(B.size(2) == 2);


	Matrix E;

	B = E.pow(3);

	//checks to make sure this is a 2x2 matrix
	REQUIRE(B.size(1) == 2);
	REQUIRE(B.size(2) == 2);
	//makes sure 0 is handled correctly
	REQUIRE(B.get(0, 0) == 0);
	REQUIRE(B.get(1, 0) == 0);
	REQUIRE(B.get(0, 1) == 0);
	REQUIRE(B.get(1, 1) == 0);

	Matrix F(C, 0, 0);//this makes a 0x0 matrix
	//this makes sure the 0x0 matrix is return as a 0x0
	B = F.pow(7);
	REQUIRE(B.size(1) == 0);
	REQUIRE(B.size(2) == 0);

	//this is to test with negative numbers
	A.set(0, 0, -2);
	A.set(1, 0, 1);
	A.set(0, 1, -1);
	A.set(1, 1, 2);

	B = A.pow(5);

	//makes sure the output is
	// |-18 -9|
	// |9 18|
	REQUIRE(B.get(0, 0) == -18);
	REQUIRE(B.get(1, 0) == 9);
	REQUIRE(B.get(0, 1) == -9);
	REQUIRE(B.get(1, 1) == 18);
	//makes sure the output is a 2x2 matrix
	REQUIRE(B.size(1) == 2);
	REQUIRE(B.size(2) == 2);

	//preparing C to make a 3x3 matrix
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);
	C.push_back(1);

	Matrix G(C, 3, 3); //makes a 3x3 matrix

	//makes sure the 0th power functions correctly
	B = G.pow(0);
	//makes sure the size did not get changed
	REQUIRE(B.size(1) == 3);
	REQUIRE(B.size(2) == 3);
	// |1 0 0|
	// |0 1 0|
	// |0 0 1|
	//checks to make sure the matrix is the same as the above matrix
	REQUIRE(B.get(0) == 1);
	REQUIRE(B.get(1) == 0);
	REQUIRE(B.get(2) == 0);
	REQUIRE(B.get(3) == 0);
	REQUIRE(B.get(4) == 1);
	REQUIRE(B.get(5) == 0);
	REQUIRE(B.get(6) == 0);
	REQUIRE(B.get(7) == 0);
	REQUIRE(B.get(8) == 1);

	Matrix H(C, 0, 0);

	//makes sure the 0x0 matrix works as expected
	B = H.pow(0);
	REQUIRE(B.size(1) == 0);
	REQUIRE(B.size(2) == 0);
}