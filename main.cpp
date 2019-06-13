#include <cppcms/application.h>  
#include <cppcms/applications_pool.h>  
#include <cppcms/service.h>  
#include <cppcms/http_response.h>  
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/applications_pool.h>
#include <cppdb/frontend.h>
#include <cppcms/http_file.h>
#include <iostream> 
#include <string> 
#include <vector>
#include <fstream>


#include "utils.h"

// include tmpl:
#include "main_window.h"
#include "note_page.h"
#include "user.h"
#include "file_test.h"
// end tmpl



class hello : public cppcms::application {  
public:  
    
    hello(cppcms::service &srv) :  
        cppcms::application(srv)  
    { 
    dispatcher().assign("",&hello::main_window,this);
    dispatcher().assign("/",&hello::main_window,this);
    mapper().assign("");

    dispatcher().assign("/test_file",&hello::test_file,this);
    mapper().assign("file_test","/test_file");

    
    dispatcher().assign("/note/(\\S+)",&hello::note,this,1);
    mapper().assign("note","/note/(\\S+)");

    dispatcher().assign("/note_page",&hello::note_page,this);
    mapper().assign("note_page","/note_page");


    dispatcher().assign("/user",&hello::user, this);
    mapper().assign("user","/user");


    dispatcher().assign("/post/create_user",&hello::create_user_post,this);
    mapper().assign("create_user","/post/create/user");

    dispatcher().assign("/post/login_user",&hello::login_user,this);
    mapper().assign("login_user","/post/login_user");
 

    dispatcher().assign("/post/create_note", &hello::create_note, this);
    mapper().assign("create_note","/post/create_note");
    dispatcher().assign("/post/create_quick_note", &hello::create_quick_note,this);
    mapper().assign("create_quick_note","/post/create_quick_note");
    dispatcher().assign("/post/update_quick_note",&hello::update_quick_note,this);
    mapper().assign("update_quick_note","/post/update_quick_note");
    dispatcher().assign("/post/create_user_session",&hello::create_user_session,this);
    mapper().assign("create_user_session","/post/create_user_session");
    dispatcher().assign("/post/share_note",&hello::share_note,this);
    mapper().assign("share_note","/post/share_note");
    dispatcher().assign("/post/update_note",&hello::update_note,this);
    mapper().assign("update_note","/post/update_note");

    dispatcher().assign("/get/get_note",&hello::get_note,this);
    mapper().assign("get_note","/get/get_note");
    dispatcher().assign("/get/get_quick_note",&hello::get_quick_note,this);
    mapper().assign("get_quick_note","/get/get_quick_note");
    dispatcher().assign("/get/test_id_user_note",&hello::test_id_user_note,this);
    mapper().assign("test_id_user_note","/get/test/id/user/note");
    dispatcher().assign("/get/get_id",&hello::get_id,this);
    mapper().assign("get_id","/get/get_id");
    dispatcher().assign("/get/get_name",&hello::get_name,this);
    mapper().assign("get_name","/get/get_name");
    dispatcher().assign("/get/get_notes_id",&hello::get_notes_id,this);
    mapper().assign("get_notes_id","/get/get_notes_id");
    dispatcher().assign("/get/delete_note",&hello::delete_note, this);
    mapper().assign("delete_note","/get/delete_note");

    std::cout << "init -------------------------" << std::endl;
    
    
    mapper().root("/");

    }  

    void test_file(){
        if(request().request_method() == "GET"){
            file_test_content::content c;
            render("file_test_view",c);
        }
        else if (request().request_method() == "POST"){
            file_test_content::content c;
            c.form.load(context());
            
            if(c.form.validate()){
                std::string text = c.form.text.value();
                std::cout << text << std::endl;
                //c.form.file.load(context());
                auto file_name = (*c.form.file.value()).filename(); //c.form.file.value()->filename()
                c.form.file.value()->save_to(file_name);
                
            }
            c.form.clear();
            render("file_test_view",c);
        }
        
    }    


    void main_window(){
        main_window_content::content c;
        c.title ="oahuth";  //timed
        c.welcome_text = "toaehusnt"; //timed
        c.account.account_name = "Arseney";   //timed
        if (request().request_method() == "POST"){ //какая-то дичь
            c.qn_form.load(context());
            if (c.qn_form.validate()){
                std::cout << c.qn_form.textarea.value() << std::endl;
                c.quick_note.data = c.qn_form.textarea.value();
            
            }
            c.qn_form.clear();
        }
        render("phoenix_view",c); 
    }


    void note(std::string id){
        note_page_content::content c;
        if (request().request_method() == "GET"){
            //std::string local_id = 'q' + request().get("note");
            std::string local_id = 'q' + id;
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
            cppdb::result res =   sql << "select text from quick_notes where local_id = ?" << local_id << cppdb::row;
            if (!res.empty()){
                std::string text;
                res.fetch(0,text);
                //response().out() << text;
                c.local_id = id;
                c.text = text;
                render("note_page_view",c);
            }
            else{
                //response().out() << "problems";
                //написать что такая заметка отсутсвует
                //c.local_id = "Такая заметка не существует";
                //c.text = "";
                //render("note_page_view",c);


                //произвести поиск в расшаренных заметках 
                std::string s = "share";
                res = sql << "select text from notes where local_id = ? and prop = ?" << 'n' +id<< s << cppdb::row;
                if (!res.empty()){
                    std::string text;
                    res.fetch(0,text);
                    c.local_id = id;
                    c.text = text;
                    render("note_page_view",c);
                }
                else{
                    c.local_id = "Такая заметка не существует";
                    c.text = "";
                    //response().set_redirect_header("../note_not_exist.html");
                    render("note_page_view",c);
		}
            }
        }
    }


    void note_page(){
        note_page_content::content c;
        if (request().request_method() == "GET"){
            std::string local_id = 'q' + request().get("note");
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
            cppdb::result res =   sql << "select text from quick_notes where local_id = ?" << local_id << cppdb::row;
            if (!res.empty()){
                std::string text;
                res.fetch(0,text);
                //response().out() << text;
                c.local_id = request().get("note");
                c.text = text;
                render("note_page_view",c);
            }
            else{
                //response().out() << "problems";
                //написать что такая заметка отсутсвует
                //c.local_id = "Такая заметка не существует";
                //c.text = "";
                //render("note_page_view",c);


                //произвести поиск в расшаренных заметках 
                std::string s = "share";
                res = sql << "select text from notes where local_id = ? and prop = ?" << 'n' + request().get("note") << s << cppdb::row;
                if (!res.empty()){
                    std::string text;
                    res.fetch(0,text);
                    c.local_id = request().get("note");
                    c.text = text;
                    render("note_page_view",c);
                }
                else
                    response().set_redirect_header("./note_not_exist.html");
            }
        }
    }


    void get_note(){
        if(request().request_method() == "GET"){
            std::string user_id = request().get("user_id");
            std::string local_id = 'n'+ request().get("local_id");
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
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
            std::string local_id = 'q' + request().get("local_id");
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
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
            //std::string local_id = "q" + request().post("local_id");
            std::string local_id = 'q' + create_quick_note_id(10);
            std::string text = request().post("text");
            std::string date = request().post("date");
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
            sql << "insert into quick_notes(local_id,text,date) values(?,?,?)" << local_id << text  << date << cppdb::exec;
            response().out() << local_id.substr(1);
        }
    }

    bool test_id_note(std::string id){
        //id = 'n' + id;
        cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
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
            std::string ret_id = create_quick_note_id(10);// то есть по умолчанию id будет рандомным 
            std::string local_id = 'n' + ret_id;
            std::string creater_name = request().post("creater_id");
            //проверка на пользователя:
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
            cppdb::result res = sql << "select exists(select * from users where user_id = ? )" << creater_name << cppdb::row;
            std::string ans;
            if(!res.empty()){res.fetch(0,ans);};
            if(ans == "0"){
                response().out() << "user with this id not found";
                return;
            }

            std::string text = request().post("text");
            std::string date = request().post("date");
            //cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
            sql << "insert into notes(local_id,text,creater_id,date) values(?,?,?,?)" << local_id << text << creater_name << date << cppdb::exec;
            response().out() << ret_id;
        }
    }

    void share_note_f(std::string last_id,std::string new_id){
        cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
        sql << "update notes set local_id = ? where local_id = ?" << new_id << last_id << cppdb::exec;
        std::string s = "share";
        sql << "update notes set prop = ? where local_id  =? " << s << new_id << cppdb::exec;
    }

    void share_note(){
        if(request().request_method() == "POST"){
            std::string user_id =  request().post("user_id");
            std::string last_id = 'n' + request().post("last_id");
            std::string new_id = 'n' + request().post("new_id");
            //проверка на пользователя
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
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
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");

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
	        std::string name = request().post("login");
	        std::string pass = request().post("pass");
            if(name.empty() || pass.empty()){
                response().out() << "empty data";
                return;
            }
            //проверка есть ли пользователь с таким именем или почтой
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
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
            std::string user_id = request().post("user_id");
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
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
            render("user_view",c); 
        }
        else{
            response().set_redirect_header("/hello/");
        }
    }
   
    void update_note(){
        if(request().request_method() == "POST"){
            std::string local_id = 'n' + request().post("local_id");
            std::string text = request().post("text");
            std::string user_id = request().post("user_id");
            if(local_id.empty()|| user_id.empty()){
                response().out() << "empty data";
                return;
            }
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
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
            std::string local_id = 'q' + request().post("local_id");
            std::string text = request().post("text");
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");

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

 

    void get_name(){
        if(request().request_method() == "GET"){
            std::string id = request().get("id");
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
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
        cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
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
    
  

    void delete_note(){
        if(request().request_method() == "GET"){
            std::string user_id = request().get("user_id");
            std::string local_id = 'n' + request().get("local_id");
            cppdb::session sql("mysql:database=phoenix;user=tester;password=123456789");
            cppdb:: result res = sql << "select exists(select * from users where user_id = ?)" << user_id << cppdb::row;
            std::string check_user;
            if(!res.empty()){res.fetch(0,check_user);}
            if(check_user == "0"){
                response().out() << "user not found";
                return;
            }
            sql << "delete from notes where local_id = ?" << local_id << cppdb::exec;

        }
    }

   
  
};  




/*void hello::main(std::string url){
    //response().out() << "<h1> Hello World </h1>";

    content::message c;
    c.text = ">>>HELLO<<<<";
    render("message",c);

    std::cout << url << std::endl;
}*/


int main(int argc, char ** argv){
    try{
        cppcms::service srv(argc, argv);
        srv.applications_pool().mount(
            cppcms::applications_factory<hello>()
        );
        std::cout << "start init---------------------" << std::endl;
        srv.run();
        std::cout << "end init-----------------------------" << std::endl;
    }
    catch(std:: exception &e){
        std::cout << e.what() << std::endl;
    }

}