package itschool.misha.note;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.design.button.MaterialButton;
import android.support.design.widget.NavigationView;
import android.support.v4.app.Fragment;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Calendar;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class NotePrivateCreateFragment extends Fragment {
    MaterialButton button;
    EditText editText;
    SimpleDateFormat dateFormat;
    String authID;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        dateFormat = new SimpleDateFormat("dd-MM-yyyy hh:mm:ss");
        authID=((MainActivity) getActivity()).getAuthID();
        View view=inflater.inflate(R.layout.fragment_createprivatenote,container,false);
        ((AppCompatActivity) getActivity()).getSupportActionBar().setTitle(R.string.createPrivateNotes);
        button=view.findViewById(R.id.priv_createbtn);
        editText=view.findViewById(R.id.priv_createtext);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String cid=editText.getText().toString();
                App.getApi().createLoginedNote(cid,dateFormat.format(Calendar.getInstance().getTime()),authID).enqueue(new Callback<String>() {
                    @Override
                    public void onResponse(Call<String> call, Response<String> response) {
                        ((NavigationView) getActivity().findViewById(R.id.nav_view)).setCheckedItem(R.id.actionshow);
                        ((NavigationView) getActivity().findViewById(R.id.nav_view)).getMenu().findItem(R.id.actionsaved).setChecked(true);
                        InputMethodManager inputManager = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
                        inputManager.hideSoftInputFromWindow(getActivity().getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
                        getActivity().getCurrentFocus().clearFocus();
                        getFragmentManager().beginTransaction().replace(R.id.fragment_container, new SavedNotesFragment()).commit();
                    }

                    @Override
                    public void onFailure(Call<String> call, Throwable t) {
                        Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
        return view;
    }
}
