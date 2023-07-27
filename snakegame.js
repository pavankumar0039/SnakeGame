const canvas = document.getElementById("gameCanvas");
const ctx = canvas.getContext("2d");

const blockSize = 20;
const boardSize = 20;
const initialSpeed = 150;
const foodColor = "#f00";
const snakeColor = "#0f0";

let gameboard = new Array(boardSize).fill(0).map(() => new Array(boardSize).fill(-1));
let snake = [{ x: 0, y: 0 }];
let food = {};

function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function drawBlock(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x * blockSize, y * blockSize, blockSize, blockSize);
}

function drawGameBoard() {
    for (let y = 0; y < boardSize; y++) {
        for (let x = 0; x < boardSize; x++) {
            const value = gameboard[y][x];
            if (value === 0) {
                drawBlock(x, y, foodColor);
            } else if (value === 1) {
                drawBlock(x, y, snakeColor);
            } else {
                drawBlock(x, y, "#fff");
            }
        }
    }
}

function generateFood() {
    let x, y;
    do {
        x = getRandomInt(0, boardSize - 1);
        y = getRandomInt(0, boardSize - 1);
    } while (gameboard[y][x] !== -1);

    gameboard[y][x] = 0;
    food = { x, y };
}

function updateSnakePosition() {
    const head = snake[0];
    let newX = head.x;
    let newY = head.y;

    if (direction === "UP") {
        newY--;
    } else if (direction === "RIGHT") {
        newX++;
    } else if (direction === "DOWN") {
        newY++;
    } else if (direction === "LEFT") {
        newX--;
    }

    if (newX < 0 || newX >= boardSize || newY < 0 || newY >= boardSize) {
        endGame();
        return;
    }

    if (gameboard[newY][newX] === 1) {
        endGame();
        return;
    }

    snake.unshift({ x: newX, y: newY });

    if (gameboard[newY][newX] === 0) {
        generateFood();
        speed -= 10;
    } else {
        const tail = snake.pop();
        gameboard[tail.y][tail.x] = -1;
    }

    gameboard[newY][newX] = 1;
}

function endGame() {
    clearInterval(gameLoop);
    alert("Game Over!");
}

let direction = "RIGHT";
let speed = initialSpeed;

document.addEventListener("keydown", (event) => {
    const key = event.keyCode;
    if (key === 37 && direction !== "RIGHT") {
        direction = "LEFT";
    } else if (key === 38 && direction !== "DOWN") {
        direction = "UP";
    } else if (key === 39 && direction !== "LEFT") {
        direction = "RIGHT";
    } else if (key === 40 && direction !== "UP") {
        direction = "DOWN";
    }
});

generateFood();

const gameLoop = setInterval(() => {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    updateSnakePosition();
    drawGameBoard();
}, speed);
