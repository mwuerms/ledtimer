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
}

//TC20-11RWA
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

//TC20-11RWA
module ledsTC2011RWA_chtholes(loc_res = 32) {
    translate([-6/2*2.54, -38.1/2, 0]) {
        // pins
        color("LightGray") {
            // pins 1 - 7
            translate([0, 0, -4])
            for(n = [0:1:6]) {
                translate([n*2.54, 0, 0])
                rotate([0, 0, 45])
                cylinder(d = 1, h = 5, $fn = loc_res);
            }
            // pins 8 - 14
            translate([0, 38.1, -4])
            for(n = [0:1:6]) {
                translate([n*2.54, 0, 0])
                rotate([0, 0, 45])
                cylinder(d = 1, h = 5, $fn = loc_res);
            }
        }
    }
}
//ledsTC2011RWA();
//ledsTC2011RWA_cut();
//ledsTC2011RWA_chtholes();

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

module buttonTS0266_cutholes(loc_res = 32) {
    // origin: center
    translate([-6.5/2, -4.5/2, -3])
    cylinder(d = 1.5, h = 5, $fn = loc_res);
    translate([-6.5/2, +4.5/2, -3])
    cylinder(d = 1.5, h = 5, $fn = loc_res);
    translate([+6.5/2, -4.5/2, -3])
    cylinder(d = 1.5, h = 5, $fn = loc_res);
    translate([+6.5/2, +4.5/2, -3])
    cylinder(d = 1.5, h = 5, $fn = loc_res);
}

//buttonTS026695();
//buttonTS0266_cut();
//buttonTS0266_cutholes();

module switchMFP140_5x(loc_res = 32, show_origin = 1) {
    // origin: center
    if(show_origin) {
        translate([0, 0, 0])
        origin();
    }
    color("Silver")
    translate([-18.2/2, -6/2, -5.6/2])
    cube([18.2, 6, 5.6]);
    color("Black")
    translate([-2*3.2, 6/2, -3.4/2])
    cube([3.4, 5, 3.4]);
    // pins, 5x
    color("Silver")
    for(n = [0:1:4]) {
        translate([-2*3.2+n*3.2, -3.4-6/2, 0])
        rotate([-90, 0, 0])
        rotate([0, 0, 45])
        cylinder(d = 1, h = 4, $fn = 4);
    }
}

module switchMFP140_5x_cut() {
    translate([-18.6/2, -6.4/2, -6/2])
    cube([18.6, 6.4, 6]);
}
//switchMFP140_5x();
//switchMFP140_5x_cut();


// PEC11S-929K-H/S0015
module rotary_encoder_pec11s_929k(loc_res = 32) {
    // body
    color("DarkGray")
    translate([-16/2, -12/2, 0])
    cube([16, 12, 5]);
    // working contacts
    color("LightGray")
    translate([-16.2/2, -(5/2+1/2), 0.1])
    cube([16.2, 1, 1]);
    color("LightGray")
    translate([0, -(1/2), 0.1])
    cube([16.2/2, 1, 1]);
    color("LightGray")
    translate([-16.2/2, +(5/2-1/2), 0.1])
    cube([16.2, 1, 1]);
    // mounting contacts
    color("LightGray")
    translate([-18/2, +(12/2-2), 0.1])
    cube([18, 1.9, 1]);
    color("LightGray")
    translate([-18/2, -(12/2)+0.1, 0.1])
    cube([18, 1.9, 1]);
    // positioning pegs
    color("DarkGray")
    translate([0, 0, -1.2])
    cylinder(d = 2, h = 1.3, $fn = loc_res);
    color("DarkGray")
    translate([+4.5, 0, -1.2])
    cylinder(d = 1.5, h = 1.3, $fn = loc_res);
    // shaft
    color("DarkGray")
    translate([0, 0, 5])
    cylinder(d = 7, h = 5, $fn = loc_res);
    // kurled head
    color("LightGray")
    translate([0, 0, 5])
    cylinder(d = 5, h = 9, $fn = loc_res);
    color("LightGray")
    translate([0, 0, 5+(9.5-2.9)])
    cylinder(d = 6, h = 2.9, $fn = loc_res);
}
//rotary_encoder_pec11s_929k();

module rotary_encoder_pec11s_929k_cut(loc_res = 32) {
    // body
    translate([-16.6/2, -12.2/2, 0])
    cube([16.6, 12.2, 5.3]);
    // working contacts
    // mounting contacts
    translate([-18/2, -12.2/2, 0])
    cube([18.4, 12.2, 1.4]);
    // positioning pegs
    translate([0, 0, -1.4])
    cylinder(d = 2.4, h = 1.5, $fn = loc_res);
    translate([+4.5, 0, -1.4])
    cylinder(d = 2, h = 1.5, $fn = loc_res);
    // shaft
    translate([0, 0, 5])
    cylinder(d = 7.4, h = 10, $fn = loc_res);
    // kurled head
}
rotary_encoder_pec11s_929k_cut();

module vibra_motor(loc_res = 32) {
    color("LightGray")
    translate([0, 0, 0])
    cylinder(d = 10, h = 3.6, $fn = loc_res);
    // cussion on top
    color("Black")
    translate([0, 0, 0.1])
    cylinder(d = 9, h = 4, $fn = loc_res);
    // el. connection
    translate([-3/2, 9/2, 0.01])
    cube([3, 3, 2]);
}
//vibra_motor();

module vibra_motor_cut(loc_res = 32) {
    translate([0, 0, 0])
    cylinder(d = 11, h = 4.3, $fn = loc_res);
    // cussion on top
    // el. connection
    translate([-3.6/2, 9/2, 0])
    cube([3.6, 3.2, 4.3]);
}
//vibra_motor_cut();
