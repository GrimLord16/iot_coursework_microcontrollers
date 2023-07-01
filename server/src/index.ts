import express from 'express';
import { onComData } from './connection.js';
import { createData, getData } from './database.js';
import cors from 'cors';


const app = express();
app.use(cors());

const port = 3000;

app.get('/', async (req, res) => {
  const data = await getData();
  res.send(data);
});


app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});


onComData((temperature, distance) => {
  createData(+temperature, +distance).then((result) => {
    console.log(result);
  });
});

