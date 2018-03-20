console.log('index.js');
import mongoose from 'mongoose';
import express from 'express';
import cors from 'cors';
import bodyParser from 'body-parser' //easily parse any json requests sent in
import routes from './routes';
var session = require('express-session')
const app = express()

 //we need cors if you want a server to be hosted on a different domain
// and we want clients on the same local host to hit our server. this is a security risk
//to have enabled.
mongoose.connect('mongodb://localhost:27017/projection_db', () => {
    console.log('Connected to mongodb...');
});
//pulls from app.js, now we have access from app anywhere we want to
//not just one file.

//middleware
app.use(bodyParser.json());

/*HTTP is a stateless protocol, which means that web servers don’t keep track of who is visiting a page. 
Displaying specific content to logged-in users require this tracking. Therefore sessions with a session ID are created. 
Cookies are key/value pairs managed by browsers. Those correspond with the sessions of the server.*/

//use sessions for tracking logins
app.use(session({
    secret: 'work hard',
    resave: true,
    saveUninitialized: false
  }));
  
// use it before all route definitions, allows front end vue app to talk to localhost (chrome disabled this by default)
app.use(cors({origin: 'http://localhost:8080'}));

//so everything that involves our API //specifically our CRUD functionality, just so we can distinguish the 
//routes that involve our CRUD functions. 
app.use('/api', routes);
//this makes sense aswell!!!! remember the /get/post//etc, it's literally an API
//as it's essentially like calling these functions within a class, e.g. class.getName

export default app;