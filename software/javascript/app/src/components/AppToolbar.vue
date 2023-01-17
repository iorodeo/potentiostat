<template>

  <div class="AppToolbar">

    <md-toolbar>
      <md-button class="md-icon-button" @click="toggleSideNav">
        <md-icon>menu</md-icon>
      </md-button>
      <h1 class="md-title" style="flex: 1"> Rodeostat Web App V1.1.0</h1> 
      <!-- <md-button> IO Rodeo </md-button> --> 
      <h1 class="md-subheading" style="width:70px"> IO Rodeo </h1> 
    </md-toolbar>

    <md-sidenav class="md-left" ref="sideNav" @open="sideNavOpen" @close="sideNavClose">
      <md-toolbar class="md-small">
        <div class="md-toolbar-container">
          <h3 class="md-title"> Select Option </h3>
        </div>
      </md-toolbar>
      <div>
        <md-list>
          <md-list-item>
            <md-button @click="onSideNavOptionClick('DeviceConnection')"> Device Connection </md-button>
          </md-list-item>
          <md-list-item>
            <md-button @click="onSideNavOptionClick('TestAndParameters')"> Test & Parameters </md-button>
          </md-list-item>
          <md-list-item>
            <md-button @click="onSideNavOptionClick('CollectData')"> Data Acquisition </md-button>
          </md-list-item>
          <!-- 
          <md-list-item>
            <md-button @click="onSideNavOptionClick('ExportData')"> Export Data </md-button>
          </md-list-item>
          -->
        </md-list>
      </div>
    </md-sidenav>

  </div>

</template>

<script>
export default {
  name: 'AppToolbar',
  data () {
    return {
      dummy: "dummy"
    }
  },
  methods: {
    toggleSideNav() {
      this.$refs.sideNav.toggle()
    }, 
    sideNavOpen() {
    },
    sideNavClose() {
    },
    onSideNavOptionClick(optionName) {
      this.$refs.sideNav.toggle()
      this.$store.commit('setCurrentOption', optionName);
    },
  }
}
</script>
