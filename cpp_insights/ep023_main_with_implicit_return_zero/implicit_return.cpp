/********
  This example demonstrates about compiler returning implicit zero from
  main when no return statement is provided
 *******/

int main (int argc, char * argv[]) {

    if(0 == argc) 
        return 1;

    // return 0;    (impilicit) // check in https://cppinsights.io/
}

/*****
  END OF FILE
 ******/
