#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char* int_to_string(uint number)
{
    char* result = (char*)malloc(10 * sizeof(char));
    int i = 0;
    while(number > 0)
    {
        result[i] = (number % 10) + '0';
        number /= 10;
        i++;
    }
    result[i] = '\n';
    result[i + 1] = '\0';
    printf(2, "i : %d\n", i);
    for(int j = 0; j < (i / 2); j++)
    {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
    return result;
}

int main(int argc, char* argv[])
{
    printf(2, "pid : %d\n", getpid());
    uint numbers[5];
    for(int i = 1; i < 6; i++)
        numbers[i - 1] = atoi(argv[i]);

    int temp;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 4; j++)
            if(numbers[j] > numbers[j + 1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }

    int fd = open("result", O_CREATE | O_WRONLY);
    if (fd < 0)
    {
        printf(2, "Create or open file failed \n");
        exit();
    }

    for(int i = 0; i < 5; i++)
    {
        char* number_string = int_to_string(numbers[i]);
        printf(2, "%s \n", number_string);
        write(fd, number_string, strlen(number_string));
        free(number_string);
    }
    close(fd);
    exit();
}
