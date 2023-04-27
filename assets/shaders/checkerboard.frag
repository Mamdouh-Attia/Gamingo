#version 330 core

out vec4 frag_color;

// In this shader, we want to draw a checkboard where the size of each tile is (size x size).
// The color of the bottom-left most tile should be "colors[0]" and the 2 tiles adjacent to it
// should have the color "colors[1]".

//TODO: (Req 1) Finish this shader.
// set the size of each tile to
uniform int size = 32;
// set the color of the bottom-left most tile to
uniform vec3 colors[2];

void main(){
    //get the row by dividing the x coordinate of the fragment by the size of each tile
    //as if we are drawing a 2D array of tiles
    //the row is the index of the row of the tile that the fragment is in
    int row = int (gl_FragCoord.x)/size;
    //get the column by dividing the y coordinate of the fragment by the size of each tile
    //the column is the index of the column of the tile that the fragment is in
    int col = int (gl_FragCoord.y)/size;
    //if the sum of the row and column is even, then the tile should be colored with colors[0]
    if (mod((row+col),2.0)==0){
    frag_color = vec4(colors[0], 1.0);
    }else{
    //otherwise, the tile should be colored with colors[1]
    frag_color = vec4(colors[1], 1.0);
    }
}