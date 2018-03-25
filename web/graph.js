var nodeSize = 10;
var maxDistanceSquare = 100;
var dragForce = 10;

function Node(x, y) {
    this.id = x+y;
    this.pos = createVector(x, y);
    this.vel = createVector(0, 0);
    this.acc = createVector(0, 0);
    this.acc.limit(10);
    this.acc.x = 0;
    this.acc.y = 0;
    this.neighbors = [];
    this.selected = false;
    this.marked = false;
}

Node.prototype.link = function(node) {
    this.neighbors.push(node);
}

Node.prototype.unlink = function(node) {
    this.neighbors.splice(this.neighbors.indexOf(node), 1);
}

Node.prototype.unlinkAll = function() {
    for (var neighbor in this.neighbors) {
        this.unlink(neighbor);
    }
}

Node.prototype.setAcc = function(x, y) {
    this.acc.x = x;
    this.acc.y = y;
}

Node.prototype.applyForce = function(forceX, forceY) {
    this.acc.x += forceX;
    this.acc.y += forceY;
}

Node.prototype.update = function(delta) {
    this.vel.add(this.acc);
    this.pos.add(this.vel.mult(delta));
    this.setAcc(0, 0);
    if (this.selected) {
        this.moveTo(mouseX, mouseY);
    }
}

Node.prototype.contains = function(x, y) {
    var dx = x - this.pos.x;
    var dy = y - this.pos.y;
    var d = sqrt(dx*dx + dy*dy);
    return d <= nodeSize;
}

Node.prototype.moveTo = function(x, y) {
    var dx = x - this.pos.x;
    var dy = y - this.pos.y;
    var d = sqrt(dx*dx + dy*dy);
    this.applyForce(dx * d, dy * d);
}

Node.prototype.getNodesOfDistance = function(dist) {
    if (dist == 0) {
        return [this];
    }
    var result = [];
    for (var node in this.neighbors) {
        var neighbor = this.neighbor[node];
        neighbor.marked = true;
        result = result.concat(neighbor.getNodesOfDistance(n - 1));
    }
}

function Edge(nodeStart, nodeEnd) {
    this.nodeStart = nodeStart;
    this.nodeEnd = nodeEnd;
}

function Graph() {
    this.nodes = [];
    this.edges = [];
    this.nodesToDelete = [];
    this.springRestLength = 100;
    this.springFactor = 1;
    this.repulsiveFactor = 6250;
    this.delta = 0.004;
}

Graph.prototype.clear = function() {
    this.nodes.length = 0;
    this.edges.length = 0;
}

Graph.prototype.link = function(node1, node2) {
    for (var node in node1.neighbors) {
        if (node1.neighbors[node] == node2) {
            console.log("nodes already linked");
            return;
        }
    }
    this.edges.push(new Edge(node1, node2));
    node1.link(node2);
    node2.link(node1);
}

Graph.prototype.addNode = function(x, y) {
    this.nodes.push(new Node(x, y));
}

Graph.prototype.deleteNode = function(node) {
    for (var edge in this.edges) {
        if (this.edges[edge].nodeEnd == node) {
            console.log("destroyed");
            this.edges.splice(this.edges.indexOf(edge), 1);
        }
    }
    node.unlinkAll();
    this.nodes.splice(this.nodes.indexOf(node), 1);
}

Graph.prototype.markAll = function(state) {
    for (var node in this.nodes) {
        this.nodes[node] = state;
    }
}

// Graph.prototype.clearNodesToDelete = function() {
//     for (var node in this.nodesToDelete) {
//         this.nodes.splice(this.nodesToDelete[node], 1);
//         this.nodesToDelete.splice(node, 1);
//     }
// }

Graph.prototype.generate = function(nbNodesMax, nbEdgesMax) {
    this.clear();
    var nbNodes = round(random(1, nbNodesMax + 1));
    var nbEdges = round(random(1, nbEdgesMax + 1));
    for (var i = 0; i < nbNodes; i++) {
        var x = random(nodeSize, width - nodeSize);
        var y = random(nodeSize, height - nodeSize);
        this.addNode(x, y);
    }
    for (var i = 0; i < nbEdges; i++) {
        var startNodeIndex = round(random(0, nbNodes - 1));
        var endNodeIndex = round(random(0, nbNodes - 1));
        while (startNodeIndex == endNodeIndex) {
            endNodeIndex = round(random(0, nbNodes - 1));
        }
        // this.edges[i] = new Edge(startNodeIndex, endNodeIndex);
        this.link(this.nodes[startNodeIndex], this.nodes[endNodeIndex]);
    }
}
    
Graph.prototype.generateSquare = function() {
    this.clear();
    this.addNode(100, 100);
    this.addNode(300, 100);
    this.addNode(300, 300);
    this.addNode(100, 300);
    this.addNode(200, 200);
    this.link(this.nodes[0], this.nodes[1]);
    this.link(this.nodes[1], this.nodes[2]);
    this.link(this.nodes[2], this.nodes[3]);
    this.link(this.nodes[3], this.nodes[0]);
    this.link(this.nodes[0], this.nodes[4]);
    this.link(this.nodes[1], this.nodes[4]);
    this.link(this.nodes[2], this.nodes[4]);
    this.link(this.nodes[3], this.nodes[4]);
    //console.log(getNDegreeNeighbors(this, this.nodes[0], 2));
}

Graph.prototype.randomizePos = function() {
    for (var node in this.nodes) {
        this.nodes[node].pos.x = round(random(nodeSize, width - nodeSize));
        this.nodes[node].pos.y = round(random(nodeSize, height - nodeSize));
    }
}

Graph.prototype.update = function() {
    var d = new p5.Vector();
    for (var node in this.nodes) {
        var n = this.nodes[node];
        n.update(this.delta);
    }
}

Graph.prototype.behavior = function() {
    if (algo == 0) {
        this.forceBasedRepulsive();
    }
    else if (algo == 1) {
        this.onlySpringForce();
    }
}

Graph.prototype.onlySpringForce = function() {
    var d = createVector(0, 0);
    var f = createVector(0, 0);
    var dSquared, distance, sMag, rMag;
    for (var edge in this.edges) {
        var startNode = this.edges[edge].nodeStart;
        var endNode = this.edges[edge].nodeEnd;
        d.x = endNode.pos.x - startNode.pos.x;
        d.y = endNode.pos.y - startNode.pos.y;
        dSquared = d.magSq();
        distance = d.mag();
        sMag = this.springFactor * (distance - this.springRestLength);
        f.x = (sMag * d.x) / distance;
        f.y = (sMag * d.y) / distance;
        startNode.applyForce(f.x, f.y);
        endNode.applyForce(-f.x, -f.y);
        for (var start in startNode.neighbors) {
            var startNeighbor = startNode.neighbors[start];
            if (startNeighbor != endNode) {
                d.x = endNode.pos.x - startNeighbor.pos.x;
                d.y = endNode.pos.y - startNeighbor.pos.y;
                dSquared = d.magSq();
                distance = d.mag();
                sMag = this.springFactor * (distance - (this.springRestLength * 2));
                f.x = (sMag * d.x) / distance;
                f.y = (sMag * d.y) / distance;
                startNeighbor.applyForce(f.x, f.y);
                endNode.applyForce(-f.x, -f.y);
            }
        }
        for (var end in endNode.neighbors) {
            var endNeighbor = endNode.neighbors[end];
            if (endNeighbor != startNode) {
                d.x = endNeighbor.pos.x - startNode.pos.x;
                d.y = endNeighbor.pos.y - startNode.pos.y;
                dSquared = d.magSq();
                distance = d.mag();
                sMag = this.springFactor * (distance - (this.springRestLength * 2));
                f.x = (sMag * d.x) / distance;
                f.y = (sMag * d.y) / distance;
                startNode.applyForce(f.x, f.y);
                endNeighbor.applyForce(-f.x, -f.y);
            }
        }
    }
}

Graph.prototype.forceBasedRepulsive = function() {
    var d = createVector(0, 0);
    var f = createVector(0, 0);
    var dSquared, distance, sMag, rMag;
    for (var i = 0; i < (this.nodes.length - 1); i++) {
        for (var j = i + 1; j < this.nodes.length; j++) {
            d.x = this.nodes[j].pos.x - this.nodes[i].pos.x;
            d.y = this.nodes[j].pos.y - this.nodes[i].pos.y;
            if (d.x != 0 || d.y != 0) {
                dSquared = d.magSq();
                distance = d.mag();
                rMag = this.repulsiveFactor / dSquared;
                f.x = (rMag * d.x) / distance;
                f.y = (rMag * d.y) / distance;
                this.nodes[i].applyForce(-f.x, -f.y);
                this.nodes[j].applyForce(f.x, f.y);
            }
        }
    }
    for (var edge in this.edges) {
        var startNode = this.edges[edge].nodeStart;
        var endNode = this.edges[edge].nodeEnd;
        d.x = endNode.pos.x - startNode.pos.x;
        d.y = endNode.pos.y - startNode.pos.y;
        dSquared = d.magSq();
        distance = d.mag();
        sMag = this.springFactor * (distance - this.springRestLength);
        f.x = (sMag * d.x) / distance;
        f.y = (sMag * d.y) / distance;
        startNode.applyForce(f.x, f.y);
        endNode.applyForce(-f.x, -f.y);
    }
}

Graph.prototype.draw = function() {
    stroke(255);
    for (var edge in this.edges) {
        var start = this.edges[edge].nodeStart;
        var end = this.edges[edge].nodeEnd;
        line(start.pos.x, start.pos.y, end.pos.x, end.pos.y);
    }
    noStroke();
    for (var node in this.nodes) {
        if (this.nodes[node].selected) {
            fill(255, 0, 0);
        } else {
            fill(255);
        }
        ellipse(this.nodes[node].pos.x, this.nodes[node].pos.y, nodeSize, nodeSize);
    }
    if (nodeSelectedRight != null) {
        stroke(255);
        line(this.nodes[nodeSelectedRight].pos.x, this.nodes[nodeSelectedRight].pos.y, mouseX, mouseY);
    }
}
