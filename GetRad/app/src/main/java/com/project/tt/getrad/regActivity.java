package com.project.tt.getrad;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.text.TextUtils;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

/**
 * Created by Tt-01 on 2016/1/2.
 */
public class regActivity extends Activity{
    private int P_ID = 0;
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.reg);
        TelephonyManager tm = (TelephonyManager)getSystemService(Context.TELEPHONY_SERVICE);
        String DEVICE_ID = tm.getDeviceId();
        TextView Pid = (TextView)findViewById(R.id.PhoneId);
        for(int i =0;i<3;i++){
            String temp = DEVICE_ID.substring(i*5+0,i*5+4);
            int t = Integer.parseInt(temp);
            P_ID+=t;
        }
        Pid.setText(P_ID+"");
    }
    public void reg(View v){
        int temp = 0 ;
        temp = P_ID^11111;
        //Toast.makeText(this, temp+"", Toast.LENGTH_SHORT).show();
        EditText et = (EditText)findViewById(R.id.regId);
        if(TextUtils.isEmpty(et.getText().toString())){
            Toast.makeText(this, "请输入注册码", Toast.LENGTH_SHORT).show();
            return;
        }
        else {
            String id = et.getText().toString();
            if(id.equals(temp+"")){
                Toast.makeText(this, "注册成功", Toast.LENGTH_SHORT).show();
                SharedPreferences sp = getSharedPreferences("data", MODE_PRIVATE);
                SharedPreferences.Editor ed = sp.edit();
                ed.putBoolean("reg", true);
                ed.commit();
                restartApplication();
            }
            else{
                Toast.makeText(this, "注册码错误", Toast.LENGTH_SHORT).show();
            }
        }
    }
    private void restartApplication() {
        final Intent intent = getPackageManager().getLaunchIntentForPackage(getPackageName());
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(intent);
    }
}
