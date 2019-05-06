const SerialPort = require('serialport');
const port = new SerialPort('COM3', { baudRate: 9600 });
let str = "";
// Read the port data
port.on("open", () => {
  console.log('serial port open');
});
port.on('data', data =>{
    let rawData;
    rawData = data.toString(); //Convert to string
    rawData = rawData.replace(/\r?\n|\r/g, ""); //remove '\r' from this String
    rawData = JSON.stringify(rawData); // Convert to JSON
    rawData = JSON.parse(rawData); //Then parse it
    str = str.concat(rawData);
});

module.exports = ({ arduino }) => {
    arduino.get('/', async (ctx, next) => {
      if(str.includes("done") && str.includes("start") && str.lastIndexOf("done") > str.indexOf("start") ){
        const start = str.indexOf("start");
        const end = str.lastIndexOf("done");
        str = str.substring(start + 6, end - 1);
        JSON.stringify(str);
        ctx.body = str;
        str = ""
      } else {
        ctx.body = "Waiting for data"
      }
      let json = JSON.stringify({
        "pin" : parseInt(ctx.query.pin),
        "brightness" : parseInt(ctx.query.brightness),
      })
      port.write(json+"\n");
    })
}