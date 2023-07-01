# Smart water container for water flowering
## Coursework for 4th term on IoT program in LPNU
## How to run
  1. Clone the repository
  2. Create a database using the schema.sql file
  3. Create server/.env file and add the following lines to it:
     ```
     MYSQL_HOST="your_host_here"
     MYSQL_USER="your_username_here"
     MYSQL_PASSWORD="your_password_here"
     ```
 4. Run ```npm install``` in both server and client folders
 5. Download needed libraries and check whether everything is set up properly
 6. Set up a pairing of vitual COMPs and write down in code through which comport you will hold a connection, also change COMP in Proteus if needed
 7. Run ```npm run start:dev``` on server and ```npm run dev``` on client
