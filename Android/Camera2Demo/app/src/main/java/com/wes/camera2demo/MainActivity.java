package com.wes.camera2demo;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CaptureRequest;
import android.media.Image;
import android.media.ImageReader;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.nio.ByteBuffer;
import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    private CameraManager cameraManager;
    private String mCameraId = "20";
    private CameraDevice mCameraDevice;
    private final String TAG = "Camera2Demo";
    private ImageReader imageReader;
    private SurfaceView mSurfaceView;
    private SurfaceHolder surfaceHolder;
    private CameraCaptureSession cameraCaptureSession;
    private Handler cameraHandler;
    private CaptureRequest.Builder previewRequestBuilder;

    private final int width = 1920;
    private final int height = 1080;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mSurfaceView = findViewById(R.id.sfview);
        surfaceHolder = mSurfaceView.getHolder();
        cameraManager = (CameraManager) this.getSystemService(Context.CAMERA_SERVICE);

        mSurfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                //一定要先确定surfaceView的大小  然后开启摄像头  不然就会出现拉伸
                //todo 这里要动态的获取大小
//                mSurfaceView.setAspectRatio(1920, 1080);
//                view.post(()->initCamera());
                initCamera();

            }


            @Override
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {

            }
        });
    }


    void initCamera()
    {

        if(ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED)
        {
            return;
        }

        CameraDevice.StateCallback deviceCallback = new CameraDevice.StateCallback() {
            @Override
            public void onOpened(@NonNull CameraDevice cameraDevice) {
                mCameraDevice = cameraDevice;
                Log.i(TAG, "camera device " + mCameraDevice);
                try {
                    previewRequestBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
                    previewRequestBuilder.addTarget(imageReader.getSurface());
                    previewRequestBuilder.addTarget(surfaceHolder.getSurface());
                } catch (CameraAccessException e) {
                    e.printStackTrace();
                }

                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
                    try {
                        mCameraDevice.createCaptureSession(Arrays.asList(surfaceHolder.getSurface(), imageReader.getSurface()), new CameraCaptureSession.StateCallback(){
                            @Override
                            public void onConfigured(@NonNull CameraCaptureSession session) {

                                cameraCaptureSession = session;

                                CaptureRequest captureRequest = previewRequestBuilder.build();
                                try {
                                    cameraCaptureSession.setRepeatingRequest(captureRequest,null,cameraHandler);

                                } catch (CameraAccessException e) {

                                    Log.e(TAG,"cameraCaptureSession访问摄像头失败");
                                }
                            }
                            @Override
                            public void onConfigureFailed(@NonNull CameraCaptureSession session) {

                            }
                        },null);
                    } catch (CameraAccessException e) {
                        e.printStackTrace();
                    }
                }
            }

            @Override
            public void onDisconnected(@NonNull CameraDevice cameraDevice) {

            }

            @Override
            public void onError(@NonNull CameraDevice cameraDevice, int i) {
                Log.e(TAG, "camera open failed " + i);

            }
        };

        try {
            cameraManager.openCamera(mCameraId, deviceCallback, null);
            Log.i(TAG, "camera openCamera " );
        } catch (CameraAccessException e) {
            Log.e(TAG, "camera openCamera failed " );
            e.printStackTrace();
        }

        //imageReader
        imageReader = ImageReader.newInstance(width,height, ImageFormat.JPEG, 10);
        imageReader.setOnImageAvailableListener(reader -> {
            //取出最新的图片并清除队列里的旧图片
            Image image = reader.acquireLatestImage();
            //todo 对获取的图片进行操作

            //将图片转换成Bitmap
            ByteBuffer buffer = image.getPlanes()[0].getBuffer();
            byte[] bytes = new byte[buffer.remaining()];
            buffer.get(bytes);//由缓冲区存入字节数组

            final Bitmap bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);

            //释放资源
            image.close();
        },cameraHandler);
    }


}