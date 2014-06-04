package be.pxl.mecrobcontrol.ble;

import android.annotation.TargetApi;
import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;


public class ControlActivity extends Activity {
    private BluetoothAdapter mBluetoothAdapter = null;
    private static BluetoothSerialService mSerialService = null;
    private MenuItem mMenuItemConnect;
    private String mConnectedDeviceName = null;
    //private static InputMethodManager mInputManager;
    // Message types sent from the BluetoothReadService Handler
    public static final int MESSAGE_STATE_CHANGE = 1;
    public static final int MESSAGE_READ = 2;
    public static final int MESSAGE_WRITE = 3;
    public static final int MESSAGE_DEVICE_NAME = 4;
    public static final int MESSAGE_TOAST = 5;
    private static final int REQUEST_CONNECT_DEVICE = 1;
    private static final int REQUEST_ENABLE_BT = 2;
    //private int mIncomingEoL_0D = 0x0D;
    //private int mIncomingEoL_0A = 0x0A;
    private int mOutgoingEoL_0D = 0x0D;
    private int mOutgoingEoL_0A = 0x0A;
    private boolean mEnablingBT;
    private boolean isGo = false;
    private Button btnGo;

    // Key names received from the BluetoothChatService Handler
    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        if (mBluetoothAdapter == null) {
            finishDialogNoBluetooth();
            return;
        }
        mSerialService = new BluetoothSerialService(this, mHandlerBT);//, mEmulatorView);
        //mInputManager = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        //final Button btnGo = (Button) findViewById(R.id.btnGo);
        final Button btnForward = (Button) findViewById(R.id.btnForward);
        final Button btnBack = (Button) findViewById(R.id.btnBack);
        final Button btnStrafeLeft = (Button) findViewById(R.id.btnStrafeLeft);
        final Button btnStrafeRight = (Button) findViewById(R.id.btnStrafeRight);
        final Button btnCCW = (Button) findViewById(R.id.btnCCW);
        final Button btnCW = (Button) findViewById(R.id.btnCW);
        final Button btnDDL = (Button) findViewById(R.id.btnDiagDownLeft);
        final Button btnDDR = (Button) findViewById(R.id.btnDiagDownRight);
        final Button btnDUL = (Button) findViewById(R.id.btnDiagUpLeft);
        final Button btnDUR = (Button) findViewById(R.id.btnDiagUpRight);
        btnGo = (Button) findViewById(R.id.btnGo);

        btnGo.setOnTouchListener(onTouchListener);
        btnForward.setOnTouchListener(onTouchListener);
        btnBack.setOnTouchListener(onTouchListener);
        btnStrafeRight.setOnTouchListener(onTouchListener);
        btnStrafeLeft.setOnTouchListener(onTouchListener);
        btnCCW.setOnTouchListener(onTouchListener);
        btnCW.setOnTouchListener(onTouchListener);
        btnDDL.setOnTouchListener(onTouchListener);
        btnDDR.setOnTouchListener(onTouchListener);
        btnDUL.setOnTouchListener(onTouchListener);
        btnDUR.setOnTouchListener(onTouchListener);

        final SeekBar sk=(SeekBar) findViewById(R.id.skbSpeed);
        sk.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress,boolean fromUser) {
                Toast.makeText(getApplicationContext(), String.valueOf(progress),Toast.LENGTH_LONG).show();
                byte[] bufferke = new byte[1];
                switch(progress){
                    case 0:
                        bufferke[0] = (byte)'1';
                        break;
                    case 1:
                        bufferke[0] = (byte)'2';
                        break;
                    case 2:
                        bufferke[0] = (byte)'3';
                        break;
                }
                send(bufferke);
            }
        });
    }
    private View.OnTouchListener onTouchListener = new View.OnTouchListener() {
        @Override
        public boolean onTouch(View v, MotionEvent event) {
            byte[] buffer = new byte[1];
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                switch (v.getId()) {
                    case R.id.btnGo:
                        if(!isGo){
                            btnGo.setText("Stop");
                            isGo=!isGo;
                            //Toast.makeText(getApplicationContext(), "GO",
                              //      Toast.LENGTH_LONG).show();
                            buffer[0] = (byte)'m';
                            send( buffer );
                        }else{
                            btnGo.setText("Start");
                            isGo=!isGo;
                            //Toast.makeText(getApplicationContext(), "STOP",
                              //      Toast.LENGTH_LONG).show();
                            buffer[0] = (byte)'x';
                            send( buffer );
                        }

                        break;
                    case R.id.btnForward:
                        //Toast.makeText(getApplicationContext(), "Vooruit",
                          //      Toast.LENGTH_LONG).show();
                        buffer[0] = (byte)'z';
                        send( buffer );
                        break;
                    case R.id.btnStrafeLeft:
                        //Toast.makeText(getApplicationContext(), "Strafe Left",
                          //      Toast.LENGTH_LONG).show();
                        buffer[0] = (byte) 'q';
                        send(buffer);
                        break;
                    case R.id.btnStrafeRight:
                        //Toast.makeText(getApplicationContext(), "Strafe Right",
                          //      Toast.LENGTH_LONG).show();
                        buffer[0] = (byte)'d';
                        send( buffer );
                        break;
                    case R.id.btnBack:
                        //Toast.makeText(getApplicationContext(), "Terug",
                          //      Toast.LENGTH_LONG).show();
                        buffer[0] = (byte)'s';
                        send( buffer );
                        break;
                    case R.id.btnCCW:
                       // Toast.makeText(getApplicationContext(), "CCW",
                         //       Toast.LENGTH_LONG).show();
                        buffer[0] = (byte)'w';
                        send( buffer );
                        break;
                    case R.id.btnCW:
                        //Toast.makeText(getApplicationContext(), "CW",
                          //      Toast.LENGTH_LONG).show();
                        buffer[0] = (byte)'c';
                        send( buffer );
                        break;
                    case R.id.btnDiagDownLeft:
                        //Toast.makeText(getApplicationContext(), "DLB",
                          //      Toast.LENGTH_LONG).show();
                        buffer[0] = (byte)'v';
                        send( buffer );
                        break;
                    case R.id.btnDiagDownRight:
                        //Toast.makeText(getApplicationContext(), "DRB",
                          //      Toast.LENGTH_LONG).show();
                        buffer[0] = (byte)'n';
                        send( buffer );
                        break;
                    case R.id.btnDiagUpLeft:
                        //Toast.makeText(getApplicationContext(), "DLU",
                          //      Toast.LENGTH_LONG).show();
                        buffer[0] = (byte)'t';
                        send( buffer );
                        break;
                    case R.id.btnDiagUpRight:
                        //Toast.makeText(getApplicationContext(), "DRU",
                          //      Toast.LENGTH_LONG).show();
                        buffer[0] = (byte)'u';
                        send( buffer );
                        break;
                }
            } else if (event.getAction() == MotionEvent.ACTION_UP) {
                if(v.getId()!=R.id.btnGo) {
                   // Toast.makeText(getApplicationContext(), "gelost",
                     //       Toast.LENGTH_LONG).show();
                    buffer[0] = (byte) 'x';
                    send(buffer);
                }
            }
            return false;
        }
    };

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.control, menu);
        mMenuItemConnect = menu.getItem(0);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        //int id = item.getItemId();
        switch(item.getItemId()){
            case R.id.menu_info:
                Toast.makeText(getApplicationContext(), "App created by PXL",
                        Toast.LENGTH_LONG).show();
                return true;
            case R.id.connect:
                if (getConnectionState() == BluetoothSerialService.STATE_NONE) {
                    // Launch the DeviceListActivity to see devices and do scan
                    Intent serverIntent = new Intent(this, DeviceListActivity.class);
                    startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE);
                }
                else
                if (getConnectionState() == BluetoothSerialService.STATE_CONNECTED) {
                    mSerialService.stop();
                    mSerialService.start();
                }
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    public void finishDialogNoBluetooth() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(R.string.alert_dialog_no_bt)
                .setIcon(android.R.drawable.ic_dialog_info)
                .setTitle(R.string.app_name)
                .setCancelable( false )
                .setPositiveButton(R.string.alert_dialog_ok, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        finish();
                    }
                });
        AlertDialog alert = builder.create();
        alert.show();
    }
    private final Handler mHandlerBT = new Handler() {

        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MESSAGE_STATE_CHANGE:
                    switch (msg.arg1) {
                        case BluetoothSerialService.STATE_CONNECTED:
                            if (mMenuItemConnect != null) {
                                mMenuItemConnect.setIcon(android.R.drawable.ic_menu_close_clear_cancel);
                                mMenuItemConnect.setTitle(R.string.disconnect);
                            }

                            Toast.makeText(getApplicationContext(), getString(R.string.toast_connected_to) + " "
                                    + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
                            break;

                        case BluetoothSerialService.STATE_CONNECTING:
                            Toast.makeText(getApplicationContext(), getString(R.string.toast_connecting),
                                    Toast.LENGTH_SHORT).show();
                            break;

                        case BluetoothSerialService.STATE_LISTEN:
                        case BluetoothSerialService.STATE_NONE:
                            if (mMenuItemConnect != null) {
                                mMenuItemConnect.setIcon(android.R.drawable.ic_menu_search);
                                mMenuItemConnect.setTitle(R.string.connect);
                            }
                            break;
                    }
                    break;

                case MESSAGE_DEVICE_NAME:
                    // save the connected device's name
                    mConnectedDeviceName = msg.getData().getString(DEVICE_NAME);
                    Toast.makeText(getApplicationContext(), getString(R.string.toast_connected_to) + " "
                            + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
                    break;
                case MESSAGE_TOAST:
                    Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST), Toast.LENGTH_SHORT).show();
                    break;
            }
        }
    };

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {

            case REQUEST_CONNECT_DEVICE:

                // When DeviceListActivity returns with a device to connect
                if (resultCode == Activity.RESULT_OK) {
                    // Get the device MAC address
                    String address = data.getExtras()
                            .getString(DeviceListActivity.EXTRA_DEVICE_ADDRESS);
                    // Get the BluetoothDevice object
                    BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
                    // Attempt to connect to the device
                    mSerialService.connect(device);
                }
                break;

            case REQUEST_ENABLE_BT:
                // When the request to enable Bluetooth returns
                if (resultCode != Activity.RESULT_OK) {
                    finishDialogNoBluetooth();
                }
        }
    }

    public int getConnectionState() {
        return mSerialService.getState();
    }
    public void send(byte[] out) {

        if ( out.length == 1 ) {
            if ( out[0] == 0x0D ) {
                out = handleEndOfLineChars( mOutgoingEoL_0D );
            }
            else {
                if ( out[0] == 0x0A ) {
                    out = handleEndOfLineChars( mOutgoingEoL_0A );
                }
            }
        }

        if ( out.length > 0 ) {
            mSerialService.write( out );
        }
    }
    private byte[] handleEndOfLineChars( int outgoingEoL ) {
        byte[] out;

        if ( outgoingEoL == 0x0D0A ) {
            out = new byte[2];
            out[0] = 0x0D;
            out[1] = 0x0A;
        }
        else {
            if ( outgoingEoL == 0x00 ) {
                out = new byte[0];
            }
            else {
                out = new byte[1];
                out[0] = (byte)outgoingEoL;
            }
        }

        return out;
    }
    @Override
    public void onDestroy() {
        super.onDestroy();

        if (mSerialService != null)
            mSerialService.stop();

    }
    @Override
    public void onStart() {
        super.onStart();
        mEnablingBT = false;
    }

    @Override
    public synchronized void onResume() {
        super.onResume();

        if (!mEnablingBT) { // If we are turning on the BT we cannot check if it's enable
            if ( (mBluetoothAdapter != null)  && (!mBluetoothAdapter.isEnabled()) ) {

                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setMessage(R.string.alert_dialog_turn_on_bt)
                        .setIcon(android.R.drawable.ic_dialog_alert)
                        .setTitle(R.string.alert_dialog_warning_title)
                        .setCancelable( false )
                        .setPositiveButton(R.string.alert_dialog_yes, new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                mEnablingBT = true;
                                Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                                startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
                            }
                        })
                        .setNegativeButton(R.string.alert_dialog_no, new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                finishDialogNoBluetooth();
                            }
                        });
                AlertDialog alert = builder.create();
                alert.show();
            }

            if (mSerialService != null) {
                // Only if the state is STATE_NONE, do we know that we haven't started already
                if (mSerialService.getState() == BluetoothSerialService.STATE_NONE) {
                    // Start the Bluetooth services
                    mSerialService.start();
                }
            }
        }
    }

}
