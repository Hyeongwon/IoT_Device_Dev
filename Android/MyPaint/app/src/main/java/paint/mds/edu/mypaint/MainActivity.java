package paint.mds.edu.mypaint;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends Activity {

    MyView m;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        m = (MyView) findViewById(R.id.my_view);

        m.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {

                m.show_toast("I got it...");
            }
        });
    }
}
