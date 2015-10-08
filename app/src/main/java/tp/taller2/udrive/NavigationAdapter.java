package tp.taller2.udrive;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * Created by mati on 08/10/15.
 */
public class NavigationAdapter extends BaseAdapter{

    private Activity activity;
    ArrayList<ItemObject> arrayItems;

    public NavigationAdapter(Activity activity, ArrayList<ItemObject> listArray){
        super();
        this.activity = activity;
        this.arrayItems = listArray;
    }

    @Override
    public int getCount() {
        return arrayItems.size();
    }

    @Override
    public Object getItem(int position) {
        return arrayItems.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    public static class Row{
        TextView titleItem;
        ImageView icon;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        Row view;
        LayoutInflater inflator = activity.getLayoutInflater();
        if(convertView == null){
            view = new Row();
            ItemObject item = arrayItems.get(position);
            convertView = inflator.inflate(R.layout.itm, null);

            view.titleItem = (TextView) convertView.findViewById(R.id.title_item);
            view.titleItem.setText(item.getTitle());

            view.icon = (ImageView) convertView.findViewById(R.id.icon);
            view.icon.setImageResource(item.getIcon());

            convertView.setTag(view);
        } else {
            view = (Row) convertView.getTag();
        }
        return convertView;
    }
}
