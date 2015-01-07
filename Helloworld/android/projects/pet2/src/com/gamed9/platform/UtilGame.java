package com.gamed9.platform;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.app.ActivityManager;
import android.app.ActivityManager.MemoryInfo;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.Service;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.telephony.TelephonyManager;
import android.text.format.Formatter;
import android.util.Log;

public class UtilGame {
    private static final String TAG = "Platform.UtilGame";

    public static Map<String, String> parseInfoMap(String info)
    {
        Log.d(TAG, "parseStr=" + info);
        Map<String, String> infoMap = new HashMap<String, String>();
        String[] buyInfo = info.split("\\|");
        for(int i = 0; i < buyInfo.length; i++)
        {
            int pos = buyInfo[i].indexOf("=");
            if(pos > 0)
            {
                String[] itemInfo = buyInfo[i].split("=");
                if(itemInfo.length < 2)
                {
                    continue;
                }
                infoMap.put(itemInfo[0], itemInfo[1]);
                Log.d(TAG, "[" + itemInfo[0] + "] " + itemInfo[1]);
            }
        }
        return infoMap;
    }

    public static String getDeviceId(Context context)
    {
        // IMEI  or  MAC or ANDROIDID
        
        // IMEI
        TelephonyManager tm = (TelephonyManager) context.getSystemService(Service.TELEPHONY_SERVICE);
        String id = tm.getDeviceId();
        if(id != null && id.length() > 1)
        {
            return id;
        }
        
        id = getLocalMacAddress(context); 
        if(id != null && id.length() > 1)
        {
            return id;
        }

        id = getAndroidId(context); 
        if(id != null && id.length() > 1)
        {
            return id;
        }
        
        return "invalidid";
    }

    public static String getDeviceIdType(Context context)
    {
        // IMEI  or  MAC or ANDROIDID
        
        // IMEI
        TelephonyManager tm = (TelephonyManager) context.getSystemService(Service.TELEPHONY_SERVICE);
        String id = tm.getDeviceId();
        if(id != null && id.length() > 1)
        {
            return "IMEI";
        }
        
        id = getLocalMacAddress(context); 
        if(id != null && id.length() > 1)
        {
            return "MAC";
        }

        id = getAndroidId(context); 
        if(id != null && id.length() > 1)
        {
            return "ANDROIDID";
        }
        
        return "INVALIDTYPE";
    }
    

    private static String getAndroidId(Context context) {
        String androidId = android.provider.Settings.System.getString(
                context.getContentResolver(),
                android.provider.Settings.Secure.ANDROID_ID);
        return androidId;
    }

    private static String getLocalMacAddress(Context context) {
        String macAddress = null;
        WifiManager wifiMgr = (WifiManager) context
                .getSystemService(Context.WIFI_SERVICE);
        WifiInfo info = (null == wifiMgr ? null : wifiMgr.getConnectionInfo());
        if (info != null) {
            macAddress = info.getMacAddress();
        }
        return macAddress;
    }

    public static String getDeviceType()
    {
        String info = android.os.Build.MODEL;
        return info;
    }

    public static String getDeviceOsVer()
    {
        String info = String.valueOf(android.os.Build.VERSION.RELEASE);
        return info;
    }

	public static String getDeviceTotalMemory(Context context) {
        String value = (getAvailMemoryBytes(context)/1024/1024) + "MB/" + (getTotalMemoryBytes()/1024/1024) + "MB";
        Log.d(TAG, "getDeviceTotalMemory:" + value);
        return value;
    }
   
	private static long getAvailMemoryBytes(Context context) {// 获取android当前可用内存大小
		ActivityManager am = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
		MemoryInfo mi = new MemoryInfo();
		am.getMemoryInfo(mi);// mi.availMem; 当前系统的可用内存
		return mi.availMem;
	}

	private static long getTotalMemoryBytes() {
		String str1 = "/proc/meminfo";// 系统内存信息文件
		String str2;
		String[] arrayOfString;
		long initial_memory = 0;
		try {
			FileReader localFileReader = new FileReader(str1);
			BufferedReader localBufferedReader = new BufferedReader(
					localFileReader, 8192);
			str2 = localBufferedReader.readLine();// 读取meminfo第一行，系统总内存大小
			arrayOfString = str2.split("\\s+");
			for (String num : arrayOfString) {
				Log.i(str2, num + "\t");

			}
			initial_memory = Integer.valueOf(arrayOfString[1]).intValue() * 1024;// 获得系统总内存，单位是KB，乘以1024转换为Byte
			localBufferedReader.close();
		} catch (IOException e) {
		}
		return initial_memory;
	}
    /**
     * Model + version
     */
    public static String getDeviceName()
    {
        String info = android.os.Build.MODEL + ","
                + android.os.Build.VERSION.RELEASE;
        return info;
    }
    
    public static boolean isAppOnForeground(Context context) {
        ActivityManager activityManager = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        String packageName = context.getPackageName();
        List<RunningAppProcessInfo> appProcesses = activityManager.getRunningAppProcesses();
        if (appProcesses == null)
            return false;
        for (RunningAppProcessInfo appProcess : appProcesses) {
            if (appProcess.processName.equals(packageName)
                    && appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
                return true;
            }
        }
        return false;
    } 

    /**
     * @param context
     * @return
     * 0 : unknown
     * 1 : wifi
     * 2 : 2g/3g/4g
     */
    public static int getNetType(Context context) {
        ConnectivityManager connectMgr = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);

        NetworkInfo info = connectMgr.getActiveNetworkInfo();
        if(info == null)
        {
            return 0;
        }
        if(info.getType() == ConnectivityManager.TYPE_WIFI)
        {
            return 1;
        }
        if(info.getType() == ConnectivityManager.TYPE_MOBILE)
        {
            return 2;
        }
        return 0;
    }

}
