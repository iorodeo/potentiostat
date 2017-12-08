import Vue from 'vue'
import Vuex from 'vuex'
import VueMaterial from 'vue-material'

import App from './App'
import {store} from './store';

Vue.use(VueMaterial)
Vue.config.productionTip = false

/* eslint-disable no-new */
new Vue({
  el: '#app',
  store,
  render: h => h(App),
})
