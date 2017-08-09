"use strict";
import * as converters from './test_converters.js'


// Generic parameter info objects
const SAMPLE_RATE_PARAM_DEF = { 
  name: 'sample rate',
  unit: 'Hz',
  type: 'number',
  minVal: 10.0,
  maxVal: 100.0,
  defaultVal: 100.0,
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
  defaultVal: 0.0,
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
  defaultVal: 0.0,
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
  defaultVal: 10.0,
  step: 1,
  scale: 1000,
  converter: converters.secondToMillisecond,
}

const SCAN_RATE_PARAM_DEF = {
  name: 'scan rate',
  unit: 'V/s',
  type: 'number',
  minVal: 0.001,
  maxVal: 50.000,
  defaultVal: 0.01,
  step: 0.001,
  scale: 1.0,
  converter: converters.identity,
};

const SHIFT_PARAM_DEF = {
  name: 'shift',
  unit: '',
  type: 'number',
  minVal: 0.0,
  maxVal: 1.0,
  defaultVal: 0.0,
  step: 0.1,
  scale: 1.0,
  converter: converters.identity,
};

const NUM_CYCLES_PARAM_DEF = {
  name: 'cycles',
  unit: '#',
  type: 'number',
  minVal: 1,
  maxVal: 10000,
  defaultVal: 1,
  step: 1,
  scale: 1,
  converter: converters.identity,
};

const START_HILO_RADIO_PARAM_DEF = {
  type: 'radio',
  defaultVal: 'startMin',
  options: {
    startMin: 'start minimum',
    startMax: 'start maximum',
  },
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
  minValue: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'min value',defaultVal: -1.0}),
  maxValue: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'max value',defaultVal:  1.0}),
  scanRate: SCAN_RATE_PARAM_DEF,
  numCycles: NUM_CYCLES_PARAM_DEF,
  startOption: START_HILO_RADIO_PARAM_DEF,
  converter: converters.cyclicParam,
};

// Parameter defs for linear sweep test
const LINEARSWEEP_TEST_DEFS = {
  sampleRate: SAMPLE_RATE_PARAM_DEF, 
  quietTime:  QUIET_TIME_PARAM_DEF,
  quietValue: QUIET_VALUE_PARAM_DEF,
  startValue: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'start value',defaultVal: -1.0}),
  finalValue: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'final value',defaultVal:  1.0}),
  scanRate: SCAN_RATE_PARAM_DEF,
  converter: converters.linearSweepParam,
};

// Parameter defs for multistep test
const MULTISTEP_TEST_DEFS = {
  sampleRate: SAMPLE_RATE_PARAM_DEF, 
  quietTime:  QUIET_TIME_PARAM_DEF,
  quietValue: QUIET_VALUE_PARAM_DEF,
  converter: converters.multiStepParam,
};

// Parameter defs for sinudoid test
const SINUSOID_TEST_DEFS = {
  sampleRate: SAMPLE_RATE_PARAM_DEF, 
  quietTime:  QUIET_TIME_PARAM_DEF,
  quietValue: QUIET_VALUE_PARAM_DEF,
  amplitude: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'amplitude',minVal: 0.0, defaultVal: 1.0}),
  offset: Object.assign({},VOLT_VALUE_PARAM_DEF,{name:'offset'}),
  period: Object.assign({},TIME_VALUE_PARAM_DEF,{name:'period'}),
  numCycles: NUM_CYCLES_PARAM_DEF,
  shift: SHIFT_PARAM_DEF,
  converter: converters.sinusoidParam,
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
    defs: SINUSOID_TEST_DEFS,
  },
};

