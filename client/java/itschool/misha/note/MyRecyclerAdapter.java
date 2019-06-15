package itschool.misha.note;

import android.app.AlertDialog;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.DialogInterface;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentManager;
import android.support.v7.widget.CardView;
import android.support.v7.widget.RecyclerView;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.ContextMenu;
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

import java.io.IOException;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class MyRecyclerAdapter extends RecyclerView.Adapter<MyRecyclerAdapter.MyviewHolder>{
    private String[] data;
    Context context;
    String authID;
    FragmentManager fragmentManager;

    public MyRecyclerAdapter(String[] data, Context context,String authID,FragmentManager fragmentManager) {
        this.data = data;
        this.context=context;
        this.authID=authID;
        this.fragmentManager=fragmentManager;
    }

    @Override
    public MyviewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
        CardView cardView =(CardView) LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.card,viewGroup,false);
        MyviewHolder holder=new MyviewHolder(cardView);
        return holder;
    }

    @Override
    public void onBindViewHolder(MyviewHolder myviewHolder, final int i)
    {

        final CardView cardView=myviewHolder.cardView;
        final ImageButton textView=cardView.findViewById(R.id.cardmenu);

        textView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PopupMenu popupMenu=new PopupMenu(context,textView);
                popupMenu.inflate(R.menu.contextmenu);
                popupMenu.getMenu().getItem(0).setTitle(data[i]);
                popupMenu.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
                    @Override
                    public boolean onMenuItemClick(MenuItem item) {
                        switch (item.getItemId())
                        {
                            case R.id.contextmenu_delete:{
                                AlertDialog.Builder builder=new AlertDialog.Builder(context)
                                        .setPositiveButton(context.getText(R.string.yes), new DialogInterface.OnClickListener() {
                                            @Override
                                            public void onClick(DialogInterface dialog, int which) {
                                                App.getApi().deleteNote(authID,data[i]).enqueue(new Callback<String>() {
                                                    @Override
                                                    public void onResponse(Call<String> call, Response<String> response) {
                                                        String[] dd=new String[data.length-1];
                                                        for(int j=0,k=0;j<data.length;j++,k++)
                                                            if(j==i) {
                                                                k--;
                                                                continue;
                                                            }
                                                            else
                                                                dd[k]=data[j];
                                                        data=dd;

                                                        notifyDataSetChanged();

                                                    }

                                                    @Override
                                                    public void onFailure(Call<String> call, Throwable t) {
                                                        Toast.makeText(context, "An error occurred during networking", Toast.LENGTH_SHORT).show();
                                                    }
                                                });


                                            }
                                        })
                                        .setNegativeButton(context.getText(R.string.no), new DialogInterface.OnClickListener() {
                                            @Override
                                            public void onClick(DialogInterface dialog, int which) {

                                            }
                                        })
                                        .setMessage(context.getString(R.string.deletewhat));
                                builder.create().show();


                            }break;
                            case R.id.contextmenuid:{
                                ClipboardManager clipboard = (ClipboardManager) context.getSystemService(Context.CLIPBOARD_SERVICE);
                                ClipData cdata=ClipData.newPlainText("id",data[i]);
                                Toast.makeText(context,context.getString(R.string.copyingID),Toast.LENGTH_SHORT).show();
                                clipboard.setPrimaryClip(cdata);
                            }break;
                            case R.id.contextmenu_share:{
                                final ShareDialog dialog=new ShareDialog();
                                final Bundle bundle=new Bundle();
                                bundle.putString("noteID",data[i]);
                                bundle.putString("authID",authID);
                                dialog.setArguments(bundle);
                                dialog.show(fragmentManager,"shareDialog");
                                final Handler handler=new Handler(){
                                    @Override
                                    public void handleMessage(Message msg) {
                                        super.handleMessage(msg);
                                        String a=msg.getData().getString("ID");
                                        data[i]=a;
                                        notifyDataSetChanged();
                                    }
                                };
                                new Thread(new Runnable() {
                                    @Override
                                    public void run() {
                                        while (dialog.getDialog()==null) {
                                            try {
                                                Thread.sleep(100);
                                            } catch (InterruptedException e) {
                                                e.printStackTrace();
                                            }
                                        }
                                        while (dialog.getDialog()!=null)
                                        {
                                            try {
                                                Thread.sleep(100);
                                            } catch (InterruptedException e) {
                                                e.printStackTrace();
                                            }
                                        }
                                        if(dialog.newID!=null) {
                                            Bundle bundle1 = new Bundle();
                                            bundle.putString("ID", dialog.newID);
                                            Message msg = new Message();
                                            msg.setData(bundle);
                                            msg.setTarget(handler);
                                            msg.sendToTarget();
                                        }

                                    }
                                }).start();

                            }break;
                        }
                        return false;
                    }
                });
                popupMenu.show();
            }
        });




        final EditText edit=myviewHolder.cardView.findViewById(R.id.cardtext);
        final ProgressBar progressBar=myviewHolder.cardView.findViewById(R.id.cardprogress);
        edit.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                if(i<data.length)

                App.getApi().updatePrivateNote(authID,s.toString(),data[i]).enqueue(new Callback<String>() {
                    @Override
                    public void onResponse(Call<String> call, Response<String> response) {
                        System.out.println(response.body());

                    }

                    @Override
                    public void onFailure(Call<String> call, Throwable t) {
                        Toast.makeText(context, "An error occurred during networking", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
        edit.post(new Runnable() {
            @Override
            public void run() {
                   App.getApi().getLoginedNote(data[i],authID).enqueue(new Callback<String>() {
                       @Override
                       public void onResponse(Call<String> call, Response<String> response) {
                           if(!response.body().equals("problems")) {
                               progressBar.setVisibility(View.GONE);
                               edit.setVisibility(View.VISIBLE);
                               edit.setText(response.body());
                           }
                       }

                       @Override
                       public void onFailure(Call<String> call, Throwable t) {
                           Toast.makeText(context, "An error occurred during networking", Toast.LENGTH_SHORT).show();
                       }
                   });


            }
        });

    }
    @Override
    public int getItemCount() {
        if(data!=null)
        return data.length;
        else return 0;
    }



    public static class MyviewHolder extends RecyclerView.ViewHolder {
        public CardView cardView;

        public MyviewHolder(CardView itemView) {
            super(itemView);
            cardView=itemView;
        }

    }
}
