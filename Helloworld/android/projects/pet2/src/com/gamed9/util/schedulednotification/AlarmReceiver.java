package com.gamed9.util.schedulednotification;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.SystemClock;
import android.util.Log;


public class AlarmReceiver extends BroadcastReceiver {
 private static final String TAG = "zdbg.AlarmReceiver";

@Override
 public void onReceive(Context context, Intent intent) {

     String id = intent.getStringExtra("id");

     Log.d(TAG, "AlarmReceiver onReceive " + (SystemClock.elapsedRealtime()/1000) + " id=" + id);
     NotificationMgr.init(context);
     NotificationMgr.onTrigger(id);
 }
}
