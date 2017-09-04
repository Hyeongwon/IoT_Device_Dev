package edu.mds.network.firstapp;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    void a1_call(View v) {

        //Toast.makeText(this, "!!!", Toast.LENGTH_SHORT).show();
        Intent i = new Intent();
        i.setClass(this, A1_Activity.class);
        startActivity(i);
    }

    void a2_call(View v) {

        Intent i = new Intent();

        /*
        ComponentName cpName = new ComponentName("edu.mds.network.secondapp",
                "edu.mds.network.secondapp.A2_Activity");

        i.setComponent(cpName);
        */
        i.setClassName("edu.mds.network.secondapp", "edu.mds.network.secondapp.A2_Activity");
        startActivity(i);
    }

    void a3_call(View v) {

        Intent i = new Intent();
        i.setAction("edu.mds.action.Edit");
        startActivity(i);
    }
}
