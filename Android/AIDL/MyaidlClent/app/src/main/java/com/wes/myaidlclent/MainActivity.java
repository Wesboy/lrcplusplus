package com.wes.myaidlclent;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import com.wes.myaidltest.IAIDLInterface;


public class MainActivity extends AppCompatActivity {

    private IAIDLInterface mAIDLInterface;

    private ServiceConnection serviceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
            mAIDLInterface = IAIDLInterface.Stub.asInterface(iBinder);
            Log.i("clientAIDL", "onServiceConnected");
            try {
//            int res = mAIDLInterface.getPid();
                if(mAIDLInterface != null)
                    Log.i("clientAIDL", "bindService:" + mAIDLInterface.getSum(3, 4));
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            Log.i("clientAIDL", "onServiceDisconnected");
            mAIDLInterface = null;

        }
    };



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initService();
    }

    private void initService()
    {
        Intent intent = new Intent();
        intent.setAction(IAIDLInterface.class.getName());
        intent.setPackage("com.wes.myaidltest");
        boolean ret = bindService(intent, serviceConnection, BIND_AUTO_CREATE);
        Log.i("clientAIDL", "bindService:" + ret);

//        try {
////            int res = mAIDLInterface.getPid();
//            if(mAIDLInterface != null)
//                Log.i("clientAIDL", "bindService:" + mAIDLInterface.getSum(3, 4));
//        } catch (RemoteException e) {
//            e.printStackTrace();
//        }
    }

}