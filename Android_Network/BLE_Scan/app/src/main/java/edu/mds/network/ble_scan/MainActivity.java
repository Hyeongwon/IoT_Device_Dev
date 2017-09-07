package edu.mds.network.ble_scan;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.util.List;
import java.util.UUID;

public class MainActivity extends Activity {

    EditText macEt;
    TextView infoTv;

    BluetoothAdapter bluetoothAdapter;
    String myMacAddress;
    BluetoothDevice bluetoothDev;
    BluetoothGatt bluetoothGatt;

    UUID UUID_KEY_SERV = UUID
            .fromString("0000ffe0-0000-1000-8000-00805f9b34fb");
    UUID UUID_KEY_DATA = UUID
            .fromString("0000ffe1-0000-1000-8000-00805f9b34fb");

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        macEt = (EditText) findViewById(R.id.macEtext);
        infoTv = (TextView) findViewById(R.id.infoTv);

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        if(bluetoothAdapter == null) {

            Toast.makeText(this, "This device does not support bluetooth ...!!!", Toast.LENGTH_SHORT).show();
            finish();
        }
    }

    @Override
    protected void onResume() {

        super.onResume();

        if(!bluetoothAdapter.isEnabled()) {

            Intent i = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(i, 0);
        }
    }

    @Override
    protected void onPause() {

        super.onPause();
        bluetoothAdapter.stopLeScan(leScanCallback);
    }

    public void startScan(View view) {

        myMacAddress = macEt.getText().toString().trim();
        bluetoothAdapter.startLeScan(leScanCallback);
        infoTv.append("\n startScan...!!!");
    }

    public void stopScan(View view) {

        bluetoothAdapter.stopLeScan(leScanCallback);
        infoTv.append("\n stopScan...!!!");

    }

    BluetoothAdapter.LeScanCallback leScanCallback = new BluetoothAdapter.LeScanCallback() {
        @Override
        public void onLeScan(BluetoothDevice bluetoothDevice, int rssi, byte[] scanRecords) {

            Log.e("info", "-----------------------" + bluetoothDevice.getAddress());

            if(myMacAddress.equals(bluetoothDevice.getAddress())) {

                Log.w("info", "-----------------------" + bluetoothDevice.getAddress());
                bluetoothDev = bluetoothDevice;
                infoTv.append("\n My BLE Device : " + bluetoothDevice.getAddress());
                bluetoothAdapter.stopLeScan(leScanCallback);
            }
        }
    };

    public void conGattServer(View view) {

        bluetoothGatt = bluetoothDev.connectGatt(this, false, gattCallback);
    }

    BluetoothGattCallback gattCallback = new BluetoothGattCallback() {

        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {

            super.onConnectionStateChange(gatt, status, newState);

            if(newState == BluetoothProfile.STATE_CONNECTED) {

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {

                        Log.e("info : ", "Gatt Server Connected...!!!" + Thread.currentThread().getName());
                        infoTv.append("\n Gatt Server Connected...!!!");
                        bluetoothGatt.discoverServices();
                    }
                });

            } else if(newState == BluetoothProfile.STATE_DISCONNECTED) {

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {

                        Log.e("info : ", "Gatt Server disconnected...!!!");
                        infoTv.append("\n Gatt Server disconnected...!!!");
                    }
                });
            }
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {

            super.onServicesDiscovered(gatt, status);
            enableKeyEvent();
            /*
            List<BluetoothGattService>gattServiceList = gatt.getServices();

            for(BluetoothGattService sev : gattServiceList) {

                Log.e("info", "---------------- " + sev.getUuid());
                List<BluetoothGattCharacteristic> bgcList = sev.getCharacteristics();

                for(BluetoothGattCharacteristic bgc : bgcList) {

                    Log.e("Characteristic", "------ " + bgc.getUuid());
                }
            }
            */
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {

            super.onCharacteristicRead(gatt, characteristic, status);
        }

        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {

            super.onCharacteristicWrite(gatt, characteristic, status);
        }

        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {

            super.onCharacteristicChanged(gatt, characteristic);
            getCharacteristic(characteristic);
        }
    };

    private void enableKeyEvent() {
        BluetoothGattCharacteristic c = null;
        c = bluetoothGatt.getService(UUID_KEY_SERV).getCharacteristic(UUID_KEY_DATA);
        bluetoothGatt.setCharacteristicNotification(c, true);

        BluetoothGattDescriptor descriptor = c.getDescriptor(UUID
                .fromString("00002902-0000-1000-8000-00805f9b34fb"));

        if (descriptor != null) {
            byte[] val = BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE;
            descriptor.setValue(val);
            bluetoothGatt.writeDescriptor(descriptor);
        }

    }
    String value;
    public void getCharacteristic(BluetoothGattCharacteristic ch) {
        if (bluetoothAdapter == null || bluetoothGatt == null || ch == null) {
            return;
        }
        UUID uuid = ch.getUuid();

        byte[] rawValue = ch.getValue();

        value = Conversion.BytetohexString(rawValue, rawValue.length);
        Log.e("info", "value : " + value);
        runOnUiThread(new Runnable() {

            @Override
            public void run() {
                // TODO Auto-generated method stub
                if(value.equals("01")) {

                    infoTv.append("\n Play...!!!");
                    startService(new Intent(MainActivity.this, MyService.class));
                } else if(value.equals("02")) {

                    infoTv.append("\n Stop...!!!");
                    stopService(new Intent(MainActivity.this, MyService.class));
                } else if(value.equals("03")) {

                    infoTv.append("\n Continue...!!!");
                }
            }
        });
    }
}
