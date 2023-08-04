/**********

    This example demonstrates about C++ smart pointers - Deleter

    For more info visit
    Back to Basics: C++ Smart Pointers - David Olsen - CppCon 2022 
    https://www.youtube.com/watch?v=YokY6HzLkXs

******************/

#include <iostream>
#include <memory>
#include <cstdio>

struct File_Deleter {
    void operator()(FILE * fp) { std::cout << "Closing file\n"; fclose(fp); return; }
};

int main() {


    {
        std::cout << "=== Deleter for unique_ptr ===\n";
        {
            std::unique_ptr<std::FILE, File_Deleter> upf(fopen("testfile.txt", "w"));
        }
        {
            auto File_Deleter = [] (FILE * fp) { std::cout << "Closing file\n"; fclose(fp); return; };
            std::unique_ptr<std::FILE, decltype(File_Deleter)> upf(fopen("testfile.txt", "w"));
        }
        {
            std::unique_ptr<std::FILE, 
                            decltype([] (FILE * fp) { std::cout << "Closing file\n"; fclose(fp); return;})
                            > upf(fopen("testfile.txt", "w"));
        }
    }

    {
        std::cout << "=== Deleter for shared_ptr ===\n";
        {
            std::shared_ptr<std::FILE> spf1(fopen("testfile.txt", "w"), File_Deleter{});
            std::shared_ptr<std::FILE> spf2(spf1);
        }
        {
            auto File_Deleter = [] (FILE * fp) { std::cout << "Closing file\n"; fclose(fp); return; };
            std::shared_ptr<std::FILE> spf1(fopen("testfile.txt", "w"), File_Deleter);
            std::shared_ptr<std::FILE> spf2(spf1);
        }
        {
            std::shared_ptr<std::FILE> spf1(fopen("testfile.txt", "w"),
                                        [] (FILE * fp) { std::cout << "Closing file\n"; fclose(fp); return; });
            std::shared_ptr<std::FILE> spf2(spf1);                                        
        }
    }

    return 0;
}

/**********
    END OF FILE
******************/

