<template>

  <div class="TestAndParameters">

    <md-layout md-column>

      <md-layout md-row md-align="left" class="row-with-margin">
        <h3 class="md-title"> Test & Parameters </h3>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-input-container class="fixed-width-container">
          <label> voltammetric test </label>
          <md-select v-model="currentTest" v-bind:placeholder="currentTest" @change="onTestChange">
            <md-option 
              v-for="(value,key) in testParamDefs" 
              v-bind:value="key" 
              v-bind:key="value.id" 
              >  
              {{value.dispName}}  
            </md-option>
          </md-select>
        </md-input-container>
      </md-layout>

      <md-layout md-row 
        v-for="(paramInfo,paramName) in testParamDefs[currentTest].paramInfo"
        v-bind:key="paramInfo.id"
        class="row-with-margin"
        md-align="left" 
        >
        <div v-if="paramInfo.type ==='number'">
          <md-input-container 
             v-bind:class="{'fixed-width-container':true, 'md-input-invalid':testParamErrs[currentTest][paramName].flag}" 
            >
            <label> {{paramInfo.name}} ({{paramInfo.unit}})  </label>
            <md-input 
              type="number" 
              v-model="testParamVals[currentTest][paramName]"
              v-bind:step="testParamDefs[currentTest].paramInfo[paramName].step"
              v-bind:max="testParamDefs[currentTest].paramInfo[paramName].maxVal"
              v-bind:min="testParamDefs[currentTest].paramInfo[paramName].minVal"
              @change="onNumberChange(paramName, $event)"
              >
            </md-input> 
            <span class="md-error">
              {{testParamErrs[currentTest][paramName].message}}
            </span>
          </md-input-container>
          <md-tooltip md-direction="right"> 
            min = {{paramInfo.minVal}}, max = {{paramInfo.maxVal}}
          </md-tooltip>
        </div>
      </md-layout>

      <md-layout md-row class="row-with-margin">
        <md-button 
          class="md-primary md-raised" 
          @click=onDebugClick
          > 
          Debug 
        </md-button>
      </md-layout>

    </md-layout>

  </div>

</template>

<script>

import { TEST_DEFS } from './test_defs'


export default {
  name: 'TestAndParameters',
  props: ['selectedTest'],
  data () {
    return {
      currentTest: this.selectedTest,
      testParamDefs: TEST_DEFS,
      testParamVals: this.initParamValsFromDefs(TEST_DEFS),
      testParamErrs: this.initParamErrsFromDefs(TEST_DEFS),
    }
  },
  methods: {
    onDebugClick() {
      console.log('onDebugClick');
      //this.testParamVals[this.currentTest]['quietTime'] = 20;
    },
    onTestChange(testName) {
      this.currentTest = testName
      this.$emit('test-change', testName)
    },
    onNumberChange(paramName, newValue) {
      console.log('onNumberChange ' + newValue);
      let paramInfo = this.testParamDefs[this.currentTest].paramInfo[paramName];
      let flag = false;
      let message = '';
      if (!newValue) { 
        flag = true;
        message =  'value must be a valid number'; 
      }
      else if (newValue > paramInfo.maxVal) {
        flag = true;
        message = 'value is > than maximum allowed, ' + paramInfo.maxVal;
      }
      else if (newValue < paramInfo.minVal) {
        flag = true;
        message = 'value is < than minimum allowed, ' + paramInfo.minVal;
      }
      this.testParamErrs[this.currentTest][paramName].flag = flag;
      this.testParamErrs[this.currentTest][paramName].message = message;
    },
    initParamValsFromDefs(testParamDefs) {
      let testParamVals = {}
      for (let name in testParamDefs) {
        testParamVals[name] = {}
        for (let param in testParamDefs[name].paramInfo) {
          testParamVals[name][param] = testParamDefs[name].paramInfo[param].defVal 
        }
      }
      return testParamVals
    },
    initParamErrsFromDefs(testParamDefs) {
      let testParamErrs = {}
      for (let name in testParamDefs) {
        testParamErrs[name] = {}
        for (let param in testParamDefs[name].paramInfo) {
          testParamErrs[name][param] = {flag: false, message: 'none'} 
        }
      }
      
      return testParamErrs;
    }
  },
  mounted() {
    //for (let name in this.testParamVals) {
    //  for (let test in this.testParamVals[name]) {
    //    console.log(name + ' ' + test + ' ' + this.testParamVals[name][test])
    //  }
    //}
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
