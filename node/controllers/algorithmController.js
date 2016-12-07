/** handles data processing operations - distributes them to c++ processing **/
var Event = require('../models/event.js');
const numCPUs = require('os').cpus().length;
var execFile = require('child_process').execFile
const spawn = require('child_process').spawn
const path = require('path');
const fs = require('fs');

var handle = null;
var hasCalledLaunch = false;

function AlgorithmController(data) {
  this.data = data;
}

AlgorithmController.prototype.data = {};

AlgorithmController.prototype.nearestNeighbors = function(target, callback) {
  //exec and perform analysis in C++
  if (handle == null) callback(Error("Unitialized nearest neighbor handle."), null);

  console.log(target); 
  var input = target.data["id"] + ', ';
  var targetDate = new Date(target.data["date"]);
  input = input + targetDate.getTime() + ', ';
  input = input + target.data["popularity"] + ', ';
  input = input + target.data["category"]["id"] + '\n';

  var result = '';

  handle.stdout.once("data", function(data) {
    var buff = new Buffer(data);
    var neighbors = buff.toString('utf8').trim().split('\n');
    callback(null, neighbors);
  });

  handle.stdin.write(input);

};

AlgorithmController.prototype.launchNearestNeighbors = function(data, callback) {
  //exec and perform analysis in C++
  if (hasCalledLaunch == false) {

    hasCalledLaunch = true;
    var program = "../nearest";
    var inputFile = 'input' + '.txt';

    var inputPath = path.join(path.dirname(require.main.filename), inputFile);
    //console.log(inputPath);

    var keys = ["id", "date", "popularity", "category"]; //keys to be used in nearest neighbor processing
    var subKeys = ["", "", "id"]; //subkeys of these keys.

    var input = formatFileString(data, keys, ["", "", "", "id"]);
    // write the "under" value to the input files
    fs.writeFile(inputPath, input, function(err) {
      if (err) throw err;
      // once the input file is ready, execute with the input and
      // output paths specified on the command line
      var child = spawn(program, [inputPath]);
      child.on('error', function (err) {
        console.log('Failed to start child process.');
      });

      child.on('close' , (code) => {
        console.log(code);
      });

      handle = child;
      callback(null);

      });
  }
  else callback(null);
};


function formatFileString(data, keys, subkeys) {
  var result = '';
  for (var i = 0; i < data.length; i++) {
    for (var j = 0; j < keys.length; j++) {
      var eventObj = data[i].data;
      if (keys[j] == "date") {
        var date = new Date(eventObj[keys[j]]);
        result = result + date.getTime();
      }
      else if (subkeys[j] != "") {
        if (eventObj[keys[j]] != null) result = result + eventObj[keys[j]][subkeys[j]];
        else result = result + '-1';
      }
      else {result = result + eventObj[keys[j]];}

      if (j == keys.length-1) result+='\n';
      else result+=', ';
    }
  }
  return result;
}

module.exports = AlgorithmController;
