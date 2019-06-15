package itschool.misha.note;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.design.button.MaterialButton;
import android.support.design.card.MaterialCardView;
import android.support.design.widget.TextInputEditText;
import android.support.design.widget.TextInputLayout;
import android.support.v4.app.Fragment;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.PopupMenu;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import itschool.misha.note.api.NoteApi;
import okhttp3.MediaType;
import okhttp3.RequestBody;
import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class ShowNoteFragment extends Fragment {

    private static final int READ_REQUEST_CODE = 42;
    private static final int DEFAULT_BUFFER_SIZE = 1024 * 4;

    TextInputEditText editText;
    TextInputLayout editlay;
    MaterialButton button;
    MaterialCardView cardView;
    ImageButton attachButton;
    EditText textView;
    ProgressBar progressBar;
    String id;
    TextWatcher textWatcher=new TextWatcher() {
        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) {

        }

        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count) {

        }

        @Override
        public void afterTextChanged(Editable s) {
            if(!id.equals(""))
                App.getApi().updateNote(id,s.toString()).enqueue(new Callback<Void>() {
                    @Override
                    public void onResponse(Call<Void> call, Response<Void> response) {

                    }

                    @Override
                    public void onFailure(Call<Void> call, Throwable t) {
                        Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                    }
                });
        }
    };


    {id="";}

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode==READ_REQUEST_CODE && resultCode== Activity.RESULT_OK)
        {
            Uri uri=data.getData();
            InputStream input=null;
            try {
                input = getActivity().getContentResolver().openInputStream(uri);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
            Cursor cursor=getActivity().getContentResolver().query(uri,null,null,null,null);
            String[] name={""};
            if(cursor.moveToFirst())
            {
                name=cursor.getString(2).split("\\.");
            }
            cursor.close();
            File tempfile=null;
            try {
                tempfile = File.createTempFile(name[0],"."+name[1]);
                FileOutputStream out=new FileOutputStream(tempfile);


                int n;
                byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
                while ((n=input.read(buffer))!=-1)
                {
                    out.write(buffer,0,n);
                }
                out.close();
                input.close();
                tempfile.deleteOnExit();
                System.out.println(tempfile.getPath());



            } catch (IOException e) {
                e.printStackTrace();
            }

            System.out.println(name[0]);
                Log.i("File info:", getActivity().getContentResolver().getType(uri));

        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, final ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_shownote,container,false);
        ((AppCompatActivity) getActivity()).getSupportActionBar().setTitle(R.string.ShowQuickNotes);
        editlay=view.findViewById(R.id.shownoteeditlay);
        editText=view.findViewById(R.id.shownoteedit);
        button=view.findViewById(R.id.shownotebtn);
        attachButton=view.findViewById(R.id.shownote_attach);
        cardView=view.findViewById(R.id.shownotecard);
        textView=view.findViewById(R.id.shownotecardtext);
        progressBar=view.findViewById(R.id.show_progress);
        final TextView menubtn=view.findViewById(R.id.shownotecardmenu);

        textView.addTextChangedListener(textWatcher);

        attachButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(Intent.ACTION_OPEN_DOCUMENT);
                intent.addCategory(Intent.CATEGORY_OPENABLE);
                intent.setType("*/*");

                startActivityForResult(intent,READ_REQUEST_CODE);
            }
        });

        menubtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MySqlHelper helper=new MySqlHelper(getContext());
                SQLiteDatabase db=helper.getReadableDatabase();
                Cursor cursor=db.rawQuery("select * from "+MySqlHelper.TABLE+" where "+MySqlHelper.COLUMN_NOTEID+"=?",new String[]{id});
                PopupMenu popupMenu=new PopupMenu(getContext(),menubtn);
                popupMenu.inflate(R.menu.shownote_cardmenu);
                if(id.equals("")||cursor.getCount()>0)
                    popupMenu.getMenu().getItem(0).setEnabled(false);
                cursor.close();
                db.close();
                popupMenu.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
                    @Override
                    public boolean onMenuItemClick(MenuItem item) {
                        MySqlHelper helper=new MySqlHelper(getContext());
                        SQLiteDatabase db=helper.getWritableDatabase();
                        ContentValues cv=new ContentValues();
                        cv.put(MySqlHelper.COLUMN_NOTEID,id);
                        db.insert(MySqlHelper.TABLE,null,cv);
                        db.close();
                        return false;
                    }
                });
                popupMenu.show();
            }
        });

        if(getArguments()!=null) {
            Bundle bundle=getArguments();
            id = bundle.getString("id");
            editText.setText(id);
            if (!id.equals("")) {
                cardView.setVisibility(View.VISIBLE);
                progressBar.setVisibility(View.VISIBLE);
                textView.setVisibility(View.GONE);
                App.getApi().getNote(id).enqueue(new Callback<String>() {
                    @Override
                    public void onResponse(Call<String> call, Response<String> response) {
                        progressBar.setVisibility(View.GONE);
                        textView.setVisibility(View.VISIBLE);
                        textView.removeTextChangedListener(textWatcher);
                        if(response.body().equals("problems")||response.body().equals("not found")) {
                            textView.setEnabled(false);
                            textView.setText(getString(R.string.noteNotFound));
                            id = "";
                        }
                        else {
                            textView.setEnabled(true);
                            textView.setText(response.body());
                        }
                        textView.addTextChangedListener(textWatcher);
                    }

                    @Override
                    public void onFailure(Call<String> call, Throwable t) {
                        Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                        id="";
                    }
                });

            }
        }
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final String a=editText.getText().toString();
                if(a.equals(""))
                {
                    editlay.setError(getString(R.string.void2));
                }
                else {
                    cardView.setVisibility(View.VISIBLE);
                    progressBar.setVisibility(View.VISIBLE);
                    textView.setVisibility(View.GONE);

                    App.getApi().getNote(a).enqueue(new Callback<String>() {
                        @Override
                        public void onResponse(Call<String> call, Response<String> response) {
                            progressBar.setVisibility(View.GONE);
                            textView.setVisibility(View.VISIBLE);
                            textView.removeTextChangedListener(textWatcher);
                            if(response.body().equals("problems")||response.body().equals("not found")) {
                                id = "";
                                textView.setEnabled(false);
                                textView.setText(getString(R.string.noteNotFound));
                            }
                            else {
                                textView.setEnabled(true);
                                textView.setText(response.body());
                                id = a;
                            }
                            textView.addTextChangedListener(textWatcher);
                        }

                        @Override
                        public void onFailure(Call<String> call, Throwable t) {
                            Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                            id="";
                        }
                    });

                }

            }
        });


        return view;
    }



}
