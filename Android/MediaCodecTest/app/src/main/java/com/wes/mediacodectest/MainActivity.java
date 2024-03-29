package com.wes.mediacodectest;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void file(View view) {
        startActivity(new Intent(this, FileActivity.class));
    }

    public void byteclick(View view) {
        startActivity(new Intent(this, StreamActivity.class));
    }

    public void MediaCodecClick(View view) {
        startActivity(new Intent(this, MediaCodecActivity.class));
    }

    public void openSL(View view) {
        startActivity(new Intent(this, OpenSLActivity.class));

    }
}