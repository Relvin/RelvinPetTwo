package com.gamed9.util.network;

import com.gamed9.platform.api.PlatformMgr;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;


public class NetReceiver extends BroadcastReceiver {
	@Override
	public void onReceive(Context context, Intent intent) {
		Log.d("NetReceiver", "net state changed");
		// TODO Auto-generated method stub
		//Toast.makeText(context, intent.getAction(), 1).show();
		ConnectivityManager manager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo mobileInfo = manager.getNetworkInfo(ConnectivityManager.TYPE_MOBILE);
		NetworkInfo wifiInfo = manager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
		NetworkInfo activeInfo = manager.getActiveNetworkInfo();
		
		if(activeInfo != null && activeInfo.isConnected())
		{
			PlatformMgr.getInstance().call(PlatformMgr.MODULE_NATIVE, PlatformMgr.KEY_ACTION+"=NetworkDisconnected");
		}else
		{
			PlatformMgr.getInstance().call(PlatformMgr.MODULE_NATIVE, PlatformMgr.KEY_ACTION+"=NetworkConnected");
		}
	}  //如果无网络连接activeInfo为null

}