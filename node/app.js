var Event = require('./models/event.js');
var AlgorithmController = require('./controllers/algorithmController.js');
var algo = null;

Event.listEvents(function(err, res) {
  if (err) {
    console.log(err);
  }
  else {
    console.log(res);
    algo = new AlgorithmController(res);
    algo.launchNearestNeighbors(algo.data, function(err) {
      if (err) console.log("Error launching nearest neighbors algorithm.");
      else {
        Event.getEventById(1032490, function(err, ev) {
        if (!err) {
          algo.nearestNeighbors(ev, function(err, ids) {
            if (err) console.log(err);
            else {
              console.log(ids);
            }
          });
        }
        else console.log(err);
        });
      }
    });
  }
});

/*

Event.searchEvents("Steelers", function(err, events) {
  if (err) {
    console.log(err);
  }
  else {
    var algo = new AlgorithmController(events);
    algo.launchNearestNeighbors(algo.data, function(err) {
      if (err) console.log("Error launching nearest neighbors algorithm.");
      else {
        algo.nearestNeighbors(algo.data[1], function(err, ids) {
          if (err) console.log(err);
          else {
            console.log(ids);

          }
        });
      }
    });

  }
});
*/
/*Event.listEvents(function(err, res) {
  if (err) {
    console.log(err);
  }
  else {
    console.log(res.length);
  }
})

*/
