package tp.taller2.udrive;

/**
 * Created by mati on 30/09/15.
 */

import android.app.Activity;
import android.app.DialogFragment;
import android.content.Intent;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.widget.SwipeRefreshLayout;
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
    String shareUsers;
    String products [] = {"Taller2.pdf", "tdd.pdf", "RNG.doc"};

    public HomeFragment(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_home, container, false);

        lv = (ListView) rootView.findViewById(R.id.list_view);
        ArrayAdapter<String> productsList = new ArrayAdapter<>(getActivity(),android.R.layout.simple_list_item_1,products);
        lv.setAdapter(productsList);
        registerForContextMenu(lv);

        foldersList.add("taller");
        foldersList.add("tecnicas");
        foldersList.add("distribuidos");

        folderlv = (ListView) rootView.findViewById(R.id.folder_list_view);
        ArrayAdapter<String> folderList = new ArrayAdapter<>(getActivity(),android.R.layout.simple_list_item_1,foldersList);
        folderlv.setAdapter(folderList);

        Utility.setDynamicHeight(lv);
        Utility.setDynamicHeight(folderlv);

        folderlv.setOnItemClickListener(this);
        registerForContextMenu(folderlv);


        swipeRefreshLayout = (SwipeRefreshLayout) rootView.findViewById(R.id.swipe_refresh_layout);
        swipeRefreshLayout.setOnRefreshListener(this);
        swipeRefreshLayout.setColorSchemeResources(R.color.ColorPrimary);

        session = new SessionManager(getContext());
        user = session.getUserDetails();
        email = user.get(SessionManager.KEY_EMAIL);

        CoordinatorLayout coordinatorLayout = (CoordinatorLayout) rootView.findViewById(R.id.coordinatorLayout);
        Snackbar snackbar = Snackbar.make(coordinatorLayout, "You are logged in as\n" + email, Snackbar.LENGTH_LONG);
        snackbar.show();

        /**
         * Showing Swipe Refresh animation on activity create
         * As animation won't start on onCreate, post runnable is used
         */
        swipeRefreshLayout.post(new Runnable() {
                                    @Override
                                    public void run() {
                                        //swipeRefreshLayout.setRefreshing(true);
                                        //new getUserFilesService().execute("http://192.168.1.9:8080/");
                                    }
                                }
        );

        return rootView;
    }

    @Override
    public void onRefresh() {
        //new getUserFilesService().execute("http://192.168.1.9:8080/");
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
        Toast.makeText(getContext(), "Share item click", Toast.LENGTH_LONG).show();
        showShareFileDialog();
    }

    private void deleteCurrentItem() {
        Toast.makeText(getContext(), "Delete item click", Toast.LENGTH_LONG).show();
        if(!Utility.getExtensionFromFile(itemName).isEmpty()){
            Toast.makeText(getContext(), "Delete file", Toast.LENGTH_LONG).show();
            //new deleteFileService().execute("http://192.168.1.9:8080/archivos");
        } else {
            Toast.makeText(getContext(), "Delete folder", Toast.LENGTH_LONG).show();
            //new deleteFolderService().execute("http://192.168.1.9:8080/carpetas");
        }
    }

    private void downloadCurrentItem() {
        Toast.makeText(getContext(), "Download item click", Toast.LENGTH_LONG).show();
        //new getDownloadFileService().execute("http://192.168.0.16:8080/descargar");
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
                Log.d("Error", "Failed to get user files");
            }
        } catch (Exception e) {
            Log.d("Error", e.getLocalizedMessage());
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
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
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
                }
            } catch (Exception e) {
                Log.d("Error", e.getLocalizedMessage());
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
            json.put("direccion", "tmp/" + email + "/");
            json.put("extension", Utility.getExtensionFromFile(itemName));
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
            json.put("direccion","tmp/" + email + "/");
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
            return deleteFile(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if(status.equals("ok")) {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
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
            json.put("nombre", itemName);
            json.put("propietario",email);
            json.put("baja_logica","si");
            json.put("direccion","tmp/" + email + "/");
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
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                Log.d("Error", e.getLocalizedMessage());
            }
        }
    }


    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Toast.makeText(getContext(), "folder click", Toast.LENGTH_LONG).show();
        Intent intent = new Intent(getContext(),FilesInFolderActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.putExtra("folderName", foldersList.get(position));
        startActivity(intent);
    }

 }
