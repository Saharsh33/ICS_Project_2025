#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "constants.h"
/*
Tasks:-use DMA in main function because 60000 images are there to train 
       use gui to take user input as 28x28 grid
       load mnsit data set to train test model
        use softmax function to get output
        calculate accuracy
        make loop to train model
*/
float ReLU(float x)
{
    if (x >= 0)
    {
        return x;
    }
    else
    {
        return 0;
    }
}

float ReLU_derivative(float x)
{
    if (x >= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void softmax(int size, float *input, float *result)
/*
Function has been verified with test cases
*/
{

    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += exp(*input);
        input++;
    }
    input -= size;
    for (int i = 0; i < size; i++)
    {
        *result = exp(*input) / sum;
        result++;
        input++;
    }
}

float sigmoid(float x)
{
    return (1 / (1 + exp(-x)));
}

float sigmoid_derivative(float x)
{
    float s = sigmoid(x);
    return (s * (1 - s));
}

float random_float(void)
{
    float n;
    n = ((float)rand() / (float)RAND_MAX);
    return n;
}

void matrix_multiplication(int row1, int col1, int row2, int col2, float *matrix1, float *matrix2, float *result)
/*
Here col1 & row2 are equal otherwise multiplication is not possible
(so result matrix will be of size (row1 x col2))
Function has been verified with test cases
*/
{
    for (int k = 0; k < row1; k++) // moves in row of result matrix
    {
        for (int j = 0; j < col2; j++) // moves in column of result matrix
        {
            *result = 0;
            for (int i = 0; i < row2; i++) // for each element in result
            {
                *result += (*matrix1) * (*matrix2);
                matrix1++;
                matrix2 += col2;
            }
            matrix2 -= (row2 * col2);
            matrix1 -= col1;
            matrix2++;
            result++;
        }
        matrix2 -= col2;
        matrix1 += col1;
    }
}

void matrix_transpose(int row, int col, float *matrix, float *result)
/*
Function has been verified with test cases
*/
{
    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            *result = *matrix;
            result++;
            matrix += col;
        }
        matrix -= (row * col);
        matrix++;
    }
}

void matrix_addition(int row, int col, float *matrix1, float *matrix2, float *result)
/*
Function has been verified with test cases
*/
{
    for (int i = 0; i < (row * col); i++)
    {
        *result = *matrix1 + *matrix2;
        matrix1++;
        matrix2++;
        result++;
    }
}

void matrix_substraction(int row, int col, float *matrix1, float *matrix2, float *result)
/*
Function has been verified with test cases
*/
{
    for (int i = 0; i < (row * col); i++)
    {
        *result = *matrix1 - *matrix2;
        matrix1++;
        matrix2++;
        result++;
    }
}

void matrix_flattening(int row, int col, float *matrix, float *result)
{
    /*
    Function has been verified with test cases
    */
    for (int i = 0; i < (row * col); i++)
    {
        *result = *matrix;
        matrix++;
        result++;
    }
}

void weights_initialization(int row, int col, float *matrix)
{
    float *ptr = matrix;
    for (int i = 0; i < (row * col); i++)
    {
        *matrix = random_float();
        matrix++;
    }
}

int main(void)
{
    float w1[hidden_layer_size][image_size];
    float b1[hidden_layer_size][1] = {0};
    float w2[output_numbers][hidden_layer_size];
    float b2[output_numbers][1] = {0};

    float *ptr_w1 = &w1[0][0];
    float *ptr_b1 = &b1[0][0];
    float *ptr_w2 = &w2[0][0];
    float *ptr_b2 = &b2[0][0];

    weights_initialization(hidden_layer_size, image_size, ptr_w1);
    weights_initialization(output_numbers, hidden_layer_size, ptr_w2);

    int input_label = 0;
    float input[image_size][1] = {0};
    float *ptr_input = &input[0][0];

    float input_w1_multiply[hidden_layer_size][1];//W1.X
    float *ptr_input_w1_multiply = &input_w1_multiply[0][0];

    matrix_multiplication(hidden_layer_size, image_size, image_size, 1, ptr_w1, ptr_input, ptr_input_w1_multiply);

    float hidden_input[hidden_layer_size][1];
    float *ptr_hidden_input = &hidden_input[0][0];

    matrix_addition(hidden_layer_size, 1, ptr_input_w1_multiply, ptr_b1, ptr_hidden_input);//W1.X + b1

    float z1_ReLU_derivative[hidden_layer_size][1];
    float *ptr_z1_ReLU_derivative = &z1_ReLU_derivative[0][0];

    for (int i = 0; i < hidden_layer_size; i++)
    {
        *ptr_z1_ReLU_derivative = ReLU_derivative(*ptr_hidden_input);
        ptr_z1_ReLU_derivative++;
    }

    for (int i = 0; i < hidden_layer_size; i++)
    {
        *ptr_hidden_input = ReLU(*ptr_hidden_input);
        ptr_hidden_input++;
    }
    ptr_hidden_input -= hidden_layer_size;

    float output[output_numbers][1];
    float *ptr_output = &output[0][0];

    float hidden_w2_multiply[output_numbers][1];//W2.H
    float *ptr_hidden_w2_multiply = &hidden_w2_multiply[0][0];

    matrix_multiplication(output_numbers, hidden_layer_size, hidden_layer_size, 1, ptr_w2, ptr_hidden_input, ptr_hidden_w2_multiply);

    matrix_addition(hidden_layer_size, 1, ptr_hidden_w2_multiply, ptr_b2, ptr_output);//W2.H + b2

    float output2[output_numbers][1];
    float *ptr_output2 = &output2[0][0];

    softmax(output_numbers, ptr_output, ptr_output2);//applying softmax function

    float hot_vector[output_numbers][1] = {0};//making array such that correct output will be 1 and others are zero
    float *ptr_hot_vector = &hot_vector[0][0];

    for (int i = 0; i < output_numbers; i++)
    {
        if (i == input_label)
        {
            hot_vector[i][0] = 1;
        }
    }

    float dZ2[output_numbers][1];
    float *ptr_dZ2 = &dZ2[0][0];

    matrix_substraction(output_numbers, 1, ptr_output2, ptr_hot_vector, ptr_dZ2);//dZ2=output - hot_vector

    float dW2[output_numbers][hidden_layer_size];
    float *ptr_dW2 = &dW2[0][0];

    float hidden_input_transpose[1][hidden_layer_size];//transposing hidden_input
    float *ptr_hidden_input_transpose;

    matrix_transpose(hidden_layer_size, 1, ptr_hidden_input, ptr_hidden_input_transpose);

    matrix_multiplication(output_numbers, 1, 1, hidden_layer_size, ptr_dZ2, ptr_hidden_input_transpose, ptr_dW2);//dW2=dZ2*hidden_input_transpose

    float w2_transpose[hidden_layer_size][output_numbers];
    float *ptr_w2_transpose = &w2_transpose[0][0];

    matrix_transpose(output_numbers, hidden_layer_size, ptr_w2, ptr_w2_transpose);//transposing w2

    float dH[hidden_layer_size][1];
    float *ptr_dH = &dH[0][0];

    matrix_multiplication(hidden_layer_size, output_numbers, output_numbers, 1, ptr_w2_transpose, ptr_dZ2, ptr_dH);//W2_transpose*dZ2

    float dZ1[hidden_layer_size][1];
    float *ptr_dZ1 = &dZ1[0][0];

    matrix_multiplication(hidden_layer_size, 1, hidden_layer_size, 1, ptr_dH, ptr_z1_ReLU_derivative, ptr_dZ1);//dZ1=dH*ReLU_derivative

    float input_transpose[1][image_size];
    float *ptr_input_transpose;

    matrix_transpose(image_size, 1, ptr_input, ptr_input_transpose);//transposing input

    float dW1[hidden_layer_size][image_size];
    float *ptr_dW1 = &dW1[0][0];

    matrix_multiplication(hidden_layer_size, 1, 1, image_size, ptr_dZ1, ptr_input_transpose, ptr_dW1);//dW1=dZ1*input_transpose

    for (int i = 0; i < hidden_layer_size; i++)//updating weights
    {
        for (int j = 0; j < image_size; j++)
        {
            w1[i][j] -= learning_rate * dW1[i][j];
        }
    }

    for (int i = 0; i < output_numbers; i++)//updating weights
    {
        for (int j = 0; j < hidden_layer_size; j++)
        {
            w2[i][j] -= learning_rate * dW2[i][j];
        }
    }

    for (int i = 0; i < hidden_layer_size; i++)//updating biases
    {
        b1[i][0] -= learning_rate * dZ1[i][0];
    }

    for (int i = 0; i < output_numbers; i++)//updating biases
    {
        b2[i][0] -= learning_rate * dZ2[i][0];
    }
}
