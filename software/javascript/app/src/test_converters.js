"use strict";

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
  let paramValsCon = Object.assign({}, paramValsTmp);
  delete paramValsCon.duration1;
  delete paramValsCon.duration2;
  delete paramValsCon.value1;
  delete paramValsCon.value2;
  paramValsCon['step'] = [
    [paramValsTmp.step1Duration, paramValsTmp.step1Value],
    [paramValsTmp.step2Duration, paramValsTmp.step2Value],
  ]
  return paramValsCon;
}


export function cyclicParam(paramVals, paramDefs) {
  let paramValsTmp = applyValueConverters(paramVals, paramDefs);
  let paramValsCon = Object.assign({}, paramValsTmp);
  delete paramValsCon.scanRate;
  delete paramValsCon.minValue;
  delete paramValsCon.maxValue;
  delete paramValsCon.startOption;
  paramValsCon.amplitude = 0.5*Math.abs(paramValsTmp.maxValue - paramValsTmp.minValue);
  paramValsCon.offset = 0.5*(paramValsTmp.maxValue + paramValsTmp.minValue); 
  paramValsCon.period = (1000*4*paramValsCon.amplitude/paramValsTmp.scanRate).toFixed(0);
  if (paramValsTmp.startOption === 'startMin') {
    paramValsCon.shift = 0.0;
  } else {
    paramValsCon.shift = 0.5;
  }
  return paramValsCon;
}

export function linearSweepParam(paramVals, paramDefs) {
}

export function multiStepParam(paramVals, paramDefs) {
}

export function sinusoidParam(paramsVals, paramsDefs) {

}
