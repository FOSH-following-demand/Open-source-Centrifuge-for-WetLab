module rotor(){
  translate([18,258,0])
  import("V2_Rotor.stl", convexity=3);
  $fn=64;
  for(i=[0:5]){
    rotate(i*60,[0,0,1])
    translate([0,25,0])
    rotate([0,20,30])cube([2,13,17]);
  }
}

/* rotor(); */
module sample(){
  difference(){
    cylinder(h=20, r=9, center=true);
    cylinder(h=30, r=5.6, center=true);
  }
}

for(i=[0:5]){
  rotate(i*60,[0,0,1])
  union(){
  translate([-25,0,2])rotate([0,45,0])sample();
  translate([12,20,0])rotate([0,-60,0])cube([2,20,27]);
  }
}


module fan(){
  import("4-inch-fan.stl");
}

/* scale(0.85)translate([0,0,0])color("DarkSlateGray",0.25)fan(); */

/* translate([0,60,0])
union(){
sample();
translate([12,-5,2])rotate([0,-50,0])cube([2,27,20],center=true);
} */
