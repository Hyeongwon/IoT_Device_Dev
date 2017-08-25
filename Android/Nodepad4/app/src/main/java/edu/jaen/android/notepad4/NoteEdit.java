package edu.jaen.android.notepad4;

import java.util.ArrayList;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class NoteEdit extends Activity {
	private EditText mTitleText;
	private EditText mBodyText;
	private Long mRowId;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.note_edit);
		mTitleText = (EditText) findViewById(R.id.title);
		mBodyText = (EditText) findViewById(R.id.body);

		Button confirmButton = (Button) findViewById(R.id.confirm);

		if(savedInstanceState != null){
			mRowId = savedInstanceState.getLong("_id");
		}else{
			Bundle extras = getIntent().getExtras();
			if(extras != null){
				mRowId = extras.getLong("_id");
				populateFields(extras);
			}else{
				mRowId = null;
			}
		}
		
		confirmButton.setOnClickListener(new View.OnClickListener() {

			public void onClick(View view) {
				String title = mTitleText.getText().toString();
				String body = mBodyText.getText().toString();
				if(title.trim().length() == 0 || body.trim().length()==0) return;
				
				Intent i = new Intent();
				i.putExtra("_id", mRowId);
				i.putExtra("title", title);
				i.putExtra("body", body);
				setResult(RESULT_OK,i);
				finish();
			}

		});
	}

	private void populateFields(Bundle b) {
		if (mRowId != null) {
			mTitleText.setText(b.getCharSequence("title"));
			mBodyText.setText(b.getCharSequence("body"));
		}
	}

	@Override
	protected void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
		outState.putLong("_id", mRowId);
	}
}
