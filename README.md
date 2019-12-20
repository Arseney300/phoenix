# phoenix
Phoenix note


PHOENIX NOTE is modern note-creating service.  
The main idea of service is simpify the ability of sharing notes,both between registered users and regular users.  

This is implemented by an special ID,which assigned to every notes in service.  
Such as, if you need to quickly send a text or file, you can create "quick note", and send only 5-8 simbols ID.  
If you don't like unclear ID and want to create your self identificator, you can registrate in service and create any free ID, size of ID and kind of simbols  -- not limited.  


# Server side: 
Creating with using cppcms framework [GitHub Pages](https://github.com/artyom-beilis/cppcms)

Dependencies:  
cppcms(1.2.0 and newer)    
cppdb(1.0.0 and newer)  
boost  
mariadb:  
  mariadb-dev*   
  mariadb-server  
g++ with c++17 

install and run:  
```
git clone https://github.com/Arseney300/phoenix.git  
cd phoenix  
make  
./phoenix -c config.json 
```


