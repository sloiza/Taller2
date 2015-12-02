package tp.taller2.udrive;

import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.LayerDrawable;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashMap;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.client.methods.HttpPut;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import de.hdodenhof.circleimageview.CircleImageView;

public class EditProfileActivity extends AppCompatActivity {

    private static int RESULT_LOAD_IMAGE = 1;
    EditText nameET;
    EditText emailET;
    EditText passwordET;
    EditText surnameET;
    EditText cityET;
    CircleImageView pic;
    SessionManager session;
    String picturePath;
    Bitmap profilePic;
    String name, email, password, surname, city;
    HashMap<String, String> user;
    Float storage;
    String sessionPicture;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_profile);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        nameET = (EditText)findViewById(R.id.username_text);
        emailET = (EditText)findViewById(R.id.email_text);
        passwordET = (EditText)findViewById(R.id.password_text);
        surnameET = (EditText)findViewById(R.id.surname_text);
        cityET = (EditText)findViewById(R.id.place_text);
        pic = (CircleImageView)findViewById(R.id.imgView);

        session = new SessionManager(getApplicationContext());
        user = session.getUserDetails();
        name = user.get(SessionManager.KEY_NAME);
        surname = user.get(SessionManager.KEY_SURNAME);
        email = user.get(SessionManager.KEY_EMAIL);
        city = user.get(SessionManager.KEY_CITY);
        password = user.get(SessionManager.KEY_PASSWORD);
        sessionPicture = user.get(SessionManager.KEY_PICTURE);
        storage = session.getUserStorageUsed();

        nameET.setText(name);
        surnameET.setText(surname);
        emailET.setText(email);
        cityET.setText(city);
        passwordET.setText(password);
        Bitmap picture = Utility.stringToBitmap(sessionPicture);
        pic.setImageBitmap(picture);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_empty, menu);
        return true;
    }

    /**
     * Handle action bar item clicks here. The action bar will
     * automatically handle clicks on the Home/Up button, so long
     * as you specify a parent activity in AndroidManifest.xml.
     * @param item
     * @return option
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public void changePicture(View view) {
        Intent i = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(i, RESULT_LOAD_IMAGE);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == RESULT_LOAD_IMAGE && resultCode == RESULT_OK && null != data) {
            Uri selectedImage = data.getData();
            String[] filePathColumn = {MediaStore.Images.Media.DATA};

            Cursor cursor = getContentResolver().query(selectedImage,
                    filePathColumn, null, null, null);
            cursor.moveToFirst();

            int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
            picturePath = cursor.getString(columnIndex);
            cursor.close();

            CircleImageView imageView = (CircleImageView) findViewById(R.id.imgView);
            profilePic = BitmapFactory.decodeFile(picturePath);
            imageView.setImageBitmap(profilePic);

        }
    }

    public void saveProfile(View view) {
        name = nameET.getText().toString();
        email = emailET.getText().toString();
        password = passwordET.getText().toString();
        city = cityET.getText().toString();
        surname = surnameET.getText().toString();
        String sessionEmail = user.get(SessionManager.KEY_EMAIL);
        String sessionPassword = user.get(SessionManager.KEY_PASSWORD);
        if(Utility.isNotNull(name) && Utility.isNotNull(email) && Utility.isNotNull(password)
                && Utility.isNotNull(surname) && Utility.isNotNull(city)){
            if(!Utility.validateEmail(email)){
                emailET.requestFocus();
                emailET.setError(getString(R.string.email_error));
            }else{
                if(Utility.validatePassword(password)){
                    if(sessionEmail.equals(email) && sessionPassword.equals(password)){
                        new userUpdateProfileService().execute(session.getIp() + session.getPort() + "usuario?");
                    } else {
                        new userUpdateProfileAndStartNewSessionService().execute(session.getIp() + session.getPort() + "usuario?");
                    }
                } else {
                    passwordET.requestFocus();
                    passwordET.setError(getString(R.string.password_error));
                }
            }
        }else{
            Toast.makeText(getApplicationContext(), R.string.error_emptyFields, Toast.LENGTH_LONG).show();
        }
    }

    public String userUpdateProfileAndStartNewSession(String URL) {
        String encodedImage = sessionPicture;
        if(profilePic != null){
            encodedImage = Utility.bitmapToString(profilePic);
        }
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", name);
            json.put("apellido", surname);
            json.put("mail", email);
            json.put("lugar", city);
            json.put("password", password);
            json.put("foto", encodedImage);
            httpPost.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpPost.setHeader("Content-Type", "application/json");
            httpPost.setHeader("Accept-Encoding", "application/json");
            HttpResponse response = httpClient.execute(httpPost);
            StatusLine statusLine = response.getStatusLine();
            int statusCode = statusLine.getStatusCode();
            if (statusCode == 200) {
                HttpEntity entity = response.getEntity();
                InputStream inputStream = entity.getContent();
                BufferedReader reader = new BufferedReader(
                        new InputStreamReader(inputStream));
                String line;
                while ((line = reader.readLine()) != null) {
                    stringBuilder.append(line);
                }
                inputStream.close();
            } else {
                Log.e("New update profile", "service status code: " + statusCode);
                Utility.appendToErrorLog("Update profile and start new session", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("New update profile", e.getLocalizedMessage());
            Utility.appendToErrorLog("Update profile and start new session", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class userUpdateProfileAndStartNewSessionService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return userUpdateProfileAndStartNewSession(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("New update profile", message.toString());
                    Utility.appendToInfoLog("Update profile and start new session", message.toString());
                    Log.d("New update profile", jsonObject.toString());
                    Utility.appendToDebugLog("Update profile and start new session", message.toString());
                    navigatetoLoginActivity();
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("New update profile", message.toString());
                    Utility.appendToErrorLog("Update profile and start new session", message.toString());
                }
            } catch (Exception e) {
                Log.e("New update profile", e.getLocalizedMessage());
                Utility.appendToErrorLog("Update profile and start new session", e.getLocalizedMessage());
            }
        }
    }

    public String userUpdateProfile(String URL) {
        String encodedImage = sessionPicture;
        if(profilePic != null){
            encodedImage = Utility.bitmapToString(profilePic);
        }
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPut httpPut = new HttpPut(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", name);
            json.put("apellido", surname);
            json.put("mail", email);
            json.put("lugar", city);
            json.put("foto", encodedImage);
            json.put("password", password);
            httpPut.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpPut.setHeader("Content-Type", "application/json");
            httpPut.setHeader("Accept-Encoding", "application/json");
             HttpResponse response = httpClient.execute(httpPut);
            StatusLine statusLine = response.getStatusLine();
            int statusCode = statusLine.getStatusCode();
            if (statusCode == 200) {
                HttpEntity entity = response.getEntity();
                InputStream inputStream = entity.getContent();
                BufferedReader reader = new BufferedReader(
                        new InputStreamReader(inputStream));
                String line;
                while ((line = reader.readLine()) != null) {
                    stringBuilder.append(line);
                }
                inputStream.close();
            } else {
                Log.e("Update profile", "service status code: " + statusCode);
                Utility.appendToErrorLog("Update profile", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Update profile", e.getLocalizedMessage());
            Utility.appendToErrorLog("Update profile", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class userUpdateProfileService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return userUpdateProfile(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                String encodedImage = sessionPicture;
                if(profilePic != null){
                    encodedImage = Utility.bitmapToString(profilePic);
                }
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("Update profile", message.toString());
                    Utility.appendToInfoLog("Update profile", message.toString());
                    Log.d("Update profile", jsonObject.toString());
                    Utility.appendToDebugLog("Update profile", jsonObject.toString());
                    session.createLoginSession(email, name, surname, city, password, encodedImage, storage, session.getIp(), session.getPort());
                    navigatetoProfileActivity();
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Update profile", message.toString());
                    Utility.appendToErrorLog("Update profile", message.toString());
                }
            } catch (Exception e) {
                Log.e("Update profile", e.getLocalizedMessage());
                Utility.appendToErrorLog("Update profile", e.getLocalizedMessage());
            }
        }
    }

    /**
     * Method which navigates from EditProfile Activity to Profile Activity
     */
    public void navigatetoProfileActivity(){
        Intent profileIntent = new Intent(getApplicationContext(),ProfileActivity.class);
        profileIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(profileIntent);
    }

    public void navigatetoLoginActivity(){
        Intent intent = new Intent(getApplicationContext(),LoginActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }

}
