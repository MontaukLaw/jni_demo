package com.wulala.myjnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.wulala.myjnidemo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    static {
        System.loadLibrary("myjnidemo");
    }

    private ActivityMainBinding binding;
    TextView tv;
    TextView numberTextView;
    String centerText = "Oh yeah";

    int numberTextNumber = 2;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        tv = binding.sampleText;
        tv.setText(stringFromJNI());

        numberTextView = binding.numberText;
        numberTextView.setText(numberTextNumber + "");

        Button changeBtn = binding.changeBtn;
        changeBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onChangeBtnClick();
            }
        });

        binding.plusOneBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                numberTextNumber = plusOne(numberTextNumber);  // 重新赋值
                binding.numberText.setText(numberTextNumber+ "");
            }
        });
    }

    public void onChangeBtnClick() {
        Log.d(TAG, "onChangeBtnClick: yes!");
        changeText();
        tv.setText(centerText);
    }

    public native int plusOne(int number);

    public native void changeText();

    public native String stringFromJNI();

}