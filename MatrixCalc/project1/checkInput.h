//Sergey Bogdankevich, Dor Sharir

#ifndef CHECK
	#define CHECK
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	#include<math.h>
	#define N 4
	#pragma warning(disable: 4996)

	//global pointer that runs all over the input string
	char* ptr;

	/*
		Structure of each Matrix, includes matrix 4x4 of numbers 
		and integer isDefined that represents if matrix was set (1) or not (0)
	*/
	typedef struct
	{
		float matrix[N][N];
		int isDefined;
	} Matrix; 

	/*
		Function for 'clearing' spaces in the string,
		it takes the global pointer to the first place of char that differents from ' ' (space)
	*/
	void clear_space();

	/*
		Function for 'clearing' spaces and commas in the string,
		it takes the global pointer to the first place of char that 
		differents from ' ' (space) and ',' (comma)
	*/
	int clear_space_comma();

	/*
		Function that compares the inputed command
		with given 'commands-list'
	*/
	int get_sub_command();

	/*
		Function for comparing the name of Matrix
		that was inputed with given 'names-list'
	*/
	int get_mat_name(int*);

	/*
		Function for getting amount of arguments in action 
		(function intended for commands such as add_mat, sub_mat, trans_mat...)
	*/
	int get_mat_names(int*, int*, int*);

	/*
		Function for checking the scalar for correctness, 
		that number is indeed a number, without letters and with one dot or without dots
	*/
	int check_scalar(char*, float*);

	/*
		Function for getting scalar, we get the scalar and then 
		we send it to check function that is above
	*/
	int get_scalar(float*);

	/*
		Function for getting amount of arguments and scalar in action
		(function intended for command mul_scalar)
	*/
	int get_mat_scalar(int*, int*, float*);

	/*
		Function that set all values of matrix with zero
	*/
	void zero_mat(Matrix*);

	/*
		Function that makes backup matrix in case that something went wrong
	*/
	void backup_matrix(Matrix*, Matrix*);

	/*
		Function checks if matrix was set
	*/
	int check_definition_mat(Matrix*);

#endif 