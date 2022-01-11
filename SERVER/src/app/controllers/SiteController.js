const { request } = require('express')




class SiteController {

    // GET /
    index(req, res) {


        res.render('home')
    }

    // GET /
    nhietdo(req, res) {
        res.render('nhietdo')
    }
    doam(req, res) {

        res.render('doam')
    }


}
module.exports = new SiteController();