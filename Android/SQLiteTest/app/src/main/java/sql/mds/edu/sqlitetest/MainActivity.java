package sql.mds.edu.sqlitetest;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private ListView list;
    private EditText title;
    private EditText msg;
    private long _id;
    private SQLiteOpenHelper mHelper;
    private SQLiteDatabase mDb;

    private class MyHelper extends SQLiteOpenHelper{

        public MyHelper(Context context, String name, int version) {
            super(context, name, null, version);
        }
        @Override
        public void onCreate(SQLiteDatabase db) {
            db.execSQL("create table if not exists note(_id integer primary key autoincrement, title text, msg text); ");
        }
        @Override
        public void onUpgrade(SQLiteDatabase db, int i, int i1) {
            db.execSQL("drop table if exists note");
            onCreate(db);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mHelper = new MyHelper(this, "data.db",2);

        list = (ListView) findViewById(R.id.list);
        title = (EditText) findViewById(R.id.title);
        msg = (EditText) findViewById(R.id.msg);

        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long id) {
                MainActivity.this._id = id;
                title.setText(((TextView)view.findViewById(android.R.id.text1)).getText().toString());
                msg.setText(((TextView)view.findViewById(android.R.id.text2)).getText().toString());
            }
        });
        dbQuery();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        menu.add(0,1,0,"추가").setIcon(android.R.drawable.ic_menu_add)
                .setShowAsAction(MenuItem.SHOW_AS_ACTION_ALWAYS);
        menu.add(0,2,0,"수정").setIcon(android.R.drawable.ic_menu_edit)
                .setShowAsAction(MenuItem.SHOW_AS_ACTION_ALWAYS);
        menu.add(0,3,0,"삭제").setIcon(android.R.drawable.ic_menu_delete)
                .setShowAsAction(MenuItem.SHOW_AS_ACTION_ALWAYS);

        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()){
            case 1:
                //Toast.makeText(this, "나와라", Toast.LENGTH_SHORT).show();
                dbInsert();
                break;
            case 2:
                dbUpdate();
                break;
            case 3:
                dbDelete();
                break;
            default:

        }
        dbQuery();
        return super.onOptionsItemSelected(item);
    }

    public void dbInsert(){
        String strTitle = title.getText().toString();
        String strMsg = msg.getText().toString();
        mDb = mHelper.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put("title", strTitle);
        cv.put("msg", strMsg);
        mDb.insert("note",null,cv);
    }
    public void dbUpdate(){
        mDb = mHelper.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put("title", title.getText().toString());
        cv.put("msg", msg.getText().toString());
        mDb.update("note",cv, "_id = ?",new String[]{_id +""});
    }
    public void dbDelete(){
        mDb = mHelper.getWritableDatabase();
        mDb.delete("note","_id = ?",new String[]{_id +""});
    }
    public void dbQuery(){
        mDb = mHelper.getReadableDatabase();
        // select * from note;
        Cursor c = mDb.query("note",null,null,null,null,null,null);
        String[] from = {"title", "msg"};
        int[] to = {android.R.id.text1, android.R.id.text2};
        SimpleCursorAdapter sca = new SimpleCursorAdapter(this, android.R.layout.simple_list_item_activated_2, c,from ,to);
        list.setAdapter(sca);

    }
}




