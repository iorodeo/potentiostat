import Vue from 'vue'
import VueMaterial from 'vue-material'
import App from './App'

Vue.use(VueMaterial)

Vue.config.productionTip = false

/* eslint-disable no-new */
new Vue({
  el: '#app',
  render: h => h(App),
})
