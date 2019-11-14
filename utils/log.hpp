#ifndef log_h
#define log_h
#include <string>
#include <fstream>
#include <filesystem>
class loger{
private:
    std::ofstream main_file;
    std::string global_path;
public:
    loger(std::string name_of_file = "phoenix_main_log.log", std::filesystem::path dir= "/var/log/phoenix/"){
        this->global_path = dir.c_str() + name_of_file;
        this->main_file.open(global_path, std::ios_base::app);
    }


    void open_file(std::filesystem::path file = "/var/log/phoenix/phoenix_main_log.log"){
        this->global_path = file.c_str();
        this->main_file.open(this->global_path, std::ios_base::app);
    }

    void close_file(){
        this->main_file.close();
    }

    void write(std::string text){
        this->main_file << text << std::endl;
    }
    void write(const char text[] ){
        this->main_file << text << std::endl;
    }
    ~loger(){
        this->main_file.close();
    }
};
#endif