var net = require('net');//Module TCP/IP

var events = require('events'); //Module Events 
var eventEmitter = new events.EventEmitter();

var SOCKET_PAYLOAD = '192.168.1.13';
var PORT_PAYLOAD  = 7891;
		
var SOCKET_PYTHON = '192.168.1.13';
var PORT_PYTHON = 7890;

var bots = [];

var serverPayload = net.createServer(function(socket){
	
	console.log("a client is connected to server payload \n");

	

	socket.on('error', function(exception){
	console.log('an error on socket payload has occured : ' + exception);	
	});

	//Reception des données
	eventEmitter.on('sendingPythontoPayload',function(data){
		console.log('socket payload received this : ' + data + '');
		console.log ('sending command to bot ...');
		socket.write(data);
		//socket.pipe(socket);
		console.log('command sent to bot !\n');
	});
	
	 socket.on('data', function(data){
		console.log('client send this data : ' + data.toString());
		console.log('data has this size : ' + data.length);
		data = data.toString();""
		eventEmitter.emit('sendingPayloadtoPython',data); 
	 });

});

var serverPython = net.createServer(function(socket){
	
	console.log("a client is connected to server python \n");
	socket.on('data', function(data) {
		console.log("data has been received : " + data);
	
		//Envoie de la data à la première socket
		console.log("sending command to " + SOCKET_PAYLOAD + ":" + PORT_PAYLOAD + "...");	
		eventEmitter.emit('sendingPythontoPayload',data); 
		console.log("command send !\n\n");	 
		
		
	});

	eventEmitter.on('sendingPayloadtoPython',function(data){
		console.log('socket python received this : ' + data + '');
		console.log ('sending command to python client');
		socket.write(data);
		console.log('command sent to python client !\n');
	});


	socket.on('end', function(){
		console.log('client ended connection');	
	});
	socket.on('close', function(){
		console.log('connection with client has been closed on server python\n');
	});
	socket.on('error', function(exception){
		console.log('an error on socket python has occured : ' + exception);	
	});
	
});
serverPayload.listen(PORT_PAYLOAD, SOCKET_PAYLOAD);
serverPython.listen(PORT_PYTHON, SOCKET_PYTHON);


