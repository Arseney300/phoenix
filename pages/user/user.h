#ifndef begin_h
#define begin_h
#include <cppcms/view.h>
#include <string>
#include <cppcms/form.h>
#endif
namespace user_content{




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

    struct content: public cppcms::base_content{
        std::string title{"phoenix note"};
        uint count_of_notes{0};
        struct Account{
            std::string account_name;
            std::string email;
        }account;
        Left_title left_title;
        search_area search;
    };

}

