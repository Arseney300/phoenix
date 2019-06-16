package itschool.misha.note;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class SavedNotesFragment extends Fragment implements SwipeRefreshLayout.OnRefreshListener {
    private RecyclerView recyclerView;
    private RecyclerView.LayoutManager layoutManager;
    private RecyclerView.Adapter adapter;
    SwipeRefreshLayout refreshLayout;
    String[] ids;
    String authID;


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_savednotes, container, false);
        Bundle bundle=getArguments();
        if(bundle!=null) {
            if (!bundle.getString("auth").equals("")) {
                authID = bundle.getString("auth");
            }
        }
        else
        authID=((MainActivity) getActivity()).getAuthID();

        ((AppCompatActivity) getActivity()).getSupportActionBar().setTitle(R.string.privateNotes);

        App.getApi().getAllNotes(authID).enqueue(new Callback<String>() {
            @Override
            public void onResponse(Call<String> call, Response<String> response) {
                if (!response.body().equals("")) {
                    ids = response.body().split(" ");

                    recyclerView = view.findViewById(R.id.savednotesRecView);

                    recyclerView.setHasFixedSize(true);

                    layoutManager = new LinearLayoutManager(getContext());
                    recyclerView.setLayoutManager(layoutManager);
                    refreshLayout = view.findViewById(R.id.saved_refresh);
                    refreshLayout.setOnRefreshListener(SavedNotesFragment.this);
                    refreshLayout.setColorSchemeColors(Color.parseColor("#00B0FF"));
                    adapter = new MyRecyclerAdapter(ids, getContext(), authID, getFragmentManager());
                    recyclerView.setAdapter(adapter);
                }
                else{
                    ((TextView) view.findViewById(R.id.saved_notes_gone)).setVisibility(View.VISIBLE);
                }
            }

            @Override
            public void onFailure(Call<String> call, Throwable t) {
                Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
            }
        });


        return view;
    }

    @Override
    public void onRefresh() {
        refreshLayout.setRefreshing(true);
        App.getApi().getAllNotes(((MainActivity) getActivity()).getAuthID()).enqueue(new Callback<String>() {
            @Override
            public void onResponse(Call<String> call, Response<String> response) {
                if (!response.body().equals("")) {
                    ids = response.body().split(" ");


                    recyclerView.setHasFixedSize(true);

                    layoutManager = new LinearLayoutManager(getContext());
                    recyclerView.setLayoutManager(layoutManager);
                    adapter = new MyRecyclerAdapter(ids, getContext(), authID, getFragmentManager());
                    recyclerView.setAdapter(adapter);
                    refreshLayout.setRefreshing(false);
                }
            }

            @Override
            public void onFailure(Call<String> call, Throwable t) {
                Toast.makeText(getContext(), "An error occurred during networking", Toast.LENGTH_SHORT).show();
                refreshLayout.setRefreshing(false);
            }
        });
    }
}
