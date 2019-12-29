//Dor Sharir, Sergey Bogdankevich

/**************************************************************************
 ***	This program represents the basic calculator for matrices 4x4.	***
 ***	In prompt window user types the command, names of matrices		***
 ***	and values of matrices, if need. Program checks if command is	***
 ***    correct and existing, checks names of matrices and values.		***
 **************************************************************************/

#include"matActions.h"

void main()
{
	char command[300];					//here we save the string inputted by user.
	Matrix arr[7];						//creating array of structures of matrices,0-5 for matrices, 6 for backup matrix .
	float scalar;						//here we save the value of scalar, for command mul_scalar.
	int sub_command;					//here we save the number of command that user inputs, 1-7 respectively 
										//to the given list of commands.
	int arg1, arg2, arg3;				//saves the number of the names of matrices,
										//need for array of structures of matrices.
	int i;								//we need index i to make default value of isDefined as 0.

	/*
		starting with running through all structures, set isDefined as 0 and
		setting in each matrix zero values.
	*/
	for (i = 0; i < 6; i++)
	{
		arr[i].isDefined = 0;
		zero_mat(&arr[i]);
	}

	/*
		User will input his command here, then the input will run through all checks.
		To stop the program, user has to print command 'stop'
	*/
	do
	{
		printf("\nEnter your command: ");
		gets(command);					//getting the input from user
		ptr = command;					//now global pointer points on the start of user's input
		sub_command = get_sub_command();	//getting the number of command

		switch (sub_command)
		{
			//user's command is incorrect
		case 0: break;

			//user's command is read_mat
		case 1: if (!get_mat_name(&arg1)) //checking the name of matrix for correctness
			break;
			read_mat(&arr[arg1], &arr[6]); //sending the respective matrix to function read_mat
			break;

			//user's command is print_mat
		case 2: if (get_mat_name(&arg1)) //getting the name of matrix that need to be printed
		{
			clear_space();		//clearing spaces after the name of matrix
			if (*ptr == '\0')	//means that there is nothing else after the name of matrix
				print_mat(arr + arg1); //calling function print_mat for respective matrix
			else
				printf("\nERROR: Too many values\n"); //in case we found something else...
		}
				break;

				//user's command is add_mat
		case 3:	if (!get_mat_names(&arg1, &arg2, &arg3)) //checking all names of matrices in command
			break;
			if (arg3 == -1)			//in case user want to print the result
				add_sub_mat_a(arr + arg1, arr + arg2, 1);
			else					//in case user want to save the result in the third matrix
				add_sub_mat_b(arr + arg1, arr + arg2, arr + arg3, 1);
			break;

			//user's command is sub_mat
		case 4:	if (!get_mat_names(&arg1, &arg2, &arg3)) //checking all names of matrices in command 
			break;
			if (arg3 == -1)			//in case user want to print the result
				add_sub_mat_a(arr + arg1, arr + arg2, 0);
			else					//in case user want to save the result in the third matrix
				add_sub_mat_b(arr + arg1, arr + arg2, arr + arg3, 0);
			break;

			//user's command is mul_scalar
		case 5: if (!get_mat_scalar(&arg1, &arg2, &scalar)) //checking all names and scalar for correctness
			break;
			if (arg2 == -1)			//in case user want to print the result
				mul_scalar_a(arr + arg1, scalar);
			else					//in case user want to save the result in the second matrix
				mul_scalar_b(arr + arg1, arr + arg2, scalar);
			break;

			//user's command is trans_mat
		case 6: if (!get_mat_name(&arg1)) //checking the name of matrix
			break;
			clear_space();			//clearing spaces
			if (*ptr == '\0')		//checking that there is nothing else after name of matrix, that user want to print the result
				trans_mat_a(arr + arg1);
			else					//in case that it found something else
			{
				clear_space_comma(); //clearing spaces and commas
				if (!get_mat_name(&arg2)) //checking the second name of matrix, in case that user want to save the result
					break;
				trans_mat_b(arr + arg1, arr + arg2);
			}
			break;

			//user's command is stop
		case 7:	clear_space();			//clears all spaces after the command
			if (*ptr != '\0')		//in case that finds something else after command stop
			{
				printf("\nERROR: '%s' - is invalid command\n", command);
				sub_command = -1;	//changes to -1 for entering the loop next time,
									//only in case that command stop was incorrect
			}
			break;
		}

	} while (sub_command != 7);
	system("pause");
}