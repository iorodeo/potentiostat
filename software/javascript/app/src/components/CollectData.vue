<template>

  <div class="CollectData" style="width:100%;">

    <md-layout md-column>

      <md-layout md-row md-align="left" class="row-with-margin">
        <h3 class="md-title"> Data Acquisition </h3>
      </md-layout>


      <md-layout md-row class="row-with-margin">
        <md-layout md-col>
        <div style="width:90%;height:30px;">
          <md-progress v-bind:md-progress="progressValue"> </md-progress>
        </div>
        </md-layout>
      </md-layout>

      <md-layout md-row class="row-with-margin"> 
        <md-button class="md-primary md-raised" v-on:click=onRunClick > 
          Run Test
        </md-button>
      </md-layout>


      <md-layout md-row class="row-with-margin">
        <md-button 
          class="md-primary md-raised" 
          v-on:click=onDebugClick
          v-if="showDebugButton"
          > 
          Debug
        </md-button>
      </md-layout>

      <md-layout md-row md-align="center">
        <div ref="volt_vs_time_plot" > </div> 
      </md-layout>

      <md-layout md-row md-align="center">
        <div ref="curr_vs_time_plot"> </div> 
      </md-layout>

      <md-layout md-row md-align="center">
        <div ref="volt_vs_curr_plot" > </div> 
      </md-layout>

      <!--
      <md-layout md-row md-align="center">
        <div ref="volt_vs_time_plot" style="width:95%;height;margin-top:50px;margin-bottom:50px;" > </div> 
      </md-layout>

      <md-layout md-row md-align="center">
        <div ref="curr_vs_time_plot" style="width:95%;height;margin-top:50px;margin-bottom:50px;" > </div> 
      </md-layout>

      <md-layout md-row md-align="center">
        <div ref="volt_vs_curr_plot" style="width:95%;height;margin-top:50px;margin-bottom:50px;" > </div> 
      </md-layout>
      -->

    </md-layout>

  </div>

</template>

<script>

import {mapState} from 'vuex';
import {mapGetters} from 'vuex';
import {applyValueConverters} from '../test_converters'
//import Dygraph from 'dygraphs';

export default {

  name: 'CollectData',

  data () {
    return {
      progressValue: 0,
      showDebugButton: false,
      plotVoltVsTime: null,
      voltVsTimeLayout: { 
        xaxis: { 
          title: 'time (sec)', 
          zeroline: true, 
        }, 
        yaxis: { 
          title: 'potential (V)', 
          zeroline: true,
        },
      },
      currVsTimeLayout: { 
        xaxis: { 
          title: 'time (sec)', 
          zeroline: true, 
        }, 
        yaxis: { 
          title: 'current (uA)', 
          zeroline: true,
        },
      },
      currVsVoltLayout: { 
        xaxis: { 
          title: 'potential (V)', 
          zeroline: true, 
        }, 
        yaxis: { 
          title: 'current (uA)', 
          zeroline: true,
        },
      },
    }
  },

  computed: {

    isReady() {
      return this.serialBridgeConnected && this.serialPortOpen;
    },
    ...mapState([ 
      'currentTest', 
      'testParamDefs',
      'testParamVals',
      'testParamErrs',
      'serialBridgeConnected',
      'serialBridge',
      'serialPortOpen', 
      'data',
    ]),
    ...mapGetters([
      'currentTestParamVals',
      'currentTestParamDefs',
      'convertedTestParamVals',
      'dataLength',
      'runProgress',
    ]),
  },

  methods: {

    onRunClick() {
      console.log('onRunClick');
      console.log('currentTest = ' + this.currentTest);
      console.log(JSON.stringify(this.currentTestParamVals))

      this.progressValue = 0;
      this.clearPlots();

      this.$store.commit('clearData');

      let command = JSON.stringify({
        command: 'setCurrRange', 
        currRange: this.convertedTestParamVals.currRange
      });
      this.serialBridge.writeReadLine('setCurrRange',command);
      this.$store.commit('setTestDoneCallback', this.testDoneCallback);
      this.$store.commit('startProgressTimer', this.updateProgressBar); 
    },

    onDebugClick() {
      console.log(' ');
      console.log('onDebugClick');
      
    },

    updateProgressBar() { 
      this.progressValue = this.runProgress;
      console.log(this.runProgress);
    },

    testDoneCallback() {
      this.updateProgressBar();

      let voltVsTimeData = {
        x: this.data.time,
        y: this.data.volt,
        mode: 'lines',
        visible: true,
      };

      Plotly.plot(this.$refs.volt_vs_time_plot, [voltVsTimeData], this.voltVsTimeLayout);

      let currVsTimeData = {
        x: this.data.time, 
        y: this.data.curr, 
        mode: 'lines', 
        visible: true,
      };

      Plotly.plot(this.$refs.curr_vs_time_plot, [currVsTimeData], this.currVsTimeLayout);

      let currVsVoltData = {
        x: this.data.volt, 
        y: this.data.curr, 
        mode: 'lines', 
        visible: true,
      };

      Plotly.plot(this.$refs.volt_vs_curr_plot, [currVsVoltData], this.currVsVoltLayout);
    },

    clearPlots() {
      Plotly.deleteTraces(this.$refs.volt_vs_time_plot,0); 
      Plotly.deleteTraces(this.$refs.curr_vs_time_plot,0); 
      Plotly.deleteTraces(this.$refs.volt_vs_curr_plot,0); 
    },
            
  }, 

  mounted() { 

    let data = {
      x: [ 0 ,1],
      y: [-1, 1],
      mode: 'lines',
      visible: false,
    }

    Plotly.plot(this.$refs.volt_vs_time_plot, [data], this.voltVsTimeLayout);
    Plotly.plot(this.$refs.curr_vs_time_plot, [data], this.currVsTimeLayout);
    Plotly.plot(this.$refs.volt_vs_curr_plot, [data], this.currVsVoltLayout);

  },

}

</script>

<style scoped>
.row-with-margin {
  margin-left: 40px;
}
.fixed-width-container {
  width: 250px;
}
</style> 
