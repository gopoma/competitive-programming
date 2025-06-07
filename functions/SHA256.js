const crypto = require('crypto');

let users = [
    { username: "pruebausuario231", password: "12345", },
    { username: "Gunter132", password: "abcde", },
    { username: "800Enjoyer", password: "Estoesunacontraseña", },
]

function getHash(text) {
    return crypto.createHash('sha256').update(text, 'utf8').digest('hex');
}

users = users.map(user => ({ ...user, password: getHash(user.password) }));
console.table(users);
