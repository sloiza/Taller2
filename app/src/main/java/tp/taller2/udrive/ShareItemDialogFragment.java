package tp.taller2.udrive;

import android.app.Activity;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.app.DialogFragment;
import android.app.AlertDialog;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;

public class ShareItemDialogFragment extends DialogFragment {

    public static ShareItemDialogFragment newInstance(String itemName) {
        ShareItemDialogFragment frag = new ShareItemDialogFragment();
        Bundle args = new Bundle();
        args.putString("itemName", itemName);
        frag.setArguments(args);
        return frag;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        // Use the Builder class for convenient dialog construction
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        final String itemName = getArguments().getString("itemName");
        builder.setTitle("Share");
        builder.setMessage("Enter the user you want to share to");
        // Get the layout inflater
        LayoutInflater inflater = getActivity().getLayoutInflater();
        // Inflate and set the layout for the dialog
        // Pass null as the parent view because its going in the dialog layout
        View view = inflater.inflate(R.layout.dialog_share_item, null);
        final EditText shareUsersET = (EditText) view.findViewById(R.id.shareUsers);
        builder.setView(view)
                .setPositiveButton("Done", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        // Send the positive button event back to the host activity
                        String shareUsers = shareUsersET.getText().toString();
                        listener.onReturnValue(shareUsers);
                        listener.onReturnItemName(itemName);
                        listener.onDialogPositiveClick(ShareItemDialogFragment.this);
                    }
                })
                .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        // Send the negative button event back to the host activity
                        listener.onDialogNegativeClick(ShareItemDialogFragment.this);
                    }
                });
        // Create the AlertDialog object and return it
        return builder.create();
    }

    /* The activity that creates an instance of this dialog fragment must
     * implement this interface in order to receive event callbacks.
     * Each method passes the DialogFragment in case the host needs to query it. */
    public interface ShareItemDialogListener {
        void onDialogPositiveClick(DialogFragment dialog);
        void onDialogNegativeClick(DialogFragment dialog);
        void onReturnValue(String dialogInput);
        void onReturnItemName(String itemName);

    }

    ShareItemDialogListener listener;

    // Override the Fragment.onAttach() method to instantiate the LogOutDialogListener
    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        // Verify that the host activity implements the callback interface
        try {
            // Instantiate the LogOutDialogListener so we can send events to the host
            listener = (ShareItemDialogListener) activity;
        } catch (ClassCastException e) {
            // The activity doesn't implement the interface, throw exception
            throw new ClassCastException(activity.toString()
                    + " must implement ShareItemDialogListener");
        }
    }
}
