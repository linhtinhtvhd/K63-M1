const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const Dht11 = new Schema({
    temperatute: { type: Number },
    humidity: { type: Number },
    doamdat: { type: Number },
    date: { type: Date, default: Date.now() },

});


module.exports = mongoose.model('Dht11', Dht11);