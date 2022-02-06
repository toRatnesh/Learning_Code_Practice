/************
  This example demonstrates about c++ garbage initialization.

  When a variable is garbage initialized compiler ignores any operation perform on it as it will generate a random result.

 ************/

int main() {
    int i;
    ++i;
    i++;
    i += 23;
    i *= 4;
    return i;   // compiler may ignore opertaions and return any random number
}

/******
  END OF FILE
 *******/
