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
import android.util.Base64;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Random;

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
    private static int RESULT_LOAD_IMAGE = 1;

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
    }

    public void loadPicture(View view) {
        Intent i = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(i, RESULT_LOAD_IMAGE);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_register, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up borderbutton, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    /** Called when the user clicks the register borderbutton */
    public void registerMessage(View view) {
        String name = nameET.getText().toString();
        String email = emailET.getText().toString();
        String password = pwdET.getText().toString();
        String city = cityET.getText().toString();
        String surname = surnameET.getText().toString();
        if(Utility.isNotNull(name) && Utility.isNotNull(email) && Utility.isNotNull(password)
                && Utility.isNotNull(surname) && Utility.isNotNull(city)){
            if(!Utility.validateEmail(email)){
                emailET.requestFocus();
                emailET.setError(getString(R.string.email_error));
            }else{
                if(Utility.validatePassword(password)){
                    new getUserSignUpService().execute("http://192.168.1.9:8080/usuario?");
                } else {
                    pwdET.requestFocus();
                    pwdET.setError(getString(R.string.password_error));
                }
            }
        }else{
            Toast.makeText(getApplicationContext(), R.string.error_emptyFields, Toast.LENGTH_LONG).show();
        }
    }

    public String getUserSignUp(String URL) {
        String name = nameET.getText().toString();
        String email = emailET.getText().toString();
        String password = pwdET.getText().toString();
        String city = cityET.getText().toString();
        String surname = surnameET.getText().toString();
        profilePic = BitmapFactory.decodeFile(picturePath);
        String encodedImage = Utility.bitmapToString(profilePic);

        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        JSONObject json = new JSONObject();
        int min = 1;
        int max = 1000;
        Random random = new Random();
        int id = random.nextInt(max - min + 1) + min;
        try {
            json.put("nombre", name);
            json.put("apellido", surname);
            json.put("mail", email);
            json.put("id", id);
            json.put("lugar", city);
            json.put("password", password);
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

    private class getUserSignUpService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getUserSignUp(urls[0]);
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
                    setDefaultValues();
                    Toast.makeText(getApplicationContext(), R.string.success_register, Toast.LENGTH_LONG).show();
                    navigatetoLoginActivity();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
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

            CircleImageView imageView = (CircleImageView) findViewById(R.id.imgView);
            imageView.setImageBitmap(BitmapFactory.decodeFile(picturePath));

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
