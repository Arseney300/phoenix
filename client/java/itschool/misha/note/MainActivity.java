package itschool.misha.note;

import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.Nullable;
import android.support.design.widget.NavigationView;
import android.support.v4.app.Fragment;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Gravity;
import android.view.MenuItem;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;

import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.RequestBody;
import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.http.Multipart;


public class MainActivity extends AppCompatActivity {

    private DrawerLayout drawerLayout;
    NavigationView navigationView;
    ActionBar actionBar;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        Toolbar toolbar=findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        navigationView=findViewById(R.id.nav_view);
        drawerLayout=findViewById(R.id.drawer);

        actionBar=getSupportActionBar();
        if (actionBar!=null)
        {
            actionBar.setHomeAsUpIndicator(R.drawable.ic_menu);
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        navigationView.setNavigationItemSelectedListener(new NavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(final MenuItem menuItem) {

                int id = menuItem.getItemId();
                switch (id) {
                    case R.id.actionone: {
                        menuItem.setChecked(true);
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new createNoteFragment()).commit();
                    }break;
                    case R.id.actionlogin:{
                            menuItem.setChecked(true);
                            getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new LoginFragment()).commit();

                    }break;
                    case R.id.actionlogout:{
                        final MyDialog dialog=new MyDialog();
                        dialog.show(getSupportFragmentManager(),"logout");
                        final Handler handler=new Handler(){
                            @Override
                            public void handleMessage(Message msg) {
                                super.handleMessage(msg);
                                int btn=msg.getData().getInt("btn");
                                if(btn==1) {
                                    navigationView.getMenu().findItem(R.id.actionlogin).setChecked(true);
                                    getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new LoginFragment()).commit();
                                }
                            }
                        };

                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                while (dialog.getBtn()==0)
                                {
                                    try {
                                        Thread.sleep(100);
                                    } catch (InterruptedException e) {
                                        e.printStackTrace();
                                    }
                                }
                                Bundle bundle=new Bundle();
                                bundle.putInt("btn",dialog.getBtn());
                                Message msg=new Message();
                                msg.setData(bundle);
                                msg.setTarget(handler);
                                msg.sendToTarget();



                            }
                        }).start();
                    }break;
                    case R.id.actionshow:{
                        menuItem.setChecked(true);
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new ShowNoteFragment()).commit(); }break;
                    case R.id.actionsaved:{
                        menuItem.setChecked(true);
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new SavedNotesFragment()).commit();}break;
                    case R.id.actioncreateNote:{
                        menuItem.setChecked(true);
                        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,new NotePrivateCreateFragment()).commit();
                    }break;
                }
                if(getCurrentFocus()!=null) {
                    InputMethodManager inputManager = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
                    inputManager.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
                    getCurrentFocus().clearFocus();
                }
                drawerLayout.closeDrawers();
                return true;
            }
        });
        Bundle bundle=getIntent().getExtras();
        if(bundle!=null)
        {


            try {
                Fragment fragment = (Fragment) ((Class)getIntent().getExtras().get("fragment")).newInstance();
                System.out.println(fragment);
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, fragment).commit();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InstantiationException e) {
                e.printStackTrace();
            }

        }
            initLoginedUser();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id=item.getItemId();


        if(id==android.R.id.home)
        {
            if(getCurrentFocus()!=null) {
                InputMethodManager inputManager = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
                inputManager.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
                getCurrentFocus().clearFocus();
            }
            drawerLayout.openDrawer(GravityCompat.START);
        }


        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onBackPressed() {
        if(drawerLayout.isDrawerOpen(GravityCompat.START)) {
            drawerLayout.closeDrawers();
        }
        else
            super.onBackPressed();
    }
    public String getAuthID() {
        MySqlHelper helper=new MySqlHelper(this);
        SQLiteDatabase db=helper.getReadableDatabase();
        Cursor cursor=db.rawQuery("select * from "+MySqlHelper.AUTH,null);
        String id="";
        if(cursor.getCount()>0)
            if(cursor.moveToFirst())
                id=cursor.getString(0);
            cursor.close();
            db.close();
            return id;
    }
    public void initLoginedUser(){
        if(!getAuthID().equals(""))
        App.getApi().getName(getAuthID()).enqueue(new Callback<String>() {
            @Override
            public void onResponse(Call<String> call, Response<String> response) {
                ((TextView)navigationView.getHeaderView(0).findViewById(R.id.nav_name)).setText(response.body());
                ((TextView)navigationView.getHeaderView(0).findViewById(R.id.nav_name)).setVisibility(View.VISIBLE);
                navigationView.getMenu().findItem(R.id.actionlogout).setVisible(true);
                navigationView.getMenu().findItem(R.id.actionlogin).setVisible(false);
                navigationView.getMenu().findItem(R.id.actioncreateNote).setVisible(true);
                navigationView.getMenu().findItem(R.id.actionsaved).setVisible(true);
                navigationView.getMenu().findItem(R.id.actionsaved).setChecked(true);
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new SavedNotesFragment()).commit();
            }

            @Override
            public void onFailure(Call<String> call, Throwable t) {
                MySqlHelper helper=new MySqlHelper(MainActivity.this);
                SQLiteDatabase db=helper.getWritableDatabase();
                db.execSQL("DELETE FROM "+MySqlHelper.AUTH);
                db.close();
                actionBar.setTitle(navigationView.getMenu().findItem(R.id.actionlogin).getTitle());
                navigationView.getMenu().findItem(R.id.actionlogin).setChecked(true);
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new LoginFragment()).commit();

            }
        });
        else
        {
            actionBar.setTitle(navigationView.getMenu().findItem(R.id.actionlogin).getTitle());
            navigationView.getMenu().findItem(R.id.actionlogin).setChecked(true);
            getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new LoginFragment()).commit();
        }

    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {

        super.onSaveInstanceState(outState);
    }

    public void uploadFile(Uri fileUri) {

        File file=new File(fileUri.getPath());
        RequestBody requestFile = RequestBody.create(MediaType.parse(getContentResolver().getType(fileUri)),file);

        MultipartBody.Part body = MultipartBody.Part.createFormData("file",file.getName(),requestFile);
        String desctiptionStr = "description";
        RequestBody description=RequestBody.create(MultipartBody.FORM,desctiptionStr);
        Call<ResponseBody> call = App.getApi().upload(description,body);
        call.enqueue(new Callback<ResponseBody>() {
            @Override
            public void onResponse(Call<ResponseBody> call, Response<ResponseBody> response) {
                Log.v("Upload","succes");
            }

            @Override
            public void onFailure(Call<ResponseBody> call, Throwable t) {
                Log.e("Upload error:",t.getMessage());
            }
        });
    }

}
