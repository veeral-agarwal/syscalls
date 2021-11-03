#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#define lli long long

lli BUFFER_SIZE = 1000000;

void reverse_buffer(char *buffer, lli buffer_length)
{
    char temp;
    for (lli x = 0; x < buffer_length / 2; x++)
    {
        temp = buffer[x];
        buffer[x] = buffer[buffer_length - x - 1];
        buffer[buffer_length - x - 1] = temp;
    }
}

void print(char *str)
{
    write(1, str, strlen(str));
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print("Error: Invalid arguments given. Please provide single file name.\n");
        return 1;
    }

    int source_path = open(argv[1], O_RDONLY);
    if (source_path == -1)
    {
        perror("Cannot open file");
        return 1;
    }

    struct stat stats;
    int stat_return = stat(argv[1], &stats);
    if (stat_return != 0 || S_ISDIR(stats.st_mode))
    {
        print("Error: Directory given as argument instead of file.");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    lli starting_position = 0;

    lli length = strlen(argv[1]);
    lli break_index = 0;
    for (lli x = 0; x < length; x++)
        if (argv[1][x] == '/')
            break_index = x + 1;

    char *file_name = (char *)calloc(length - break_index + 1, sizeof(char));
    for (lli x = break_index; x < length; x++)
        file_name[x - break_index] = argv[1][x];
    file_name[length - break_index] = '\0';

    char *destination = (char *)calloc(length - break_index + 17, sizeof(char));
    strcat(destination, "./Assignment/1_");
    strcat(destination, file_name);
    destination[length - break_index + 17] = '\0';

    int dir_status = mkdir("./Assignment/", 0700);
    if (dir_status < 0 && errno != EEXIST)
    {
        perror("Directory creation");
        return 1;
    }
    int write_file = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (write_file == -1)
    {
        perror("Output file");
        return 1;
    }

    lli offset = lseek(source_path, 0, SEEK_END);
    lli total_size = offset;
    lseek(write_file, 0, SEEK_SET);

    lli progress = 0;
    char progress_string[100];

    while (offset > 0)
    {
        float val = 100.0 * progress / total_size;
        sprintf(progress_string, "\r%.2f%% file copied", val);
        write(1, progress_string, strlen(progress_string));

        lli length_of_data;
        if (offset >= BUFFER_SIZE)
            length_of_data = BUFFER_SIZE;
        else
            length_of_data = offset;

        offset = lseek(source_path, -length_of_data, SEEK_CUR);

        int read_file = read(source_path, buffer, length_of_data);
        if (read_file < 0)
        {
            perror("Error reading from file");
            return 1;
        }

        reverse_buffer(buffer, length_of_data);

        lli data_written = write(write_file, buffer, length_of_data);
        if (data_written < 0)
        {
            perror("Error writing to file");
            return 1;
        }
        progress += data_written;

        offset = lseek(source_path, -length_of_data, SEEK_CUR);

        val = 100.0 * progress / total_size;
        sprintf(progress_string, "\r%.2f%% file copied", val);
        write(1, progress_string, strlen(progress_string));
    }

    float val = 100.0 * progress / total_size;
    sprintf(progress_string, "\r%.2f%% file copied", val);
    write(1, progress_string, strlen(progress_string));

    int check = close(write_file);
    if (check < 0)
    {
        perror("Cannot close file");
    }

    check = close(source_path);
    if (check < 0)
    {
        perror("Cannot close file");
    }

    free(file_name);
    free(destination);
    return 0;
}