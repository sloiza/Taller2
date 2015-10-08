package tp.taller2.udrive;

import android.app.Activity;
import android.content.res.TypedArray;
import android.content.res.Configuration;
import android.support.v4.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.app.ActionBar;
import android.app.Fragment;
import android.app.FragmentManager;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.support.v4.widget.DrawerLayout;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends Activity {

    private DrawerLayout NavDrawerLayout;
    private ListView NavList;
    private String[] NavTitles;
    private ArrayList<ItemObject> NavItems;
    private TypedArray NavIcons;
    NavigationAdapter NavAdapter;
    private ActionBarDrawerToggle DrawerToggle;
    private CharSequence DrawerTitle;
    private CharSequence Title;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        NavDrawerLayout = (DrawerLayout) findViewById(R.id.drawer_layout);
        NavList = (ListView) findViewById(R.id.navigation_drawer_list);

        View header = getLayoutInflater().inflate(R.layout.header, null);
        NavList.addHeaderView(header);

        NavIcons = getResources().obtainTypedArray(R.array.navigation_icons);
        NavTitles = getResources().getStringArray(R.array.nav_options);
        NavItems = new ArrayList<ItemObject>();

        NavItems.add(new ItemObject(NavTitles[0], NavIcons.getResourceId(0, -1)));
        NavItems.add(new ItemObject(NavTitles[1], NavIcons.getResourceId(1, -1)));
        NavItems.add(new ItemObject(NavTitles[2], NavIcons.getResourceId(2, -1)));

        NavAdapter = new NavigationAdapter(this, NavItems);
        NavList.setAdapter(NavAdapter);

        DrawerToggle = new ActionBarDrawerToggle(
                this,
                NavDrawerLayout,
                R.drawable.ic_drawer,
                R.string.app_name,
                R.string.hello_world
                ) {

            public void onDrawerClosed(View view) {
                Log.e("Cerrado completo", "!!");
            }

            public void onDrawerOpened(View drawerView) {
                Log.e("Apertura completa", "!!");
            }

        };

        NavDrawerLayout.setDrawerListener(DrawerToggle);
        /*ActionBar actionBar = getActionBar();
        actionBar.setDisplayShowTitleEnabled(true);
        actionBar.setHomeButtonEnabled(true);*/

        NavList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> arg0, View arg1, int position, long id) {
                ShowFragment(position);
            }
        });

        ShowFragment(1);
    }

     /*Pasando la posicion de la opcion en el menu nos mostrara el Fragment correspondiente*/
    private void ShowFragment(int position) {
        // update the main content by replacing fragments
        Fragment fragment = null;
        switch (position) {
            case 1:
                fragment = new HomeFragment();
                break;
            case 2:
                fragment = new ShareFragment();
                break;
            case 3:
                fragment = new PreferencesFragment();
                break;

            default:
                //si no esta la opcion mostrara un toast y nos mandara a Home
                Toast.makeText(getApplicationContext(), "Opcion " + NavTitles[position - 1] + "no disponible!", Toast.LENGTH_SHORT).show();
                fragment = new HomeFragment();
                position=1;
                break;
        }
        //Validamos si el fragment no es nulo
        if (fragment != null) {
            FragmentManager fragmentManager = getFragmentManager();
            fragmentManager.beginTransaction().replace(R.id.container, fragment).commit();

            // Actualizamos el contenido segun la opcion elegida
            NavList.setItemChecked(position, true);
            NavList.setSelection(position);
            //Cambiamos el titulo en donde decia "
            setTitle(NavTitles[position-1]);
            //Cerramos el menu deslizable
            NavDrawerLayout.closeDrawer(NavList);
        } else {
            //Si el fragment es nulo mostramos un mensaje de error.
            Log.e("Error  ", "ShowFragment"+position);
        }
    }

    @Override
    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
        // Sync the toggle state after onRestoreInstanceState has occurred.
        DrawerToggle.syncState();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        DrawerToggle.onConfigurationChanged(newConfig);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Pass the event to ActionBarDrawerToggle, if it returns
        // true, then it has handled the app icon touch event
        if (DrawerToggle.onOptionsItemSelected(item)) {
            Log.e("mDrawerToggle pushed", "x");
            return true;
        }
        // Handle your other action bar items...
        return super.onOptionsItemSelected(item);
    }

}
