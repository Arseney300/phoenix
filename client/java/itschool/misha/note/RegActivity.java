package itschool.misha.note;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.design.button.MaterialButton;
import android.support.design.widget.TextInputEditText;
import android.support.design.widget.TextInputLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.Toast;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class RegActivity extends AppCompatActivity {
    TextInputEditText name,email,pass,passrep;
    TextInputLayout emailLay,passLay,nameLay,passtrueLay;
    MaterialButton btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_register);

        emailLay=findViewById(R.id.regemaillay);
        passLay=findViewById(R.id.regpassreplay);
        nameLay=findViewById(R.id.reg_loginlay);
        passtrueLay=findViewById(R.id.reg_passLay);

        btn=findViewById(R.id.reg_button);


        name=findViewById(R.id.reg_log);
        email=findViewById(R.id.reg_email);
        pass=findViewById(R.id.reg_pass);
        passrep=findViewById(R.id.reg_passrepeat);


        Toolbar toolbar=findViewById(R.id.reg_toolbar);
        setSupportActionBar(toolbar);
        ActionBar actionBar=getSupportActionBar();
        if (actionBar!=null)
        {
            actionBar.setHomeAsUpIndicator(R.drawable.ic_arrow_back_black_24dp);
            actionBar.setDisplayHomeAsUpEnabled(true);
        }


        pass.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View v, boolean hasFocus) {
                if(!hasFocus)
                if(pass.getText().toString().equals(""))
                    passtrueLay.setError(getResources().getText(R.string.Required));
                else
                    if(pass.getText().toString().length()<3)
                        passtrueLay.setError(getString(R.string.charReq));
                    else
                        passtrueLay.setError("");
            }
        });

        name.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View v, boolean hasFocus) {
                TextInputEditText editText=(TextInputEditText) v;
                if(!hasFocus)
                if (editText.getText().toString().equals(""))
                    nameLay.setError(getString(R.string.Required));
                else
                    nameLay.setError("");
            }
        });

        email.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View v, boolean hasFocus) {
                if(!hasFocus)
                    if(!validateEmail(((TextInputEditText) v).getText().toString()))
                        emailLay.setError(getString(R.string.incorrectEmail));
                    else
                        if(((TextInputEditText) v).getText().toString().equals(""))
                            emailLay.setError(getString(R.string.Required));
                        else
                            emailLay.setError("");
            }
        });
        passrep.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View v, boolean hasFocus) {
                TextInputEditText editText=(TextInputEditText) v;
                if(!hasFocus)
                    if(!editText.getText().toString().equals(pass.getText().toString()))
                        passLay.setError(getString(R.string.equalpassword));
                    else
                        if (editText.getText().toString().equals(""))
                            passLay.setError(getString(R.string.Required));
                        else
                            passLay.setError("");
            }
        });


        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(pass.getText().toString().length()<3||!validateEmail(email.getText().toString())||name.getText().toString().equals("")||email.getText().toString().equals("")||pass.getText().toString().equals("")||passrep.getText().toString().equals("")||!pass.getText().toString().equals(passrep.getText().toString())) {
                    if (name.getText().toString().equals(""))
                        nameLay.setError(getString(R.string.Required));
                    if (email.getText().toString().equals(""))
                        emailLay.setError(getString(R.string.Required));
                    if(passrep.getText().toString().equals(""))
                        passLay.setError(getString(R.string.Required));
                    if(pass.getText().toString().equals(""))
                        passtrueLay.setError(getString(R.string.Required));
                    if(pass.getText().toString().length()<3)
                        if(pass.requestFocus()) {
                            InputMethodManager inputManager = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
                            inputManager.showSoftInput(pass, InputMethodManager.SHOW_IMPLICIT);
                        }
                }
                else {
                    String log,em,ps;
                    log=name.getText().toString();
                    em=email.getText().toString();
                    ps=pass.getText().toString();
                    App.getApi().createUser(log,em,ps).enqueue(new Callback<String>() {
                        @Override
                        public void onResponse(Call<String> call, Response<String> response) {
                            if (response.body().equals("user with this name exist"))
                                nameLay.setError(getString(R.string.namelocked));
                            else
                            if(response.body().equals("user with this email exist"))
                                emailLay.setError(getString(R.string.emaillocked));
                            else {
//                            Toast.makeText(RegActivity.this,response.body(),Toast.LENGTH_SHORT).show();
                                MySqlHelper helper = new MySqlHelper(RegActivity.this);
                                SQLiteDatabase db = helper.getWritableDatabase();
                                ContentValues cv = new ContentValues();
                                cv.put(MySqlHelper.COLUMN_USERID, response.body());
                                db.insert(MySqlHelper.AUTH, null, cv);
                                db.close();
                                Intent intent = new Intent(RegActivity.this, MainActivity.class);
//            intent.addFlags(Intent.FLAG_ACTIVITY_NO_HISTORY);
                                intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                                intent.putExtra("fragment", SavedNotesFragment.class);
                                startActivity(intent);
                            }

                        }

                        @Override
                        public void onFailure(Call<String> call, Throwable t) {
                            Toast.makeText(RegActivity.this, "An error occurred during networking", Toast.LENGTH_SHORT).show();
                        }
                    });
                }
            }
        });



    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id=item.getItemId();

        if(id==android.R.id.home) {
            Intent intent=new Intent(this,MainActivity.class);
//            intent.addFlags(Intent.FLAG_ACTIVITY_NO_HISTORY);
            intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            intent.putExtra("fragment",LoginFragment.class);
            startActivity(intent);
//            finish();
        }



        return super.onOptionsItemSelected(item);
    }

    private static final String EMAIL_PATTERN = "^[a-zA-Z0-9#_~!$&'()*+,;=:.\"(),:;<>@\\[\\]\\\\]+@[a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+)*$";
    private Pattern pattern = Pattern.compile(EMAIL_PATTERN);
    private Matcher matcher;

    public boolean validateEmail(String email) {
        matcher = pattern.matcher(email);
        return matcher.matches();
    }
}
