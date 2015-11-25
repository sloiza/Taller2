package tp.taller2.udrive;

import android.app.DialogFragment;
import android.app.SearchManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.util.Log;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.support.v7.widget.SearchView;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toast;

import com.android.internal.http.multipart.MultipartEntity;

import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.entity.mime.content.StringBody;
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
import java.util.Date;
import java.util.HashMap;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.client.methods.HttpPut;
import cz.msebera.android.httpclient.entity.InputStreamEntity;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import de.hdodenhof.circleimageview.CircleImageView;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener,LogOutDialogFragment.LogOutDialogListener,
        NewFolderDialogFragment.NewFolderDialogListener, FileOptionsDialogFragment.FileOptionsDialogListener,
        ShareItemDialogFragment.ShareItemDialogListener, BinFragment.OnFragmentInteractionListener,
        IpFragment.updateIpAndPortListener{

    ActionBarDrawerToggle toggle;
    Toolbar toolbar;
    DrawerLayout drawer;
    NavigationView navigationView;
    Fragment fragment;
    FragmentManager fragmentManager;
    SessionManager session;
    GPSTracker gps;
    private static int FILE_SELECT_CODE = 1;
    private String filePath = null;
    boolean doubleBackToExitPressedOnce = false;
    String dialogInput;
    String restoreItem;
    HashMap<String, String> user;
    String name;
    String surname;
    String email;
    String picture;
    String itemName;
    String ipAddress, serverPort;

    /**
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        toolbar = (Toolbar) findViewById(R.id.tool_bar);
        setSupportActionBar(toolbar);

        drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        toggle = new ActionBarDrawerToggle(this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close) {
        };
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);
        setupDrawerContent(navigationView);

        fragment = new HomeFragment();
        fragmentManager = getSupportFragmentManager();
        fragmentManager.beginTransaction().replace(R.id.container, fragment).commit();
        setTitle(R.string.title_activity_users);

        TextView profileLink = (TextView) findViewById(R.id.profileLink);
        profileLink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i("User", "click on view profile");
                Utility.appendToInfoLog("User", "click on view profile");
                Intent intent = new Intent(getApplicationContext(), ProfileActivity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                startActivity(intent);
            }
        });

        session = new SessionManager(getApplicationContext());

        TextView userName = (TextView) findViewById(R.id.name);
        TextView userSurname = (TextView) findViewById(R.id.surname);
        TextView userEmail = (TextView) findViewById(R.id.email);
        CircleImageView pic = (CircleImageView) findViewById(R.id.circleView);

        session.checkLogin();

        user = session.getUserDetails();
        name = user.get(SessionManager.KEY_NAME);
        surname = user.get(SessionManager.KEY_SURNAME);
        email = user.get(SessionManager.KEY_EMAIL);
        picture = user.get(SessionManager.KEY_PICTURE);
        ipAddress = session.getIp();
        serverPort = session.getPort();

        userName.setText(name);
        userSurname.setText(surname);
        userEmail.setText(email);

        Bitmap pictureBM = Utility.stringToBitmap(picture);
        pic.setImageBitmap(pictureBM);

    }

    public void showNewFolderDialog() {
        DialogFragment dialog = new NewFolderDialogFragment();
        dialog.show(getFragmentManager(), "newFolder");
    }

    public void showLogOutDialog() {
        DialogFragment dialog = new LogOutDialogFragment();
        dialog.show(getFragmentManager(), "logOut");
    }

    public void showFileOptionsDialog() {
        DialogFragment dialog = new FileOptionsDialogFragment();
        dialog.show(getFragmentManager(), "restore");
    }

    @Override
    public void onFragmentInteraction(String name) {
        restoreItem = name;
        Log.d("restoreitem", restoreItem);
        showFileOptionsDialog();
    }

    @Override
    public void onDialogPositiveClick(DialogFragment dialog) {
        if (dialog.getTag().equals("logOut")) {
            Log.i("User", "log out");
            Utility.appendToInfoLog("User", "log out");
            session.logoutUser();
        } else if (dialog.getTag().equals("newFolder")) {
            new postNewFolderService().execute(ipAddress + serverPort + "carpetas");
        } else if (dialog.getTag().equals("restore")) {
            if (!Utility.getExtensionFromFile(restoreItem).isEmpty()) {
                new restoreFilesService().execute(ipAddress + serverPort + "papelera");
            } else {
                new restoreFolderService().execute(ipAddress + serverPort + "papelera");
            }
        } else if (dialog.getTag().equals("shareUsers")) {
            if (!Utility.getExtensionFromFile(itemName).isEmpty()) {
                new shareFileService().execute(ipAddress + serverPort + "compartirArchivo");
            } else {
                new shareFolderService().execute(ipAddress + serverPort + "compartirCarpeta");
            }
        }

    }

    public String restoreFiles(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPut httpPut = new HttpPut(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", Utility.getNameFromFile(restoreItem));
            json.put("extension", Utility.getExtensionFromFile(restoreItem));
            json.put("direccion", "archivos/" + email + "/");
            json.put("mail", email);
            httpPut.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpPut.setHeader("Content-Type", "application/json");
            httpPut.setHeader("Accept-Encoding", "application/json");
            HttpResponse response = httpClient.execute(httpPut);
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
                Log.e("Restore file", "service status code: " + statusCode);
                Utility.appendToErrorLog("Restore file", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Restore file", e.getLocalizedMessage());
            Utility.appendToErrorLog("Restore file", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    @Override
    public void getIpAndPortData(String ip, String port) {
        ipAddress = ip;
        serverPort = port;
    }

    public void updateIpAndPort(View view) {
        session.updateIpAndPort(ipAddress, serverPort);
    }

    private class restoreFilesService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return restoreFiles(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if (status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("Restore file", message.toString());
                    Utility.appendToInfoLog("Restore file", message.toString());
                    Log.d("Restore file", jsonObject.toString());
                    Utility.appendToDebugLog("Restore file", jsonObject.toString());
                    session.updateStorageUsed(session.getUserStorageUsed() + 0.3f);
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Restore file", message.toString());
                    Utility.appendToErrorLog("Restore file", message.toString());
                }
            } catch (Exception e) {
                Log.e("Restore file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Restore file", e.getLocalizedMessage());
            }
        }
    }

    public String restoreFolder(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPut httpPut = new HttpPut(URL);
        JSONObject json = new JSONObject();
        try {
            json.put("nombre", restoreItem);
            json.put("direccion", "archivos/" + email + "/");
            json.put("mail", email);
            httpPut.setEntity(new StringEntity(json.toString(), "UTF-8"));
            httpPut.setHeader("Content-Type", "application/json");
            httpPut.setHeader("Accept-Encoding", "application/json");
            HttpResponse response = httpClient.execute(httpPut);
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
                Log.e("Restore folder", "service status code: " + statusCode);
                Utility.appendToErrorLog("Restore folder", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Restore folder", e.getLocalizedMessage());
            Utility.appendToErrorLog("Restore folder", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    private class restoreFolderService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return restoreFolder(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                if (status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.i("Restore folder", message.toString());
                    Utility.appendToInfoLog("Restore folder", message.toString());
                    Log.d("Restore folder", jsonObject.toString());
                    Utility.appendToDebugLog("Restore folder", jsonObject.toString());
                }
            } catch (Exception e) {
                Log.e("Restore folder", e.getLocalizedMessage());
                Utility.appendToErrorLog("Restore folder", e.getLocalizedMessage());
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

    /**
     * @param navigationView navigation drawer that appears when slides to rigth
     */
    private void setupDrawerContent(NavigationView navigationView) {
        navigationView.setNavigationItemSelectedListener(
                new NavigationView.OnNavigationItemSelectedListener() {
                    @Override
                    public boolean onNavigationItemSelected(MenuItem menuItem) {
                        selectDrawerItem(menuItem);
                        return true;
                    }
                });
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
            Log.e("Upload file", "Need to install a File Manager");
            Utility.appendToErrorLog("Upload file", "Need to install a File Manager");
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
            File file = new File(filePath);
            JSONArray jsonArray = new JSONArray();
            jsonArray.put("file");
            //json.put("fecha_creacion", currentDateAndTime);
            //json.put("version", 1);
            //json.put("compartido_con", "");
            new UploadFileToServer().execute(ipAddress + serverPort + "archivos?nombre=" + Utility.getNameFromFile(file.getName())
                    + "&extension=" + Utility.getExtensionFromFile(filePath) + "&etiqueta=file"
                    + "&fecha_ulti_modi=22/11/2015" + "&usuario_ulti_modi=" + email
                    + "&propietario=" + email + "&baja_logica=no&direccion=" + "archivos/" + email + "/");
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
                    Log.i("Upload file", message.toString());
                    Utility.appendToInfoLog("Upload file", message.toString());
                    Log.d("Upload file", jsonObject.toString());
                    Utility.appendToDebugLog("Upload file", jsonObject.toString());
                    session.updateStorageUsed(session.getUserStorageUsed() + 0.3f);
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("Upload file", message.toString());
                    Utility.appendToErrorLog("Upload file", message.toString());
                }
            } catch (JSONException e) {
                Log.e("Upload file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Upload file", e.getLocalizedMessage());
            }
        }
    }

    /**
     * @param menuItem Create a new fragment and specify the planet to show based on position
     */
    public void selectDrawerItem(MenuItem menuItem) {
        Fragment fragment;
        switch (menuItem.getItemId()) {
            case R.id.nav_home:
                fragment = new HomeFragment();
                break;
            case R.id.nav_shareWithMe:
                fragment = new ShareFragment();
                break;
            case R.id.nav_bin:
                fragment = new BinFragment();
                break;
            case R.id.nav_end_session:
                fragment = new HomeFragment();
                showLogOutDialog();
                break;
            case R.id.nav_storage:
                fragment = StorageFragment.newInstance(session.getUserStorageUsed());
                break;
            case R.id.nav_ip:
                fragment = new IpFragment();
                break;
            default:
                fragment = new HomeFragment();
        }

        // Insert the fragment by replacing any existing fragment
        FragmentManager fragmentManager = getSupportFragmentManager();
        fragmentManager.beginTransaction().replace(R.id.container, fragment).commit();

        // Highlight the selected item, update the title, and close the drawer
        menuItem.setChecked(true);
        setTitle(menuItem.getTitle());
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            if (doubleBackToExitPressedOnce) {
                super.onBackPressed();
                finish();
            }

            this.doubleBackToExitPressedOnce = true;
            Toast.makeText(this, R.string.exit_message, Toast.LENGTH_SHORT).show();

            new Handler().postDelayed(new Runnable() {

                @Override
                public void run() {
                    doubleBackToExitPressedOnce = false;
                }
            }, 2000);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        MenuItem searchItem = menu.findItem(R.id.action_search);

        SearchManager searchManager = (SearchManager) MainActivity.this.getSystemService(Context.SEARCH_SERVICE);
        SearchView searchView = (SearchView) searchItem.getActionView();
        searchView.setSearchableInfo(searchManager.getSearchableInfo(MainActivity.this.getComponentName()));

        return super.onCreateOptionsMenu(menu);
    }

    /**
     * Handle action bar item clicks here. The action bar will
     * automatically handle clicks on the Home/Up button, so long
     * as you specify a parent activity in AndroidManifest.xml.
     *
     * @param item
     * @return action
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

    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        return true;
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

    public String postNewFolder(String URL) {
        StringBuilder stringBuilder = new StringBuilder();
        HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost(URL);
        JSONObject json = new JSONObject();
        JSONArray jsonArray = new JSONArray();
        SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
        String currentDateAndTime = sdf.format(new Date());
        try {
            jsonArray.put("carpeta");
            json.put("nombre", dialogInput);
            json.put("etiqueta", jsonArray);
            json.put("fecha_ulti_modi", currentDateAndTime);
            Log.d("date", currentDateAndTime);
            //json.put("fecha_creacion", currentDateAndTime);
            //json.put("compartido_con", "");
            json.put("usuario_ulti_modi", name + " " + surname);
            json.put("propietario", name + " " + surname);
            json.put("baja_logica", "no");
            json.put("direccion", "archivos/" + email + "/");
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
                Log.e("New folder", "service status code: " + statusCode);
                Utility.appendToErrorLog("New folder", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("New folder", e.getLocalizedMessage());
            Utility.appendToErrorLog("New folder", e.getLocalizedMessage());
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
                    Log.i("New folder", message.toString());
                    Utility.appendToInfoLog("New folder", message.toString());
                    Log.d("New folder", jsonObject.toString());
                    Utility.appendToDebugLog("New folder", jsonObject.toString());
                } else {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                    Log.e("New folder", message.toString());
                    Utility.appendToErrorLog("New folder", message.toString());
                }
            } catch (Exception e) {
                Log.e("New folder", e.getLocalizedMessage());
                Utility.appendToErrorLog("New folder", e.getLocalizedMessage());
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
                Log.e("Share file", "service status code: " + statusCode);
                Utility.appendToErrorLog("Share file", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Share file", e.getLocalizedMessage());
            Utility.appendToErrorLog("Share file", e.getLocalizedMessage());
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
                        Log.i("Share file", message.toString());
                        Utility.appendToInfoLog("Share file", message.toString());
                        Log.d("Share file", jsonObject.toString());
                        Utility.appendToDebugLog("Share file", jsonObject.toString());
                    } else {
                        Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                        Log.e("Share file", message.toString());
                        Utility.appendToErrorLog("Share file", message.toString());
                    }
            } catch (Exception e) {
                Log.e("Share file", e.getLocalizedMessage());
                Utility.appendToErrorLog("Share file", e.getLocalizedMessage());
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
                Log.e("Share folder", "service status code: " + statusCode);
                Utility.appendToErrorLog("Share folder", "status code: " + statusCode);
            }
        } catch (Exception e) {
            Log.e("Share folder", e.getLocalizedMessage());
            Utility.appendToErrorLog("Share folder", e.getLocalizedMessage());
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
                        Log.i("Share folder", message.toString());
                        Utility.appendToInfoLog("Share folder", message.toString());
                        Log.d("Share folder", jsonObject.toString());
                        Utility.appendToDebugLog("Share folder", jsonObject.toString());
                    } else {
                        Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                        Log.e("Share folder", message.toString());
                        Utility.appendToErrorLog("Share folder", message.toString());
                    }
                } catch (Exception e) {
                    Log.e("Share folder", e.getLocalizedMessage());
                    Utility.appendToErrorLog("Share folder", e.getLocalizedMessage());
                }
            }
        }
}
