import Request from '../libs/request';

export default {
  async checkLogin() {
    const ret = await Request.send('CheckLogin', {
      ts: Date.now().toString()
    }).catch((err) => {
      console.log('[grpc-error]', err);
    });
    console.log(ret);
  }
}
