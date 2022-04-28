package com.wes.myjnitest;

public class TestUtil {
    private static final String TAG = TestUtil.class.getSimpleName();

    static {
        System.loadLibrary("wTest");
    }


    public native int myInit(int nsInstance);

    public native int myRead(byte[] rData);

    public native int myWrite(byte[] wData);

}
