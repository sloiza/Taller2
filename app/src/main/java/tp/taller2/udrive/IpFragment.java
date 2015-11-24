package tp.taller2.udrive;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.TextInputLayout;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;

public class IpFragment extends Fragment {

    EditText ipET;
    EditText portET;
    TextInputLayout inputLayoutIp;
    TextInputLayout inputLayoutPort;
    SessionManager session;
    String ip;
    String port;
    Button ipPortButton;
    private updateIpAndPortListener listener;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_ip, container, false);

        inputLayoutIp = (TextInputLayout) rootView.findViewById(R.id.input_layout_ip);
        inputLayoutPort = (TextInputLayout) rootView.findViewById(R.id.input_layout_port);

        ipET = (EditText) rootView.findViewById(R.id.ipAddress);
        portET = (EditText) rootView.findViewById(R.id.port);
        ipPortButton = (Button) rootView.findViewById(R.id.ipPortButton);

        ipPortButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (null != listener) {
                    ip = ipET.getText().toString();
                    port = portET.getText().toString();
                    listener.getIpAndPortData(ip, port);
                }
            }
        });

        session = new SessionManager(getContext());

        return rootView;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        try {
            listener = (updateIpAndPortListener) activity;
        } catch (ClassCastException e) {
            throw new ClassCastException(activity.toString()
                    + " must implement OnFragmentInteractionListener");
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        listener = null;
    }

    public interface updateIpAndPortListener {
        void getIpAndPortData(String ip, String port);
    }
}

