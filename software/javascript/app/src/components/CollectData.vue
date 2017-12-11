<template>

  <div class="CollectData" style="width:100%;">

    <md-layout md-column>

      <md-layout md-row md-align="left" class="row-with-margin">
        <h3 class="md-title"> Data Acquisition </h3>
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
        <div ref="volt_vs_time_plot" style="width:95%;height;margin-top:50px;margin-bottom:50px;" > </div> 
      </md-layout>

    </md-layout>

  </div>

</template>

<script>

import {mapState} from 'vuex';
import {mapGetters} from 'vuex';
import {applyValueConverters} from '../test_converters'
import Dygraph from 'dygraphs';

export default {

  name: 'CollectData',

  data () {
    return {
      showDebugButton: true,
      plotVoltVsTime: null,
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
    ]),
  },

  methods: {

    onDebugClick() {
      console.log(' ');
      console.log('onDebugClick');
      console.log('currentTest: ' + this.currentTest);

      //console.log('original -------------');
      //for (let name in this.currentTestParamVals) {
      //  console.log(name + ': ' + this.currentTestParamVals[name]);
      //}
      //console.log('converted ------------');
      //for (let name in this.convertedTestParamVals) {
      //  console.log(name + ': ' + this.convertedTestParamVals[name]);
      //}

      // Run Test  
      // ------------------------------------------------------------------
      this.$store.commit('clearData');
      this.createPlot();

      let command = JSON.stringify({
        command: 'setCurrRange', 
        currRange: this.convertedTestParamVals.currRange
      });
      this.serialBridge.writeReadLine('setCurrRange',command);

      this.$store.commit('startPlotTimer', this.updatePlot); 
      // ------------------------------------------------------------------
      
    },

    updatePlot() { 
      let n = this.data.plot.timeAndVolt.length;
      console.log('t = ' + this.data.plot.timeAndVolt[n-1]); 
      console.log('len = ' + n);
      if (this.data.plot.timeAndVolt.length > 0) {
        this.graph.updateOptions({file: this.data.plot.timeAndVolt});
      }
    },

    createPlot() {
      let dummyPts = [[0.0, 0.0], [1.0, 0.0]];  
      this.graph = new Dygraph( this.$refs.volt_vs_time_plot, dummyPts, {
        labels: ['x', 'y'],
        xlabel: "time (s)",
        ylabel: "position (m)",
        dateWindow: this.getXLim(),
        axes : {
          x: {
            dateWindow: this.getXLim(),
            drawGrid: true,
            independentTicks: true,
          },
          y: {
            valueRange: this.getYLim(),
            drawGrid: true,
            independentTicks: true,
          },
        },
        strokeWidth: 1.75,
        height: 400,
        showLabelsOnHighlight: false,
        interactionModel: {},
        colors: ["rgb(255,0,0)"],
      });
    },

    getXLim() { 
      let xlim = [0, 1.0e-3*this.convertedTestParamVals.duration];
      console.log(xlim);
      return xlim;
    },

    getYLim() {
      let ylim = [-1000, 1000];
      switch (this.convertedTestParamVals.currRange) {
        case '1uA':
          ylim = [-1, 1.01];
          break;
        case '10uA':
          ylim = [-10, 10.1];
          break;
        case '100uA':
          ylim = [-100, 101];
          break;
        case '1000uA':
          ylim = [-1000, 1010];
          break;
      }
      return ylim;
    }
            
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
