package mds.edu.screen;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

/*
    TODO
    FirstActivity 화면 구현
    NextActivity 화면 구현
    FA -> NA 호출
 */

public class FirstActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    @Override
    protected void onStart() {

        super.onStart();
        Toast.makeText(this, "onStart", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onResume() {

        super.onResume();
        Toast.makeText(this, "onResume", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onPause() {

        super.onPause();
        Toast.makeText(this, "onPause", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onStop() {

        super.onStop();
        Toast.makeText(this, "onStop", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onDestroy() {

        super.onDestroy();
        Toast.makeText(this, "onDestroy", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onRestart() {

        super.onRestart();
        Toast.makeText(this, "onRestart", Toast.LENGTH_SHORT).show();
    }

    void goNext(View v) {

//        Toast.makeText(this, "next .....", Toast.LENGTH_SHORT).show();
        Intent i = new Intent();
        i.setClass(this, NextActivity.class);
        i.putExtra("name", "Josh");
        startActivity(i);
    }

    public static final int REQUEST = 1;

    void goNext1(View v) {

        Intent i = new Intent();
        i.setClass(this, NextActivity.class);
        i.putExtra("name", "Josh");
        startActivityForResult(i, REQUEST);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        if(requestCode == REQUEST && resultCode == NextActivity.RETURNCODE) {

            String msg = data.getStringExtra("return");
            Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
        }
    }

    public void goService(View v) {

        Intent i = new Intent();
        ComponentName cn = new ComponentName("mds.edu.screen", "mds.edu.screen.MyService");
        i.setComponent(cn);

        startService(i);
    }

    public void FinishService(View v) {

        Intent i = new Intent();
        ComponentName cn = new ComponentName("mds.edu.screen", "mds.edu.screen.MyService");
        i.setComponent(cn);

        stopService(i);
    }

    public void goCast(View v) {

        Intent i = new Intent();
        i.setAction("go.cast");

        sendBroadcast(i);
    }
}
