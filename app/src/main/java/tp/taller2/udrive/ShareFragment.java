package tp.taller2.udrive;

/**
 * Created by mati on 30/09/15.
 */
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

public class ShareFragment extends Fragment {

    public ShareFragment(){}

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        return inflater.inflate(R.layout.fragment_share, container, false);
    }
}
