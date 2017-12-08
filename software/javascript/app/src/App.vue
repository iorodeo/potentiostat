<template>

  <div id="app">
    <md-layout md-column>

      <app-toolbar> </app-toolbar>

        <md-layout md-row>

          <device-connection v-show="currentOption === 'DeviceConnection'"> 
          </device-connection>

          <test-and-parameters v-show="currentOption === 'TestAndParameters'">
          </test-and-parameters>

          <collect-data v-show="currentOption === 'CollectData'"> 
          </collect-data>

          <!--
          <export-data v-show="currentOption === 'ExportData'" > 
          </export-data>
          -->

        </md-layout>

    </md-layout>

  </div>

</template>


<script>

import {mapState} from 'vuex';
import AppToolbar from './components/AppToolbar';
import DeviceConnection from './components/DeviceConnection';
import TestAndParameters from './components/TestAndParameters';
import CollectData from './components/CollectData';
import ExportData from './components/ExportData';

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
      enableUnloadDialog: false,
    }
  },

  computed: mapState([
    'currentTest',
    'currentOption' 
  ]),

  methods: { 

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
