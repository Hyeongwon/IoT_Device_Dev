package edu.mds.network.foreground_nfc_reader;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.NdefMessage;
import android.nfc.NdefRecord;
import android.nfc.NfcAdapter;
import android.os.Bundle;
import android.os.Parcelable;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

    NfcAdapter nfcAdapter;
    TextView infoTv;
    IntentFilter[] fillterArr;
    PendingIntent pIntent;

    private int count = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        infoTv = (TextView) findViewById(R.id.infoTv);
        nfcAdapter = NfcAdapter.getDefaultAdapter(this);

        if(nfcAdapter == null) {

            Toast.makeText(this, "This device does not support NFC ...!!!", Toast.LENGTH_SHORT).show();
            finish();
        }

        Intent i = new Intent(this, this.getClass());
        i.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        pIntent = PendingIntent.getActivity(this, 0, i, PendingIntent.FLAG_CANCEL_CURRENT);

        IntentFilter ndefD = new IntentFilter(NfcAdapter.ACTION_NDEF_DISCOVERED);
        IntentFilter ndefU1 = new IntentFilter(NfcAdapter.ACTION_NDEF_DISCOVERED);
        IntentFilter ndefU2 = new IntentFilter(NfcAdapter.ACTION_NDEF_DISCOVERED);

//        IntentFilter tagFillter = new IntentFilter(NfcAdapter.ACTION_TAG_DISCOVERED);
//        fillterArr = new IntentFilter[]{tagFillter};
        try {
            ndefD.addDataType("text/plain");
            ndefU1.addDataScheme("http");
            ndefU2.addDataScheme("https");
            fillterArr = new IntentFilter[]{};

        } catch (IntentFilter.MalformedMimeTypeException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onResume() {

        super.onResume();
        nfcAdapter.enableForegroundDispatch(this, pIntent, fillterArr, null);
    }

    @Override
    protected void onNewIntent(Intent intent) {

        super.onNewIntent(intent);

        String action = intent.getAction();
        count++;
        infoTv.setText(count + " : " + action);

        processIntent(intent);
    }

    @Override
    protected void onPause() {

        super.onPause();
        nfcAdapter.disableForegroundDispatch(this);
    }

    private void processIntent(Intent i) {

        if (i != null && NfcAdapter.ACTION_NDEF_DISCOVERED.equals(i.getAction()) ||
                NfcAdapter.ACTION_TAG_DISCOVERED.equals(i.getAction()) ||
                NfcAdapter.ACTION_TECH_DISCOVERED.equals(i.getAction())) {

            Parcelable[] rawMessages =
                    i.getParcelableArrayExtra(NfcAdapter.EXTRA_NDEF_MESSAGES);
            NdefMessage ndefMsg = (NdefMessage) rawMessages[0];
            NdefRecord[] recArr = ndefMsg.getRecords();
            NdefRecord textRecord = recArr[0];

            byte[] ndef_type = textRecord.getType();
            String text_type = new String(ndef_type);

            if(text_type.equals("U")) {

                String UriStr = textRecord.toUri().toString();
                infoTv.setText("URL Data : " + UriStr);

            } else if(text_type.equals("T")){

                byte[] byteArr = textRecord.getPayload();
                String textString = new String(byteArr, 3, byteArr.length-3);
                infoTv.setText("Text Data : " + textString);

            } else {

                infoTv.setText("Unknown Tag...!!!");
            }
        }
    }
}
