const mongoose = require('mongoose');
   async function connect(){
    try {
        await mongoose.connect('mongodb://localhost:27017/database0'), {
            useNewUrlParser :true,
            useUnifiedTopology:true
        };
        console.log("Conncet successfully!!!")
    } catch (error) {
        console.log("Conncet failure!!!")
    }
}
module.exports = {connect}