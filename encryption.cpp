#ifndef encryption_h
#define encryption_h
#include "albatross.cpp"
#include <string>
#include <vector>

std::string encrypt_algo(std::string text,std::string key){
    std::vector<uint8_t> btext;
    for (auto i:text)
        btext.push_back(int(i));
    

}


std::string encrypt_pass(std::string pass, std::string key){

}





#endif


int main(){

}