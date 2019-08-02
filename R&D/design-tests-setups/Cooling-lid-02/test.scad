module cooling_surface(half){
    module object(){
    difference(){
    color("red")
    difference(){
    cylinder(h = 30, r1 = 42, r2 = 42, center = true);
    translate([0,0,-12])
    cylinder(h = 50, r1 = 40, r2 = 40, center = true);
    }
    cube([42,42,40], center=true);
  }
}
    if (half==true){
      difference(){
      object();
      cube([90,90,90]);
      }
    }
    else{
      object();
    }
}

module peltier(){
  color("grey")
  cube([40,40,4], center=true);
}

module fan(){
  import("4-inch-fan.stl");
}

// cooling_surface();
module rotor(){
  translate([18,258,0])
  import("V2_Rotor.stl", convexity=3);
}

module lid(){
  rotate([90,0,0])
  translate([0,-50,0])
  import("mini-fridge/cover.stl");
  translate([0,0,-53])
  rotate([90,0,0])
  import("mini-fridge/cover_2.stl");
}

module polyfuge(){
  import("polyfuge-ref4.stl");
}


/* difference(){ */
  union(){
  rotor();
  translate([0,0,10])cooling_surface();
  translate([0,0,27])peltier();
  union(){
    scale(0.85)translate([0,0,80])color("DarkSlateGray")fan();
    translate([0,0,80])lid();
  }
  translate([95,-80,-30])color("DodgerBlue")polyfuge();

  }
/* translate([-50,0,40])cube([100,150,100],center=true);
} */
