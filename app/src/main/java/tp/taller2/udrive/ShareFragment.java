package tp.taller2.udrive;

import android.app.DialogFragment;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v4.app.Fragment;
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

import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

public class ShareFragment extends Fragment implements AbsListView.OnItemClickListener, SwipeRefreshLayout.OnRefreshListener{

    List<String> filesList = new ArrayList<>();
    private ListView lv;
    private ListView folderlv;
    List<String> foldersList = new ArrayList<>();
    HashMap<String, String> user;
    String email;
    String itemName;
    SwipeRefreshLayout swipeRefreshLayout;
    SessionManager session;
    String shareUserEmail;

    public ShareFragment(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_share, container, false);

        lv = (ListView) rootView.findViewById(R.id.list_view);
        registerForContextMenu(lv);

        folderlv = (ListView) rootView.findViewById(R.id.folder_list_view);

        Utility.setDynamicHeight(lv);
        Utility.setDynamicHeight(folderlv);

        registerForContextMenu(folderlv);
        folderlv.setOnItemClickListener(this);

        session = new SessionManager(getContext());
        user = session.getUserDetails();
        email = user.get(SessionManager.KEY_EMAIL);

        swipeRefreshLayout = (SwipeRefreshLayout) rootView.findViewById(R.id.swipe_refresh_layout);
        swipeRefreshLayout.setOnRefreshListener(this);
        swipeRefreshLayout.setColorSchemeResources(R.color.ColorPrimary);


        new getShareFilesService().execute(session.getIp() + session.getPort() + "compartirArchivo");


        return rootView;
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
        intent.putExtra("pathToShareFile", shareUserEmail);
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

    public String getDownloadFile(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(URL);
        JSONObject json = new JSONObject();
        try {
            Log.d("shareUserEmail", shareUserEmail);
            json.put("nombre", Utility.getNameFromFile(itemName));
            json.put("direccion", shareUserEmail);
            json.put("extension", Utility.getExtensionFromFile(itemName));
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

    public void showShareFileDialog() {
        DialogFragment dialog = new ShareItemDialogFragment();
        dialog.show(getActivity().getFragmentManager(), "shareUsers");
    }

    public String getShareFiles(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(URL);
        HashMap<String, String> user = session.getUserDetails();
        String email = user.get(SessionManager.KEY_EMAIL);
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
                Log.e("Share", "status code: " + statusCode);
                Utility.appendToErrorLog("Share With Me", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Share With Me", e.getLocalizedMessage());
            Utility.appendToErrorLog("Share With Me", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    @Override
    public void onRefresh() {
        filesList.clear();
        foldersList.clear();
        new getShareFilesService().execute(session.getIp() + session.getPort() + "compartirArchivo");
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Intent intent = new Intent(getContext(),FilesInFolderActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.putExtra("folderName", foldersList.get(position));
        startActivity(intent);
    }

    private class getShareFilesService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getShareFiles(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                JSONArray fileArray;
                JSONArray folderArray;
                if(status.equals("ok")) {
                    Log.i("Share With Me", message.toString());
                    Utility.appendToInfoLog("Share With Me", message.toString());
                    Log.d("Share With Me", jsonObject.toString());
                    Utility.appendToDebugLog("Share With Me", jsonObject.toString());
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
                            shareUserEmail = filePath.substring(0 ,filePath.lastIndexOf("/") + 1);
                            String fileName = filePath.substring(filePath.lastIndexOf("/") + 1);
                            filesList.add(fileName);
                        }
                    }
                    ArrayAdapter<String> files = new ArrayAdapter<>(getActivity(),R.layout.list_item,filesList);
                    lv.setAdapter(files);
                    ArrayAdapter<String> folders = new ArrayAdapter<>(getActivity(),R.layout.list_item,foldersList);
                    folderlv.setAdapter(folders);
                    swipeRefreshLayout.setRefreshing(false);
                } else {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Share With Me", message.toString());
                    Utility.appendToErrorLog("Share With Me", message.toString());
                }
            } catch (Exception e) {
                Log.e("Share With Me", e.getLocalizedMessage());
                Utility.appendToErrorLog("Share With Me", e.getLocalizedMessage());
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
            json.put("direccion",shareUserEmail);
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
                Log.e("ShareWithMe delete file", "status code: " + statusCode);
                Utility.appendToErrorLog("ShareWithMe delete file", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("ShareWithMe delete file", e.getLocalizedMessage());
            Utility.appendToErrorLog("ShareWithMe delete file", e.getLocalizedMessage());
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
                    Log.i("ShareWithMe delete file", message.toString());
                    Utility.appendToInfoLog("ShareWithMe delete file", message.toString());
                    Log.d("ShareWithMe delete file", jsonObject.toString());
                    Utility.appendToDebugLog("ShareWithMe delete file", jsonObject.toString());
                } else {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("ShareWithMe delete file", message.toString());
                    Utility.appendToErrorLog("ShareWithMe delete file", message.toString());
                }
            } catch (Exception e) {
                Log.e("ShareWithMe delete file", e.getLocalizedMessage());
                Utility.appendToErrorLog("ShareWithMe delete file", e.getLocalizedMessage());
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
                Log.e("ShrWithMe deleteFolder", "status code: " + statusCode);
                Utility.appendToErrorLog("ShrWithMe deleteFolder", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("ShrWithMe deleteFolder", e.getLocalizedMessage());
            Utility.appendToErrorLog("ShrWithMe deleteFolder", e.getLocalizedMessage());
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
                    Log.i("ShrWithMe deleteFolder", message.toString());
                    Utility.appendToInfoLog("ShrWithMe deleteFolder", message.toString());
                    Log.d("ShrWithMe deleteFolder", jsonObject.toString());
                    Utility.appendToDebugLog("ShrWithMe deleteFolder", jsonObject.toString());
                } else {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("ShrWithMe deleteFolder", message.toString());
                    Utility.appendToErrorLog("ShrWithMe deleteFolder", message.toString());
                }
            } catch (Exception e) {
                Log.e("ShrWithMe deleteFolder", e.getLocalizedMessage());
                Utility.appendToErrorLog("ShrWithMe deleteFolder", e.getLocalizedMessage());
            }
        }
    }
}
