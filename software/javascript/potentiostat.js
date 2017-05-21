"use strict";

let empty = require('is-empty');
let ProgressBar = require('progress');
let SerialDevice = require('./serialdevice');

// Constants
const BAUDRATE = 115200;

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
    this.deviceOptions = {buadrate: 115200};
    this.hardwareVariant = null;
    this.device = new SerialDevice(port, {baudRate: BAUDRATE}, (err) => {
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
    });   
  }

  getHardwareVariant(callback) {
    let cmdName = 'getVariant';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) =>  {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.variant); 
    });
  }

  getVolt(callback) {
    let cmdName = 'getVolt';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.v); 
    });
  }

  setVolt(volt, callback) {
    let cmdName = 'setVolt';
    let cmd = {command: cmdName, v: volt};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.v);
    });
  }

  getCurr(callback) {
    let cmdName = 'getCurr';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.i); 
    });
  }

  getParam(testName, callback) {
    let cmdName = 'getParam';
    let cmd = {command: cmdName, test: testName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.param);
    });
  }

  setParam(testName, param, callback) {
    let cmdName = 'setParam';
    let cmd = {command: cmdName, test: testName, param: param};
    this._sendCmd(cmd, (err,msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.param);
    });
  }

  getVoltRange(callback) {
    let cmdName = 'getVoltRange';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.voltRange);
    });
  }

  setVoltRange(voltRange,callback) {
    if (VOLT_RANGE_LIST.includes(voltRange))  {
      let cmdName = 'setVoltRange';
      let cmd = {command: cmdName, voltRange: voltRange};
      this._sendCmd(cmd, (err, msg) => {
        let rsp = this._getCmdRsp(err, msg, cmdName);
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
    let cmdName = 'getCurrRange';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err,rsp.data.currRange);
    });
  }

  getAllCurrRange() {
    return HW_VARIANT_TO_CURR_RANGE[this.hardwareVariant];
  }

  setCurrRange(currRange, callback) { 
    let currRangeList = this.getAllCurrRange();
    if (currRangeList.includes(currRange)) { 
      let cmdName = 'setCurrRange'; 
      let cmd = {command: cmdName, currRange: currRange}; 
      this._sendCmd(cmd, (err, msg) => { 
        let rsp = this._getCmdRsp(err, msg, cmdName); 
        if (callback) callback(rsp.err, rsp.data.currRange); 
      }); 
    } else { 
      let err = new Error('currRange, ' + currRange + ', not allowed'); 
      if (callback) callback(err, null); 
    }
  }

  getDeviceId(callback) {
    let cmdName = 'getDeviceId';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.deviceId);
    });
  }

  setDeviceId(id, callback) {
    let cmdName = 'setDeviceId';
    let cmd = {command: cmdName, deviceId: id};
    this._sendCmd(cmd, (err,msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.deviceId);
    });
  }

  getSamplePeriod(callback) {
    let cmdName = 'getSamplePeriod';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.samplePeriod);
    });
  }

  setSamplePeriod(samplePeriod, callback) {
    let cmdName = 'setSamplePeriod';
    let cmd = {command: cmdName, samplePeriod: samplePeriod};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
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
    let cmdName = 'getTestDoneTime';
    let cmd = {command: cmdName, test: testName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.testDoneTime);
    });
  }

  getTestNames(callback) {
    let cmdName = 'getTestNames';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.testNames);
    });
  }

  getFirmwareVersion(callback) {
    let cmdName = 'getVersion';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      if (callback) callback(rsp.err, rsp.data.version);
    });
  }

  stopTest(callback) {
    let cmdName = 'stopTest';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err,msg) => {
      if (callback) callback(err);
    });
  }

  runTest(testName, initCallback, doneCallback, dataCallback, param, pbar) {
    
    // Called after setting parameters if parameters defined
    let setParamCallback = (err,param) => {
      if (err) {
        if (initCallback) initCallback(err,null);
        if (doneCallback) doneCallback(err,null);
        return;
      } 
      this.runTest(testName, initCallback, doneCallback, dataCallback, null, pbar);
    };

    // Called after getting the total time required by the test
    let getTestDoneTimeCallback = (err, testDoneTime) => {
      if (err) {
        if (initCallback) initCallback(err,null);
        if (doneCallback) doneCallback(err,null);
        return;
      }

      let tsecArray = [];
      let voltArray = [];
      let currArray = [];
      let cmdName = 'runTest';
      let cmd = {command: cmdName, test: testName};
      let testDoneTimeSec = millisecondToSecond(testDoneTime);
     
      // Setup progress bar
      let progressBar = null;
      let tsecLast = null;
      if (pbar) {
        progressBar = new ProgressBar('running test [:bar] :percent :etas', {
          complete: '=',
          incomplete: ' ',
          width: 80,
          total: testDoneTimeSec, 
        });
        tsecLast = 0.0;
      }

      // Callback function for sendCmd. Receives initial response to 
      // command and handles subsequent stream data stream.
      let sendCmdCallback = (err, msg) => { 
        if (err) {
          if (initCallback) initCallback(err,null); 
          if (doneCallback) doneCallback(err,null);
          return;
        }
        let msgObj = JSON.parse(msg);
        if ('success' in msgObj) { 
          // The msgObj is the response to the initial runTest command
          if (msgObj.success) { 
            let initResult = {tDoneSec: testDoneTimeSec};
            if (initCallback) initCallback(null,initResult); 
            return true;  // true => callback will be called again on next serial readline
          } else {
            let err = new Error(msgObj.message); 
            if (initCallback) initCallback(err,null); 
            if (doneCallback) doneCallback(err,null); 
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
            if (dataCallback) dataCallback(null,dataResult);
            if (pbar) {
              let dt = tsec - tsecLast;
              tsecLast = tsec;
              progressBar.tick(dt);
            }
            return true; // true => callback will be called again on next serial readline
          } else { 
            let doneResult= {tsec: tsecArray, volt: voltArray, curr: currArray};
            if (doneCallback) doneCallback(null,doneResult);
            return;
          }
        }
      }; // let sendCmdCallback = 

      // Send command to start running test.
      this._sendCmd(cmd, sendCmdCallback); 

    }; //  let getTestDoneTimeCallback = 

    if (param) { 
      // set test parameters, then recall with param undefined
      this.setParam(testName,param,setParamCallback);       
      return;
    } 

    // Get total time required to complete the test and then run test.
    this.getTestDoneTime(testName, getTestDoneTimeCallback);

  } // runTest()

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

};


module.exports = Potentiostat;

