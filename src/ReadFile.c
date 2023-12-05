#include <stdio.h>
#include <stdlib.h>

int MatrixSide( FILE * matrixFile ) {
/*
====================
=
= MatrixSide
=
= Identifies the side of a matrix from a text file.
=
= matrixFile must be a valid file pointer with read access on text mode.
=
====================
*/
    
    size_t  size = 64;
    char *  line = malloc( size * sizeof( char ) );

    for ( size_t i = 0; ; i++ ) {
        line[ i ] = fgetc( matrixFile );

        if ( line[ i ] == '\n' || line[ i ] == '\0' ) {
            line[ i ] = '\0';
            break;
        }

        if ( i == size - 1 ) {
            size *= 2;
            line = realloc( line, size * sizeof( char ) );
        }
    }

    size_t  side = 0;
    int     unused;
    char *  seeker = line;
    char *  previous;

    do {
        previous = seeker;
        strtol( seeker, &seeker, 10 );
        side++;
    } while ( previous != seeker );
    side--;

    free( line );

    rewind( matrixFile );

    return side;
    ( void )unused;
}

int ** ReadMatrixFile( char * matrixFileName, size_t * size ) {
/*
====================
=
= ReadMatrixFile
=
= Read a matrix text file and fills a matrix with its data.
=
= Returned matrix is dynamically allocated, caller must destroy it with DestroyMatrix.
=
====================
*/
    
    FILE * fp = fopen( matrixFileName, "r" );
    if ( fp == NULL ) {
        perror( matrixFileName );
        exit( 1 );
    }
    
    *size = MatrixSide( fp );

    int ** matrix = malloc( *size * sizeof( int * ) );
    for ( size_t i = 0; i < *size; i++ ) {
        matrix[ i ] = malloc( *size * sizeof( int ) );
    }

    for ( size_t i = 0; i < *size; i++ ) {
        for ( size_t j = 0; j < *size; j++ ) {
            fscanf( fp, "%d", &matrix[ i ][ j ] );
        }
    }

    fclose( fp );

    return matrix;
}

void DestroyMatrix( int ** matrix, size_t size ) {
/*
====================
=
= DestroyMatrix
=
= Destroys an integer matrix with size columns.
=
====================
*/
    
    for ( size_t i = 0; i < size; i++ ) {
        free( matrix[ i ] );
    }
    
    free( matrix );
}