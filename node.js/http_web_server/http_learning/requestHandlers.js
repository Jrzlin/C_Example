/* example exec
var exec = require("child_process").exec;

function start(response){
    console.log("Request handler 'start' was called.");
    
    //exec("ls -lah", ifunction(error, stdout, stderr){
    //    response.writeHead(200, {"Content-Type": "text/plain"});
    //    response.write(stdout);
    //    response.end();
    //});
    exec("find /", { timeout: 10000, maxBuffer: 20000*1024}, 
     function(error, stdout, stderr){
        response.writeHead(200, {"Content-Type": "text/plain"});
        response.write(stdout);
        response.end();
    });
}
*/
var querystring = require("querystring");
fs = require("fs");
formidable = require("formidable");

function start(response){
    console.log("Request heandler 'start' was called\n ==================================\n");
    var body = '<html>'+
        '<head>'+
        '<meta http-equiv="Content-Type" content="text/html"; '+
        'charset=UTF-8 />'+
        '</head>'+
        '<body>'+
//        '<form action="/upload" method="post">'+
//        '<textarea name="text" rows="20" cols="60"></textarea>'+
        '<form action="/upload" enctype="multipart/form-data" '+
        'method="post">'+
        '<input type="file" name="upload" multiple="multiple">'+
        '<input type="submit" value="Submit button" />'+
        '</form>'+
        '</body>'+
        '</html>';

    response.writeHead(200, {"Content-Type": "text/html"});
    response.write(body);
    response.end();
}

function upload(response, request){
    console.log("Request handler 'upload' was called.");
    var form = new formidable.IncomingForm();
    console.log("about to parse");
    form.parse(request, function(error, fields, files){
        console.log("parsing done." + files.upload.path);
        //fs.renameSync(files.upload.path, "/tmp/test.jpg");
        fs.renameSync(files.upload.path, "/tmp/test.jpg");
        response.writeHead(200, {"Content-Type": "text/html"});
        response.write("received image:<br/>");
        response.write("<img src='/show' />");
        response.end();
    });
}

function show(response){
    console.log("Request handler 'show' was called.");
    fs.readFile("/tmp/test.jpg", "binary", function(error, file){
            if(error){
                response.writeHead(500, {"Content-Type": "text/plain"});
                response.write(error + "\n");
                response.end();
            }else{
                response.writeHead(200, {"Content-Type": "image/png"});
                response.write(file, "binary");
                response.end();
            }
    });
}
// nodejs sleep function
//function sleep(milliSeconds) {
//    var startTime = new Date().getTime();
//    while (new Date().getTime() < startTime + milliSeconds);
//}
//sleep(10000);

exports.start = start;
exports.upload = upload;
exports.show = show;
