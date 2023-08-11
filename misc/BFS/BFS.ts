const mtx: number[][] = [
    [1, 1, 2, 2],
    [1, 3, 3, 2],
    [4, 4, 3, 5],
    [4, 0, 5, 5]
];

function BFS(mtx: number[][], visit: boolean[][], i: number, j: number) {
    const rows = mtx.length;
    const cols = mtx[0].length;
    const directions: [number, number][] = [
        [0, 1],
        [1, 0],
        [0, -1],
        [-1, 0]
    ];

    const value = mtx[i][j];
    const q: [number, number][] = [];

    q.push([i, j]);
    visit[i][j] = true;

    while(q.length !== 0) {
        const [xCord, yCord] = q.shift()!; // q.pop()! for DFS

        for(let k = 0; k < directions.length; k++) {
            const [xDirection, yDirection] = directions[k];

            const xRef = xCord + xDirection;
            const yRef = yCord + yDirection;

            if(xRef >= 0 && yRef >= 0 && xRef < rows && yRef < cols && !visit[xRef][yRef] && mtx[xRef][yRef] === value) {
                q.push([xRef, yRef]);
                visit[xRef][yRef] = true;
            }
        }
    }
}

function countConnectedComponents(mtx: number[][]): number {
    const rows = mtx.length;
    const cols = mtx[0].length;
    const visit: boolean[][] = Array.from({ length: rows }, ee => Array.from({ length: cols }, ee => false));

    let counter = 0;

    for(let i = 0; i < rows; i++) {
        for(let j = 0; j < cols; j++) {
            if(!visit[i][j]) {
                BFS(mtx, visit, i, j);
                counter++;
            }
        }
    }

    return counter;
}

console.log(countConnectedComponents(mtx));
