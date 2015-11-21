package tp.taller2.udrive;

import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;
import android.provider.MediaStore;
import android.support.design.widget.TextInputLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import de.hdodenhof.circleimageview.CircleImageView;

public class RegisterActivity extends AppCompatActivity {
    TextView errorMsg;
    EditText nameET;
    EditText emailET;
    EditText pwdET;
    EditText surnameET;
    EditText cityET;
    String picturePath;
    Bitmap profilePic;
    TextInputLayout inputLayoutEmail, inputLayoutPassword, inputLayoutUsername, inputLayoutSurname, inputLayoutPlace;
    String name, email, password, city, surname;
    private static int RESULT_LOAD_IMAGE = 1;
    CircleImageView imageView;
    SessionManager session;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        inputLayoutEmail = (TextInputLayout) findViewById(R.id.input_layout_newEmail);
        inputLayoutPassword = (TextInputLayout) findViewById(R.id.input_layout_newPassword);
        inputLayoutUsername = (TextInputLayout) findViewById(R.id.input_layout_username);
        inputLayoutSurname = (TextInputLayout) findViewById(R.id.input_layout_surname);
        inputLayoutPlace = (TextInputLayout) findViewById(R.id.input_layout_place);

        errorMsg = (TextView)findViewById(R.id.register_error);
        nameET = (EditText)findViewById(R.id.username_message);
        emailET = (EditText)findViewById(R.id.newEmail_message);
        pwdET = (EditText)findViewById(R.id.newPassword_message);
        surnameET = (EditText)findViewById(R.id.surname_message);
        cityET = (EditText)findViewById(R.id.place_message);

        imageView = (CircleImageView) findViewById(R.id.imgView);
        imageView.setImageResource(R.drawable.profile_default);

        session = new SessionManager(getApplicationContext());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_register, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /** Called when the user clicks the register borderbutton */
    public void registerMessage(View view) {
        name = nameET.getText().toString();
        email = emailET.getText().toString();
        password = pwdET.getText().toString();
        city = cityET.getText().toString();
        surname = surnameET.getText().toString();
        if(Utility.isNotNull(name) && Utility.isNotNull(email) && Utility.isNotNull(password)
                && Utility.isNotNull(surname) && Utility.isNotNull(city)){
            if(!Utility.validateEmail(email)){
                emailET.requestFocus();
                emailET.setError(getString(R.string.email_error));
            }else{
                if(Utility.validatePassword(password)){
                    new postUserSignUpService().execute(session.getIp() + session.getPort() + "usuario?");
                } else {
                    pwdET.requestFocus();
                    pwdET.setError(getString(R.string.password_error));
                }
            }
        }else{
            Toast.makeText(getApplicationContext(), R.string.error_emptyFields, Toast.LENGTH_LONG).show();
        }
    }

    public String postUserSignUp(String URL) {
        String encodedImage = String.valueOf(R.drawable.profile_default);
        if(profilePic.getByteCount() > 0){
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
                Log.e("User sign up", "service status code:" + statusCode);
                Utility.appendToErrorLog("User sign up", "status code:" + statusCode);
            }
        } catch (Exception e) {
            Log.e("User sign up", e.getLocalizedMessage());
            Utility.appendToErrorLog("User sign up", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class postUserSignUpService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return postUserSignUp(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                JSONObject json = new JSONObject();
                json.put("nombre", name);
                json.put("apellido", surname);
                json.put("mail", email);
                json.put("lugar", city);
                json.put("password", password);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if(status.equals("ok")) {
                    setDefaultValues();
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("User sign up", message.toString());
                    Utility.appendToInfoLog("User sign up", message.toString());
                    Log.d("User sign up", json.toString());
                    Utility.appendToDebugLog("User sign up", json.toString());
                    navigatetoLoginActivity();
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("User sign up", message.toString());
                    Utility.appendToErrorLog("User sign up", message.toString());
                }
            } catch (Exception e) {
                Log.e("User sign up", e.getLocalizedMessage());
                Utility.appendToErrorLog("User sign up", e.getLocalizedMessage());
            }
        }
    }

    /**
     * Method which navigates from Register Activity to Login Activity
     */
    public void navigatetoLoginActivity(){
        Intent loginIntent = new Intent(getApplicationContext(),LoginActivity.class);
        loginIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        loginIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(loginIntent);
    }

    public void loadPicture(View view) {
        Intent i = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(i, RESULT_LOAD_IMAGE);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == RESULT_LOAD_IMAGE && resultCode == RESULT_OK && null != data) {
            Uri selectedImage = data.getData();
            String[] filePathColumn = { MediaStore.Images.Media.DATA };

            Cursor cursor = getContentResolver().query(selectedImage,
                    filePathColumn, null, null, null);
            cursor.moveToFirst();

            int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
            picturePath = cursor.getString(columnIndex);
            cursor.close();
            profilePic = BitmapFactory.decodeFile(picturePath);
            imageView.setImageBitmap(profilePic);
        }


    }

    public void setDefaultValues(){
        nameET.setText("");
        emailET.setText("");
        pwdET.setText("");
        cityET.setText("");
        surnameET.setText("");
    }
}
