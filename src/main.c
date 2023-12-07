#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>
#include "ReadFile.h"
#include "BruteForce.h"
#include "Approximate.h"

int main( int argc, char * argv[] ) {
    size_t   size;
    int **   matrix;
    int *    bestPath = NULL;
    int      cost;
    char *   paths[] = { "./lib/tsp1_253.txt", "./lib/tsp2_1248.txt", "./lib/tsp3_1194.txt", "./lib/tsp4_7013.txt", "./lib/tsp5_27603.txt"  };
    FILE *   outputFile;
    time_t   realTime;
    clock_t  ticks;
    int      test;
    bool     bruteForceTest = true;
    int      repeatCount = 1;

    if ( argc > 1 ) {
        // Test to perform (first argument)
        test = strtol( argv[ 1 ], NULL, 10 );

        // Algorithm or repeat count (second argument)
        if ( argc > 2 ) {
            // Algorithm
            if ( *argv[ 2 ] == 'b' ) {
                bruteForceTest = true;
            } else if ( *argv[ 2 ] == 'a' ) {
                bruteForceTest = false;
            // Repeat count
            } else {
                repeatCount = strtol( argv[ 2 ], NULL, 10 );
            }

            // Repeat count (third argument)
            if ( argc > 3 ) {
                repeatCount = strtol( argv[ 3 ], NULL, 10 );
            }
        }

        matrix = ReadMatrixFile( paths[ test - 1 ], &size );

        for ( int i = 0; i < repeatCount; i++ ) {
            if ( bruteForceTest ) {
                BruteForce( matrix, size, &bestPath );
            } else {
                DestroyMatrix( matrix, size );
                matrix = ReadMatrixFile( paths[ test - 1 ], &size );
                
                Approximate( matrix, size );
            }
        }

        DestroyMatrix( matrix, size );
        free( bestPath );
        exit( EXIT_SUCCESS );
    }

    for ( int i = 0; i < 5; i++ ) {
        matrix = ReadMatrixFile( paths[ i ], &size );

        realTime = time( NULL );
        ticks = clock();
        cost = Approximate( matrix, size );
        realTime = time( NULL ) - realTime;
        ticks = clock() - ticks;

        outputFile = fopen( "./approximate.txt", "a" );
        fprintf( outputFile, "%s: %lld s, %ld ticks; result: %d.\n", &paths[ i ][ 6 ], realTime, ticks, cost );
        printf( "%s completed. Time: %lld s, %ld ticks; result: %d.\n", &paths[ i ][ 6 ], realTime, ticks, cost );

        fclose( outputFile );
        DestroyMatrix( matrix, size );
    }
    
    for ( int i = 0; i < 5; i++ ) {
        printf( "Beginning brute force %s computation.\n", &paths[ i ][ 6 ] );

        matrix = ReadMatrixFile( paths[ i ], &size );

        realTime = time( NULL );
        ticks = clock();
        cost = BruteForce( matrix, size, &bestPath );
        realTime = time( NULL ) - realTime;
        ticks = clock() - ticks;

        outputFile = fopen( "./bruteforce.txt", "a" );
        fprintf( outputFile, "%s: %lld s, %ld ticks; result: %d.\n", &paths[ i ][ 6 ], realTime, ticks, cost );
        printf( "%s completed. Time: %lld s, %ld ticks; result: %d.\n", &paths[ i ][ 6 ], realTime, ticks, cost );

        fclose( outputFile );
        DestroyMatrix( matrix, size );
        free( bestPath );
    }

    return 0;
}
