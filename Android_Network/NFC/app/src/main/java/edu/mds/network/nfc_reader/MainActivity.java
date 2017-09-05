package edu.mds.network.nfc_reader;

import android.app.Activity;
import android.content.Intent;
import android.nfc.NdefMessage;
import android.nfc.NdefRecord;
import android.nfc.NfcAdapter;
import android.os.Bundle;
import android.os.Parcelable;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

    TextView infoTv;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        infoTv = findViewById(R.id.infTv);

        Intent i = getIntent();
        String action = i.getAction();
        //infoTv.setText(action);
        processIntent(i);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
    }

    private void processIntent(Intent i) {

        if (i != null && NfcAdapter.ACTION_NDEF_DISCOVERED.equals(i.getAction())) {

            Parcelable[] rawMessages =
                    i.getParcelableArrayExtra(NfcAdapter.EXTRA_NDEF_MESSAGES);
            NdefMessage ndefMsg = (NdefMessage) rawMessages[0];
            NdefRecord[] recArr = ndefMsg.getRecords();
            NdefRecord textRecord = recArr[0];

            byte[] ndef_type = textRecord.getType();
            String text_type = new String(ndef_type);

            if(text_type.equals("U")) {

                String UriStr = textRecord.toUri().toString();
                infoTv.setText("Text Data : " + UriStr);

            } else if(text_type.equals("T")){

                byte[] byteArr = textRecord.getPayload();
                String textString = new String(byteArr, 3, byteArr.length-3);
                infoTv.setText("URL Data : " + textString);

            } else {

                infoTv.setText("Unknown Tag...!!!");
            }
        }
    }


    private void sendNdefMsg(String text) {

      /*  String testData = "test";
        NdefRecord textRecord = NdefRecord.createTextRecord(testData);

        NdefRecord[] recArr = new NdefRecord[]{textRecord};
        NdefMessage ndefMessage = new NdefMessage(recArr);

        Intent i = new Intent(NfcAdapter.ACTION_NDEF_DISCOVERED);
        i.putExtra(NfcAdapter.EXTRA_NDEF_MESSAGES, ndefMessage);

        startActivity(i);*/
    }
}
