<template>

  <div id="app">
    <md-layout md-column>
      <app-toolbar v-on:option-change="onOptionChange"> </app-toolbar>
      <md-layout md-row>

      <device-connection 
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

      <export-data 
        v-show="currentOption === 'ExportData'"
        > 
      </export-data>

      </md-layout>
    </md-layout>
  </div>

</template>


<script>

import AppToolbar from './components/AppToolbar'
import DeviceConnection from './components/DeviceConnection'
import TestAndParameters from './components/TestAndParameters'
import CollectData from './components/CollectData'
import ExportData from './components/ExportData'
import { TEST_DEFS } from './test_defs'

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
      currentTest: 'cyclic',
      testParamDefs: TEST_DEFS,
      testParamVals: this.initParamValsFromDefs(TEST_DEFS),
      testParamErrs: this.initParamErrsFromDefs(TEST_DEFS),
      enableUnloadDialog: false,
    }
  },
  methods: { 
    initParamValsFromDefs(testParamDefs) {
      let testParamVals = {};
      for (let name in testParamDefs) {
        testParamVals[name] = {};
        for (let param in testParamDefs[name].defs) {
          testParamVals[name][param] = testParamDefs[name].defs[param].defVal;
        }
      }
      return testParamVals;
    },
    initParamErrsFromDefs(testParamDefs) {
      let testParamErrs = {}
      for (let name in testParamDefs) {
        testParamErrs[name] = {}
        for (let param in testParamDefs[name].defs) {
          testParamErrs[name][param] = {flag: false, message: 'none'} 
        }
      }
      return testParamErrs;
    },
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
    beforeunload() {
      if (this.enableUnloadDialog) {
        return 'Warning: reloading page may cause data loss in the Rodeostat application';
      } 
    }
  },
  created() {
    window.onbeforeunload = this.beforeunload
  },
}

</script>

<style src="vue-material/dist/vue-material.css">  </style>
