const path = require("path");
const fs = require("fs");

const filename = "ratings_s.csv";
const myReadStream = fs.createReadStream(path.join(__dirname, filename), "utf-8");

fs.readFile(filename, 'utf8', async function(err, data){
    console.time();
    const lines = data.split("\n").join("").split("\r");
    const bd = new Map();
    const uniqueusers = new Set();
    for(const line of lines) {
        const [idUserStr, idMovieStr, ratingStr] = line.split(",");
        const [idUser, idMovie, rating] = [+idUserStr, +idMovieStr, Number.parseFloat(ratingStr)];
        uniqueusers.add(idUser);

        if(!bd.has(idUser)) {
            bd.set(idUser, new Map());
        }

        bd.get(idUser).set(idMovie, rating);
    }

    const users = [];
    for(const u of uniqueusers) {
        users.push(u);
    }
    const n = users.length;

    const mhdists = [];
    const edists = [];
    function work(i) {
        return new Promise((resolve, reject) => {
            for(let j = i + 1; j < n; j++) {
                const u = users[i];
                const v = users[j];
                //? Calculate Manhattan distance between u and v
                let mhdist = 0;
                let edist = 0;
                for(const [idMovie] of bd.get(u)) {
                    const xx = bd.get(u).get(idMovie);
                    const yy = bd.get(v).get(idMovie) ?? 0;

                    let delta = xx - yy;

                    mhdist += Math.abs(delta);
                    edist += delta * delta;
                }

                for(const [idMovie] of bd.get(v)) {
                    const xx = bd.get(u).get(idMovie) ?? 0;
                    const yy = bd.get(v).get(idMovie);

                    let delta = xx - yy;

                    mhdist += Math.abs(delta);
                    edist += delta * delta;
                }

                mhdists.push(mhdist);
                edists.push(edist);
            }

            return resolve();
        });
    }

    const promises = [];
    for(let u = 0; u < n; u++) {
        promises.push(work(u));
    }

    await Promise.allSettled(promises);
    mhdists.sort(function(a, b){return b - a});
    edists.sort(function(a, b){return b - a});

    const k = 5;
    const best5mhdists = [];
    const best5edists = [];

    for(let i = 0; i < k; i++) {
        best5mhdists[i] = mhdists[i];
        best5edists[i] = edists[i];
    }

    console.log({best5mhdists});
    console.log({best5edists});
    console.timeEnd();
});
