#include <string>
#include <stdlib.h>
char getRandomChar(){
    char c = 'A' + rand()%24;
    return c;    
}

std::string create_quick_note_id(unsigned int size){
    srand(time(NULL));
    std::string ret;
    for (auto i = 0; i< size; ++i){
        ret += getRandomChar();
    }
    return ret;
}


//std::string note_not_exist = 