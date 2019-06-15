package itschool.misha.note;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.design.widget.TextInputEditText;
import android.support.design.widget.TextInputLayout;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Toast;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class ShareDialog extends DialogFragment {
    String noteID,authID;
    AlertDialog alertDialog;
    TextInputEditText editText;
    TextInputLayout editLay;
    public String newID;

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        final LayoutInflater inflater=LayoutInflater.from(getContext());
        final View view=inflater.inflate(R.layout.dialog_share,null);
        editText=view.findViewById(R.id.dialog_shareEdit);
        editLay=view.findViewById(R.id.dialog_shareEditLay);
        noteID=getArguments().getString("noteID");
        authID=getArguments().getString("authID");


        editText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                editLay.setError("");
            }
        });
        builder.setView(view)
                .setPositiveButton(R.string.OK, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                    }
                })
                .setNegativeButton(R.string.Cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        ShareDialog.this.getDialog().cancel();
                    }
                });
        alertDialog=builder.create();


        return alertDialog;
    }


    @Override
    public void onStart() {
        super.onStart();
        alertDialog.getButton(AlertDialog.BUTTON_POSITIVE).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final String a=editText.getText().toString();
                App.getApi().checkNoteID(a).enqueue(new Callback<String>() {
                    @Override
                    public void onResponse(Call<String> call, Response<String> response) {
                        if(response.body().equals("true"))
                        {
                            App.getApi().shareNote(authID,noteID,a).enqueue(new Callback<String>() {
                                @Override
                                public void onResponse(Call<String> call, Response<String> response) {
                                    newID=a;
                                    ShareDialog.this.getDialog().cancel();
                                }

                                @Override
                                public void onFailure(Call<String> call, Throwable t) {
                                    Toast.makeText(getActivity(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                                }
                            });
                            //Расшаривание
                        }
                        else {
                            editLay.setError(getString(R.string.idlocked));
                        }
                    }

                    @Override
                    public void onFailure(Call<String> call, Throwable t) {
                        Toast.makeText(getActivity(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
    }
}
