const SerialPort = require('serialport');
const port = new SerialPort('COM3', { baudRate: 115200 });
let str;
// Read the port data
port.on("open", () => {
  console.log('serial port open');
});
port.on('data', data =>{
  str = data.toString(); //Convert to string
  str = str.replace(/\r?\n|\r/g, ""); //remove '\r' from this String
  str = JSON.stringify(str); // Convert to JSON
  str = JSON.parse(str); //Then parse it
});

module.exports = ({ arduino }) => {
    arduino.get('/', async (ctx, next) => {
      console.log('i was here');
      ctx.body = str;
    })
}