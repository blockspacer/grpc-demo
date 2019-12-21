<template>
  <div id="app">
    <el-form :inline="true" class="demo-form-inline">
      <el-form-item label="用户名">
        <el-input placeholder="用户名" v-model="register.user"></el-input>
      </el-form-item>
      <el-form-item label="密码">
        <el-input type="password" placeholder="密码" v-model="register.password"></el-input>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="registerUser">注册</el-button>
      </el-form-item>
    </el-form>
    <el-tabs v-model="activeTab">
      <el-tab-pane v-for="idx in tabCount" :label="'tab'+idx" :name="'tab'+idx" v-bind:key="idx"><Login :session-id="'tab'+idx"></Login></el-tab-pane>
    </el-tabs>
  </div>
</template>

<script>
  import Login from './components/login.vue';
  import Api from './apis';
  import {mapState} from 'vuex';
  import Cache from './widgets/cache';
  import Actions from './store/actions';

  export default {
    components: {
      Login
    },
    data() {
      return {
        activeTab: 'tab1',
        tabCount: 8,
        register: {
          user: '',
          password: ''
        }
      }
    },
    computed: mapState(['uid', 'token']),
    async created() {
      // 从cookie拿session信息
      let session = Cache.getCookie('session');
      try {
        session = JSON.parse(session);
      } catch(e) {
        session = {
          uid: '',
          token: ''
        };
      }
      if (session.uid && session.token) {
        await this.$store.dispatch(Actions.SET_LOGIN_INFO, {
          uid: session.uid,
          token: session.token
        });
      }
      const ret = await Api.CheckLogin(session.uid.toString(), session.token).catch(() => {
        this.$message.error('服务器连接失败，请确认服务是否正常');
        return {
          retCode: -1
        };
      });
      if (ret.retCode === 0) {
        this.activeTab = ret.channel;
        await this.$store.dispatch(Actions.SET_CHANNEL, {
          channel: ret.channel
        });
      } else {
        this.activeTab = 'tab1';
      }
    },
    methods: {
      async registerUser() {
        if (!this.register.user || !this.register.password) {
          this.$message.warning('请输入正确的用户名和密码');
          return ;
        }
        const ret = await Api.Register(this.register.user, this.register.password).catch(() => {
          this.$message.error('服务器连接失败，请确认服务是否正常');
          return {
            retCode: -1
          };
        });
        if (ret.retCode === 0) {
          this.$message.success('注册成功，请登录');
          this.register.user = '';
          this.register.password = '';
        } else if (ret.retCode === 2) {
          this.$message.warning('用户名已存在，请重新输入新用户名');
          this.register.user = '';
          this.register.password = '';
        } else {
          this.$message.error('注册失败，请稍后重试');
        }
      }
    }
  }
</script>
