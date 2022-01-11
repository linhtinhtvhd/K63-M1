var express = require('express');
var router = express.Router();

var authcontroller = require('../app/controllers/authController');

router.get('/login', authcontroller.login)

module.exports = router;