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
          v-bind:value="serialPortOpen"
          v-bind:disabled="serialPortSwitchDisabled"
          v-on:change="onSerialPortOpenChange"
          > 
          open serial port
        </md-switch> 
      </md-layout>

      <md-layout md-row md-align="left" class="row-with-margin" v-if="showDeviceInfo">
        <md-table>
          <md-table-header>
            <md-table-row>
              <md-table-head> Device Information </md-table-head>
              <md-table-head> </md-table-head>
            </md-table-row>
          </md-table-header>
          <md-table-body>
            <md-table-row>
              <md-table-cell> Firmware Version </md-table-cell>
              <md-table-cell> {{deviceFirmwareVersion}} </md-table-cell>
            </md-table-row>
            <md-table-row>
              <md-table-cell> Hardware Variant </md-table-cell>
              <md-table-cell> {{deviceHardwareVariant}} </md-table-cell>
            </md-table-row>
          </md-table-body>
        </md-table>
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
      showDebugButton: false,
    }
  },

  computed: {

    serialPortSelectDisabled() {
      return ((!this.serialBridgeConnected) || this.serialPortOpen);
    },

    serialPortSwitchDisabled() {
      return ((!this.serialBridgeConnected) || (!this.serialPortName));
    },

    showDeviceInfo() {
      return this.deviceFirmwareVersion && this.deviceHardwareVariant;
    },
    ...mapState([ 
      'serialBridgeAddress',
      'serialBridgeConnected',
      'serialBridge',
      'serialPortArray',
      'serialPortName',
      'serialPortOpen',
      'serialPortParam',
      'deviceFirmwareVersion',
      'deviceHardwareVariant',
    ]),
  },

  methods: {
    onDebugClick() {
      console.log('onDebugClick');
      console.log('------------');
    },
    onSerialBridgeAddressChange(value) {
      this.$store.commit('setSerialBridgeAddress', value);
    },
    onSerialBridgeConnectChange(value) {
      if (value) {
        this.connectSerialBridge();
      } else {
        this.disconnectSerialBridge();
      }
    },
    onSerialPortOpenChange(value) {
      if (value) {
        this.openSerialPort();
      } else {
        this.closeSerialPort();
      }
    },
    onPortSelectChange(value) {
      this.$store.commit('setSerialPortName', value);
    },

    connectSerialBridge() {
      this.$store.commit('setSerialPortName', null);
      this.$store.commit('setSerialPortArray', []);

      this.$store.commit(
        'setSerialBridge', 
        new SerialBridge(this.serialBridgeAddress)
      );
      this.serialBridge.connect();

      this.serialBridge.on('connect', () => {
        this.$store.commit('setSerialBridgeConnected', true);
        this.serialBridge.listPorts();
      });

      this.serialBridge.on('disconnect', () => {
        this.$store.commit('setSerialBridgeConnected',false);
        this.$store.commit('setSerialPortName', null);
        this.$store.commit('setSerialPortArray', []);
        this.$store.commit('setSerialPortOpen', false);
        this.$store.commit('setDeviceFirmwareVersion', null);
        this.$store.commit('setDeviceHardwareVariant', null);
      });

      this.serialBridge.on('listPortsRsp', (rsp) => {
        if (rsp.success) {
          this.$store.commit('setSerialPortArray', rsp.ports);
        }
      });

      this.serialBridge.on('openRsp', (rsp) => {
        if (rsp.success) {
          this.$store.commit('setSerialPortOpen', true);
          this.$store.commit('setSerialPortName', rsp.serialPortInfo.portName);
          let command = JSON.stringify({command: 'getVersion'});
          this.serialBridge.writeReadLine('getVersion',command)
        }
      });

      this.serialBridge.on('closeRsp', (rsp) => {
        this.$store.commit('setSerialPortOpen', false);
        this.$store.commit('setDeviceFirmwareVersion', null);
        this.$store.commit('setDeviceHardwareVariant', null);
      });

      this.serialBridge.on('readLineRsp', (rsp) => { 

        // If rsp.success then this just indicates a successful write to the
        // serial port, but it is not yet the response to our a command. 
        if (rsp.success) { 
          console.log(JSON.stringify(rsp));
          return; 
        } 

        // If rsp.tag then this is a response to a command sent to the serial
        // device.  Handle the response based on the tag in the rsp.
        switch (rsp.tag) { 
          case 'getVersion': 
            this.onSerialPortGetVersionRsp(rsp.line);
            break; 

          case 'getVariant':
            this.onSerialPortGetVariantRsp(rsp.line);
            break;

          default:
            console.log('unknown tag: ' + rsp.tag); 
        }
      });
      
    },

    onSerialPortGetVersionRsp(rspJson) {
      console.log('onSerialPortGetVersionRsp');
      console.log(rspJson);
      let rspObj = JSON.parse(rspJson);
      if (rspObj.success) {
        this.$store.commit('setDeviceFirmwareVersion', rspObj.response.version);
      } else {
        this.$store.commit('setDeviceFirmwareVersion', null);
      }
      let command = JSON.stringify({command: 'getVariant'});
      this.serialBridge.writeReadLine('getVariant', command); 
    },

    onSerialPortGetVariantRsp(rspJson) {
      console.log('onSerialPortGetVariantRsp');
      console.log(rspJson);
      let rspObj = JSON.parse(rspJson);
      if (rspObj.success) {
        this.$store.commit('setDeviceHardwareVariant', rspObj.response.variant);
      }
      else {
        this.$store.commit('setDeviceHardwareVariant', null);
      }
    },
    

    disconnectSerialBridge() {
      this.serialBridge.disconnect();
    },

    openSerialPort() {
      if (this.serialPortName) {
        this.serialBridge.open(this.serialPortName, this.serialPortParam);
      }
    },

    closeSerialPort() {
      this.serialBridge.close();
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
