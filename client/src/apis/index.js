import Request from '../libs/request';

export default {
  async checkLogin() {
    return await Request.send('Login', {
      user: 'test',
      password: '34nf4',
      channel: 'tab1'
    }).catch((err) => {
      console.log('[grpc-error]', err);
    });

  }
}
