#line 1 "tmpl/reset_password.tmpl"
#include "reset_password.h"
#line 2 "tmpl/reset_password.tmpl"
namespace my_skin {
	#line 3 "tmpl/reset_password.tmpl"
	struct  reset_password_view :public cppcms::base_view
	#line 3 "tmpl/reset_password.tmpl"
	{
	#line 3 "tmpl/reset_password.tmpl"
		reset_password_content::content &content;
	#line 3 "tmpl/reset_password.tmpl"
		reset_password_view(std::ostream &_s,reset_password_content::content &_content): cppcms::base_view(_s),content(_content),_domain_id(0)
	#line 3 "tmpl/reset_password.tmpl"
		{
	#line 3 "tmpl/reset_password.tmpl"
			_domain_id=booster::locale::ios_info::get(_s).domain_id();
	#line 3 "tmpl/reset_password.tmpl"
		}
		#line 4 "tmpl/reset_password.tmpl"
		virtual void render() {
		#line 4 "tmpl/reset_password.tmpl"
			cppcms::translation_domain_scope _trs(out(),_domain_id);

			#line 15 "tmpl/reset_password.tmpl"
			out()<<"\n"
				"\n"
				"<!DOCTYPE html>\n"
				"<html lang=\"en\">\n"
				"<head>\n"
				"\t<meta charset=\"UTF-8\">\n"
				"\t<title>change password</title>\n"
				"\t  <script type=\"text/javascript\" src=\"js/jquery-3.3.1.min.js\"></script>\n"
				"</head>\n"
				"<body>\n"
				"    <form method=\"post\" action=\"\" enctype=\"multipart/form-data\">\n"
				"\t";
			#line 15 "tmpl/reset_password.tmpl"
			{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html,cppcms::form_flags::as_p); (content.form).render(_form_context); }
			#line 23 "tmpl/reset_password.tmpl"
			out()<<"\n"
				"    </form>\n"
				"\n"
				"</body>\n"
				"</html>\n"
				"\n"
				"\n"
				"\n"
				"";
		#line 23 "tmpl/reset_password.tmpl"
		} // end of template render
	#line 25 "tmpl/reset_password.tmpl"
	private:
	#line 25 "tmpl/reset_password.tmpl"
		int _domain_id;
	#line 25 "tmpl/reset_password.tmpl"
	}; // end of class reset_password_view
#line 26 "tmpl/reset_password.tmpl"
} // end of namespace my_skin
#line 2 "tmpl/reset_password.tmpl"
namespace my_skin {
#line 26 "tmpl/reset_password.tmpl"
} // end of namespace my_skin
#line 26 "tmpl/reset_password.tmpl"
namespace {
#line 26 "tmpl/reset_password.tmpl"
 cppcms::views::generator my_generator; 
#line 26 "tmpl/reset_password.tmpl"
 struct loader { 
#line 26 "tmpl/reset_password.tmpl"
  loader() { 
#line 26 "tmpl/reset_password.tmpl"
   my_generator.name("my_skin");
#line 26 "tmpl/reset_password.tmpl"
   my_generator.add_view<my_skin::reset_password_view,reset_password_content::content>("reset_password_view",true);
#line 26 "tmpl/reset_password.tmpl"
    cppcms::views::pool::instance().add(my_generator);
#line 26 "tmpl/reset_password.tmpl"
 }
#line 26 "tmpl/reset_password.tmpl"
 ~loader() {  cppcms::views::pool::instance().remove(my_generator); }
#line 26 "tmpl/reset_password.tmpl"
} a_loader;
#line 26 "tmpl/reset_password.tmpl"
} // anon 
