package tp.taller2.udrive;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;

public class LoginActivity extends AppCompatActivity {

    public final static String WELCOME_MESSAGE = "com.udrive.udrive.MESSAGE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_login, menu);
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
        }

        return super.onOptionsItemSelected(item);
    }

    /** Called when the user clicks the login button */
    public void loginMessage(View view) {
        // Do something in response to button
        Intent intent = new Intent(this, UsersActivity.class);
        EditText usernameText = (EditText) findViewById(R.id.username_message);
        String welcomeMessage = usernameText.getText().toString();
        intent.putExtra(WELCOME_MESSAGE, welcomeMessage);
        startActivity(intent);
    }

    /** Called when the user clicks the sing up button */
    public void singUpMessage(View view) {
        // Do something in response to button
        Intent intent = new Intent(this, RegisterActivity.class);
        startActivity(intent);
    }
}
