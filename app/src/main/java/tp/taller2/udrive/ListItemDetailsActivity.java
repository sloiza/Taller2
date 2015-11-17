package tp.taller2.udrive;

import android.content.Intent;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.support.design.widget.TextInputLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Random;

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
    TextInputLayout inputLayoutLastModDate;
    TextInputLayout inputLayoutLastModUser;
    TextInputLayout inputLayoutOwner;
    TextInputLayout inputLayoutLocation;
    EditText nameET;
    EditText labelET;
    EditText lastModDateET;
    EditText lastModUserET;
    EditText ownerET;
    EditText locationET;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_item_details);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        inputLayoutName = (TextInputLayout) findViewById(R.id.input_layout_name);
        inputLayoutLabel = (TextInputLayout) findViewById(R.id.input_layout_label);
        inputLayoutLastModDate = (TextInputLayout) findViewById(R.id.input_layout_lastModDate);
        inputLayoutLastModUser = (TextInputLayout) findViewById(R.id.input_layout_lastModUser);
        inputLayoutOwner = (TextInputLayout) findViewById(R.id.input_layout_owner);
        inputLayoutLocation = (TextInputLayout) findViewById(R.id.input_layout_location);

        nameET = (EditText)findViewById(R.id.itemName);
        labelET = (EditText)findViewById(R.id.itemLabel);
        lastModDateET = (EditText)findViewById(R.id.itemLastModDate);
        lastModUserET = (EditText)findViewById(R.id.itemLastModUser);
        ownerET = (EditText)findViewById(R.id.itemOwner);
        locationET = (EditText)findViewById(R.id.itemLocation);

        Intent i = getIntent();
        String product = i.getStringExtra("itemName");
        nameET.setText(product);
    }

    public void editItemDetails(View view) {
        String name = nameET.getText().toString();
        String label = labelET.getText().toString();
        String lastModDate = lastModDateET.getText().toString();
        String lastModUser = lastModUserET.getText().toString();
        String owner = ownerET.getText().toString();
        String location = locationET.getText().toString();
        if(Utility.isNotNull(name) && Utility.isNotNull(label) && Utility.isNotNull(lastModDate)
                && Utility.isNotNull(lastModUser) && Utility.isNotNull(owner) && Utility.isNotNull(location)){
                new putModifyItemDetailsService().execute("http://192.168.0.14:8080/archivos?modificar");
        }else{
            Toast.makeText(getApplicationContext(), R.string.error_emptyFields, Toast.LENGTH_LONG).show();
        }
    }

    public String putModifyItemDetails(String URL) {
        String name = nameET.getText().toString();
        String label = labelET.getText().toString();
        String lastModDate = lastModDateET.getText().toString();
        String lastModUser = lastModUserET.getText().toString();
        String owner = ownerET.getText().toString();
        String location = locationET.getText().toString();

        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPut httpPut = new HttpPut(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre",name);
            json.put("etiqueta",label);
            json.put("fecha_ulti_modi",lastModDate);
            json.put("usuario_ulti_modi",lastModUser);
            json.put("propietario",owner);
            json.put("baja_logica","no");
            json.put("direccion",location);
            httpPut.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpPut.setHeader("Content-Type", "application/json");
            httpPut.setHeader("Accept-Encoding", "application/json");
        } catch (Exception e) {
            e.printStackTrace();
        }
        try {
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
                Log.d("JSON", "Failed to download file");
            }
        } catch (Exception e) {
            Log.d("readJSONFeed", e.getLocalizedMessage());
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
                Log.d("result", result);
                Log.d("Status", status.toString());
                Log.d("Message", message.toString());
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    navigatetoMainActivity();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
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
