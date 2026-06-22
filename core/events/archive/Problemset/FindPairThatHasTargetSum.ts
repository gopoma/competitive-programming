function findTargetPair(arr: number[], target: number): [number, number] | [] {
    const tmp = new Set<number>();

    for(const a of arr) {
        const complement = target - a;

        if(tmp.has(complement)) {
            return [complement, a];
        } else {
            tmp.add(a);
        }
    }

    return [];
}

const arr = [-18, 1, 10, 4, 7, -1];
const target = -19;
console.log(findTargetPair(arr, target));
