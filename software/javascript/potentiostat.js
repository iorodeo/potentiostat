"use strict";

let empty = require('is-empty');
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


class Potentiostat {

  constructor(port, callback) {
    this.deviceOptions = {buadrate: 115200};
    this.hardwareVariant = null;
    let _this = this;
    this.device = new SerialDevice(port, {baudRate: BAUDRATE}, (err) => {
      if (err) { 
        callback(err);
      } else { 
        _this.getHardwareVariant((err, hardwareVariant) => { 
          if (!err) {
            _this.hardwareVariant = hardwareVariant;
          } 
          callback(err);
        });
      }
    });   
  }

  _getCmdRsp(err, msg, cmdName) {
    //console.log(msg);
    if (err) {
      return {data: {}, err: err};
    } else {
      let rspData = {};
      let rspErr = null;
      let msgObj = JSON.parse(msg);
      if (msgObj.success) {
        if (msgObj.response.command == cmdName) {
          rspData = msgObj.response;
          delete rspData.command;
        } else {
          rspErr = new Error('command received does not match');
        }
      } else {
        rspErr = new Error(msgObj.message);
      }
      return {data: rspData, err: rspErr};
    }
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

  getHardwareVariant(callback) {
    let cmdName = 'getVariant';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) =>  {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.variant);
    });
  }

  getVolt(callback) {
    let cmdName = 'getVolt';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.v);
    });
  }

  setVolt(volt, callback) {
    let cmdName = 'setVolt';
    let cmd = {command: cmdName, v: volt};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.v);
    });
  }

  getCurr(callback) {
    let cmdName = 'getCurr';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.i);
    });
  }

  getParam(testName, callback) {
    let cmdName = 'getParam';
    let cmd = {command: cmdName, test: testName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.param);
    });
  }

  setParam(testName, param, callback) {
    let cmdName = 'setParam';
    let cmd = {command: cmdName, test: testName, param: param};
    this._sendCmd(cmd, (err,msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.param);
    });
  }

  getVoltRange(callback) {
    let cmdName = 'getVoltRange';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.voltRange);
    });
  }

  setVoltRange(voltRange,callback) {
    if (VOLT_RANGE_LIST.includes(voltRange))  {
      let cmdName = 'setVoltRange';
      let cmd = {command: cmdName, voltRange: voltRange};
      this._sendCmd(cmd, (err, msg) => {
        let rsp = this._getCmdRsp(err, msg, cmdName);
        callback(rsp.err, rsp.data.voltRange);
      });
    } else {
      let err = new Error('voltRange, ' + voltRange + ', is not allowed');
      callback(err,null);
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
      callback(rsp.err,rsp.data.currRange);
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
        callback(rsp.err, rsp.data.currRange); 
      }); 
    } else { 
      let err = new Error('currRange, ' + currRange + ', not allowed'); 
      callback(err, null); 
    }
  }

  getDeviceId(callback) {
    let cmdName = 'getDeviceId';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.deviceId);
    });
  }

  setDeviceId(id, callback) {
    let cmdName = 'setDeviceId';
    let cmd = {command: cmdName, deviceId: id};
    this._sendCmd(cmd, (err,msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.deviceId);
    });
  }

  getSamplePeriod(callback) {
    let cmdName = 'getSamplePeriod';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.samplePeriod);
    });
  }

  setSamplePeriod(samplePeriod, callback) {
    let cmdName = 'setSamplePeriod';
    let cmd = {command: cmdName, samplePeriod: samplePeriod};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.samplePeriod);
    });
  }

  getSampleRate(callback) {
    this.getSamplePeriod((err, samplePeriod) => {
      if (err) {
        callback(err, null);
      } else {
        let sampleRate = 1.0/millisecondToSecond(samplePeriod);
        callback(null, sampleRate);
      }
    });
  }

  setSampleRate(sampleRate, callback) {
    let samplePeriod = Math.round(secondToMillisecond(1.0/sampleRate));
    this.setSamplePeriod(samplePeriod, (err, samplePeriod) => {
      let sampleRate = 1.0/millisecondToSecond(samplePeriod);
      callback(err,sampleRate);
    });
  }

  getTestDoneTime(testName, callback) {
    let cmdName = 'getTestDoneTime';
    let cmd = {command: cmdName, test: testName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.testDoneTime);
    });
  }

  getTestNames(callback) {
    let cmdName = 'getTestNames';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.testNames);
    });
  }

  getFirmwareVersion(callback) {
    let cmdName = 'getVersion';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err, msg) => {
      let rsp = this._getCmdRsp(err, msg, cmdName);
      callback(rsp.err, rsp.data.version);
    });
  }

  stopTest(callback) {
    let cmdName = 'stopTest';
    let cmd = {command: cmdName};
    this._sendCmd(cmd, (err,msg) => {
      callback(err);
    });
  };

};

function secondToMillisecond(val) {
  return  val*1.0e3;
}

function millisecondToSecond(val) {
  return val*1.0e-3;
}


module.exports = Potentiostat;

