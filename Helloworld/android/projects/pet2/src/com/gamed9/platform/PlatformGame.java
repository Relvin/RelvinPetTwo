package com.gamed9.platform;


import java.util.Calendar;
import java.util.Map;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo.State;
import android.net.Uri;
import android.util.Log;

import com.gamed9.game.template.R;
import com.gamed9.util.schedulednotification.NotificationMgr;

public class PlatformGame {

    private static final String TAG = "PlatformGame";

    private static PlatformGame mPlatformGame;
    
    private static Activity mActivity;
    
    public static PlatformGame getInstance()
    {
        if(mPlatformGame == null)
        {
            mPlatformGame = new PlatformGame();
        }
        return mPlatformGame;
    }
    
    public void init(Activity activity)
    {
        Log.d(TAG, "init");

        mActivity = activity;
        
        // 
        NotificationMgr.init(mActivity);
    }
    
    public void onResume()
    {
        Log.d(TAG, "onResume");
    }
    
    public void onPause()
    {
        Log.d(TAG, "onPause");
    }
    
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
    }
    
    public void onDestroy()
    {
        Log.d(TAG, "onDestroy");

        mActivity = null;
    }
    
    public static String jniGetDeviceId()
    {
        String devId = UtilGame.getDeviceId(mActivity);
        Log.d(TAG, "jniGetDeviceId " + devId);
        return devId;
    }
    
    public static String jniGetDeviceIdType()
    {
        String devIdType = UtilGame.getDeviceIdType(mActivity);
        Log.d(TAG, "jniGetDeviceIdType " + devIdType);
        return devIdType;
    }

    public static int jniGetAccountChannel()
	{
        try {
            ApplicationInfo appInfo = mActivity.getPackageManager().getApplicationInfo(mActivity.getPackageName(), PackageManager.GET_META_DATA);
            int channel = appInfo.metaData.getInt("CLIENT_CHANNEL");
			Log.d(TAG, "jniGetAccountChannel:channel=" + channel);
            return channel;
        } catch (Exception e) {
            e.printStackTrace();
        }
		return 0;
	}

    public static int jniGetNetworkState()
	{
	    if(mActivity == null)
	    {
	        return 0;
	    }
        ConnectivityManager conMan = (ConnectivityManager) mActivity.getSystemService(Context.CONNECTIVITY_SERVICE);

        State mobile = conMan.getNetworkInfo(ConnectivityManager.TYPE_MOBILE).getState();
        State wifi = conMan.getNetworkInfo(ConnectivityManager.TYPE_WIFI).getState();
        
        int state = (wifi==State.CONNECTED || mobile == State.CONNECTED) ? 1 : 0;
        Log.d(TAG, "jniGetNetworkState got state:" + state);
        return state;
	}
	

    public static String jniGetAppVersion() {
        PackageManager packageManager = mActivity.getPackageManager();
        try {
            PackageInfo packInfo = packageManager.getPackageInfo(
                    mActivity.getPackageName(), 0);
            String version = packInfo.versionName;
            Log.d(TAG, "jniGetAppVersion " + version);
            return version;
        } catch (Exception e) {
        }
        return "";
    }

    public static String jniGetDeviceName()
    {
        String value = UtilGame.getDeviceName();
        Log.d(TAG, "jniGetDeviceName " + value);
        return value;
    }
    
    public static void jniOpenUrl(final String url)
    {
        Log.d(TAG, "jniOpenUrl " + url);
		try{
        Intent intent = new Intent();
        intent.setAction(Intent.ACTION_VIEW);
        intent.setData(Uri.parse(url));
        mActivity.startActivity(intent);
		}catch(Exception e){}
    }
    
    public static void showExitAppDialog()
    {
        Log.d(TAG, "showExitAppDialog");
        Dialog alertDialog = new AlertDialog.Builder(mActivity).
                setTitle(R.string.exit_app_msg).
                setPositiveButton(R.string.exit_app_yes, new OnClickListener() {
                    
                    @Override
                    public void onClick(DialogInterface arg0, int arg1) {
                        com.gamed9.platform.api.PlatformMgr.getInstance().callExitResult();
                    }
                }).setNegativeButton(R.string.exit_app_no, new OnClickListener() {
                    
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                    }
                }).create();
        alertDialog.show();
    }
    
    public static void jniAddNotification(String id, int seconds, String info)
    {
        Log.d(TAG, "jniAddNotification id:" + id + " seconds:" + seconds + " info:" + info);
        NotificationMgr.addRecord(id, seconds, 0, info);
    }

    public static void jniAddNotificationInWeek(String id, int atDay, int atHour, int atMin, String info)
    {
        if(atDay < 1 || atDay > 7) {Log.d(TAG, "jniAddNotificationInWeek dayError:" + atDay); atDay = 1; }

        Calendar curCal = Calendar.getInstance();

        int atDayOfCalendar = (atDay)%7 + 1; // MON 1 TUE 2 ... SUN 7   => SUNDAY 1, MONDAY 2, ... SAT 7
        Calendar atCal = Calendar.getInstance();
        atCal.setFirstDayOfWeek(Calendar.SUNDAY);
        atCal.set(Calendar.DAY_OF_WEEK, atDayOfCalendar);
        atCal.set(Calendar.HOUR_OF_DAY, atHour);
        atCal.set(Calendar.MINUTE, atMin);

        long curSeconds = curCal.getTimeInMillis() / 1000;
        long atSeconds = atCal.getTimeInMillis() / 1000;

        Log.d(TAG, "curSeconds:" + curSeconds);
        Log.d(TAG, "atSeconds:" + atSeconds);
        
        long delay = atSeconds - curSeconds;
        if(delay < 0)
        {
            delay += 7*24*3600; // schedule at next week
        }
        Log.d(TAG, "jniAddNotificationInWeek delay(s)=" + delay);
        
        NotificationMgr.addRecord(id, delay, 7*24*3600, info);
    }
    
    public static void delAllNotification()
    {
        Log.d(TAG, "delAllNotification");
        NotificationMgr.delAll();
    }
    
    public static void jniShare(String info)
    {
    }
    
    public static void onShareResult(int code)
    {
        
    }
    
    public static int jniGetNetType()
    {
        int type = UtilGame.getNetType(mActivity);
        Log.d(TAG, "jniGetNetType type=" + type);
        return type;
    }

    public static String jniPlatformGameCall(String key)
    {
        Map<String, String> mapInfo = UtilGame.parseInfoMap(key);
        String cmd = mapInfo.get("Cmd");
        
        String value = "";
        
        if(cmd == null)
        {
        } else if(cmd.contentEquals("PLATFORM_GAME_CMD_DEV_TYPE"))
        {
            // get 
            value = UtilGame.getDeviceType();
        } else if(cmd.contentEquals("PLATFORM_GAME_CMD_DEV_OS_VER"))
        {
            // get 
            value = UtilGame.getDeviceOsVer();
        } else if(cmd.contentEquals("PLATFORM_GAME_CMD_DEV_MEMSIZE"))
        {
            // get 
            value = UtilGame.getDeviceTotalMemory(mActivity);
        }
        
        Log.d(TAG, "jniPlatformGameCall " + cmd + ":" + value);
        
        return value;
    }
    

}
