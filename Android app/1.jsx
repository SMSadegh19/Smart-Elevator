import React, { useState } from 'react';
import FingerprintScanner from 'react-native-fingerprint-android';

const App = () => {
  const [fingerprints, setFingerprints] = useState([]);

  const handleStoreFingerprint = async () => {
    try {
      const result = await FingerprintScanner.authenticate({
        onAttempt: error => console.log(error),
      });

      if (result.withBiometrics) {
        setFingerprints([...fingerprints, result.token]);
      }
    } catch (error) {
      console.log(error);
    }
  };

  const handleVerifyFingerprint = async () => {
    try {
      const result = await FingerprintScanner.authenticate({
        onAttempt: error => console.log(error),
      });

      if (result.withBiometrics) {
        const isMatched = fingerprints.includes(result.token);
        console.log(isMatched ? 'Fingerprint matched' : 'Fingerprint not matched');
      }
    } catch (error) {
      console.log(error);
    }
  };

  return (
    <>
      <Button title="Store fingerprint" onPress={handleStoreFingerprint} />
      <Button title="Verify fingerprint" onPress={handleVerifyFingerprint} />
    </>
  );
};

export default App;
