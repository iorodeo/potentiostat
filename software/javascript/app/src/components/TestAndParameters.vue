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
              v-model="testParamVals[currentTest][paramName]"
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
             v-model="testParamVals[currentTest][paramName]"
             v-bind:key="optionStr.id"
             v-bind:md-value="optionKey" 
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

import {paramValsToNumber} from '../test_converters.js'

export default {
  name: 'TestAndParameters',
  props: ['selectedTest', 'testDefs', 'testVals', 'testErrs'],
  data () {
    return {
      currentTest:   this.selectedTest,
      testParamVals: this.testVals,
      testParamDefs: this.testDefs,
      testParamErrs: this.testErrs,
      showDebugButton: true,
    }
  },
  methods: {
    onDebugClick() {
      console.log('onDebugClick');
      console.log('------------');
      let testVals = paramValsToNumber(this.testVals,this.testDefs);
      let testName = this.currentTest;
      let convfunc = this.testDefs[testName].defs['converter'];
      let origVals = testVals[testName];
      let convVals = convfunc(origVals,this.testDefs[testName].defs);
      console.log(JSON.stringify(origVals));
      console.log(JSON.stringify(convVals));
    },
    onTestChange(testName) {
      this.currentTest = testName;
      this.$emit('test-change', testName);
    },
    onNumberChange(paramName, newValue) {
      this.checkParamForErrs(this.currentTest,paramName,newValue);
      this.$emit('param-change', this.testParamVals);
    },
    checkParamForErrs(testName, paramName, value) {
      let valueNum = Number(value);
      let defs = this.testParamDefs[testName].defs[paramName];
      let flag = false;
      let message = '';
      if (valueNum === "") { 
        flag = true;
        message =  'value must be a valid number'; 
      }
      else if (valueNum > defs.maxVal) {
        flag = true;
        message = 'value is > than maximum allowed, ' + defs.maxVal;
      }
      else if (valueNum < defs.minVal) {
        flag = true;
        message = 'value is < than minimum allowed, ' + defs.minVal;
      }
      this.testParamErrs[testName][paramName].flag = flag;
      this.testParamErrs[testName][paramName].message = message;
      if (flag) {
        this.$emit('param-errs-change', this.testParamErrs);
      }
      return flag;
    },
    checkAllParamForErrs() {
      for (let testName in this.testParamVals) {
        for (let paramName in this.testParamVals[testName]) {
          let paramValue = this.testParamVals[testName][paramName];
          this.checkParamForErrs(testName,paramName,paramValue);
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
