import mysql from 'mysql2';
import dotenv from 'dotenv';
import { DBData } from './types.js';

dotenv.config()

const pool = mysql.createPool({
  host: process.env.MYSQL_HOST,
  user: process.env.MYSQL_USER,
  password: process.env.MYSQL_PASSWORD,
  database: process.env.MYSQL_DATABASE
}).promise()


export async function getData() {
  const [rows] = await pool.query("SELECT * FROM microcontroller ORDER BY created_at DESC LIMIT 10")
  return (rows as DBData[]).map(row => ({
    temperature: row.temperature, 
    distance: row.distance, 
    timestamp: row.created_at.toISOString()
  }));
}

export async function createData(temperature: number, distance: number) {
  const [result] = await pool.query(`
  INSERT INTO microcontroller (temperature, distance)
  VALUES (?, ?)
  `, [temperature, distance])
  return result;
}