"use strict";
import _ from 'lodash';
import {NONVALUE_TEST_PARAMS} from './test_definitions.js';

export function initParamValsFromDefs(testParamDefs) {
  let testParamVals = {};
  for (let name in testParamDefs) {
    testParamVals[name] = {};
    for (let param in testParamDefs[name].defs) { 
      if (_.includes(NONVALUE_TEST_PARAMS,param)) {
        continue;
      }
      testParamVals[name][param] = testParamDefs[name].defs[param].defaultVal; 
    }
  }
  return testParamVals;
}

export function initParamErrsFromDefs(testParamDefs) {
  let testParamErrs = {}
  for (let name in testParamDefs) {
    testParamErrs[name] = {}
    for (let param in testParamDefs[name].defs) {
      if (_.includes(NONVALUE_TEST_PARAMS,param)) {
        continue;
      }
      testParamErrs[name][param] = {flag: false, message: 'none'} 
    }
  }
  return testParamErrs;
}
