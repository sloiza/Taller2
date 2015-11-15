package tp.taller2.udrive;

/**
 * Created by mati on 30/09/15.
 */

import android.app.DialogFragment;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.ActionMode;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
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
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

public class HomeFragment extends Fragment implements ActionMode.Callback {

    private ListView lv;
    private ActionMode mActionMode;
    SessionManager session;
    FragmentManager fragmentManager;
    Boolean showSnackbar = true;

    // Listview Data
    List<String> filesList = new ArrayList<>();

    public HomeFragment(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {

        View rootView = inflater.inflate(R.layout.fragment_home, container, false);

        lv = (ListView) rootView.findViewById(R.id.list_view);

        fragmentManager = getFragmentManager();

        session = new SessionManager(getContext());
        HashMap<String, String> user = session.getUserDetails();
        String email = user.get(SessionManager.KEY_EMAIL);
        CoordinatorLayout coordinatorLayout = (CoordinatorLayout) rootView.findViewById(R.id.coordinatorLayout);
        if(showSnackbar){
            Snackbar snackbar = Snackbar.make(coordinatorLayout, "You are logged in as\n" + email, Snackbar.LENGTH_LONG);
            snackbar.show();
            showSnackbar = false;
        }

        new getUserFilesService().execute("http://192.168.0.14:8080/");

        return rootView;
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        lv.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE_MODAL);
        lv.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            public boolean onItemLongClick(AdapterView<?> parent, View view,
                                           int position, long id) {
                /*if (mActionMode != null) {
                    return false;
                }

                // Start the CAB using the ActionMode.Callback defined above
                mActionMode = getActivity().startActionMode(HomeFragment.this);
                view.setSelected(true);
                return true;*/
 ;               ((ListView) parent).setItemChecked(position,
                        ((ListView) parent).isItemChecked(position));
                return false;
            }
        });
        lv.setMultiChoiceModeListener(new AbsListView.MultiChoiceModeListener() {

            private int nr = 0;

            @Override
            public boolean onCreateActionMode(ActionMode mode, Menu menu) {
                getActivity().getMenuInflater().inflate(R.menu.menu_context,menu);
                return true;
            }

            @Override
            public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
                mode.setTitle("Item select");
                return true;
            }

            @Override
            public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
                switch (item.getItemId()) {
                    case R.id.item_share:
                        shareCurrentItem();
                        mode.finish(); // Action picked, so close the CAB
                        return true;
                    case R.id.item_delete:
                        deleteCurrentItem();
                        mode.finish(); // Action picked, so close the CAB
                        return true;
                    case R.id.item_download:
                        downloadCurrentItem();
                        mode.finish(); // Action picked, so close the CAB
                        return true;
                    default:
                        return false;
                }
            }

            @Override
            public void onDestroyActionMode(ActionMode mode) {
                nr = 0;
            }

            @Override
            public void onItemCheckedStateChanged(ActionMode mode,int position, long id, boolean checked) {
                if (checked) {
                    nr++;
                } else {
                    nr--;
                }
                mode.setTitle(nr + " rows selected!");
            }
        });
    }

    private void shareCurrentItem() {
        Toast.makeText(getContext(), "Share item click", Toast.LENGTH_LONG).show();
    }

    private void deleteCurrentItem() {
        Toast.makeText(getContext(), "Delete item click", Toast.LENGTH_LONG).show();
        new deleteFileService().execute("http://192.168.0.14:8080/archivos");
    }

    private void downloadCurrentItem() {
        Toast.makeText(getContext(), "Download item click", Toast.LENGTH_LONG).show();
        //new getDownloadFileService().execute("http://192.168.0.16:8080/archivos");
    }

    public String getUserFiles(String URL) {
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
    public boolean onCreateActionMode(ActionMode mode, Menu menu) {
        return false;
    }

    @Override
    public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
        return false;
    }

    @Override
    public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
        return false;
    }

    @Override
    public void onDestroyActionMode(ActionMode mode) {

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
                Object folders = jsonObject.get("archivos");
                JSONArray fileArray = jsonObject.getJSONArray("archivos");
                Log.d("respuesta", result);
                Log.d("archivos", folders.toString());
                  //Object folders = jsonObject.get("carpetas");
                for (int i=0; i<fileArray.length(); i++) {
                    JSONObject fileName = fileArray.getJSONObject(i);
                    Log.d("filename", fileArray.getJSONObject(i).toString());
                    filesList.add(fileName.toString());
                }
                ArrayAdapter<String> files = new ArrayAdapter<>(getActivity(),R.layout.list_item,filesList);
                lv.setAdapter(files);
                //Log.d("folders", folders.toString());
                if(status.equals("ok")) {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
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
        try {
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

    private class getDownloadFileService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getDownloadFile(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }

    public String deleteFile(String URL) {
        //String surname = surnameET.getText().toString();
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpDelete httpDelete = new HttpDelete(URL);
        HashMap<String, String> user = session.getUserDetails();
        String email = user.get(SessionManager.KEY_EMAIL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre","ResumenAG.pdf");
            json.put("extension", "extensionDefault");
            json.put("etiqueta","archivo");
            json.put("fecha_ulti_modi","26102015");
            json.put("usuario_ulti_modi","1234");
            json.put("propietario",email);
            json.put("baja_logica","no");
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
