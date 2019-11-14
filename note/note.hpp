#ifndef note_h
#define note_h
#include <iostream>
#include <string>
#include "text.hpp"
#include "date.hpp"
#include "prop.hpp"
//delete_time (in days)
#define BASIC_DELETE_TIME 60 //60 days
//!delete_time
class basic_note{
protected: 
    typedef text text_type; //use default text
    typedef  date date_type;
    typedef props prop_type;
    typedef std::string id_type;
private:
    text_type text_data;
    date_type date_data;
    prop_type prop_data;
    id_type local_id;
public:
    basic_note(text_type text__, date_type date__, prop_type prop__,  id_type local_id):
        text_data{text__}, date_data{date__}, prop_data{prop__}
    {}
    virtual text_type & get_text(){
        return this->text_data;
    }
    virtual void set_text(std::string text){
        this->text_data = text;
    }
    virtual void set_text(const char text[]){
        this->text_data = text;
    }
    virtual date_type& get_date(){
        return this->date_data;
    }
    virtual prop_type&get_props(){
        return this->prop_data;
    }
};

class quick_note : public basic_note{
private:
    signed long long time_to_delete;
private:
    signed long long calc_delete_time(){
        this->time_to_delete =  BASIC_DELETE_TIME - this->get_date().get_days();
        return this->time_to_delete;
    }
protected:

public:
    quick_note(text_type text__, date_type date__, prop_type prop__, id_type id__): basic_note(text__, date__, prop__, id__){

    }    

};

/*auto create_quick_note(props prop, std::string text = "", date date = "0000:00:00 00:00"){

}*/


#endif