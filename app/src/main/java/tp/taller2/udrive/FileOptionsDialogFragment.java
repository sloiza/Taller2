package tp.taller2.udrive;

import android.app.Activity;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.AsyncTask;
import android.os.Bundle;
import android.app.DialogFragment;
import android.app.AlertDialog;
import android.util.Log;
import android.widget.Toast;

import com.loopj.android.http.HttpDelete;

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

public class FileOptionsDialogFragment extends DialogFragment {


    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        // Use the Builder class for convenient dialog construction
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setTitle("Choose an option")
                .setItems(R.array.fileOptions, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        // The 'which' argument contains the index position
                        // of the selected item
                        switch(which) {
                            case 0:
                                new deleteFileService().execute("http://192.168.1.9:8080/archivos");
                                break;
                            case 1:
                                break;
                            case 2:
                                break;
                        }
                    }
                });
        // Create the AlertDialog object and return it
        return builder.create();
    }

    public String deleteFile(String URL) {
        //String surname = surnameET.getText().toString();
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpDelete httpDelete = new HttpDelete(URL);
        JSONObject json = new JSONObject();
        try {
            /*json.put("nombre",f.getName());
            json.put("etiqueta","archivo");
            json.put("fecha_ulti_modi","26102015");
            json.put("usuario_ulti_modi","1234");
            json.put("propietario",email);
            json.put("baja_logica","no");
            json.put("direccion","tmp/" + email + "/");*/
            httpDelete.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpDelete.setHeader("Content-Type", "application/json");
            httpDelete.setHeader("Accept-Encoding", "application/json");
        } catch (Exception e) {
            e.printStackTrace();
        }
        try {
            HttpResponse response = httpClient.execute(httpDelete);
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

    private class deleteFileService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return deleteFile(urls[0]);
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
                    Toast.makeText(getContext(), R.string.success_register, Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }
}