#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#define lli long long

char progress_string[100];

void print(char *str)
{
    write(1, str, strlen(str));
}

void formatted_print(char *str, char *name)
{
    sprintf(progress_string, str, name);
    print(progress_string);
}

void print_permissions(struct stat *file_stat, char *file_name)
{
    formatted_print("User has read permission on %s: ", file_name);
    if (file_stat->st_mode & S_IRUSR)
        print("Yes\n");
    else
        print("No\n");

    formatted_print("User has write permission on %s: ", file_name);
    if (file_stat->st_mode & S_IWUSR)
        print("Yes\n");
    else
        print("No\n");

    formatted_print("User has execute permission on %s: ", file_name);
    if (file_stat->st_mode & S_IXUSR)
        print("Yes\n\n");
    else
        print("No\n\n");

    formatted_print("Group has read permission on %s: ", file_name);
    if (file_stat->st_mode & S_IRGRP)
        print("Yes\n");
    else
        print("No\n");

    formatted_print("Group has write permission on %s: ", file_name);
    if (file_stat->st_mode & S_IWGRP)
        print("Yes\n");
    else
        print("No\n");

    formatted_print("Group has execute permission on %s: ", file_name);
    if (file_stat->st_mode & S_IXGRP)
        print("Yes\n\n");
    else
        print("No\n\n");

    formatted_print("Others has read permission on %s: ", file_name);
    if (file_stat->st_mode & S_IROTH)
        print("Yes\n");
    else
        print("No\n");

    formatted_print("Others has write permission on %s: ", file_name);
    if (file_stat->st_mode & S_IWOTH)
        print("Yes\n");
    else
        print("No\n");
    formatted_print("Others has execute permission on %s: ", file_name);
    if (file_stat->st_mode & S_IXOTH)
        print("Yes\n");
    else
        print("No\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print("Error: Invalid arguments given. Please provide single file name.");
        return 1;
    }

    struct stat directory_stats;
    int dir_status = stat("./Assignment/", &directory_stats);
    if (!(dir_status == 0 && S_ISDIR(directory_stats.st_mode)))
    {
        print("Directory is created: No\n");
        return 0;
    }

    print("Directory is created: Yes\n\n");

    struct stat file1_stats;

    lli length = strlen(argv[1]);
    lli break_index = 0;
    for (lli x = 0; x < length; x++)
        if (argv[1][x] == '/')
            break_index = x + 1;

    char *file_name = (char *)calloc(length - break_index + 1, sizeof(char));
    for (lli x = break_index; x < length; x++)
        file_name[x - break_index] = argv[1][x];
    file_name[length - break_index] = '\0';

    char *file1_destination = (char *)calloc(length - break_index + 17, sizeof(char));
    strcat(file1_destination, "./Assignment/1_");
    strcat(file1_destination, file_name);
    file1_destination[length - break_index + 17] = '\0';

    int file1_status = stat(file1_destination, &file1_stats);
    if (file1_status < 0)
    {
        perror("First output file");
        print("\n");
    }
    else
    {
        print_permissions(&file1_stats, "output_file_1");
        print("\n");
    }

    struct stat file2_stats;

    char *file2_destination = (char *)calloc(length - break_index + 17, sizeof(char));
    strcat(file2_destination, "./Assignment/2_");
    strcat(file2_destination, file_name);
    file2_destination[length - break_index + 17] = '\0';

    int file2_status = stat(file2_destination, &file2_stats);
    if (file2_status < 0)
    {
        perror("Second output file");
        print("\n");
    }
    else
    {
        print_permissions(&file2_stats, "output_file_2");
        print("\n");
    }
    print_permissions(&directory_stats, "directory");

    free(file_name);
    free(file1_destination);
    free(file2_destination);

    return 0;
}