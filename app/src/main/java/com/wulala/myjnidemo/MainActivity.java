package com.wulala.myjnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.wulala.myjnidemo.databinding.ActivityMainBinding;
import com.wulala.myjnidemo.entity.Person;

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

    Person[] persons = new Person[10];
    Person p = new Person();

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
                binding.numberText.setText(numberTextNumber + "");
            }
        });

        binding.callJavaInCBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                callJavaMethod();
            }
        });

        p.setAge(11);
        p.setName("Lee");
        p.setSex(1);

        persons[0] = p;
        Log.d(TAG, "Person[" + 0 + "]: " + persons[0].getName() + " is " + persons[0].getAge());

        binding.changeArrayItem0Btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                changePersonZero(p);
                Log.d(TAG, "person name changed to " + p.getName());
            }
        });

        binding.createObjInCBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Person p = createPerson();
                Log.d(TAG, "P created: " + p.toString());
            }
        });
    }

    public void onChangeBtnClick() {
        Log.d(TAG, "onChangeBtnClick: yes!");
        changeText();
        tv.setText(centerText);
    }

    public void callByC() {
        Log.d(TAG, "Call by C");
    }

    public native Person createPerson();

    public native void changePersonZero(Person person);

    public native void callJavaMethod();

    public native int plusOne(int number);

    public native void changeText();

    public native String stringFromJNI();

}