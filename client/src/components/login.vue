<template>
  <div>
    <el-form label-position="left" label-width="80px" v-if="!isLoginTab">
      <el-form-item label="账号">
        <el-input type="text" v-model="user"></el-input>
      </el-form-item>
      <el-form-item label="密码">
        <el-input type="password" v-model="password"></el-input>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="login">提交</el-button>
      </el-form-item>
    </el-form>
    <div v-else>You have just logged in {{sessionId}}!</div>
  </div>
</template>
<script>
  import Api from '../apis';
  import Actions from '../store/actions';
  import Cache from '../widgets/cache';

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
    computed: {
      isLoginTab() {
        return this.sessionId === this.$store.state.channel;
      }
    },
    methods: {
      async login() {
        if (!this.user.length || !this.password) {
          this.$message.warning('请输入正确的用户名和密码');
          return ;
        }
        const ret = await Api.Login(this.user, this.password, this.sessionId).catch(() => {
          this.$message.error('服务器连接失败，请确认服务是否正常');
          return {
            retCode: -1
          };
        });
        console.log(ret);
        if (ret.retCode === 0) {
          await this.$store.dispatch(Actions.SET_LOGIN_INFO, {
            uid: ret.uid,
            token: ret.token
          });
          await this.$store.dispatch(Actions.SET_CHANNEL, {
            channel: this.sessionId
          });
          Cache.setCookie('session', {
            uid: ret.uid,
            token: ret.token
          });
          this.user = '';
          this.password = '';
        } else {
          this.$message.error('登录失败，用户名密码错误');
        }
      }
    }
  }
</script>
