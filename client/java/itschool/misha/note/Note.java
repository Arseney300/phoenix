package itschool.misha.note;

import android.content.Context;
import android.widget.Toast;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class Note {
    public String local_id;
    private String body="";
        Note(String local_id, final Context context)
        {
        this.local_id=local_id;
        App.getApi().getNote(local_id).enqueue(new Callback<String>() {
@Override
public void onResponse(Call<String> call, Response<String> response) {
        body=response.body();
        }

@Override
public void onFailure(Call<String> call, Throwable t) {
        Toast.makeText(context, "An error occurred during networking", Toast.LENGTH_SHORT).show();
        body="An error occurred during networking";
        }
        });
        }
        String getNotebody(){
        return body;
        }
        }
