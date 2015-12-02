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
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.entity.InputStreamEntity;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

public class FilesInFolderActivity extends AppCompatActivity implements  AbsListView.OnItemClickListener, SwipeRefreshLayout.OnRefreshListener,
        ShareItemDialogFragment.ShareItemDialogListener, NewFolderDialogFragment.NewFolderDialogListener{

    List<String> filesList = new ArrayList<>();
    List<String> foldersList = new ArrayList<>();
    private ListView lv;
    private ListView folderlv;
    HashMap<String, String> user;
    String email;
    SessionManager session;
    String name, surname;
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
        folderlv.setOnItemClickListener(this);

        swipeRefreshLayout = (SwipeRefreshLayout) findViewById(R.id.swipe_refresh_layout);
        swipeRefreshLayout.setOnRefreshListener(this);
        swipeRefreshLayout.setColorSchemeResources(R.color.ColorPrimary);

        session = new SessionManager(getApplicationContext());
        user = session.getUserDetails();
        email = user.get(SessionManager.KEY_EMAIL);
        name = user.get(SessionManager.KEY_NAME);
        surname = user.get(SessionManager.KEY_SURNAME);

        new getFolderFilesService().execute(session.getIp() + session.getPort() + "carpetas");

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
        showShareFileDialog();
    }

    private void deleteCurrentItem() {
        if(!Utility.getExtensionFromFile(itemClick).isEmpty()){
            new deleteFileService().execute(session.getIp() + session.getPort() + "archivos");
        } else {
            new deleteFolderService().execute(session.getIp() + session.getPort() + "carpetas");
        }
    }

    private void downloadCurrentItem() {
        //new getDownloadFileService().execute(session.getIp() + session.getPort() + "descargar");
    }

    public void showShareFileDialog() {
        DialogFragment dialog = ShareItemDialogFragment.newInstance(itemClick);
        dialog.show(getFragmentManager(), "shareUsers");
    }

    @Override
    public void onRefresh() {
        filesList.clear();
        foldersList.clear();
        new getFolderFilesService().execute(session.getIp() + session.getPort() + "carpetas");
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Intent intent = new Intent(getApplicationContext(),FilesInFolderActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.putExtra("folderName", foldersList.get(position));
        startActivity(intent);
    }

    public String getFolderFiles(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", itemName);
            json.put("direccion", "archivos/" + email + "/");
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
                Log.e("Folder files", "service status code: " + statusCode);
                Utility.appendToErrorLog("Folder files", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Folder files", e.getLocalizedMessage());
            Utility.appendToErrorLog("Folder files", e.getLocalizedMessage());
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
                    Log.i("Folder files", message.toString());
                    Utility.appendToInfoLog("Folder files", message.toString());
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
                    Log.d("Folder files", jsonObject.toString());
                    Utility.appendToDebugLog("Folder files", jsonObject.toString());
                    ArrayAdapter<String> files = new ArrayAdapter<>(getApplicationContext(),R.layout.list_item,filesList);
                    lv.setAdapter(files);
                    ArrayAdapter<String> folders = new ArrayAdapter<>(getApplicationContext(),R.layout.list_item,foldersList);
                    folderlv.setAdapter(folders);
                    swipeRefreshLayout.setRefreshing(false);
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Folder files", message.toString());
                    Utility.appendToErrorLog("Folder files", message.toString());
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
            json.put("direccion", "archivos/" + email + "/" + itemName);
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
                Log.e("Folder download file", "status code: " + statusCode);
                Utility.appendToErrorLog("Folder download file", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Folder download file", e.getLocalizedMessage());
            Utility.appendToErrorLog("Folder download file", e.getLocalizedMessage());
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
                Log.e("Folder download file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Folder download file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Folder download file", e.getLocalizedMessage());
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
            json.put("direccion","archivos/" + email + "/" + itemName);
            httpDelete.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpDelete.setHeader("Content-Type", "application/json");
            httpDelete.setHeader("Accept-Encoding", "application/json");
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
                Log.e("Folder delete file", "status code: " + statusCode);
                Utility.appendToErrorLog("Folder delete file", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Folder delete file", e.getLocalizedMessage());
            Utility.appendToErrorLog("Folder delete file", e.getLocalizedMessage());
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
                    Log.i("Folder delete file", message.toString());
                    Utility.appendToInfoLog("Folder delete file", message.toString());
                    Log.d("Folder delete file", jsonObject.toString());
                    Utility.appendToDebugLog("Folder delete file", jsonObject.toString());
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Folder delete file", message.toString());
                    Utility.appendToErrorLog("Folder delete file", message.toString());
                }
            } catch (Exception e) {
                Log.e("Folder delete file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Folder delete file", e.getLocalizedMessage());
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
            json.put("direccion","archivos/" + email + "/" + itemName + "/");
            httpDelete.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpDelete.setHeader("Content-Type", "application/json");
            httpDelete.setHeader("Accept-Encoding", "application/json");
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
                Log.e("Folder delete folder", "status code: " + statusCode);
                Utility.appendToErrorLog("Folder delete folder", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Folder delete folder", e.getLocalizedMessage());
            Utility.appendToErrorLog("Folder delete folder", e.getLocalizedMessage());
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
                    Log.i("Folder delete folder", message.toString());
                    Utility.appendToInfoLog("Folder delete folder", message.toString());
                    Log.d("Folder delete folder", jsonObject.toString());
                    Utility.appendToDebugLog("Folder delete folder", jsonObject.toString());
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Folder delete folder", message.toString());
                    Utility.appendToErrorLog("Folder delete folder", message.toString());
                }
            } catch (Exception e) {
                Log.e("Folder delete folder", e.getLocalizedMessage());
                Utility.appendToErrorLog("Folder delete folder", e.getLocalizedMessage());
            }
        }
    }

    @Override
    public void onDialogPositiveClick(DialogFragment dialog) {
         if (dialog.getTag().equals("newFolder")) {
            new postNewFolderService().execute(session.getIp() + session.getPort() + "carpetas");
        } else if (dialog.getTag().equals("shareUsers")) {
             if(!Utility.getExtensionFromFile(itemClick).isEmpty()){
                 new shareFileService().execute(session.getIp() + session.getPort() + "compartirArchivo");
             } else {
                 new shareFolderService().execute(session.getIp() + session.getPort() + "compartirCarpeta");
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
            Toast.makeText(getApplicationContext(), "Please install a File Manager.", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == FILE_SELECT_CODE && resultCode == -1 && null != data) {
            Uri uri = data.getData();
            filePath = uri.getPath();
            SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
            String currentDateAndTime = sdf.format(new Date());
            SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd-MM-yyyy");
            String currentDate = simpleDateFormat.format(new Date());
            File file = new File(filePath);
            JSONArray jsonArray = new JSONArray();
            jsonArray.put("file");
            try {
                String lastModDate = URLEncoder.encode(currentDateAndTime, "utf-8");
                String label = URLEncoder.encode(jsonArray.toString(), "utf-8");
                new UploadFileToServer().execute(session.getIp() + session.getPort() + "archivos?nombre=" + Utility.getNameFromFile(file.getName())
                        + "&extension=" + Utility.getExtensionFromFile(filePath) + "&etiqueta=file"
                        + "&fecha_ulti_modi=" + currentDate + "&usuario_ulti_modi=" + email + "&fecha_creacion=" + currentDate
                        + "&propietario=" + email + "&baja_logica=no&direccion=" + "archivos/" + email + "/" + itemName + "/");
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            }
        }
    }

    public String uploadFile(String urlServer) {
        HttpURLConnection connection;
        DataOutputStream outputStream;
        StringBuilder sb = null;
        int serverResponseCode;

        int bytesRead, bytesAvailable, bufferSize;
        byte[] buffer;
        int maxBufferSize = 1*1024*1024;

        try
        {
            FileInputStream fileInputStream = new FileInputStream(new File(filePath) );

            URL url = new URL(urlServer);
            connection = (HttpURLConnection) url.openConnection();

            // Allow Inputs &amp; Outputs.
            connection.setDoInput(true);
            connection.setDoOutput(true);
            connection.setUseCaches(false);

            // Set HTTP method to POST.
            connection.setRequestMethod("POST");

            connection.setRequestProperty("Connection", "Keep-Alive");
            connection.setRequestProperty("Content-Type", "multipart/form-data");

            outputStream = new DataOutputStream( connection.getOutputStream() );

            bytesAvailable = fileInputStream.available();
            bufferSize = Math.min(bytesAvailable, maxBufferSize);
            buffer = new byte[bufferSize];

            // Read file
            bytesRead = fileInputStream.read(buffer, 0, bufferSize);

            while (bytesRead > 0)
            {
                outputStream.write(buffer, 0, bufferSize);
                bytesAvailable = fileInputStream.available();
                bufferSize = Math.min(bytesAvailable, maxBufferSize);
                bytesRead = fileInputStream.read(buffer, 0, bufferSize);
            }

            // Responses from the server (code and message)
            serverResponseCode = connection.getResponseCode();
            InputStream is;
            if (serverResponseCode >= 400) {
                is = connection.getErrorStream();
            } else {
                is = connection.getInputStream();
            }
            sb = new StringBuilder();
            BufferedReader rd = new BufferedReader(new InputStreamReader(is));
            String line;
            while ((line = rd.readLine()) != null) {
                sb.append(line);
            }
            fileInputStream.close();
            outputStream.flush();
            outputStream.close();
        }
        catch (Exception ex)
        {
            //Exception handling
        }
        return sb.toString();
    }

    /**
     * Uploading the file to server
     */
    class UploadFileToServer extends AsyncTask<String, Void, String> {

        protected String doInBackground(String... urls) {
            return uploadFile(urls[0]);
        }

        @Override
        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if (status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("Folder Upload file", message.toString());
                    Utility.appendToInfoLog("Folder Upload file", message.toString());
                    Log.d("Folder Upload file", jsonObject.toString());
                    Utility.appendToDebugLog("Folder Upload file", jsonObject.toString());
                    session.updateStorageUsed(session.getUserStorageUsed() + 0.3f);
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Folder Upload file", message.toString());
                    Utility.appendToErrorLog("Folder Upload file", message.toString());
                }
            } catch (JSONException e) {
                Log.e("Folder Upload file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Folder Upload file", e.getLocalizedMessage());
            }
        }
    }

    public String postNewFolder(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        JSONObject json = new JSONObject();
        JSONArray jsonArray = new JSONArray();
        SimpleDateFormat sdf = new SimpleDateFormat("ddmmyyyyy_HHmmss");
        String currentDateAndTime = sdf.format(new Date());
        try {
            Log.d("dialogInput", dialogInput);
            jsonArray.put("carpeta");
            json.put("nombre", dialogInput);
            json.put("etiqueta", jsonArray);
            json.put("fecha_ulti_modi", currentDateAndTime);
            //json.put("fecha_creacion", currentDateAndTime);
            //json.put("compartido_con", "");
            json.put("usuario_ulti_modi", email);
            json.put("propietario", email);
            json.put("baja_logica", "no");
            json.put("direccion", "archivos/" + email + "/" + itemName + "/");
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
                Log.e("Folder New folder", "service status code: " + statusCode);
                Utility.appendToErrorLog("Folder New folder", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Folder New folder", e.getLocalizedMessage());
            Utility.appendToErrorLog("Folder New folder", e.getLocalizedMessage());
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
                    Log.i("Folder New folder", message.toString());
                    Utility.appendToInfoLog("Folder New folder", message.toString());
                    Log.d("Folder New folder", jsonObject.toString());
                    Utility.appendToDebugLog("Folder New folder", jsonObject.toString());
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Folder New folder", message.toString());
                    Utility.appendToErrorLog("Folder New folder", message.toString());
                }
            } catch (Exception e) {
                Log.e("Folder New folder", e.getLocalizedMessage());
                Utility.appendToErrorLog("Folder New folder", e.getLocalizedMessage());
            }
        }
    }

    public String shareFile(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        JSONObject json = new JSONObject();
        JSONArray jsonArray = new JSONArray();
        try {
            jsonArray.put(dialogInput);
            json.put("nombre", Utility.getNameFromFile(itemName));
            json.put("extension", Utility.getExtensionFromFile(itemName));
            json.put("direccion", "archivos/" + email + "/");
            json.put("usuarios", jsonArray);
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
                Log.e("Folder Share file", "service status code: " + statusCode);
                Utility.appendToErrorLog("Folder Share file", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Folder Share file", e.getLocalizedMessage());
            Utility.appendToErrorLog("Folder Share file", e.getLocalizedMessage());
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
                if (status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("Folder Share file", message.toString());
                    Utility.appendToInfoLog("Folder Share file", message.toString());
                    Log.d("Folder Share file", jsonObject.toString());
                    Utility.appendToDebugLog("Folder Share file", jsonObject.toString());
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Folder Share file", message.toString());
                    Utility.appendToErrorLog("Folder Share file", message.toString());
                }
            } catch (Exception e) {
                Log.e("Folder Share file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Folder Share file", e.getLocalizedMessage());
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
            json.put("nombre", itemName);
            json.put("direccion", "archivos/" + email + "/");
            json.put("usuarios", jsonArray);
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
                Log.e("Folder Share folder", "service status code: " + statusCode);
                Utility.appendToErrorLog("Folder Share folder", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Folder Share folder", e.getLocalizedMessage());
            Utility.appendToErrorLog("Folder Share folder", e.getLocalizedMessage());
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
                    Log.i("Folder Share folder", message.toString());
                    Utility.appendToInfoLog("Folder Share folder", message.toString());
                    Log.d("Folder Share folder", jsonObject.toString());
                    Utility.appendToDebugLog("Folder Share folder", jsonObject.toString());
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Folder Share folder", message.toString());
                    Utility.appendToErrorLog("Folder Share folder", message.toString());
                }
            } catch (Exception e) {
                Log.e("Folder Share folder", e.getLocalizedMessage());
                Utility.appendToErrorLog("Folder Share folder", e.getLocalizedMessage());
            }
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
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
