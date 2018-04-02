var algo = 0;
var paused = false;
var debug = false;
var nodeSelectedRight = null;
var graph = new Graph();

var slider = document.getElementById("delta");
var output = document.getElementById("delta_value");
slider.value = graph.delta * 1000;
output.innerHTML = "Delta: "+slider.value / 1000;


function setup() {
    var canvas = createCanvas(800, 600);
    var x = (windowWidth - width) / 2;
    var y = (windowHeight - height) / 2;

    canvas.parent('canvas_container');

    graph.generateSquare();    
}

function draw() {
    background(0);
    if (!paused) {
        graph.behavior();
        graph.update();
    }
    else {
        text("Paused", 10, 20);
    }

    if (debug) {
        fill(255);
        text("Nodes: "+this.graph.nodes.length, 10, 50);
        text("Edges: "+this.graph.edges.length, 10, 70);        
    }
    graph.draw();
}

/////////////////// IO
function keyPressed() {
    switch (keyCode) {
        case 71: // G
            graph.generate(10, 10);        
            break;
        case 79: // O
            debug = !debug;
            break;
        case 80: // P
            pause();
            break;
        case 82: // R
            graph.randomizePos();
            break;
    }
}

function mousePressed() {
    if (mouseButton == LEFT) {
        for (var node in graph.nodes) {
            if (graph.nodes[node].contains(mouseX, mouseY)) {
                graph.nodes[node].selected = true;
            }
        }
    }
    else if (mouseButton == RIGHT) {
        if (keyIsPressed && keyCode == 16) {
            for (var node in graph.nodes) {
                if (graph.nodes[node].contains(mouseX, mouseY)) {
                    graph.deleteNode(graph.nodes[node]);
                }
            }
        } else {
            for (var node in graph.nodes) {
                if (graph.nodes[node].contains(mouseX, mouseY)) {
                    nodeSelectedRight = node;
                    return;
                }
            }
            nodeSelectedRight = null;
            graph.addNode(mouseX, mouseY);
        }
    }
}

function mouseReleased() {
    if (mouseButton == LEFT) {
        for (var node in graph.nodes) {
            graph.nodes[node].selected = false;
        }
    }
    else if (mouseButton == RIGHT) {
        if (nodeSelectedRight != null) {
            for (var node in graph.nodes) {
                if (graph.nodes[node].contains(mouseX, mouseY) && node != nodeSelectedRight) {
                    graph.link(graph.nodes[nodeSelectedRight], graph.nodes[node]);
                }
            }
        }
        nodeSelectedRight = null;
    }
}

slider.oninput = function() {
    graph.delta = this.value / 1000;
    output.innerHTML = "Delta: " + this.value / 1000;
}

//////////////////// END IO

//////////////////// BEGIN INTERFACE
function switchAlgo(version) {
    algo = version;
}

function generate() {
    graph.generate(10, 10);
}

function generateSquare() {
    graph.generateSquare();
}

function randomizePos() {
    graph.randomizePos();
}

function pause() {
    paused = !paused;
}
//////////////////// END INTERFACE
