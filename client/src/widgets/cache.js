const cacheKey = 'fans';

export default {
  setCache(key, value) {
    if (window.localStorage) {
      let cacheObj = window.localStorage.getItem(cacheKey) || '{}';
      try {
        cacheObj = JSON.parse(cacheObj);
      } catch (e) {
        cacheObj = {};
      }
      cacheObj[key] = value;
      window.localStorage.setItem(cacheKey, JSON.stringify(cacheObj));
      return true;
    } else {
      return false;
    }
  },

  getCache(key) {
    if (window.localStorage) {
      let cacheObj = window.localStorage.getItem(cacheKey) || '{}';
      try {
        cacheObj = JSON.parse(cacheObj);
      } catch (e) {
        cacheObj = {};
      }
      return cacheObj[key];
    } else {
      throw new Error('Client is not support ls');
    }
  },

  getCookie(name) {
    let reg = new RegExp('(^| )' + name + '(?:=([^;]*))?(;|$)'),
      val = document.cookie.match(reg);
    return val ? (val[2] ? decodeURIComponent(val[2]) : '') : null;
  },

  setCookie(name, value, expire = 10800 * 1000) {
    if (typeof value === 'object') {
      value = JSON.stringify(value);
    }
    let expires = "";
    if (expire) {
      const date = new Date();
      date.setTime(date.getTime() + expire);
      expires = "; expires=" + date.toUTCString();
    }
    document.cookie = name + "=" + (value || "") + expires + "; path=/";
  }
};
