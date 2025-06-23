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


    template <typename T>
    void ProcessNextByte(byte b, T&& frameCompleted) {
        static std::string frame{};
        static bool inHeader{false};
        static bool wasESC{false};
        static bool lookingForSOF{false};

        if (inHeader) {
            if ((ESC == b) && not wasESC) {
                wasESC = true;
                return;
            } else if (wasESC) {
                wasESC = false;

                if ((SOF == b) || (ESC != b)) {
                    // if b is not SOF discard the frame
                    if (SOF == b) {
                        frameCompleted(frame);
                    }

                    frame.clear();
                    inHeader = false;
                    return;
                }
            }

            frame += static_cast<char>(b);

        } else if ((ESC == b) && !lookingForSOF) {
            lookingForSOF = true;
        } else if ((SOF == b) && lookingForSOF) {
            inHeader = true;
            lookingForSOF = false;
        } else {
            lookingForSOF = false;
        }
    }

*******/

#include <coroutine>
#include <exception>
#include <utility>

int main() { return 0; }

/*****
    END OF FILE
**********/
