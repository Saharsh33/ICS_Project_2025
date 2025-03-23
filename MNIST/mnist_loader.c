#include <stdio.h>
#include <stdlib.h>

void mnist_image_loader(const char *file, int image_size, unsigned char *image_input_matrix, int index)
{
    FILE *file_pointer = fopen(file, "rb");
    if (file_pointer == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    fseek(file_pointer, 16 + (index * image_size), SEEK_SET);

    fread(image_input_matrix, sizeof(unsigned char), image_size, file_pointer);

    fclose(file_pointer);
    return;
}
void mnist_label_loader(const char *file, int image_size, unsigned char *image_input_matrix, int index)
{
    FILE *file_pointer = fopen(file, "rb");
    if (file_pointer == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    fseek(file_pointer, 8 + (index * image_size), SEEK_SET);

    fread(image_input_matrix, 1, 1, file_pointer);

    fclose(file_pointer);
    return;
}

int main(void)
{
    unsigned char *image_input_matrix = (unsigned char *)malloc(784 * sizeof(unsigned char));
    unsigned char *label_input_matrix = (unsigned char *)malloc(1 * sizeof(unsigned char));

    const char *file = "train-images.idx3-ubyte";
    const char *file_label = "train-labels.idx1-ubyte";

    mnist_image_loader(file, 784, image_input_matrix, 1);
    mnist_label_loader(file_label, 1, label_input_matrix, 1);

    int input_label = *label_input_matrix;
    float input[784][1];

    for (int i = 0; i < 784; i++)
    {
        input[i][0] = (float)((*image_input_matrix)/255.0);
        image_input_matrix++;
    }
    image_input_matrix -= 784;
    float *ptr_input = &input[0][0];

    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            // float pixel = (float)((*image_input_matrix) / 255.0);
            // printf("%.2f", pixel);
            // image_input_matrix++;
            printf("%.2f ",*ptr_input);
            ptr_input++;
        }
        printf("\n");
    }
    ptr_input-=784;
    image_input_matrix -= 784;

    printf("Label: %d\n", *label_input_matrix);
    
    free(image_input_matrix);
    free(label_input_matrix);
}