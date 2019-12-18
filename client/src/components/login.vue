<template>
  <el-form label-position="left" label-width="80px">
    <el-form-item label="账号">
      <el-input></el-input>
    </el-form-item>
    <el-form-item label="密码">
      <el-input type="password"></el-input>
    </el-form-item>
    <el-form-item>
      <el-button type="primary" @click="login">提交</el-button>
    </el-form-item>
  </el-form>
</template>
<script>
  import Api from '../apis';

  export default {
    props: {
      sessionId: {
        type: String
      }
    },
    data() {
      return {
        user: '',
        password: ''
      };
    },
    methods: {
      async login() {
        const ret = await Api.checkLogin();
        console.log(ret);
      }
    }
  }
</script>
