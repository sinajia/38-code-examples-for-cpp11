const fs = require('fs')

fs.readFile('./lambda.js', function (err, data) {
    console.log(data.toString());
})
