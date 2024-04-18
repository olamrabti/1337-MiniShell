#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char path[1024]; // Buffer to hold the path

    // Call getcwd to get the current working directory
    if (getcwd(path, sizeof(path)) != NULL)
    {
        printf("Current working directory: %s\n", path);
    }
    else
    {
        perror("getcwd() error");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
