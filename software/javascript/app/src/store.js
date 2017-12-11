import Vue from 'vue'
import Vuex from 'vuex'
import {TEST_DEFS} from './test_definitions';
import {initParamValsFromDefs, initParamErrsFromDefs} from './test_utils';

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
    data: {
      raw: { 
        time: [],
        volt: [],
        curr: [],
      },
      plot: {
        timeAndVolt: [],
        timeAndCurr: [],
        voltAndCurr: [],
      },
    }
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

    appendData(state, payload) {
      state.data.raw.time.push(payload.t);
      state.data.raw.volt.push(payload.v);
      state.data.raw.curr.push(payload.i);
      state.data.plot.timeAndVolt.push([payload.t, payload.v]);
      state.data.plot.timeAndCurr.push([payload.t, payload.i]);
      state.data.plot.voltAndCurr.push([payload.v, payload.i]);
    },

    clearData(state) {
      state.data.raw.time = [];
      state.data.raw.volt = [];
      state.data.raw.curr = [];
      state.data.plot.timeAndVolt = [];
      state.data.plot.timeAndCurr = [];
      state.data.plot.voltAndCurr = [];
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
    }

  }
})
