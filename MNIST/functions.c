#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
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

float random_float(int fan_in, int fan_out)
{
    float limit = sqrt(6.0 / (fan_in + fan_out));
    return ((float)rand() / (float)RAND_MAX) * 2 * limit - limit;
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
    for (int i = 0; i < (row * col); i++)
    {
        *matrix = random_float(row, col);
        matrix++;
    }
}

void mnist_image_loader(const char *file, int size, unsigned char *image_input_matrix, int index)
{
    FILE *file_pointer = fopen(file, "rb");
    if (file_pointer == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    fseek(file_pointer, 16 + (index * size), SEEK_SET);

    fread(image_input_matrix, sizeof(unsigned char), size, file_pointer);

    fclose(file_pointer);
    return;
}

void mnist_label_loader(const char *file, int size, unsigned char *image_input_matrix, int index)
{
    FILE *file_pointer = fopen(file, "rb");
    if (file_pointer == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    fseek(file_pointer, 8 + (index * size), SEEK_SET);

    fread(image_input_matrix, 1, 1, file_pointer);

    fclose(file_pointer);
    return;
}

float cross_entropy_loss(int size, float *predicted, int actual_label)
{
    return -log(predicted[actual_label] + 1e-9); // Adding small value to avoid log(0)
}

int main(void)
{
    srand(time(NULL));
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

    const char *file = "train-images.idx3-ubyte";
    const char *file_label = "train-labels.idx1-ubyte";

    for (int e = 0; e < 10; e++)
    {
        int correct = 0;
        for (int current_images = 0; current_images < train_images; current_images++)
        {
            unsigned char *image_input_matrix = (unsigned char *)calloc(784, sizeof(unsigned char));
            unsigned char *label_input_matrix = (unsigned char *)calloc(1, sizeof(unsigned char));

            mnist_image_loader(file, 784, image_input_matrix, current_images);
            mnist_label_loader(file_label, 1, label_input_matrix, current_images);

            int input_label = *label_input_matrix;
            float input[image_size][1];

            for (int i = 0; i < image_size; i++)
            {
                input[i][0] = (float)((*image_input_matrix) / 255.0);
                image_input_matrix++;
            }
            image_input_matrix -= 784;
            float *ptr_input = &input[0][0];

            int guess = 0;
            float *input_w1_multiply = (float *)calloc(hidden_layer_size, sizeof(float)); //
            float *hidden_input = (float *)calloc(hidden_layer_size, sizeof(float));      //
            float *hidden_input_transpose = (float *)calloc(hidden_layer_size, sizeof(float));
            float *z1_ReLU_derivative = (float *)calloc(hidden_layer_size, sizeof(float));
            float *output = (float *)calloc(output_numbers, sizeof(float));
            float *hidden_w2_multiply = (float *)calloc(output_numbers, sizeof(float));
            float *output2 = (float *)calloc(output_numbers, sizeof(float));
            float *hot_vector = (float *)calloc(output_numbers, sizeof(float));
            float *dZ2 = (float *)calloc(output_numbers, sizeof(float));
            float *dW2 = (float *)calloc(output_numbers * hidden_layer_size, sizeof(float));          //
            float *w2_transpose = (float *)calloc(hidden_layer_size * output_numbers, sizeof(float)); //
            float *dH = (float *)calloc(hidden_layer_size, sizeof(float));                            //
            float *dz1 = (float *)calloc(hidden_layer_size, sizeof(float));
            float *input_transpose = (float *)calloc(image_size, sizeof(float));
            float *dW1 = (float *)calloc(hidden_layer_size * image_size, sizeof(float));

            matrix_multiplication(hidden_layer_size, image_size, image_size, 1, ptr_w1, ptr_input, input_w1_multiply); // w1*input
            matrix_addition(hidden_layer_size, 1, input_w1_multiply, ptr_b1, hidden_input);                            // w1*input+b1

            for (int i = 0; i < hidden_layer_size; i++)
            {
                hidden_input[i] = ReLU(hidden_input[i]);                  // ReLU(w1*input+b1)
                z1_ReLU_derivative[i] = ReLU_derivative(hidden_input[i]); // ReLU'(w1*input+b1)
            }

            matrix_multiplication(output_numbers, hidden_layer_size, hidden_layer_size, 1, ptr_w2, hidden_input, hidden_w2_multiply); // w2*H
            matrix_addition(output_numbers, 1, hidden_w2_multiply, ptr_b2, output);                                                   // w2*H+b2

            softmax(output_numbers, output, output2); // softmax(w2*H+b2)
            for (int i = 0; i < output_numbers; i++)
            {

                if (output2[i] > output2[guess])
                {
                    guess = i;
                }
            }

            hot_vector[*label_input_matrix] = 1.0; // hot vector

            matrix_substraction(output_numbers, 1, output2, hot_vector, dZ2); // output2-hot_vector

            matrix_transpose(hidden_layer_size, 1, hidden_input, hidden_input_transpose); // H^T

            matrix_multiplication(output_numbers, 1, 1, hidden_layer_size, dZ2, hidden_input_transpose, dW2); // dW2=dZ2*H^T

            matrix_transpose(output_numbers, hidden_layer_size, ptr_w2, w2_transpose); // w2^T

            matrix_multiplication(hidden_layer_size, output_numbers, output_numbers, 1, w2_transpose, dZ2, dH); // dH=w2^T*dZ2

            matrix_transpose(image_size, 1, ptr_input, input_transpose); // transposing input matrix

            matrix_multiplication(hidden_layer_size, 1, 1, image_size, dH, input_transpose, dW1);

            // matrix_multiplication(hidden_layer_size, 1, hidden_layer_size, 1, dH, z1_ReLU_derivative, dz1); // dZ1=dH*ReLU_derivative

            // matrix_multiplication(hidden_layer_size, 1, 1, image_size, dz1, input_transpose, dW1); // dW1=dZ1*input_transpose

            for (int i = 0; i < hidden_layer_size; i++) // updating weights
            {
                for (int j = 0; j < image_size; j++)
                {
                    w1[i][j] -= learning_rate * (*dW1);
                    dW1++;
                }
            }
            dW1 -= (hidden_layer_size * image_size);

            for (int i = 0; i < output_numbers; i++) // updating weights
            {
                for (int j = 0; j < hidden_layer_size; j++)
                {
                    w2[i][j] -= learning_rate * (*dW2);
                    dW2++;
                }
            }
            dW2 -= (output_numbers * hidden_layer_size);

            for (int i = 0; i < hidden_layer_size; i++) // updating biases
            {
                b1[i][0] -= learning_rate * (*dz1);
                dz1++;
            }
            dz1 -= hidden_layer_size;

            for (int i = 0; i < output_numbers; i++) // updating biases
            {
                b2[i][0] -= learning_rate * (*dZ2);
                dZ2++;
            }
            dZ2 -= output_numbers;
            if (guess == input_label)
            {
                correct++;
            }

            // Free allocated memory
            free(image_input_matrix);
            free(label_input_matrix);
            free(input_w1_multiply);
            free(hidden_input);
            free(hidden_input_transpose);
            free(z1_ReLU_derivative);
            free(output);
            free(hidden_w2_multiply);
            free(output2);
            free(hot_vector);
            free(dZ2);
            free(dW2);
            free(w2_transpose);
            free(dH);
            free(dz1);
            free(input_transpose);
            free(dW1);
            // if ((current_images + 1) % 100 == 0)
            // {
            //     printf("%f\n", ((float)correct *100.0)/(float) (current_images + 1));
            // }
        }
        printf("Epoch %d accuracy: %f\n", e + 1, ((float)correct / train_images) * 100.0);
    }

    const char *file2 = "t10k-images.idx3-ubyte";
    const char *file2_label = "t10k-labels.idx1-ubyte";

    for (int e = 0; e < 1; e++)
    {
        int correct = 0;
        for (int current_images = 0; current_images < test_images; current_images++)
        {
            unsigned char *image_input_matrix = (unsigned char *)calloc(784, sizeof(unsigned char));
            unsigned char *label_input_matrix = (unsigned char *)calloc(1, sizeof(unsigned char));

            mnist_image_loader(file2, 784, image_input_matrix, current_images);
            mnist_label_loader(file2_label, 1, label_input_matrix, current_images);

            int input_label = *label_input_matrix;
            float input[image_size][1];

            for (int i = 0; i < image_size; i++)
            {
                input[i][0] = (float)((*image_input_matrix) / 255.0);
                image_input_matrix++;
            }
            image_input_matrix -= 784;
            float *ptr_input = &input[0][0];

            int guess = 0;
            float *input_w1_multiply = (float *)calloc(hidden_layer_size, sizeof(float)); //
            float *hidden_input = (float *)calloc(hidden_layer_size, sizeof(float));      //
            float *hidden_input_transpose = (float *)calloc(hidden_layer_size, sizeof(float));
            float *z1_ReLU_derivative = (float *)calloc(hidden_layer_size, sizeof(float));
            float *output = (float *)calloc(output_numbers, sizeof(float));
            float *hidden_w2_multiply = (float *)calloc(output_numbers, sizeof(float));
            float *output2 = (float *)calloc(output_numbers, sizeof(float));
            float *hot_vector = (float *)calloc(output_numbers, sizeof(float));
            float *dZ2 = (float *)calloc(output_numbers, sizeof(float));
            float *dW2 = (float *)calloc(output_numbers * hidden_layer_size, sizeof(float));          //
            float *w2_transpose = (float *)calloc(hidden_layer_size * output_numbers, sizeof(float)); //
            float *dH = (float *)calloc(hidden_layer_size, sizeof(float));                            //
            float *dz1 = (float *)calloc(hidden_layer_size, sizeof(float));
            float *input_transpose = (float *)calloc(image_size, sizeof(float));
            float *dW1 = (float *)calloc(hidden_layer_size * image_size, sizeof(float));

            matrix_multiplication(hidden_layer_size, image_size, image_size, 1, ptr_w1, ptr_input, input_w1_multiply); // w1*input
            matrix_addition(hidden_layer_size, 1, input_w1_multiply, ptr_b1, hidden_input);                            // w1*input+b1

            for (int i = 0; i < hidden_layer_size; i++)
            {
                hidden_input[i] = ReLU(hidden_input[i]);                  // ReLU(w1*input+b1)
                z1_ReLU_derivative[i] = ReLU_derivative(hidden_input[i]); // ReLU'(w1*input+b1)
            }

            matrix_multiplication(output_numbers, hidden_layer_size, hidden_layer_size, 1, ptr_w2, hidden_input, hidden_w2_multiply); // w2*H
            matrix_addition(output_numbers, 1, hidden_w2_multiply, ptr_b2, output);                                                   // w2*H+b2

            softmax(output_numbers, output, output2); // softmax(w2*H+b2)
            for (int i = 0; i < output_numbers; i++)
            {

                if (output2[i] > output2[guess])
                {
                    guess = i;
                }
            }

            hot_vector[*label_input_matrix] = 1.0; // hot vector

            if (guess == input_label)
            {
                correct++;
            }

            // Free allocated memory
            free(image_input_matrix);
            free(label_input_matrix);
            free(input_w1_multiply);
            free(hidden_input);
            free(hidden_input_transpose);
            free(z1_ReLU_derivative);
            free(output);
            free(hidden_w2_multiply);
            free(output2);
            free(hot_vector);
            free(dZ2);
            free(dW2);
            free(w2_transpose);
            free(dH);
            free(dz1);
            free(input_transpose);
            free(dW1);
        }
        printf("Test accuracy: %f\n", ((float)correct / test_images) * 100.0);
    }
}
