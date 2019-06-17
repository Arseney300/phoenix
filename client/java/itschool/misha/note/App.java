package itschool.misha.note;

import android.app.Application;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import itschool.misha.note.api.NoteApi;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import retrofit2.converter.scalars.ScalarsConverterFactory;

public class App extends Application {
    private final String URL="http://phoenixnote.site/";
    private static NoteApi api;
    private Retrofit retrofit;
    @Override
    public void onCreate() {
        super.onCreate();
        Gson gson=new GsonBuilder()
                .setLenient()
                .create();
        retrofit = new Retrofit.Builder()
                .baseUrl(URL)
//                .addConverterFactory(GsonConverterFactory.create(gson))
                .addConverterFactory(ScalarsConverterFactory.create())
                .build();
        api=retrofit.create(NoteApi.class);
    }

    public static NoteApi getApi() {
        return api;
    }
}
