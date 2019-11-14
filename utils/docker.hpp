#ifndef docker_h
#define docker_h
#include <vector>
#include<string>
#include <map>
#include "../note/text.hpp"
#include <fstream>
class docker_pool{
private:
    //std::map<std::string, std::string> lang{{"cpp","cpp"}, {"pascal","pascal"}, {"python", "python"}};
    //std::map<std::string, std::string> run_command{{"cpp", "g++-9 -std=c++17 $name_of_program -o $name_of_program.out"}, {"python", "python3.7 $name_of_program"}};
    std::vector<std::string> limits;

    text text_of_program{""};
    std::string pr_lang;
    std::string name_of_program;

    std::ifstream output_file;
    std::ifstream config_file;
private:

    void create_compile_file(){
        std::ofstream compile_file;
        compile_file.open("./"+this->name_of_program);
        //this->text_of_program.get_text() >> compile_file;
        compile_file << this->text_of_program.get_text();
        compile_file.close();
    }
public:

    docker_pool(std::string prog_lang, std::string name_of_program_){
        this->pr_lang = this->lang[prog_lang];
        this->name_of_program = name_of_program_;
        //this->output_file.open("./"+this->name_of_program + ".text_output");
    }
    ~docker_pool(){
        this->output_file.close();
    }
    void set_text(std::string text_){
        this->text_of_program = text_;
    }
    void set_text(char text[]){
        this->text_of_program = text;
    }
    void set_text(text text_){
        this->text_of_program = text_.get_text();
    }
    std::string run_program(){
        
    }
};
#endif