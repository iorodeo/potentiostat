import Vue from 'vue'
import Vuex from 'vuex'
import {TEST_DEFS} from './test_definitions';
import {initParamValsFromDefs, initParamErrsFromDefs} from './test_utils';
import _ from 'lodash';

Vue.use(Vuex)

export const store = new Vuex.Store({

  state: { 
    currentOption: 'DeviceConnection',
    currentTest: 'linearSweep',
    testParamDefs: TEST_DEFS,
    testParamVals: initParamValsFromDefs(TEST_DEFS), 
    testParamErrs: initParamErrsFromDefs(TEST_DEFS),
    serialBridgeAddress: 'http://localhost:5000',
    serialBridgeConnected: false,
    serialBridge: null,
    serialPortArray: [],
    serialPortName: null,
    serialPortOpen: false,
    serialPortParam: {
      baudrate: 115200,
      timeout: 10.0,
    },
    deviceFirmwareVersion: null,
    deviceHardwareVariant: null,
    testRunning: false,
    progressTimer: null,
    progressTimerInterval: 100, 
    testDoneTime: null,
    testDoneCallback: null,
    data: { 
      time: [], 
      volt: [], 
      curr: [],
    },
  },

  mutations: {

    setCurrentOption(state, option) {
      state.currentOption = option;
    },

    setCurrentTest(state, test) {
      state.currentTest = test;
    },

    setTestParamVals(state, newVals) {
      state.testParamVals = newVals;
    },

    setTestParamValsByTest(state, payload) {
      state.testParamVals[payload.test][payload.name] = payload.value;
    },

    setTestParamErrs(state, newErrs) {
      state.testParamErrs = newErrs;
    },

    setTestParamErrsByTest(state, payload) {
      state.testParamErrs[payload.test][payload.name].flag = payload.flag;
      state.testParamErrs[payload.test][payload.name].message = payload.message;
    },

    setSerialBridgeAddress(state,address) {
      state.serialBridgeAddress = address;
    },

    setSerialBridge(state, serialBridge) {
      state.serialBridge = serialBridge;
    },

    setSerialBridgeConnected(state, connected) {
      state.serialBridgeConnected = connected;
    },

    setSerialPortArray(state, portArray) {
      state.serialPortArray = portArray;
    },

    setSerialPortName(state, newName) {
      state.serialPortName = newName;
    },

    setSerialPortOpen(state, portOpen) {
      state.serialPortOpen = portOpen;
    },

    setDeviceFirmwareVersion(state,value) {
      state.deviceFirmwareVersion = value;
    },

    setDeviceHardwareVariant(state, value) {
      state.deviceHardwareVariant = value;
    },

    setTestRunning(state,value) {
      state.testRunning = value;
    },

    startProgressTimer(state, callback) { 
      state.progressTimer = setInterval(callback, state.progressTimerInterval);
    },

    clearProgressTimer(state) {
      clearInterval(state.progressTimer);
      state.progressTimer = null;
    },

    setTestDoneTime(state, value) {
      state.testDoneTime = value;
    },

    setTestDoneCallback(state, cb) {
      state.testDoneCallback = cb;
    }, 

    appendData(state, payload) {
      state.data.time.push(payload.t);
      state.data.volt.push(payload.v);
      state.data.curr.push(payload.i);
    },

    clearData(state) {
      state.data.time = [];
      state.data.volt = [];
      state.data.curr = [];
    },

  },

  getters: {

    testParamDefsByTest: (state, getters) => (test,name) => {
      if (name === undefined) {
        return state.testParamDefs[test]['defs'];
      } else {
        return state.testParamDefs[test]['defs'][name];
      }
    },

    testParamValsByTest: (state, getters) => (test,name) => {
      if (name === undefined) {
        return state.testParamVals[test];
      } else {
        return state.testParamVals[test][name];
      }
    },

    testDisplayName: (state, getters) => (test) => {
      return getters.testParamDefsByTest(test).name;
    },

    currentTestDisplayName: (state,getters) => {
      return testDisplayName(state.currentTest);
    },

    currentTestParamDefs: (state, getters) =>  {
      return getters.testParamDefsByTest(state.currentTest);
    },

    currentTestParamVals: (state, getters) => {
      return getters.testParamValsByTest(state.currentTest);
    },

    convertedTestParamVals: (state,getters) => {
      let currVals = getters.currentTestParamVals;
      let currDefs = getters.currentTestParamDefs;
      let convertedVals =  currDefs.converter(currVals,currDefs); 
      return convertedVals;
    },

    testParamErrsByTest: (state, getters) => (test,name) => {
      if (name === undefined) {
        return state.testParamErrs[test];
      } else {
        return state.testParamErrs[test][name];
      }
    },

    testNameArray: (state, getters) => () => {
      return Object.keys(state.testParamVals);
    },

    paramNameArray: (state, getters) => (test) => {
      return Object.keys(state.testParamVals[test]);
    },

    dataLength: (state, getters) => {
      let len = 0;
      if (state.data.time !== undefined) {
        len = state.data.time.length;
      }
      return len;
    },

    runProgress: (state, getters) => {
      let value = 0;
      if (getters.dataLength  !== 0) {
        if (state.testDoneTime !== null) {
          let t = state.data.time[getters.dataLength-1];
          value = t/state.testDoneTime; 
          value = _.clamp(value,0,1);
          value = 100*value;
        }
      } 
      return value;
    },

  }
})
