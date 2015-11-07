package tp.taller2.udrive;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.TextInputLayout;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;
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
    Toolbar toolbar;
    SessionManager session;
    TextInputLayout inputLayoutEmail, inputLayoutPassword;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        toolbar = (Toolbar) findViewById(R.id.tool_bar);
        setSupportActionBar(toolbar);

        inputLayoutEmail = (TextInputLayout) findViewById(R.id.input_layout_email);
        inputLayoutPassword = (TextInputLayout) findViewById(R.id.input_layout_password);

        errorMsg = (TextView)findViewById(R.id.login_error);
        emailET = (EditText)findViewById(R.id.email_message);
        passwordET = (EditText)findViewById(R.id.password_message);

        session = new SessionManager(getApplicationContext());
    }

    public String getUserLogin(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        String email = emailET.getText().toString();
        String password = passwordET.getText().toString();
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
                Log.d("JSON", "Failed to download file");
            }
        } catch (Exception e) {
            Log.d("readJSONFeed", e.getLocalizedMessage());
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
                String email = emailET.getText().toString();
                if(status.equals("ok")) {
                    session.createLoginSession(email, "Matias", "Carreras");
                    Toast.makeText(getApplicationContext(), R.string.success_login, Toast.LENGTH_LONG).show();
                    navigatetoHomeActivity();
                } else {
                    Toast.makeText(getApplicationContext(), R.string.error_login, Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_login, menu);
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

    /** Called when the user clicks the login */
    public void loginMessage(View view) {
        String email = emailET.getText().toString();
        String password = passwordET.getText().toString();
        if(Utility.isNotNull(email) && Utility.isNotNull(password)){
            if(!Utility.validateEmail(email)){
                emailET.requestFocus();
                inputLayoutEmail.setError(getString(R.string.email_error));
            }else{
                if(Utility.validatePassword(password)){
                    new getUserLoginService().execute("http://192.168.0.16:8080/usuario?");
                }else{
                    passwordET.requestFocus();
                    inputLayoutPassword.setError(getString(R.string.password_error));
                }
            }
        } else{
            Toast.makeText(getApplicationContext(), R.string.error_emptyFields, Toast.LENGTH_LONG).show();
        }
    }

    private void requestFocus(View view) {
        if (view.requestFocus()) {
            getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_VISIBLE);
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
        registerIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        registerIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(registerIntent);
        finish();
    }
}
