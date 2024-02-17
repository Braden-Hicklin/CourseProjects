var http = require('http');
var url = require('url');
var fs = require('fs');
var path = require('path');
var express = require('express');
var database = require('Scripts/database.js');

var port = 8080;

console.log("Starting server on port " + port);

http.createServer(function (req, res) {
  if(url.parse(req.url, true).pathname == '/') { 
    req.url = "/main.html"; 
  }
  
  var q = url.parse(req.url, true);
  var filename = "." + q.pathname;
  var content_type = 'text/html'; 
  
  if(q.pathname.endsWith('.css')) {
	  content_type = 'text/css';
  }
  
  fs.readFile(filename, function(err, data) {
    if (err) { 
      res.writeHead(404, {'Content-Type': 'text/html'});
      return res.end("<h1>404 Resource Not Found</h1>");
      
    }
	
    res.writeHead(200, {'Content-Type': content_type});
    res.write(data);
    return res.end();
  });

  router.get('/get_data', function(request, response, next){

    var search_query = request.query.search_query;

    var query = `
    SELECT c1 FROM Monsters5e 
    WHERE c1 LIKE '%${search_query}%' 
    LIMIT 10
    `;

    database.query(query, function(error, data){

        response.json(data);
      });

    });
}).listen(port);
