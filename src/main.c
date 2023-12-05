#include <stdio.h>
#include "ReadFile.h"

int main() {
    size_t  size;
    int **  matrix = ReadMatrixFile( "C:\\Users\\lucas\\Desktop\\tsp3_1194.txt", &size );

    for ( size_t i = 0; i < size; i++ ) {
        for ( size_t j = 0; j < size; j++ ) {
            printf( "%05d ", matrix[ i ][ j ] );
        }
        putchar( '\n' );
    }

    DestroyMatrix( matrix, size );

    return 0;
}
