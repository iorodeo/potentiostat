"use strict";

let SerialPort = require('serialport');


class SerialDevice {

  constructor(port, options, openCallback) {

    this.busy = false;
    this.cmdQueue = [];
    this.cmdCurrent = null;

    let serialOptions = options;
    if (!('parser' in options)) {
      serialOptions.parser = SerialPort.parsers.readline('\n');
    }
    this.serial = new SerialPort(port,serialOptions);

    let onDataCallback = (data) => {
      if (!this.cmdCurrent) {
        return;
      }
      let moreFlag = false;
      if (this.cmdCurrent.callback) { 
        moreFlag = this.cmdCurrent.callback(null,data)
      }
      if (moreFlag) {
        this.cmdQueue.unshift({
          message: null, 
          callback: this.cmdCurrent.callback
        });
      } 
      this.processQueue();
    };

    this.serial.on('open', openCallback);
    this.serial.on('data', onDataCallback); 
  }

  sendCmd(data,callback) {
    this.cmdQueue.push({message: data, callback: callback});
    if (this.busy) {
      return;
    }
    this.busy = true;
    this.processQueue();
  }

  processQueue() {
    let cmdNext  = this.cmdQueue.shift();
    if (!cmdNext) {
      this.busy = false;
      this.cmdCurrent = null; 
      return;
    }
    this.cmdCurrent = cmdNext;
    if (cmdNext.message) {
      this.serial.write(cmdNext.message + '\n', (err) =>  {
        if (err) {
          if (cmdNext.callback) cmdNext.callback(err,null);
        }
      });
    }
  }

};

module.exports = SerialDevice;


