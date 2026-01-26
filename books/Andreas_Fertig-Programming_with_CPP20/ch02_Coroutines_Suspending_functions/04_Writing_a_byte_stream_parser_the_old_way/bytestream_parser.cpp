/*******

References

    Programming with C++20 | Andreas Fertig
	https://en.cppreference.com/w/cpp/language/coroutines


Chapter 2 | Coroutines: Suspending functions

    A coroutine is a function that can suspend itself.

2.4 Writing a bytestream parser the old way

    we like to parse a data-stream containing the string ”Hello World”

    A protocol that contains a special ESC byte (not to be confused with ASCII ESC, 0x1B), which stands for escape. 
    ESC’s job is to escape all other protocol bytes. 
    In the payload, each byte that has the same value  as ESC is escaped with ESC as well.
    That way, the protocol can contain the full width of a byte and not only printable characters.

    A frame starts with ESC + SOF, where SOF stands for Start Of Frame.

                        Escape 'H'
                        -------
    | 0x70 | ESC | SOF | ESC | ‘H’ | ‘e’ | ‘l’ | ‘l’ | ‘o’ | ESC | SOF | 0x7 | ESC | SOF 
    | ‘W’ | ‘o’ | ‘r’ | ‘l’ | ‘d’ | ESC | SOF | 0x99 | …


    static const byte ESC{'H'};
    static const byte SOF{0x10};

    How can we implement this protocol? 
    There are various ways. Most likely, we tend to create a class to track the state.


*******/

#include <iostream>
#include <vector>
#include <string>

using byte_t = std::byte;

const byte_t SOF{0x11};
const byte_t ESC{'H'};

auto processBytes(byte_t bval, auto && callback) {

    static bool l_in_header{false};
    static bool l_was_esc{false};
    static bool l_searching_sof{false};

    static std::string l_frame;


    if(l_in_header) {

        if(l_was_esc) {
            l_was_esc = false;

            if((SOF == bval) || (ESC != bval)) {

                if(SOF == bval) {
                    callback(l_frame);
                }

                l_frame.clear();
                l_in_header = false;
                return;
            }
        }
        else if((not l_was_esc) && (ESC == bval)) {
            l_was_esc = true;
            return;
        }

        l_frame = l_frame + static_cast<char>(bval);

    }
    else if((not l_searching_sof) && (ESC == bval)) {
        l_searching_sof = true;
    }
    else if(l_searching_sof && (SOF == bval)) {
        l_searching_sof = false;
        l_in_header = true;
    }
    else {
        l_searching_sof = false;
    }


}

int main() { 

    const std::vector<byte_t> fakebytes1{
        byte_t{0x70}, byte_t{0x24}, ESC,         SOF,         ESC,
        byte_t{'H'},  byte_t{'e'},  byte_t{'l'}, byte_t{'l'}, byte_t{'o'},
        ESC,          SOF,          byte_t{0x7}, ESC,         SOF};

    const std::vector<byte_t> fakebytes2{byte_t{'W'}, byte_t{'o'}, byte_t{'r'},
                                         byte_t{'l'}, byte_t{'d'}, ESC,
                                         SOF,         byte_t{0x99}};

    auto frameDisplay = [](const std::string& frame) {
        std::cout << "Frame: " << frame << '\n';
    };


    for(const auto bval : fakebytes1) {
        processBytes(bval, frameDisplay);
    }

    for(const auto bval : fakebytes2) {
        processBytes(bval, frameDisplay);
    }

    return 0;    
}

/*****
    END OF FILE
**********/

