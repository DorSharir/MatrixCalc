//Sergey Bogdankevich, Dor Sharir
#include"checkInput.h"

/*
	Function moves the global pointer
	to the first place that differs from space
*/
void clear_space()
{
	while (*ptr == ' ')
		ptr++;
}

/*
	Moves global pointer to the place that differs from space and comma,
	also checks that there is only one comma between 
	numbers or names of matrices.
	Returns 1 if all input was right, else, returns 0
*/
int clear_space_comma()
{
	int flag = 0;						//check if there was a comma
	while (*ptr == ' ' || *ptr == ',')
	{
		if (*ptr == ',')
			if (!flag)
				flag = 1;
			else						//in case there was a comma and we found another one
			{
				printf("\nERROR: Too many commas\n");
				return 0;
			}
		ptr++;
	}
	if (flag) 
		return 1;						//only 1 comma, all input right
	printf("\nERROR: No comma between argumants or values\n");  //in case there was no comma at all
	return 0;
}

/*
	Here we figure out what command was called, by comparing 
	with all commands from the given list.
	Returns number of command (1-7), if command wasn't found in the
	list (incorrect input), returns 0
*/
int get_sub_command()
{
	int i;								//sub command index
	char subCommand[30];				//here we copy the sub command and compare to the list of commands
	//clear_space();					//clearing spaces before the command if necessary
	for (i = 0; *ptr != ' ' && *ptr != '\0'; ptr++, i++) //copying the command from the input to the sub command
		subCommand[i] = *ptr;
	subCommand[i] = '\0';				//adding '\0' to the end of the sub command
	//comparing the sub with the list commands
	if (!strcmp(subCommand, "read_mat")) return 1;
	if (!strcmp(subCommand, "print_mat")) return 2;
	if (!strcmp(subCommand, "add_mat")) return 3;
	if (!strcmp(subCommand, "sub_mat")) return 4;
	if (!strcmp(subCommand, "mul_scalar")) return 5;
	if (!strcmp(subCommand, "trans_mat")) return 6;
	if (!strcmp(subCommand, "stop")) return 7;

	printf("\nERROR: '%s' is incorrect command\n", subCommand);
	return 0;
}

/*
	Here we get the name of matrix,
	also we check that the name is between letters A and F including.
	*arg saves the number of matrix (0 - 6 respectively to the letter).
	Returns 1 if name is correct, else, returns 0
*/
int get_mat_name(int* arg)
{
	clear_space();						//clearing any spaces before the name
	if (*(ptr + 1) != ' ' && *(ptr + 1) != ',' && *(ptr + 1) != '\0') //checks if name consists only of one letter
	{
		printf("\nERROR: Incorrect name of matrix (need to be only one letter)\n");
		return 0;
	}
	if (*ptr >= 'A' && *ptr <= 'F')		//checking name of matrix, changing *arg into a number of matrix
	{
		*arg = *(ptr++) - 65;
		return 1;
	}
	printf("\nERROR: No such matrix as '%c'\n", *ptr);
	return 0;
}

/*
	Function works like get_mat_name, but for number of names of matrices.
	Checks if there was two matrices or three, if only two, in the third matrix name will be saved -1
	Returns 1 if all names were correct, esle, returns 0
*/
int get_mat_names(int *arg1, int *arg2, int *arg3)
{
	clear_space();						//clearing all spaces
	//checking if the first and the second names are correct and clearing spaces and commas between names
	if (!get_mat_name(arg1) || !clear_space_comma() || !get_mat_name(arg2)) 
		return 0;
	clear_space();						//clearing spaces
	if (*ptr != '\0')					//checking if the third argument exists in input
		if (!clear_space_comma() || !get_mat_name(arg3)) //checking if the third name is correct
			return 0;
		else 
		{
			clear_space();
			if (*ptr != '\0') 			// checking if there is something after third name
			{
				printf("\nERROR: Too many matrices\n");
				return 0;
			}
		}
	else								//only 2 names
		*arg3 = -1;						// sign that the third name wasn't mentioned
	return 1;
}

/*
	Function recieves the part of the input string and check 
	it for correctness of number that was inputted.
	If it correct and indeed represents a number, it will be saved in scalar.
	Returns 1 if number is correct, else, returns 0.
*/
int check_scalar(char* temp, float* scalar)
{
	int flag_point = 0;					//is changed into 1 if found the dot in number
	int i = 0;							//index of string that represents the number
	if (temp[i] == '\0') {				//in case there was a comma in end of input
		printf("\nERROR: Number after comma is not found\n");
		return 0;
	}
	if (temp[i] == '-') 				//for negative numbers
		if (temp[++i] < '0' || temp[i] > '9') { //checking the digit after '-'
			printf("\nERROR: Invalid number was detected\n");
			return 0;
		}
	if (temp[i] == '0' && temp[i + 1] != '.' && temp[i + 1] != '\0') {
		printf("\nERROR: Invalid scalar value\n");
		return 0;
	}
	if (temp[i] == '.')	{				//check that number doesn't start with dot
		printf("\nERROR: Scalar can not start with point\n");
		return 0;
	}
	for (; temp[i] != '\0'; i++) {		//checking all part of string that represents a number
		if (temp[i] == '.')
			if (flag_point) {			//in case that was found more then 1 point
				printf("\nERROR: Invalis scalar: there can be only one point\n");
				return 0;
			}
			else
				flag_point = 1;
		else							// the char is not a point
			if (temp[i] < '0' || temp[i] > '9') {
				printf("\nERROR: Invalid scalar: scalar can be only a float number\n");
				return 0;
			}
	}
	*scalar = atof(temp);				//casting from string to float after all checks
	if (!strcmp(temp, "-0")) {
		printf("\nERROR: Invalid scalar's value\n");
		return 0;
	}
	return 1;
}

/*
	Function that saves a part of inputted string in temp_scalar, that must to represent 
	a number. Global pointer runs until space or comma or end of string. After, sends
	the temp_scalar to check function on correctness of number.
	Returns 1 if result of checking is right, else, returns 0.
*/
int get_scalar(float *scalar)
{
	int i;								//index for temp_scalar
	char temp_scalar[20];				//here we save the part of inputted string
	//loop, where global pointer runs through the inputted string
	for (i = 0; *ptr != ',' && *ptr != ' ' && *ptr != '\0'; i++, ptr++) 
		temp_scalar[i] = *ptr;
	temp_scalar[i] = '\0';				//adding '\0' in the end of the temp_scalar

	if (!check_scalar(temp_scalar, scalar)) //sending the temp_scalar to the check function
		return 0;						//number is not correct
	return 1;							//number is correct
}

/*
	Function intended for command mul_scalar. Firstly, checks correctness of the name of Matrix,
	secondly, checks the scalar of multyplication, thirdly, checks if the second Matrix presents
	in input command, if it is, checks it's name for correctnes too, else, saves it's name as -1.
	Returns 1 if all checks were right, else, returns 0.
*/
int get_mat_scalar(int *arg1, int *arg2, float *scalar)
{
	//gets the name of the first Matrix and checks it, clears spaces and commas and gets and checks the scalar
	if (!get_mat_name(arg1) || !clear_space_comma() || !get_scalar(scalar))			
		return 0;
	clear_space();						//clear spaces
	if (*ptr == '\0')					//checking if there is nothing after scalar
	{
		*arg2 = -1;						//means that there is no second matrix in input command
		return 1;						
	}
	//means that there is something after scalar, so need to clear spaces and commas, get and check the name of the second Matrix
	if (!clear_space_comma() || !get_mat_name(arg2))			
		return 0;
	clear_space();
	if (*ptr == '\0')
		return 1;						
	return 0;							//in case that there was found something else than space after the name of the second matrix
}

/*
	Function for creating zero matrix, all values are zero
*/
void zero_mat(Matrix *matrix)
{
	int i, j;							//indexes of matrix
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			matrix->matrix[i][j] = 0;	//putting zero in place i.j
}

/*
	Backup function, is called each time after command read_mat.
	In case, that first time we created a correct matrix, then we decided to re-write it,
	and if the second time and all other times we created the incorrect matrix/matrices with the same name,
	program will return the the last correct version of matrix
*/
void backup_matrix(Matrix *mat1, Matrix *mat2)
{
	int i, j;							//indexes for matrices
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			mat2->matrix[i][j] = mat1->matrix[i][j]; //transporting the values between matrices
}

/*
	Function checks if the matrix was set (defined), if it was, returns 1,
	else, returns 0 with appropiate message
*/
int check_definition_mat(Matrix * matrix)
{
	if (!matrix->isDefined)				//checks if matrix was set
	{
		printf("\nERROR: The matrix hasn't been set yet\n");
		return 0;
	}
	return 1;
}

