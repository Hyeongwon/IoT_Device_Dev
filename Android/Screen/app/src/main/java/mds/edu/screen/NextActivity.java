package mds.edu.screen;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Toast;

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
}
