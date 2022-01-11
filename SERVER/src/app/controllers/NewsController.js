const { request } = require('express');
const { create } = require('../models/Dht11');
const Dht11 = require('../models/Dht11')
class Dht11Controller {
    // GET /news
    index(req, res) {
        Dht11.find({}, function(err, dht11s) {
            if (err) {
                res.status(400).json({ message: 'Can not get data' })
            } else {
                res.status(200).json(dht11s)
            }
        })
    };
    create(req, res) {
        var newDht11 = new Dht11({
            temperatute: req.query.temperature,
            doamdat: req.query.doamdat,
            humidity: req.query.humidity
        })
        newDht11.save(function(err) {
            if (!err) {
                console.log("Saved new dht11 data")
                res.status(200).json({ 'message': 'Success' })
            } else {
                console.log("Get error saved new dht11 data")
                res.status(200).json({ 'message': 'Error' })
            }
        })
    }
}

module.exports = new Dht11Controller();