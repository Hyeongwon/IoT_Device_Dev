package mds.edu.screen;

import android.app.Activity;
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

    void goNext(View v) {

//        Toast.makeText(this, "next .....", Toast.LENGTH_SHORT).show();
        Intent i = new Intent();
        i.setClass(this, NextActivity.class);
        i.putExtra("name", "Josh");
        startActivity(i);
    }
}
