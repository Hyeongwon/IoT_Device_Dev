package edu.jaen.android.notepad4;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class NoteDBAdapter {
	private MyHelper helper;
	private SQLiteDatabase mDb;
	
	public NoteDBAdapter(Context context) {
		helper = new MyHelper(context, "mydb.db", 3);
	};

	private class MyHelper extends SQLiteOpenHelper {

		public MyHelper(Context context, String name, int version) {
			super(context, name, null, version);
			// TODO Auto-generated constructor stub
		}

		@Override
		public void onCreate(SQLiteDatabase db) {
			// TODO Auto-generated method stub
			db.execSQL("create table note(_id integer primary key autoincrement, title text, body text);");
		}

		@Override
		public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
			// TODO Auto-generated method stub
			db.execSQL("drop table if exists note; ");
			onCreate(db);
		}

	}

	public long insert(String title, String body) {
		mDb = helper.getWritableDatabase();
		ContentValues cv = new ContentValues();
		cv.put(NoteUri.title, title);
		cv.put(NoteUri.body, body);
		return mDb.insert(NoteUri.tableName, null, cv);
	}

	public int update(long _id, String title, String body) {
		mDb = helper.getWritableDatabase();
		ContentValues cv = new ContentValues();
		cv.put(NoteUri.title, title);
		cv.put(NoteUri.body, body);
		int count = mDb.update(NoteUri.tableName, cv, " _id = ? ", new String[] { _id + "" });
		return count;
	}

	public int delete(long _id) {
		mDb = helper.getWritableDatabase();
		int count = mDb.delete(NoteUri.tableName, " _id = ? ", new String[] { _id + "" });
		return count;
	}

	public Cursor select() {
		mDb = helper.getReadableDatabase();
		Cursor c = mDb.query(NoteUri.tableName, null, null, null, null, null, null);
		c.moveToFirst();
		return c;
	}
	
	public Cursor select(long _id){
		mDb = helper.getReadableDatabase();
		Cursor c = mDb.query(NoteUri.tableName, null, " _id = ? ", new String[]{_id+""}, null, null, null);
		c.moveToFirst();
		return c;
	}
}


