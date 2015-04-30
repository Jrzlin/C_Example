var http = require('http');
var fs = require('fs');
var url = require('url');
var S = require('string');

http.createServer(function(request, response){
        response.writeHead(200,{'Content-Type':'text/plain'});
        //show header
        console.log(request.headers);
        //get original filename
        var filename = S(request.url).chompLeft('/').s;
        console.log("Remote upload filename is " + filename + "\n");
        //set sava filename
        var destinationFile = fs.createWriteStream(filename);
        request.pipe(destinationFile);
        //get file size
        var fileSize = request.headers['content-length'];
        var uploadedBytes = 0;
        request.on('data',function(d){
            uploadedBytes += d.length;
            var p = (uploadedBytes/fileSize) * 100;
            response.write("Uploading " + parseInt(p)+ " %\n");
        });
        //server 
        request.on('end',function(){
            response.end(" == File Upload Complete ==\n");
        //show folder
        console.log("@Query Folder Files ");
        var files=fs.readdirSync('.');
        for(fn in files)
            console.log(files[fn]);
        });
}).listen(8888,function(){
    console.log("Charles Server Started");
    console.log("::: support file upload");
});





