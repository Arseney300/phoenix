#ifndef begin_h
#define begin_h
#include <cppcms/view.h>
#include <string>
#include <cppcms/form.h>
#endif
namespace main_window_content{

    struct quick_note_form: public cppcms::form{
        cppcms::widgets::textarea textarea;
        quick_note_form(){
            textarea.name("QuickNoteTextArea");
            add(textarea);
        }
    };


    struct example{
        std::string title{"Примеры"};
        std::vector<std::string> names;
        std::vector<std::string> file_names;

    };

    struct search_area: public cppcms::form{
        cppcms::widgets::text input;
        std::string placeholder{"поиск"};
        std::string button_name{"Найти"};
        search_area(){
            input.name("search");
            add(input);
        }
    };

    struct Left_title{
        std::string main_title = "PHOENIX";
        std::string first_button_name = "news";
        std::string second_button_name = "contacts";
        std::string third_button_name = "source code";
    };

    struct content: public cppcms::base_content{
        std::string title {"Phoenix"};
        std::string welcome_text {"Phoenix -- современнный сервис для создания заметок. Основная идея сервиса заключается в упрощении возможности делиться заметками, как между зарегестрированными, там и обычными пользователями"};
        std::string hello_user_text {"Hello, user"}; //default -- user, can change to nickname of user
        std::string new_text_title { "Обновление 3.0.5"};
        std::string new_text {"Добавлена возможность работы с файлами \n Обновлён движок сайта \n Добавлена возможность компилировать программы \n Обновлён движок"};
        std::string reg_button_name{"РЕГИСТРАЦИЯ"};

        example examples;
        search_area search;

        Left_title left_title;

        struct Account{
            std::string account_name{"PHOENIX"};//default
        }account;

        struct quick_notes{
            std::string data;
            std::string title{"Быстрая заметка:"};
            std::string input_text{"Введите текст:"};
            std::string button_name{"СОЗДАТЬ"};
        }quick_note;
        quick_note_form qn_form;
    };

}

