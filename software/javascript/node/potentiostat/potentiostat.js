"use strict";

let os = require('os');
let fs = require('fs');
let empty = require('is-empty');
let ProgressBar = require('progress');
let SerialDevice = require('./serialdevice');

// Constants
const BAUDRATE = 115200;
const DATA_FILE_PRECISION = 10;

const VOLT_RANGE_LIST = [
  '1V', 
  '2V', 
  '5V', 
  '10V'
];

const CURR_RANGE_LIST_NANO_AMP = [
  '60nA', 
  '100nA', 
  '1uA', 
  '10uA'
];

const CURR_RANGE_LIST_MICRO_AMP = [
  '1uA', 
  '10uA', 
  '100uA', 
  '1000uA'
];

const HW_VARIANT_TO_CURR_RANGE = {
  'nanoAmpV0.1': CURR_RANGE_LIST_NANO_AMP,
  'microAmpV0.1':CURR_RANGE_LIST_MICRO_AMP,
};
const CMD_KEYS_FORCE_INT = [
  'quietTime', 
  'duration', 
  'deviceId', 
  'samplePeriod', 
  'period', 
  'numCycles'
];

// Make constant objects immutable
Object.freeze(VOLT_RANGE_LIST);
Object.freeze(CURR_RANGE_LIST_NANO_AMP);
Object.freeze(CURR_RANGE_LIST_MICRO_AMP);
Object.freeze(HW_VARIANT_TO_CURR_RANGE);
Object.freeze(CMD_KEYS_FORCE_INT);

var secondToMillisecond = (val) => {
  return  val*1.0e3;
}

var millisecondToSecond = (val) => {
  return val*1.0e-3;
}


class Potentiostat {

  constructor(port, callback) {
    this.hardwareVariant = null;

    this.device = new SerialDevice(port, {buadRate: BAUDRATE}, (err) => {
      this._onDeviceOpen(err,callback);
    }); 

    //const promise = new Promise( (resolve,reject) => {
    //  this.device = new SerialDevice(port, {buadRate: BAUDRATE}, (err) => {
    //    this._onDeviceOpen(err,callback);
    //  }); 
    //});

  }

  getHardwareVariant(callback) {
    let cmd = {command: 'getVariant'};
    this._sendCmdGetRsp(cmd, (err, rsp) =>  {
      if (callback) callback(rsp.err, rsp.data.variant); 
    });
  }

  getVolt(callback) {
    let cmd = {command: 'getVolt'};
    this._sendCmdGetRsp(cmd, (err,rsp) => {
      if (callback) callback(rsp.err, rsp.data.v);
    });
  }

  getVoltPromise() {
    return new Promise( (resolve,reject) => {
      let cmd = {command: 'getVolt'};
      this._sendCmdGetRsp(cmd, (err,rsp) => {
        if (err) { 
          reject(err);
        } else {
          resolve(rsp.data.v);
        }
      });
    });
  }

  setVolt(volt, callback) {
    let cmd = {command: 'setVolt', v: volt};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.v);
    });
  }

  getCurr(callback) {
    let cmd = {command: 'getCurr'};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.i); 
    });
  }

  getParam(testName, callback) {
    let cmd = {command: 'getParam', test: testName};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.param);
    });
  }

  setParam(testName, param, callback) {
    let cmd = {command: 'setParam', test: testName, param: param};
    this._sendCmdGetRsp(cmd, (err,rsp) => {
      if (callback) callback(rsp.err, rsp.data.param);
    });
  }

  getVoltRange(callback) {
    let cmd = {command: 'getVoltRange'};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.voltRange);
    });
  }

  setVoltRange(voltRange,callback) {
    if (VOLT_RANGE_LIST.includes(voltRange))  {
      let cmd = {command: 'setVoltRange', voltRange: voltRange};
      this._sendCmdGetRsp(cmd, (err, rsp) => {
        if (callback) callback(rsp.err, rsp.data.voltRange);
      });
    } else {
      let err = new Error('voltRange, ' + voltRange + ', is not allowed');
      if (callback) callback(err,null);
    }
  }

  getAllVoltRange() {
    return VOLT_RANGE_LIST;
  }

  getCurrRange(callback) {
    let cmd = {command: 'getCurrRange'};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err,rsp.data.currRange);
    });
  }

  getAllCurrRange() {
    return HW_VARIANT_TO_CURR_RANGE[this.hardwareVariant];
  }

  setCurrRange(currRange, callback) { 
    let currRangeList = this.getAllCurrRange();
    if (currRangeList.includes(currRange)) { 
      let cmd = {command: 'setCurrRange', currRange: currRange}; 
      this._sendCmdGetRsp(cmd, (err, rsp) => { 
        if (callback) callback(rsp.err, rsp.data.currRange); 
      }); 
    } else { 
      let err = new Error('currRange, ' + currRange + ', not allowed'); 
      if (callback) callback(err, null); 
    }
  }

  getDeviceId(callback) {
    let cmd = {command: 'getDeviceId'};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.deviceId);
    });
  }

  setDeviceId(id, callback) {
    let cmd = {command: 'setDeviceId', deviceId: id};
    this._sendCmdGetRsp(cmd, (err,rsp) => {
      if (callback) callback(rsp.err, rsp.data.deviceId);
    });
  }

  getSamplePeriod(callback) {
    let cmd = {command: 'getSamplePeriod'};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.samplePeriod);
    });
  }

  setSamplePeriod(samplePeriod, callback) {
    let cmd = {command: 'setSamplePeriod', samplePeriod: samplePeriod};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.samplePeriod);
    });
  }

  getSampleRate(callback) {
    this.getSamplePeriod((err, samplePeriod) => {
      if (err) {
        if (callback) callback(err, null);
      } else {
        let sampleRate = 1.0/millisecondToSecond(samplePeriod);
        if (callback) callback(null, sampleRate);
      }
    });
  }

  setSampleRate(sampleRate, callback) {
    let samplePeriod = Math.round(secondToMillisecond(1.0/sampleRate));
    this.setSamplePeriod(samplePeriod, (err, samplePeriod) => {
      let sampleRate = 1.0/millisecondToSecond(samplePeriod);
      if (callback) callback(err,sampleRate);
    });
  }

  getTestDoneTime(testName, callback) {
    let cmd = {command: 'getTestDoneTime', test: testName};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.testDoneTime);
    });
  }

  getTestNames(callback) {
    let cmd = {command: 'getTestNames'};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.testNames);
    });
  }

  getFirmwareVersion(callback) {
    let cmd = {command: 'getVersion'};
    this._sendCmdGetRsp(cmd, (err, rsp) => {
      if (callback) callback(rsp.err, rsp.data.version);
    });
  }

  stopTest(callback) {
    let cmd = {command: 'stopTest'};
    this._sendCmdGetRsp(cmd, (err,rsp) => {
      if (callback) callback(err);
    });
  }

  runTest(testName, options) { 
    // options  
    // ---------------------------------------------------------------------
    //   testParam:     optional test parameters set prior to running test, 
    //   initCallback:  function called on start of test,
    //   doneCallback:  function called at end of test, 
    //   dataCallback:  function called with each acquired data point, 
    //   progressBar:   show progress bar during test (true/false)
    //   fileName:      name of output file for saving data
    //
    //----------------------------------------------------------------------

    // Called after setting parameters if parameters defined
    let runTestAfterSetParam = (err,testParam) => {
      if (err) {
        if (options.initCallback) options.initCallback(err,null);
        if (options.doneCallback) options.doneCallback(err,null);
        return;
      } 
      let optionsMinusParam = {};
      Object.assign(optionsMinusParam,options);
      delete optionsMinusParam.testParam;
      this.runTest(testName, optionsMinusParam);    
    };

    // Called after getting the total time required by the test
    let setupAndRunTest = (err, testDoneTime) => {
      if (err) {
        if (options.initCallback) options.initCallback(err,null);
        if (options.doneCallback) options.doneCallback(err,null);
        return;
      }

      let tsecArray = [];
      let voltArray = [];
      let currArray = [];
      let cmd = {command: 'runTest', test: testName};
      let testDoneTimeSec = millisecondToSecond(testDoneTime);
     
      // Setup progress bar
      let progressBar = null;
      let tsecLast = null;
      if (options.progressBar) {
        progressBar = new ProgressBar('running test [:bar] :percent :etas', {
          complete: '=',
          incomplete: ' ',
          width: 80,
          total: testDoneTimeSec, 
        });
        tsecLast = 0.0;
      }

      // Setup output file
      let wstream = null;
      if (options.fileName) {
        wstream = fs.createWriteStream(options.fileName);
      }

      // Callback function for sendCmd. Receives initial response to command 
      // and handles subsequent data stream until run is complete.
      let sendCmdCallback = (err, msg) => { 
        if (err) {
          if (options.initCallback) options.initCallback(err,null); 
          if (options.doneCallback) options.doneCallback(err,null);
          return;
        }
        let msgObj = JSON.parse(msg);
        if ('success' in msgObj) { 
          // The msgObj is the response to the initial runTest command
          if (msgObj.success) { 
            let initResult = {tDoneSec: testDoneTimeSec};
            if (options.initCallback) options.initCallback(null,initResult); 
            return true;  // true => callback will be called again on next serial readline
          } else {
            let err = new Error(msgObj.message); 
            if (options.initCallback) options.initCallback(err,null); 
            if (options.doneCallback) options.doneCallback(err,null); 
            return;
          }
        } else {
          // The msgObj is a data point 
          if (!empty(msgObj)) {
            let tsec = millisecondToSecond(msgObj.t);
            tsecArray.push(tsec);
            voltArray.push(msgObj.v);
            currArray.push(msgObj.i);
            let dataResult = {tsec:tsec, volt:msgObj.v, curr:msgObj.i, tDoneSec: testDoneTimeSec}
            if (options.dataCallback) options.dataCallback(null,dataResult);
            if (options.fileName) { 
              wstream.write(tsec.toPrecision(DATA_FILE_PRECISION) + ', '); 
              wstream.write(msgObj.v.toPrecision(DATA_FILE_PRECISION) + ', '); 
              wstream.write(msgObj.i.toPrecision(DATA_FILE_PRECISION) + os.EOL); 
            }
            if (options.progressBar) {
              let dt = tsec - tsecLast;
              tsecLast = tsec;
              progressBar.tick(dt);
            }
            return true; // true => callback will be called again on next serial readline
          } else { 
            let doneResult= {tsec: tsecArray, volt: voltArray, curr: currArray};
            if (options.fileName) wstream.end(); 
            if (options.doneCallback) options.doneCallback(null,doneResult);
            return;
          }
        }
      }; // let sendCmdCallback = 

      // Send command to start running test.
      this._sendCmd(cmd, sendCmdCallback); 

    }; //  let setupAndRunTest = 

    if (options.testParam) { 
      // set test parameters, then recall with param undefined
      this.setParam(testName,options.testParam,runTestAfterSetParam);       
      return;
    } 

    // Get total time required to complete the test and then run test.
    this.getTestDoneTime(testName, setupAndRunTest);

  } // runTest()


  _onDeviceOpen(err,callback) {
    if (err) { 
      if (callback) callback(err);
      return;
    }  
    this.getHardwareVariant((err, hardwareVariant) => { 
      if (!err) {
        this.hardwareVariant = hardwareVariant;
      } 
      if (callback) callback(err);
    });
  }

  _getCmdRsp(err, msg, cmdName) {
    let rspData = {};
    if (err) {
      return {data: rspData, err: err};
    } 
    let rspErr = null;
    let msgObj = JSON.parse(msg);
    if (!msgObj.success) {
      rspErr = new Error(msgObj.message);
      return {data: rspData, err: rspErr};
    } 
    if (msgObj.response.command != cmdName) {
      rspErr = new Error('command received does not match');
      return {data: rspData, err: rspErr};
    } 
    rspData = msgObj.response;
    delete rspData.command;
    return {data: rspData, err: rspErr};
  }

  _sendCmd(cmd, callback) {
    cmd = this._forceTimeValsToInt(cmd);
    this.device.sendCmd(JSON.stringify(cmd), callback);
  };

  _sendCmdGetRsp(cmd, callback) {
    var wrappedCallback = (err,msg) => {
      let rsp = this._getCmdRsp(err, msg, cmd.command);
      callback(err,rsp);
    };
    this._sendCmd(cmd, wrappedCallback);
  };

  _forceTimeValsToInt(cmd) {
    for (let key of Object.keys(cmd)) {
      if (typeof cmd[key] === 'object') {
        cmd[key] = this._forceTimeValsToInt(cmd[key]);
      } else {
        if (CMD_KEYS_FORCE_INT.includes(key)) {
          cmd[key] = Math.floor(cmd[key]);
        }
      }
    }
    return cmd;
  }

}; // class Potentiostat


module.exports = Potentiostat;

