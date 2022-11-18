/************
    This example demonstrates how a simple bug has lead to PS jailbreak
    and it could have been avoided by simply addding -Wconversion flag

    This also demonstrates that we should always follow best practices

    For more info visit:
    episode: https://www.youtube.com/watch?v=rWCvk4KZuV4&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=347

************/

#include <iostream>

size_t getSize() { return 876499869; }
int takeInt(int parm) {return parm *2; } 

int main() {
    size_t sval = getSize();
    int retval = takeInt(sval); // warning: conversion from 'size_t' {aka 'long unsigned int'} to 'int' may change value
    return retval;
}

/*************
    END OF FILE
***************/
