
const myURL = 'http://127.0.0.1:8000'

var stage, output;
var pixNum = 20;
// for the canvas
var grid = new Array(pixNum);
for (i=0; i<pixNum; i++) {
  grid[i] = new Array(pixNum);
}
// to send to server
var imageArray = new Array(pixNum);
for (i=0; i<pixNum; i++) {
  imageArray[i] = new Array(pixNum);
}

var mouseClicked = false;
var mouseMoved = false;

function init() {

  stage = new createjs.Stage("canvas");

  // mouseOver refresh rate: 50ms (1s / 20)
  stage.enableMouseOver(20);

  for (i=0; i<pixNum; i++) {
    for (j=0; j<pixNum; j++) {
      var square = new createjs.Shape();
      square.graphics.beginFill("black").drawRect(0, 0, 20, 20);
      square.x = (i*20);
      square.y = (j*20);
      square.alpha = 0.01;
      grid[i][j] = square;
      stage.addChild(grid[i][j]);
      stage.update();
      imageArray[i][j] = 255;
    }
  }

  for (i=0; i<pixNum; i++) {
    for (j=0; j<pixNum; j++) {
      handleEvent(grid[i][j], i, j);
    }
  }

  stage.update();
}

function handleEvent(square, i, j) {
  square.on("click", handleClick, null, false, {m: i, n: j});
  square.on("mouseover", handleClick, null, false, {m: i, n: j});
}

function handleClick(evt, index) {
  var i = index.m;
  var j = index.n;

  if (!mouseClicked && evt.type == "click") {
    mouseClicked = true;
  }

  if (mouseClicked && evt.type == "mouseover") {
    for (p=-2; p<3; p++){
      for (q=-2; q<3; q++){
        // Check if index is out of grid
        if (i+p < 0 || j+q < 0 || i+p > pixNum-1 || j+q > pixNum-1)
          break;

        // drawing black pixels
        evt.target.alpha = 1;
        imageArray[i][j] = 0;
        square = grid[i+p][j+q];

        // drawing light gray pixels
        if (square.alpha != 1 && square.alpha != 0.5){
          square.alpha = 0.25;
          imageArray[i+p][j+q] = Math.round((1-0.25)*255);
        }

        // drawing dark gray pixels
        if (p>= -1 && q >= -1 && p<=1 && q<=1 && square.alpha != 1){
          square.alpha = 0.5;
          imageArray[i+p][j+q] = Math.round(0.5*255);
        }

      }
    }
    mouseMoved = true;
  }

  if (mouseMoved && evt.type == "click") {
    mouseClicked = false;
    mouseMoved = false;
  }

  stage.update();
}


function clear_board(){
  for (i=0; i<pixNum; i++) {
    for (j=0; j<pixNum; j++) {
      grid[i][j].alpha = 0.01;
      imageArray[i][j] = 255;
    }
  }
  stage.update();
}


function postData() {

  // retrieve number entered for training.
  var num = document.getElementById("number");
  // options to send data to server
  const options = {
      method: 'POST',
      body: JSON.stringify([imageArray, num.value]),
      headers: {
          'Content-Type': 'application/json'
      }
  }

  fetch(myURL, options)
  .then(response => response.json())
  .then(json => {
      obj = JSON.parse(json);
      result = obj.replaceAll(",","&nbsp; % <br>").replace("{", "").replace("}", "&nbsp; % "); // formatting
      document.getElementById("return").innerHTML = result;
  })

  clear_board();

}
