function compress(s: string): string {
    if(s.length === 0) {
        return "";
    }

    const tmp = new Map<string, number>();
    let prev = s[0];
    tmp.set(prev, 1);

    let result = "";

    for(let i = 1; i < s.length; i++) {
        const current = s[i];

        if(current === prev) {
            tmp.set(prev, tmp.get(prev)! + 1);
        } else {
            result += `${prev}${tmp.get(prev)}`;
            tmp.delete(prev);
            tmp.set(current, 1);
            prev = current;
        }
    }

    result += `${prev}${tmp.get(prev)}`

    return (result.length < s.length)? result : s;
}

console.log(compress("aabcccccaaa"))
console.log(compress("x"))
