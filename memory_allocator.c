#include <stdio.h>

const int MEMORY_SIZE = 128;

void *my_malloc(char memory[MEMORY_SIZE], char allocated[MEMORY_SIZE], size_t size)
{
    int start_index = -1;
    int unallocated_count = 0;
    int to_allocated = size + 1;

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        if (!allocated[i])
        {
            if (unallocated_count == 0)
            {
                start_index = i;
            }
            unallocated_count++;

            if (unallocated_count == to_allocated)
            {
                for (int j = 0; j < to_allocated; j++)
                {
                    allocated[start_index + j] = 1;
                }

                memory[start_index] = size;

                return &memory[start_index + 1];
            }
        }
        else
        {
            unallocated_count = 0;
        }
    }

    return NULL;
}

void my_free(char memory[MEMORY_SIZE], char allocated[MEMORY_SIZE], void *pointer)
{
    if (pointer == NULL)
    {
        return;
    }

    int start_index = (char *)pointer - memory - 1;
    if (start_index < 0 || start_index >= MEMORY_SIZE) {
        return;
    }

    int size = memory[start_index];

    for (int i = 0; i <= size; i++)
    {
        allocated[start_index + i] = 0;
    }
}

int main()
{
    char memory[MEMORY_SIZE];
    char allocated[MEMORY_SIZE];

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        allocated[i] = 0;
    }

    char *string = my_malloc(memory, allocated, 6 * sizeof(char));
    string[0] = 'A';
    string[1] = 'A';
    string[2] = 'A';
    string[3] = 'A';
    string[4] = 'A';
    string[5] = '\0';

    printf("%s\n", string);

    //my_free(memory, allocated, string);

    char *new_string = my_malloc(memory, allocated, 6 * sizeof(char));
    new_string[0] = 'B';
    new_string[1] = 'B';
    new_string[2] = 'B';
    new_string[3] = 'B';
    new_string[4] = 'B';
    new_string[5] = '\0';

    printf("%s\n", string);
    printf("%s\n", new_string);

    my_free(memory, allocated, new_string);

    return 0;
}