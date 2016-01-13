SerialPort = require("serialport").SerialPort
Parsers = require("serialport").parsers
serialport = new SerialPort "/dev/ttyACM0",
   baudRate: 9600
   parser: Parsers.readline("\n")

messages = []
serialport.on 'open', ->
  console.log 'Serial Port Opened'
  serialport.on 'data', (data) ->
      message = JSON.parse(data.toString 'utf8')
      messages.push message
      console.log message.angle
