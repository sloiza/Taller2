package tp.taller2.udrive;

import android.app.DialogFragment;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.support.v4.widget.SwipeRefreshLayout;
import android.util.Log;
import android.view.ContextMenu;
import android.view.LayoutInflater;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

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

public class ShareFragment extends Fragment implements SwipeRefreshLayout.OnRefreshListener{

    List<String> filesList = new ArrayList<>();
    private ListView lv;
    private ListView folderlv;
    List<String> foldersList = new ArrayList<>();
    HashMap<String, String> user;
    String email;
    String products [] = {"parciales.pdf", "finales.pdf"};
    String itemName;
    SwipeRefreshLayout swipeRefreshLayout;

    SessionManager session;


    public ShareFragment(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_share, container, false);

        lv = (ListView) rootView.findViewById(R.id.list_view);
        ArrayAdapter<String> productsList = new ArrayAdapter<>(getActivity(),android.R.layout.simple_list_item_1,products);
        lv.setAdapter(productsList);
        registerForContextMenu(lv);

        foldersList.add("inteligentes");

        folderlv = (ListView) rootView.findViewById(R.id.folder_list_view);
        ArrayAdapter<String> folderList = new ArrayAdapter<>(getActivity(),android.R.layout.simple_list_item_1,foldersList);
        folderlv.setAdapter(folderList);

        Utility.setDynamicHeight(lv);
        Utility.setDynamicHeight(folderlv);

        registerForContextMenu(folderlv);

        session = new SessionManager(getContext());
        user = session.getUserDetails();
        email = user.get(SessionManager.KEY_EMAIL);

        swipeRefreshLayout = (SwipeRefreshLayout) rootView.findViewById(R.id.swipe_refresh_layout);
        swipeRefreshLayout.setOnRefreshListener(this);
        swipeRefreshLayout.setColorSchemeResources(R.color.ColorPrimary);

        swipeRefreshLayout.post(new Runnable() {
                                    @Override
                                    public void run() {
                                        //swipeRefreshLayout.setRefreshing(true);
                                        //new getShareFilesService().execute("http://192.168.1.9:8080/archivos");
                                    }
                                }
        );


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
                Log.d("JSON", "Failed to download file");
            }
        } catch (Exception e) {
            Log.d("readJSONFeed", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    @Override
    public void onRefresh() {
        //new getShareFilesService().execute("http://192.168.1.9:8080/archivos");
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
                    ArrayAdapter<String> files = new ArrayAdapter<>(getActivity(),R.layout.list_item,filesList);
                    lv.setAdapter(files);
                    ArrayAdapter<String> folders = new ArrayAdapter<>(getActivity(),R.layout.list_item,foldersList);
                    folderlv.setAdapter(folders);
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }
}
