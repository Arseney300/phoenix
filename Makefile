
LIB_FLAGS = -lcppcms -lcppdb -lbooster 
TMPL_SOURCE= main_window.tmpl user.tmpl note_page.tmpl reset_password.tmpl contacts.tmpl news.tmpl quick_note.tmpl user_note.tmpl notes.tmpl
TMPL_CPP = $(TMPL_SOURCE:.tmpl=.cpp) 
TMPL_OBJECTS = $(TMPL_CPP:.cpp=.o) $(MAIN_FILES:.cpp=.o)
MAIN_FILES = main.cpp
all:hello


hello: TMPL_OBJECTS
	g++-9 -std=c++17 -O2 $(TMPL_OBJECTS) $(LIB_FLAGS) -o phoenix.out
	rm *.o
TMPL_OBJECTS: TMPL_CPP
	g++-9 -c  -std=c++17 -O2   $(addprefix pages/,$(TMPL_CPP)) $(MAIN_FILES)
	rm pages/*.cpp
TMPL_CPP:
	cppcms_tmpl_cc  tmpl/main_window.tmpl -o pages/main_window.cpp
	cppcms_tmpl_cc tmpl/user.tmpl -o pages/user.cpp
	cppcms_tmpl_cc tmpl/note_page.tmpl -o pages/note_page.cpp
	cppcms_tmpl_cc tmpl/reset_password.tmpl -o pages/reset_password.cpp
	cppcms_tmpl_cc tmpl/contacts.tmpl -o pages/contacts.cpp
	cppcms_tmpl_cc tmpl/news.tmpl -o pages/news.cpp
	cppcms_tmpl_cc tmpl/quick_note.tmpl -o pages/quick_note.cpp
	cppcms_tmpl_cc tmpl/user_note.tmpl -o pages/user_note.cpp
	cppcms_tmpl_cc tmpl/notes.tmpl -o pages/notes.cpp

