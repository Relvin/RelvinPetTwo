package com.gamed9.util.schedulednotification;

import java.util.HashSet;
import java.util.Set;

import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.SystemClock;
import android.util.Log;

public class NotificationMgr {
    private static final String TAG = "zdbg.NotificationMgr";
    
    public static String MAIN_ACTIVITY_NAME = "com.gamed9.dota.Dota";

    private static Context context;
    
    private static class TimerRecord
    {
        public String id;
        public long time;
        public long intval;
        
        
        // noti info
        public String info;
        
        // runtime
        public long timerId;
        public long notificationId;

        public long fireTime;

        public TimerRecord(String idv, long timev, long intvalv, String infov, long timerIdv, long notificationIdv)
        {
            id = idv;
            time = timev;
            intval = intvalv;
            info = infov;

            timerId = timerIdv;
            notificationId = notificationIdv;
            
            fireTime = 0;
        }
        
        public static TimerRecord load(String id)
        {
            if(!Ids.exists(id))
            {
                return null;
            }
            try
            {
                long time = Long.parseLong(getPref(id+"_time"));
                long intval = Long.parseLong(getPref(id+"_intval"));
                long timerId = Long.parseLong(getPref(id+"_timerId"));
                long noId = Long.parseLong(getPref(id+"_noId"));
                String info = getPref(id+"_invo");
                long fireTime = Long.parseLong(getPref(id+"_fireTime"));
                if(info == null || info.isEmpty())
                {
                    return null;
                }
                TimerRecord rec = new TimerRecord(id, time, intval, info, timerId, noId);
                rec.fireTime = fireTime;
                return rec;
            }
            catch(Exception e)
            {
            }
            return null;
        }
        
        public static Set<TimerRecord> loadAll()
        {
            String[] ids = Ids.loadAll();
            Set<TimerRecord> recs = new HashSet<TimerRecord>();
            for(String id : ids)
            {
                recs.add(TimerRecord.load(id));
            }
            return recs;
        }
        
        public void save(){
            savePref(id+"_time", String.valueOf(time));
            savePref(id+"_intval", String.valueOf(intval));
            savePref(id+"_timerId", String.valueOf(timerId));
            savePref(id+"_noId", String.valueOf(notificationId));
            savePref(id+"_invo", String.valueOf(info));
            savePref(id+"_fireTime", String.valueOf(fireTime));
        }
        
        public boolean isExpired()
        {
            if(intval != 0)
            {
                return false;
            }
            long curTime = getCurTime()/1000;
            if(fireTime > curTime)
            {
                Log.d(TAG, "expired: id:" + id);
                return true;
            }
            return false;
        }
        
        public void addTimer()
        {

            // Schedule show alarm
            AlarmManager alarmMgr = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
            long curTime = getCurTime()/1000;
            if(intval == 0)
            {
                Log.d(TAG, "addTimer time=" + time*1000 + " curTime:"+curTime*1000);
                if(curTime > time)
                {
                    time = curTime + 1;
                }
                alarmMgr.set(AlarmManager.ELAPSED_REALTIME, time*1000, getAlarmReceiverIntent());
                Log.d(TAG, "add getAlarmReceiverIntent:" + timerId);
            } else
            {
                Log.d(TAG, "addTimer invtal=" + intval + " time=" + time*1000);
                alarmMgr.setRepeating(AlarmManager.ELAPSED_REALTIME, time*1000, intval*1000, getAlarmReceiverIntent());
                Log.d(TAG, "add getAlarmReceiverIntent:" + timerId);
            }

        }
        
        public void delTimer()
        {
            Log.d(TAG, "delTimer id=" + id);
            Log.d(TAG, "del getAlarmReceiverIntent:" + timerId);
            AlarmManager alarmMgr = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
            alarmMgr.cancel(getAlarmReceiverIntent());
        }
        
        private PendingIntent getAlarmReceiverIntent()
        {
            Intent intent = new Intent(context, AlarmReceiver.class);
            intent.putExtra("id", id);
            int requestCode = (int) timerId;
            PendingIntent pendIntent = PendingIntent.getBroadcast(context,
                    requestCode, intent, PendingIntent.FLAG_UPDATE_CURRENT);
            return pendIntent;
        }
        
        public void showNotification()
        {
            Log.d(TAG, "onTrigger showNotification id:" + id + " time:" + time);
            // update trigger time
            NotificationManager nm = (NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);
            Notification n = new Notification(context.getApplicationInfo().icon, info, System.currentTimeMillis());
            n.flags |= Notification.FLAG_AUTO_CANCEL;
            n.defaults = Notification.DEFAULT_SOUND;

            Intent i;
            try {
                i = new Intent(context, Class.forName(MAIN_ACTIVITY_NAME));
            } catch (ClassNotFoundException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
                return;
            }
//            Intent i = new Intent("open activity action");
            i.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP|Intent.FLAG_ACTIVITY_NEW_TASK);
            PendingIntent activityIntent = PendingIntent.getActivity(context, (int) notificationId, i, PendingIntent.FLAG_UPDATE_CURRENT);
            n.setLatestEventInfo(context, context.getString(context.getApplicationInfo().labelRes), info, activityIntent);
            
            nm.notify((int) notificationId, n);
            
            fireTime = System.currentTimeMillis();
        }
        public static void cancelAllNotification()
        {
            NotificationManager nm = (NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);
            nm.cancelAll();
        }
        public static void delAllTimer()
        {
            Set<TimerRecord> set = loadAll();
            if(set != null)
            {
                for(TimerRecord rec : set)
                {
                    if(rec != null)
                    {
                        rec.delTimer();
                    }
                }
            }
        }
    };

    private static class Ids
    {
        public static String[] loadAll()
        {
            String idStr = getPref("ids");
            if(idStr == null)
            {
                return null;
            }
            String[] ids = idStr.split(";");
            return ids;
        }
        public static boolean exists(String idAdd)
        {
            String[] ids = Ids.loadAll();
            for(String id:ids)
            {
                if(idAdd.contentEquals(id))
                {
                    return true;
                }
            }
            return false;
        }
        public static void add(String idAdd)
        {
            String[] ids = Ids.loadAll();
            for(String id:ids)
            {
                if(idAdd.contentEquals(id))
                {
                    return;
                }
            }

            String idStr = getPref("ids");
            savePref("ids", idStr+ idAdd + ";");
        }
        public static void del(String delId)
        {
            String[] ids = loadAll();
            if(ids == null)
            {
                return;
            }
            String idStr = "";
            for(String id:ids)
            {
                if(delId.contentEquals(id))
                {
                    continue;
                }
                idStr += id + ";";
            }
            savePref("ids", idStr);
        }
        public static void delAll()
        {
            savePref("ids", "");
        }
    }
    

    public static void init(Context contextv)
    {
        context  =contextv;
    }
    
    /*
     */
    public static void updateTimerRecords()
    {
        String[] ids = Ids.loadAll();
        for(String id : ids)
        {
            TimerRecord rec = TimerRecord.load(id);
            if(rec == null || rec.isExpired())
            {
                Ids.del(id);
                continue;
            }
            rec.addTimer();
            rec.save();
        }
    }
    
    public static void addRecord(String id, long seconds, long intval,
            String info) {
        long time = getCurTime() / 1000 + seconds + 1;
        long timerId = (int) (Math.random() * 100000);
        long notificationId = (int) (Math.random() * 100000);
        TimerRecord rec = TimerRecord.load(id);
        if (rec == null) {
            rec = new TimerRecord(id, time, intval, info, timerId,
                    notificationId);
            Ids.add(id);
        }
        rec.time = time;
        rec.intval = intval;
        rec.info = info;
        rec.addTimer();
        rec.save();
    }
    
    public static void delAll()
    {
        TimerRecord.cancelAllNotification();
        TimerRecord.delAllTimer();
        // must at last
        Ids.delAll();
    }
    
    public static void onTrigger(String id)
    {
        TimerRecord rec = TimerRecord.load(id);
        if(rec == null)
        {
            return;
        }
        rec.showNotification();
        
        // one shot
        if(rec.isExpired())
        {
            Ids.del(id);
        }
    }
    
    private static long getCurTime()
    {
        return SystemClock.elapsedRealtime();
    }
    
    private static void savePref(String key, String value)
    {
        SharedPreferences share = context.getSharedPreferences("PREF_ALARM_TAG",
                Context.MODE_PRIVATE);
        share.edit().putString(key, value).commit();
        Log.d(TAG, "set: "+key + "=>" + value);
    }
    private static String getPref(String key)
    {
        SharedPreferences share = context.getSharedPreferences("PREF_ALARM_TAG",
                Context.MODE_PRIVATE);
        String value = share.getString(key, "");
        Log.d(TAG, "get: "+key + "=>" + value);
        return value;
    }
}
