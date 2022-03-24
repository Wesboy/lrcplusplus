package com.wes.camerademo;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Camera;
import android.os.Bundle;
import android.view.SurfaceView;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    private MyCamera mCamera;
    private Button bt_swh;
    private Button bt_pic;
    private Button bt_rec;
    private TextView tvTil;
    private SurfaceView mCameraView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
        mCamera = new MyCamera(this, mCameraView);
        mCamera.openCamera();
//        try {
//            mCamera.startPerview(mCameraView);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
    }

    private void initView()
    {
        bt_pic = findViewById(R.id.bt_pic);
        bt_swh = findViewById(R.id.bt_switch);
        bt_rec = findViewById(R.id.bt_record);

        tvTil = findViewById(R.id.tv_title);
        mCameraView = findViewById(R.id.cameraView);

    }
}