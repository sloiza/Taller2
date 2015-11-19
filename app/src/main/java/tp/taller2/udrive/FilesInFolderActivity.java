package tp.taller2.udrive;

import android.app.DialogFragment;
import android.app.SearchManager;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.SearchView;
import android.util.Log;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.loopj.android.http.HttpDelete;
import com.loopj.android.http.HttpGet;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

public class FilesInFolderActivity extends AppCompatActivity implements  SwipeRefreshLayout.OnRefreshListener,
        ShareItemDialogFragment.ShareItemDialogListener, NewFolderDialogFragment.NewFolderDialogListener{

    List<String> filesList = new ArrayList<>();
    List<String> foldersList = new ArrayList<>();
    private ListView lv;
    private ListView folderlv;
    HashMap<String, String> user;
    String email;
    SessionManager session;
    String itemName;
    SwipeRefreshLayout swipeRefreshLayout;
    private static int FILE_SELECT_CODE = 1;
    private String filePath = null;
    long totalSize = 0;
    String dialogInput;
    GPSTracker gps;
    String itemClick;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_files_in_folder);
        getSupportActionBar().setDisplayShowHomeEnabled(true);



        lv = (ListView) findViewById(R.id.list_view);
        session = new SessionManager(getApplicationContext());

        Intent intent = getIntent();
        itemName = intent.getStringExtra("folderName");
        getSupportActionBar().setTitle(itemName);

        registerForContextMenu(lv);

        folderlv = (ListView) findViewById(R.id.folder_list_view);

        Utility.setDynamicHeight(lv);
        Utility.setDynamicHeight(folderlv);

        registerForContextMenu(folderlv);


        swipeRefreshLayout = (SwipeRefreshLayout) findViewById(R.id.swipe_refresh_layout);
        swipeRefreshLayout.setOnRefreshListener(this);
        swipeRefreshLayout.setColorSchemeResources(R.color.ColorPrimary);

        session = new SessionManager(getApplicationContext());
        user = session.getUserDetails();
        email = user.get(SessionManager.KEY_EMAIL);

        swipeRefreshLayout.post(new Runnable() {
                                    @Override
                                    public void run() {
                                        //swipeRefreshLayout.setRefreshing(true);
                                        new getFolderFilesService().execute("http://192.168.1.9:8080/carpetas");
                                    }
                                }
        );
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);
        if (v.getId()==R.id.list_view || v.getId()==R.id.folder_list_view) {
            MenuInflater inflater = getMenuInflater();
            inflater.inflate(R.menu.menu_context, menu);
        }
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();
        itemClick = ((TextView) info.targetView).getText().toString();
        switch(item.getItemId()) {
            case R.id.item_share:
                shareCurrentItem();
                return true;
            case R.id.item_delete:
                deleteCurrentItem();
                return true;
            case R.id.item_download:
                downloadCurrentItem();
                return true;
            case R.id.item_details:
                showItemDetails();
                return true;
            default:
                return super.onContextItemSelected(item);
        }
    }

    private void showItemDetails() {
        Intent intent = new Intent(getApplicationContext(), ListItemDetailsActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.putExtra("itemName", itemClick);
        startActivity(intent);
    }

    private void shareCurrentItem() {
        Toast.makeText(getApplicationContext(), "Share item click", Toast.LENGTH_LONG).show();
        showShareFileDialog();
    }

    private void deleteCurrentItem() {
        Toast.makeText(getApplicationContext(), "Delete item click", Toast.LENGTH_LONG).show();
        if(!Utility.getExtensionFromFile(itemClick).isEmpty()){
            Toast.makeText(getApplicationContext(), "Delete file", Toast.LENGTH_LONG).show();
            new deleteFileService().execute("http://192.168.1.9:8080/archivos");
        } else {
            Toast.makeText(getApplicationContext(), "Delete folder", Toast.LENGTH_LONG).show();
            new deleteFolderService().execute("http://192.168.1.9:8080/carpetas");
        }
    }

    private void downloadCurrentItem() {
        Toast.makeText(getApplicationContext(), "Download item click", Toast.LENGTH_LONG).show();
        //new getDownloadFileService().execute("http://192.168.0.16:8080/descargar");
    }

    public void showShareFileDialog() {
        DialogFragment dialog = ShareItemDialogFragment.newInstance(itemClick);
        dialog.show(getFragmentManager(), "shareUsers");
    }

    @Override
    public void onRefresh() {
        filesList.clear();
        foldersList.clear();
        new getFolderFilesService().execute("http://192.168.1.9:8080/carpetas");
    }

    public String getFolderFiles(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(URL);
        HashMap<String, String> user = session.getUserDetails();
        String email = user.get(SessionManager.KEY_EMAIL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", itemName);
            json.put("direccion", "tmp/" + email + "/");
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

    private class getFolderFilesService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getFolderFiles(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                JSONArray fileArray;
                JSONArray folderArray;
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    if(jsonObject.has("carpetas")){
                        folderArray = jsonObject.getJSONArray("carpetas");
                        for (int i=0; i<folderArray.length(); i++) {
                            String folderPath = folderArray.getString(i);
                            String folderName = folderPath.substring(folderPath.lastIndexOf("/") + 1);
                            foldersList.add(folderName);
                        }
                    }
                    if(jsonObject.has("archivos")){
                        fileArray = jsonObject.getJSONArray("archivos");
                        for (int i=0; i<fileArray.length(); i++) {
                            String filePath = fileArray.getString(i);
                            String fileName = filePath.substring(filePath.lastIndexOf("/") + 1);
                            filesList.add(fileName);
                        }
                    }
                    ArrayAdapter<String> files = new ArrayAdapter<>(getApplicationContext(),R.layout.list_item,filesList);
                    lv.setAdapter(files);
                    ArrayAdapter<String> folders = new ArrayAdapter<>(getApplicationContext(),R.layout.list_item,foldersList);
                    folderlv.setAdapter(folders);
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }

    public String getDownloadFile(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", Utility.getNameFromFile(itemClick));
            json.put("direccion", "tmp/" + email + "/" + itemName);
            json.put("extension", Utility.getExtensionFromFile(itemClick));
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
                Log.d("Error", "Failed to download file");
            }
        } catch (Exception e) {
            Log.d("Error", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class getDownloadFileService extends AsyncTask<String, Void, String> {

        protected String doInBackground(String... urls) {
            return getDownloadFile(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                //devuelve los bytes
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }

    public String deleteFiles(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpDelete httpDelete = new HttpDelete(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre",Utility.getNameFromFile(itemClick));
            json.put("extension", Utility.getExtensionFromFile(itemClick));
            json.put("propietario",email);
            json.put("baja_logica","si");
            json.put("direccion","tmp/" + email + "/" + itemName);
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
                Log.d("Error", "Failed to delete file");
            }
        } catch (Exception e) {
            Log.d("Error", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class deleteFileService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return deleteFiles(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                Log.d("Error", e.getLocalizedMessage());
            }
        }
    }

    public String deleteFolder(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpDelete httpDelete = new HttpDelete(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", itemClick);
            json.put("propietario",email);
            json.put("baja_logica","si");
            json.put("direccion","tmp/" + email + "/" + itemName);
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
                Log.d("Error", "Failed to delete folder");
            }
        } catch (Exception e) {
            Log.d("Error", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class deleteFolderService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return deleteFolder(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if(status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                Log.d("Error", e.getLocalizedMessage());
            }
        }
    }

    @Override
    public void onDialogPositiveClick(DialogFragment dialog) {
        // User touched the dialog's positive button
         if (dialog.getTag().equals("newFolder")) {
             Log.d("dialogInput", dialogInput);
            new postNewFolderService().execute("http://192.168.1.9:8080/carpetas");
        } else if (dialog.getTag().equals("shareUsers")) {
            Log.d("itemName", itemClick);
            Log.d("dialogInput", dialogInput);
             if(!Utility.getExtensionFromFile(itemClick).isEmpty()){
                 Toast.makeText(getApplicationContext(), "share file", Toast.LENGTH_LONG).show();
                 new shareFileService().execute("http://192.168.1.9:8080/compartirArchivo");
             } else {
                 new shareFolderService().execute("http://192.168.1.9:8080/compartirCarpeta");
                 Toast.makeText(getApplicationContext(), "share folder", Toast.LENGTH_LONG).show();
             }
        }
    }

    @Override
    public void onDialogNegativeClick(DialogFragment dialog) {

    }

    @Override
    public void onReturnValue(String input) {
        dialogInput = input;
    }

    @Override
    public void onReturnItemName(String item) {
        itemName = item;
    }

    public void showNewFolderDialog() {
        // Create an instance of the dialog fragment and show it
        DialogFragment dialog = new NewFolderDialogFragment();
        dialog.show(getFragmentManager(), "newFolder");
    }

    public void newFolder(View view) {
        showNewFolderDialog();
    }

    public void uploadFile(View view) {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("*/*");
        intent.addCategory(Intent.CATEGORY_OPENABLE);

        try {
            startActivityForResult(Intent.createChooser(intent, "Select a File to Upload"), FILE_SELECT_CODE);
        } catch (android.content.ActivityNotFoundException ex) {
            // Potentially direct the user to the Market with a Dialog
            Toast.makeText(getApplicationContext(), "Please install a File Manager.", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == FILE_SELECT_CODE && resultCode == -1 && null != data) {
            // Get the Uri of the selected file
            Uri uri = data.getData();
            // Get the file instance
            filePath = uri.getPath();
            // Initiate the upload
            new UploadFileMetadatosToServer().execute();
        }
    }

    /**
     * Uploading the file to server
     */
    class UploadFileToServer extends AsyncTask<Void, Integer, String> {
        @Override
        protected String doInBackground(Void... params) {
            return uploadFile();
        }

        @SuppressWarnings("deprecation")
        private String uploadFile() {
            String responseString;
            HttpURLConnection con;
            URL url;

            try {
                AndroidMultiPartEntity entity = new AndroidMultiPartEntity(
                        new AndroidMultiPartEntity.ProgressListener() {

                            @Override
                            public void transferred(long num) {
                                publishProgress((int) ((num / (float) totalSize) * 100));
                            }
                        });

                File file = new File(filePath);
                url = new URL("http://192.168.1.9:8080/archivos?");
                con = (HttpURLConnection) url.openConnection();
                con.setDoOutput(true);
                con.setFixedLengthStreamingMode(file.length());

                OutputStream out = con.getOutputStream();
                out.write(Utility.convertFileToByteArray(file));
                out.flush();
                out.close();
                int statusCode = con.getResponseCode();
                if (statusCode == 200) {
                    responseString = con.getResponseMessage();
                } else {
                    responseString = "Error occurred! Http Status Code: " + statusCode;
                }
            } catch (IOException e) {
                responseString = e.toString();
            }
            return responseString;
        }

        @Override
        protected void onPostExecute(String result) {
            //try {
            Log.d("respuesta: ", result);
            //JSONObject jsonObject = new JSONObject(result);
            //Object status = jsonObject.get("estado");
            //Object message = jsonObject.get("mensaje");
            //if (status.equals("ok")) {
            Toast.makeText(getApplicationContext(), "Upload file success", Toast.LENGTH_LONG).show();
            //} else {
            //    Toast.makeText(getApplicationContext(), "upload file error", Toast.LENGTH_LONG).show();
            //}
            //} catch (JSONException e) {
            // e.printStackTrace();
            //}

            super.onPostExecute(result);
        }

    }

    /**
     * Uploading the file to server
     */
    class UploadFileMetadatosToServer extends AsyncTask<Void, Integer, String> {

        @Override
        protected String doInBackground(Void... params) {
            return uploadFileMetadatos();
        }

        @SuppressWarnings("deprecation")
        private String uploadFileMetadatos() {
            String responseString = "";
            HttpURLConnection con;
            URL url;

            try {
                AndroidMultiPartEntity entity = new AndroidMultiPartEntity(
                        new AndroidMultiPartEntity.ProgressListener() {

                            @Override
                            public void transferred(long num) {
                                publishProgress((int) ((num / (float) totalSize) * 100));
                            }
                        });

                url = new URL("http://192.168.1.9:8080/archivos?");
                con = (HttpURLConnection) url.openConnection();
                con.setDoOutput(true);

                JSONObject json = new JSONObject();
                File file = new File(filePath);
                json.put("nombre", Utility.getNameFromFile(file.getName()));
                json.put("extension", Utility.getExtensionFromFile(filePath));
                json.put("etiqueta", "archivo");
                json.put("fecha_ulti_modi", "26102015");
                json.put("usuario_ulti_modi", "1234");
                json.put("propietario", email);
                json.put("baja_logica", "no");
                json.put("direccion", "tmp/" + email + "/" + itemName + "/");

                OutputStream out = con.getOutputStream();
                out.write(json.toString().getBytes());
                out.flush();
                out.close();
                int statusCode = con.getResponseCode();
                if (statusCode == 200) {
                    responseString = con.getResponseMessage();
                    Log.d("respuesta metadatos", responseString);
                } else {
                    responseString = "Error occurred! Http Status Code: " + statusCode;
                }
            } catch (IOException e) {
                responseString = e.toString();
            } catch (JSONException e) {
                e.printStackTrace();
            }
            return responseString;
        }

        @Override
        protected void onPostExecute(String result) {
            //try {
            Log.d("respuesta: ", result);
            //JSONObject jsonObject = new JSONObject(result);
            //Object status = jsonObject.get("estado");
            //Object message = jsonObject.get("mensaje");
            //if (status.equals("ok")) {
            new UploadFileToServer().execute();
            //} else {
            //    Toast.makeText(getApplicationContext(), "upload file error", Toast.LENGTH_LONG).show();
            //}
            //} catch (JSONException e) {
            //  e.printStackTrace();
            //}

            super.onPostExecute(result);
        }

    }

    public String postNewFolder(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", dialogInput);
            json.put("etiqueta", "carpeta");
            json.put("fecha_ulti_modi", "26102015");
            json.put("usuario_ulti_modi", "0");
            json.put("propietario", email);
            json.put("baja_logica", "no");
            json.put("direccion", "tmp/" + email + "/" + itemName);
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
                Log.d("JSON", "Failed to create new folder");
            }
        } catch (Exception e) {
            Log.d("readJSONFeed", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class postNewFolderService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return postNewFolder(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if (status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }

    public String shareFile(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        HashMap<String, String> user = session.getUserDetails();
        String email = user.get(SessionManager.KEY_EMAIL);
        JSONObject json = new JSONObject();
        JSONArray jsonArray = new JSONArray();
        try {
            jsonArray.put(dialogInput);
            json.put("nombre", Utility.getNameFromFile(itemClick));
            json.put("extension", Utility.getExtensionFromFile(itemClick));
            json.put("direccion", "tmp/" + email + "/" + itemName);
            json.put("usuarios", jsonArray);
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

    private class shareFileService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return shareFile(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                Log.d("result", result);
                Log.d("Status", status.toString());
                Log.d("Message", message.toString());
                if (status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }

        public String shareFolder(String URL) {
            StringBuilder stringBuilder = new StringBuilder();
            HttpClient httpClient = new DefaultHttpClient();
            HttpPost httpPost = new HttpPost(URL);
            JSONObject json = new JSONObject();
            JSONArray jsonArray = new JSONArray();
            try {
                jsonArray.put(dialogInput);
                json.put("nombre", itemClick);
                json.put("direccion", "tmp/" + email + "/" + itemName);
                json.put("usuarios", jsonArray);
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
                    Log.d("JSON", "Failed to share folder");
                }
            } catch (Exception e) {
                Log.d("readJSONFeed", e.getLocalizedMessage());
            }
            return stringBuilder.toString();
        }

        private class shareFolderService extends AsyncTask<String, Void, String> {
            protected String doInBackground(String... urls) {
                return shareFolder(urls[0]);
            }

            protected void onPostExecute(String result) {
                try {
                    JSONObject jsonObject = new JSONObject(result);
                    Object status = jsonObject.get("estado");
                    Object message = jsonObject.get("mensaje");
                    if (status.equals("ok")) {
                        Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    }
                } catch (Exception e) {
                    Log.d("ReadJSONTask", e.getLocalizedMessage());
                }
            }
        }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        MenuItem searchItem = menu.findItem(R.id.action_search);

        SearchManager searchManager = (SearchManager) FilesInFolderActivity.this.getSystemService(Context.SEARCH_SERVICE);
        SearchView searchView = (SearchView) searchItem.getActionView();
        searchView.setSearchableInfo(searchManager.getSearchableInfo(FilesInFolderActivity.this.getComponentName()));

        return super.onCreateOptionsMenu(menu);
    }

    /**
     * Handle action bar item clicks here. The action bar will
     * automatically handle clicks on the Home/Up button, so long
     * as you specify a parent activity in AndroidManifest.xml.
     *
     * @param item
     * @return
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Take appropriate action for each action item click
        switch (item.getItemId()) {
            case R.id.action_search:
                return true;
            case R.id.action_location_found:
                LocationFound();
                return true;
            case R.id.action_settings:
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

      /**
     * Launching new activity
     */
    private void LocationFound() {
        gps = new GPSTracker(this);
        // check if GPS enabled
        if (gps.canGetLocation()) {
            double latitude = gps.getLatitude();
            double longitude = gps.getLongitude();
            Uri gmmIntentUri = Uri.parse("geo:" + latitude + "," + longitude);
            Intent mapIntent = new Intent(Intent.ACTION_VIEW, gmmIntentUri);
            mapIntent.setPackage("com.google.android.apps.maps");
            if (mapIntent.resolveActivity(getPackageManager()) != null) {
                startActivity(mapIntent);
            }
        } else {
            // can't get location
            // GPS or Network is not enabled
            // Ask user to enable GPS/network in settings
            gps.showSettingsAlert();
        }
    }

}
