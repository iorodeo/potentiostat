"use strict";

let Potentiostat = require('./potentiostat');

let pstat = new Potentiostat('/dev/ttyACM0', (err) => {

  if (err) {
    console.log('open failed: ' + err);
  } else {

    //pstat.getHardwareVariant( (err, variant) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('hardware variant: ' + variant);
    //  }
    //});


    //pstat.getVolt( (err, volt) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('volt: ' + volt);
    //  }
    //});


    //pstat.setVolt(0.9, (err, volt) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('volt: ' + volt);
    //  }
    //});


    //pstat.getCurr( (err, curr) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('curr: ' + curr);
    //  }
    //});

    //pstat.getParam('linearSweep', (err,param) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('param: ' + JSON.stringify(param));
    //  }
    //});

    //let newParam = { 
    //  quietTime: 1000,
    //  quietValue: -0.1,
    //  startValue: -0.5,
    //  finalValue: 0.6,
    //  duration: 3000,
    //};

    //pstat.setParam('linearSweep', newParam, (err, param) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('param: ' + JSON.stringify(param));
    //  }
    //});

    //pstat.getVoltRange( (err,voltRange) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('voltRange: ' + voltRange);
    //  }
    //});

    //pstat.setVoltRange('2V', (err,voltRange) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('voltRange: ' + voltRange);
    //  }
    //});

    //let voltRangeList = pstat.getAllVoltRange();
    //console.log('allowed voltRange: ' + voltRangeList);

    //pstat.getCurrRange( (err,currRange) => {
    //  if (err) {
    //    console.log(err); 
    //  } else {
    //    console.log('currRange: ' + currRange);
    //  }
    //});

    //pstat.setCurrRange('10uA', (err,currRange) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('currRange: ' + currRange);
    //  }
    //});

    //pstat.getDeviceId( (err,deviceId) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('deviceId: ' + deviceId);
    //  }
    //});

    //pstat.setDeviceId(2, (err,deviceId) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('deviceId: ' + deviceId);
    //  }
    //});

    //pstat.getSamplePeriod((err,samplePeriod) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('samplePeriod: ' + samplePeriod);
    //  }
    //});

    //pstat.setSamplePeriod(10, (err,samplePeriod) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('samplePeriod: ' + samplePeriod);
    //  }
    //});

    //pstat.getSampleRate((err,sampleRate) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('sampleRate: ' + sampleRate);
    //  }
    //});

    //pstat.setSampleRate(100, (err,sampleRate) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('sampleRate: ' + sampleRate);
    //  }
    //});

    //pstat.getTestDoneTime('linearSweep', (err,testDoneTime) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('testDoneTime: ' + testDoneTime);
    //  }
    //});

    //pstat.getTestNames((err,testNames) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('testNames: ' + JSON.stringify(testNames));
    //  }
    //});

    //pstat.getFirmwareVersion((err,version) => {
    //  if (err) {
    //    console.log(err);
    //  } else {
    //    console.log('firmwareVersion: ' + version );
    //  }
    //});

    let testParam = { 
      quietTime: 1000,
      quietValue: -0.1,
      startValue: -0.5,
      finalValue: 0.6,
      duration: 3000,
    };

    let initCb = (err,data) => { 
      if (err) { 
        console.log(err);
      } else {
        console.log('running test, total time = ' + data.tDoneSec + ' (sec)');
      }
    }; 

    let doneCb = (err, data) => {
      if (err) {
        console.log(err);
      } else {
        console.log('test done');
        console.log('tsec.length = ' + data.tsec.length);
        console.log('volt.length = ' + data.volt.length);
        console.log('curr.length = ' + data.curr.length);
        process.exit(0);
      }
    };

    let dataCb = (err, data) => {
      if (err) {
        console.log(err);
      } else {
        let deci = 3;
        let tsec = data.tsec.toFixed(deci);
        let volt = data.volt.toFixed(deci);
        let curr = data.curr.toFixed(deci);
        console.log(tsec,volt,curr);
      }
    };
    pstat.runTest('linearSweep',initCb, doneCb, dataCb, testParam);

  }
}); 






