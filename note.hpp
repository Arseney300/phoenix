#ifndef note_hpp
#define note_hpp
#include "boost_include.hpp"
#include <string>

class date{
    private:
        int validate(unsigned int num, std::string type){
            if (type == "year"){
                /////сделать нормальную валидацию
            }
        }
    public:
        unsigned int year{0};
        unsigned int mounth{0};
        unsigned int day{0};
        unsigned int hour{0};
        unsigned int minute{0};
        unsigned int second{0};

        int size{0};

        date(std::string date){
            std::vector<std::string> split_str;
            boost::split(split_str,date,boost::is_any_of(";"));
            try{
                ///+ добавить сюда валидацию 
                this->year = std::stoi(split_str.at(0));
            }
            catch(std::exception& e){
                this->year = 0;
            }
            try{
                this->mounth = std::stoi(split_str.at(1));
            }
            catch(std::exception&e){
                this->mounth = 0;
            }
            try{
                this->day = std::stoi(split_str.at(2));
            }
            catch(std::exception&e){
                this->day = 0;
            }
            try{
                /////////и так далее, нужно продолжить 
            }
            catch(std::exception&e){

            }
        }
        date(int year,int mounth,int day,int hour, int minute,int second):
        year(year),mounth(mounth),day(day),hour(hour),minute(minute),second(second)
        {

        }
        date(int year,int mounth,int day):
        year(year),mounth(mounth),day(day)
        {
            
        }


};


//test class
//отстутсвие глубокого копирования 
//да и вообще отстуствие копирования в принципе
//нужно будет добавить НЕсырые указатели и закончить этот класс
//с class note аналогично 
class text{
private:
    unsigned int size{0}; //start value = 0
    char* text;
public:
    char* get_text(){
        return text;
    }
    unsigned int get_size(){
        return this->size;
    }

    void set_text(std::string t){
        this->text = (char*)t.c_str();
        this->size = strlen(this->text);
    }
    void set_text(char t[] ){
        this->text = (char*)(t);
        this->size = strlen(this->text);
    }
    /*void set_text(char*t){
        this->text = t;
    }*/
};


class note{
private:
    //text text();
    std::map<std::string,std::string> prop;
    
public:
    std::string id;
    

    note(bool share):
    prop({{std::string{"share"}, std::string{share ? "true":"false"}}})
    {
        //default init
    }

};




#endif // !note_hpp