<template>

  <div class="CollectData" style="width:100%;">

    <md-layout md-column>

      <md-layout md-row md-align="left" class="row-with-margin">
        <h3 class="md-title"> Data Collection </h3>
      </md-layout>


      <md-layout md-row md-align="left" class="row-with-margin" style="margin-bottom:20px;">
        <h3 style="margin-right:10px;"> Graphs:  </h3> 
        <md-checkbox class="md-primary" v-show="includeVoltVsTime" v-model="showVoltVsTime"> potential vs time </md-checkbox>
        <md-checkbox class="md-primary" v-show="includeCurrVsTime" v-model="showCurrVsTime"> current vs time </md-checkbox>
        <md-checkbox class="md-primary" v-show="includeCurrVsVolt" v-model="showCurrVsVolt"> current vs potential </md-checkbox>
      </md-layout>

      <md-layout md-row class="row-with-margin"> 
        <md-button class="md-primary md-raised" style="width:110px;" v-on:click="onRunClick" > 
          Run Test
        </md-button>
        <md-button class="md-primary md-raised" style="width:110px;" v-on:click="onDebugClick" v-if="showDebugButton"> 
          Debug
        </md-button>
        <md-button  class="md-primary md-raised" style="width:110px;" v-bind:disabled="!saveDataReady" v-on:click="onSaveDataClick"> 
          Save Data
        </md-button>
      </md-layout>

      <md-dialog-prompt 
        v-model="dataFileName"
        md-title="Filename"
        md-ok-text="Save"
        md-cancel-text="Cancel"
        md-input-placeholder="data.txt"
        ref="saveDataDialog"
        v-on:open="onSaveDataDialogOpen"
        v-on:close="onSaveDataDialogClose"
        >
      </md-dialog-prompt>


      <md-layout md-row v-show="testRunning" style="margin-left:50px;margin-top:20px;">
        <md-progress  style="width:90%;" v-bind:md-progress="progressValue"> </md-progress>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin" v-show="includeVoltVsTime && showVoltVsTime">
        <div ref="volt_vs_time_plot" > </div> 
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin" v-show="includeCurrVsTime && showCurrVsTime">
        <div ref="curr_vs_time_plot"> </div> 
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin" v-show="includeCurrVsVolt && showCurrVsVolt">
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
import {applyValueConverters} from '../test_converters';
import {saveAs} from 'file-saver';

export default {

  name: 'CollectData',

  data () {
    return {
      showDebugButton: false,
      progressValue: 0,
      plotVoltVsTime: null,
      testRunning: false,
      showVoltVsTime: true,
      showCurrVsTime: true,
      showCurrVsVolt: true,
      dataFileName: 'testdata.txt',
      voltVsTimeLayout: { 
        xaxis: { 
          title: 'time (sec)', 
          zeroline: true, 
        }, 
        yaxis: { 
          title: 'potential (V)', 
          zeroline: true,
        },
        width: 1200,
        height: 500,
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
        width: 1200,
        height: 500,
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
        width: 1200,
        height: 500,
      },
    }
  },

  computed: {

    isReady() {
      return this.serialBridgeConnected && this.serialPortOpen;
    },

    includeVoltVsTime() {
      return this.currentTestParamDefs.plotTypes.includes('voltVsTime');
    },

    includeCurrVsTime() {
      return this.currentTestParamDefs.plotTypes.includes('currVsTime');
    },
    
    includeCurrVsVolt() {
      return this.currentTestParamDefs.plotTypes.includes('currVsVolt');
    },

    saveDataReady() {
      return  (this.dataLength > 0) && !this.testRunning;
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

    onDebugClick() {
      console.log(' ');
      console.log('onDebugClick');
      console.log('currentTest = ' + this.currentTest);
      //console.log(JSON.stringify(this.currentTestParamVals));
      //console.log(JSON.stringify(this.currentTestParamDefs));
      //console.log();
      //for (let item in this.currentTestParamDefs)
      //{
      //  console.log(item);
      //}
      console.log('saveDataReady = ' + this.saveDataReady);
    },

    onSaveDataClick() {
      console.log('onSaveDataClick');
      this.$refs.saveDataDialog.open();
    },

    onSaveDataDialogOpen() {
      console.log('onSaveDataDialogOpen');
    },

    onSaveDataDialogClose(type) {
      console.log('onSaveDataDialogClose');
      console.log('type = ' + type);
      if (type === 'ok')
      {
        console.log('savedata')
        let dataArray = [];
        for (let i=0; i<this.dataLength; i++)
        {
          // TO DO save precision somewhere
          let dataLine = ''; 
          dataLine += this.data.time[i].toPrecision(4) + ', '; 
          dataLine += this.data.volt[i].toPrecision(4) + ', '; 
          dataLine += this.data.curr[i].toPrecision(4);
          dataArray.push(dataLine);
        }
        dataArray = [dataArray.join('\n') + '\n'];
        let blob = new Blob(dataArray, {type: "text/plain;charset=utf-8"});
        saveAs(blob, this.dataFileName, true);
      }
    },


    onRunClick() {
      //console.log('onRunClick');
      //console.log('currentTest = ' + this.currentTest);
      //console.log(JSON.stringify(this.currentTestParamVals))

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
      this.testRunning = true;
    },

    updateProgressBar() { 
      this.progressValue = this.runProgress;
      //console.log(this.runProgress);
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

      this.testRunning = false;
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
