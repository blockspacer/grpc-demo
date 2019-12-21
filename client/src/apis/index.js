import Request from '../libs/request';

export default {
  Login(user, password, channel) {
    return Request.send('Login', {
      user,
      password,
      channel
    }).catch((err) => {
      console.log('[grpc-error]', err);
    });
  },
  CheckLogin(uid, token) {
    return Request.send('CheckLogin', {
      uid,
      token
    }).catch((err) => {
      console.log('[grpc-error]', err);
    })
  },
  Register(user, password) {
    return Request.send('Register', {
      user,
      password
    }).catch((err) => {
      console.log('[grpc-error]', err);
    })
  }
}
