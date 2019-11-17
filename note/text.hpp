#ifndef text_h
#define text_h
#include <string>
#include <cstring>
class basic_text{
protected:
    typedef std::string text_type;
    text_type data;
public:
    virtual text_type & get_text(){
        return this->data;
    }
    virtual void set_text(std::string text){
        this->data = text;
    }
    virtual void set_text(char* text){
        this->data = text;
    }

    basic_text(text_type text): 
        data{text}
    {}
    basic_text(char mas[]):
        data{mas}
    {}
};

class text:  public basic_text{
private:
    typedef unsigned int text_size;

    text_size length;
public:
    text(const char text[]) : basic_text(text){
        this->length = strlen(text);
    }
    text(std::string text) : basic_text(text){
        this->length = text.length();
    }
    
    void set_text(std::string text) override {
        this->data = text;
        this->length = text.length();
    }
    void set_text(char text[]) override{
        this->data = text;
        this->length = strlen(text);
    }

    text_type & get_text() override{
        return this->data;
    }

    text& operator=(const text& source){
        //переделать, пока что всё в этом классе временно 
        this->data  = source.data;
        this->length = source.length;
        return *this;
    }

    text& operator=(std::string text){
        this-> data = text;
        this->length = text.length();
        return *this;
    }
    text& operator=(char text[]){
        this->data = text;
        this->length = strlen(text);
        return *this;
    }
};

#endif