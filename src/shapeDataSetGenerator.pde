void setup(){
  size(28,28);
}


void draw(){
  
  for(int i=0;i<3;i++){
    background(255);
    pushMatrix();
    strokeWeight(3);
    float r = random(4,8);
    float x = random(8,16);
    float y = random(8,16);
    
    stroke(random(100),random(100),random(100));
    translate(x,y);
    if(i == 0){
      circle(0,0,r*2);
      saveFrame("data/circle/circle####.png");
    }else if(i == 1){
      rotate(random(-0.1,0.1));
      square(0,0,r*1.5);
      saveFrame("data/square/square####.png");
    }else{
      rotate(random(-0.1,0.1));
      triangle(-r/2,r,0,-r,r/2,r);
      saveFrame("data/triangle/triangle####.png");
    }
    popMatrix();
  }
  println(frameCount);
  if(frameCount == 5000)
    exit();
}
