#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define MAX_PATH 1024
int main(int argc, char *argv[]) {
    char line[256];
    
    // current directory
    char current_dir[MAX_PATH] = "";
    getcwd(current_dir, MAX_PATH);
    printf("Current directory before change is: %s\n", current_dir);


    // Change the current working directory to a different folder
    if (chdir("D1") != 0) {
        perror("chdir");
        exit(1);
    }

    getcwd(current_dir, MAX_PATH);
    printf("Current directory after change is: %s\n", current_dir);

    // Open the file in the different folder
    FILE *file_in_other_folder = fopen("a.txt", "r");
    if (file_in_other_folder == NULL) {
        perror("fopen");
        exit(1);
    }

    // Read and print the contents of the file in the different folder
    fgets(line, sizeof(line), file_in_other_folder);
    printf("Content of a.txt in the D1 folder: %s\n", line);


    // Close the files
    fclose(file_in_other_folder);

    return 0;
}