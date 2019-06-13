#line 1 "file_test.tmpl"
#include "file_test.h"
#line 2 "file_test.tmpl"
namespace my_skin {
	#line 3 "file_test.tmpl"
	struct  file_test_view :public cppcms::base_view
	#line 3 "file_test.tmpl"
	{
	#line 3 "file_test.tmpl"
		file_test_content::content &content;
	#line 3 "file_test.tmpl"
		file_test_view(std::ostream &_s,file_test_content::content &_content): cppcms::base_view(_s),content(_content),_domain_id(0)
	#line 3 "file_test.tmpl"
		{
	#line 3 "file_test.tmpl"
			_domain_id=booster::locale::ios_info::get(_s).domain_id();
	#line 3 "file_test.tmpl"
		}
		#line 4 "file_test.tmpl"
		virtual void render() {
		#line 4 "file_test.tmpl"
			cppcms::translation_domain_scope _trs(out(),_domain_id);

			#line 14 "file_test.tmpl"
			out()<<"\n"
				"\n"
				"<!DOCTYPE html>\n"
				"<html lang=\"en\">\n"
				"<head>\n"
				"\t<meta charset=\"UTF-8\">\n"
				"\t<title>Title</title>\n"
				"</head>\n"
				"<body>\n"
				"    <form method=\"post\" action=\"\" enctype=\"multipart/form-data\">\n"
				"\t";
			#line 14 "file_test.tmpl"
			{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html,cppcms::form_flags::as_p); (content.form).render(_form_context); }
			#line 22 "file_test.tmpl"
			out()<<"\n"
				"    </form>\n"
				"\n"
				"</body>\n"
				"</html>\n"
				"\n"
				"\n"
				"\n"
				"";
		#line 22 "file_test.tmpl"
		} // end of template render
	#line 24 "file_test.tmpl"
	private:
	#line 24 "file_test.tmpl"
		int _domain_id;
	#line 24 "file_test.tmpl"
	}; // end of class file_test_view
#line 25 "file_test.tmpl"
} // end of namespace my_skin
#line 2 "file_test.tmpl"
namespace my_skin {
#line 25 "file_test.tmpl"
} // end of namespace my_skin
#line 25 "file_test.tmpl"
namespace {
#line 25 "file_test.tmpl"
 cppcms::views::generator my_generator; 
#line 25 "file_test.tmpl"
 struct loader { 
#line 25 "file_test.tmpl"
  loader() { 
#line 25 "file_test.tmpl"
   my_generator.name("my_skin");
#line 25 "file_test.tmpl"
   my_generator.add_view<my_skin::file_test_view,file_test_content::content>("file_test_view",true);
#line 25 "file_test.tmpl"
    cppcms::views::pool::instance().add(my_generator);
#line 25 "file_test.tmpl"
 }
#line 25 "file_test.tmpl"
 ~loader() {  cppcms::views::pool::instance().remove(my_generator); }
#line 25 "file_test.tmpl"
} a_loader;
#line 25 "file_test.tmpl"
} // anon 
