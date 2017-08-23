package mds.edu.uicomponent;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity /*implements View.OnClickListener*/ {
    TextView tv;
    Button bt;
    EditText et;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tv = (TextView) findViewById(R.id.first_TextView);
        tv.setText("Hello");

        bt = (Button) findViewById(R.id.first_button);

        et = (EditText) findViewById(R.id.first_edit);

//        MyClick click = new MyClick();
//        bt.setOnClickListener(this);


        bt.setOnClickListener(new View.OnClickListener() {

            public void onClick(View view) {

                tv.setText(et.getText());
                et.setText("");
            }
        });

        et.setOnKeyListener(new View.OnKeyListener() {

            public boolean onKey(View view, int key, KeyEvent keyEvent) {

                if(keyEvent.getAction() == KeyEvent.ACTION_DOWN) {

                    if(key == keyEvent.KEYCODE_ENTER) {

                        Toast.makeText(MainActivity.this, et.getText().toString(), Toast.LENGTH_SHORT).show();
                        return true;
                    }
                }
                return false;
            }
        });

        findViewById(R.id.first_linear).setOnTouchListener(new View.OnTouchListener() {

            public boolean onTouch(View view, MotionEvent event) {

                switch (event.getAction()) {

                    case MotionEvent.ACTION_DOWN:
                        Toast.makeText(MainActivity.this, "x : " + event.getX() +
                                " y : " + event.getY(), Toast.LENGTH_SHORT).show();
                        return true;

                    case MotionEvent.ACTION_MOVE:
                        break;

                    case MotionEvent.ACTION_UP:
                        break;
                }
                return false;
            }
        });
    }
}
    /* 1st event
    public void onClick(View view) {

        tv.setText(et.getText());
        et.setText("");
    }*/

   /*2nd event
   class MyClick implements View.OnClickListener {

        public void onClick(View view) {

            tv.setText(et.getText());
        }
    }*/

   /* 3rd event
      bt.setOnClickListener(new View.OnClickListener() {

           @Override
           public void onClick(View view) {

           }
       });*/

   /* 4th event
   xml Onclick method
   */


