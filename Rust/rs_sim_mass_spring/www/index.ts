import init, { World, Direction, GameStatus } from "sim_mass_spring";
import { rnd } from "./utils/rnd";

init().then((wasm) => {
  const CELL_SIZE = 40;
  const WORLD_WIDTH = 10;
  const snakeSpawnIdx = rnd(WORLD_WIDTH * WORLD_WIDTH);

  const world = World.new(WORLD_WIDTH, snakeSpawnIdx);
  const worldWidth = world.width();

  const points = document.getElementById("points");
  const gameStatus = document.getElementById("game-status");
  const gameControlBtn = document.getElementById("game-control-btn");
  const canvas = document.getElementById("snake-canvas") as HTMLCanvasElement;
  const ctx = canvas.getContext("2d");

  canvas.height = worldWidth * CELL_SIZE;
  canvas.width = worldWidth * CELL_SIZE;

  gameControlBtn?.addEventListener("click", (_) => {
    const gameStatus = world.game_status();
    if (gameStatus === undefined) {
      gameControlBtn.textContent = "Playing...";
      world.start_game();
      play();
    } else {
      location.reload();
    }
  });

  document.addEventListener("keydown", (e) => {
    switch (e.code) {
      case "Space":
        gameControlBtn?.click();
        break;
      case "ArrowUp":
        world.change_snake_dir(Direction.Up);
        break;
      case "ArrowRight":
        world.change_snake_dir(Direction.Right);
        break;
      case "ArrowDown":
        world.change_snake_dir(Direction.Down);
        break;
      case "ArrowLeft":
        world.change_snake_dir(Direction.Left);
        break;
    }
  });

  function drawWorld() {
    if (!ctx) return;

    ctx.fillStyle = "blue";
    ctx.beginPath();
    ctx.roundRect(0, 0, 200, 100, 10);
    ctx.fill();
    // ctx.beginPath();

    // ctx.strokeStyle = "#aaa";
    // for (let x = 0; x < worldWidth + 1; x++) {
    //   ctx.moveTo(CELL_SIZE * x, 0);
    //   ctx.lineTo(CELL_SIZE * x, worldWidth * CELL_SIZE);
    // }

    // for (let y = 0; y < worldWidth + 1; y++) {
    //   ctx.moveTo(0, CELL_SIZE * y);
    //   ctx.lineTo(worldWidth * CELL_SIZE, CELL_SIZE * y);
    // }

    // ctx.stroke();
  }

  function paint() {
    drawWorld();
  }

  function play() {
    if (!gameControlBtn) {
      return;
    }
    const status = world.game_status();

    if (status === GameStatus.Won || status === GameStatus.Lost) {
      gameControlBtn.textContent = "Replay";
      return;
    }

    const fps = 10;
    setTimeout(() => {
      ctx?.clearRect(0, 0, canvas.width, canvas.height);
      world.step();
      paint();
      requestAnimationFrame(play);
    }, 1000 / fps);
  }

  paint();
});
