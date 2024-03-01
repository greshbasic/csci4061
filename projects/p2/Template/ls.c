/*test machine: csel-kh1262-18
* date: 02/28/24
* name: Gresham Basic, Elaine Nguyen
* x500: basic009, nguy4546
*/

#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include <stdbool.h>


#include <dirent.h>		// for scandir and readdir
#include <sys/stat.h>   // for stat

#define MAX_ENTRIES 1024

//based on lab6!
void ls_sorted(char **entries, int *num_entries, char *new_entry) {
    int i;
    for (i = *num_entries - 1; i >= 0 && strcmp(new_entry, entries[i]) < 0; i--) {
        entries[i + 1] = entries[i];
    }
    entries[i + 1] = strdup(new_entry);
    if(entries[i + 1] == NULL) {
        perror("strdup failure");
        exit(EXIT_FAILURE);
    }
    (*num_entries)++;
}


void ls_rec_help(char *path, bool recurse_flag) {
	struct dirent *dir_entry;
	struct stat s;
	DIR *dir;
	char *entries[MAX_ENTRIES];
    int num_entries = 0;

	dir = opendir(path);
	if (!dir) {
		perror("ls");
		return;
	}


    // Read the directory and store the entries in the entries array
    while ((dir_entry = readdir(dir)) != NULL && num_entries < MAX_ENTRIES) {
        if (strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..") != 0) {
            ls_sorted(entries, &num_entries, dir_entry->d_name);
        }
    }

    for (int i = 0; i < num_entries; i++) {
        printf("%s\n", entries[i]);

        // Recursion into subdirectories if -R flag is set
        if (recurse_flag) {
            char this_path[100]; 
            snprintf(this_path, sizeof(this_path), "%s/%s", path, entries[i]);
            if (stat(this_path, &s) == 0 && S_ISDIR(s.st_mode)) {
                ls_rec_help(this_path, recurse_flag);
            }
        }
        free(entries[i]); // Free the allocated memory
    }
    closedir(dir);
}

void ls(const char *path, bool recurse_flag) {
    char current_dir[100];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("ls getcwd");
        return;
    }

    printf("Currently in: %s\n", current_dir);
    if (path && strlen(path) > 0) {
        ls_rec_help(path, recurse_flag);
    } else {
        ls_rec_help(".", recurse_flag); // Default to current directory if no path is provided
    }
    printf("\n");
}

int main(int argc, char *argv[]){
	if (argc < 2) { // No -R flag and no path name
		ls(NULL, false);
	} else if (strcmp(argv[1], "-R") == 0) { 
		if (argc == 2) { // only -R flag
			ls(NULL, true);
		} else { // -R flag with some path name
			ls(argv[2], true);
		}
	} else { // no -R flag but path name is given
    	ls(argv[1], false);
  }
	return 0;
}