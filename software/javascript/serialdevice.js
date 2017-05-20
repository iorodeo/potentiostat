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

    let device = this;

    this.serial.on('data', function(data) {
      if (!device.cmdCurrent) {
        return;
      }
      let moreDataFlag = device.cmdCurrent.callback(null,data)
      if (moreDataFlag) {
        device.cmdQueue.unshift({
          message: null, 
          callback: device.cmdCurrent.callback
        });
      } 
      device.processQueue();
    });

    this.serial.on('open', openCallback);
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
          cmdNext.callback(err,null);
          }
      });
    }
  }

};

module.exports = SerialDevice;


