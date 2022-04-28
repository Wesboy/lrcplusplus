package com.wes.myjnitest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    private final String TAG = "JNITest";
    private TestUtil mTestUtil = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTestUtil = new TestUtil();
        mTestUtil.myInit(1);

        byte[] test = new byte[100];
        for(byte i = 0 ; i < 100; i++)
        {
            test[i] = i;
        }
        Log.i(TAG, "jni write : "+ test[6]);
        mTestUtil.myWrite(test);
        mTestUtil.myRead(test);
        Log.i(TAG, "jni read : "+ test[6]);
    }
}