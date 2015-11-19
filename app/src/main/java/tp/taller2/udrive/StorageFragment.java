package tp.taller2.udrive;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class StorageFragment extends Fragment {

    Double storageUsed;

    public static final StorageFragment newInstance(Double storageUsed) {
        StorageFragment f = new StorageFragment();
        Bundle bdl = new Bundle(1);
        bdl.putDouble("storageUsed", storageUsed);
        f.setArguments(bdl);
        return f;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_storage, container, false);

        storageUsed = getArguments().getDouble("storageUsed");
        TextView storage = (TextView) rootView.findViewById(R.id.storageUsed);
        storage.setText(storageUsed.toString() + "GB");


        return rootView;
    }
}
