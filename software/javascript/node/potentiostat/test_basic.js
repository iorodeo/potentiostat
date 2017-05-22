"use strict";

let Potentiostat = require('./potentiostat');

let dataFileName = 'data.txt';
let testName = 'linearSweep';

let testParam = { 
  quietTime: 1000,
  quietValue: -0.5,
  startValue: -0.5,
  finalValue: 0.6,
  duration: 5000,
};

let pstat = new Potentiostat('/dev/ttyACM0', (err) => {

  if (err) {
    console.log('open failed: ' + err);
  } else {

    pstat.setSampleRate(100, (err,sampleRate) => {
      if (err) {
        console.log(err);
      } else {
        console.log('sampleRate: ' + sampleRate);
      }
    });

    pstat.setCurrRange('100uA', (err,currRange) => {
      if (err) {
        console.log(err);
      } else {
        console.log('currRange: ' + currRange);
      }
    });

    let initCb = (err, data) => { if (err) console.log(err); };
    let doneCb = (err, data) => { (err) ? console.log(err) : process.exit(0);};

    let testOptions = {
      testParam: testParam, 
      initCallback: initCb, 
      doneCallback: doneCb,
      progressBar: true,
      fileName: dataFileName,
    };
    pstat.runTest(testName,testOptions);

  }
}); 






