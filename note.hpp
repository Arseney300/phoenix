#ifndef note_hpp
#define note_hpp
#include "boost_include.hpp"
#include <string>
#include <memory>
#include <iostream>

/*
DATE CLASS
not exist validation with mounth(such as 31 day in feb)!!!!need fix
*/
class date{
    private:
        int validate(unsigned int num, std::string type){
            if (type == "year"){
               return ( (num>=1000 and num<=9999) ? num: -1);
            }
            else if (type=="mounth"){
                return ( (num>=1 and num<=12) ? num:-1 );
            }
            else if(type=="day"){
                return (num>=1 and num<=31 ? num:-1);
            }
            else if(type=="hour"){
                return (num>=1 and num<=23 ? num:-1);
            }
            else if(type=="min"){
                return (num>=1 and num<=59 ? num:-1);
            }
            else if(type=="sec"){
                return (num>=1 and num<=59 ? num:-1);
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

        date():
        year(0),mounth(0),day(0),hour(0),minute(0),second(0)
        {}

        date(std::string date){
            std::vector<std::string> split_str;
            boost::split(split_str,date,boost::is_any_of(";"));
            try{
                this->year = validate(std::stoi(split_str.at(0)),"year");
            }
            catch(std::exception& e){
                this->year = 0;
            }
            try{
                this->mounth = validate(std::stoi(split_str.at(1)),"mounth");
            }
            catch(std::exception&e){
                this->mounth = 0;
            }
            try{
                this->day = validate(std::stoi(split_str.at(2)),"day");
            }
            catch(std::exception&e){
                this->day = 0;
            }
            try{
                this->hour = validate(std::stoi(split_str.at(3)),"hour");
            }
            catch(std::exception&e){
                this->hour = 0;
            }
            try{
                this->minute = validate(std::stoi(split_str.at(4)),"min");
            }
            catch(std::exception&e){
                this->minute = 0;
            }
            try{
                this->second = validate(std::stoi(split_str.at(5)),"sec");
            }
            catch(std::exception&e){
                this->second = 0;
            }
        }
        date(int year,int mounth,int day,int hour, int minute,int second):
        year(year),mounth(mounth),day(day),hour(hour),minute(minute),second(second)
        {

        }
        date(int year,int mounth,int day):
        year(year),mounth(mounth),day(day),hour(0),minute(0),second(0)
        {
            
        }

        date(date& source):
        year(source.year),mounth(source.mounth),day(source.day),hour(source.hour),minute(source.minute),second(source.second)
        {
            
        }
        date(date&&source)
        {
            this->year = std::move(source.year);
            this->mounth = std::move(source.mounth);
            this->day = std::move(source.day);
            this->hour = std::move(source.hour);
            this->minute = std::move(source.minute);
            this->second = std::move(source.second);
        }

        date& operator= (date& other){
            if(this == &other){
                return *this;
            }
            this->year = other.year;
            this->mounth = other.mounth;
            this->day = other.day;
            this->hour = other.hour;
            this->minute = other.minute;
            this->second = other.second;
            return *this;
        }

        date& operator= (date&& other){
            if (this== &other){
                return *this;
            }
            this->year = other.year;
            this->mounth = other.mounth;
            this->day = other.day;
            this->hour = other.hour;
            this->minute = other.minute;
            this->second = other.second;
            return *this;
        }
        std::string to_string(){
            return std::to_string(this->year) +'-'+ std::to_string(this->mounth) + '-' + std::to_string(this->day)+' '+std::to_string(this->hour) + ':'+std::to_string(this->minute) + ':'+std::to_string(this->second);
        }
        
};


//test class
//отстутсвие глубокого копирования 
//да и вообще отстуствие копирования в принципе
//нужно будет добавить НЕсырые указатели и закончить этот класс
// auto f = std::make_unique<std::function<void()>>([]() { ; }); timed
//с class note аналогично 
class text{
private:
    unsigned int size{0};
    std::unique_ptr<char[]> data;
public:
    char* get_text(){
        return data.get();
    }
    unsigned int get_size(){
        return this->size;
    }
    //append не сделат без доп capacity, нужно реализовать 
    /*void append(std::string append_text){
        unsigned int new_size = this->size + append_text.length();

    }
    void append(char append_text){

    }*/

    void set_text(std::string t){
        this->data = std::unique_ptr<char[]>{new char[t.length()]};
        //this->data = (char*)t.c_str();
        std::copy(t.c_str(), t.c_str()+strlen(t.c_str()),this->data.get());
        this->size = strlen(this->data.get());
    }
    void set_text(char t[] ){
        this->data = std::make_unique<char[]>(strlen(t));
        this->size = strlen(t);
        std::copy(t,t+strlen(t),this->data.get());
    }
    /*void set_text(char*t){
        this->text = t;
    }*/
    text(std::string text){
        set_text(text);
    }
    text(char text[]){
        set_text(text);
    }
    text(int num){
        this->data = std::make_unique<char[]>(num);
    }

    text(){
        set_text("");
    }
    text(text& source){
        //копирование
        this->size = source.size;
        this->data = std::make_unique<char[]>(source.get_size());
        std::copy(source.get_text(),source.get_text()+source.get_size(),this->data.get());
    }
    
    text(text&&source){
        //перемещение
        this->data = std::move(source.data);
        this->size = std::move(source.size);
    }
    text& operator= (text&source){
        //работает как копирование
        if(this == &source){
            //проверка на самокопирование 
            return *this;
        }
        this->size = source.size;
        this->data = std::make_unique<char[]>(source.size);
        std::copy(source.get_text(),source.get_text()+source.get_size(),this->data.get());
        return *this;
    }
    text& operator= (text&& source){
        if (this == &source){
            return *this;
        }
        this->size = source.size;
        this->data = std::make_unique<char[]>(source.size);
        std::copy(source.get_text(), source.get_text()+source.get_size(),this->data.get());
        return *this;
    }

    friend std::ostream& operator<< (std::ostream& stream, text& source){
        stream << source.get_text();
        return stream;
    }
    friend std::istream& operator>>(std::istream& stream,text&source){
        int num = stream.gcount();
        std::unique_ptr<char[]> simbols = std::make_unique<char[]>(num);
        stream >> simbols.get();
        source.set_text(simbols.get());
        return stream;
    }
};


class note{
private:
    text data;
    std::map<std::string,std::string> prop;
    date creation_date;
public:
    std::string id;
    
    char* get_text(){
        return data.get_text();
    }

    date get_date(){
        return this->creation_date;
    }


    note(char* input_text, date date,bool share):
    prop({{std::string{"share"}, std::string{share ? "true":"false"}}})
    {
        //default init
        this->creation_date = date;
        this->data = text(input_text);
    }
    note(char input_text[]):
    prop({{"share","false"}})
    {
        this->data = text(input_text);
    }
    note(char input_text[],date date){
        this->creation_date = date;
        this->data = text(input_text);
    }


};


class quick_note:note{
    

};

class user_note:note{
    private:
        std::string creater_id;
};





#endif // !note_hpp