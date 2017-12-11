"use strict";
import _ from 'lodash';


// Converters for parameter values
// -----------------------------------------------------------------------------

export function identity(value) {
  return value;
}


export function secondToMillisecond(value) {
  return 1000.0*value;
}


export function applyValueConverters(paramVals, paramDefs) {
  let paramValsCon = {};
  for (name in paramVals) {
    paramValsCon[name] = paramDefs[name].converter(paramVals[name]);
  }
  return paramValsCon;
}


export function paramValsToNumber(paramVals, paramDefs) {
  let paramValsCon = {};
  for (let testName in paramVals) {
    paramValsCon[testName] = {};
    for (let paramName in paramVals[testName]) {
      let val = paramVals[testName][paramName];
      if (paramDefs[testName].defs[paramName].type === 'number') {
        val = Number(paramVals[testName][paramName]);
      } 
      paramValsCon[testName][paramName] = val;
    }
  }
  return paramValsCon;
}


// Converters for Tests
// ----------------------------------------------------------------------------


export function constantParam(paramVals, paramDefs) {
  return applyValueConverters(paramVals, paramDefs);
}


export function chronoampParam(paramVals, paramDefs) {
  let paramValsTmp = applyValueConverters(paramVals, paramDefs);
  let valsToOmit= ['step1Duration', 'step2Duration', 'step1Value', 'step2Value'];
  let paramValsCon = _.omit(paramValsTmp,valsToOmit);
  paramValsCon['step'] = [
    [paramValsTmp.step1Duration, paramValsTmp.step1Value],
    [paramValsTmp.step2Duration, paramValsTmp.step2Value],
  ]
  return paramValsCon;
}


export function cyclicParam(paramVals, paramDefs) {
  let paramValsTmp = applyValueConverters(paramVals, paramDefs);
  let valsToOmit = ['scanRate', 'minValue', 'maxValue', 'startOption'];
  let paramValsCon = _.omit(paramValsTmp, valsToOmit);
  paramValsCon.amplitude = 0.5*Math.abs(paramValsTmp.maxValue - paramValsTmp.minValue);
  paramValsCon.offset = 0.5*(paramValsTmp.maxValue + paramValsTmp.minValue); 
  paramValsCon.period = secondToMillisecond(4*paramValsCon.amplitude/paramValsTmp.scanRate).toFixed(0);
  if (paramValsTmp.startOption === 'startMin') {
    paramValsCon.shift = 0.0;
  } else {
    paramValsCon.shift = 0.5;
  }
  return paramValsCon;
}

export function linearSweepParam(paramVals, paramDefs) {
  let paramValsTmp = applyValueConverters(paramVals, paramDefs);
  let paramValsCon = _.omit(paramValsTmp,['scanRate']);
  let deltaVolt = Math.abs(paramValsTmp.startValue - paramValsTmp.finalValue);
  paramValsCon.duration = Number(secondToMillisecond(deltaVolt/paramValsTmp.scanRate).toFixed(0));
  return paramValsCon;
}

export function multiStepParam(paramVals, paramDefs) {
  let paramValsTmp = applyValueConverters(paramVals, paramDefs);
  let paramValsCon = _.omit(paramValsTmp,['numSteps']);
  // --------------------------------------------------
  // TODO 
  // ---------------------------------------------------
  return paramValsCon;
}

export function sinusoidParam(paramVals, paramDefs) {
  let paramValsCon = applyValueConverters(paramVals, paramDefs);
  return paramValsCon;
}
