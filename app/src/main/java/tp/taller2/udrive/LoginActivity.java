package tp.taller2.udrive;

import android.app.ProgressDialog;
import android.content.Intent;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.loopj.android.http.RequestParams;
import com.loopj.android.http.AsyncHttpClient;
import com.loopj.android.http.AsyncHttpResponseHandler;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.Console;

import cz.msebera.android.httpclient.Header;

public class LoginActivity extends AppCompatActivity {

    ProgressDialog prgDialog;
    TextView errorMsg;
    EditText emailET;
    EditText passwordET;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        errorMsg = (TextView)findViewById(R.id.login_error);
        emailET = (EditText)findViewById(R.id.email_message);
        passwordET = (EditText)findViewById(R.id.password_message);

        prgDialog = new ProgressDialog(this);
        prgDialog.setMessage(getString(R.string.wait));
        prgDialog.setCancelable(false);
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
        RequestParams params = new RequestParams();
        if(Utility.isNotNull(email) && Utility.isNotNull(password)){
            if(Utility.validateEmail(email)){
                params.put("username", email);
            }
            else{
                emailET.requestFocus();
                emailET.setError(getString(R.string.email_error));
            }
            if(Utility.validatePassword(password)){
                params.put("password", password);
                invokeWS(params);
            } else {
                passwordET.requestFocus();
                passwordET.setError(getString(R.string.password_error));
            }
        } else{
            Toast.makeText(getApplicationContext(), R.string.error_emptyFields, Toast.LENGTH_LONG).show();
        }
    }

    public String getIpAddress() {
        WifiManager wifiManager = (WifiManager) getSystemService(WIFI_SERVICE);
        WifiInfo wifiInfo = wifiManager.getConnectionInfo();
        int ip = wifiInfo.getIpAddress();

        return String.format(
                "%d.%d.%d.%d",
                (ip & 0xff),
                (ip >> 8 & 0xff),
                (ip >> 16 & 0xff),
                (ip >> 24 & 0xff));
    }

    //Method that performs RESTful webservice invocations
    public void invokeWS(RequestParams params){
        prgDialog.show();
        // Make RESTful webservice call using AsyncHttpClient object
        AsyncHttpClient client = new AsyncHttpClient();
        String ipAddress = getIpAddress();
        Log.d("ip", ipAddress);
        client.put("http://192.168.0.14:8080/useraccount/login/dologin", params, new AsyncHttpResponseHandler() {
            @Override
            public void onSuccess(int statusCode, Header[] headers, byte[] responseBody) {
                prgDialog.hide();

                if (statusCode == 200) {

                    /*try {

                        String response = responseBody.toString();
                        JSONObject obj = new JSONObject(response);
                        if (obj.getBoolean("status")) {*/
                        if(true) {
                            Toast.makeText(getApplicationContext(), R.string.success_login, Toast.LENGTH_LONG).show();
                            navigatetoHomeActivity();
                        }
                        /*} else {
                            errorMsg.setText(obj.getString("error_msg"));
                            Toast.makeText(getApplicationContext(), obj.getString("error_msg"), Toast.LENGTH_LONG).show();
                        }
                    } catch (JSONException e) {
                        // TODO Auto-generated catch block
                        Toast.makeText(getApplicationContext(), R.string.invalidJsonResponse, Toast.LENGTH_LONG).show();
                        e.printStackTrace();

                    }*/
                }
            }

            @Override
            public void onFailure(int statusCode, Header[] headers, byte[] responseBody, Throwable error) {
                prgDialog.hide();
                if (statusCode == 404) {
                    Toast.makeText(getApplicationContext(), R.string.resourceNotFound, Toast.LENGTH_LONG).show();
                } else if (statusCode == 500) {
                    Toast.makeText(getApplicationContext(), R.string.error_serverEnd, Toast.LENGTH_LONG).show();
                } else {
                    Toast.makeText(getApplicationContext(), R.string.unexpected_error, Toast.LENGTH_LONG).show();
                }
            }
        });
    }

    //Method which navigates from Login Activity toHome Activity
    public void navigatetoHomeActivity(){
        Intent homeIntent = new Intent(this,UsersActivity.class);
        homeIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(homeIntent);
    }

    //Called when the user clicks the sing up
    public void singUpMessage(View view) {
        Intent registerIntent = new Intent(this, RegisterActivity.class);
        registerIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(registerIntent);
    }
}
