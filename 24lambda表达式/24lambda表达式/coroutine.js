const fs = require('fs/promises')

async function read() {
    const l = await fs.readdir('./')
    console.log(l)
}

read()
console.log('更早运行到这里')
