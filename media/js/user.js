id_mas = []; //в нем содеражатся все id заметок
note_open = false;
//первичная инициализация:
jQuery(document).ready(function($) {
  $("#create_note_card").hide();
});
//получаем user_id:
jQuery(document).ready(function($) {
  $.get('http://phoenixnote.site/get/get_id', function(data) {
    /*optional stuff to do after success */
    if(data == "you haven't session"){
      window.location.assign("http://phoenixnote.site/");
      alert("problems");
    }
    else{
      document.user_id = data;
      get_notes_id_fi(); //получаем все id заметок по данному пользователю, а в нём и текст для этих хаметок
    }
  });
  
});

function get_notes_id_fi() {
  // body...
  $.get('http://phoenixnote.site/get/get_notes_id',{'user_id':document.user_id}, function(data) {
    /*optional stuff to do after success */
    data = data.split(" ");
    for (i = 0;i< data.length-1;++i)
      id_mas.push(data[i]);
    for (i = 0; i< id_mas.length;++i){
        main.notes.push({"id":id_mas[i],"text":""});
    }
    get_text_fi();
    m();
  });
}

function get_text_fi() {
  // body...
  count = 0;
  for(i = 0;i<id_mas.length;++i){
    $.get('http://phoenixnote.site/get/get_note',{"user_id":document.user_id,"local_id":id_mas[i]}, function(data) {
      /*optional stuff to do after success */
      new_data = data.toString;
      main.notes[count].text = data;
      count++;
    });
  }

}


function create_note(text) {
  date = new Date();
  $.post('http://phoenixnote.site/post/create_note', {"text":text,"creater_id":document.user_id, "date":date}, function(data) {
    /*optional stuff to do after success */
    id_mas.push(data);
    main.notes.push({"id":data,"text":""});
    update(data);
  });
  $("#create_note_card").hide();
  $("#CreateNoteTextArea").val("");
}


function set_an_click(local_id) {
  // body...
  jQuery(function($){
  $(document).mouseup(function (e){ // событие клика по веб-документу
    var div = $("#" + local_id); // тут указываем ID элемента
    if (!div.is(e.target) // если клик был не по нашему блоку
        && div.has(e.target).length === 0) { // и не по его дочерним элементам
      div.removeAttr('style');
    note_open = false;
    }
  });
});
}

function close_note(local_id) {
  // body...
  $("#"+local_id).removeAttr('style');
  note_open = false;
}


function update(local_id){
  $.get('http://phoenixnote.site/get/get_note', {"user_id": document.user_id, "local_id":local_id}, function(data) {
    /*optional stuff to do after success */
    index = id_mas.indexOf(local_id);
    main.notes[index].text = data;  

  });
}


var main = new Vue({
  el: "main",
  data:{
   notes:[]
  }

})






function bind_click(note_id) {
  return "open_note('"+note_id + "');";
}
function bind_close(note_id) {
  // body...
  return 'close_note("'+ note_id + '");';
}

function open_note(note_id) {
  if(note_open == false){
  $("#"+note_id).css('position', 'fixed');
  $("#"+note_id).removeAttr('onclick')
  $("#"+note_id).animate(
    {
    left: "6%",
    top:"10%",
    height: "80%",
    width: "88%",
    },
    function() {
      // body..
      $(this).css({
        "z-index": '999',
      });
    }
  )
  $("#"+note_id).find("img").css('display','block');
  note_open = true;
  }
}



function share(last_id,new_id) {
  // body...
  $.post('http://phoenixnote.site/post/share_note', {user_id: document.user_id, "last_id":last_id, "new_id": new_id}, function(data,) {
    /*optional stuff to do after success */
    index = id_mas.indexOf(last_id);
    id_mas[index] = new_id;
    main.notes[index].id = new_id;
    update(new_id);
  });
}

function open_create_note_function() {
  // body...
  if(!note_open){
  $("#create_note_card").show();
  $("#create_note_card").animate({
        left: "5%",
        top:"10%",
        height: "80%",
        width: "90%"});
  note_open = true;
}

}



function m(argument) {
  // body...
for(i = 0;i< id_mas.length;++i){
  $("#"+id_mas[i]).find("textarea").on('input', function(event) {
        /*event.preventDefault();
        counter +=1;
        if (counter == 5){
          update_note($("#local_id").text() ,$("#QuickNoteTextArea").val());
          counter = 0;
        }*/
        alert('hello');
        
        /* Act on the event */
      });

}
}
