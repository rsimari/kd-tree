/** Ticket Evolution Web Service **/
var https = require("https");
var http = require("http");
var crypto = require('crypto');
var config = require("../conf/config.js").TEvoConf;

function TEvoWebService() {
  this.conf = config;
}

TEvoWebService.prototype.searchEvents = function(options, callback) {
  this.performRequest(options, "GET", "/events/search", function(status, res){
    if (status != 200) {
      callback(Error("Ticket Evolution Error"), null);
    }
    else {
      callback(null, res);
    }
  });
}

TEvoWebService.prototype.listEvents = function(options, callback) {
  this.performRequest(options, "GET", "/events", function(status, res){
    if (status != 200) {
      callback(Error("Ticket Evolution Error"), null);
    }
    else {
      callback(null, res);
    }
  });
}

TEvoWebService.prototype.search = function(options, callback) {
  this.performRequest(options, "GET", "/search", function(status, res){
    if (status != 200) {
      callback(Error("Ticket Evolution Error"), null);
    }
    else {
      callback(null, res);
    }
  });
}

TEvoWebService.prototype.performRequest = function(options, type, path, callback) {
  options.page = 1;
  options.per_page = 8000;
  var pathString = this.buildPathString(options, path);
  var reqString = this.buildReqString(pathString, type);
  var token = this.generateToken(reqString);
  var reqOpts = this.buildReqOptions(pathString, type, token);

  this.executeRequest(reqOpts, function(status, res) {
    callback(status, res);
  });
}


TEvoWebService.prototype.generateToken = function(reqString) {
  var hash = crypto.createHmac('SHA256', this.conf.secret).update(reqString).digest('base64');
  //returns tokenized request string
  return hash;
}

TEvoWebService.prototype.buildPathString = function(options, path) {
  //builds a sorted path string
  var path = '/v' + this.conf["apiVersion"].toString() + path + '?';
  var keys = Object.keys(options);
  keys.sort();

  var i = 0;
  for (i; i < keys.length-1; i++) {
    path = path + keys[i] + '=' + options[keys[i]] + '&';
  }
  path = path + keys[i] + '=' + options[keys[i]];

  //replace spaces with +
  path = path.replace(/ /g, '+');
  console.log(path) ;
  return path;
}

TEvoWebService.prototype.buildReqString = function(pathString, type) {
    return type + " " + this.conf.baseUri + pathString;
  //builds the actual URL string
}

TEvoWebService.prototype.buildReqOptions = function(path, type, token) {
  var reqOpts = {
    hostname: this.conf.baseUri,
    port: 443,
    path: path,
    headers: {
      "Host" : this.conf.baseUri,
      "Accept" : "application/json",
      "X-Signature" : token,
      "X-Token" : this.conf.apiKey
    },
    method: type
  };
  return reqOpts;
  //build req options from options
}

TEvoWebService.prototype.executeRequest = function(options, callback) {
    var req = https.request(options, (res) => {
      //console.log(`STATUS: ${res.statusCode}`);
      //console.log(`HEADERS: ${JSON.stringify(res.headers)}`);
      var output = '';
      res.setEncoding('utf8');
      res.on('data', (chunk) => {
        //console.log(`BODY: ${chunk}`);
        output += chunk;
      });
      res.on('end', () => {
        var resObj = JSON.parse(output);
        //console.log(res);
        callback(res.statusCode, resObj);
      });
    });

    req.on('error', function(err) {
      //console.log(err);
      callback(err, null);
    });
    req.end();
  //actually execute the request.
}

module.exports = TEvoWebService;
