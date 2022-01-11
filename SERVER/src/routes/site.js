var express = require('express');

var router = express.Router();


const siteController = require('../app/controllers/SiteController');




router.use('/nhietdo', siteController.nhietdo);
router.use('/doam', siteController.doam);
router.use('/', siteController.index);





module.exports = router;