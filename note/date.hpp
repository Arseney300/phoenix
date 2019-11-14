#ifndef date_h
#define date_h
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
class date{
private:
    typedef unsigned int uint;
    typedef uint month_type;
    typedef uint day_type;
    typedef uint year_type;
    typedef uint hour_type;
    typedef uint minute_type;
private:
    std::string to_string_data;
protected:
    std::string string_data{"null"};

    year_type year;
    month_type month;
    day_type day;
    hour_type hour;
    minute_type minute;
public:
    date(year_type year_, month_type month_, day_type day_, hour_type hour_, minute_type minute_):
        year{year_}, month{month_}, day{day_}, hour{hour_}, minute{minute_}
    {
        this->string_data = std::to_string(this->year)+':'+std::to_string(this->month)+':'+std::to_string(this->day)+' '+std::to_string(this->hour)+':'+std::to_string(this->minute);
        this->to_string_data =  "year: " + std::to_string(this->year) + " month: " + std::to_string(this->month) + " day: " + std::to_string(this->day) + " hour: " + std::to_string(this->hour) + " minute: " + std::to_string(this->minute);

    }
    date(std::string date_text):
        string_data{date_text}
    {
        std::vector<std::string> splited;
        boost::split(splited, date_text, boost::is_any_of(" "), boost::token_compress_on);
        std::vector<std::string> ymd;
        boost::split(ymd, splited[0], boost::is_any_of(":"), boost::token_compress_on);
        std::vector<std::string> hm;
        boost::split(hm, splited[1], boost::is_any_of(":"), boost::token_compress_on);
        this->year = std::stoi(ymd[0]);
        this->month = std::stoi(ymd[1]);
        this->day = std::stoi(ymd[2]);
        this->hour = std::stoi(hm[0]);
        this->minute = std::stoi(hm[1]);
        this->to_string_data =  "year: " + std::to_string(this->year) + " month: " + std::to_string(this->month) + " day: " + std::to_string(this->day) + " hour: " + std::to_string(this->hour) + " minute: " + std::to_string(this->minute);
    }
    date(char  date_text_[]):
        string_data{date_text_}
    {
        std::string date_text{date_text_};
        std::vector<std::string> splited;
        boost::split(splited, date_text, boost::is_any_of(" "), boost::token_compress_on);
        std::vector<std::string> ymd;
        boost::split(ymd, splited[0], boost::is_any_of(":"), boost::token_compress_on);
        std::vector<std::string> hm;
        boost::split(hm, splited[1], boost::is_any_of(":"), boost::token_compress_on);
        this->year = std::stoi(ymd[0]);
        this->month = std::stoi(ymd[1]);
        this->day = std::stoi(ymd[2]);
        this->hour = std::stoi(hm[0]);
        this->minute = std::stoi(hm[1]);
        this->to_string_data =  "year: " + std::to_string(this->year) + " month: " + std::to_string(this->month) + " day: " + std::to_string(this->day) + " hour: " + std::to_string(this->hour) + " minute: " + std::to_string(this->minute);
    }
    std::string to_string(){
        return this->to_string_data;
    }

    auto get_days(){
        return this->day;
    }
};
#endif