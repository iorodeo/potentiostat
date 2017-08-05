<template>

  <div class="DeviceConnection">

    <md-layout md-column>

      <md-layout md-row md-align="left" class="row-with-margin">
        <h3 class="md-title"> Device Connection </h3>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-input-container class="fixed-width-container">
          <label> serialport-bridge host address</label>
          <md-input v-model="serialBridgeAddress"></md-input>
        </md-input-container>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-switch 
          class="md-primary" 
          v-on:change="onBridgeConnectChange"
          > 
          connect to serialport-bridge
        </md-switch> 
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-input-container class="fixed-width-container">
          <label> serial port </label>
          <md-select 
            v-bind:disabled="!isConnected"
            v-model="serialPortName"
            >
            <md-option value="/dev/ttyACM0"> /dev/ttyACM0 </md-option>
            <md-option value="/dev/ttyACM1"> /dev/ttyACM1 </md-option>
            <md-option value="/dev/ttyACM2"> /dev/ttyACM2 </md-option>
            <md-option value="/dev/ttyUSB0"> /dev/ttyUSB0 </md-option>
            <md-option value="/dev/ttyUSB1"> /dev/ttyUSB1 </md-option>
          </md-select>
        </md-input-container>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-switch 
          class="md-primary" 
          v-bind:disabled="!isConnected"
          v-on:change="onSerialPortOpenChange"
          > 
          open serial port
        </md-switch> 
      </md-layout>

    </md-layout>

  </div>

</template>

<script>



export default {
  name: 'DeviceConnection',
  props: {
    isConnected: {
      type: Boolean,
      default: false,
    },
  },
  data () {
    return {
      serialBridgeAddress: 'http://localhost:5000',
      serialPortName: null,
    }
  },
  methods: {
    onBridgeConnectChange(value) {
      if (value) { 
        this.$emit('bridge-connect',this.serialBridgeAddress);
      } else {
        this.$emit('bridge-disconnect');
      }
    },
    onSerialPortOpenChange(value) {
      console.log('serial port open change: ' + value);
    },
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
