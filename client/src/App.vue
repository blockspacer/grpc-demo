<template>
  <div id="app">
    <el-button type="primary">注册</el-button>
    <el-tabs v-model="activeTab" @tab-click="changeTab">
      <el-tab-pane label="tab1" name="first"><Login session-id="0"></Login></el-tab-pane>
      <el-tab-pane label="tab2" name="second"><Login session-id="1"></Login></el-tab-pane>
    </el-tabs>
  </div>
</template>

<script>
  import Login from './components/login.vue';

  export default {
    components: {
      Login
    },
    data() {
      return {
        activeTab: 'first'
      }
    },
    methods: {
      changeTab() {

      }
    }
  }
</script>
