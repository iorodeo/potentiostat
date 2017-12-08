<template>

  <div class="TestAndParameters">

    <md-layout md-column>

      <md-layout md-row md-align="left" class="row-with-margin">
        <h3 class="md-title"> Test & Parameters </h3>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-input-container class="fixed-width-container">
          <label> voltammetric test </label>
          <md-select v-bind:placeholder="currentTest" @change="onTestChange">
            <md-option 
              v-for="(value,key) in testParamDefs" 
              v-bind:value="key" 
              v-bind:key="value.id" 
              >  
              {{value.name}}  
            </md-option>
          </md-select>
        </md-input-container>
      </md-layout>

      <md-layout md-row 
        v-for="(paramDef,paramName) in testParamDefs[currentTest].defs"
        v-bind:key="paramDef.id"
        class="row-with-margin"
        md-align="left" 
        >
        <div v-if="paramDef.type ==='number'">
          <md-input-container 
             v-bind:class="{'fixed-width-container':true, 'md-input-invalid':testParamErrs[currentTest][paramName].flag}" 
            >
            <label> {{paramDef.name}} ({{paramDef.unit}})  </label>
            <md-input 
              type="number" 
              v-bind:value="testParamVals[currentTest][paramName]"
              v-bind:step="testParamDefs[currentTest].defs[paramName].step"
              v-bind:max="testParamDefs[currentTest].defs[paramName].maxVal"
              v-bind:min="testParamDefs[currentTest].defs[paramName].minVal"
              @change="onNumberChange(paramName, $event)"
              >
            </md-input> 
            <span class="md-error">
              {{testParamErrs[currentTest][paramName].message}}
            </span>
          </md-input-container>
          <md-tooltip md-direction="right"> 
            min = {{paramDef.minVal}}, max = {{paramDef.maxVal}}
          </md-tooltip>
        </div>

        <div v-if="paramDef.type === 'radio'">  
          <md-radio 
             v-for="(optionStr,optionKey) in testParamDefs[currentTest].defs[paramName].options"
             v-bind:value="testParamVals[currentTest][paramName]"
             v-bind:key="optionStr.id"
             v-bind:md-value="optionKey" 
             @change="onRadioChange(paramName,$event)"
             class="md-primary"
             >
             {{optionStr}}
          </md-radio>
        </div>

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
import {paramValsToNumber} from '../test_converters.js';
import  _ from 'lodash';

export default {

  name: 'TestAndParameters',

  data () {
    return {
      showDebugButton: true,
    }
  },

  computed: mapState([ 
    'currentTest', 
    'testParamDefs',
    'testParamVals',
    'testParamErrs',
  ]),

  methods: {

    onDebugClick() {
      console.log('onDebugClick');
      console.log('------------');
      let testParamVals = paramValsToNumber(this.$store.state.testParamVals,this.$store.state.testParamDefs);
      let testName = this.currentTest;
      let convfunc = this.$store.state.testParamDefs[testName].defs['converter'];
      let origVals = testParamVals[testName];
      let convVals = convfunc(origVals,this.$store.state.testParamDefs[testName].defs);
      console.log(JSON.stringify(origVals));
      console.log(JSON.stringify(convVals));
    },

    onTestChange(testName) {
      this.$store.commit('setCurrentTest', testName);
    },


    onNumberChange(paramName, newValue) {
      this.checkNumberForErrs(this.currentTest,paramName,newValue);
      this.$store.commit('setTestParamValsByTest', {
        test: this.currentTest,
        name: paramName,
        value: Number(newValue),
      });
    },

    onRadioChange(paramName, newValue) {
      this.$store.commit('setTestParamValsByTest', {
        test: this.currentTest,
        name: paramName,
        value: newValue,
      });
    },

    checkNumberForErrs(testName, paramName, value) {
      let valueNum = Number(value);
      let defs = this.testParamDefs[testName].defs[paramName];
      let boundType = _.get(defs, ['boundType'], ['closed','closed']);
      let flag = false;
      let message = '';
      if (valueNum === "") { 
        flag = true;
        message =  'value must be a valid number'; 
      } else {
        let maxType = boundType[1];
        let minType = boundType[0];
        if (maxType === 'closed') {
          if (valueNum > defs.maxVal) {
            flag = true;
            message = 'value is > than maximum allowed, ' + defs.maxVal;
          }
        } else {
          if (valueNum >= defs.maxVal) {
            flag = true;
            message = 'value is >= than maximum allowed, ' + defs.maxVal;
          }
        }
        if (minType === 'closed') {
          if (valueNum < defs.minVal) {
            flag = true;
            message = 'value is < than minimum allowed, ' + defs.minVal;
          }
        } else {
          if (valueNum <= defs.minVal) {
            flag = true;
            message = 'value is <= than minimum allowed, ' + defs.minVal;
          }
        }
      }

      this.$store.commit('setTestParamErrsByTest', {
        test: testName,
        name: paramName,
        flag: flag,
        message: message,
      });
      return flag;
    },

    checkAllParamForErrs() {
      for (let testName in this.testParamVals) {
        for (let paramName in this.testParamVals[testName]) {
          let paramValue = this.testParamVals[testName][paramName];
          let paramType = this.testParamDefs[testName].defs[paramName].type;
          if (paramType  === 'number') {
            this.checkNumberForErrs(testName,paramName,paramValue);
          }
        }
      }
    },
    
  },

  mounted() {
    this.checkAllParamForErrs();
  }
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
