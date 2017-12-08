<template>

  <div class="DeviceConnection">

    <md-layout md-column>

      <md-layout md-row md-align="left" class="row-with-margin">
        <h3 class="md-title"> Device Connection </h3>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-input-container class="fixed-width-container">
          <label> serialport-bridge host address</label>
          <md-input 
            v-bind:value="serialBridgeAddress" 
            v-on:change="onSerialBridgeAddressChange" 
            >
          </md-input>
        </md-input-container>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-switch 
          class="md-primary" 
          v-on:change="onSerialBridgeConnectChange"
          > 
          connect to serialport-bridge
        </md-switch> 
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-input-container class="fixed-width-container">
          <label> serial port </label>
          <md-select 
            v-bind:disabled="serialPortSelectDisabled"
            v-bind:value="serialPortName"
            v-on:change="onPortSelectChange"
            >
            <md-option 
              v-for="item in serialPortArray"
              v-bind:key="item.id"
              v-bind:value="item.device"
              > 
              {{item.device}} ({{item.product}})
            </md-option>
          </md-select>
        </md-input-container>
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin">
        <md-switch 
          class="md-primary" 
          v-bind:value="serialPortSwitch"
          v-bind:disabled="serialPortSwitchDisabled"
          v-on:change="onSerialPortOpenChange"
          > 
          open serial port
        </md-switch> 
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

import {mapState} from 'vuex';
import {SerialBridge} from '../serial_bridge';

export default {

  name: 'DeviceConnection',

  data () {
    return {
      showDebugButton: true,
    }
  },

  computed: {

    serialPortSelectDisabled() {
      return ((!this.$store.state.serialBridgeConnected) || this.$store.state.serialPortOpen);
    },

    serialPortSwitchDisabled() {
      return ((!this.$store.state.serialBridgeConnected) || (!this.$store.state.serialPortName));
    },
    ...mapState([ 
      'serialBridgeAddress',
      'serialBridgeConnected',
      'serialBridge',
      'serialPortArray',
      'serialPortName',
      'serialPortOpen',
      'serialPortParam',
    ]),
  },

  methods: {
    onDebugClick() {
      console.log('debug');
      console.log(JSON.stringify(this.$store.state.serialPortArray));
    },
    onSerialBridgeAddressChange(value) {
      console.log('onSerialBridgeAddressChange: ' + value);
      this.$store.commit('setSerialBridgeAddress', value);
    },
    onSerialBridgeConnectChange(value) {
      console.log('onSerialBridgeConnectChange: ' + value);
      if (value) {
        this.connectSerialBridge();
      } else {
        this.disconnectSerialBridge();
      }
    },
    onSerialPortOpenChange(value) {
      console.log('serialPortOpenChange: ' + value);
      if (value) {
        this.openSerialPort();
      } else {
        this.closeSerialPort();
      }
    },
    onPortSelectChange(value) {
      console.log('onPortSelectChange: ' + value);
      this.$store.commit('setSerialPortName', value);
    },

    connectSerialBridge() {
      console.log('connectSerialBridge');
      this.$store.commit('setSerialPortName', null);
      this.$store.commit('setSerialPortArray', []);

      this.$store.commit(
        'setSerialBridge', 
        new SerialBridge(this.$store.state.serialBridgeAddress)
      );
      this.$store.state.serialBridge.connect();

      this.$store.state.serialBridge.on('connect', () => {
        this.$store.commit('setSerialBridgeConnected', true);
        this.$store.state.serialBridge.listPorts();
      });

      this.$store.state.serialBridge.on('disconnect', () => {
        console.log('serialBridge.on.disconnect')
        this.$store.commit('setSerialBridgeConnected',false);
        this.$store.commit('setSerialPortName', null);
        this.$store.commit('setSerialPortArray', []);
      });

      this.$store.state.serialBridge.on('listPortsRsp', (rsp) => {
        console.log('listPortsRsp: ' + JSON.stringify(rsp));
        if (rsp.success) {
          console.log('storing serialPortArray');
          this.$store.commit('setSerialPortArray', rsp.ports);
        }
      });

      this.$store.state.serialBridge.on('openRsp', (rsp) => {
        console.log('openRsp: ' + JSON.stringify(rsp));
        if (rsp.success) {
          this.$store.commit('setSerialPortOpen', true);
          this.$store.commit('setSerialPortName', rsp.serialPortInfo.portName);
          console.log('serialPortOpen: ' + this.$store.state.serialPortOpen);
          console.log('serialPortName: ' + this.$store.state.serialPortName);
        }
      });

      this.$store.state.serialBridge.on('closeRsp', (rsp) => {
        this.$store.commit('setSerialPortOpen', false);
      });
    },

    disconnectSerialBridge() {
      console.log('disconnectSerialBridge');
      this.$store.state.serialBridge.disconnect();
    },

    openSerialPort() {
      console.log('openSerialPort');
      if (this.serialPortName) {
        this.$store.state.serialBridge.open(
          this.$store.state.serialPortName,
          this.$store.state.serialPortParam
        );
      }
    },

    closeSerialPort() {
      console.log('closeSerialPort');
      this.$store.state.serialBridge.close();
    },

  },
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
