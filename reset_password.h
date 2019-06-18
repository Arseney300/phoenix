#ifndef begin_h
#define begin_h
#include <cppcms/view.h>
#include <string>
#include <cppcms/form.h>
#endif
namespace reset_password_content{

    struct input_form: public cppcms::form{
        cppcms::widgets::text password,password_again;
        cppcms::widgets::submit button;
        input_form(){
            password.name("first_password");
            password_again.name("second_password");
            button.name("main_button");
            add(password);
            add(password_again);
            add(button);
        }
    };

    struct content: public cppcms::base_content{
        input_form form;
    };

}

