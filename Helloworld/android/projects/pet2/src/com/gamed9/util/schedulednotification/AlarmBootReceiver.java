package com.gamed9.util.schedulednotification;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class AlarmBootReceiver extends BroadcastReceiver {
    private static final String TAG = "zdbg.AlarmBootReceiver";

    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "onReceive action:" + intent.getAction());
        if (intent.getAction().equals(Intent.ACTION_SHUTDOWN)) {
        } else if (intent.getAction().equals(Intent.ACTION_BOOT_COMPLETED)) {
            // Restore alarm
            Log.d(TAG, "onReceive bootcomplete update records");
            NotificationMgr.init(context);
            NotificationMgr.updateTimerRecords();
        }
    }
}
