"use strict";

let Potentiostat = require('./potentiostat');


let pstat = new Potentiostat('/dev/ttyACM0', (err) => {

  if (err) {
    console.log('open failed: ' + err);
  } else {

    pstat.getHardwareVariant( (err, variant) => {
      if (err) {
        console.log(err);
      } else {
        console.log('hardware variant: ' + variant);
      }
    });


    pstat.getVolt( (err, volt) => {
      if (err) {
        console.log(err);
      } else {
        console.log('volt: ' + volt);
      }
    });


    pstat.setVolt(0.9, (err, volt) => {
      if (err) {
        console.log(err);
      } else {
        console.log('volt: ' + volt);
      }
    });


    pstat.getCurr( (err, curr) => {
      if (err) {
        console.log(err);
      } else {
        console.log('curr: ' + curr);
      }
    });

    pstat.getParam('linearSweep', (err,param) => {
      if (err) {
        console.log(err);
      } else {
        console.log('param: ' + JSON.stringify(param));
      }
    });

    let newParam = { 
      quietTime: 1000,
      quietValue: -0.1,
      startValue: -0.5,
      finalValue: 0.6,
      duration: 3000,
    };

    pstat.setParam('linearSweep', newParam, (err, param) => {
      if (err) {
        console.log(err);
      } else {
        console.log('param: ' + JSON.stringify(param));
      }
    });

    pstat.getVoltRange( (err,voltRange) => {
      if (err) {
        console.log(err);
      } else {
        console.log('voltRange: ' + voltRange);
      }
    });

    pstat.setVoltRange('2V', (err,voltRange) => {
      if (err) {
        console.log(err);
      } else {
        console.log('voltRange: ' + voltRange);
      }
    });

    let voltRangeList = pstat.getAllVoltRange();
    console.log('allowed voltRange: ' + voltRangeList);

    pstat.getCurrRange( (err,currRange) => {
      if (err) {
        console.log(err); 
      } else {
        console.log('currRange: ' + currRange);
      }
    });

    pstat.setCurrRange('10uA', (err,currRange) => {
      if (err) {
        console.log(err);
      } else {
        console.log('currRange: ' + currRange);
      }
    });

    pstat.getDeviceId( (err,deviceId) => {
      if (err) {
        console.log(err);
      } else {
        console.log('deviceId: ' + deviceId);
      }
    });

    pstat.setDeviceId(2, (err,deviceId) => {
      if (err) {
        console.log(err);
      } else {
        console.log('deviceId: ' + deviceId);
      }
    });

    pstat.getSamplePeriod((err,samplePeriod) => {
      if (err) {
        console.log(err);
      } else {
        console.log('samplePeriod: ' + samplePeriod);
      }
    });

    pstat.setSamplePeriod(10, (err,samplePeriod) => {
      if (err) {
        console.log(err);
      } else {
        console.log('samplePeriod: ' + samplePeriod);
      }
    });

    pstat.getSampleRate((err,sampleRate) => {
      if (err) {
        console.log(err);
      } else {
        console.log('sampleRate: ' + sampleRate);
      }
    });

    pstat.setSampleRate(50, (err,sampleRate) => {
      if (err) {
        console.log(err);
      } else {
        console.log('sampleRate: ' + sampleRate);
      }
    });

    pstat.getTestDoneTime('linearSweep', (err,testDoneTime) => {
      if (err) {
        console.log(err);
      } else {
        console.log('testDoneTime: ' + testDoneTime);
      }
    });

    pstat.getTestNames((err,testNames) => {
      if (err) {
        console.log(err);
      } else {
        console.log('testNames: ' + JSON.stringify(testNames));
      }
    });

    pstat.getFirmwareVersion((err,version) => {
      if (err) {
        console.log(err);
      } else {
        console.log('firmwareVersion: ' + version );
      }
    });

  }
}); 


// OLD
// ------------------------------------------------------------------------------
//
//let empty = require('is-empty');
//let SerialDevice = require('./serialdevice');
//let device = new SerialDevice('/dev/ttyACM0', {baudRate: 115200}, (error) => { 
//
//  if (error) {
//    console.log('error opening device: ' + error);
//  }
//
//  // Set sample period
//  let cmd = {
//    command: 'setSamplePeriod',
//    samplePeriod: 10,
//  };
//
//  device.sendCmd(JSON.stringify(cmd), (data) => {
//    let dataObj = JSON.parse(data);
//    //console.log(JSON.stringify(dataObj));
//  });
//
//  // Set Test parameters
//  cmd = { 
//    command: 'setParam', 
//    test: 'linearSweep', 
//    param: {
//      quietTime: 1000,
//      quietValue: -0.1,
//      startValue: -0.1,
//      stopValue: 0.9,
//      duration: 1000
//    }
//  }; 
//
//  device.sendCmd(JSON.stringify(cmd), (data) => {
//    let dataObj = JSON.parse(data);
//    //console.log(JSON.stringify(dataObj));
//  });
//
//  // Run test
//  cmd = {
//    command: 'runTest',
//    test: 'linearSweep',
//  };
//
//  device.sendCmd(JSON.stringify(cmd), (data) => {
//    let dataObj = JSON.parse(data);
//    //console.log(JSON.stringify(dataObj));
//    if (!empty(dataObj)) {
//      console.log(dataObj);
//      return true;
//    } else {
//      process.exit(0);
//    }
//  });
//
//});
//
//-----------------------------------------------------------------------------




