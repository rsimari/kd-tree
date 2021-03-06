/** event.js **/
var schemas = require("./schemas.js");
var TEvoWebService = require("./tevowebservice.js");
var _ = require("lodash");


function Event(data) {
  this.data = this.sanitize(data);
}

Event.prototype.data = {}

Event.prototype.get = function(name) {
  return this.data[name];
}

Event.prototype.set = function(name, value) {
  this.data[name] = value;
}

Event.searchEvents = function(term, callback) {
  var tevo = new TEvoWebService();
  term = term.replace(/[|;$%@"<>()+,]/g, "");
  var options = {
    q: term
  }

  tevo.searchEvents(options, function(err, res) {
    //create event objects?
    if (!err) {
      //create array of events and return;
      var eventsObj = res.events;
      callback(null, convertToEventArray(eventsObj));
    }
    else {
      callback(err, null);
    }
  });

}

Event.listEvents = function(callback) {
  var tevo = new TEvoWebService();

  tevo.listEvents({}, function(err, res) {
    //create event objects?
    if (!err) {
      //create array of events and return;
      var eventsObj = res.events;
      callback(null, convertToEventArray(eventsObj));
    }
    else {
      callback(err, null);
    }
  });
}

Event.getEventById = function(id, callback) {
  var tevo = new TEvoWebService();

  tevo.showEvent(id, function(err, res){
    if (!err) {
      callback(null, convertToEvent(res));
    }
    else callback(err, null);
  });


}

Event.prototype.save = function(callback) {
  var self = this;
  this.data = this.sanitize(this.data);

  //save to db
}

Event.prototype.sanitize = function(data) {
  data = data || {};
  schema = schemas.event;

  return _.pick(_.defaults(data, schema), _.keys(schema));
}

function convertToEventArray(events) {
  var eventArr = [];
  for (var i = 0; i < events.length; i++) {
    var eventStrObj = events[i];
    var eventObj = convertToEvent(eventStrObj);
    eventArr.push(eventObj);
  }
  return eventArr;
}

function convertToEvent(eventStrObj) {
  var eventObj = {
    id: eventStrObj.id,
    title: eventStrObj.name,
    date: eventStrObj.occurs_at,
    performers: eventStrObj.performances,
    venue:  eventStrObj.venue,
    category: eventStrObj.category,
    etickets: eventStrObj.products_eticket_count,
    seating_chart_url:eventStrObj.configuration.seating_chart.medium,
    popularity: eventStrObj.popularity_score
  }
  return new Event(eventObj);
}

module.exports = Event;
