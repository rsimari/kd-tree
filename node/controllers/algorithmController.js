
/** handles data processing operations - distributes them to c++ processing **/
var Event = require('../models/event.js');
const numCPUs = require('os').cpus().length;
var execFile = require('child_process').execFile
const path = require('path');
const fs = require('fs');


function AlgorithmController(data) {
  this.data = data;
}

AlgorithmController.prototype.data = {};

AlgorithmController.prototype.nearestNeighbors = function(data, target, callback) {
  //exec and perform analysis in C++
  var program = "../test.n";
  var inputFile = 'input' + '.txt';
  var outputFile = 'output' + '.txt';
  var inputPath = path.join(path.dirname(require.main.filename), inputFile);
  //console.log(inputPath);
  var outputPath = path.join(path.dirname(require.main.filename), outputFile);

  var input = target.data["date"] + '\n';
  input = input + target.data["popularity"] + '\n\n';
  input = input + formatFileString(data, ["date", "popularity"]);

  // write the "under" value to the input files
  fs.writeFile(inputPath, input, function(err) {
    if (err) throw err;
    // once the input file is ready, execute with the input and
    // output paths specified on the command line
    var neighbors;
    execFile(program, [inputPath, outputPath],
        function(error) {
            if (error) throw error;
            fs.readFile(outputPath, function(err, data) {
                if (err) throw err;
                var neighbors = data.toString().split('\n')
                callback(null, neighbors);
            });
        });
    });
};

function formatFileString(data, keys) {
  var result = '';
  for (var i = 0; i < data.length; i++) {
    for (var j = 0; j < keys.length; j++) {
      var eventObj = data[i].data;
      result = result + eventObj[keys[j]] + '\n';
    }
    result += '\n';
  }
  return result;
}

module.exports = AlgorithmController;
