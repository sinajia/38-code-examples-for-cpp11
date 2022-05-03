function a (x) {
    var i = 1
    var d = 0.15
    return (y) => {
        return i + d + x + y;
    }
}

var fun = a(100)

const v = fun(110)

console.log(v)
