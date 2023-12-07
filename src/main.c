#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "ReadFile.h"
#include "BruteForce.h"
#include "Approximate.h"

int main() {
    size_t   size;
    int **   matrix;
    int *    bestPath;
    int      cost;
    char *   paths[] = { "./lib/tsp1_253.txt", "./lib/tsp2_1248.txt", "./lib/tsp3_1194.txt", "./lib/tsp4_7013.txt", "./lib/tsp5_27603.txt"  };
    FILE *   outputFile;
    time_t   realTime;
    clock_t  ticks;

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
