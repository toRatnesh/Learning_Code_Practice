/****************

  This example demonstrates about special way to explicitaly cast lambda to function pointer using +.
  (+[](){})()

 ******************/

int main () {
	(+[](){})();
	(&**&*+[](){})();

	([](){})();
	(&**&*[](){})();

	return 0;
}
/*****
  END OF FILE
 *******/
