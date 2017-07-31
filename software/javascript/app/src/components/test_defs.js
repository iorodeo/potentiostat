"use strict";
import * as converters from './converters.js'


// Generic parameter info objects
const SAMPLE_RATE_PARAM_INFO = { 
  name: 'sample rate',
  unit: 'Hz',
  type: 'number',
  minVal: 10.0,
  maxVal: 100.0,
  defVal: 100.0,
  step:  10.0,
  scale: 1.0,
  converter: converters.identity,
} 

const QUIET_TIME_PARAM_INFO = {
  name: 'quiet time',
  unit: 's',
  type: 'number',
  minVal: 0.0,
  maxVal: 60*60*1,
  defVal: 0.0,
  step:  1.0, 
  scale: 1000.0,
  converter: converters.secondToMillisecond,
}

const VOLT_VALUE_PARAM_INFO = {
  name: 'value',
  unit: 'V',
  type: 'number',
  minVal: -10.0,
  maxVal: 10.0,
  defVal: 0.0,
  step:  0.1,
  scale: 1.0,
  converter: converters.identity,
}
const QUIET_VALUE_PARAM_INFO = Object.assign(
  {},
  VOLT_VALUE_PARAM_INFO,
  {name:'quiet value'}
)

const TIME_VALUE_PARAM_INFO = {
  name: 'time',
  unit: 's',
  type: 'number',
  minVal: 0.0,
  maxVal: 60*60*24*2,
  defVal: 10.0,
  step: 1,
  scale: 1000,
  converter: converters.secondToMillisecond,
}

const SCAN_RATE_PARAM_INFO = {
  name: 'scan rate',
  unit: 'V/s',
  type: 'number',
  minVal: 0.0,
  maxVal: 10.0,
  defVal: 0.05,
  step: 0.01,
  scale: 1.0,
  converter: converters.identity,
};

// Parameters defs for constant voltage test
const CONSTANT_PARAM_INFO = {
  sampleRate: SAMPLE_RATE_PARAM_INFO, 
  quietTime:  QUIET_TIME_PARAM_INFO,
  quietValue: QUIET_VALUE_PARAM_INFO,
  value: VOLT_VALUE_PARAM_INFO, 
  duration: Object.assign({},TIME_VALUE_PARAM_INFO,{name:'duration'}),
  converter: converters.constantParam,
};

// Parameter defs for chronoamp test
const CHRONOAMP_PARAM_INFO = {
  sampleRate: SAMPLE_RATE_PARAM_INFO, 
  quietTime:  QUIET_TIME_PARAM_INFO,
  quietValue: QUIET_VALUE_PARAM_INFO,
  step1Duration: Object.assign({},TIME_VALUE_PARAM_INFO,{name:'step 1 duration'}),
  step1Value: Object.assign({},VOLT_VALUE_PARAM_INFO,{name:'step 1 value'}),
  step2Duration: Object.assign({},TIME_VALUE_PARAM_INFO,{name:'step 2 duration'}),
  step2Value: Object.assign({},VOLT_VALUE_PARAM_INFO,{name:'step 2 value'}),
  converter: converters.chronoampParam,
};

// Parameter defs for cyclic voltammetry test
const CYCLIC_PARAM_INFO = {
  sampleRate: SAMPLE_RATE_PARAM_INFO, 
  quietTime:  QUIET_TIME_PARAM_INFO,
  quietValue: QUIET_VALUE_PARAM_INFO,
  maxValue: Object.assign({},VOLT_VALUE_PARAM_INFO,{name:'max value'}),
  minValue: Object.assign({},VOLT_VALUE_PARAM_INFO,{name:'min value'}),
  scanRate: SCAN_RATE_PARAM_INFO,
};

// Parameter defs for linear sweep test
const LINEARSWEEP_PARAM_INFO = {
  sampleRate: SAMPLE_RATE_PARAM_INFO, 
  quietTime:  QUIET_TIME_PARAM_INFO,
  quietValue: QUIET_VALUE_PARAM_INFO,
  startValue: Object.assign({},VOLT_VALUE_PARAM_INFO,{name:'start value'}),
  finalValue: Object.assign({},VOLT_VALUE_PARAM_INFO,{name:'final value'}),
  scanRate: SCAN_RATE_PARAM_INFO,
};

// Parameter defs for multistep test
const MULTISTEP_PARAM_INFO = {
  sampleRate: SAMPLE_RATE_PARAM_INFO, 
  quietTime:  QUIET_TIME_PARAM_INFO,
  quietValue: QUIET_VALUE_PARAM_INFO,
};

// Parameter defs for sinudoid test
const SINUSOID_PARAM_INFO = {
  sampleRate: SAMPLE_RATE_PARAM_INFO, 
  quietTime:  QUIET_TIME_PARAM_INFO,
  quietValue: QUIET_VALUE_PARAM_INFO,
};

// Collection of all test definitions
export const TEST_DEFS = {
  constant: {
    dispName: 'constant voltage',
    paramInfo: CONSTANT_PARAM_INFO, 
  },
  chronoamp: {
    dispName: 'chronoamperometry', 
    paramInfo: CHRONOAMP_PARAM_INFO,
  },
  cyclic: {
    dispName: 'cyclic',
    paramInfo: CYCLIC_PARAM_INFO,
  },
  linearSweep: {
    dispName: 'linear sweep',
    paramInfo: LINEARSWEEP_PARAM_INFO,
  },
  multiStep: {
    dispName: 'multistep',
    paramInfo: MULTISTEP_PARAM_INFO,
  },
  sinusoid: { 
    dispName: 'sinusoid',
    paramInfo: MULTISTEP_PARAM_INFO,
  },
};

