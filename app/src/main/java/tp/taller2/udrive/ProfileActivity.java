package tp.taller2.udrive;

import android.content.Intent;
import android.graphics.Bitmap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import java.util.HashMap;

import de.hdodenhof.circleimageview.CircleImageView;

public class ProfileActivity extends AppCompatActivity {

    SessionManager session;
    TextView nameTV;
    TextView emailTV;
    TextView surnameTV;
    TextView cityTV;
    TextView storageET;
    CircleImageView picTV;
    String name, email, surname, city, picture;
    HashMap<String, String> user;
    Float storage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        nameTV = (TextView)findViewById(R.id.username_text);
        emailTV = (TextView)findViewById(R.id.email_text);
        surnameTV = (TextView)findViewById(R.id.surname_text);
        cityTV = (TextView)findViewById(R.id.place_text);
        storageET = (TextView)findViewById(R.id.storage_text);
        picTV = (CircleImageView)findViewById(R.id.imgView);

        session = new SessionManager(getApplicationContext());

        user = session.getUserDetails();
        name = user.get(SessionManager.KEY_NAME);
        surname = user.get(SessionManager.KEY_SURNAME);
        email = user.get(SessionManager.KEY_EMAIL);
        city = user.get(SessionManager.KEY_CITY);
        picture = user.get(SessionManager.KEY_PICTURE);
        storage = session.getUserStorageUsed();

        nameTV.setText(name);
        surnameTV.setText(surname);
        emailTV.setText(email);
        cityTV.setText(city);
        storageET.setText(String.valueOf(storage) + "GB of 20 GB used");
        Bitmap pictur = Utility.stringToBitmap(picture);
        picTV.setImageBitmap(pictur);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_profile, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        } else if (id == R.id.action_editProfile){
            Intent intent = new Intent(this, EditProfileActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            startActivity(intent);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
