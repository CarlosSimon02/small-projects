let screen = document.getElementById("screen");
let ctx = screen.getContext("2d");
let score = document.getElementById("score");
let highscore = document.getElementById("highscore");
let homescreen = document.getElementById("homescreen");
let gameoverscreen = document.getElementById("gameoverscreen");

let mouse = {
    x: undefined,
    y: undefined,
}

let playerSquare = {
    x: screen.width / 2 - 50 / 2,
    y: screen.height - 200,
    width: 50,
    height: 50,
    speed: {
        x: 7,
        y: 0
    },
    bounceSpeed: 9,
    gravity: 0.2,
    direction: {
        x: 0,
        y: 1,
    },
    update: function () {
        //haddle x axis
        if (mouse.x >= this.x && mouse.x <= this.x + this.width) this.direction.x = 0;
        else if (mouse.x > this.x) this.direction.x = 1;
        else if (mouse.x < this.x) this.direction.x = -1;
        this.x += this.direction.x * this.speed.x;

        //handle y axis
        if (this.direction.y == 1) this.speed.y += this.gravity;
        else this.speed.y -= this.gravity;
        this.y += (this.direction.y * this.speed.y);
        if (this.speed.y <= 0) this.direction.y = (1);

    },
    draw: function () {
        ctx.beginPath();
        ctx.fillStyle = "yellow";
        ctx.rect(this.x, this.y, this.width, this.height);
        ctx.fill();
    },
    hasCollideTo: function (whiteBoxes) {
        if (this.direction.y == 1 &&
            (whiteBoxes.y <= this.y + this.height &&
                whiteBoxes.y + whiteBoxes.height >= this.y + this.height) &&
            (whiteBoxes.x <= this.x &&
                whiteBoxes.x + whiteBoxes.width >= this.x ||
                whiteBoxes.x <= this.x + this.width &&
                whiteBoxes.x + whiteBoxes.width >= this.x + this.width)) {
            this.speed.y = this.bounceSpeed;
            this.direction.y = (-1);
            this.y = whiteBoxes.y - this.height;
            return true;
        }
        return false;
    }
}

class whiteBoxes {
    constructor(y, x = Math.random() * screen.width, width = 80, speed = Math.random() * game.level) {
        let dir = [1, -1];

        this.x = x;
        this.y = y;
        this.width = width;
        this.height = 20;
        this.speed = speed;
        this.directionX = dir[Math.floor(Math.random() * 1)];
    }

    update() {
        this.x += this.directionX * this.speed;

        if (this.x <= 0) {
            this.x = 0;
            this.directionX = 1;
        } else if (this.x + this.width >= screen.width) {
            this.x = screen.width - this.width;
            this.directionX = -1;
        }
    }

    draw() {
        ctx.beginPath();
        ctx.fillStyle = "white";
        ctx.rect(this.x, this.y, this.width, this.height);
        ctx.fill();
    }
}

screen.addEventListener('click', function (event) {
    mouse.x = event.clientX - screen.getBoundingClientRect().left;
    mouse.y = event.clientY - screen.getBoundingClientRect().top;
});

let game = {
    whiteBoxes: [],
    screenMoveFlag: false,
    screenUpMax: 0,
    screenUpOffset: 0,
    groundwhiteBoxes: undefined,
    state: undefined,
    level: 0,
    play: function () {

        homescreen.parentNode.removeChild(homescreen);
        this.state = this.gameState;
    },
    restart: function () {
        this.init();
        this.state = this.gameState;
    },
    moveObjectsUp: function () {
        let cameraSpeed = 5;
        if ((this.whiteBoxes[0].y - this.whiteBoxes[1].y) == this.screenUpOffset) {
            this.screenMoveFlag = false;
            this.screenUpOffset = 0;

            if (this.whiteBoxes[0].y > screen.height) {
                this.whiteBoxes.shift();
                this.groundwhiteBoxes = this.whiteBoxes[0];
            }
            return;
        }
        this.screenUpOffset += cameraSpeed;
        playerSquare.y += cameraSpeed;
        for (let i = 0; i < this.whiteBoxes.length; i++) this.whiteBoxes[i].y += cameraSpeed;
    },
    init: function () {
        highscore.innerHTML = (localStorage.getItem("highscore") === null) ? "0000" : parseInt(localStorage.getItem("highscore")).toLocaleString('en-US', {
            minimumIntegerDigits: 4,
            useGrouping: false
        });
        gameoverscreen.parentNode.removeChild(gameoverscreen);
        this.state = this.homeState;
        playerSquare.x = screen.width / 2 - 50 / 2;
        playerSquare.y = screen.height - 200;
        playerSquare.direction.x = 0;
        mouse.x = undefined;
        mouse.y = undefined;
        score.innerHTML = "0000";
        this.whiteBoxes = [];
        this.whiteBoxes.push(new whiteBoxes(screen.height - 30, screen.width / 2 - 190, 380, 0));
        for (let i = 0; i < 4; i++) this.whiteBoxes.push(new whiteBoxes(this.whiteBoxes[this.whiteBoxes.length - 1].y - 150));

        this.groundwhiteBoxes = this.whiteBoxes[0];
    },
    run: function () {
        this.state();
        requestAnimationFrame(this.run.bind(this));
    },
    homeState: function () {
        playerSquare.draw();
    },
    gameState: function () {
        ctx.clearRect(0, 0, screen.width, screen.height);

        for (let i = 0; i < this.whiteBoxes.length; i++) {
            this.whiteBoxes[i].update();
            this.whiteBoxes[i].draw();
            if (playerSquare.hasCollideTo(this.whiteBoxes[i]) && this.groundwhiteBoxes != this.whiteBoxes[i]) {
                this.screenMoveFlag = true;
                if (parseInt(score.innerHTML) % 5 == 0) this.level++;
                    this.whiteBoxes.push(new whiteBoxes(this.whiteBoxes[this.whiteBoxes.length - 1].y - 150));
                score.innerHTML = (parseInt(score.innerHTML) + 1).toLocaleString('en-US', {
                    minimumIntegerDigits: 4,
                    useGrouping: false
                });
            }
        }
        if (this.screenMoveFlag) this.moveObjectsUp();
        if (playerSquare.y > screen.height) {
            if (parseInt(score.innerHTML) > parseInt(highscore.innerHTML)) {
                localStorage.setItem("highscore", parseInt(score.innerHTML));
                highscore.innerHTML = (localStorage.getItem("highscore") === null) ? "0000" : parseInt(localStorage.getItem("highscore")).toLocaleString('en-US', {
                    minimumIntegerDigits: 4,
                    useGrouping: false
                });
            }
            this.level = 0;
            this.state = this.gameOverState;
        }
        playerSquare.update();
        playerSquare.draw();
    },
    gameOverState: function () {
        document.getElementById("body").appendChild(gameoverscreen);
        ctx.clearRect(0, 0, screen.width, screen.height);
        for (let i = 0; i < this.whiteBoxes.length; i++) {
            this.whiteBoxes[i].draw();
        }
        playerSquare.draw
    }
}
game.init();
game.run();

