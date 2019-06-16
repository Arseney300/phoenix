package itschool.misha.note;

import android.os.Bundle;
import android.renderscript.ScriptGroup;
import android.support.design.button.MaterialButton;
import android.support.design.widget.NavigationView;
import android.support.design.widget.TextInputEditText;
import android.support.design.widget.TextInputLayout;
import android.support.v4.app.Fragment;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Calendar;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class createNoteFragment extends Fragment {
    MaterialButton button;
    EditText editText;
    String authID;
    SimpleDateFormat dateFormat;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {
        dateFormat = new SimpleDateFormat("dd-MM-yyyy hh:mm:ss");
        final View view= inflater.inflate(R.layout.fragmnet_createnote,container,false);
        ((AppCompatActivity) getActivity()).getSupportActionBar().setTitle(R.string.createnote);
        System.out.println( dateFormat.format(Calendar.getInstance().getTime()));
        button=view.findViewById(R.id.createbtn);
        editText=view.findViewById(R.id.createtext);
        authID=((MainActivity)getActivity()).getAuthID();
        if(!authID.equals(""))
        {

            /*inputIDLay.setVisibility(View.VISIBLE);
            inputID.setOnFocusChangeListener(new View.OnFocusChangeListener() {
                @Override
                public void onFocusChange(View v, boolean hasFocus) {
                    if(!hasFocus)
                        App.getApi().checkNoteID(inputID.getText().toString()).enqueue(new Callback<String>() {
                            @Override
                            public void onResponse(Call<String> call, Response<String> response) {
                                if(!response.body().equals("true"))
                                    inputIDLay.setError("ID занят");
                                else
                                    inputIDLay.setError("");
                            }

                            @Override
                            public void onFailure(Call<String> call, Throwable t) {
                                Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                            }
                        });
                }
            });*/
        }

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String a=editText.getText().toString();
                if(a.equals(""))
                    editText.setError(getString(R.string.void2));
                else {
//                    if(authID.equals("")) { //||inputID.getText().toString().equals("")
                    String date =dateFormat.format(Calendar.getInstance().getTime());

                        App.getApi().createNote(a, dateFormat.format(Calendar.getInstance().getTime())).enqueue(new Callback<String>() {
                            @Override
                            public void onResponse(Call<String> call, Response<String> response) {
                                ((NavigationView) getActivity().findViewById(R.id.nav_view)).setCheckedItem(R.id.actionshow);
                                Bundle bundle = new Bundle();
                                ShowNoteFragment showNoteFragment = new ShowNoteFragment();
                                showNoteFragment.setArguments(bundle);
                                bundle.putString("id", response.body());
                                getFragmentManager().beginTransaction().replace(R.id.fragment_container, showNoteFragment).commit();
                            }

                            @Override
                            public void onFailure(Call<String> call, Throwable t) {
                                Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                            }
                        });
//                    }
                    /*else{
                        String cid=inputID.getText().toString();
                        App.getApi().createLoginedNote(cid,a,dateFormat.format(Calendar.getInstance().getTime()),authID).enqueue(new Callback<String>() {
                            @Override
                            public void onResponse(Call<String> call, Response<String> response) {
                                ((NavigationView) getActivity().findViewById(R.id.nav_view)).setCheckedItem(R.id.actionshow);
                                Bundle bundle = new Bundle();
                                ShowNoteFragment showNoteFragment = new ShowNoteFragment();
                                showNoteFragment.setArguments(bundle);
                                bundle.putString("id", response.body());
                                getFragmentManager().beginTransaction().replace(R.id.fragment_container, showNoteFragment).commit();
                            }

                            @Override
                            public void onFailure(Call<String> call, Throwable t) {
                                Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                            }
                        });
                    }*/

                    }
            }
        });

        return view;
    }
}
