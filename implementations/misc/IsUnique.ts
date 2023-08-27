function isUnique(s: string): boolean {
    return s.length === new Set(s).size;
}

console.log(isUnique("amonguss"))
