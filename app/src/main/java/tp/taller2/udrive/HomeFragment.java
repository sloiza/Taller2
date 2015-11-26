package tp.taller2.udrive;

import android.app.DialogFragment;
import android.content.Intent;
import android.os.Environment;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.widget.SwipeRefreshLayout;
import android.util.Base64;
import android.util.Log;
import android.view.ContextMenu;
import android.view.LayoutInflater;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.loopj.android.http.HttpDelete;
import com.loopj.android.http.HttpGet;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

public class HomeFragment extends Fragment implements AbsListView.OnItemClickListener, SwipeRefreshLayout.OnRefreshListener {

    private ListView lv;
    private ListView folderlv;

    SessionManager session;
    String itemName;
    List<String> filesList = new ArrayList<>();
    List<String> foldersList = new ArrayList<>();
    HashMap<String, String> user;
    String email;
    SwipeRefreshLayout swipeRefreshLayout;

    public HomeFragment(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_home, container, false);
        session = new SessionManager(getContext());
        session.checkLogin();

        lv = (ListView) rootView.findViewById(R.id.list_view);
        registerForContextMenu(lv);

        folderlv = (ListView) rootView.findViewById(R.id.folder_list_view);

        Utility.setDynamicHeight(lv);
        Utility.setDynamicHeight(folderlv);

        folderlv.setOnItemClickListener(this);
        registerForContextMenu(folderlv);

        swipeRefreshLayout = (SwipeRefreshLayout) rootView.findViewById(R.id.swipe_refresh_layout);
        swipeRefreshLayout.setOnRefreshListener(this);
        swipeRefreshLayout.setColorSchemeResources(R.color.ColorPrimary);

        user = session.getUserDetails();
        email = user.get(SessionManager.KEY_EMAIL);

        CoordinatorLayout coordinatorLayout = (CoordinatorLayout) rootView.findViewById(R.id.coordinatorLayout);
        Snackbar snackbar = Snackbar.make(coordinatorLayout, "You are logged in as\n" + email, Snackbar.LENGTH_LONG);
        snackbar.show();
        Log.d("IP", session.getIp());
        Log.d("PORT", session.getPort());
         new getUserFilesService().execute(session.getIp() + session.getPort());
        return rootView;
    }

    @Override
    public void onRefresh() {
        filesList.clear();
        foldersList.clear();
        new getUserFilesService().execute(session.getIp() + session.getPort());
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);
        if (v.getId()==R.id.list_view || v.getId()==R.id.folder_list_view) {
            MenuInflater inflater = getActivity().getMenuInflater();
            inflater.inflate(R.menu.menu_context, menu);
        }
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();
        itemName = ((TextView) info.targetView).getText().toString();
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
        Intent intent = new Intent(getContext(), ListItemDetailsActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.putExtra("itemName", itemName);
        startActivity(intent);
    }

    private void shareCurrentItem() {
        showShareFileDialog();
    }

    private void deleteCurrentItem() {
        if(!Utility.getExtensionFromFile(itemName).isEmpty()){
            new deleteFileService().execute(session.getIp() + session.getPort() + "archivos");
        } else {
            new deleteFolderService().execute(session.getIp() + session.getPort() + "carpetas");
        }
    }

    private void downloadCurrentItem() {
        new getDownloadFileService().execute(session.getIp() + session.getPort() + "descargar");
    }

    public void showShareFileDialog() {
        DialogFragment dialog = ShareItemDialogFragment.newInstance(itemName);
        dialog.show(getActivity().getFragmentManager(), "shareUsers");
    }

    public String getUserFiles(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("mail", email);
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
                Log.e("User files", "status code: " + statusCode);
                Utility.appendToErrorLog("User files", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("User files", e.getLocalizedMessage());
            Utility.appendToErrorLog("User files", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class getUserFilesService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getUserFiles(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                JSONArray fileArray;
                JSONArray folderArray;
                if(status.equals("ok")) {
                    Log.i("User files", message.toString());
                    Utility.appendToInfoLog("User files", message.toString());
                    Log.d("User files", jsonObject.toString());
                    Utility.appendToDebugLog("User files", jsonObject.toString());
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
                    ArrayAdapter<String> files = new ArrayAdapter<>(getActivity(),android.R.layout.simple_list_item_1,filesList);
                    ArrayAdapter<String> folders = new ArrayAdapter<>(getActivity(),android.R.layout.simple_list_item_1,foldersList);
                    lv.setAdapter(files);
                    folderlv.setAdapter(folders);
                    swipeRefreshLayout.setRefreshing(false);
                } else {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("User files", message.toString());
                    Utility.appendToErrorLog("User files", message.toString());
                }
            } catch (Exception e) {
                Log.e("User files", e.getLocalizedMessage());
                Utility.appendToErrorLog("User files", e.getLocalizedMessage());
            }
        }
    }



    public String getDownloadFile(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", Utility.getNameFromFile(itemName));
            json.put("direccion", "archivos/" + email + "/");
            json.put("extension", Utility.getExtensionFromFile(itemName));
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
                Log.e("Download file", "status code: " + statusCode);
                Utility.appendToErrorLog("Download file", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Download file", e.getLocalizedMessage());
            Utility.appendToErrorLog("Download file", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class getDownloadFileService extends AsyncTask<String, Void, String> {

          protected String doInBackground(String... urls) {
            return getDownloadFile(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                FileOutputStream out = new FileOutputStream("/sdcard/" + itemName);
                byte[] data = Base64.decode(result, Base64.DEFAULT);
                out.write(data);
                out.flush();
                out.close();
                Toast.makeText(getContext(), "Download file success", Toast.LENGTH_LONG).show();
                Log.i("Download file", "Download file success");
                Utility.appendToInfoLog("Download file", "Download file success");
            } catch (Exception e) {
                Log.e("Download file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Download file", e.getLocalizedMessage());
            }
        }
    }

    public String deleteFile(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpDelete httpDelete = new HttpDelete(URL);
         JSONObject json = new JSONObject();
        try {
            json.put("nombre",Utility.getNameFromFile(itemName));
            json.put("extension", Utility.getExtensionFromFile(itemName));
            json.put("propietario",email);
            json.put("baja_logica","si");
            json.put("direccion","archivos/" + email + "/");
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
                Log.e("Delete file", "status code: " + statusCode);
                Utility.appendToErrorLog("Delete file", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Delete file", e.getLocalizedMessage());
            Utility.appendToErrorLog("Delete file", e.getLocalizedMessage());
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
                if(status.equals("ok")) {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("Delete file", message.toString());
                    Utility.appendToInfoLog("Delete file", message.toString());
                    Log.d("Delete file", jsonObject.toString());
                    Utility.appendToDebugLog("Delete file", jsonObject.toString());
                    session.updateStorageUsed(session.getUserStorageUsed() - 0.3f);
                } else {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Delete file", message.toString());
                    Utility.appendToErrorLog("Delete file", message.toString());
                }
            } catch (Exception e) {
                Log.e("Delete file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Delete file", e.getLocalizedMessage());
            }
        }
    }

    public String deleteFolder(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpDelete httpDelete = new HttpDelete(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", itemName);
            json.put("propietario",email);
            json.put("baja_logica","si");
            json.put("direccion","archivos/" + email + "/");
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
                Log.e("Delete folder", "status code: " + statusCode);
                Utility.appendToErrorLog("Delete folder", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Delete folder", e.getLocalizedMessage());
            Utility.appendToErrorLog("Delete folder", e.getLocalizedMessage());
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
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("Delete folder", message.toString());
                    Utility.appendToInfoLog("Delete folder", message.toString());
                    Log.d("Delete folder", jsonObject.toString());
                    Utility.appendToDebugLog("Delete folder", jsonObject.toString());
                } else {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Delete folder", message.toString());
                    Utility.appendToErrorLog("Delete folder", message.toString());
                }
            } catch (Exception e) {
                Log.e("Delete folder", e.getLocalizedMessage());
                Utility.appendToErrorLog("Delete folder", e.getLocalizedMessage());
            }
        }
    }


    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Intent intent = new Intent(getContext(),FilesInFolderActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.putExtra("folderName", foldersList.get(position));
        startActivity(intent);
    }

 }
