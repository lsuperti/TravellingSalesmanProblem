#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "ReadFile.h"
#include "BruteForce.h"

int main() {
    size_t   size;
    int **   matrix;
    int *    bestPath;
    int      cost;
    char *   paths[] = { "./lib/tsp1_253.txt", "./lib/tsp2_1248.txt", "./lib/tsp3_1194.txt", "./lib/tsp4_7013.txt", "./lib/tsp5_27603.txt"  };
    FILE *   outputFile;
    time_t   bruteForceTime;
    clock_t  bruteForceTicks;

    for ( int i = 0; i < 5; i++ ) {
        printf( "Beginning %s computation.\n", &paths[ i ][ 6 ] );

        matrix = ReadMatrixFile( paths[ i ], &size );

        bruteForceTime = time( NULL );
        bruteForceTicks = clock();
        cost = BruteForce( matrix, size, &bestPath );
        bruteForceTime = time( NULL ) - bruteForceTime;
        bruteForceTicks = clock() - bruteForceTicks;

        outputFile = fopen( "./bruteforce.txt", "a" );
        fprintf( outputFile, "%s: %lld s, %ld ticks; result: %d.\n", &paths[ i ][ 6 ], bruteForceTime, bruteForceTicks, cost );
        printf( "%s completed. Time: %lld s, %ld ticks; result: %d.\n", &paths[ i ][ 6 ], bruteForceTime, bruteForceTicks, cost );

        fclose( outputFile );
        DestroyMatrix( matrix, size );
        free( bestPath );
    }

    return 0;
}
