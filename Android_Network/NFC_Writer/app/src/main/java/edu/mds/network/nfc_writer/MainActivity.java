package edu.mds.network.nfc_writer;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends Activity {

    TextView tv;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void write_text(View v) {

        tv = findViewById(R.id.textEt);
        String text = tv.getText().toString();

        Intent i = new Intent();
        i.putExtra("text", text);
        i.putExtra("type", "T");
        i.setClass(this, NFCWriteActivity.class);
        startActivity(i);
    }

    public void write_url(View v) {

        tv = findViewById(R.id.urlEt);
        String url = tv.getText().toString();
        Intent i = new Intent();
        i.putExtra("url", url);
        i.putExtra("type", "U");
        i.setClass(this, NFCWriteActivity.class);
        startActivity(i);

    }
}
