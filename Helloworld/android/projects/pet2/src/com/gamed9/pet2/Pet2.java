/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.gamed9.pet2;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.KeyguardManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ConfigurationInfo;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.ImageView.ScaleType;
import android.widget.Toast;

import com.gamed9.game.template.R;
import com.gamed9.platform.PlatformGame;
import com.gamed9.platform.api.PlatformMgr;
import com.gamed9.platform.api.Request;
public class Pet2 extends Cocos2dxActivity{

    private static final String TAG = "Pet2";
    private static Activity mActivity;
    private static ImageView mSplashView;
    private static ImageView mSlplashBg = null;
    
    
    private boolean mResumeSkipped = false;
    

    @Override
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		Log.d(TAG,"oncreate");
		
		mActivity = this;
		
		// Do this before nd91
        showSplash();
        
        if(!detectOpenGLES20())
        {
            Log.d(TAG, "don't support gles2.0");
            Toast.makeText(mActivity, "open gles2.0 not supported", Toast.LENGTH_SHORT).show();
            finish();
            return;
        }
		
		PlatformGame.getInstance().init(this);
		        
		PlatformMgr.getInstance().init(this);
        PlatformMgr.getInstance().onCreate(savedInstanceState);
	}

	@Override
	public void onNewIntent(Intent intent)
	{
	    super.onNewIntent(intent);
	    
	    PlatformMgr.getInstance().onNewIntent(intent);
	}

    /**
     * Pause: CocosActivity.onPause -- glView.onPause -- AppDelegate.applicationDidEnterBackground (skip stop anim)
     * Pause(old): onPause -- Platform.onPause -- nativePauseMusic
     */
    
	@Override
	protected void onPause() {
		super.onPause();

        Log.d(TAG,"onPause");
        PlatformGame.getInstance().onPause();
		
		PlatformMgr.getInstance().onPause();
		PlatformMgr.getInstance().call("Native", "NativePauseMusic", null);
	}

	    @Override
    public void onWindowFocusChanged(boolean hasFocus)
    {
        Log.d(TAG,"onWindowFocusChanged");
        super.onWindowFocusChanged(hasFocus);

        if(hasFocus && mResumeSkipped)
        {
            Log.d(TAG, "mGLView resume onWindowFocusChanged");
			PlatformMgr.getInstance().call("Native", "NativeResumeMusic", null);
			mResumeSkipped = false;
        }
    }


    public final static boolean isScreenLocked(Context c) {
        boolean isScreenLocked = true;
        try
        {
            android.app.KeyguardManager mKeyguardManager = (KeyguardManager) c.getSystemService(c.KEYGUARD_SERVICE);
            isScreenLocked = mKeyguardManager.inKeyguardRestrictedInputMode();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        Log.d(TAG, "isScreenLocked=" + isScreenLocked);
        return isScreenLocked;
    }
    
    @Override
    public void onResume()
    {
        Log.d(TAG,"onResume");
        super.onResume();

        boolean isScreenLocked = isScreenLocked(mActivity);
        if(!isScreenLocked)
        {
			PlatformMgr.getInstance().call("Native", "NativeResumeMusic", null);
        } else
        {
            mResumeSkipped = true;
        }

		
        PlatformGame.getInstance().onResume();
		
        PlatformMgr.getInstance().onResume();
    }


    @Override
    public void onStart()
    {
        Log.d(TAG,"onStart");
        super.onStart();
        PlatformMgr.getInstance().onStart();
    }
    @Override
    public void onRestart()
    {
        Log.d(TAG,"onRestart");
        super.onRestart();
        PlatformMgr.getInstance().onRestart();
    }
    @Override
    public void onStop()
    {
        Log.d(TAG,"onStop");
        super.onStop();
        PlatformMgr.getInstance().onStop();
    }
    
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
    	super.onActivityResult(resultCode, resultCode, data);
        Log.d(TAG,"onActivityResult");
        PlatformGame.getInstance().onActivityResult(resultCode, resultCode, data);
        
        PlatformMgr.getInstance().onActivityResult(requestCode, resultCode, data);
    }
    
	@Override
	public void onDestroy()
	{
        Log.d(TAG,"onDestroy");
        super.onDestroy();
	    PlatformGame.getInstance().onDestroy();

        PlatformMgr.getInstance().onDestroy();

	}
    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        PlatformMgr.getInstance().onSaveInstanceState(outState);
    }


    private boolean detectOpenGLES20() {
        ActivityManager am = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo info = am.getDeviceConfigurationInfo();
        return (info.reqGlEsVersion >= 0x20000);
    }
	
	private void showSplash()
	{
        Log.d(TAG,"initSplash");
	    View view = getContentView();
	    FrameLayout f = (FrameLayout) view;
	    if(f == null || mSplashView != null)
	    {
	        return;
	    }
		mSlplashBg = new ImageView(mActivity);
		mSlplashBg.setBackgroundColor(Color.BLACK);

        Animation alpha = AnimationUtils.loadAnimation(mActivity, R.anim.alpha);
        ViewGroup.LayoutParams slplashLayerParams = new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.FILL_PARENT,
                ViewGroup.LayoutParams.FILL_PARENT);
        mSplashView = new ImageView(mActivity);
        mSplashView.setImageDrawable(mActivity.getResources().getDrawable(R.drawable.splash));
        mSplashView.setAnimation(alpha);
        mSplashView.setScaleType(ScaleType.FIT_XY);
        mSplashView.setTag("splash_view_tag");
        f.addView(mSlplashBg, slplashLayerParams);
        f.addView(mSplashView, slplashLayerParams);
        
        Handler handler = new Handler(mActivity.getMainLooper());
        handler.postDelayed(new Runnable() {
            
            @Override
            public void run() {
                //setSplashGone();// not needed here, close by c++
            }
        }, 5000);

	}
	public static void setSplashGone()
	{
        Log.d(TAG,"setSplashGone");
        mActivity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
			    if(mSplashView != null)
			    {
		            mSplashView.setVisibility(View.GONE);
					mSlplashBg.setVisibility(View.GONE);
			    }
			}
		});
	}
	
    static {
		System.loadLibrary("fmodL");
        System.loadLibrary("cocos2dcpp");
    }     

    @Override
    public boolean dispatchKeyEvent(final KeyEvent event) {

        if (event.getAction() == KeyEvent.ACTION_DOWN) {
            switch (event.getKeyCode()) {
            case KeyEvent.KEYCODE_BACK:
				String resultStr = PlatformMgr.getInstance().call(PlatformMgr.ACT_EXIT, null);
				Request result = new Request(resultStr);
    			boolean handled = result.getInt("Result", 0) == 1;
                if(!handled)
                {
                    PlatformGame.showExitAppDialog();
                }
                return false;// add this line, if not work, return true
            }
        }
        return super.dispatchKeyEvent(event);
    }
    

    private View getContentView(){
        Log.d(TAG, "android.R.id.content=" + android.R.id.content);
        ViewGroup decorView = (ViewGroup)mActivity.getWindow().getDecorView();
        View contentView = ((ViewGroup)decorView.findViewById(android.R.id.content)).getChildAt(0);
        return contentView;
    }

}
