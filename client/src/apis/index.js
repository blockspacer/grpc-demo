import Request from '../libs/request';

export default {
  Login(user, password, channel) {
    return Request.send('Login', {
      user,
      password,
      channel
    });
  },
  CheckLogin(uid, token) {
    return Request.send('CheckLogin', {
      uid,
      token
    });
  },
  Register(user, password) {
    return Request.send('Register', {
      user,
      password
    });
  }
}
