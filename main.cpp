/**
 * Main code with core
 * update....
 * 
*/


//cppcms headers:
#include <cppcms/application.h>  
#include <cppcms/applications_pool.h>  
#include <cppcms/service.h>  
#include <cppcms/http_response.h>  
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/applications_pool.h>
#include <cppdb/frontend.h>
#include <cppcms/http_file.h>
//!cppcms headers

//c++ headers:
#include <iostream> 
#include <string> 
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <utility>
//!c++ headers

//utist
#include "utils/utils.h"
#include "utils/log.hpp"
#include "utils/docker.hpp"
//!utils

//include boost
#include "utils/boost_include.hpp"
//!include boost

// include tmpl:
#include "pages/main_window/main_window.h"
#include "pages/note_page/note_page.h"
#include "pages/user/user.h"
#include "pages/reset_password/reset_password.h"
#include "pages/contacts/contacts.h"
#include "pages/news/news.h"
#include "pages/quick_note/quick_note.h"
// end tmpl



//main phoenix application
class phoenix_main_application: public cppcms::application {  
private:
    //main sql_session:
    //cppdb::session sql;
    //password file:
    std::ifstream pass_file;
    //db init string:
    std::string db_data;
    //reset_password_list;
    std::map<std::string,std::string> reset_password_list;
    //user_files_directory:
    std::filesystem::path user_files_directory{"./data/user_files/"};
    //mait_loger:
    loger main_loger{};
    
public:  
    phoenix_main_application(cppcms::service &srv) :  
        cppcms::application(srv)  
    { 
    //init pass file
    try{
        pass_file.open("./data/passwords.pass");
    }
    catch(std::exception&e){
        std::cout << e.what();
    }
    if(!pass_file.is_open()){
        std::cout << "problems with pass_file";
    }
    //!init fiss_file

    //init sql
    //sql -- first line
    //std::string db_data;
    pass_file >> this->db_data;
    //sql = cppdb::session(db_data);
    //!init sql
    //default page (main_window)
    dispatcher().assign("",&phoenix_main_application::main_window,this);
    dispatcher().assign("/",&phoenix_main_application::main_window,this);
    mapper().assign("");
    //!default page
    
    //news page
    dispatcher().assign("/news",&phoenix_main_application::news, this);
    mapper().assign("news","/news");
    //!news page

    //contacts
    dispatcher().assign("/contacts",&phoenix_main_application::contacts,this);
    mapper().assign("contacts","/contacts");
    //!contacts

    //note page
    dispatcher().assign("/note/(\\S+)",&phoenix_main_application::note,this,1); //render:note_page_view
    mapper().assign("note","/note/(\\S+)");
    //!note page

    //user page
    dispatcher().assign("/user",&phoenix_main_application::user, this);
    mapper().assign("user","/user");
    dispatcher().assign("/user/change_password",&phoenix_main_application::user_change_password,this);
    mapper().assign("change_password","/user/change_password");
    //!user page

    //create_quick_note page
    dispatcher().assign("/quick_note", &phoenix_main_application::create_quick_note_page,this);
    mapper().assign("quick_note","/quick_note");
    //!create_quick_note page

    //user_work requestes
    dispatcher().assign("/post/create_user",&phoenix_main_application::create_user_post,this);
    mapper().assign("create_user","/post/create/user");

    dispatcher().assign("/post/login_user",&phoenix_main_application::login_user,this);
    mapper().assign("login_user","/post/login_user");

    dispatcher().assign("/reset_password/(\\S+)",&phoenix_main_application::reset_password_page,this,1);
    mapper().assign("reset_password_page","/reset_password/(\\S+)");

    dispatcher().assign("/post/create_user_session",&phoenix_main_application::create_user_session,this);
    mapper().assign("create_user_session","/post/create_user_session");

    dispatcher().assign("/get/delete_user_session",&phoenix_main_application::delete_user_session, this);
    mapper().assign("delete_user_session","/get/delete_user_session");

    dispatcher().assign("/post/reset_password",&phoenix_main_application::reset_password,this);
    mapper().assign("reset_password","/post/reset_password");

    dispatcher().assign("/post/change_password",&phoenix_main_application::change_password,this);
    mapper().assign("change_password","/post/change_password");

    dispatcher().assign("/get/delete_user",&phoenix_main_application::delete_user,this);
    mapper().assign("delete_user","/get/delete_user");

    dispatcher().assign("/get/get_name",&phoenix_main_application::get_name,this); //return name of user_id
    mapper().assign("get_name","/get/get_name");

    dispatcher().assign("/get/get_id",&phoenix_main_application::get_id,this); //return user_id, if user have session
    mapper().assign("get_id","/get/get_id");
    //!user_work requestes



    //quick_note
    dispatcher().assign("/post/create_quick_note", &phoenix_main_application::create_quick_note,this);
    mapper().assign("create_quick_note","/post/create_quick_note");

    dispatcher().assign("/post/update_quick_note",&phoenix_main_application::update_quick_note,this);
    mapper().assign("update_quick_note","/post/update_quick_note");

    dispatcher().assign("/post/share_note",&phoenix_main_application::share_note,this);
    mapper().assign("share_note","/post/share_note");

    dispatcher().assign("/get/get_quick_note",&phoenix_main_application::get_quick_note,this);
    mapper().assign("get_quick_note","/get/get_quick_note");

    dispatcher().assign("/get/delete_quick_note", &phoenix_main_application::delete_quick_note, this);
    mapper().assign("delete_quick_note","/get/delete_quick_note");
    //!quick_note

    //user_note
    dispatcher().assign("/post/create_note", &phoenix_main_application::create_note, this);
    mapper().assign("create_note","/post/create_note");
    
    dispatcher().assign("/post/update_note",&phoenix_main_application::update_note,this);
    mapper().assign("update_note","/post/update_note");

    dispatcher().assign("/get/delete_user_note",&phoenix_main_application::delete_user_note, this);
    mapper().assign("delete_user_note","/get/delete_user_note");

    dispatcher().assign("/get/get_user_note",&phoenix_main_application::get_user_note,this);
    mapper().assign("get_note","/get/get_user_note");

    dispatcher().assign("/get/get_notes_id",&phoenix_main_application::get_notes_id,this); //return all id of user_notes of user
    mapper().assign("get_notes_id","/get/get_notes_id");
    //!user_note

    //files
    dispatcher().assign("/post/new_file",&phoenix_main_application::new_file, this);
    mapper().assign("new_file","/post/new_file");

    dispatcher().assign("/get/check_file_exist", &phoenix_main_application::check_file_exist, this);
    mapper().assign("check_file_exist","/get/check_file_exist");

    dispatcher().assign("/get/download_file",&phoenix_main_application::download_file,this)    ;
    mapper().assign("download_file","/get/download_file");

    //!files



    dispatcher().assign("/post/compile",&phoenix_main_application::compile,this);
    mapper().assign("compile","/post/compile");


    //???????
    dispatcher().assign("/post/new_file",&phoenix_main_application::new_file,this);
    mapper().assign("new_file","/post/new_file");
    //?????


    
    
    dispatcher().assign("/get/test_id_user_note",&phoenix_main_application::test_id_user_note,this); //???????????
    mapper().assign("test_id_user_note","/get/test/id/user/note");

     
    
   
    mapper().root("/"); 

    }  

    void main_window(){
        this->main_loger.open_file();
        this->main_loger.write("main_window_render");
        this->main_loger.close_file();
        main_window_content::content c;
        //init examples:
        c.examples.names.push_back("Создание заметки:");
        c.examples.names.push_back("Создание пользователя:");
        c.examples.names.push_back("id заметки:");
        //нужно добавть картинки !!!!
        if(session().is_set("logged") && session().get("logged") == "1"){
            this->user();
            return;
        }
        if(session().is_set("logged") && session().get("logged") == "1")
            c.account.account_name == session().get("name");
        /*if (request().request_method() == "POST"){ 
            c.qn_form.load(context());
            if (c.qn_form.validate()){
                std::cout << c.qn_form.textarea.value() << std::endl;
                c.quick_note.data = c.qn_form.textarea.value();
            
            }
            c.qn_form.clear();
        }*/
        render("main_window",c); 
    }


    void note(std::string id){
        note_page_content::content c;
        if (request().request_method() == "GET"){
            if(session().is_set("logged") and session().get("logged") == "1"){
                //добавить в этот режим поиск по user notes
                cppdb::session sql{this->db_data};
                std::string local_id = 'q' + id;
                cppdb::result res =   sql << "select text from quick_notes where local_id = ?" << local_id << cppdb::row;
                if (!res.empty()){
                    std::string text;
                    res.fetch(0,text);
                    c.title = id;
                    c.local_id = id;
                    c.text = text;
                    render("note_page_session_view",c);
                }
                else{
                    //произвести поиск в расшаренных заметках 
                    std::string s = "share";
                    res = sql << "select text from notes where local_id = ? and prop = ?" << 'n' +id<< s << cppdb::row;
                    if (!res.empty()){
                        std::string text;
                        res.fetch(0,text);
                        c.title = id;
                        c.local_id = id;
                        c.text = text;
                        render("note_page_session_view",c);
                    }
                    else{
                        c.title = "phoenix note";
                        c.local_id = id;
                        c.text = "Такая заметка не существует";
                        render("note_page_session_view",c);
                    }
                }
            }
            else{
                cppdb::session sql{this->db_data};
                std::string local_id = 'q' + id;
                cppdb::result res =   sql << "select text from quick_notes where local_id = ?" << local_id << cppdb::row;
                if (!res.empty()){
                    std::string text;
                    res.fetch(0,text);
                    c.title = id;
                    c.local_id = id;
                    c.text = text;
                    render("note_page_view",c);
                }
                else{
                    //произвести поиск в расшаренных заметках 
                    std::string s = "share";
                    res = sql << "select text from notes where local_id = ? and prop = ?" << 'n' +id<< s << cppdb::row;
                    if (!res.empty()){
                        std::string text;
                        res.fetch(0,text);
                        c.title = id;
                        c.local_id = id;
                        c.text = text;
                        render("note_page_view",c);
                    }
                    else{
                        c.title = "phoenix note";
                        c.local_id = id;
                        c.text = "Такая заметка не существует";
                        render("note_page_view",c);
                    }
                }
            }
        }
    }
    void create_quick_note_page(){
        if(request().request_method() == "POST"){
            if(session().is_set("logged") && session().get("logged") =="1"){
                quick_note_content::content c;
                render("quick_note_session_view",c);
            }
            else{
                quick_note_content::content c;
                render("quick_note_view",c);
            }
        }
    }




    void news(){
        if(request().request_method() == "GET"){
            news_content::content c;
            render("news_view",c);
        }
    }
    void contacts(){
        if(request().request_method() == "GET"){
            contacts_content::content c;
            render("contacts_view",c);
        }
    }


    void get_user_note(){
        if(request().request_method() == "GET"){
            cppdb::session sql{this->db_data};
            std::string user_id = request().get("user_id");
            std::string local_id = 'n'+ request().get("local_id");
            cppdb::result res = sql << "select text from notes where creater_id = ? and local_id = ? " << user_id << local_id << cppdb::row;
            if(!res.empty()){
                std::string text;
                res.fetch(0,text);
                response().out() << text;
            }
            else{
                response().out() << "problems";
            }
        }
    }
    void get_quick_note(){
        if(request().request_method() == "GET"){
            cppdb::session sql{this->db_data};
            std::string local_id = 'q' + request().get("local_id");
            cppdb::result res =   sql << "select text from quick_notes where local_id = ?" << local_id << cppdb::row;
            if (!res.empty()){
                std::string text;
                res.fetch(0,text);
                response().out() << text;
            }
            else{
                //поиск в расшариных заметках
                std::string s = "share";
                res = sql << "select text from notes where local_id = ? and prop = ?" << 'n'+request().get("local_id") << s << cppdb::row;
                std::string text;
                if(!res.empty()){
                    res.fetch(0,text);
                    response().out() << text;
                }
                else{
                    response().out() << "not found";
                }
            }
        }
    }

    void create_quick_note(){
        if(request().request_method() == "GET"){
            response().status(404);
            return;
        }
        if(request().request_method() =="POST"){
            cppdb::session sql{this->db_data};
            std::string local_id = 'q' + create_quick_note_id(5);
            std::string text = request().post("text");
            std::string date = request().post("date");
            sql << "insert into quick_notes(local_id,text,date) values(?,?,?)" << local_id << text  << date << cppdb::exec;
            response().out() << local_id.substr(1);
        }
    }

    bool test_id_note(std::string id){
        cppdb::session sql{this->db_data};
        //id = 'n' + id;
        cppdb::result res = sql << "select exists(select * from notes where local_id = ? )" << id << cppdb::row;
        std::string ans;
        if(!res.empty()){res.fetch(0,ans);}
        if(ans == "0"){
            return true;
        }
        else{
            return false;
        }
    }

    void test_id_user_note(){
        if(request().request_method() == "GET"){
            std::string id = 'n'+ request().get("id");
            if(test_id_note(id)){
                response().out() << "true";
            }
            else{
                response().out() << "false";
            }
        }
    }
    

    

    void create_note(){
        if(request().request_method() == "GET"){
            response().status(404);
            return;
        }
        if(request().request_method() == "POST"){
            //по умолчанию заметка пользователя скрыта ото всех, но потом её можно расшарить, то есть добавить общедоступный id
            /*std::string local_id = "n"+request().post("local_id");
            if(!test_id_note(local_id)){
                response().out() << "id not free";
                return;
            }*/
            cppdb::session sql{this->db_data};
            std::string ret_id = create_quick_note_id(10);// то есть по умолчанию id будет рандомным 
            std::string local_id = 'n' + ret_id;
            std::string creater_name = request().post("creater_id");
            //проверка на пользователя:
            cppdb::result res = sql << "select exists(select * from users where user_id = ? )" << creater_name << cppdb::row;
            std::string ans;
            if(!res.empty()){res.fetch(0,ans);};
            if(ans == "0"){
                response().out() << "user with this id not found";
                return;
            }

            std::string text = request().post("text");
            std::string date = request().post("date");
            sql << "insert into notes(local_id,text,creater_id,date) values(?,?,?,?)" << local_id << text << creater_name << date << cppdb::exec;
            response().out() << ret_id;
        }
    }

    void share_note_f(std::string last_id,std::string new_id){
        cppdb::session sql{this->db_data};
        sql << "update notes set local_id = ? where local_id = ?" << new_id << last_id << cppdb::exec;
        std::string s = "share";
        sql << "update notes set prop = ? where local_id  =? " << s << new_id << cppdb::exec;
    }

    void share_note(){
        if(request().request_method() == "POST"){
            cppdb::session sql{this->db_data};
            std::string user_id =  request().post("user_id");
            std::string last_id = 'n' + request().post("last_id");
            std::string new_id = 'n' + request().post("new_id");
            //проверка на пользователя
            cppdb::result res = sql << "select exists(select * from users where user_id = ?)" << user_id << cppdb::row;
            std::string user_check;
            if(!res.empty()){res.fetch(0,user_check);}
            if(user_check == "0"){
                response().out() << "problems";
                return;
            }
            //проверка на новый id:
            res = sql << "select exists(select * from notes where local_id = ?)" << new_id <<cppdb::row;
            std::string id_check;
            if(!res.empty()){res.fetch(0,id_check);}
            if(id_check != "0"){
                response().out() << "id is not free";
                return;
            }
            share_note_f(last_id,new_id);

        }
    }

    std::string create_user(std::string name,std::string email, std::string pass){
        if (name.empty() || email.empty() || pass.empty() ){
            //return problems
            return "empty data";
        }
        else{
            // i need protect password
	        // i need сделать проверку на то, есть ли такой пользователь
            cppdb::session sql{this->db_data};
            cppdb::result res = sql << "select exists(select * from users  where name = ? )" << name << cppdb::row;
            std::string flag;
            if (!res.empty()){
                res.fetch(0,flag);
            }
            else{
                return ("PROBLEMS");
            }
            if (std::stoi(flag) == 1){ //то есть пользователь с таким именем существует
                return "user with this name exist";
            }
            res = sql<< "select exists(select * from users where email = ? )" << email << cppdb::row;
            if (!res.empty()){
                res.fetch(0,flag);
            }
            else{
                return ("PROBLEMS");
            }
            if (std::stoi(flag) == 1){ //то есть пользователь с таким email существует
                return "user with this email exist";
            }
            std::string id_of_user = create_quick_note_id(15); //создание id для пользователя на 10 символов
            sql << "insert into users(name,email,pass,user_id) values(?,?,?,?)" << name << email << pass << id_of_user<< cppdb::exec;
            return id_of_user;
        }
        
    }
    void create_user_post(){
       if(request().request_method() == "GET"){
            response().status(404);
            return;
        }
        if (request().request_method() == "POST"){
            std::string name = request().post("name");
            std::string email = request().post("email");
            std::string pass = request().post("pass");
            if (name.empty() || email.empty() || pass.empty() ){
                response().out() << "empty data";
            }
            else{
                std::string res = create_user(name,email,pass);
                response().out() << res;
            }
        } 
    }
    void login_user(){
        if (request().request_method() == "GET"){response().status(404);return;}
	    if (request().request_method() == "POST"){
            cppdb::session sql{this->db_data};
	        std::string name = request().post("login");
	        std::string pass = request().post("pass");
            if(name.empty() || pass.empty()){
                response().out() << "empty data";
                return;
            }
            //проверка есть ли пользователь с таким именем или почтой
            cppdb::result res = sql << "select exists(select * from users where name= ? )" << name << cppdb::row;
            cppdb::result res2 = sql << "select exists(select * from users where email =? )" << name/*like email*/ << cppdb::row;
            std::string name_exist, email_exist;
            if(!res.empty()){ res.fetch(0,name_exist);}
            if(!res2.empty()){res2.fetch(0,email_exist);}
            if (std::stoi(name_exist) == 1){
                res = sql << "select pass from users where name = ? " << name  << cppdb::row;
                std::string from_sql_pass;
                if (!res.empty()) {res.fetch(0,from_sql_pass);}
                if (pass == from_sql_pass){
                    //LOGINED // дальше нужно создать сессию и так далее
                    //возвращает id_of_user
                    //response().out() << "LOGINED";
                    res = sql << "select user_id from users where name = ?" << name << cppdb::row;
                    std::string user_id;
                    if(!res.empty()) {res.fetch(0,user_id);}
                    response().out() << user_id;;
                }
                else{
                    response().out() << "user with this name or email not exist";
                }
            }
            else if(std::stoi(email_exist)){
                res = sql << "select pass from users where email = ? " << name << cppdb::row;
                std::string from_sql_pass;
                if(!res.empty()){res.fetch(0,from_sql_pass);}
                if(pass == from_sql_pass){
                    // сессия и так далее
                    // тоже возвращает user_id 
                    res = sql << "select user_id from users where email = ?" << name << cppdb::row;
                    std::string user_id;
                    if(!res.empty()){res.fetch(0,user_id);}
                    response().out() << user_id;
                    //response().out() << "LOGINED";
                }
                else{
                    response().out() << "user with this name or email not exist";
                }
            }
            else{
                response().out() << "user with this name or email not exist";
            }
        }

    }


    void create_user_session(){
        if(request().request_method() == "POST"){
            cppdb::session sql{this->db_data};
            std::string user_id = request().post("user_id");
            //проверка на пользователя:
            cppdb::result res = sql << "select exists(select * from users where user_id = ?)" << user_id << cppdb::row;
            std::string flag;
            if(!res.empty()){res.fetch(0,flag);}
            if(flag=="0"){
                response().out() << "user not found";
                return;
            }

            res  = sql << "select * from users where user_id = ?" << user_id << cppdb::row;
            std::string name,email; //data
            if(!res.empty()){
                res.fetch(1,name);
                res.fetch(2,email);
            }
            
            //create session:
            session()["user_id"] = user_id;
            session()["name"] = name;
            session()["email"] = email;
            session()["logged"] = "1";
            response().out() << "success";
        }
    }
    void delete_user_session(){
        if(session().is_set("logged") && session()["logged"] =="1"){
            session().clear();
        }
    }
    void get_id(){
        if(request().request_method() == "GET"){
            if(session().is_set("logged") and session()["logged"]=="1"){
                response().out() << session()["user_id"];
            }
            else{
                response().out() << "you haven't session";
            }
        }
        

    }

    void user(){
        if (session().is_set("logged") and session()["logged"] == "1"){
            user_content::content c; 
            c.account.account_name = session()["name"];
            c.account.email = session()["email"];
            c.count_of_notes = get_notes_id_f(session().get("user_id")).size();;
            render("user_view",c); 
        }
        else{
            response().set_redirect_header("/");
        }
    }
    void user_change_password(){
        if(request().request_method() == "POST"){
            if(session().is_set("logged") && session()["logged"] == "1"){
                auto user_id = session()["user_id"];
                auto last_pass =  request().post("last_pass");
                auto new_pass_1 = request().post("password_1");
                auto new_pass_2 = request().post("password_2");
                if(new_pass_1 != new_pass_2){
                    response().out() << "password not equal";
                    return;
                }
                cppdb::session sql{this->db_data};
                std::string last_password = last_pass;
                std::string new_password =new_pass_1;

                //проверка на пользователя:
                cppdb::result res = sql << "select exists(select * from users where user_id = ?)" << user_id << cppdb::row;
                std::string ans;
                if(!res.empty()){res.fetch(0,ans);}
                if(ans =="0"){
                    response().out() << "user not found";
                    return;
                }
                std::string user_password;
                res = sql << "select pass from users where user_id = ?" << user_id << cppdb::row;
                if(!res.empty()){
                    res.fetch(0,user_password);
                }
                if(user_password == last_password){
                    if(new_password.length()!=0 and new_password != last_password){
                        sql << "update users set pass = ? where user_id = ?" << new_password << user_id << cppdb::exec;
                        response().out() << "OK";
                    }
                    else{
                        response().out() << "wrong new password";
                        return;
                    }
                }
                else{
                    response().out() << "wrong password";
                    return;
                }

            }
        }
    }

    


    void update_note(){
        if(request().request_method() == "POST"){
            cppdb::session sql{this->db_data};
            std::string local_id = 'n' + request().post("local_id");
            std::string text = request().post("text");
            std::string user_id = request().post("user_id");
            if(local_id.empty()|| user_id.empty()){
                response().out() << "empty data";
                return;
            }
            //проверка существует ли заметка:
            cppdb::result res = sql << "select exists(select * from notes where local_id = ? and creater_id = ?)" << local_id << user_id << cppdb::row;
            std::string flag;
            if(!res.empty()){res.fetch(0,flag);}
            if(flag =="0"){
                response().out() << "problems";
                return;
            }
            sql << "update notes set text = ? where local_id = ?" << text << local_id << cppdb::exec;
            response().out() << "OK";
        }
    }


    void update_quick_note(){
        if (request().request_method() == "POST"){
            cppdb::session sql{this->db_data};
            std::string local_id = 'q' + request().post("local_id");
            std::string text = request().post("text");

            //проверка на то, гда находится данная заметка
            cppdb::result res = sql << "select exists(select * from quick_notes where local_id = ? )" << local_id << cppdb::row;
            std::string flag;
            if(!res.empty()){res.fetch(0,flag);}

            if(flag != "0"){
                sql << "update quick_notes set text = ? where local_id = ?" << text << local_id << cppdb::exec;
                response().out() << "good";
                return;
            }
            std::string s = "share";
            res = sql << "select exists(select * from notes where local_id = ? and prop = ? )" << 'n'+ request().post("local_id") << s << cppdb::row;
            if(!res.empty()){res.fetch(0,flag);}
            if(flag != "0"){
                sql << "update notes set text = ? where local_id = ?" << text << 'n' + request().post("local_id") << cppdb::exec;
                response().out() << "good";
                return;
            }

        }
        else{
            response().out() << "fail";
        }
    }


    void delete_quick_note(){
        if(request().request_method() =="GET"){
            cppdb::session sql{this->db_data};
            std::string local_id = 'q' + request().post("local_id");
            cppdb::result res = sql << "select exists(select * from users where local_id = ?)" << local_id;
            std::string check_note;
            if(!res.empty()){res.fetch(0,check_note);}
            if(check_note == "0"){
                response().out() << "note not found";
                return;
            }
            sql << "delete from quick_notes where local_id = ?" << local_id << cppdb::exec;
        }
    }

    void get_name(){
        if(request().request_method() == "GET"){
            cppdb::session sql{this->db_data};
            std::string id = request().get("id");
            cppdb::result res = sql << "select name from users where user_id = ? " << id << cppdb::row;
            std::string ans;
            if(!res.empty()){
                res.fetch(0,ans);
            }
            else{
                response().out() << "problems";
                return;
            }
            response().out() << ans;
        }
    }


    std::vector<std::string> get_notes_id_f(std::string user_id){
        cppdb::session sql{this->db_data};
        cppdb::result res = sql << "select local_id from notes where creater_id = ?" << user_id;
        std::vector<std::string> ids;
        while(res.next()){
            std::string timed_id;
            res >> timed_id;
            timed_id = timed_id.substr(1);
            ids.push_back(timed_id);
        }
        return ids;
    }


    void get_notes_id(){
        if (request().request_method() == "GET"){
            std::string user_id = request().get("user_id");
            if(user_id.empty())
            {
                response().out() << "empty data";
                return;
            }
            auto ans = get_notes_id_f(user_id);
            for (auto i = ans.begin(); i< ans.end(); i++)
                response().out() << *i << " ";
        }
    }
    
    //delete user
    void delete_user(){
        if(request().request_method() == "GET"){
            cppdb::session sql{this->db_data};
            std::string user_id = request().get("user_id");
            cppdb::result res = sql<<"select exists(select * from users where user_id = ?)" << user_id <<cppdb::row;
            std::string check_user;
            if(!res.empty()){res.fetch(0,check_user);}
            if(check_user =="0"){
                response().out() << "user not found";
                return;
            }
            sql << "delete from users where user_id =?" << user_id << cppdb::row;
            //удалить все файлы, которые принадлежат данному пользователю:
            std::string command = "rm ./data/user_files/"+user_id+"::*";
            system(command.c_str());
        }
    }

    //delete user note
    void delete_user_note(){ 
        if(request().request_method() == "GET"){
            cppdb::session sql{this->db_data};
            std::string user_id = request().get("user_id");
            std::string local_id = 'n' + request().get("local_id");
            cppdb:: result res = sql << "select exists(select * from users where user_id = ?)" << user_id << cppdb::row;
            std::string check_user;
            if(!res.empty()){res.fetch(0,check_user);}
            if(check_user == "0"){
                response().out() << "user not found";
                return;
            }
            sql << "delete from notes where local_id = ?" << local_id << cppdb::exec;
            //удалить файл, которые принадлежит данной заметки, если он вообще существует:
            std::string command = "rm ./data/user_files/"+user_id+"::"+local_id+"::*";
            system(command.c_str());
        }
    }


    void reset_password(){
        if(request().request_method() == "POST"){
            cppdb::session sql{this->db_data};
            std::string name_or_email = request().post("name");
            //exist user:
            cppdb::result res = sql << "select exists(select * from users where name = ? or email =?)" << name_or_email << name_or_email << cppdb::row;
            std::string ans;
            if(!res.empty()){res.fetch(0,ans);}
            if(ans == "0"){
                response().out() << "user not found";
                return;
            }
            std::string email;
            res = sql << "select email from users where name = ? or email =?" << name_or_email << name_or_email << cppdb::row;
            if(!res.empty()){res.fetch(0,email);}

            //do generate URL for reset_password_page

            std::string url = create_quick_note_id(20); //20 simbols
            reset_password_list.insert(std::make_pair(url,email));

            std::string message{"www.phoenixnote.site/reset_password/"+url};
            send_email(email,message);
        }
    }

    void reset_password_page(std::string url){
        if(request().request_method() =="GET"){
            //search in reset_password_list
            auto i = reset_password_list.find(url);
            if(i != reset_password_list.end()){
                reset_password_content::content c;
                render("reset_password_view",c);
            }
            else
                response().status(404);
            
        }
        else if(request().request_method() == "POST"){
            cppdb::session sql{this->db_data};
            reset_password_content::content c;
            c.form.load(context());
            if(c.form.validate()){
                std::string password = c.form.password.value();
                std::string password_again = c.form.password_again.value();
                std::string email;
                auto i = reset_password_list.find(url);
                if(i!= reset_password_list.end()){
                    email = i->second;
                }
                else{
                    response().status(404);
                }
                if(password == password_again){
                    sql << "update users set pass = ? where email =?" << password << email << cppdb::exec;
                    reset_password_list.erase(i);
                }
                else{
                    response().out() << "password not compare";
                    c.form.clear();
                    render("reset_password_view",c);
                }
                
                response().set_redirect_header("/");
            }
            
        }
    }


    void change_password(){
        if(request().request_method() =="POST"){
            cppdb::session sql{this->db_data};
            std::string user_id = request().post("user_id");
            std::string last_password = request().post("last_pass");
            std::string new_password = request().post("new_pass");
            //проверка на пользователя:
            cppdb::result res = sql << "select exists(select * from users where user_id = ?)" << user_id << cppdb::row;
            std::string ans;
            if(!res.empty()){res.fetch(0,ans);}
            if(ans =="0"){
                response().out() << "user not found";
                return;
            }
            std::string user_password;
            res = sql << "select pass from users where user_id = ?" << user_id << cppdb::row;
            if(!res.empty()){
                res.fetch(0,user_password);
            }
            if(user_password == last_password){
                if(new_password.length()!=0 and new_password != last_password)
                    sql << "update users set pass = ? where user_id = ?" << new_password << user_id << cppdb::exec;
                else{
                    response().out() << "wrong new password";
                    return;
                }
            }
            else{
                response().out() << "wrong password";
                return;
            }

        }
    }


    void new_file(){
        std::string dir = "./data/user_files/";
        if(request().request_method() == "GET"){
            response().status(404);
        }
        else if(request().request_method() == "POST"){
            cppdb::session sql{this->db_data};
            auto file = request().files().at(1);
            std::string name_of_file = file->filename();
            std::vector<std::string> split_name_of_file;
            boost::split(split_name_of_file,name_of_file, boost::is_any_of("::"),boost::token_compress_on);
            std::string user_id = split_name_of_file.at(0);
            std::string note_id = split_name_of_file.at(1);
            std::string file_name = split_name_of_file.at(2);
            //дальше нужно такому-то пользователю в его заметку добавить имя  файла, чтобы потом было легче найти её
            
            if(!user_id.empty()){
                //то есть user note (не важно расшаренная или нет)
                note_id = 'n' + note_id;
                sql << "update notes set file = ? where local_id = ? and creater_id = ? " << file_name << note_id << user_id <<  cppdb::exec;
                //нужно реализховать проверку на то, есть ли файл от такой заметки такого пользователя на сервере (формата user_id::note_id::*)
                // и заменить файл, если да
                std::string command = "rm ./data/user_files/" + user_id+ "::" +note_id.substr(1)+"::*";
                system(command.c_str());
                file->save_to(dir+name_of_file);
            }
            else{
                //то есть или расшаренная или quick_note
                //для начала проверка на quick_note:
                cppdb::result res  = sql << "select exists(select * from quick_notes where local_id = ? )" << 'q'+note_id << cppdb::row;
                std::string ans;
                if(!res.empty()){res.fetch(0,ans);}
                if(ans == "1"){
                    //то есть quick_note
                    note_id = 'q' + note_id;
                    sql << "update quick_notes set file = ? where local_id = ?" << file_name << note_id << cppdb::exec;
                    //нужно сделат проверку на то, есть ли файл от такой заметки (format: ::note_id::*)
                    std::string command = "rm ./data/user_files/::"+note_id.substr(1)+"::*";
                    system(command.c_str());
                    file->save_to(dir+name_of_file);
                }
                else{
                    // то есть расшаренная(ну или не существует, хотя такой вариант пока не рассматривается)
                    note_id = 'n' + note_id;
                    sql << "update notes set file = ? where local_id = ? " << file_name << note_id << cppdb::exec;
                    //сделать проверку на то есть ли файо такой заметки (format ::note_id::*)
                    std::string command = "rm ./data/user_files/::"+note_id.substr(1)+"::*";
                    system(command.c_str());
                    file->save_to(dir+name_of_file);
                }
            }
            //переношу файл:
            //file->save_to(dir+name_of_file);

        }
        
    }    
    void check_file_exist(){
        if(request().request_method() == "GET"){
            cppdb::session sql{this->db_data};
            std::string user_id = request().get("user_id");
            std::string note_id ='n'+ request().get("note_id");
            //сейчас файлы смотрятся только в user_note
            cppdb::result res = sql << "select file from notes where local_id = ? and creater_id = ?" << note_id << user_id << cppdb::row;
            std::string name_of_file;
            if(!res.empty()){res.fetch(0,name_of_file);}
            if(!name_of_file.empty()){
                std::string full_name_of_file{user_id + "::" + request().get("note_id") + "::" + name_of_file};
                response().out() << full_name_of_file;
            }
            else{
                response().out() << "false";
            }
        }
    }
    void download_file(){
        if(request().request_method() == "GET"){
            std::string name_of_file = request().get("name");
            std::ifstream file{this->user_files_directory.c_str() + name_of_file};
            response().content_type("application/octet-stream");
            response().out() << file.rdbuf();
        }
        else{
            response().status(500);
        }
    }


    void compile(){
        if(request().request_method() == "POST"){
            cppdb::session sql{this->db_data};
            std::string note_id = 'n' + request().post("note_id");
            std::string input = request().post("input");
            std::string pr_lang = request().post("pr_lang");
            docker_pool docker{pr_lang, note_id};
            cppdb::result res = sql << "select text from notes where local_id = ?" << note_id << cppdb::row;
            std::string text;
            if(!res.empty()){res.fetch(0,text);}
            docker.set_text(text);
            docker.set_input(input);
            std::string output = docker.run_program();
            response().out() << output;
        }
    }

};  


int main(int argc, char ** argv){
    try{
        loger* begin_loger = new loger{};
        cppcms::service srv(argc, argv);
        srv.applications_pool().mount(
            cppcms::applications_factory<phoenix_main_application>()
        );
        begin_loger->write("start phoenix main application");
        begin_loger->close_file();
        srv.run();
        begin_loger->open_file();
        begin_loger->write("end phoenix main application");
        begin_loger->close_file();
    }
    catch(std:: exception &e){
        std::cout << e.what() << std::endl;
    }

}
