#ifndef prop_h
#define prop_h
#include <string>
#include <map>
#include <vector>
#include <utility>
class props{
private:
    std::map<std::string, std::vector<std::string>> data;
public:
    auto get(std::string key){
        return &this->data[key];
    }
    void append(std::string key, std::vector<std::string> values){
        this->data.insert({key, values});
    }
    auto get_raw(){
        return &this->data;
    }

    props &operator=(props&source){
        this->data = source.data;
        return *this;
    }
    props(){

    }   
    props(std::map<std::string, std::vector<std::string>> new_map){
        this->data = new_map;
    }
    
};
#endif