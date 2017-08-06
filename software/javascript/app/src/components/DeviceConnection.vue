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
            v-on:change="onPortSelectChange"
            >
            <md-option 
              v-for="item in serialPortArray"
              v-bind:key="item.id"
              v-bind:value="item.device"
              > 
              {{item.device}}
            </md-option>
          </md-select>
        </md-input-container>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-switch 
          class="md-primary" 
          v-bind:disabled="serialPortOpenSwitchDisabled"
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
    serialPortArray: {
      type: Array,
      default: function() {
        return [];
      },
    },
    isSerialPortOpen: {
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
        this.$emit('bridge-connect-request',this.serialBridgeAddress);
      } else {
        this.$emit('bridge-disconnect-request');
        this.$emit('serialport-change', null);
        this.serialPortName = null;
      }
    },
    onSerialPortOpenChange(value) {
      console.log('serial port open change: ' + value);
      console.log(this.serialPortName);
      if (value) {
        this.$emit('serialport-open-request');
      } else {
        this.$emit('serialport-close-request');
      }
    },
    onPortSelectChange(value) {
      console.log(value);
      this.$emit('serialport-change',value);
    },
  },

  computed: {
    serialPortOpenSwitchDisabled() {
      return ((!this.isConnected) || (!this.serialPortName));
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
