package edu.mds.network.nfc_writer;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.FormatException;
import android.nfc.NdefMessage;
import android.nfc.NdefRecord;
import android.nfc.NfcAdapter;
import android.nfc.Tag;
import android.nfc.tech.Ndef;
import android.os.Parcelable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

import java.io.IOException;
import java.nio.charset.Charset;

public class NFCWriteActivity extends Activity {

    NfcAdapter nfcAdapter;
    PendingIntent pIntent;
    IntentFilter[] fillterArr;

    String type, url, text;
    NdefMessage ndefMsg;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_nfcwrite);

//        //TODO MainActivity 에서 전달된 인텐트에서 Type, data를 끄집어낸다.
        Intent i = getIntent();
        type = i.getExtras().getString("type");

        Toast.makeText(this, type, Toast.LENGTH_SHORT).show();
        if(type.equals("T")) {

            text = i.getExtras().getString("text");
            Toast.makeText(this, text, Toast.LENGTH_SHORT).show();
            ndefMsg = makeNdefMsg(type, text);

        } else if(type.equals("U")) {

            url = i.getExtras().getString("url");
            Toast.makeText(this, url, Toast.LENGTH_SHORT).show();
            ndefMsg = makeNdefMsg(type, url);

        } else {

            Toast.makeText(this, "Unknown Type", Toast.LENGTH_SHORT).show();
            finish();
        }


        //TODO Foreground 모드 사용을 위한 코드 구현.
        //NFCAdapter, Intent, PendingIntent, Filter ... 생성 .. Tag Discovered
        nfcAdapter = NfcAdapter.getDefaultAdapter(this);
        if(nfcAdapter == null) {

            Toast.makeText(this, "This device does not support NFC ...!!!", Toast.LENGTH_SHORT).show();
            finish();
        }

        Intent intent = new Intent(this, this.getClass());
        intent.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        pIntent = PendingIntent.getActivity(this, 0, intent, PendingIntent.FLAG_CANCEL_CURRENT);

        IntentFilter tagFilter = new IntentFilter(NfcAdapter.ACTION_TAG_DISCOVERED);
        fillterArr = new IntentFilter[]{tagFilter};

    }

    @Override
    protected void onResume() {

        super.onResume();
        //TODO foreground function enable;
        nfcAdapter.enableForegroundDispatch(this, pIntent, fillterArr, null);
    }

    @Override
    protected void onNewIntent(Intent intent) {

        super.onNewIntent(intent);

        if (intent != null && NfcAdapter.ACTION_TAG_DISCOVERED.equals(intent.getAction())) {
            //TODO 1. Intent 에서 Tag 객체를 얻어온다...
            Tag detectedTag = intent.getParcelableExtra(NfcAdapter.EXTRA_TAG);

            //TODO 2. writeTagData() function call
            writeTagData(ndefMsg, detectedTag);
        }
    }

    @Override
    protected void onPause() {

        super.onPause();
        //TODO foreground function disable;
        nfcAdapter.disableForegroundDispatch(this);
    }

    private void writeTagData(NdefMessage ndefMsg, Tag tag) {

        Ndef ndef = Ndef.get(tag);

        if(ndef != null) {

            try {

                ndef.connect();

                if(!ndef.isWritable()) {
                    Toast.makeText(this, "This device does not support .. !!!", Toast.LENGTH_SHORT).show();
                    return;
                }

                int dataSize = ndefMsg.getByteArrayLength();

                if(dataSize > ndef.getMaxSize()) {

                    Toast.makeText(this, "Data Size is  .. !!!", Toast.LENGTH_SHORT).show();
                    return;
                }

                Toast.makeText(this, "Start Writing action ...!!!", Toast.LENGTH_SHORT).show();
                ndef.writeNdefMessage(ndefMsg);
                Toast.makeText(this, "Done Writing action ...!!!", Toast.LENGTH_SHORT).show();

            } catch (IOException e) {

                e.printStackTrace();

            } catch (FormatException e) {

                e.printStackTrace();
            }

        }
    }

    private NdefMessage makeNdefMsg(String type, String rawData) {

        if(type.equals("T")) {

            NdefRecord textRecord = NdefRecord.createTextRecord("en", rawData);
            NdefRecord aarR = NdefRecord.createApplicationRecord("edu.mds.network.nfc_writer");

            return new NdefMessage(new NdefRecord[] {textRecord, aarR});

        } else if(type.equals("U")){

            NdefRecord uriRecord = NdefRecord.createUri(rawData);

            return new NdefMessage(new NdefRecord[] {uriRecord});

        } else {

            return null;
        }
    }
}
