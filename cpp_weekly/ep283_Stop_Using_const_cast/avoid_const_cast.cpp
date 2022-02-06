/**********
 *	This example demonstrates the undefined behavior of using const_cast on const object and 
 *	suggests why it should be not used.
 *
 *	For mroe info visit:
 *	Documentation:	http://eel.is/c++draft/dcl.type.cv#4
 *	Tutorial by Jason:	https://www.youtube.com/watch?v=iuLwHoMFP_Y&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=284	
 *
 *	Check another example in tutorial video.
 *
 ************/

#include <iostream>

struct S {

	int i;

	private:
	template<typename Self>
		static decltype(auto) get_i_common(Self * self) {
			return (self->i);
		}

	public:
	decltype(auto) get_i() {
		return get_i_common(this);
	}

	decltype(auto) get_i() const {
		return get_i_common(this);
	}

};

int main() {

	/* case -1 
	   const int i = 5;
	   const_cast<int &>(i) = 32;  // const_cast of const object is UB
	   return i;   // i here will return UB valule

*/

	/* case -2 this is one way to avoid const cast*/
	S s{5};
	s.get_i() = 13;

	const S s2{23};
	//s2.get_i() = 33;    //assignment of read-only location 's2.S::get_i()'

}

/**********
 *	END OF FILE
 * ********/
