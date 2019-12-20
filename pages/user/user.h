#ifndef begin_h
#define begin_h
#include <cppcms/view.h>
#include <string>
#include <cppcms/form.h>
#endif
namespace user_content{

    // struct quick_note_form: public cppcms::form{
    //     cppcms::widgets::textarea textarea;
    //     quick_note_form(){
    //         textarea.name("QuickNoteTextArea");
    //         add(textarea);
    //     }
    // };



struct Left_title{
        std::string main_title = "PHOENIX";
        std::string first_button_name = "news";
        std::string second_button_name = "contacts";
        std::string third_button_name = "source code";
    };


    struct content: public cppcms::base_content{
        std::string title;
        std::string welcome_text;

        struct Account{
            std::string account_name;
            std::string email;
        }account;
        Left_title left_title;
        // struct quick_notes{
        //     std::string data;
        // }quick_note;
        // quick_note_form qn_form;
    };

}

