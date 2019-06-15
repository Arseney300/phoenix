package itschool.misha.note;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.app.DialogFragment;
import android.view.View;
import android.widget.TextView;

public class MyDialog extends DialogFragment {
    private  int btn;
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        btn=0;

        AlertDialog.Builder builder=new AlertDialog.Builder(getActivity());
        builder.setMessage(getString(R.string.quitSeriosly))
                .setPositiveButton(R.string.yes, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        btn=1;
                        MySqlHelper helper=new MySqlHelper(getContext());
                        SQLiteDatabase db=helper.getReadableDatabase();
                        db.execSQL("DELETE FROM "+MySqlHelper.AUTH);
                        db.close();
                        ((NavigationView)getActivity().findViewById(R.id.nav_view)).getMenu().findItem(R.id.actionlogout).setVisible(false);
                        ((NavigationView)getActivity().findViewById(R.id.nav_view)).getMenu().findItem(R.id.actionlogin).setVisible(true);
                        ((NavigationView)getActivity().findViewById(R.id.nav_view)).getMenu().findItem(R.id.actioncreateNote).setVisible(false);
                        ((NavigationView)getActivity().findViewById(R.id.nav_view)).getMenu().findItem(R.id.actionsaved).setVisible(false);
                        ((TextView) ((NavigationView)getActivity().findViewById(R.id.nav_view)).getHeaderView(0).findViewById(R.id.nav_name)).setVisibility(View.GONE);
                    }
                })
                .setNegativeButton(R.string.no, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        btn=-1;
                        MyDialog.this.getDialog().cancel();
                    }
                });
        return builder.create();
    }

    public int getBtn() {
        return btn;
    }
}
