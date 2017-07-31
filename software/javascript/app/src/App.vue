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
        v-on:test-change="onTestChange" 
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
      enableUnloadDialog: false,
    }
  },
  methods: { 
    onOptionChange(newOptionName) {
      this.currentOption = newOptionName
    },
    onTestChange(newTestName) {
      this.currentTest = newTestName
    },
    beforeunload() {
      if (this.enableUnloadDialog) {
        return 'Warning: reloading page may cause data loss in the Rodeostat application'
      } 
    }
  },
  created() {
    window.onbeforeunload = this.beforeunload
  },
}

</script>

<style src="vue-material/dist/vue-material.css">  </style>
