package tp.taller2.udrive;

/**
 * Created by mati on 30/09/15.
 */
import android.app.ListFragment;
import android.content.Intent;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.FloatingActionButton;
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
import android.widget.TextView;
import android.widget.Toast;

import com.loopj.android.http.HttpGet;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

public class HomeFragment extends Fragment {

    private ListView lv;
    private ActionMode mActionMode;
    ArrayAdapter<String> adapter;

    // Listview Data
    String products[] = {"Dell Inspiron", "HTC One X", "HTC Wildfire S", "HTC Sense", "HTC Sensation XE",
            "iPhone 4S", "Samsung Galaxy Note 800",
            "Samsung Galaxy S3", "MacBook Air", "Mac Mini", "MacBook Pro"};

    public HomeFragment(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View rootView = inflater.inflate(R.layout.fragment_home, container, false);

        lv = (ListView) rootView.findViewById(R.id.list_view);

          ArrayAdapter<String> files = new ArrayAdapter<String>(getActivity(),
                R.layout.list_item,
                products);

        lv.setAdapter(files);

        // listening to single list item on click
        lv.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            public boolean onItemLongClick(AdapterView<?> parent, View view,
                                           int position, long id) {
                // selected item
                 String product = ((TextView) view).getText().toString();
                // Launching new Activity on selecting single List Item
                Intent i = new Intent(getContext(), SingleListItem.class);
                // sending data to new activity
                i.putExtra("product", product);
                startActivity(i);
                return true;
                //if (mActionMode != null) {
                //    return false;
                //}

                // Start the CAB using the ActionMode.Callback defined above
                //mActionMode = HomeFragment.this.startActionMode(mActionModeCallback);
                //view.setSelected(true);
                //return true;
            }
        });

        //new getUserFilesService().execute("http://192.168.0.16:8080/archivos");

        return rootView;
    }


    private ActionMode.Callback mActionModeCallback = new ActionMode.Callback() {

        // Called when the user selects a contextual menu item
        @Override
        public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
            switch (item.getItemId()) {
                case R.id.item_share:
                    //shareCurrentItem();
                    mode.finish(); // Action picked, so close the CAB
                    return true;
                case R.id.item_delete:
                    //deleteCurrentItem();
                    mode.finish(); // Action picked, so close the CAB
                    return true;
                case R.id.item_download:
                    //downloadCurrentItem();
                    mode.finish(); // Action picked, so close the CAB
                    return true;
                default:
                    return false;
            }
        }

        // Called when the action mode is created; startActionMode() was called
        @Override
        public boolean onCreateActionMode(ActionMode mode, Menu menu) {
            // Inflate a menu resource providing context menu items
            MenuInflater inflater = mode.getMenuInflater();
            inflater.inflate(R.menu.menu_context, menu);
            return true;
        }

        // Called when the user exits the action mode
        @Override
        public void onDestroyActionMode(ActionMode mode) {
            mActionMode = null;
        }

        // Called each time the action mode is shown. Always called after onCreateActionMode, but
        // may be called multiple times if the mode is invalidated.
        @Override
        public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
            // TODO Auto-generated method stub
            mode.setTitle("Item is Click");
            return false;
        }
    };

    /*lv = (ListView)rootView.findViewById(R.id.list_view);
    lv.setAdapter(adapter);
    // listening to single list item on click
    lv.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
        public boolean onItemLongClick(AdapterView<?> parent, View view,
        int position, long id) {
            // selected item
            // String product = ((TextView) view).getText().toString();
            // Launching new Activity on selecting single List Item
            //Intent i = new Intent(getApplicationContext(), SingleListItem.class);
            // sending data to new activity
            //i.putExtra("product", product);
            //startActivity(i);
            if (mActionMode != null) {
                return false;
            }

            // Start the CAB using the ActionMode.Callback defined above
            mActionMode = HomeFragment.this.startActionMode(mActionModeCallback);
            view.setSelected(true);
            return true;
        }
    });*/


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
}
