//Dor Sharir, Sergey Bogdankevich

#ifndef ACTIONS
	#define ACTIONS
	#include"checkInput.h"

	/*
		Function for command read_mat, recieves two matrices, one for 
		getting values of matrix, second is backup matrix
	*/
	int read_mat(Matrix*, Matrix*);

	/*
		Function for printing matrix
	*/
	void print_mat(Matrix*);

	/*
		Function for addition/subtraction of matrices respectively
		and printing the result, without any changes of matrices.
		We use flag to know if to use add_mat or sub_mat
	*/
	void add_sub_mat_a(Matrix*, Matrix*, int flag);

	/*
		Function for addition/subtraction of matrices respectively
		and NOT printing the result, but saving result in the third matrix.
		We use flag to know if to use add_mat or sub_mat
	*/
	void add_sub_mat_b(Matrix*, Matrix*, Matrix*, int flag);

	/*
		Function for multyplication of matrix by scalar,
		after multiplication it will print the result, without
		any changes of the matrix
	*/
	void mul_scalar_a(Matrix*, float);

	/*
		Function for multyplication of matrix by scalar,
		after multiplication it will NOT print the result, but
		will save the result in the second matrix
	*/
	void mul_scalar_b(Matrix*, Matrix*, float);

	/*
		Function prints transposed matrix, does not change anything
	*/
	void trans_mat_a(Matrix*);

	/*
		Function saves the transposed matrix in the mat2, without printing
	*/
	void trans_mat_b(Matrix*, Matrix*);

#endif