/**
 * Martin Egli
 * 2023-09-13
 */

module origin(col = "red", loc_res = 5, height = 20) {
    color(col)
    cylinder(d1 = 0, d2 = 1, h = 20, $fn = loc_res);
}

//TC20-11RWA
module ledsTC2011RWA(loc_res = 32, show_origin = 1) {
    // origin: center
    if(show_origin) {
        translate([0, 0, 0])
        origin();
    }
    
    translate([-6/2*2.54, -38.1/2, 0]) {
        // pins
        color("LightGray") {
            // pins 1 - 7
            translate([0, 0, -4])
            for(n = [0:1:6]) {
                translate([n*2.54, 0, 0])
                rotate([0, 0, 45])
                cylinder(d = 0.5, h = 4, $fn = 4);
            }
            // pins 8 - 14
            translate([0, 38.1, -4])
            for(n = [0:1:6]) {
                translate([n*2.54, 0, 0])
                rotate([0, 0, 45])
                cylinder(d = 0.5, h = 4, $fn = 4);
            }
        }
        deltax = (37.7-(6*2.54))/2;
        deltay = (53-38.1)/2;
        // case
        color("White")
        translate([-deltax, -deltay, 0])
        cube([37.7-0.1, 53, 8.45]);
        
        deltax2 = (37.7 - 4*7.62)/2;
        deltay2 = (53 - 6*7.62)/2;
        leddia = 5.0;
        color("Red")
        translate([-(deltax-deltax2), -deltay2, 8.45]) {
            for(m = [0:1:6]) {
                for(n = [0:1:4]) {
                    translate([n*7.62, m*7.62, 0])
                    cylinder(d = leddia, h = 0.1, $fn = loc_res);
                }
            }
        }
    }
}//TC20-11RWA
module ledsTC2011RWA_cut(loc_res = 32, cut_height = 10, show_origin = 1) {
    // origin: center
    if(show_origin) {
        translate([0, 0, 0])
        origin();
    }
    
    translate([-6/2*2.54, -38.1/2, 0]) {
        deltax = (37.7-(6*2.54))/2+0.2;
        deltay = (53-38.1)/2+0.2;
        // case
        translate([-deltax, -deltay, 0])
        cube([37.7-0.1+0.2*2, 53+0.2*2, cut_height]);
    }
}
//ledsTC2011RWA();
//ledsTC2011RWA_cut();

//TS02-66-95-BK-260-LCR-D
module buttonTS0266(height = 6, loc_res = 32, show_origin = 1) {
    // origin: center
    if(show_origin) {
        translate([0, 0, 0])
        origin();
    }
    // button
    color("Black")
    translate([0, 0, 0])
    cylinder(d = 4, h = height, $fn = loc_res);
    
    // body
    color("Black")
    translate([-3, -3, 0])
    cube([6, 6, 3.5-0.1]);
    color("LightGray")
    translate([-3, -3, 3.5-0.1])
    cube([6, 6, 0.1]);
    
    // THT
    color("LightGray") {
        translate([-6.5/2, -4.5/2, -3])
        cylinder(d = 1.0, h = 4, $fn = loc_res);
        translate([-6.5/2, +4.5/2, -3])
        cylinder(d = 1.0, h = 4, $fn = loc_res);
        translate([+6.5/2, -4.5/2, -3])
        cylinder(d = 1.0, h = 4, $fn = loc_res);
        translate([+6.5/2, +4.5/2, -3])
        cylinder(d = 1.0, h = 4, $fn = loc_res);
    }
}
module buttonTS026695(loc_res = 32, show_origin = 1) {
    buttonTS0266(9.5, loc_res, show_origin);
}
module buttonTS0266_cut(height = 12, loc_res = 32, show_origin = 1) {
    // origin: center
    if(show_origin) {
        translate([0, 0, 0])
        origin();
    }
    // button
    translate([0, 0, 0])
    cylinder(d = 5, h = height, $fn = loc_res);
    // body
    translate([-3.5, -3.5, 0])
    cube([7, 7, 3.7]);
}

//buttonTS026695();
buttonTS0266_cut();
