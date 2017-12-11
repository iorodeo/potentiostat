<template>

  <div class="CollectData">

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
      console.log('------------');
      console.log('currentTest: ' + this.currentTest);

      console.log('original -------------');
      for (let name in this.currentTestParamVals) {
        console.log(name + ': ' + this.currentTestParamVals[name]);
      }

      let testParamValsConv = this.currentTestParamDefs.converter(this.currentTestParamVals,this.currentTestParamDefs);

      console.log('converted ------------');
      for (let name in this.convertedTestParamVals) {
        console.log(name + ': ' + this.convertedTestParamVals[name]);
      }

      this.$store.commit('clearData');

      let command = JSON.stringify({
        command: 'setCurrRange', 
        currRange: this.convertedTestParamVals.currRange
      });
      this.serialBridge.writeReadLine('setCurrRange',command);
      this.$store.commit('startPlotTimer', () => {
        console.log('hello');
      });
      
    },

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
