import React, { useState } from "react";
// import { makeStyles } from "@mui/styles";
import * as Bluetooth from 'react-bluetooth';
import Paper from "@mui/material/Paper";
import Typography from "@mui/material/Typography";
import Button from "@mui/material/Button";
import Grid from "@mui/material/Grid";

// const useStyles = makeStyles((theme) => ({
//   root: {
//     padding: theme.spacing(3, 2),
//     margin: theme.spacing(2),
//   },
//   button: {
//     margin: theme.spacing(1),
//   },
// }));

async function pairRequest() {
    try {
      const result = await Bluetooth.requestDeviceAsync();
  
      if (result.type === 'cancel') {
        return;
      }
  
      const device = result.device;
    } catch ({ message, code }) {
      console.log('Error:', message, code);
    }
}

const ElevatorManager = () => {
//   const classes = useStyles();
  const [elevatorLocation, setElevatorLocation] = useState(1);
  const [elevatorOrdered, setElevatorOrdered] = useState(false);

  const handleOrderElevator = (floor) => {
    setElevatorOrdered(true);
    setElevatorLocation(floor);
  };

  const [isBluetoothRequested, setIsBluetoothRequested] = React.useState(false);

  const handleBluetoothRequest = async () => {
    setIsBluetoothRequested(true);
    await pairRequest();
  };

  return (
    <div>
      <Grid 
        container
        spacing={2}
        direction="column"
        justifyContent="space-around"
        alignItems="center"
      >
        <Grid item xs={3}>
          <Paper
            // direction="column"
            // justifyContent="space-around"
            // alignItems="center"
          >
            <Typography variant="h4" component="h1">
              Smart Elevator Manager
            </Typography>
          </Paper>
        </Grid>
        <Grid item xs={3}>
            {!isBluetoothRequested && (
            <Button
                variant="contained"
                color="primary"
                onClick={() => handleBluetoothRequest()}
            >
                Connect to Bluetooth
            </Button>
            )}
        </Grid>
        <Grid item xs={3}>
          <Paper>
            <Typography variant="h5" component="h3">
              Floor 1
            </Typography>
            <Button
              variant="contained"
              color="primary"
              onClick={() => handleOrderElevator(1)}
            >
              Order Elevator
            </Button>
            {elevatorLocation === 1 && elevatorOrdered && (
              <Typography component="p">Elevator Here</Typography>
            )}
          </Paper>
        </Grid>
        <Grid item xs={3}>
          <Paper>
            <Typography variant="h5" component="h3">
              Floor 2
            </Typography>
            <Button
              variant="contained"
              color="primary"
              onClick={() => handleOrderElevator(2)}
            >
              Order Elevator
            </Button>
            {elevatorLocation === 2 && elevatorOrdered && (
              <Typography component="p">Elevator Here</Typography>
            )}
          </Paper>
        </Grid>
        <Grid item xs={3}>
          <Paper>
            <Typography variant="h5" component="h3">
              Floor 3
            </Typography>
            <Button
              variant="contained"
              color="primary"
              onClick={() => handleOrderElevator(3)}
            >
              Order Elevator
            </Button>
            {elevatorLocation === 3 && elevatorOrdered && (
              <Typography component="p">Elevator Here</Typography>
            )}
          </Paper>
        </Grid>
        <Grid item xs={3}>
          <Paper>
            <Typography variant="h5" component="h3">
              Floor 4
            </Typography>
            <Button
              variant="contained"
              color="primary"
              onClick={() => handleOrderElevator(4)}
            >
              Order Elevator
            </Button>
            {elevatorLocation === 4 && elevatorOrdered && (
              <Typography component="p">Elevator Here</Typography>
            )}
          </Paper>
        </Grid>
      </Grid>
    </div>
  );
};

export default ElevatorManager;
