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
proto.UserAgent.UserServerClient =
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
proto.UserAgent.UserServerPromiseClient =
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
 *   !proto.UserAgent.CheckLoginRequest,
 *   !proto.UserAgent.CheckLoginResponse>}
 */
const methodDescriptor_UserServer_CheckLogin = new grpc.web.MethodDescriptor(
  '/UserAgent.UserServer/CheckLogin',
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
const methodInfo_UserServer_CheckLogin = new grpc.web.AbstractClientBase.MethodInfo(
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
proto.UserAgent.UserServerClient.prototype.checkLogin =
    function(request, metadata, callback) {
  return this.client_.rpcCall(this.hostname_ +
      '/UserAgent.UserServer/CheckLogin',
      request,
      metadata || {},
      methodDescriptor_UserServer_CheckLogin,
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
proto.UserAgent.UserServerPromiseClient.prototype.checkLogin =
    function(request, metadata) {
  return this.client_.unaryCall(this.hostname_ +
      '/UserAgent.UserServer/CheckLogin',
      request,
      metadata || {},
      methodDescriptor_UserServer_CheckLogin);
};


module.exports = proto.UserAgent;

