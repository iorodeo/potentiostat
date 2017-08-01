"use strict";

export function identity(value) {
  return value;
}

export function secondToMillisecond(value) {
  return 1000.0*value;
}

export function applyValueConverters(paramVals,paramDefs) {
  let paramValsCon = {};
  for (name in paramVals) {
    paramValsCon[name] = paramDefs[name].converter(paramVals[name]);
  }
  return paramValsCon;
}

export function constantParam(paramVals,paramDefs) {
  return applyValueConverters(paramVals,paramDefs);
}

export function chronoampParam(paramVals,paramDefs) {
  let paramValsTmp = applyValueConverters(paramVals,paramDefs);
  let paramValsCon = Object.assign({},paramValsTmp);
  delete paramValsCon.duration1;
  delete paramValsCon.duration2;
  delete paramValsCon.value1;
  delete paramValsCon.value2;
  paramValsCon['step'] = [
    [paramValsTmp.duration1,paramValsTmp.value1],
    [paramValsTmp.duration2,paramValsTmp.value2],
  ]
  return paramValsCon;
}


