
LIB_FLAGS = -lcppcms -lcppdb -lbooster 
TMPL_SOURCE= main_window.tmpl user.tmpl note_page.tmpl
TMPL_CPP = $(TMPL_SOURCE:.tmpl=.cpp) main.cpp
TMPL_OBJECTS = $(TMPL_CPP:.cpp=.o)
all:hello


hello: TMPL_OBJECTS
	g++ -std=c++17  $(TMPL_OBJECTS) $(LIB_FLAGS) -o hello
TMPL_OBJECTS: TMPL_CPP
	g++ -c  $(TMPL_CPP)
TMPL_CPP:
	#timed:
	cppcms_tmpl_cc  tmpl/main_window.tmpl -o main_window.cpp
	cppcms_tmpl_cc tmpl/user.tmpl -o user.cpp
	cppcms_tmpl_cc tmpl/note_page.tmpl -o note_page.cpp


	

