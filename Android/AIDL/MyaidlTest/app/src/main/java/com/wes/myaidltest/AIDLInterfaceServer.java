package com.wes.myaidltest;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import com.wes.myaidltest.IAIDLInterface;

public class AIDLInterfaceServer extends Service {
    public AIDLInterfaceServer() {
    }

    public void onCreate(){
        Log.i("remote Server intface", "onCreate");
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.i("remote Server intface", "onBind");
        // TODO: Return the communication channel to the service.
        //throw new UnsupportedOperationException("Not yet implemented");
        return binder;
    }

    private final IAIDLInterface.Stub binder = new IAIDLInterface.Stub() {
        public int getSum(int a, int b)
        {
            return a+b;
        }

        public String getName()
        {
            return "test name";
        }

    };

}