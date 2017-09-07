package edu.mds.network.ble_scan;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.IBinder;

public class MyService extends Service {
    public MyService() {
    }

    MediaPlayer player;

    @Override
    public void onCreate() {

        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        if(player != null) {
            player.stop();
            player.release();
        }

        player = MediaPlayer.create(this, R.raw.song);
        player.setLooping(false);
        player.start();
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {

        super.onDestroy();

        if(player != null) {
            player.stop();
            player.release();
        }

        player = MediaPlayer.create(this, R.raw.song);
        player.setLooping(false);
        player.start();
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }
}
