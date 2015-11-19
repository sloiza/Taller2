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

import org.json.JSONArray;
import org.json.JSONException;
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
import java.util.Date;
import java.util.HashMap;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.StatusLine;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpPost;
import cz.msebera.android.httpclient.client.methods.HttpPut;
import cz.msebera.android.httpclient.entity.StringEntity;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import de.hdodenhof.circleimageview.CircleImageView;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener,LogOutDialogFragment.LogOutDialogListener,
        NewFolderDialogFragment.NewFolderDialogListener, FileOptionsDialogFragment.FileOptionsDialogListener,
        ShareItemDialogFragment.ShareItemDialogListener, BinFragment.OnFragmentInteractionListener
         {

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
    long totalSize = 0;
    boolean doubleBackToExitPressedOnce = false;
    String dialogInput;
    String restoreItem;
    HashMap<String, String> user;
    String name;
    String surname;
    String email;
    String picture;
    String itemName;
    Double storageUsed = 0.0;


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
        setTitle("My Unity");

        TextView profileLink = (TextView) findViewById(R.id.profileLink);
        profileLink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
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

        userName.setText(name);
        userSurname.setText(surname);
        userEmail.setText(email);

        Bitmap pictureBM = Utility.stringToBitmap(picture);
        pic.setImageBitmap(pictureBM);

    }

    public void showNewFolderDialog() {
        // Create an instance of the dialog fragment and show it
        DialogFragment dialog = new NewFolderDialogFragment();
        dialog.show(getFragmentManager(), "newFolder");
    }

    public void showLogOutDialog() {
        // Create an instance of the dialog fragment and show it
        DialogFragment dialog = new LogOutDialogFragment();
        dialog.show(getFragmentManager(), "logOut");
    }

    public void showFileOptionsDialog() {
        // Create an instance of the dialog fragment and show it
        DialogFragment dialog = new FileOptionsDialogFragment();
        dialog.show(getFragmentManager(), "restore");
    }

    // The dialog fragment receives a reference to this Activity through the
    // Fragment.onAttach() callback, which it uses to call the following methods
    // defined by the LogOutDialogFragment.LogOutDialogListener interface
    @Override
    public void onDialogPositiveClick(DialogFragment dialog) {
        // User touched the dialog's positive button
        if (dialog.getTag().equals("logOut")) {
            session.logoutUser();
        } else if (dialog.getTag().equals("newFolder")) {
            new postNewFolderService().execute("http://192.168.1.9:8080/carpetas");
        } else if (dialog.getTag().equals("restore")) {
            new restoreFilesService().execute("http://192.168.1.9:8080/compartirCarpeta");
        } else if (dialog.getTag().equals("shareUsers")) {
            Log.d("itemName", itemName);
            Log.d("dialogInput", dialogInput);
            if(!Utility.getExtensionFromFile(itemName).isEmpty()){
                Toast.makeText(getApplicationContext(), "share file", Toast.LENGTH_LONG).show();
                //new shareFileService().execute("http://192.168.1.9:8080/compartirArchivo");
            } else {
                //new shareFolderService().execute("http://192.168.1.9:8080/compartirCarpeta");
                Toast.makeText(getApplicationContext(), "share folder", Toast.LENGTH_LONG).show();
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
            json.put("direccion", "tmp/" + email + "/");
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
                Log.d("JSON", "Failed to restore file");
            }
        } catch (Exception e) {
            Log.d("readJSONFeed", e.getLocalizedMessage());
        }
        return stringBuilder.toString();
    }

    @Override
    public void onFragmentInteraction(String name) {
        restoreItem = name;
        Log.d("restoreitem", restoreItem);
        showFileOptionsDialog();
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
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
            }
        }
    }

    @Override
    public void onDialogNegativeClick(DialogFragment dialog) {
        // User touched the dialog's negative button
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
            // Potentially direct the user to the Market with a Dialog
            Toast.makeText(getApplicationContext(), "Please install a File Manager.", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == FILE_SELECT_CODE && resultCode == -1 && null != data) {
            // Get the Uri of the selected file
            Uri uri = data.getData();
            // Get the file instance
            filePath = uri.getPath();
            // Initiate the upload
            new UploadFileMetadatosToServer().execute();
        }
    }

    /**
     * Uploading the file to server
     */
    class UploadFileToServer extends AsyncTask<Void, Integer, String> {
        @Override
        protected String doInBackground(Void... params) {
            return uploadFile();
        }

        @SuppressWarnings("deprecation")
        private String uploadFile() {
            String responseString;
            HttpURLConnection con;
            URL url;

            try {
                AndroidMultiPartEntity entity = new AndroidMultiPartEntity(
                        new AndroidMultiPartEntity.ProgressListener() {

                            @Override
                            public void transferred(long num) {
                                publishProgress((int) ((num / (float) totalSize) * 100));
                            }
                        });

                File file = new File(filePath);
                url = new URL("http://192.168.1.9:8080/archivos?");
                con = (HttpURLConnection) url.openConnection();
                con.setDoOutput(true);
                con.setFixedLengthStreamingMode(file.length());

                OutputStream out = con.getOutputStream();
                out.write(Utility.convertFileToByteArray(file));
                out.flush();
                out.close();
                int statusCode = con.getResponseCode();
                if (statusCode == 200) {
                    responseString = con.getResponseMessage();
                } else {
                    responseString = "Error occurred! Http Status Code: " + statusCode;
                }
            } catch (IOException e) {
                responseString = e.toString();
            }
            return responseString;
        }

        @Override
        protected void onPostExecute(String result) {
            //try {
            Log.d("respuesta: ", result);
            //JSONObject jsonObject = new JSONObject(result);
            //Object status = jsonObject.get("estado");
            //Object message = jsonObject.get("mensaje");
            //if (status.equals("ok")) {
            Toast.makeText(getApplicationContext(), "Upload file success", Toast.LENGTH_LONG).show();
            //} else {
            //    Toast.makeText(getApplicationContext(), "upload file error", Toast.LENGTH_LONG).show();
            //}
            //} catch (JSONException e) {
            // e.printStackTrace();
            //}

            super.onPostExecute(result);
            storageUsed = storageUsed + 0.3;
        }

    }

    /**
     * Uploading the file to server
     */
    class UploadFileMetadatosToServer extends AsyncTask<Void, Integer, String> {

        @Override
        protected String doInBackground(Void... params) {
            return uploadFileMetadatos();
        }

        @SuppressWarnings("deprecation")
        private String uploadFileMetadatos() {
            String responseString = "";
            HttpURLConnection con;
            URL url;

            try {
                AndroidMultiPartEntity entity = new AndroidMultiPartEntity(
                        new AndroidMultiPartEntity.ProgressListener() {

                            @Override
                            public void transferred(long num) {
                                publishProgress((int) ((num / (float) totalSize) * 100));
                            }
                        });

                url = new URL("http://192.168.1.9:8080/archivos?");
                con = (HttpURLConnection) url.openConnection();
                con.setDoOutput(true);

                JSONObject json = new JSONObject();
                json.put("nombre", Utility.getNameFromFile(filePath));
                json.put("extension", Utility.getExtensionFromFile(filePath));
                json.put("etiqueta", "archivo");
                json.put("fecha_ulti_modi", "26102015");
                json.put("usuario_ulti_modi", "1234");
                json.put("propietario", email);
                json.put("baja_logica", "no");
                json.put("direccion", "tmp/" + email + "/");

                OutputStream out = con.getOutputStream();
                out.write(json.toString().getBytes());
                out.flush();
                out.close();
                int statusCode = con.getResponseCode();
                if (statusCode == 200) {
                    responseString = con.getResponseMessage();
                    Log.d("respuesta metadatos", responseString);
                } else {
                    responseString = "Error occurred! Http Status Code: " + statusCode;
                }
            } catch (IOException e) {
                responseString = e.toString();
            } catch (JSONException e) {
                e.printStackTrace();
            }
            return responseString;
        }

        @Override
        protected void onPostExecute(String result) {
            //try {
            Log.d("respuesta: ", result);
            //JSONObject jsonObject = new JSONObject(result);
            //Object status = jsonObject.get("estado");
            //Object message = jsonObject.get("mensaje");
            //if (status.equals("ok")) {
            new UploadFileToServer().execute();
            //} else {
            //    Toast.makeText(getApplicationContext(), "upload file error", Toast.LENGTH_LONG).show();
            //}
            //} catch (JSONException e) {
            //  e.printStackTrace();
            //}

            super.onPostExecute(result);
        }

    }


    /**
     * @param menuItem Create a new fragment and specify the planet to show based on position
     */
    public void selectDrawerItem(MenuItem menuItem) {
        // Create a new fragment and specify the planet to show based on
        // position
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
                fragment = StorageFragment.newInstance(storageUsed);
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
        // Inflate the menu; this adds items to the action bar if it is present.
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
     * @return
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
        try {
            json.put("nombre", dialogInput);
            json.put("etiqueta", "carpeta");
            json.put("fecha_ulti_modi", "26102015");
            json.put("usuario_ulti_modi", "0");
            json.put("propietario", email);
            json.put("baja_logica", "no");
            json.put("direccion", "tmp/" + email + "/");
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
                Log.d("JSON", "Failed to create new folder");
            }
        } catch (Exception e) {
            Log.d("readJSONFeed", e.getLocalizedMessage());
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
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
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
            json.put("direccion", "tmp/" + email + "/");
            json.put("usuarios", jsonArray);
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

    private class shareFileService extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... urls) {
            return shareFile(urls[0]);
        }

        protected void onPostExecute(String result) {
            try {
                JSONObject jsonObject = new JSONObject(result);
                Object status = jsonObject.get("estado");
                Object message = jsonObject.get("mensaje");
                Log.d("result", result);
                Log.d("Status", status.toString());
                Log.d("Message", message.toString());
                if (status.equals("ok")) {
                    Toast.makeText(getApplicationContext(), message.toString(), Toast.LENGTH_LONG).show();
                }
            } catch (Exception e) {
                Log.d("ReadJSONTask", e.getLocalizedMessage());
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
                json.put("direccion", "tmp/" + email + "/");
                json.put("usuarios", jsonArray);
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
                    Log.d("JSON", "Failed to share folder");
                }
            } catch (Exception e) {
                Log.d("readJSONFeed", e.getLocalizedMessage());
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
                    }
                } catch (Exception e) {
                    Log.d("ReadJSONTask", e.getLocalizedMessage());
                }
            }
        }
    }
}
