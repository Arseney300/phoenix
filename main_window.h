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

    struct content: public cppcms::base_content{
        std::string title;
        std::string welcome_text;
        struct Account{
            std::string account_name;
        }account;

        struct quick_notes{
            std::string data;
        }quick_note;
        quick_note_form qn_form;
    };

}

