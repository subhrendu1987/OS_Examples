/* 
 * File:   clear.c
 * Author: subhrendu
 *
 * Created on 26 October, 2012, 6:56 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
/*
 * 
 */
#define SCREEN_ROW 30

void clearScreen()
{
    const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO,CLEAR_SCREE_ANSI,12);
}

int main(int argc, char** argv) {
    int count;
    clearScreen();
    return (EXIT_SUCCESS);
}

