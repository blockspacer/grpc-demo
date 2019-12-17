<template>
  <el-form label-position="left" label-width="80px" :model="formLabelAlign">
    <el-form-item label="账号">
      <el-input></el-input>
    </el-form-item>
    <el-form-item label="密码">
      <el-input type="password"></el-input>
    </el-form-item>
    <el-form-item>
      <el-button type="primary">提交</el-button>
    </el-form-item>
  </el-form>
</template>
<script>
  export default {
    props: {
      sessionId: {
        type: String
      }
    }
  }
</script>
