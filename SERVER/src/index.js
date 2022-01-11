const path = require('path');
const express = require('express');
const handlebars = require('express-handlebars');
const morgan = require('morgan');
const { extname } = require('path');
const app = express();
const port = 3000;
const db = require('./config/db');
var fs = require('fs');
var url = require('url');
var http = require('http');
var WebSocket = require('ws');




const route = require('./routes');

db.connect();

// function gửi yêu cầu(response) từ phía server hoặc nhận yêu cầu (request) của client gửi lên

// create http server
var server = http.createServer(app);
var ws = new WebSocket.Server({
    server
});

var clients = [];

function broadcast(socket, data) {
    console.log(clients.length);
    for (var i = 0; i < clients.length; i++) {
        if (clients[i] != socket) {
            clients[i].send(data);
        }
    }
}
ws.on('connection', function(socket, req) {
    clients.push(socket);
    socket.on('message', function(message) {
        console.log('received: %s', message);
        broadcast(socket, message);
    });
    socket.on('close', function() {
        var index = clients.indexOf(socket);
        clients.splice(index, 1);
        console.log('disconnected');
    });
});

app.engine(
    'hbs',
    handlebars({
        extname: '.hbs',
    }),
);



app.set('view engine', 'hbs');
app.set('views', path.join(__dirname, 'resources\\views'));

app.use(express.static(path.join(__dirname, 'public')));

app.use(
    express.urlencoded({
        extended: true,
    }),
);
app.use(express.json());

app.use(morgan('combined'));

route(app);





server.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`);
});