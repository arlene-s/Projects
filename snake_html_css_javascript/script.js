// define HTML elements
// game board does not change
const board = document.getElementById('game-board');
const instructionText = document.getElementById('instruction-text');
const logo = document.getElementById('logo');
const score = document.getElementById('score');
const highScoreText = document.getElementById('highScore');

// define game variables
const gridSize = 20;
// snake will change in size, objects are positions in game map
let snake = [{x: 10, y: 10}]; // initially starts in middle of 20x20 board
let food = generateFood(); // position of food randomized
let highScore = 0;
let direction = 'right';
let gameInterval;
let gameSpeedDelay = 200;
let gameStarted = false;

// draw game map, snake, and food
function draw() {
    board.innerHTML = ''; // set element to empty, will reset board
    drawSnake();
    drawFood();
    updateScore();
}

// draw snake
function drawSnake() {
    // iterate through snake array
    snake.forEach((segment) => {
        // create snake class for each segment
        const snakeElement = createGameElement('div', 'snake');
        // assign snakes position to snake class
        setPosition(snakeElement, segment);
        // add snake class with position to game board
        board.appendChild(snakeElement);
    });
}

// create a snake or food cube/div
function createGameElement(tag, className) {
    const element = document.createElement(tag); // create tag
    element.className = className; // assign a classname for tag
    return element;
}

// set the position of the snake or food on game board
function setPosition(element, position) {
    element.style.gridColumn = position.x; // assign coordinate/position to class
    element.style.gridRow = position.y;
}

// testing draw function, draw snake to game board
//draw();

// draw food onto game board
function drawFood() {
    if (gameStarted) {
        const foodElement = createGameElement('div', 'food'); // create class food
        setPosition(foodElement, food);
        board.appendChild(foodElement);
    }
}


// generate random position for food
function generateFood() {
    const x = Math.floor(Math.random() * gridSize) + 1; // ((0 - 1)*20) + 1
    const y = Math.floor(Math.random() * gridSize) + 1;
    return {x, y};
}


// make snake move
function move() {
    // dont want to alter original snake array
    const head = { ...snake[0]}; // copy of array
    switch (direction) {
        case 'up':
            head.y--; // decrease y position by 1
            break;
        case 'down':
            head.y++; // increase y position by 1
            break;
        case 'right':
            head.x++; // increase x position by 1
            break;
        case 'left':
            head.x--; // decrease x position by 1
            break;
    }

    // adds a head object to the beginning of snake array
    snake.unshift(head);
    // when added, snake array has added coordinate
    // snake not 'moving' - actually growing in direction but removing end piece
    
    //snake.pop();

    if (head.x === food.x && head.y === food.y) {
        // snake eats food, place new food at new position
        food = generateFood();
        increaseSpeed();
        clearInterval(gameInterval); // reset movement
        gameInterval = setInterval(() => {
            move(); // move in direction pressed by user
            checkCollision(); // check if hit walls or itself
            draw(); // 
        }, gameSpeedDelay);
    // add snake body otherwise remove tail end
    } else { 
        snake.pop(); 
    }
}

// // test moving
// setInterval(() => {
//     move(); // move first
//     draw(); // then draw again new posiion
// }, 200);    // for 200 ms

// start game function
function startGame() {
    gameStarted = true; // keep track of a running game
    // when start game hide logo and intro text
    instructionText.style.display = 'none';
    logo.style.display = 'none';
    gameInterval = setInterval(() => {
        move();
        checkCollision();
        draw();
    }, gameSpeedDelay);
}

// key press event listener
function handleKeyPress(event) {
    if (!gameStarted && (event.code === 'Space' || event.key === ' ')) {
        startGame();
    } else {
        switch (event.key) {
            case 'ArrowUp': 
                direction = 'up';
                break;
            case 'ArrowDown':
                direction = 'down';
                break;
            case 'ArrowLeft':
                direction = 'left';
                break;
            case 'ArrowRight':
                direction = 'right';
                break;
        }
    }
}

// when key pressed, call handleKeyPress function, pass in event
document.addEventListener('keydown', handleKeyPress);

function increaseSpeed() {
    // console.log(gameSpeedDelay);
    if (gameSpeedDelay > 150) {
        gameSpeedDelay -= 5;
    } else if (gameSpeedDelay > 100) {
        gameSpeedDelay -= 3;
    } else if (gameSpeedDelay > 50) {
        gameSpeedDelay -= 2;
    } else if (gameSpeedDelay > 25) {
        gameSpeedDelay -= 1;
    }
}

function checkCollision() {
    const head = snake[0];

    // hitting walls
    if (head.x < 1 || head.x > gridSize || head.y < 1 || head.y > gridSize) {
        resetGame();
    }

    // snake collides with itself
    for (let i = 1; i < snake.length; i++) {
        if (head.x === snake[i].x && head.y === snake[i].y) {
            resetGame();
        }
    }
}

function resetGame() {
    updateHighScore();
    stopGame();

    // reset snake's position, direction, and food
    snake = [{x: 10, y: 10}];
    food = generateFood();
    direction = 'right';
    gameSpeedDelay = 200;
    // also want to update the score
    updateScore();
}

function updateScore() {
    const currScore = snake.length - 1; // don't include head
    score.textContent = currScore.toString().padStart(3, '0');
}

function stopGame(){
    clearInterval(gameInterval);
    gameStarted = false;
    instructionText.style.display = 'block';
    logo.style.display = 'block';
}

function updateHighScore(){
    const currentScore = snake.length - 1; 
    if (currentScore > highScore) {
        highScore = currentScore;
        highScoreText.textContent = highScore.toString().padStart(3, '0');
    }
    highScoreText.style.display = 'block';

}