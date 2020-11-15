var http = require("http");
http.createServer(function(request,response){
	response.writeHead(200,{
		"Content-Type":"text/plain"
	});
	response.write("this is before;Hello World");
	response.end();
}).listen(8100);
console.log("this is after;nodejs start listen 8100 port!");
