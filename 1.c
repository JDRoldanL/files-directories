#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    struct stat sb;

    if (argc != 2) {
        fprintf(stderr, "Faltan parametros en: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (stat(argv[1], &sb) == -1) {
        perror("Error en stat");
        exit(EXIT_FAILURE);
    }

    printf("Tipo de archivo:                ");

    switch (sb.st_mode & S_IFMT) {
    case S_IFDIR:  printf("Directorio\n");               break;
    case S_IFREG:  printf("Archivo normal\n");            break;
    default:       printf("No es un archivo o directorio.\n");
                    exit(EXIT_FAILURE);
    }

    printf("Contador de referencias:              %ld\n", (long) sb.st_nlink);
    printf("Tamaño de archivo:                %lld bytes\n", (long long) sb.st_size);
    printf("Bloques asignados:                    %lld\n", (long long) sb.st_blocks);

    exit(EXIT_SUCCESS);
}