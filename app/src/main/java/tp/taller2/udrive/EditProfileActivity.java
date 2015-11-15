package tp.taller2.udrive;

import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
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
import java.util.Random;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import de.hdodenhof.circleimageview.CircleImageView;

public class EditProfileActivity extends AppCompatActivity {

    private static int RESULT_LOAD_IMAGE = 1;
    EditText name;
    EditText email;
    EditText password;
    EditText surname;
    EditText city;
    CircleImageView pic;
    SessionManager session;
    String picturePath;
    Bitmap profilePic;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_profile);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        name = (EditText)findViewById(R.id.username_text);
        email = (EditText)findViewById(R.id.email_text);
        password = (EditText)findViewById(R.id.password_text);
        surname = (EditText)findViewById(R.id.surname_text);
        city = (EditText)findViewById(R.id.place_text);
        pic = (CircleImageView)findViewById(R.id.imgView);

        session = new SessionManager(getApplicationContext());
        HashMap<String, String> user = session.getUserDetails();
        String sessionName = user.get(SessionManager.KEY_NAME);
        String sessionSurname = user.get(SessionManager.KEY_SURNAME);
        String sessionEmail = user.get(SessionManager.KEY_EMAIL);
        String sessionCity = user.get(SessionManager.KEY_CITY);
        String sessionPassword = user.get(SessionManager.KEY_PASSWORD);
        String sessionPicture = user.get(SessionManager.KEY_PICTURE);

        name.setText(sessionName);
        surname.setText(sessionSurname);
        email.setText(sessionEmail);
        city.setText(sessionCity);
        password.setText(sessionPassword);
        Bitmap picture = Utility.stringToBitmap(sessionPicture);
        pic.setImageBitmap(picture);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_empty, menu);
        return true;
    }

    /**
     * Handle action bar item clicks here. The action bar will
     * automatically handle clicks on the Home/Up button, so long
     * as you specify a parent activity in AndroidManifest.xml.
     * @param item
     * @return
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
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
            imageView.setImageBitmap(BitmapFactory.decodeFile(picturePath));

        }
    }

    /** Called when the user clicks the register borderbutton */
    public void saveProfile(View view) {
        String newName = name.getText().toString();
        String newEmail = email.getText().toString();
        String newpassword = password.getText().toString();
        String newCity = city.getText().toString();
        String newSurname = surname.getText().toString();
        HashMap<String, String> user = session.getUserDetails();
        String sessionEmail = user.get(SessionManager.KEY_EMAIL);
        String sessionPassword = user.get(SessionManager.KEY_PASSWORD);
        if(Utility.isNotNull(newName) && Utility.isNotNull(newEmail) && Utility.isNotNull(newpassword)
                && Utility.isNotNull(newSurname) && Utility.isNotNull(newCity)){
            if(!Utility.validateEmail(newEmail)){
                email.requestFocus();
                email.setError(getString(R.string.email_error));
            }else{
                if(Utility.validatePassword(newpassword)){
                    if(sessionEmail.equals(newEmail) && sessionPassword.equals(newpassword)){
                        new getUserUpdateProfileService().execute("http://192.168.1.8:8080/usuario?");
                    } else {
                        new getUserUpdateProfileAndStartNewSessionService().execute("http://192.168.1.8:8080/usuario?");
                    }
                } else {
                    password.requestFocus();
                    password.setError(getString(R.string.password_error));
                }
            }
        }else{
            Toast.makeText(getApplicationContext(), R.string.error_emptyFields, Toast.LENGTH_LONG).show();
        }
    }

    public String getUserUpdateProfileAndStartNewSession(String URL) {
        String newName = name.getText().toString();
        String newEmail = email.getText().toString();
        String newpassword = password.getText().toString();
        String newCity = city.getText().toString();
        String newSurname = surname.getText().toString();
        profilePic = BitmapFactory.decodeFile(picturePath);
        String encodedImage = Utility.bitmapToString(profilePic);
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", newName);
            json.put("apellido", newSurname);
            json.put("mail", newEmail);
            json.put("lugar", newCity);
            json.put("password", newpassword);
            json.put("foto", encodedImage);
            httpPost.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpPost.setHeader("Content-Type", "application/json");
            httpPost.setHeader("Accept-Encoding", "application/json");
        } catch (Exception e) {
            e.printStackTrace();
        }
        try {
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
                Log.d("JSON", "Failed to download file");
            }
        } catch (Exception e) {
            Log.d("readJSONFeed", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class getUserUpdateProfileAndStartNewSessionService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getUserUpdateProfileAndStartNewSession(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                Log.d("result", result);
                Log.d("Status", status.toString());
                Log.d("Message", message.toString());
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), R.string.success_register, Toast.LENGTH_LONG).show();
                    navigatetoLoginActivity();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }

    public String getUserUpdateProfile(String URL) {
        String newName = name.getText().toString();
        String newEmail = email.getText().toString();
        String newpassword = password.getText().toString();
        String newCity = city.getText().toString();
        String newSurname = surname.getText().toString();
        profilePic = BitmapFactory.decodeFile(picturePath);
        String encodedImage = Utility.bitmapToString(profilePic);
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", newName);
            json.put("apellido", newSurname);
            json.put("mail", newEmail);
            json.put("lugar", newCity);
            json.put("foto", encodedImage);
            json.put("password", newpassword);
            httpPost.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpPost.setHeader("Content-Type", "application/json");
            httpPost.setHeader("Accept-Encoding", "application/json");
        } catch (Exception e) {
            e.printStackTrace();
        }
        try {
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
                Log.d("JSON", "Failed to download file");
            }
        } catch (Exception e) {
            Log.d("readJSONFeed", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class getUserUpdateProfileService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getUserUpdateProfile(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                Log.d("result", result);
                Log.d("Status", status.toString());
                Log.d("Message", message.toString());
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), R.string.success_register, Toast.LENGTH_LONG).show();
                    navigatetoProfileActivity();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }

    /**
     * Method which navigates from EditProfile Activity to Profile Activity
     */
    public void navigatetoProfileActivity(){
        Intent profileIntent = new Intent(getApplicationContext(),ProfileActivity.class);
        profileIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        profileIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(profileIntent);
    }

    public void navigatetoLoginActivity(){
        Intent loginIntent = new Intent(getApplicationContext(),LoginActivity.class);
        loginIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        loginIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(loginIntent);
    }

}
