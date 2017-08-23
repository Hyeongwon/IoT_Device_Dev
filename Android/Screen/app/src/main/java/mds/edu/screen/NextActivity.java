package mds.edu.screen;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;
import android.view.View;

public class NextActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_next);

        String name = getIntent().getStringExtra("name");

        if(name != null) {

            Toast.makeText(this, name, Toast.LENGTH_SHORT).show();
        }
    }

    public static final int RETURNCODE = 2;

    public void back(View v) {

        Intent i = new Intent();
        i.putExtra("return", "Joy");
        setResult(RETURNCODE, i);
        finish();
    }
}
