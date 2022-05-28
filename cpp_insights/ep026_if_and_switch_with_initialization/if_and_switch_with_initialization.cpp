/********
  This example demonstrates about 
  C++ 17 if and switch with initialization

 *********/

int getInt() {
	return 5;
}

double getDouble() {
	return 7.9;
}

int main() {

	if(int val = getInt();
	   5 == val) {
		val = val * val;
	}
	else if(double val = getDouble();
			7.9 == val) {
		val = val * 2;
	}
	else {
		val = val * 3;
	}

	switch(int val = getInt();
		   val) {
		case 1:
			val = val + 1;
			break;
		case 2:
			val = val + 2;
			break;
		case 3:
			val = val + 3;
			break;
		default:
			val = val + 5;
			break;
	}

	return 0;
}

/*******
  END OF FILE
 *******/
