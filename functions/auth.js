const bcrypt = require("bcrypt");

(async () => {
    let users = [
        { username: "pruebausuario231", password: "12345", },
        { username: "Gunter132", password: "abcde", },
        { username: "800Enjoyer", password: "Estoesunacontraseña", },
    ];

    const saltRounds = 10;
    for(const user of users) {
        const salt = await bcrypt.genSalt(saltRounds);
        user.password = await bcrypt.hash(user.password, salt);
    }
    console.table(users);
})();
