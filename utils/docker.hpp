#ifndef docker_h
#define docker_h
#include <vector>
#include<string>
#include <map>
#include "../note/text.hpp"
#include <fstream>
#include <filesystem>
#include <cppcms/json.h>
using json = cppcms::json::value;
class docker_pool{
private:
    //config:
    json compiler_config;
    json limits;
    //program_data:
    text text_of_program{""};
    std::string pr_lang;
    std::string name_of_program;

    //input_data:
    std::string input_data;

    //output_data:
    std::ifstream output_file;
private:

    void delete_all_files(std::filesystem::path path__,std::string begin_name){
        std::string command = "rm "+ path__.string() + begin_name + "*";
        system(command.c_str());
    }
public:

    docker_pool(std::string prog_lang, std::string name_of_program_):
        pr_lang{prog_lang},name_of_program{name_of_program_}
    {
        std::ifstream compiler_config_file{"config/compiler.json"};
        compiler_config_file >> this->compiler_config;
        compiler_config_file.close();
        std::ifstream limits_file{"config/compiler_limits.json"};
        limits_file >> this->limits;
        limits_file.close();
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
    void set_pr_lang(std::string text_){
        this->pr_lang = text_;
    }
    void set_pr_lang(char text_[]){
        this->pr_lang = text_;
    }
    void set_pr_lang(text text_){
        this->pr_lang = text_.get_text();
    }

    void set_input(text text_){
        this->input_data = text_.get_text();
    }
    void set_input(char text[]){
        this->input_data = text;
    }
    void set_input(std::string text_){
        this->input_data = text_;
    }

    std::string run_program(){
        if(this->compiler_config[this->pr_lang]["type"].str() == "compile"){
            std::filesystem::path path_to_compile_files{"./data/compiler_files/"};
            std::string compile_file_name = this->name_of_program;
            std::ofstream programm_file{path_to_compile_files.c_str() + compile_file_name + "."+this->pr_lang};
            programm_file << this->text_of_program.get_text();
            programm_file.close();
            //limits:
            std::string lim = this->limits["default_limits"].str();
            //compile_command:
            std::string compile_command= "path_to_files="+path_to_compile_files.string()+";name_of_program="+this->name_of_program + "."+this->pr_lang + ";"+lim + this->compiler_config[this->pr_lang]["compile_command"].str();
            int code = system(compile_command.c_str());
            if(code != 0){
                std::ifstream error_file{"./data/compiler_files/"+this->name_of_program + "." + this->pr_lang + ".output"};
                std::string timed;
                std::string return_error;
                while(std::getline(error_file,timed)){
                    return_error +=  timed + '\n';
                }
                this->delete_all_files("./data/compiler_files/",this->name_of_program);
                return return_error;
            }
            //run_command:
            //input_file:
            std::ofstream file{"./data/compiler_files/" + this->name_of_program + "." + this->pr_lang + ".input" };
            file << this->input_data;
            std::string run_command = "path_to_files="+path_to_compile_files.string()+";name_of_program="+this->name_of_program+"."+this->pr_lang + ";"+ lim + this->compiler_config[this->pr_lang]["run_command"].str();            system(run_command.c_str());
            std::ifstream output_file{"./data/compiler_files/" + this->name_of_program + "." + this->pr_lang + ".output"};
            std::string timed, return_output;
            while(std::getline(output_file,timed)){
                return_output += timed+'\n';
            }
            this->delete_all_files("./data/compiler_files/",this->name_of_program);
            return return_output;
        }
        else if(this->compiler_config[this->pr_lang]["type"].str() == "inter"){
            std::filesystem::path path_to_compile_files{"./data/compiler_files/"};
            std::string compile_file_name = this->name_of_program;
            std::ofstream programm_file{path_to_compile_files.c_str() + compile_file_name + "."+this->pr_lang};
            programm_file << this->text_of_program.get_text();
            programm_file.close();
            //limits:
            std::string lim = this->limits["default_limits"].str();
            //run_command:
            //input_data:
            std::ofstream file{"./data/compiler_files/" + this->name_of_program + "." + this->pr_lang + ".input" };
            file << this->input_data << std::endl;
            std::string run_command = "path_to_files="+path_to_compile_files.string() + ";name_of_program="+this->name_of_program+"."+this->pr_lang + ';'+lim + this->compiler_config[this->pr_lang]["run_command"].str();            system(run_command.c_str());
            std::ifstream output_file{"./data/compiler_files/"+this->name_of_program + "." + this->pr_lang + ".output"};
            std::string timed, return_output;
            while(std::getline(output_file, timed)){
                return_output += timed + '\n';
            }
            this->delete_all_files("./data/compiler_files/",this->name_of_program);
            return return_output;
        }
        return "error";
    }
};
#endif