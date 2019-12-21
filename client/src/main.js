import Vue from 'vue';
import App from './App.vue';
import Store from './store';
import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';

Vue.use(ElementUI);
Vue.config.productionTip = false;

new Vue({
  render: h => h(App),
  store: Store
}).$mount('#app');
