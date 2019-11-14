
LIB_FLAGS = -lcppcms -lcppdb -lbooster
TMPL_SOURCE= main_window.tmpl user.tmpl note_page.tmpl reset_password.tmpl
TMPL_CPP = $(TMPL_SOURCE:.tmpl=.cpp) 
TMPL_OBJECTS = $(TMPL_CPP:.cpp=.o) $(MAIN_FILES:.cpp=.o)
MAIN_FILES = main.cpp
all:hello


hello: TMPL_OBJECTS
	g++ -std=c++17  $(TMPL_OBJECTS) $(LIB_FLAGS) -o phoenix
	rm *.o
TMPL_OBJECTS: TMPL_CPP
	g++ -c  -std=c++17  $(addprefix pages/,$(TMPL_CPP)) $(MAIN_FILES)
	rm pages/*.cpp
TMPL_CPP:
	#timed:
	cppcms_tmpl_cc  tmpl/main_window.tmpl -o pages/main_window.cpp
	cppcms_tmpl_cc tmpl/user.tmpl -o pages/user.cpp
	cppcms_tmpl_cc tmpl/note_page.tmpl -o pages/note_page.cpp
	cppcms_tmpl_cc tmpl/reset_password.tmpl -o pages/reset_password.cpp

	

