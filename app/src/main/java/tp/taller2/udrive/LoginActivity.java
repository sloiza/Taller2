package tp.taller2.udrive;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.TextInputLayout;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.loopj.android.http.HttpGet;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

public class LoginActivity extends AppCompatActivity {

    TextView errorMsg;
    EditText emailET;
    EditText passwordET;
    SessionManager session;
    TextInputLayout inputLayoutEmail, inputLayoutPassword;
    String email, password, ip, port;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        inputLayoutEmail = (TextInputLayout) findViewById(R.id.input_layout_email);
        inputLayoutPassword = (TextInputLayout) findViewById(R.id.input_layout_password);

        errorMsg = (TextView)findViewById(R.id.login_error);
        emailET = (EditText)findViewById(R.id.email_message);
        passwordET = (EditText)findViewById(R.id.password_message);

        session = new SessionManager(getApplicationContext());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_login, menu);
        return true;
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        return id == R.id.action_settings || super.onOptionsItemSelected(item);
    }

    /** Called when the user clicks the login */
    public void loginMessage(View view) {
        email = emailET.getText().toString();
        password = passwordET.getText().toString();
        if(Utility.isNotNull(email) && Utility.isNotNull(password)){
            if(!Utility.validateEmail(email)){
                emailET.requestFocus();
                emailET.setError(getString(R.string.email_error));
            }else{
                if(Utility.validatePassword(password)){
                    new getUserLoginService().execute("http://192.168.43.171:8080/usuario?");
                }else{
                    passwordET.requestFocus();
                    passwordET.setError(getString(R.string.password_error));
                }
            }
        } else{
            Toast.makeText(getApplicationContext(), R.string.error_emptyFields, Toast.LENGTH_LONG).show();
        }
    }

    public String getUserLogin(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("mail", email);
            json.put("password", password);
            httpGet.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpGet.setHeader("Content-Type", "application/json");
            httpGet.setHeader("Accept-Encoding", "application/json");
            HttpResponse response = httpClient.execute(httpGet);
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
                Log.e("User login", "service status code: " + statusCode);
                Utility.appendToErrorLog("User login", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("User login", e.getLocalizedMessage());
            Utility.appendToErrorLog("User login", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class getUserLoginService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getUserLogin(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if(status.equals("ok")) {
                    Object name = jsonObject.get("nombre");
                    Object surname = jsonObject.get("apellido");
                    Object email = jsonObject.get("mail");
                    Object password = jsonObject.get("password");
                    Object city = jsonObject.get("lugar");
                    Object picture = null;
                    String pic;
                    if(jsonObject.has("foto")){
                        pic = jsonObject.get("foto").toString();
                    } else {
                        pic = String.valueOf(R.drawable.profile_default);
                    }
                    session.createLoginSession(email.toString(), name.toString(), surname.toString(),
                            city.toString(), password.toString(), pic, 0.0f,
                            session.getIp(), session.getPort());
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("User login", message.toString());
                    Utility.appendToInfoLog("User login", message.toString());
                    Log.d("User login", jsonObject.toString());
                    Utility.appendToDebugLog("User login", jsonObject.toString());
                    navigatetoHomeActivity();
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("User login", message.toString());
                    Utility.appendToErrorLog("User login", message.toString());
                }
            } catch (Exception e) {
                Log.e("User login", e.getLocalizedMessage());
                Utility.appendToErrorLog("User login", e.getLocalizedMessage());
            }
        }
    }

    //Method which navigates from Login Activity to Main Activity
    public void navigatetoHomeActivity(){
        Intent homeIntent = new Intent(this,MainActivity.class);
        homeIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        homeIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(homeIntent);
        finish();
    }

    //Called when the user clicks the sing up
    public void singUpMessage(View view) {
        Intent registerIntent = new Intent(this, RegisterActivity.class);
        registerIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(registerIntent);
        finish();
    }
}
