package tp.taller2.udrive;

import java.util.HashMap;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class SessionManager {

    SharedPreferences pref;
    Editor editor;
    Context context;
    String ipDefault = "http://192.168.0.19";
    String portDefault = ":8080/";

    int PRIVATE_MODE = 0;

    private static final String PREF_NAME = "SessionData";
    private static final String IS_LOGIN = "IsLoggedIn";

    public static final String KEY_NAME = "name";
    public static final String KEY_SURNAME = "surname";
    public static final String KEY_EMAIL = "email";
    public static final String KEY_CITY = "city";
    public static final String KEY_PASSWORD = "password";
    public static final String KEY_PICTURE = "picture";
    public static final String KEY_STORAGE = "storage";
    public static final String KEY_IP = "ip";
    public static final String KEY_PORT = "port";


    public SessionManager(Context context) {
        this.context = context;
        pref = context.getSharedPreferences(PREF_NAME, PRIVATE_MODE);
        editor = pref.edit();
    }

    /**
     * Create login session
     * */
    public void createLoginSession(String email, String name, String surname, String city, String password, String picture,
                                   Float storage, String ip, String port){
        editor.putBoolean(IS_LOGIN, true);
        editor.putString(KEY_EMAIL, email);
        editor.putString(KEY_NAME, name);
        editor.putString(KEY_SURNAME, surname);
        editor.putString(KEY_CITY, city);
        editor.putString(KEY_PASSWORD, password);
        editor.putString(KEY_PICTURE, picture);
        editor.putFloat(KEY_STORAGE, storage);
        editor.putString(KEY_IP, ip);
        editor.putString(KEY_PORT, port);
        editor.commit();
    }

    /**
     * Get stored session data
     * */
    public HashMap<String, String> getUserDetails(){
        HashMap<String, String> user = new HashMap<>();
        user.put(KEY_EMAIL, pref.getString(KEY_EMAIL, null));
        user.put(KEY_NAME, pref.getString(KEY_NAME, null));
        user.put(KEY_SURNAME, pref.getString(KEY_SURNAME, null));
        user.put(KEY_CITY, pref.getString(KEY_CITY, null));
        user.put(KEY_PASSWORD, pref.getString(KEY_PASSWORD, null));
        user.put(KEY_PICTURE, pref.getString(KEY_PICTURE, null));
        user.put(KEY_IP, pref.getString(KEY_IP, null));
        user.put(KEY_PORT, pref.getString(KEY_PORT, null));
        return user;
    }

    /**
     * Check login method wil check user login status
     * If false it will redirect user to login page
     * Else won't do anything
     * */
    public void checkLogin(){
        if(!this.isLoggedIn()){
            Intent i = new Intent(context, LoginActivity.class);
            i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(i);
        }
    }

    /**
     * Clear session details
     * */
    public void logoutUser(){
        editor.clear();
        editor.commit();
        Intent i = new Intent(context, LoginActivity.class);
        i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        context.startActivity(i);
    }

    /**
     * Quick check for login
     * **/
    public boolean isLoggedIn(){
        return pref.getBoolean(IS_LOGIN, false);
    }

    public float getUserStorageUsed(){
        return pref.getFloat(KEY_STORAGE, 0);
    }

    public void updateStorageUsed(Float storage){
        editor.putFloat(KEY_STORAGE, storage);
        editor.commit();
    }

    public void updateIpAndPort(String ip, String port){
        editor.putString(KEY_IP, ip);
        editor.putString(KEY_PORT, port);
        editor.commit();
    }

    public String getIp(){
        return pref.getString(KEY_IP, ipDefault);
    }

    public String getPort(){
        return pref.getString(KEY_PORT, portDefault);
    }


}