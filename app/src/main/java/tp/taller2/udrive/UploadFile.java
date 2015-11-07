package tp.taller2.udrive;


import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.entity.ContentType;
import cz.msebera.android.httpclient.entity.mime.HttpMultipartMode;
import cz.msebera.android.httpclient.entity.mime.MultipartEntityBuilder;
import cz.msebera.android.httpclient.entity.mime.content.ByteArrayBody;
import tp.taller2.udrive.AndroidMultiPartEntity.ProgressListener;

import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Config;
import android.util.Log;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;


import org.apache.http.entity.mime.content.ContentBody;

import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.entity.mime.content.StringBody;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;


import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;

public class UploadFile extends AppCompatActivity {

    private static int FILE_SELECT_CODE = 1;
    private ProgressBar progressBar;
    private String filePath = null;
    private TextView txtPercentage;
    long totalSize = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_upload_file);
        getSupportActionBar().setDisplayShowHomeEnabled(true);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        txtPercentage = (TextView) findViewById(R.id.txtPercentage);
        progressBar = (ProgressBar) findViewById(R.id.progressBar);
    }

    public void uploadFile(View view) {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("*//*");
        intent.addCategory(Intent.CATEGORY_OPENABLE);

        try {
            startActivityForResult(
                    Intent.createChooser(intent, "Select a File to Upload"),
                    FILE_SELECT_CODE);
        } catch (android.content.ActivityNotFoundException ex) {
            // Potentially direct the user to the Market with a Dialog
            Toast.makeText(this, "Please install a File Manager.",
                    Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == FILE_SELECT_CODE && resultCode == RESULT_OK && null != data) {
            // Get the Uri of the selected file
            Uri uri = data.getData();
            Log.d("File Uri: ", uri.toString());
            // Get the file instance
            filePath = uri.getPath();
            Log.d("File path: ", filePath);
            // Initiate the upload
            new UploadFileToServer().execute();

        }
    }

    public static byte[] convertFileToByteArray(File f)
    {
        byte[] byteArray = null;
        try
        {
            InputStream inputStream = new FileInputStream(f);
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            byte[] b = new byte[1024*8];
            int bytesRead =0;

            while ((bytesRead = inputStream.read(b)) != -1)
            {
                bos.write(b, 0, bytesRead);
            }

            byteArray = bos.toByteArray();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        return byteArray;
    }

        /**
         * Uploading the file to server
         * */
        class UploadFileToServer extends AsyncTask<Void, Integer, String> {
            @Override
            protected void onPreExecute() {
                // setting progress bar to zero
                progressBar.setProgress(0);
                super.onPreExecute();
            }

            @Override
            protected void onProgressUpdate(Integer... progress) {
                // Making progress bar visible
                progressBar.setVisibility(View.VISIBLE);

                // updating progress bar value
                progressBar.setProgress(progress[0]);

                // updating percentage value
                txtPercentage.setText(String.valueOf(progress[0]) + "%");
            }

            @Override
            protected String doInBackground(Void... params) {
                return uploadFile();
            }

            @SuppressWarnings("deprecation")
            private String uploadFile() {
                String responseString = null;
                HttpURLConnection con = null;
                URL url = null;

                try {
                    AndroidMultiPartEntity entity = new AndroidMultiPartEntity(
                            new AndroidMultiPartEntity.ProgressListener() {

                                @Override
                                public void transferred(long num) {
                                    publishProgress((int) ((num / (float) totalSize) * 100));
                                }
                            });

                    Log.d("File pasddddddath: ", filePath);

                    File file = new File(filePath);
                    url = new URL("http://192.168.0.16:8080/archivos?");


                    con = (HttpURLConnection) url.openConnection();

                    // Activar método POST
                    con.setDoOutput(true);

                    // Tamaño desconocido
                    con.setFixedLengthStreamingMode(file.length());

                    OutputStream out = con.getOutputStream();
                    out.write(convertFileToByteArray(file));
                    out.flush();
                    out.close();
                    int statusCode = con.getResponseCode();
                    if (statusCode == 200) {
                        // Server response
                        responseString = con.getResponseMessage();
                    } else {
                        responseString = "Error occurred! Http Status Code: "
                                + statusCode;
                    }

                } catch (ClientProtocolException e) {
                    responseString = e.toString();
                } catch (IOException e) {
                    responseString = e.toString();
                }
                return responseString;
            }

                @Override
            protected void onPostExecute(String result) {
                //try {
                    Log.d("respuesta: ", result);
                    /*JSONObject jsonObject = new JSONObject(result);
                    Object status = jsonObject.get("estado");
                    Object message = jsonObject.get("mensaje");

                    if (status.equals("ok")) {*/
                        Toast.makeText(getApplicationContext(), "upload file success", Toast.LENGTH_LONG).show();
                   /* } else {
                        Toast.makeText(getApplicationContext(), "upload file error", Toast.LENGTH_LONG).show();
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }*/

                super.onPostExecute(result);
            }

        }
    }

