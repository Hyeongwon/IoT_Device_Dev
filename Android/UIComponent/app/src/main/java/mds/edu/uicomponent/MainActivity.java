package mds.edu.uicomponent;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    TextView tv;
    Button bt;
    EditText et;
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tv = (TextView)findViewById(R.id.first_TextView);
        tv.setText("Hello");

        bt = (Button)findViewById(R.id.first_button);

        et = (EditText)findViewById(R.id.first_edit);

        bt.setOnClickListener(this);

    }

    @Override
    public void onClick(View view) {

        tv.setText(et.getText());
        et.setText("");
    }
}

