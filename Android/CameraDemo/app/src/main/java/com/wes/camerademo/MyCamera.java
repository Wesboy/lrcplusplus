package com.wes.camerademo;

import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

import java.io.IOException;

public class MyCamera implements SurfaceHolder.Callback{

    private final String TAG = "Mycamera";
    private Camera mCamera;
    private boolean hasPermission = false;
    private SurfaceHolder mSurfaceHolder;
    private int cameraNum = 0;

    MyCamera(Context context, SurfaceView mSurfaceView)
    {
        hasPermission = checkCameraHardware(context);
        mSurfaceHolder = mSurfaceView.getHolder();
        mSurfaceHolder.addCallback(this);
    }

    /** Check if this device has a camera */
    private boolean checkCameraHardware(Context context) {

        if (context.getPackageManager().hasSystemFeature(PackageManager.FEATURE_CAMERA)){
            // this device has a camera
            return true;
        } else {
            // no camera on this device
            return false;
        }
    }

    public void openCamera()
    {
        cameraNum = Camera.getNumberOfCameras();
        Log.i(TAG, "num:" + cameraNum);
        if(hasPermission)
        {
            mCamera = Camera.open(0);
        }
    }

    public void startPerview(SurfaceView sv) throws IOException {
        mCamera.stopPreview();
        mCamera.setPreviewDisplay(sv.getHolder());
        mCamera.startPreview();
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder surfaceHolder) {

    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder surfaceHolder, int i, int i1, int i2) {

        try {
            mCamera.setPreviewDisplay(surfaceHolder);
        } catch (IOException e) {
            e.printStackTrace();
        }
        mCamera.startPreview();
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder surfaceHolder) {
        mCamera.stopPreview();
        mCamera.release();
        mCamera = null;
    }
}
