#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    DIR *d;
    struct stat sb;
    struct dirent *dir;
    int i = 0;
    char* l = "-l";
    if(argc == 1){
        d = opendir(".");
        if (d){
            while ((dir = readdir(d)) != NULL){
                printf("Nombre archivo: %s\n", dir->d_name);
            }
        }
    }else if(argc == 2){
        if(strcmp(argv[1], l)==0){
            d = opendir(".");
            i = 1;
        }else{
            d = opendir(argv[1]);
        }    
    }else if(argc == 3){
        d = opendir(argv[2]);
        i = 1;
    }else{
        d = opendir(".");
        fprintf(stderr, "Faltan parametros o parametros invalidos en: %s [-l] [directory]\n", argv[0]);
        closedir(d);
        return(0);
    }

    if(d){
        while ((dir = readdir(d)) != NULL){
            printf("Nombre archivo: %s\n", dir->d_name);
            if(i == 1){
                lstat(dir->d_name ,&sb);
                printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
                printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
                printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
                printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
                printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
                printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
                printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
                printf( (sb.st_mode & S_IROTH) ? "r" : "-");
                printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
                printf( (sb.st_mode & S_IXOTH) ? "x    " : "-    ");
                printf("Ownership:  UserID=%ld   GroupID=%ld    ", (long) sb.st_uid, (long) sb.st_gid);
                printf("Contador de referencias: %ld   ", (long) sb.st_nlink);
                printf("Tamaño de archivo: %lld bytes    ", (long long) sb.st_size);
                printf("Bloques asignados: %lld\n\n", (long long) sb.st_blocks);
            }
        }
    }  
    closedir(d);
    return(0);
}