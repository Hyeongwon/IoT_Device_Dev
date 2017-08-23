package paint.mds.edu.mypaint;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Toast;

import java.util.ArrayList;

class Point {

    float x;
    float y;
    boolean isDraw;

    public Point(float x, float y, boolean isDraw) {

        this.x = x;
        this.y = y;
        this.isDraw = isDraw;
    }
}

public class MyView extends View {

    private Context context;
    String msg;
    //private float startX, startY, stopX, stopY;

    ArrayList<Point> list = new ArrayList<Point>();

    public MyView(Context context, AttributeSet attrs) {

        super(context, attrs);
        this.context = context;

        msg = attrs.getAttributeValue(null, "value");

        this.setOnTouchListener(new OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent event) {

                switch (event.getAction()) {

                    case MotionEvent.ACTION_DOWN:

                        //startX = stopX = event.getX();
                        list.add(new Point(event.getX(), event.getY(), false));
                        invalidate();

                        return true;

                    case MotionEvent.ACTION_MOVE:

//                        startX = stopX;
//                        stopX = event.getX();
//                        startY = stopY;
//                        stopY = event.getY();
                        list.add(new Point(event.getX(), event.getY(), true));
                        invalidate();

                        return true;

                    case MotionEvent.ACTION_UP:

//                        startX = stopX;
//                        stopX = event.getX();
//                        startY = stopY;
//                        stopY = event.getY();
                        list.add(new Point(event.getX(), event.getY(), true));
                        invalidate();

                        return true;
                }
                return false;
            }
        });
    }

    public void show_toast(String msg) {

        Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onDraw(Canvas canvas) {

        super.onDraw(canvas);
        Paint p = new Paint();
        p.setColor(Color.RED);
        p.setStrokeWidth(3);
        canvas.drawText(msg, 100, 100, p);

        for(int i = 0; i < list.size(); i++) {

            if(list.get(i).isDraw)
                canvas.drawLine(list.get(i-1).x, list.get(i-1).y, list.get(i).x, list.get(i).y, p);
        }
    }
}