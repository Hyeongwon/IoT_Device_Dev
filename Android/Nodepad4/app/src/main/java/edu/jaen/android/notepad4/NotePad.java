package edu.jaen.android.notepad4;

import java.util.ArrayList;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.ContextMenu.ContextMenuInfo;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.AdapterView.AdapterContextMenuInfo;

public class NotePad extends Activity {
	private NoteDBAdapter noteList;
	private ListView list;
	private MyAdapter notes;
	private static final int ACTIVITY_CREATE = 0;
	private static final int ACTIVITY_EDIT = 1;

	private static final int INSERT_ID = Menu.FIRST;
	private static final int DELETE_ID = Menu.FIRST + 1;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.note_list);
		list = (ListView) findViewById(R.id.list);
		noteList = new NoteDBAdapter(this);
		registerForContextMenu(list);
		fillData();
		
		list.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> list, View view, int position,
					long id) {
				// TODO Auto-generated method stub
				Note item = (Note) notes.getItem(position);
				Intent i = new Intent(NotePad.this, NoteEdit.class);
				i.putExtra("_id", id);
				i.putExtra("title", item.title);
				i.putExtra("body", item.body);
				startActivityForResult(i, ACTIVITY_EDIT);				
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// TODO Auto-generated method stub
		menu.add(0, INSERT_ID, 0, R.string.menu_insert);

		return super.onCreateOptionsMenu(menu);
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// TODO Auto-generated method stub
		switch (item.getItemId()) {
		case INSERT_ID:
			createNote();
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	private void createNote() {
		Intent i = new Intent(this, NoteEdit.class);
		startActivityForResult(i, ACTIVITY_CREATE);
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);
		Bundle extras = data.getExtras();
		switch (requestCode) {
		case ACTIVITY_CREATE:
			noteList.insert(extras.getString("title"), extras.getString("body"));
			break;
		case ACTIVITY_EDIT:
			Log.e("1111111", extras.getLong("_id")+" : "+ extras.getString("title")+" : "+extras.getString("body"));
			noteList.update(extras.getLong("_id"), extras.getString("title"), extras.getString("body"));
			break;
		default:
			break;
		}
		fillData();
	}

	@Override
	public void onCreateContextMenu(ContextMenu menu, View v,
			ContextMenuInfo menuInfo) {
		// TODO Auto-generated method stub
		super.onCreateContextMenu(menu, v, menuInfo);
		menu.add(0, DELETE_ID, 0, R.string.menu_delete);
	}

	@Override
	public boolean onContextItemSelected(MenuItem item) {
		// TODO Auto-generated method stub
		switch(item.getItemId()) {
    	case DELETE_ID:
    		AdapterContextMenuInfo info = (AdapterContextMenuInfo) item.getMenuInfo();
	        noteList.delete(info.id);
    	    fillData();
	        return true;
		}
		return super.onContextItemSelected(item);
	}

	private void fillData() {
		// Get all of the rows from the database and create the item list
		notes = new MyAdapter();
		list.setAdapter(notes);
	}

	class MyAdapter extends BaseAdapter {
		private LayoutInflater inflater;
		private Cursor data;
		public MyAdapter() {
			inflater = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			data = noteList.select();
			startManagingCursor(data);
		}

		@Override
		public int getCount() {
			// TODO Auto-generated method stub
			return data.getCount();
		}

		@Override
		public Object getItem(int position) {
			// TODO Auto-generated method stub
			data.moveToPosition(position);
			long id = data.getLong(data.getColumnIndex(NoteUri._id));
			String title = data.getString(data.getColumnIndex(NoteUri.title));
			String body = data.getString(data.getColumnIndex(NoteUri.body));
			Note n = new Note(id, title, body);
			return n;
		}

		@Override
		public long getItemId(int position) {
			// TODO Auto-generated method stub
			data.moveToPosition(position);
			return data.getLong(data.getColumnIndex(NoteUri._id));
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			// TODO Auto-generated method stub
			if (convertView == null)
				convertView = inflater.inflate(R.layout.note_row, null);
			data.moveToPosition(position);
			TextView title = (TextView) convertView.findViewById(R.id.rowtitle);
			TextView body = (TextView) convertView.findViewById(R.id.rowbody);
			title.setText(data.getString(data.getColumnIndex(NoteUri.title)));
			body.setText(data.getString(data.getColumnIndex(NoteUri.body)));
			return convertView;
		}
	}
}