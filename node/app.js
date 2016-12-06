var Event = require('./models/event.js');
var AlgorithmController = require('./controllers/algorithmController.js');

Event.searchEvents("Steelers", function(err, events) {
  if (err) {
    console.log(err);
  }
  else {
    //console.log(res);
    var algo = new AlgorithmController(events);
    algo.nearestNeighbors(algo.data, algo.data[0], function(err, data) {
      console.log(data);
    });
  }
});

/*Event.listEvents(function(err, res) {
  if (err) {
    console.log(err);
  }
  else {
    console.log(res.length);
  }
})

*/
