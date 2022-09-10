/**************
  2.1 if with Initialization
  Any value initialized inside an if statement is valid until the end of the then and the else part (if any). 
  Note that any object being initialized must have a name. Otherwise, the initialization creates and immediately destroys a temporary. 
  In principle, a single _ as a name would be enough (as some programmers prefer but others hate and is not allowed in the global namespace)

  if (int val = getValue(); 0 == (val % 2)) {
  std::clog << val << " is even\n";
  } else {
  std::clog << val << " is odd\n";
  }

  this will be equivalent to (generated using https://cppinsights.io/)
  {
  	int val = getValue();
  	if(0 == (val % 2)) {
  	std::operator<<(std::clog.operator<<(val), " is even\n");
  	} else {
  	std::operator<<(std::clog.operator<<(val), " is odd\n");
  	}
  }

  2.2 switch with Initialization
  Using the switch statement with an initialization allows us to initialize an object/entity for the scope of the switch before formulating the condition to decide where to continue the control flow.

 *************/
#include <iostream>

using user_status_t = enum class UserStatus { BLOCKED, ALLOWED, GREYLISTED };

int getValue() { return 5; }
user_status_t getUserStatus() { return UserStatus::BLOCKED; }

int main() {

	if (int val = getValue(); 0 == (val % 2)) {
		std::clog << val << " is even\n";
	} else {
		std::clog << val << " is odd\n";
	}

	switch(user_status_t status = getUserStatus(); status) {
		case UserStatus::BLOCKED:
			std::clog << "User status is blocked\n"; break;
		case UserStatus::ALLOWED:
			std::clog << "User status is allowed\n"; break;
		case UserStatus::GREYLISTED:
			std::clog << "User status is greylisted\n"; break;
		default:
			std::clog << "User status is unknown\n"; break;
	}

	return 0;
}

/*******
  END OF FILE
 *****/
