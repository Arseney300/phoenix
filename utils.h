#ifndef utils_h
#define utils_h
#include <string>
#include <stdlib.h>
#include <fstream>
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


void send_email(std::string email,std::string text){
    std::string from{"From: <Arseney300@gmail.com>"};
    std::string to{"To: <"+email+">"};
    std::string subject{"Subject: Reset password for phoenix note"};
    std::string command_1{"touch ./data/"+email+"_msg.txt"};
    std::string command_3{"rm ./data/"+email+"_msg.txt"};
    std::string command_2{"cat ./data/"+email+"_msg.txt | msmtp -a gmail "+email};
    system(command_1.c_str());
    std::ofstream file;
    try{
        file.open("./data/"+email+"_msg.txt");
        file << from << std::endl;
        file << to << std::endl;
        file << subject << std::endl;
        file << text << std::endl;
    }
    catch(std::exception&e){
        std::cout << e.what() << std::endl;
    }
    system(command_2.c_str());
    system(command_3.c_str());

}





#endif // !utils_h