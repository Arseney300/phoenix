#ifndef begin_h
#define begin_h
#include <cppcms/view.h>
#include <string>
#include <cppcms/form.h>
#endif
namespace contacts_content{
     struct Left_title{
        std::string main_title = "PHOENIX";
        std::string first_button_name = "news";
        std::string second_button_name = "contacts";
        std::string third_button_name = "source code";
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

    struct Account{
            std::string account_name{"PHOENIX"};//default
    };
    

    struct Person{
        public:
        std::string name;
        std::string info;
        std::string mail;
    };

    struct content: public cppcms::base_content{
        std::string title {"Contacts"};
        Left_title left_title;  
        search_area search;
        Account account;
        Person person_1, person_2,person_3;
        
        content(){
            person_1.name = "Мещеряков Арсений";
            person_1.info = "back-end часть и сайт";
            person_1.mail = "Arseney300@gmail.com";

            person_2.name="Солодкин Михаил";
            person_2.info = "Разработка android приложения";
            person_2.mail = "JIaIILLIa3@yandex.ru";

            person_3.name = "Муль Павел";
            person_3.info = "Предоставление сервера на базе ИЛ НГТУ";
            person_3.mail = "paulmy@yandex.ru";
        }
    };

}

