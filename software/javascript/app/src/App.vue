<template>

  <div id="app">
    <md-layout md-column>
      <app-toolbar v-on:option-change="onOptionChange"> </app-toolbar>
      <md-layout md-row>

      <device-connection 
        v-bind:is-connected="serialBridgeConnected"
        v-bind:serial-port-array="serialPortArray"
        v-bind:is-serial-port-open="serialPortOpen"
        v-bind:serial-port="serialPortName"
        v-on:bridge-connect-request="connectSerialBridgeReq"
        v-on:bridge-disconnect-request="disconnectSerialBridgeReq"
        v-on:serialport-open-request="openSerialPortReq"
        v-on:serialport-close-request="closeSerialPortReq"
        v-on:serialport-change="onSerialPortChange"
        v-show="currentOption === 'DeviceConnection'"
        > 
      </device-connection>

      <test-and-parameters 
        v-show="currentOption === 'TestAndParameters'" 
        v-bind:selected-test="currentTest"
        v-bind:test-defs="testParamDefs"
        v-bind:test-vals="testParamVals"
        v-bind:test-errs="testParamErrs"
        v-on:test-change="onTestChange" 
        v-on:param-change="onParamChange"
        > 
      </test-and-parameters>

      <collect-data 
        v-show="currentOption === 'CollectData'"
        > 
      </collect-data>

      <!--
      <export-data 
        v-show="currentOption === 'ExportData'"
        > 
      </export-data>
      -->

      </md-layout>
    </md-layout>
  </div>

</template>


<script>

import AppToolbar from './components/AppToolbar';
import DeviceConnection from './components/DeviceConnection';
import TestAndParameters from './components/TestAndParameters';
import CollectData from './components/CollectData';
import ExportData from './components/ExportData';
import {TEST_DEFS} from './test_definitions';
import {SerialBridge} from './serial_bridge';
import {initParamValsFromDefs, initParamErrsFromDefs} from './test_utils.js';

export default {
  name: 'app',
  components: {
    AppToolbar,
    DeviceConnection,
    TestAndParameters,
    CollectData,
    ExportData,
  },
  data: function() {
    return {
      currentOption: 'TestAndParameters',
      currentTest: 'linearSweep',
      testParamDefs: TEST_DEFS,
      testParamVals: initParamValsFromDefs(TEST_DEFS),
      testParamErrs: initParamErrsFromDefs(TEST_DEFS),
      serialBridge: null,
      serialBridgeConnected: false,
      serialPortArray: [],
      serialPortName: null,
      serialPortOpen: false,
      serialPortParam: {
        baudrate: 115200,
        timeout: 10.0,
      },
      enableUnloadDialog: false,
    }
  },
  methods: { 

    onOptionChange(newOptionName) {
      this.currentOption = newOptionName;
    },

    onTestChange(newTestName) {
      this.currentTest = newTestName;
    },

    onParamChange(newTestParamVals) {
      this.testParamVals = newTestParamVals;
    },

    onParamErrsChange(newTestParamErrs) {
      this.testParamErrs = newTestParamErrs;
    },

    connectSerialBridgeReq(address) {
      console.log('on serialport-bridge connect');
      console.log(address)

      this.serialBridge = new SerialBridge(address);
      this.serialBridge.connect();

      this.serialBridge.on('connect', () => {
        this.serialBridgeConnected = true;
        this.serialBridge.listPorts();
      });

      this.serialBridge.on('disconnect', () => {
        this.serialBridgeConnected = false;
        this.serialPortName = null;
        this.serialPortArray = [];
      });

      this.serialBridge.on('listPortsRsp', (rsp) => {
        console.log('listPortsRsp: ' + JSON.stringify(rsp));
        if (rsp.success) {
          this.serialPortArray = rsp.ports;
        }
      });

      this.serialBridge.on('openRsp', (rsp) => {
        console.log('openRsp: ' + JSON.stringify(rsp));
        if (rsp.success) {
          this.serialPortOpen = true;
          this.serialPortName = rsp.serialPortInfo.portName;
          console.log('serialPortOpen: ' + this.serialPortOpen);
          console.log('serialPortName: ' + this.serialPortName);
        }
      });

      this.serialBridge.on('closeRsp', (rsp) => {
        this.serialPortOpen = false;
      });

    },

    disconnectSerialBridgeReq() {
      console.log('on serialport-bridge disconnect');
      this.serialBridge.disconnect();
    },

    openSerialPortReq() {
      console.log('openSerialPortReq');
      if (this.serialPortName) {
        this.serialBridge.open(this.serialPortName,this.serialPortParam);
      }
    },

    closeSerialPortReq() {
      console.log('closeSerialPortReq');
      this.serialBridge.close();
    },

    onSerialPortChange(newName) {
      console.log('onSerialPortChange');
      this.serialPortName = newName;
    },

    beforeunload() {
      if (this.enableUnloadDialog) {
        return 'Warning: reloading page may cause data loss in the Rodeostat application';
      } 
    }
  },

  created() {
    window.onbeforeunload = this.beforeunload
  },

};

</script>

<style src="vue-material/dist/vue-material.css">  </style>
