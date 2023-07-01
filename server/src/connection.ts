import { ReadlineParser, SerialPort } from "serialport";

const comPort = new SerialPort({
  path: 'COM1',
  baudRate: 9600
});

const parser = comPort.pipe(new ReadlineParser());

let temperature: string;
let distance: string;

export function onComData(func: (temperature: string, distance :string) => void) {
  parser.on('data', (line) => {
    const data = line.split("/");
    
    if (data.length >= 2) {
      temperature = data[0];
      distance = data[1];

      func(temperature, distance); // Call the provided function with the original line
    }
  });
}
comPort.on('error', (err) => {
  console.error('Error:', err);
});