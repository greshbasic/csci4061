#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include <stdbool.h>


#include <dirent.h>		// for scandir and readdir
#include <sys/stat.h>   // for stat

void ls_rec_help(char *path, bool recurse_flag) {
	struct dirent *dir;

}

void ls(char *path, bool recurse_flag) {
	/* Insert code here*/
	if (path) {
		ls_rec_help(path, recurse_flag);
	} else {
		ls_rec_help(".", recurse_flag);
	}
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
