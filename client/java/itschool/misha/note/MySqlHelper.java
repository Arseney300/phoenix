package itschool.misha.note;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class MySqlHelper extends SQLiteOpenHelper {
    private static final String DB_NAME="notes.db";
    static final int SCHEMA=6;

    public static final String TABLE = "notes";
    public static final String AUTH = "user";

    public static final String COLUMN_USERID = "userid";

    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_NOTEID = "local_id";


    public MySqlHelper(Context context) {
        super(context, DB_NAME, null, SCHEMA);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE "+TABLE+" ("+COLUMN_ID+" INTEGER PRIMARY KEY AUTOINCREMENT, "+COLUMN_NOTEID+" TEXT);");
        db.execSQL("CREATE TABLE "+AUTH+" ("+COLUMN_USERID+" TEXT);");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS "+TABLE);
        db.execSQL("DROP TABLE IF EXISTS "+AUTH);
        onCreate(db);
    }
}
