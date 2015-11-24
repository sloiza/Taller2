package tp.taller2.udrive;

import android.content.Intent;
import android.os.AsyncTask;
import android.support.design.widget.TextInputLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import com.loopj.android.http.HttpGet;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpPut;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

public class ListItemDetailsActivity extends AppCompatActivity {

    TextInputLayout inputLayoutName;
    TextInputLayout inputLayoutLabel;
    TextInputLayout inputLayoutModified;
    TextInputLayout inputLayoutOwner;
    TextInputLayout inputLayoutLocation;
    TextInputLayout inputLayoutShareWith;
    TextInputLayout inputLayoutCreated;
    EditText nameET;
    EditText labelET;
    EditText modifiedET;
    EditText ownerET;
    EditText locationET;
    EditText shareWithET;
    EditText createdET;
    String actualItemPath;
    SessionManager session;
    HashMap<String, String> user;
    String email;
    String itemName;
    String name;
    String surname;
    Integer actualVersion;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_item_details);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        inputLayoutName = (TextInputLayout) findViewById(R.id.input_layout_name);
        inputLayoutLabel = (TextInputLayout) findViewById(R.id.input_layout_label);
        inputLayoutModified = (TextInputLayout) findViewById(R.id.input_layout_modified);
        inputLayoutOwner = (TextInputLayout) findViewById(R.id.input_layout_owner);
        inputLayoutLocation = (TextInputLayout) findViewById(R.id.input_layout_location);
        inputLayoutShareWith = (TextInputLayout) findViewById(R.id.input_layout_shareWith);
        inputLayoutCreated = (TextInputLayout) findViewById(R.id.input_layout_created);

        nameET = (EditText)findViewById(R.id.itemName);
        labelET = (EditText)findViewById(R.id.itemLabel);
        modifiedET = (EditText)findViewById(R.id.itemModified);
        locationET = (EditText)findViewById(R.id.itemLocation);
        shareWithET = (EditText)findViewById(R.id.itemShareWith);
        createdET = (EditText)findViewById(R.id.itemCreated);
        ownerET = (EditText)findViewById(R.id.itemOwner);

        session = new SessionManager(getApplicationContext());
        user = session.getUserDetails();
        email = user.get(SessionManager.KEY_EMAIL);
        name = user.get(SessionManager.KEY_NAME);
        surname = user.get(SessionManager.KEY_SURNAME);

        Intent intent = getIntent();
        itemName = intent.getStringExtra("itemName");
        actualItemPath = "tmp/" + email + "/";

        nameET.setText(itemName);
        ownerET.setText(email);
        locationET.setText(actualItemPath);

        new getItemMetadataService().execute(session.getIp() + session.getPort() + "archivos");
    }

    public void editItemDetails(View view) {
        String label = labelET.getText().toString();
        String location = locationET.getText().toString();
        if(Utility.isNotNull(label) && Utility.isNotNull(location)){
                new putModifyItemDetailsService().execute(session.getIp() + session.getPort() + "archivos");
        }else{
            Toast.makeText(getApplicationContext(), R.string.error_emptyFields, Toast.LENGTH_LONG).show();
        }
    }

    public String getItemMetadata(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("direccion",actualItemPath);
            json.put("nombre",Utility.getNameFromFile(itemName));
            json.put("extension",Utility.getExtensionFromFile(itemName));
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
                Log.e("Item metadata", "status code: " + statusCode);
                Utility.appendToErrorLog("Item metadata", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Item metadata", e.getLocalizedMessage());
            Utility.appendToErrorLog("Item metadata", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class getItemMetadataService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getItemMetadata(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                Object label = jsonObject.getJSONArray("etiqueta");
                Object lastModDate = jsonObject.get("fecha_ulti_modi");
                Object lastModUser = jsonObject.get("usuario_ulti_modi");
                //Object version = jsonObject.get("version");
                //Object created = jsonObject.get("fecha_creacion");
                //Object shareWith = jsonObject.get("compartido_con");
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("Item metadata", message.toString());
                    Utility.appendToInfoLog("Item metadata", message.toString());
                    Log.d("Item metadata", jsonObject.toString());
                    Utility.appendToDebugLog("Item metadata", jsonObject.toString());
                    nameET.setText(itemName);
                    labelET.setText(label.toString());
                    createdET.setText("11/10/2015");
                    //createdEt.setText(created.toString());
                    modifiedET.setText(lastModDate.toString() + " by " + lastModUser.toString()); ;
                    ownerET.setText(email);
                    shareWithET.setText("miglesias@gmail.com");
                    //shareWithET.setText(shareWith.toString());
                    locationET.setText("tmp/" + lastModUser.toString() + "/");
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Item metadata", message.toString());
                    Utility.appendToErrorLog("Item metadata", message.toString());
                }
            } catch (Exception e) {
                Log.e("Item metadata", e.getLocalizedMessage());
                Utility.appendToErrorLog("Item metadata", e.getLocalizedMessage());
            }
        }
    }

    public String putModifyItemDetails(String URL) {
        String label = labelET.getText().toString();
        String location = locationET.getText().toString();
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPut httpPut = new HttpPut(URL);
        JSONObject json = new JSONObject();
        JSONArray jsonArray = new JSONArray();
        SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
        String currentDateAndTime = sdf.format(new Date());
        try {
            jsonArray.put(label);
            json.put("nombre",Utility.getNameFromFile(itemName));
            json.put("extension",Utility.getExtensionFromFile(itemName));
            json.put("etiqueta",jsonArray);
            json.put("fecha_ulti_modi",currentDateAndTime);
            json.put("usuario_ulti_modi",email);
            json.put("propietario",email);
            json.put("baja_logica","no");
            json.put("direccion",location);
            json.put("path",actualItemPath);
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
                Log.e("Modify metadata", "status code: " + statusCode);
                Utility.appendToErrorLog("Modify metadata", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Modify metadata", e.getLocalizedMessage());
            Utility.appendToErrorLog("Modify metadata", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class putModifyItemDetailsService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return putModifyItemDetails(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("Modify metadata", message.toString());
                    Utility.appendToInfoLog("Modify metadata", message.toString());
                    Log.d("Modify metadata", jsonObject.toString());
                    Utility.appendToDebugLog("Modify metadata", jsonObject.toString());
                    navigatetoMainActivity();
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Modify metadata", message.toString());
                    Utility.appendToErrorLog("Modify metadata", message.toString());
                }
            } catch (Exception e) {
                Log.e("Modify metadata", e.getLocalizedMessage());
                Utility.appendToErrorLog("Modify metadata", e.getLocalizedMessage());
            }
        }
    }

    public void navigatetoMainActivity(){
        Intent intent = new Intent(getApplicationContext(),MainActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }

}
