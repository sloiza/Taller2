package tp.taller2.udrive;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import java.util.HashMap;

import de.hdodenhof.circleimageview.CircleImageView;

public class ProfileActivity extends AppCompatActivity {

    SessionManager session;
    TextView name;
    TextView email;
    TextView surname;
    TextView city;
    CircleImageView pic;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        name = (TextView)findViewById(R.id.username_text);
        email = (TextView)findViewById(R.id.email_text);
        surname = (TextView)findViewById(R.id.surname_text);
        city = (TextView)findViewById(R.id.place_text);
        pic = (CircleImageView)findViewById(R.id.imgView);

        session = new SessionManager(getApplicationContext());
        HashMap<String, String> user = session.getUserDetails();
        String sessionName = user.get(SessionManager.KEY_NAME);
        String sessionSurname = user.get(SessionManager.KEY_SURNAME);
        String sessionEmail = user.get(SessionManager.KEY_EMAIL);
        String sessionCity = user.get(SessionManager.KEY_CITY);
        String sessionPicture = user.get(SessionManager.KEY_PICTURE);

        name.setText(sessionName);
        surname.setText(sessionSurname);
        email.setText(sessionEmail);
        city.setText(sessionCity);
        Bitmap picture = Utility.stringToBitmap(sessionPicture);
        pic.setImageBitmap(picture);


    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_profile, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
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
