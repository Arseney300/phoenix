#ifndef begin_h
#define begin_h
#include <cppcms/view.h>
#include <string>
#include <cppcms/form.h>
#endif
namespace file_test_content{

    struct file_form: public cppcms::form{
        cppcms::widgets::file file;
        cppcms::widgets::textarea text;
        cppcms::widgets::submit button;
        file_form(){
            text.name("textarea");
            file.name("file");
            //file.non_empty();
            //file.limits(0,100*1024);
            //file.add_valid_magic("\x89\x50\x4e\x47\x0D\x0A\x1A\x0A");
            button.name("my_button");
            add(file);
            add(text);
            add(button);
        }
    };

    struct content: public cppcms::base_content{
        file_form form;
    };

}

