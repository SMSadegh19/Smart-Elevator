import android.app.Activity;
import android.content.Context;
import android.hardware.fingerprint.FingerprintManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends Activity {

    private static final int MAX_FINGERPRINTS = 10;

    private FingerprintManager mFingerprintManager;
    private FingerprintManager.CryptoObject mCryptoObject;
    private TextView mFingerprintStatus;

    private int mNumberOfFingerprints = 0;
    private List<byte[]> mFingerprintList = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mFingerprintManager = (FingerprintManager)getSystemService(Context.FINGERPRINT_SERVICE);
        mCryptoObject = new FingerprintManager.CryptoObject(mFingerprintManager.createCryptoObject());

        mFingerprintStatus = findViewById(R.id.fingerprint_status);

        // Register a listener to get called when a fingerprint is successfully authenticated
        mFingerprintManager.authenticate(mCryptoObject, new FingerprintManager.AuthenticationCallback() {
            @Override
            public void onAuthenticationSucceeded(FingerprintManager.AuthenticationResult result) {
                // Store the fingerprint data
                byte[] fingerprint = result.getCryptoObject().getCipher().getIV();
                mFingerprintList.add(fingerprint);

                mNumberOfFingerprints++;
                if (mNumberOfFingerprints == MAX_FINGERPRINTS) {
                    mFingerprintStatus.setText("Fingerprints saved!");
                } else {
                    mFingerprintStatus.setText(String.format("Fingerprint %d of %d saved!", mNumberOfFingerprints, MAX_FINGERPRINTS));
                }
            }

            @Override
            public void onAuthenticationFailed() {
                mFingerprintStatus.setText("Fingerprint authentication failed");
            }
        }, null);

        Button verifyButton = findViewById(R.id.verify_fingerprint_button);
        verifyButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mFingerprintManager.authenticate(mCryptoObject, new FingerprintManager.AuthenticationCallback() {
                    @Override
                    public void onAuthenticationSucceeded(FingerprintManager.AuthenticationResult result) {
                        byte[] fingerprint = result.getCryptoObject().getCipher().getIV();
                        if (mFingerprintList.contains(fingerprint)) {
                            mFingerprintStatus.setText("Fingerprint verified!");
                        } else {
                            mFingerprintStatus.setText("Fingerprint not found");
                        }
                    }

                    @Override
                    public void onAuthenticationFailed() {
                        mFingerprintStatus.setText("Fingerprint authentication failed");
                    }
                }, null);
            }
        });
    }
}
