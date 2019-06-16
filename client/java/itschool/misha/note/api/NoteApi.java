package itschool.misha.note.api;

import itschool.misha.note.Note;
import okhttp3.MultipartBody;
import okhttp3.RequestBody;
import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.Response;
import retrofit2.http.Field;
import retrofit2.http.FormUrlEncoded;
import retrofit2.http.GET;
import retrofit2.http.Multipart;
import retrofit2.http.POST;
import retrofit2.http.Part;
import retrofit2.http.Query;

public interface NoteApi {
    @GET("/get/get_quick_note")
    Call<String> getNote(@Query("local_id") String id);

    @FormUrlEncoded
    @POST("/post/create_quick_note")
    Call<String> createNote(@Field("text") String text, @Field("date") String date);

    @FormUrlEncoded
    @POST("/post/update_quick_note")
    Call<Void> updateNote(@Field("local_id") String id,@Field("text") String text);

    @FormUrlEncoded
    @POST("/post/create_user")
    Call<String> createUser(@Field("name") String name,@Field("email") String email,@Field("pass") String password);

    @FormUrlEncoded
    @POST("/post/login_user")
    Call<String> loginUser(@Field("login") String login,@Field("pass") String pass);

    @FormUrlEncoded
    @POST("/post/create_note")
    Call<String> createLoginedNote(@Field("text") String text, @Field("date") String date,@Field("creater_id") String creater_id);

    @GET("/get/test_id_user_note")
    Call<String> checkNoteID(@Query("id") String id);

    @FormUrlEncoded
    @POST("/post/share_note")
    Call<String> shareNote(@Field("user_id") String userID,@Field("last_id") String lastID,@Field("new_id") String newID);

    @GET("/get/get_note")
    Call<String> getLoginedNote(@Query("local_id") String id,@Query("user_id") String userID);

    @GET("/get/get_notes_id")
    Call<String> getAllNotes(@Query("user_id") String userID);

    @GET("/get/delete_note")
    Call<String> deleteNote(@Query("user_id") String userID,@Query("local_id") String id);

    @FormUrlEncoded
    @POST("/post/update_note")
    Call<String> updatePrivateNote(@Field("user_id") String userID,@Field("text") String text,@Field("local_id") String id);

    @GET("/get/get_name")
    Call<String> getName(@Query("id") String id);

    @Multipart
    @POST("/upload")
    Call<ResponseBody> upload(@Part("description") RequestBody description, @Part MultipartBody.Part file);

}
