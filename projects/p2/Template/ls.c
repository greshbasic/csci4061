#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include <stdbool.h>


#include <dirent.h>		// for scandir and readdir
#include <sys/stat.h>   // for stat

void ls_rec_help(char *path, bool recurse_flag) {
	struct dirent *dir_entry;
	struct stat s;
	DIR *dir;

	dir = opendir(path);
	if (!dir) {
		perror("ls");
		return;
	}

	dir_entry = readdir(dir);
	while (dir_entry) {

		// getting specific path in order to evaluate if looking at a dir or a file
		char this_path[100];
		strcpy(this_path, path);
		strcat(this_path, "/");
		strcat(this_path, dir_entry->d_name);

		int stat_status = stat(this_path, &s); 
		if (stat_status < 0) {
			perror("ls");
			return;
		}

		int is_not_current_dir = strcmp(dir_entry->d_name, ".");
		int is_not_parent_dir = strcmp(dir_entry->d_name, "..");

		if (is_not_current_dir && is_not_parent_dir) {		// if it's not the current or parent directory...
			if (S_ISDIR(s.st_mode)) {						// ...if it's a directory...
				printf("%s\n", dir_entry->d_name);			// ...print its name
				if (recurse_flag) {							// if the -R flag is set...
					ls_rec_help(this_path, recurse_flag);	// ...recurse into the directory to get deeper files
				}
			} else {										// if its a file...
				printf("%s\n", dir_entry->d_name);			// ...print its name
			}
		}
		dir_entry = readdir(dir); 							// get next entry
	}
	return;
}

void ls(char *path, bool recurse_flag) {
	/* Insert code here*/
	if (path) {
		ls_rec_help(path, recurse_flag);
	} else {  
		ls_rec_help(".", recurse_flag);
	}
	printf("\n");
}

int main(int argc, char *argv[]){
	if(argc < 2){ // No -R flag and no path name
		ls(NULL, false);
	} else if(strcmp(argv[1], "-R") == 0) { 
		if(argc == 2) { // only -R flag
			ls(NULL, true);
		} else { // -R flag with some path name
			ls(argv[2], true);
		}
	}else { // no -R flag but path name is given
    	ls(argv[1], false);
  }
	return 0;
}