#include "lib.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        search_file_with_threads(argv[1], argv[2]);
    }
    else
    {
        printf("Enter filename:");
        char file[120];
        scanf("%s", file);
        printf("Enter path:");
        char path[120];
        scanf("%s", path);
        search_file_with_threads(file, path);
    }
    return 0;
}