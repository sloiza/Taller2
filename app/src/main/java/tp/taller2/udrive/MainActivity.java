package tp.taller2.udrive;

import android.app.DialogFragment;
import android.app.SearchManager;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.view.ActionMode;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SearchView;
import android.util.Log;
import android.view.MenuInflater;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;

import java.util.HashMap;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener,LogOutDialogFragment.LogOutDialogListener{

    ActionBarDrawerToggle toggle;
    Toolbar toolbar;
    FloatingActionButton fab;
    DrawerLayout drawer;
    NavigationView navigationView;
    Fragment fragment;
    FragmentManager fragmentManager;
    SessionManager session;
    RelativeLayout relativeLayout;
    private CoordinatorLayout coordinatorLayout;
    private Button btnSimpleSnackbar;
    GPSTracker gps;


    /**
     *
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        toolbar = (Toolbar) findViewById(R.id.tool_bar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayShowHomeEnabled(true);

        drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        toggle = new ActionBarDrawerToggle(this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close) {
            @Override
            public void onDrawerOpened(View drawerView) {
                super.onDrawerOpened(drawerView);
                // code here will execute once the drawer is opened
            }

            @Override
            public void onDrawerClosed(View drawerView) {
                super.onDrawerClosed(drawerView);
                // Code here will execute once drawer is closed
            }
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

        session.checkLogin();

        HashMap<String, String> user = session.getUserDetails();
        String name = user.get(SessionManager.KEY_NAME);
        String surname = user.get(SessionManager.KEY_SURNAME);
        String email = user.get(SessionManager.KEY_EMAIL);
        userName.setText(name);
        userSurname.setText(surname);
        userEmail.setText(email);

        relativeLayout = (RelativeLayout) findViewById(R.id
                .container);
        Snackbar snackbar = Snackbar
                .make(relativeLayout, "You are logged in as\n" + email, Snackbar.LENGTH_LONG);

        snackbar.show();

    }

    public void showLogOutDialog() {
        // Create an instance of the dialog fragment and show it
        DialogFragment dialog = new LogOutDialogFragment();
        dialog.show(getFragmentManager(), "logOut");
    }

    // The dialog fragment receives a reference to this Activity through the
    // Fragment.onAttach() callback, which it uses to call the following methods
    // defined by the LogOutDialogFragment.LogOutDialogListener interface
    @Override
    public void onDialogPositiveClick(DialogFragment dialog) {
        // User touched the dialog's positive button
        session.logoutUser();
    }

    @Override
    public void onDialogNegativeClick(DialogFragment dialog) {
        // User touched the dialog's negative button
    }

    /**
     *
     * @param navigationView
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

    public void fabAction(View view) {
        /*PopupMenu popup = new PopupMenu(this, view);
        MenuInflater inflater = popup.getMenuInflater();
        inflater.inflate(R.menu.menu_fab_options, popup.getMenu());
        popup.show();*/
        Intent intent = new Intent(this, UploadFile.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(intent);
    }


    /**
     *
     * @param menuItem
     * Create a new fragment and specify the planet to show based on position
     */
    public void selectDrawerItem(MenuItem menuItem) {
        // Create a new fragment and specify the planet to show based on
        // position
        Fragment fragment;
        switch(menuItem.getItemId()) {
            case R.id.nav_home:
                fragment = new HomeFragment();
                break;
            case R.id.nav_shareWithMe:
                fragment = new ShareFragment();
                break;
            case R.id.nav_settings:
                fragment = new PreferencesFragment();
                break;
            case R.id.nav_end_session:
                fragment = new HomeFragment();
                showLogOutDialog();
                break;
            default:
                fragment = new HomeFragment();
        }

        if (fragment != null) {

            // Insert the fragment by replacing any existing fragment
            FragmentManager fragmentManager = getSupportFragmentManager();
            fragmentManager.beginTransaction().replace(R.id.container, fragment).commit();

            // Highlight the selected item, update the title, and close the drawer
            menuItem.setChecked(true);
            setTitle(menuItem.getTitle());
            DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
            drawer.closeDrawer(GravityCompat.START);
        } else {
            // error in creating fragment
            Log.e("MainActivity", "Error in creating fragment");
        }
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);



        // Associate searchable configuration with the SearchView
        SearchManager searchManager = (SearchManager) getSystemService(Context.SEARCH_SERVICE);
        SearchView searchView = (SearchView) menu.findItem(R.id.action_search).getActionView();
        //searchView.setSearchableInfo(searchManager.getSearchableInfo(getComponentName()));
        return true;
    }

    /**
     * Handle action bar item clicks here. The action bar will
     * automatically handle clicks on the Home/Up button, so long
     * as you specify a parent activity in AndroidManifest.xml.
     * @param item
     * @return
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Take appropriate action for each action item click
        switch (item.getItemId()) {
            case R.id.action_search:
                // search action
                 return true;
            case R.id.action_location_found:
                // location found
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
       return  true;
    }

    /**
     * Launching new activity
     * */
    private void LocationFound() {
        /*Intent i = new Intent(MainActivity.this, LocationFound.class);
        startActivity(i);*/
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
}
