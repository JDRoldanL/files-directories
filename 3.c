#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAXLON 10000


int main(int argc, char *argv[]){
    struct stat sb;
    int leidos, fildes;
    FILE* fd;
    char cadena[MAXLON];

    //char cadena2[MAXLON];

    if (argc != 3) {
        fprintf(stderr, "Faltan parámetros o parámetros inválidos en: %s [-nro_lineas] [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }else{        
        if (stat(argv[2], &sb) == -1) {
            perror("Error en stat");
            exit(EXIT_FAILURE);
        }
        if((sb.st_mode & S_IFMT) != S_IFREG){
            fprintf(stderr, "No es un archivo regular\n");
        }

        fd = fopen(argv[2],"rb");
        fseek(fd, 0, SEEK_END);
        int cont = 0;
        unsigned long long posicion = ftell(fd);
        
        while (cont > atoi(argv[1]) && posicion){
            if( fgetc(fd) == '\n'){
                cont--;
            }
            fseek(fd, --posicion, SEEK_SET);
        }
        if (posicion != 0){
            posicion+=2;
        }       
        

        fildes = open(argv[2],O_RDONLY);
        lseek(fildes, posicion, SEEK_SET);
        while ((leidos = read(fildes,cadena,MAXLON))!= 0) {
            sleep(2);
            printf("%s" ,cadena);
        }
        printf("\n");

    }
    return 0;

}