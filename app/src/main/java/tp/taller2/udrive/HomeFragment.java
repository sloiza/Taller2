package tp.taller2.udrive;

/**
 * Created by mati on 30/09/15.
 */
import android.app.ListFragment;
import android.content.Intent;
import android.net.Uri;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.ActionMode;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.getbase.floatingactionbutton.FloatingActionsMenu;
import com.loopj.android.http.HttpGet;

import org.apache.http.client.ClientProtocolException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.HashMap;
import java.util.Random;

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
    private static int FILE_SELECT_CODE = 1;
    private ProgressBar progressBar;
    private String filePath = null;
    private TextView txtPercentage;
    long totalSize = 0;

    // Listview Data
    String products[] = {"Dell Inspiron", "HTC One X", "HTC Wildfire S", "HTC Sense", "HTC Sensation XE",
            "iPhone 4S", "Samsung Galaxy Note 800",
            "Samsung Galaxy S3", "MacBook Air", "Mac Mini", "MacBook Pro"};

    public HomeFragment(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {

        View rootView = inflater.inflate(R.layout.fragment_home, container, false);

        lv = (ListView) rootView.findViewById(R.id.list_view);

        ArrayAdapter<String> files = new ArrayAdapter<String>(getActivity(),R.layout.list_item,products);

        lv.setAdapter(files);

        SessionManager session = new SessionManager(getContext());
        HashMap<String, String> user = session.getUserDetails();
        String email = user.get(SessionManager.KEY_EMAIL);
        CoordinatorLayout coordinatorLayout = (CoordinatorLayout) rootView.findViewById(R.id.coordinatorLayout);
        Snackbar snackbar = Snackbar.make(coordinatorLayout, "You are logged in as\n" + email, Snackbar.LENGTH_LONG);

        snackbar.show();
        //new getUserFilesService().execute("http://192.168.0.16:8080/archivos");

        return rootView;
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        lv.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            public boolean onItemLongClick(AdapterView<?> parent, View view,
                                           int position, long id) {
                if (mActionMode != null) {
                    return false;
                }

                // Start the CAB using the ActionMode.Callback defined above
                mActionMode = getActivity().startActionMode(HomeFragment.this);
                view.setSelected(true);
                return true;
            }
        });

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

    private void shareCurrentItem() {
        Toast.makeText(getContext(), "Share item click", Toast.LENGTH_LONG).show();
    }

    private void deleteCurrentItem() {
        Toast.makeText(getContext(), "Delete item click", Toast.LENGTH_LONG).show();
        //new postDeleteFileService().execute("http://192.168.0.16:8080/archivos");
    }

    private void downloadCurrentItem() {
        Toast.makeText(getContext(), "Download item click", Toast.LENGTH_LONG).show();
        //new getDownloadFileService().execute("http://192.168.0.16:8080/archivos");
    }

    @Override
    public boolean onCreateActionMode(ActionMode mode, Menu menu) {
        getActivity().getMenuInflater().inflate(R.menu.menu_context, menu);
        return true;
    }

    @Override
    public void onDestroyActionMode(ActionMode mode) {
        mode.finish();
    }

    @Override
    public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
        return false;
    }


    public String getUserFiles(String URL) {
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

    private class getUserFilesService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getUserFiles(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
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

    public String postDeleteFile(String URL) {
        //String surname = surnameET.getText().toString();
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        JSONObject json = new JSONObject();
        int min = 1;
        int max = 1000;
        Random random = new Random();
        int id = random.nextInt(max - min + 1) + min;
        try {
            //json.put("apellido", surname);
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

    private class postDeleteFileService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return postDeleteFile(urls[0]);
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
                    //Toast.makeText(getContext(), R.string.success_register, Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }
}
