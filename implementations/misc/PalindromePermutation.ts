function isPermutation(s: string): boolean {
    const tmp = new Map<string, number>();

    const ss = s.toLowerCase();

    for(const c of ss) {
        if(c === " ") continue;

        if(tmp.has(c)) {
            tmp.set(c, tmp.get(c)! + 1);
        } else {
            tmp.set(c, 1);
        }
    }

    const amountOdds = [...tmp.values()].filter((v) => v % 2 !== 0).length

    return amountOdds <= 1;
}

console.log(isPermutation("Tact Coa"));
console.log(isPermutation("amonguSugnomAx"))
