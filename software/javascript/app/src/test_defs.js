"use strict";
import * as converters from './test_converters.js'


// Generic parameter info objects
const SAMPLE_RATE_PARAM_DEF = { 
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

const QUIET_TIME_PARAM_DEF = {
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

const VOLT_VALUE_PARAM_DEF = {
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
const QUIET_VALUE_PARAM_DEF = Object.assign(
  {},
  VOLT_VALUE_PARAM_DEF,
  {name:'quiet value'}
)

const TIME_VALUE_PARAM_DEF = {
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

const SCAN_RATE_PARAM_DEF = {
  name: 'scan rate',
  unit: 'V/s',
  type: 'number',
  minVal: 0.0,
  maxVal: 50.000,
  defVal: 0.01,
  step: 0.01,
  scale: 1.0,
  converter: converters.identity,
};

// Parameters defs for constant voltage test
const CONSTANT_TEST_DEFS = {
  sampleRate: SAMPLE_RATE_PARAM_DEF, 
  quietTime:  QUIET_TIME_PARAM_DEF,
  quietValue: QUIET_VALUE_PARAM_DEF,
  value: VOLT_VALUE_PARAM_DEF, 
  duration: Object.assign({},TIME_VALUE_PARAM_DEF,{name:'duration'}),
  converter: converters.constantParam,
};

// Parameter defs for chronoamp test
const CHRONOAMP_TEST_DEFS = {
  sampleRate: SAMPLE_RATE_PARAM_DEF, 
  quietTime:  QUIET_TIME_PARAM_DEF,
  quietValue: QUIET_VALUE_PARAM_DEF,
  step1Duration: Object.assign({},TIME_VALUE_PARAM_DEF,{name:'step 1 duration'}),
  step1Value: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'step 1 value'}),
  step2Duration: Object.assign({},TIME_VALUE_PARAM_DEF,{name:'step 2 duration'}),
  step2Value: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'step 2 value'}),
  converter: converters.chronoampParam,
};

// Parameter defs for cyclic voltammetry test
const CYCLIC_TEST_DEFS = {
  sampleRate: SAMPLE_RATE_PARAM_DEF, 
  quietTime:  QUIET_TIME_PARAM_DEF,
  quietValue: QUIET_VALUE_PARAM_DEF,
  minValue: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'min value'}),
  maxValue: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'max value'}),
  scanRate: SCAN_RATE_PARAM_DEF,
};

// Parameter defs for linear sweep test
const LINEARSWEEP_TEST_DEFS = {
  sampleRate: SAMPLE_RATE_PARAM_DEF, 
  quietTime:  QUIET_TIME_PARAM_DEF,
  quietValue: QUIET_VALUE_PARAM_DEF,
  startValue: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'start value'}),
  finalValue: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'final value'}),
  scanRate: SCAN_RATE_PARAM_DEF,
};

// Parameter defs for multistep test
const MULTISTEP_TEST_DEFS = {
  sampleRate: SAMPLE_RATE_PARAM_DEF, 
  quietTime:  QUIET_TIME_PARAM_DEF,
  quietValue: QUIET_VALUE_PARAM_DEF,
};

// Parameter defs for sinudoid test
const SINUSOID_TEST_DEFS = {
  sampleRate: SAMPLE_RATE_PARAM_DEF, 
  quietTime:  QUIET_TIME_PARAM_DEF,
  quietValue: QUIET_VALUE_PARAM_DEF,
};

// Collection of all test definitions
export const TEST_DEFS = {
  constant: {
    name: 'constant voltage',
    defs: CONSTANT_TEST_DEFS, 
  },
  chronoamp: {
    name: 'chronoamperometry', 
    defs: CHRONOAMP_TEST_DEFS,
  },
  cyclic: {
    name: 'cyclic',
    defs: CYCLIC_TEST_DEFS,
  },
  linearSweep: {
    name: 'linear sweep',
    defs: LINEARSWEEP_TEST_DEFS,
  },
  multiStep: {
    name: 'multistep',
    defs: MULTISTEP_TEST_DEFS,
  },
  sinusoid: { 
    name: 'sinusoid',
    defs: MULTISTEP_TEST_DEFS,
  },
};

