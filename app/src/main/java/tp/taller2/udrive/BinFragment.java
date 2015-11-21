package tp.taller2.udrive;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
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

public class BinFragment extends Fragment implements AbsListView.OnItemClickListener, SwipeRefreshLayout.OnRefreshListener {

    private OnFragmentInteractionListener mListener;
    private AbsListView mListView;
    List<String> filesList = new ArrayList<>();
    SwipeRefreshLayout swipeRefreshLayout;
    SessionManager session;
    HashMap<String, String> user;
    String email;

    public BinFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_item_bin, container, false);

        mListView = (AbsListView) view.findViewById(android.R.id.list);
        mListView.setOnItemClickListener(this);

        swipeRefreshLayout = (SwipeRefreshLayout) view.findViewById(R.id.swipe_refresh_layout);
        swipeRefreshLayout.setOnRefreshListener(this);
        swipeRefreshLayout.setColorSchemeResources(R.color.ColorPrimary);

        swipeRefreshLayout.post(new Runnable() {
                                    @Override
                                    public void run() {
                                        swipeRefreshLayout.setRefreshing(true);
                                        new getPaperBinFilesService().execute(session.getIp() + session.getPort() + "papelera");
                                    }
                                }
        );

        session = new SessionManager(getContext());
        user = session.getUserDetails();
        email = user.get(SessionManager.KEY_EMAIL);

        return view;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        try {
            mListener = (OnFragmentInteractionListener) activity;
        } catch (ClassCastException e) {
            throw new ClassCastException(activity.toString()
                    + " must implement OnFragmentInteractionListener");
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        if (null != mListener) {
            mListener.onFragmentInteraction(filesList.get(position));
        }
    }

    @Override
    public void onRefresh() {
        new getPaperBinFilesService().execute(session.getIp() + session.getPort() + "papelera");
    }

    public interface OnFragmentInteractionListener {
        void onFragmentInteraction(String name);
    }

    public String getPaperBinFiles(String URL) {
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
                Log.e("Paper bin", "service status code: " + statusCode);
                Utility.appendToErrorLog("Paper bin", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Paper bin", e.getLocalizedMessage());
            Utility.appendToErrorLog("Paper bin", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class getPaperBinFilesService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return getPaperBinFiles(urls[0]);
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
                    Log.i("Paper bin", message.toString());
                    Utility.appendToInfoLog("Paper bin", message.toString());
                    if(jsonObject.has("carpetas")){
                        folderArray = jsonObject.getJSONArray("carpetas");
                        for (int i=0; i<folderArray.length(); i++) {
                            String folderPath = folderArray.getString(i);
                            String folderName = folderPath.substring(folderPath.lastIndexOf("/") + 1);
                            filesList.add(folderName);
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
                    Log.d("Paper bin", jsonObject.toString());
                    Utility.appendToDebugLog("Paper bin", jsonObject.toString());
                    ArrayAdapter<String> files = new ArrayAdapter<>(getActivity(),android.R.layout.simple_list_item_1,filesList);
                    mListView.setAdapter(files);
                    swipeRefreshLayout.setRefreshing(false);
                } else {
                    Toast.makeText(getContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Paper bin", message.toString());
                    Utility.appendToErrorLog("Paper bin", message.toString());
                }
            } catch (Exception e) {
                Log.e("Paper bin", e.getLocalizedMessage());
                Utility.appendToErrorLog("Paper bin", e.getLocalizedMessage());
            }
        }
    }

}
