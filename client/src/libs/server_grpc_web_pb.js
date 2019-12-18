/**
 * @fileoverview gRPC-Web generated client stub for UserAgent
 * @enhanceable
 * @public
 */

// GENERATED CODE -- DO NOT EDIT!



const grpc = {};
grpc.web = require('grpc-web');

const proto = {};
proto.UserAgent = require('./server_pb.js');

/**
 * @param {string} hostname
 * @param {?Object} credentials
 * @param {?Object} options
 * @constructor
 * @struct
 * @final
 */
proto.UserAgent.UserServiceClient =
    function(hostname, credentials, options) {
  if (!options) options = {};
  options['format'] = 'text';

  /**
   * @private @const {!grpc.web.GrpcWebClientBase} The client
   */
  this.client_ = new grpc.web.GrpcWebClientBase(options);

  /**
   * @private @const {string} The hostname
   */
  this.hostname_ = hostname;

};


/**
 * @param {string} hostname
 * @param {?Object} credentials
 * @param {?Object} options
 * @constructor
 * @struct
 * @final
 */
proto.UserAgent.UserServicePromiseClient =
    function(hostname, credentials, options) {
  if (!options) options = {};
  options['format'] = 'text';

  /**
   * @private @const {!grpc.web.GrpcWebClientBase} The client
   */
  this.client_ = new grpc.web.GrpcWebClientBase(options);

  /**
   * @private @const {string} The hostname
   */
  this.hostname_ = hostname;

};


/**
 * @const
 * @type {!grpc.web.MethodDescriptor<
 *   !proto.UserAgent.LoginRequest,
 *   !proto.UserAgent.LoginResponse>}
 */
const methodDescriptor_UserService_Login = new grpc.web.MethodDescriptor(
  '/UserAgent.UserService/Login',
  grpc.web.MethodType.UNARY,
  proto.UserAgent.LoginRequest,
  proto.UserAgent.LoginResponse,
  /**
   * @param {!proto.UserAgent.LoginRequest} request
   * @return {!Uint8Array}
   */
  function(request) {
    return request.serializeBinary();
  },
  proto.UserAgent.LoginResponse.deserializeBinary
);


/**
 * @const
 * @type {!grpc.web.AbstractClientBase.MethodInfo<
 *   !proto.UserAgent.LoginRequest,
 *   !proto.UserAgent.LoginResponse>}
 */
const methodInfo_UserService_Login = new grpc.web.AbstractClientBase.MethodInfo(
  proto.UserAgent.LoginResponse,
  /**
   * @param {!proto.UserAgent.LoginRequest} request
   * @return {!Uint8Array}
   */
  function(request) {
    return request.serializeBinary();
  },
  proto.UserAgent.LoginResponse.deserializeBinary
);


/**
 * @param {!proto.UserAgent.LoginRequest} request The
 *     request proto
 * @param {?Object<string, string>} metadata User defined
 *     call metadata
 * @param {function(?grpc.web.Error, ?proto.UserAgent.LoginResponse)}
 *     callback The callback function(error, response)
 * @return {!grpc.web.ClientReadableStream<!proto.UserAgent.LoginResponse>|undefined}
 *     The XHR Node Readable Stream
 */
proto.UserAgent.UserServiceClient.prototype.login =
    function(request, metadata, callback) {
  return this.client_.rpcCall(this.hostname_ +
      '/UserAgent.UserService/Login',
      request,
      metadata || {},
      methodDescriptor_UserService_Login,
      callback);
};


/**
 * @param {!proto.UserAgent.LoginRequest} request The
 *     request proto
 * @param {?Object<string, string>} metadata User defined
 *     call metadata
 * @return {!Promise<!proto.UserAgent.LoginResponse>}
 *     A native promise that resolves to the response
 */
proto.UserAgent.UserServicePromiseClient.prototype.login =
    function(request, metadata) {
  return this.client_.unaryCall(this.hostname_ +
      '/UserAgent.UserService/Login',
      request,
      metadata || {},
      methodDescriptor_UserService_Login);
};


/**
 * @const
 * @type {!grpc.web.MethodDescriptor<
 *   !proto.UserAgent.CheckLoginRequest,
 *   !proto.UserAgent.CheckLoginResponse>}
 */
const methodDescriptor_UserService_CheckLogin = new grpc.web.MethodDescriptor(
  '/UserAgent.UserService/CheckLogin',
  grpc.web.MethodType.UNARY,
  proto.UserAgent.CheckLoginRequest,
  proto.UserAgent.CheckLoginResponse,
  /**
   * @param {!proto.UserAgent.CheckLoginRequest} request
   * @return {!Uint8Array}
   */
  function(request) {
    return request.serializeBinary();
  },
  proto.UserAgent.CheckLoginResponse.deserializeBinary
);


/**
 * @const
 * @type {!grpc.web.AbstractClientBase.MethodInfo<
 *   !proto.UserAgent.CheckLoginRequest,
 *   !proto.UserAgent.CheckLoginResponse>}
 */
const methodInfo_UserService_CheckLogin = new grpc.web.AbstractClientBase.MethodInfo(
  proto.UserAgent.CheckLoginResponse,
  /**
   * @param {!proto.UserAgent.CheckLoginRequest} request
   * @return {!Uint8Array}
   */
  function(request) {
    return request.serializeBinary();
  },
  proto.UserAgent.CheckLoginResponse.deserializeBinary
);


/**
 * @param {!proto.UserAgent.CheckLoginRequest} request The
 *     request proto
 * @param {?Object<string, string>} metadata User defined
 *     call metadata
 * @param {function(?grpc.web.Error, ?proto.UserAgent.CheckLoginResponse)}
 *     callback The callback function(error, response)
 * @return {!grpc.web.ClientReadableStream<!proto.UserAgent.CheckLoginResponse>|undefined}
 *     The XHR Node Readable Stream
 */
proto.UserAgent.UserServiceClient.prototype.checkLogin =
    function(request, metadata, callback) {
  return this.client_.rpcCall(this.hostname_ +
      '/UserAgent.UserService/CheckLogin',
      request,
      metadata || {},
      methodDescriptor_UserService_CheckLogin,
      callback);
};


/**
 * @param {!proto.UserAgent.CheckLoginRequest} request The
 *     request proto
 * @param {?Object<string, string>} metadata User defined
 *     call metadata
 * @return {!Promise<!proto.UserAgent.CheckLoginResponse>}
 *     A native promise that resolves to the response
 */
proto.UserAgent.UserServicePromiseClient.prototype.checkLogin =
    function(request, metadata) {
  return this.client_.unaryCall(this.hostname_ +
      '/UserAgent.UserService/CheckLogin',
      request,
      metadata || {},
      methodDescriptor_UserService_CheckLogin);
};


/**
 * @const
 * @type {!grpc.web.MethodDescriptor<
 *   !proto.UserAgent.RegisterRequest,
 *   !proto.UserAgent.RegisterResponse>}
 */
const methodDescriptor_UserService_Register = new grpc.web.MethodDescriptor(
  '/UserAgent.UserService/Register',
  grpc.web.MethodType.UNARY,
  proto.UserAgent.RegisterRequest,
  proto.UserAgent.RegisterResponse,
  /**
   * @param {!proto.UserAgent.RegisterRequest} request
   * @return {!Uint8Array}
   */
  function(request) {
    return request.serializeBinary();
  },
  proto.UserAgent.RegisterResponse.deserializeBinary
);


/**
 * @const
 * @type {!grpc.web.AbstractClientBase.MethodInfo<
 *   !proto.UserAgent.RegisterRequest,
 *   !proto.UserAgent.RegisterResponse>}
 */
const methodInfo_UserService_Register = new grpc.web.AbstractClientBase.MethodInfo(
  proto.UserAgent.RegisterResponse,
  /**
   * @param {!proto.UserAgent.RegisterRequest} request
   * @return {!Uint8Array}
   */
  function(request) {
    return request.serializeBinary();
  },
  proto.UserAgent.RegisterResponse.deserializeBinary
);


/**
 * @param {!proto.UserAgent.RegisterRequest} request The
 *     request proto
 * @param {?Object<string, string>} metadata User defined
 *     call metadata
 * @param {function(?grpc.web.Error, ?proto.UserAgent.RegisterResponse)}
 *     callback The callback function(error, response)
 * @return {!grpc.web.ClientReadableStream<!proto.UserAgent.RegisterResponse>|undefined}
 *     The XHR Node Readable Stream
 */
proto.UserAgent.UserServiceClient.prototype.register =
    function(request, metadata, callback) {
  return this.client_.rpcCall(this.hostname_ +
      '/UserAgent.UserService/Register',
      request,
      metadata || {},
      methodDescriptor_UserService_Register,
      callback);
};


/**
 * @param {!proto.UserAgent.RegisterRequest} request The
 *     request proto
 * @param {?Object<string, string>} metadata User defined
 *     call metadata
 * @return {!Promise<!proto.UserAgent.RegisterResponse>}
 *     A native promise that resolves to the response
 */
proto.UserAgent.UserServicePromiseClient.prototype.register =
    function(request, metadata) {
  return this.client_.unaryCall(this.hostname_ +
      '/UserAgent.UserService/Register',
      request,
      metadata || {},
      methodDescriptor_UserService_Register);
};


module.exports = proto.UserAgent;

