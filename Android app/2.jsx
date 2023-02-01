import React, { useState, useEffect } from 'react';
import FingerprintScanner from 'react-native-fingerprint-scanner';
import { View, Text } from 'react-native';

const App = () => {
  const [isAuthenticated, setIsAuthenticated] = useState(false);
  const [errorMessage, setErrorMessage] = useState('');

  useEffect(() => {
    FingerprintScanner
      .isSensorAvailable()
      .then(biometryType => {
        if (biometryType === FingerprintScanner.FINGERPRINT) {
          FingerprintScanner.authenticate({ title: 'Scan your fingerprint' })
            .then(() => {
              setIsAuthenticated(true);
              setErrorMessage('');
            })
            .catch(error => {
              setErrorMessage(error.message);
            });
        } else {
          setErrorMessage('Fingerprint authentication is not available on this device');
        }
      })
      .catch(error => {
        setErrorMessage(error.message);
      });
  }, []);

  return (
    <View style={{flex: 1, justifyContent: 'center', alignItems: 'center'}}>
      {isAuthenticated ? (
        <Text>Fingerprint authenticated!</Text>
      ) : (
        <Text>{errorMessage}</Text>
      )}
    </View>
  );
};

export default App;