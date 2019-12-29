//Dor Sharir, Sergey Bogdankevich

#include "matActions.h"

/*
	Function fills the matrix with values, checking each value (scalar),
	if matrix was defined we will save it in backup matrix. If matrix was defined and something 
	went wrong, we will call the backup function to recieve last version of this matrix.
	Also, function checks that the was -1 in input. If there wasn't in won't define the matrix.
	Also, in case that input concisted of amount (of values) higher then 16, if -1 was inputted,
	function saves 16 first values, else, if -1 wasn't inputted, it will send ERROR and not define the matrix,
	but still will checks all numbers
*/
int read_mat(Matrix *matrix, Matrix *backupMat)
{
	float temp_scalar;					//saves the value in float type
	int flagNegOne = 1;					//representes the -1, end of setting the matrix with values, if wasn't found, input is incorrect
	int count = 0;						//counter representes the place of value in matrix
	if (matrix->isDefined)				//makes backup matrix if matrix was defined
		backup_matrix(matrix, backupMat);
	zero_mat(matrix);					//making zero matrix for getting new input
	while (*ptr != '\0') {				//runs until the end of the input
		if (count == 0) {				//for the first number, that comes after the name of matrix
			clear_space();
			if (*ptr == ',') {			//check the comma after the name of matrix
				printf("\nERROR: Found comma after the name of Matrix\n");
				return 0;
			}
		}
		else							//for all other numbers
			if (!clear_space_comma()) { //clearing spaces and commas
				backup_matrix(backupMat, matrix);
				return 0;
			}
		if (!get_scalar(&temp_scalar)) { //checks if value in input was corrent, if it was, saves in temp_scalar
			backup_matrix(backupMat, matrix);
			return 0;
		}
		if (temp_scalar == -1)			
			flagNegOne = 0;
		if (flagNegOne && count <= 16)	//setting the 16 first numbers in matrix or setting numbers until -1 was inputted
			matrix->matrix[count % N][count++ / N] = temp_scalar;
		clear_space();
	}
	if (flagNegOne) {					//ther was no '-1'
		printf("\nThere was no '-1'\n");
		backup_matrix(backupMat, matrix);
		return 0;
	}
	matrix->isDefined = 1;				//defines matrix
	return 1;							//all input was corrent
}


/*
	Function that prints the matrix's values,
	first, checks if matrix was set, if it was, prints,
	else, gives error - message.
*/
void print_mat(Matrix* matrix)
{
	int i, j;							//indexes of matrix
	if (!check_definition_mat(matrix)) //checks if matrix was defined
		return;
	for (i = 0; i < N; i++)				//running through the matrix
	{
		for (j = 0; j < N; j++)
			printf("%.2f\t", matrix->matrix[i][j] == 0 ? abs(matrix->matrix[i][j]) : matrix->matrix[i][j] ); //prints value of matrix with index i, j
		printf("\n");
	}
}

/*
	Function for addition or subtraction of matrices and in the end
	printing the result, without any changes of matrices. Ckecks the definition of matrices.
	With help of flag function understands which command to use.
	If flag is 1, makes addition, if flag is 0, makes subtraction.
	Work only if matrices were set.
*/
void add_sub_mat_a(Matrix *mat1, Matrix *mat2, int flag)
{
	int i, j;							//indexes of the matrix
	if (!check_definition_mat(mat1) || !check_definition_mat(mat2)) //checks if both matrices were set
		return;
	for (i = 0; i < N; i++)				//running through matrices
	{
		//loop checks the flag and makes add/sub respectively
		for (j = 0; j < N; j++)
			printf("%.2f\t", flag ? mat1->matrix[i][j] + mat2->matrix[i][j] : mat1->matrix[i][j] - mat2->matrix[i][j]);
		printf("\n");
	}
}



/*
	Function checks if the first and the second matrices were both set, in a good case, 
	checks the flag and then makes addition or subtraction respectively with flag.
	Does not print anything, but saves the result in the third matrix, setting it.
	In a bad case, prints appropriate message
*/
void add_sub_mat_b(Matrix *mat1, Matrix *mat2, Matrix *mat3, int flag)
{
	int i, j;							//indexes of matrices
	if(!check_definition_mat(mat1) || !check_definition_mat(mat2)) //check if both matrices were set
		return;
	for (i = 0; i < N; i++)				//running through both matrices
		for (j = 0; j < N; j++)
			mat3->matrix[i][j] = (flag ? mat1->matrix[i][j] + mat2->matrix[i][j] : mat1->matrix[i][j] - mat2->matrix[i][j]);
	mat3->isDefined = 1;				//definition of the third matrix
}

/*
	Function for multiplication of matrix by scalar.
	Firstly, checks if matrix was set, if it was, makes multyplication and print
	the result without any changes of matrix. If it wasn't set, quit the function with 
	appropriate message.
*/
void mul_scalar_a(Matrix *mat1, float scalar)
{
	int i, j;							//indexes of matrix
	if (!check_definition_mat(mat1)) //checks if matrix was defined
		return;
	for (i = 0; i < N; i++)				//running through the matrix
	{
		for (j = 0; j < N; j++)
			printf("%.2f\t", mat1->matrix[i][j] == 0 ? abs(mat1->matrix[i][j]) : mat1->matrix[i][j] * scalar);
		printf("\n");
	}
}

/*
	Function for multiplication of matrix by scalar.
	Firstly, checks if matrix was set, if it was, makes multyplication and saves the result
	in the second matrix, defining it, doesn't change the first matrix.
	If it wasn't set, quit the function with
	appropriate message.
*/
void mul_scalar_b(Matrix *mat1, Matrix *mat2, float scalar)
{
	int i, j;							//indexes of matrices
	if (!check_definition_mat(mat1)) //checks definition of the first matrix
		return;
	mat2->isDefined = 1;				//definition of the second matrix
	for (i = 0; i < N; i++)				//running through matrices,saving the result
		for (j = 0; j < N; j++) {
			mat2->matrix[i][j] = mat1->matrix[i][j] * scalar;
			if(mat2->matrix[i][j] == 0)
				mat2->matrix[i][j] = abs(mat2->matrix[i][j]);
		}
}

/*
	Function checks if matrix was defined, than prints transpose matrix,
	without any changes of it. If matrix wasn't defined, quit the function 
	with appropriate message.
*/
void trans_mat_a(Matrix *mat1)
{
	int i, j;							//indexes of matrix
	if (!check_definition_mat(mat1)) //checks if matrix was defined
		return;
	for (i = 0; i < N; i++)				//running through the matrix
	{
		for (j = 0; j < N; j++)
			printf("%.2f\t", mat1->matrix[j][i]);
		printf("\n");
	}
}

/*
	Function checks if first matrix was defined, than saves the transposion 
	of the first matrix in the second matrix, defining the second.
	Doesn't print the result. If matrix wasn't defined, quit the function
	with appropriate message.
*/
void trans_mat_b(Matrix *mat1, Matrix *mat2)
{
	int i, j;							//indexes of matrices
	if (!check_definition_mat(mat1)) //checks if first mstrix was set
		return;
	mat2->isDefined = 1;				//definition of the second matrix
	for (i = 0; i < N; i++)				//running through the matrices
		for (j = 0; j < N; j++)
			mat2->matrix[i][j] = mat1->matrix[j][i];
}
