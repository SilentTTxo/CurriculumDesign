package com.project.tt.getrad;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.text.TextUtils;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private int num = -1;
    private SharedPreferences sp;
    private boolean zc;
    private boolean debug = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        sp = getSharedPreferences("data", MODE_PRIVATE);
        if(debug){
            SharedPreferences.Editor ed = sp.edit();
            ed.putBoolean("reg",false);
            ed.putInt("num",5);
            ed.commit();
        }
        zc =sp.getBoolean("reg", false);
        if(!zc){
            num = sp.getInt("num",0);
        }
    }
    public void count(View v){
        ((InputMethodManager)getSystemService(INPUT_METHOD_SERVICE)).hideSoftInputFromWindow(this.getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
        int w,h;
        EditText Width = (EditText) findViewById(R.id.Width);
        EditText Height = (EditText) findViewById(R.id.Height);
        if(num == 0 && !zc){
            Toast.makeText(this, "试用已结束，请购买注册", Toast.LENGTH_SHORT).show();
            Intent intent = new Intent(this,regActivity.class);
            startActivity(intent);
            return;
        }
        if(!TextUtils.isEmpty(Width.getText().toString())&&!TextUtils.isEmpty(Height.getText().toString())) {
            w = Integer.parseInt(Width.getText().toString());
            h = Integer.parseInt(Height.getText().toString());
            TextView ans = (TextView) findViewById(R.id.Ans);
            ans.setText("半径：" + ((w * w / (8 * h)) + h / 2));
            if(!zc){
                num--;
                Toast.makeText(this, "剩余试用次数:"+num, Toast.LENGTH_SHORT).show();
                SharedPreferences.Editor ed = sp.edit();
                ed.putInt("num",num);
                ed.commit();
            }
        }else{
            Toast.makeText(this, "请输入数据", Toast.LENGTH_SHORT).show();
        }
    }
}
