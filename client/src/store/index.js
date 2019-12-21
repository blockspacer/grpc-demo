import Vue from 'vue';
import Vuex from 'vuex';
import Actions from './actions';

Vue.use(Vuex);
const store = new Vuex.Store({
  state: {
    uid: '',
    token: '',
    channel: ''
  },
  mutations: {
    [Actions.SET_LOGIN_INFO](state, payload) {
      state.uid = payload.uid;
      state.token = payload.token;
    },
    [Actions.SET_CHANNEL](state, payload) {
      state.channel = payload.channel;
    }
  },
  actions: {
    [Actions.SET_LOGIN_INFO]({commit}, payload) {
      commit(Actions.SET_LOGIN_INFO, payload);
    },
    [Actions.SET_CHANNEL]({commit}, payload) {
      commit(Actions.SET_CHANNEL, payload);
    }
  }
});
export default store;
