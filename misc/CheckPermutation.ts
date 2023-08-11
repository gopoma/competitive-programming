function isPermutation(a: string, b: string): boolean {
    const tmp = new Map<string, number>()
    
    for(const c of a) {
        if(tmp.has(c)) {
            tmp.set(c, tmp.get(c)! + 1);
        } else {
            tmp.set(c, 1);
        }
    }

    for(const c of b) {
        if(!tmp.has(c) || tmp.get(c) === 0) {
            return false;
        }

        tmp.set(c, tmp.get(c)! - 1);
    }

    for(const v of tmp.values()) {
        if(v !== 0) {
            return false;
        }
    }

    return true;
}

console.log(isPermutation("abc", "cba"))
console.log(isPermutation("abcxxx", "cbax"))
