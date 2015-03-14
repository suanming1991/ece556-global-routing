// ECE556 - Copyright 2014 University of Wisconsin-Madison.  All Rights Reserved.

#include "ece556.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

// some utils
int startsWith(const char* start, const char* str) {
    int startLength = strlen(start);
    int strLength = strlen(str);
    return strLength < startLength ? 0 : strncmp(start, str, startLength) == 0;
}

/**
 * This function gets all the inputs from the input file specified by fileName 
 * and assign them to routing instance's fields
 * @param  fileName input file to be read
 * @param  rst      a pointer to the routing instance
 * @return          1 on successful
 */
int readBenchmark(const char *fileName, routingInst *rst) {
    char linebuff[80];

    FILE* in = fopen(fileName, "r");
    if(in == NULL) {
        err(-1, "failed to open input file");
    }
    
    while(fgets(linebuff, sizeof(linebuff), in)) {
        char junk[80];
        int lineCount = 0;
        int netCount = 0;
        int numBlockages = -1;
        if (startsWith("grid", linebuff)) {
            printf("grid size: %s", linebuff);
            sscanf(linebuff, "%s %d %d", junk, &rst->gx, &rst->gy);
            printf("gx: %d  gy: %d", rst->gx, rst->gy);
        } else if (startsWith("capacity", linebuff)) {
            printf("default capacity: %s", linebuff);
        } else if (startsWith("num net", linebuff)) {
            printf("num nets: %s", linebuff);
        } else if (startsWith("n", linebuff)) {
            netCount++;
            printf("starting new net %s", linebuff);
        } else if (netCount < rst->numNets) { 
            // we're building a net
            printf("adding net: %s", linebuff);
        } else if (netCount == rst->numNets) {
            printf("Num blockages: %s", linebuff);
        } else if (numBlockages != -1) {
            // building blockages
            printf("Adding blockage: %s", linebuff);
        } else {
            printf("Error parsing file at line %d: %s", lineCount, linebuff);
        }
        lineCount++;    
    }
    return 1;
}

int solveRouting(routingInst *rst) {
    return 1;
}

int writeOutput(const char *outRouteFile, routingInst *rst) {
    return 1;
}


int release(routingInst *rst) {
    return 1;
}
  

