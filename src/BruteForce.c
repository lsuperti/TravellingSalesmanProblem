#include <stdlib.h>
#include <limits.h>

int PathCost( int ** matrix, int matrixSize, int * path ) {
    int pathCost = 0;

    for ( int i = 0; i < matrixSize; i++ ) {
        pathCost += matrix[ path[ i ] ][ path[ i + 1 ] ];
    }

    return pathCost;
}

int BruteForce_r( int ** matrix, int matrixSize, int * path, int pathLength, int * bestPath, int bestCost ) {
    int cost;
    
    if ( pathLength == matrixSize ) {
        path[ pathLength ] = 0;
        pathLength++;
        cost = PathCost( matrix, matrixSize, path );

        if ( cost < bestCost ) {
            bestCost = cost;
            for ( int i = 0; i < matrixSize; i++ ) {
                bestPath[ i ] = path[ i ];
            }
        }

        pathLength--;

        return bestCost;
    }

    for ( int i = 0; i < matrixSize; i++ ) {
        for ( int j = 0; j < pathLength; j++ ) {
            if ( i == path[ j ] ) {
                goto inPath;
            }
        }

        path[ pathLength ] = i;
        pathLength++;

        bestCost = BruteForce_r( matrix, matrixSize, path, pathLength, bestPath, bestCost );

        pathLength--;

        inPath:
    }

    return bestCost;
}

int BruteForce( int ** matrix, int matrixSize, int ** bestPath ) {
    int * path = malloc( ( matrixSize + 1 ) * sizeof( int ) );
    int   cost;
    
    *bestPath = malloc( ( matrixSize + 1 ) * sizeof( int ) );

    path[ 0 ] = 0;
    
    cost = BruteForce_r( matrix, matrixSize, path, 1, *bestPath, INT_MAX );

    free( path );

    return cost;
}