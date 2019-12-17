import {UserServerClient} from '../libs/server_grpc_web_pb.js';
import Stub from '../libs/server_pb';

const Client = new UserServerClient(`http://${window.location.hostname}:8080`, null, null);

const lower = (str) => (str.replace(/^[A-Z]/g, (L) => L.toLowerCase()));
const Upper = (str) => (str.replace(/^[a-z]/g, (L) => L.toUpperCase()));

export default {
  send(api, params) {
    return new Promise((resolve, reject) => {
      if (!Client[lower(api)]) {
        reject(`Api:${lower(api)} has not been declared`);
        return;
      }
      const request = new Stub[`${api}Request`]();
      for(const key in params) {
        if (params.hasOwnProperty(key)) {
          request[`set${Upper(key)}`](params[key]);
        }
      }
      Client[lower(api)](request, {}, (err, response) => {
        if (err) {
          reject(err);
        } else {
          resolve(response);
        }
      })
    });
  }
}
