import { useEffect, useState } from 'react';
import './App.css';

type Data = {
  timestamp: string;
  temperature: number;
  distance: number;
}

function App() {
  const [data, setData] = useState<Data[]>([]);

  const updateData = () => {
    fetch('http://localhost:3000/')
      .then(response => response.json())
      .then(data => (data as Data[])
        .map(row => ({...row, timestamp: new Date(row.timestamp).toLocaleString()}))
      )
      .then(data => setData(data));
  }

  useEffect(() => {
    updateData();
    const id = setInterval(updateData, 60000);
    () => clearInterval(id);
  }, []);

  return (
    <table>
      <thead>
        <tr>
          <th>Time</th>
          <th>Temperature</th>
          <th>Distance</th>
        </tr>
      </thead>
      <tbody>
        {data.map((row, index) => (
          <tr key={index}>
            <td>{row.timestamp}</td>
            <td>{row.temperature}</td>
            <td>{row.distance}</td>
          </tr>
        ))}
      </tbody>
    </table>
  )
}

export default App
