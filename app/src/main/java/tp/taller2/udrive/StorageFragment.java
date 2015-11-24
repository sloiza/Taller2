package tp.taller2.udrive;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class StorageFragment extends Fragment {

    Float storageUsed;
    SessionManager session;

    public static final StorageFragment newInstance(Float storageUsed) {
        StorageFragment f = new StorageFragment();
        Bundle bdl = new Bundle(1);
        bdl.putFloat("storageUsed", storageUsed);
        f.setArguments(bdl);
        return f;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_storage, container, false);
        storageUsed = getArguments().getFloat("storageUsed");
        TextView storage = (TextView) rootView.findViewById(R.id.storageUsed);
        session = new SessionManager(getContext());
        storage.setText(session.getUserStorageUsed() + "GB");
        return rootView;
    }
}
