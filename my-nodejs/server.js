'use strict';

const express = require('express');

// Constants
const PORT = 8002;

// App
const app = express();
app.get('/', function (req, res) {
  res.send('Hello World, brought to you by NodeJS!\n');
});

app.listen(PORT);
console.log('Running on http://localhost:' + PORT);

