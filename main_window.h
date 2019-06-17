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

    struct content: public cppcms::base_content{
        std::string title = "Phoenix";
        std::string welcome_text = "Phoenix -- современнный сервис для создания заметок. Основная идея сервиса заключается в упрощении возможности делиться заметками, как между зарегестрированными, там и обычными пользователями";
        std::string hello_user_text = "Hello, user"; //по default --user, будет реализована смена на никнейм юзера по сессии
        std::string new_text_title = "Обновление 1.3";
        std::string new_text = "Добавлена возможность работы с файлами \n Добавлена возожность отслеживания даты создания заметки";
        std::string reg_button_name{"РЕГИСТРАЦИЯ"};

        example examples;
        search_area search;

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

