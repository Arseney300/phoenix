package itschool.misha.note;

import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
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
import android.view.inputmethod.InputMethodManager;
import android.widget.Toast;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class LoginFragment extends Fragment {
    MaterialButton loginBtn,regBtn;
    TextInputEditText login,pass;
    TextInputLayout logLay,passLay;


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,  Bundle savedInstanceState) {
        View view=inflater.inflate(R.layout.fragment_login,container,false);
        ((AppCompatActivity) getActivity()).getSupportActionBar().setTitle(R.string.log_in);

        login=view.findViewById(R.id.logtext);
        pass=view.findViewById(R.id.passtext);
        logLay=view.findViewById(R.id.log_loginLay);
        passLay=view.findViewById(R.id.log_passLay);

        login.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                logLay.setError("");
            }
        });
        pass.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                passLay.setError("");
            }
        });



        loginBtn=view.findViewById(R.id.loginbutton);
        regBtn=view.findViewById(R.id.registerbutton);
        regBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(getContext(),RegActivity.class);
                startActivity(intent);
            }
        });
        loginBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(login.getText().toString().equals("")||pass.getText().toString().equals(""))
                {
                    if(login.getText().toString().equals(""))
                        logLay.setError("Required");
                    if(pass.getText().toString().equals(""))
                        passLay.setError("Required");
                }
                else
                {
                    String log,pas;
                    log=login.getText().toString();
                    pas=pass.getText().toString();
                    App.getApi().loginUser(log,pas).enqueue(new Callback<String>() {
                        @Override
                        public void onResponse(Call<String> call, Response<String> response) {
//                            Toast.makeText(getContext(),response.body(),Toast.LENGTH_SHORT).show();  //user with this name or email not exist
                            if(!response.body().equals("user with this name or email not exist") && !response.body().equals(""))
                            {
                                MySqlHelper helper=new MySqlHelper(getContext());
                                SQLiteDatabase db=helper.getWritableDatabase();
                                ContentValues cv=new ContentValues();
                                cv.put(MySqlHelper.COLUMN_USERID,response.body());
                                db.insert(MySqlHelper.AUTH,null,cv);
                                db.close();

                                ((MainActivity) getActivity()).initLoginedUser();
                                ((NavigationView) getActivity().findViewById(R.id.nav_view)).setCheckedItem(R.id.actionsaved);
                                InputMethodManager inputManager = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
                                inputManager.hideSoftInputFromWindow(getActivity().getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
                                getActivity().getCurrentFocus().clearFocus();
                                Fragment fragment=new SavedNotesFragment();
                                Bundle bundle=new Bundle();
                                bundle.putString("auth",response.body());
                                fragment.setArguments(bundle);
                                getFragmentManager().beginTransaction().replace(R.id.fragment_container, fragment).commit();
                            }
                            else {
                                if(response.body().equals("user with this name or email not exist"))
                                    logLay.setError(getString(R.string.invalidLogin));


                            }
                        }

                        @Override
                        public void onFailure(Call<String> call, Throwable t) {
                            Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                        }
                    });
                }
            }
        });

        return view;
    }
}
